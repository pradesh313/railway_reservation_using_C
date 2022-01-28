#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

struct user_details
{
    char userid[30],pass[30];
};

struct train_details
{
    long int train_no;
    char train_name[30],source[20],destination[20],dep[6],arr[6];
    int sl,ac3,ac2,ac1;
    struct train_details *next;
};
struct train_details *trains=NULL;

struct tickets
{
    char date[11];
    long int train_no;
    struct passengers *booked;
    struct tickets *next;
};
struct tickets *booked_tickets=NULL;

struct passengers
{
    long int pnr;
    char user_name[30];
    char pname[30];
    int age;
    char sex;
    struct passengers *next;
    char seat_class[5];
};

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

void home_page();
void user_signup();
void user_login();
void admin_login();
void admin_menu();
void delete_trains();
void add_trains();
void disp_trains();
void backup_trains();
void retrieve_trains();
void user_menu(char user[]);
void train_enquiry(char user[]);
void book_tickets(char user[]);
void view_tickets(char user[]);
void seat_available(char user[]);
void cancel_tickets(char user[]);

int main()
{
    home_page();
    return 0;
}

void home_page()
{
    system("cls");
    printf("\n\n\tTrain Ticket Reservation System.....\n\n\n\t 1.Admin Login.\n\t 2.User Login.\n\t 3.User Signup.\n\t-1.Exit Program.\n\n\tEnter your choice: ");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
        case 1: admin_login();
                break;
        case 2: user_login();
                break;
        case 3: user_signup();
                break;
        case -1:printf("\n\n\n\tThank you for visiting the program...!!!");
                break;
        default:printf("\n\n\n\tEnter a valid Choice...!!!");
                delay(3);
                home_page();
                break;
    }
}

void user_signup()
{
    system("cls");
    printf("\n\n\tSignup.....\n");
    struct user_details *new_user,*check_uid;
    new_user=(struct user_details*)malloc(sizeof(struct user_details));
    check_uid=(struct user_details*)malloc(sizeof(struct user_details));
    printf("\n\tEnter your new user id(only alphabets and numbers with 30 characters): ");
    scanf("%s",new_user->userid);
    int i;
    for(i=0;i<strlen(new_user->userid);i++)
    {
        if(!isalnum(new_user->userid[i]))
        {
            printf("\n\n\tThe entered user id is invalid.Returning to home page...!!!");
            delay(3);
            home_page();
        }
    }
    FILE *check_user;
    check_user=fopen("user.txt","r");
    rewind(check_user);
    int flag=0;
    while(fread(check_uid,sizeof(struct user_details),1,check_user))
    {
        if(strcmp(check_uid->userid,new_user->userid)==0)
        {
            flag=1;break;
        }
    }
    fclose(check_user);
    if(flag==1)
    {
        printf("\n\n\tThe entered user id already exist.Returning to home page...!!!");
        delay(3);
        home_page();
    }
    printf("\n\tEnter your new password(below 30 characters): ");
    scanf("%s",new_user->pass);
    FILE *write_user;
    write_user=fopen("user.txt","a");
    fwrite(new_user,sizeof(struct user_details),1,write_user);
    fclose(write_user);
    printf("\n\n\tSignup Successful.Returning to home page...!!!");
    delay(3);
    home_page();
}

void user_login()
{
    system("cls");
    printf("\n\n\tLogin.....\n");
    struct user_details *login_user,*check_uid;
    int flag=0;
    login_user=(struct user_details*)malloc(sizeof(struct user_details));
    printf("\n\tEnter your user id: ");
    scanf("%s",login_user->userid);
    printf("\n\tEnter your password: ");
    scanf("%s",login_user->pass);
    FILE *check_user;
    check_user=fopen("user.txt","r");
    rewind(check_user);
    
    while(fread(check_uid,sizeof(struct user_details),1,check_user))
    {
        if((strcmp(check_uid->userid,login_user->userid)==0)&&(strcmp(check_uid->pass,login_user->pass)==0))
        {
            flag=1;break;
        }
    }
    fclose(check_user);
    if(flag==1)
    {
        printf("\n\tLogin Successful...!!!");
        delay(3);
        user_menu(login_user->userid);
    }
    else
    {
        printf("\n\n\tThe entered user credentials are invalid.Returning to Home Page...!!!");
        delay(3);
        home_page();
    }
}

