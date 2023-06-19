//Restaurant Management System
//CSA- Group 5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
FILE *fp;
//fp=fopen("Dcvdvd"\\list.txt,"a");
struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};


struct node *headc=NULL,*newnode,*tailc=NULL;
struct node *heada=NULL,*taila=NULL;
struct node *head_s;


void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View Total Sales for the day\n");
    printf("\t\t\t\t\t\t\t2. Add new items in the order menu\n");
    printf("\t\t\t\t\t\t\t3. Delete items from the order menu\n");
    printf("\t\t\t\t\t\t\t4. Update price of an item\n");
    printf("\t\t\t\t\t\t\t5. Display order menu\n");
    printf("\t\t\t\t\t\t\t6. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->"); 
}


void customermenu()
{
    printf("\n\t\t\t\t\t\t\t1. Place your order\n");
    printf("\t\t\t\t\t\t\t2. View your ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Delete ordered list\n");
    printf("\t\t\t\t\t\t\t5. Display final bill\n");
    printf("\t\t\t\t\t\t\t6. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

struct node *createadmin(struct node *head,int data, char foodname[], float price)
{
    newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->price=price;
    newnode->quantity=0;
    strcpy(newnode->foodname,foodname);
    newnode->next=NULL;
    newnode->prev=NULL;

    struct node *temp=head;
    if(temp==NULL)
    {
        heada=taila=newnode;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
        newnode->prev=taila;
        taila=newnode;
    }
    return heada;
}


struct node *createcustomer(struct node *head,int data,int quantity)
{
    newnode=(struct node *)malloc(sizeof(struct node));

    struct node *temp1=heada;
    int flag=0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag=1;
            break;
        }
        temp1=temp1->next;
    }
    if(flag==1)
    {
        newnode->data=data;
        newnode->price=quantity*(temp1->price);
        newnode->quantity=quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next=NULL;
        newnode->prev=NULL;

        struct node *temp=head;
        if(temp==NULL)
        {
            headc=tailc=newnode;
        }
        else
        {
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->prev=tailc;
            tailc=newnode;
            
        }
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headc;
}


void displayList(struct node *head)
{
    struct node *temp1=head;
    if(temp1==NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL){
            if(temp1->quantity==0)
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            }
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }
            temp1=temp1->next;
        }
        printf("\n");
    }
}


struct node *totalsales(int data, int quantity)
{
    newnode=(struct node *)malloc(sizeof(struct node));
    int flag=0;
    struct node *temp1=heada;
    while(temp1->data!=data){
        temp1=temp1->next;
    }
    newnode->data=data;
    newnode->price=quantity*(temp1->price);
    newnode->quantity=quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next=NULL;
    newnode->prev=NULL;

    struct node *temp=head_s;
    if(temp==NULL){
        head_s=newnode;
    }else{
        while(temp->next!=NULL){
            if(temp->data==data){
                flag=1;
                break;
            }
            temp=temp->next;
        }
        if(flag==1)
        {
            temp->quantity+=newnode->quantity;
            temp->price=newnode->price;
        }
        else{
            temp->next=newnode;
        }
    }
    return head_s;
}


void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}


struct node *delete(int data,struct node *head,struct node *tail){
    if(head==NULL){
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }else{
        struct node *temp;
        if(data==head->data){
            temp=head;
            head=head->next;
            if(head!=NULL){
                head->prev=NULL;
            }
            free(temp);
        }else if(data==tail->data){
            temp=tail;
            tail=tail->prev;
            tail->next=NULL;
            free(temp);
        }else{
            temp=head;
            while(temp->data!=data){
                temp=temp->next;
            }
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            free(temp);
        }
    }
    return head;
}


int deleteAdmin(){
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node *temp=heada;
    while(temp!=NULL){
        if(temp->data==num){
            heada=delete(num,heada,taila);
            return 1;
        }
        temp=temp->next;
    }
}


int deletecustomer()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}


void displaybill(){
    displayList(headc);
    struct node *temp = headc;
    float total_price=0;
    while(temp!=NULL){
        total_price += temp->price;
        temp=temp->next;
    }

     printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",total_price);
}

struct node *deleteList(struct node *head){
    if(head==NULL){
        return NULL;
    }
    else{
        struct  node *temp=head;
        while(temp->next!=0){
            temp=temp->next;
            free(temp->prev);
        }
        free(temp);
        head=NULL;   
    }
    return head;
}