void admin_login()
{
    system("cls");
    printf("\n\n\tAdministrator Login.....\n"); 
    printf("\n\tEnter Admin Password: ");
    char password[20];
    scanf("%s",password);
    char checker[]="12345678";
    if(strcmp(password,checker)==0)
    {
        printf("\n\n\tAdmin Login Successful...!!!");
        admin_menu();
    }
    else
    {
        printf("\n\n\tAdmin Password is incorrect.Returning to home page....!!!"); 
        delay(3);
        home_page();  
    }
}

void admin_menu()
{
    system("cls");
    printf("\n\n\tWelcome Admin,");
    printf("\n\n\tAdministrator Menu.....\n\n\n\t 1.Add Trains\n\t 2.Delete Trains \n\t 3.View All Trains \n\t 4.Backup Train Details to the Database\n\t 5.Retrieve Train Details from the Database \n\t-1.Logout\n\n\t Enter your Choice: ");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:add_trains();
               break;
        case 2:delete_trains();
               break;
        case 3:disp_trains();
               break;
        case 4:backup_trains();
               break;
        case 5:retrieve_trains();
               break;
        case -1:printf("\n\n\tYou have logged out successfully.....!!!");
                delay(3);
                home_page();
                break;
        default:printf("\n\n\n\tEnter a valid Choice...!!!");
                delay(3);
                admin_menu();
                break;
    }
}

void add_trains()
{
    system("cls");
    printf("\n\n\tAdd Trains.....\n\n\n");
    struct train_details *new_train,*check_trains;
    new_train=(struct train_details*)malloc(sizeof(struct train_details));
    printf("\tEnter Train Number: ");
    scanf("%ld",&new_train->train_no); 
    getchar();
    printf("\n\tEnter Train Name: ");
    gets(new_train->train_name);
    printf("\n\tEnter Source: ");
    gets(new_train->source);
    printf("\n\tEnter Source Departure Time: ");
    gets(new_train->dep);
    printf("\n\tEnter Destination: ");
    gets(new_train->destination);
    printf("\n\tEnter Destination Arrival Time: ");
    gets(new_train->arr);
    printf("\n\tEnter Total Available Tickets in SL Class: ");
    scanf("%d",&new_train->sl);
    printf("\n\tEnter Total Available Tickets in 3AC Class: ");
    scanf("%d",&new_train->ac3);
    printf("\n\tEnter Total Available Tickets in 2AC Class: ");
    scanf("%d",&new_train->ac2);
    printf("\n\tEnter Total Available Tickets in 1AC Class: ");
    scanf("%d",&new_train->ac1);
    new_train->next=NULL;
    if(trains==NULL)
        trains=new_train;
    else
    {
        check_trains=trains;
        while(check_trains->next!=NULL)
            check_trains=check_trains->next;
        check_trains->next=new_train;
    }
    printf("\n\n\n\tDetails of the New Train has been stored successfully. Returning to admin menu.....!!!!");
    delay(3);
    admin_menu();
}

void delete_trains()
{
    system("cls");
    printf("\n\n\tDelete Trains.....");
    printf("\n\n\tEnter the Train Number of the Train to be deleted: ");
    long unsigned int train_no;
    scanf("%lu",&train_no);
    struct train_details *check_train,*prev_train;
    check_train=trains;
    if((check_train->train_no)==train_no)
    {
        trains=trains->next;
        free(check_train);
    }
    else
    {
        while((check_train->train_no!=train_no)&&check_train!=NULL)
        {
            prev_train=check_train;
            check_train=check_train->next;

        }
        if(check_train==NULL)
        {
            printf("\n\n\tTrain Details Not found. Returning to admin menu.....!!!!!");
            delay(3);
            admin_menu();
        }
        else
        {
            prev_train->next=check_train->next;
            free(check_train);
        }
    }
    printf("\n\n\tDetails of the Train has been deleted successfully....!!!!");
    delay(3);
    admin_menu();
}

void disp_trains()
{
    system("cls");
    printf("\n\n\tTrain Details.....");
    printf("\n\n\tTrain Number\t||\tTrain Name\t\t  ||\tSource\t\t  || Departure || Destination\t       ||Arrival|| SL Tickets || 3AC Tickets || 2AC Tickets || 1AC Tickets ");
    struct train_details *disp_train;
    disp_train=trains;
    while(disp_train)
    {
        printf("\n\t   %-5ld\t|| %-30s || %-20s || %s     || %-20s || %s ||    %-3d     ||     %-3d     ||     %-3d     ||     %d",disp_train->train_no,disp_train->train_name,disp_train->source,disp_train->dep,disp_train->destination,disp_train->arr,disp_train->sl,disp_train->ac3,disp_train->ac2,disp_train->ac1);
        disp_train=disp_train->next;
    }
    printf("\n\n\n\n\tPress any key to return to admin menu...!!!");
        getchar();
        getchar();
        printf("\n\n\tReturning to admin menu.....!!!");
        delay(3);
        admin_menu();
}

void backup_trains()
{
    system("cls");
    if(trains==NULL){printf("\n\n\n\tThere is no train stored. Returning to admin page.....!!!");delay(3);admin_menu();}
    FILE *sp;
    remove("trains.txt");
    sp=fopen("trains.txt","w");
    struct train_details *write_train;
    write_train=trains;
    while(write_train)
    {
        fwrite(write_train,1,sizeof(struct train_details),sp);
        write_train=write_train->next;
    }
    fclose(sp);
    printf("\n\n\n\tBackup Successful. Returning to admin page.....!!!");
    delay(3);
    admin_menu();
}

void retrieve_trains()
{
    system("cls");
    FILE *retrieve;
    retrieve=fopen("trains.txt","r");
    if(retrieve==NULL)
    {
        printf("\n\n\tNo backup present. Returning to Admin menu.....!!!");
        delay(3);
        fclose(retrieve);
        admin_menu();
    }
    else
    {
        trains=NULL;
        struct train_details *move_train;
        struct train_details *temp=(struct train_details *)malloc(sizeof(struct train_details));
        rewind(retrieve);
        while(fread(temp, sizeof(struct train_details), 1,retrieve))
        {
            if(trains==NULL)
            {
                trains = move_train=(struct train_details *)malloc(sizeof(struct train_details));
            }
            else
            {
                move_train->next = (struct train_details *)malloc(sizeof(struct train_details));
                move_train= move_train->next;
            }
            move_train->train_no=temp->train_no;
            strcpy(move_train->train_name,temp->train_name);
            strcpy(move_train->source,temp->source);
            strcpy(move_train->destination,temp->destination);
            strcpy(move_train->arr,temp->arr);
            strcpy(move_train->dep,temp->dep);
            move_train->sl=temp->sl;
            move_train->ac3=temp->ac3;
            move_train->ac2=temp->ac2;
            move_train->ac1=temp->ac1;
            move_train->next = NULL;
        }
        printf("\n\n\tDetails retrieved successfully. Returning to Admin menu.....!!!");
        fclose(retrieve);
        delay(3);
        admin_menu();
    }
}

void user_menu(char user[])
{
    system("cls");
    printf("\n\n\tWelcome %s,",user);
    printf("\n\n\tUser Menu.....\n\n\n\t 1.Train Enquiry\n\t 2.Seat Availability \n\t 3.Book Tickets \n\t 4.Cancel Tickets\n\t 5.View Tickets \n\t-1.Logout\n\n\t Enter your Choice: ");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:train_enquiry(user);
               break;
        case 2:seat_available(user);
               break;
        case 3:book_tickets(user);
               break;
        case 4:cancel_tickets(user);
               break;
        case 5:view_tickets(user);
               break;
        case -1:printf("\n\n\tYou have logged out successfully.....!!!");
                delay(3);
                home_page();
                break;
        default:printf("\n\n\n\tEnter a valid Choice...!!!");
                delay(3);
                user_menu(user);
                break;
    }
}