int updatePrice(){
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be Updated: ");
    int num;
    scanf("%d",&num);
    struct node *temp;
    temp=heada;
    while(temp->data!=num && temp!=NULL){
        temp=temp->next;
    }
    if(temp==NULL){
        printf("\t\t\t\t\t\t\tThis item is not present in the menu");
        return 0;
    }
    printf("\n\t\t\t\t\tEnter the new price of the item: ");
    int p;
    scanf("%d",&p);    
    temp->price = p;
    return 1;

}

int arrayEqual(char name1[],char name2[]){
    int len1=0;
    int len2=0;
    
    while(name1[len1]!='\0'){
        len1+=1;
    }
    while(name2[len2]!='\0'){
        len2+=1;
    }

    if(len1!=len2){
        return 0;
    }
    else{
        for(int i=0;i<len1;i++){
            if(name1[i]!=name2[i]){
                return 0;
            }
        }
    }
    return 1;
}


void feedback(){
    float rating;
    printf("Thank you!, please rate our overall service in range of (0-5): ");
    scanf("%d",&rating);
}


void admin(){
    fp=fopen("C:\\Users\\Ajinkya\\OneDrive\\Documents\\Data Structure\\list.txt","a");
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1){
        adminmenu();

        int opt;
        scanf("%d",&opt);

        if(opt==6){
            break;
        }

        switch(opt){
            case 1:
                displayList(head_s);
                break;
            case 2:
                fp=fopen("C:\\Users\\Ajinkya\\OneDrive\\Documents\\Data Str cpp\\menu.txt","a");
                printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);
                printf("\n\t\t\t\t\t\t\tEnter name of the food item: ");
                scanf("%s",name);
                struct node *temp=heada;
                while(temp!=NULL){
                    if(temp->data==num || arrayEqual(temp->foodname,name)){
/* %% */                printf("\n\t\t\t\t\t\t\tFood item already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp=temp->next;
                }
                if(flag==1){
                    break;
                }

           
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f",&price);
                heada = createadmin(heada,num,name,price);
                struct node *temp1=heada;
                while(temp1->data!=num)
                {
                    temp1=temp1->next;
                }
                fprintf(fp,"%d %s %.2f\n",temp1->data,temp1->foodname,temp1->price);
                printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;

            case 3:
            if(deleteAdmin()){
/* %% */        printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
                displayList(heada);
            }
            else{
                printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");
            }
            break;

            case 4:
                if(updatePrice())
                {
                    printf("\n\t\t\t\t\t\t\t   ### Updated menu ###\n");
                    displayList(heada);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;

            case 5:
            printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
            displayList(heada);
            break;

            default:
            printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            break;


        }
    }
}

void customer(){
    int flag=0,j=1;
    char ch;
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1){
        customermenu();

        int opt;
        scanf("%d",&opt);

        if(opt==6){
            break;
        }

        switch(opt){
            case 1:
                int choice = 1;
                while(choice == 1){
                    displayList(heada);
                    printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                    int n;
                    scanf("%d",&n);
                    printf("\t\t\t\t\t\tEnter quantity: ");
                    int quantity;
                    scanf("%d",&quantity);
                    headc = createcustomer(headc,n,quantity);
                    printf("\t\t\t\t\t\tEnter 1 to add more items: ");
                    scanf("%d",&choice);
                }
                break;
            case 2:
                printf("\n\t\t\t\t\t\t\t  ### List of ordered items ###\n");
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    printf("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
                    displayList(headc);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                headc = deleteList(headc);
                break;
            case 5:
                calculatetotsales();
                printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
                displaybill();
                headc = deleteList(headc);
                feedback();
                printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
        if(flag==1)
            break;
    }
}



void mainMenu()
{
    printf("\n                                 **************************************************************************\n");
    printf("                                                     RESTAURANT MANAGEMENT SYSTEM BY G5\n");
    printf("                                 **************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. Exit--> \n\n");
    printf("\t\t\t\t\t\t\tPlease Enter Your Choice --->");
}


int main()
{
    heada=createadmin(heada,1,"Tomato Soup",90);
    heada=createadmin(heada,2,"Mango Juice",60);
    while(1)
    {
        mainMenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
            break;
        }

        switch(choice)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;
            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }


    return 0;
}