void train_enquiry(char user[])
{
    system("cls");
    printf("\n\n\tTrain Enquiry.....");
    printf("\n\n\tEnter Source: ");
    char source[20];
    getchar();
    gets(source);
    printf("\n\tEnter Destination: ");
    char destination[20];
    gets(destination);
    FILE *retrieve;
    retrieve=fopen("trains.txt","r");
    if(retrieve==NULL)
    {
        printf("\n\n\tNo Trains present. Returning to user menu.....!!!");
        delay(3);
        fclose(retrieve);
        user_menu(user);
    }
    else
    {
        trains=NULL;
        struct train_details *move_train;
        struct train_details *temp=(struct train_details *)malloc(sizeof(struct train_details));
        rewind(retrieve);
        while(fread(temp, sizeof(struct train_details), 1,retrieve))
        {
            if(trains==NULL)
            {
                trains = move_train=(struct train_details *)malloc(sizeof(struct train_details));
            }
            else
            {
                move_train->next = (struct train_details *)malloc(sizeof(struct train_details));
                move_train= move_train->next;
            }
            move_train->train_no=temp->train_no;
            strcpy(move_train->train_name,temp->train_name);
            strcpy(move_train->source,temp->source);
            strcpy(move_train->destination,temp->destination);
            strcpy(move_train->arr,temp->arr);
            strcpy(move_train->dep,temp->dep);
            move_train->sl=temp->sl;
            move_train->ac3=temp->ac3;
            move_train->ac2=temp->ac2;
            move_train->ac1=temp->ac1;
            move_train->next = NULL;
        }
        fclose(retrieve);
    }
    struct train_details *disp_train;
    int flag=0;
    disp_train=trains;
    while(disp_train)
    {
        if((strcmp(disp_train->source,source)==0)&&(strcmp(disp_train->destination,destination)==0))
        {
            flag=1;
            break;
        }
        disp_train=disp_train->next;
    }
    if(flag==0)
    {
        printf("\n\n\tThere are no trains available for this route. Returning to User menu.....!!!");
        delay(3);
        user_menu(user);
    }
    else
    {
        disp_train=trains;
        printf("\n\n\tTrain Number\t||\tTrain Name\t\t  ||\tSource\t\t  || Departure || Destination\t       ||Arrival");
        while(disp_train)
        {
            if((strcmp(disp_train->source,source)==0)&&(strcmp(disp_train->destination,destination)==0))
            printf("\n\t   %-5ld\t|| %-30s || %-20s || %s     || %-20s || %s",disp_train->train_no,disp_train->train_name,disp_train->source,disp_train->dep,disp_train->destination,disp_train->arr);
            disp_train=disp_train->next;
        } 
        printf("\n\n\n\n\tPress any key to return to user menu...!!!");
        getchar();
        printf("\n\n\tReturning to user menu.....!!!");
        delay(3);
        user_menu(user);
    }
}

void seat_available(char user[])
{
    system("cls");
    printf("\n\n\tCheck Seat Availability");
    printf("\n\n\tEnter Train number: ");
    long int train_no;
    scanf("%ld",&train_no);
    printf("\n\tEnter date of Travel (DD/MM/YYYY): ");
    char tdate[11];
    scanf("%s",tdate);
    system("cls");
    FILE *retrieve;
    retrieve=fopen("trains.txt","r");
    if(retrieve==NULL)
    {
        printf("\n\n\tNo backup present. Returning to Admin menu.....!!!");
        delay(3);
        fclose(retrieve);
        user_menu(user);
    }
    else
    {
        trains=NULL;
        struct train_details *move_train;
        struct train_details *temp=(struct train_details *)malloc(sizeof(struct train_details));
        rewind(retrieve);
        while(fread(temp, sizeof(struct train_details), 1,retrieve))
        {
            if(trains==NULL)
            {
                trains = move_train=(struct train_details *)malloc(sizeof(struct train_details));
            }
            else
            {
                move_train->next = (struct train_details *)malloc(sizeof(struct train_details));
                move_train= move_train->next;
            }
            move_train->train_no=temp->train_no;
            strcpy(move_train->train_name,temp->train_name);
            strcpy(move_train->source,temp->source);
            strcpy(move_train->destination,temp->destination);
            strcpy(move_train->arr,temp->arr);
            strcpy(move_train->dep,temp->dep);
            move_train->sl=temp->sl;
            move_train->ac3=temp->ac3;
            move_train->ac2=temp->ac2;
            move_train->ac1=temp->ac1;
            move_train->next = NULL;
        }
        fclose(retrieve);
    }
    struct train_details *find_train=trains;
    while(find_train!=NULL)
    {
        if(find_train->train_no==train_no)
            break;
        find_train=find_train->next;
    }
    if(find_train==NULL)
    {
        printf("\n\n\tTrain not found. Returning to user menu.....!!!");
        delay(3);
        user_menu(user);
    }
    else
    {
        struct tickets *show_tickets;
        show_tickets=booked_tickets;
        struct passengers *btickets;  
        while(show_tickets)
        {
            if((show_tickets->train_no==train_no)&&(strcmp(show_tickets->date,tdate)==0))
                break;
        }
        if(show_tickets==NULL)
        {
            printf("\n\n\tTrain Number\t||\tTrain Name\t\t  ||\tSource\t\t  || Departure || Destination\t       ||Arrival|| SL Tickets || 3AC Tickets || 2AC Tickets || 1AC Tickets ");
            printf("\n\t   %-5ld\t|| %-30s || %-20s || %s     || %-20s || %s ||    %-3d     ||     %-3d     ||     %-3d     ||     %d",find_train->train_no,find_train->train_name,find_train->source,find_train->dep,find_train->destination,find_train->arr,find_train->sl,find_train->ac3,find_train->ac2,find_train->ac1); 
            printf("\n\n\n\n\tPress any key to return to user menu...!!!");
            getchar();
            getchar();
            printf("\n\n\tReturning to user menu.....!!!");
            delay(3);
            user_menu(user);
        }
        else
        {
            btickets=show_tickets->booked;
            int slb=0,ac3b=0,ac2b=0,ac1b=0;
            while(btickets)
            {
                if(strcmp(btickets->seat_class,"SL")==0)
                slb+=1;
                else if(strcmp(btickets->seat_class,"3AC")==0)
                ac3b+=1;
                else if(strcmp(btickets->seat_class,"2AC")==0)
                ac2b+=1;
                else if(strcmp(btickets->seat_class,"1AC")==0)
                ac1b+=1;
                btickets=btickets->next;
            }
            printf("\n\n\tTrain Number\t||\tTrain Name\t\t  ||\tSource\t\t  || Departure || Destination\t       ||Arrival|| SL Tickets || 3AC Tickets || 2AC Tickets || 1AC Tickets ");
            printf("\n\t   %-5ld\t|| %-30s || %-20s || %s     || %-20s || %s ||    %-3d     ||     %-3d     ||     %-3d     ||     %d",find_train->train_no,find_train->train_name,find_train->source,find_train->dep,find_train->destination,find_train->arr,(find_train->sl)-slb,(find_train->ac3)-ac3b,(find_train->ac2)-ac2b,(find_train->ac1)-ac1b); 
            printf("\n\n\n\n\tPress any key to return to user menu...!!!");
            getchar();
            getchar();
            printf("\n\n\tReturning to user menu.....!!!");
            delay(3);
            user_menu(user);
        }
    }
}

void book_tickets(char user[])
{
    system("cls");
    FILE *retrieve;
    retrieve=fopen("trains.txt","r");
    if(retrieve==NULL)
    {
        printf("\n\n\tNo train backup present. Returning to user menu.....!!!");
        delay(3);
        fclose(retrieve);
        user_menu(user);
    }
    else
    {
        trains=NULL;
        struct train_details *move_train;
        struct train_details *temp=(struct train_details *)malloc(sizeof(struct train_details));
        rewind(retrieve);
        while(fread(temp, sizeof(struct train_details), 1,retrieve))
        {
            if(trains==NULL)
            {
                trains = move_train=(struct train_details *)malloc(sizeof(struct train_details));
            }
            else
            {
                move_train->next = (struct train_details *)malloc(sizeof(struct train_details));
                move_train= move_train->next;
            }
            move_train->train_no=temp->train_no;
            strcpy(move_train->train_name,temp->train_name);
            strcpy(move_train->source,temp->source);
            strcpy(move_train->destination,temp->destination);
            strcpy(move_train->arr,temp->arr);
            strcpy(move_train->dep,temp->dep);
            move_train->sl=temp->sl;
            move_train->ac3=temp->ac3;
            move_train->ac2=temp->ac2;
            move_train->ac1=temp->ac1;
            move_train->next = NULL;
        }
        fclose(retrieve);
    }
    printf("\n\n\tBook Tickets.....");
    printf("\n\n\tEnter Train number: ");
    long int train_no;
    scanf("%ld",&train_no);
    FILE *check_train;
    check_train=fopen("trains.txt","r");
    rewind(check_train);
    int flag=0,nop;
    struct train_details *temp=(struct train_details *)malloc(sizeof(struct train_details));
    while(fread(temp, sizeof(struct train_details), 1,check_train))
    {
        if(temp->train_no==train_no)
        {
            flag=1;
            break;
        }
    }
    fclose(check_train);
    if(flag==0)
    {
        printf("\n\n\tTrain not present in the database. Returning to user menu...!!!");
        delay(3);
        user_menu(user);
    }
    else
    {
        printf("\n\tEnter number of passengers: ");
        scanf("%d",&nop);
        printf("\n\tEnter date of Travel (DD/MM/YYYY): ");
        char tdate[11];
        scanf("%s",tdate);
        printf("\n\tEnter Coach class (SL,3AC,2AC,1AC): ");
        char coach_class[10];
        scanf("%s",coach_class);
        struct train_details *find_train=trains;
    while(find_train!=NULL)
    {
        if(find_train->train_no==train_no)
            break;
        find_train=find_train->next;
    }
    if(find_train==NULL)
    {
        printf("\n\n\tTrain not found. Returning to user menu.....!!!");
        delay(3);
        user_menu(user);
    }
    else
    {
        struct tickets *show_tickets;
        show_tickets=booked_tickets;
        struct passengers *btickets;  
        while(show_tickets)
        {
            if((show_tickets->train_no==train_no)&&(strcmp(show_tickets->date,tdate)==0))
                break;
        }
        if(show_tickets==NULL)
        {
            if(strcmp(coach_class,"3AC")==0)
                {
                    if(((find_train->ac3)-nop)<0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
                else if(strcmp(coach_class,"2AC")==0)
                {
                    if(((find_train->ac2)-nop)<=0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
                else if(strcmp(coach_class,"1AC")==0)
                {
                    if(((find_train->ac1)-nop)<0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
                else if(strcmp(coach_class,"SL")==0)
                {
                    if(((find_train->sl)-nop)<0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
        }
        else
        {
            btickets=show_tickets->booked;
            int slb=0,ac3b=0,ac2b=0,ac1b=0;
            while(btickets)
            {
                if(strcmp(btickets->seat_class,"SL")==0)
                slb+=1;
                else if(strcmp(btickets->seat_class,"3AC")==0)
                ac3b+=1;
                else if(strcmp(btickets->seat_class,"2AC")==0)
                ac2b+=1;
                else if(strcmp(btickets->seat_class,"1AC")==0)
                ac1b+=1;
                btickets=btickets->next;
            }
            if(strcmp(coach_class,"3AC")==0)
                {
                    if(((find_train->ac3)-nop)<0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
                else if(strcmp(coach_class,"2AC")==0)
                {
                    if(((find_train->ac2)-nop)<=0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
                else if(strcmp(coach_class,"1AC")==0)
                {
                    if(((find_train->ac1)-nop)<0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
                else if(strcmp(coach_class,"SL")==0)
                {
                    if(((find_train->sl)-nop)<0)
                    {
                        printf("\n\n\tTickets not available. Returning to user menu...!!!");
                        delay(3);
                        user_menu(user);
                    }
                }
        }
    }
        struct passengers *new_pass=NULL,*move_pass=NULL,*next_pass=NULL;
        int i;
        long int pnr_no;
        FILE *pnr;
        pnr=fopen("pnr.txt","r+");
        rewind(pnr);
        fscanf(pnr,"%ld",&pnr_no);
        rewind(pnr);
        fprintf(pnr,"%ld",pnr_no+1);
        fclose(pnr);
        for(i=0;i<nop;i++)
        {
            move_pass=(struct passengers*)malloc(sizeof(struct passengers));
            printf("\n\n\tEnter passenger %d name: ",i+1);
            scanf("%s",move_pass->pname);
            printf("\n\tEnter passenger %d age: ",i+1);
            scanf("%d",&move_pass->age);
            printf("\n\tEnter passenger %d gender (M/F): ",i+1);
            getchar();
            scanf("%c",&move_pass->sex);
            strcpy(move_pass->seat_class,coach_class);
            move_pass->pnr=pnr_no;
            strcpy(move_pass->user_name,user);
            move_pass->next=NULL;
            if(i==0)
            {
                next_pass=move_pass;
                new_pass=move_pass;
            }
            else
            {
                next_pass->next=move_pass;
                next_pass=next_pass->next;
            }
        }
        
        struct tickets *book_tickets;
        book_tickets=booked_tickets;
        if(book_tickets==NULL)
        {
            book_tickets=(struct tickets*)malloc(sizeof(struct tickets));
            book_tickets->train_no=train_no;
            strcpy(book_tickets->date,tdate);
            book_tickets->booked=new_pass;
            booked_tickets=book_tickets;
        }    
        else
        {
            while(book_tickets->next!=NULL)
            {
                if((book_tickets->train_no==train_no)&&(strcmp(book_tickets->date,tdate)==0))
                {
                    if(book_tickets->booked==NULL)
                    {
                        book_tickets->booked=new_pass;
                    }
                    else
                    {
                        struct passengers *booking=book_tickets->booked;
                        while (booking->next!=NULL)
                        {
                            booking=booking->next;
                        }
                        booking->next=new_pass;  
                    }
                    break;
                }
                book_tickets=book_tickets->next;
            }
            if(book_tickets->next==NULL)
            {
                book_tickets->next=(struct tickets*)malloc(sizeof(struct tickets));
                book_tickets=book_tickets->next;
                book_tickets->train_no=train_no;
                strcpy(book_tickets->date,tdate);
                book_tickets->booked=new_pass;
                
            }
        }
        printf("\n\n\t Tickets booked successfully. Returning to user menu.....!!!");
        delay(3);
        user_menu(user);
    }

}

void cancel_tickets(char user[])
{
    system("cls");
    printf("\n\n\t Cancel Ticket.....");
    printf("\n\n\t Enter the pnr number of the ticket to be cancelled: ");
    long int pnr_no;
    int flag=0;
    scanf("%ld",&pnr_no);
    struct tickets *show_tickets;
    show_tickets=booked_tickets;
    struct passengers *btickets=NULL,*prev=NULL;
    while(show_tickets)
    {
        btickets=show_tickets->booked;
        if((strcmp(user,btickets->user_name)==0)&&(btickets->pnr==pnr_no))
            {
                do
                {
                    if((strcmp(user,btickets->user_name)==0)&&(btickets->pnr==pnr_no))
                    {
                        flag=1;
                        prev=btickets;
                        btickets=btickets->next;
                        show_tickets->booked=btickets;
                        free(prev);
                    }
                }while(btickets!=NULL);
            }
        else
        {
            while (btickets)
            {
                if((strcmp(user,btickets->user_name)==0)&&(btickets->pnr==pnr_no))
                {
                    flag=1;
                    prev->next=btickets->next;
                    free(btickets);
                    btickets=prev->next;
                }
                else
                {
                    prev=btickets;
                    btickets=btickets->next;
                }
            }
        }
        if(flag==1)
            break;
        else
        show_tickets=show_tickets->next;
    }
    if(flag==0)
    {
        printf("\n\n\tPNR Invalid. Returning to main menu.....!!!");
        delay(3);
        user_menu(user);
    }
    else
    {
        printf("\n\n\tTicket Cancelled Successfully. Returning to main menu.....!!!");
        delay(3);
        user_menu(user);   
    }
}

void view_tickets(char user[])
{
    system("cls");
    printf("\n\n\tView Tickets......");
    struct tickets *show_tickets;
    show_tickets=booked_tickets;
    struct passengers *btickets;
    printf("\n\n\t PNR No || Train No || Date of Travel || Name \t\t\t\t|| Age || Sex || Class\n");
    while(show_tickets)
    {
        btickets=show_tickets->booked;
        while(btickets)
        {
            if(strcmp(user,btickets->user_name)==0)
                printf("\n\t %ld     || %ld    || %s     || %-30s || %d  ||  %c  || %s",btickets->pnr,show_tickets->train_no,show_tickets->date,btickets->pname,btickets->age,btickets->sex,btickets->seat_class);
            btickets=btickets->next;
        }
        show_tickets=show_tickets->next;
    }
    printf("\n\n\n\n\tPress any key to return to user menu...!!!");
    getchar();
    getchar();
    printf("\n\n\tReturning to user menu.....!!!");
    delay(3);
    user_menu(user);
}