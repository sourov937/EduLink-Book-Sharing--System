#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char Name[35];
    char Student_ID[25];
    int Semester;
    char Hash_Password[70];
} st;

typedef struct {
    char Subject[20];
    char Title[50];
    char Author[40];
    char Condition[15];
    char Availability[15];
    char Book_Owner_ID[25];
    int Semester;
} book;

typedef struct {
    char Book_Title[50];
    char Student_ID[25];
    char Borrow_Date[15];
    char Return_Date[15];
} borrow;

typedef struct {
    char Book_Title[50];
    char Student_ID[25];
    char Review[200];
} review;

void Reg_Student();
void Log_In(char Student_ID[25]);
void Book_Menu(char Student_ID[25]);
void Book_List_Option(char Student_ID[25]);
void Hash_Password(const char *password, char *hashedPassword);
void Brain_Teaser();
void Borrow_Book(char Student_ID[25]);
void View_Borrow_History(char Student_ID[25]);
void View_Books();
void Study_Tips();
void Add_Review(char Student_ID[25]);
void View_Reviews();
void Show_Reminders(char Student_ID[25]);

void Hash_Password(const char *password, char *hashedPassword) {
    unsigned int hash = 5381;
    int c;
    while ((c = *password++)) {
        hash = ((hash << 5) + hash) + c;
    }
    sprintf(hashedPassword, "%u", hash);
}

void Reg_Student() {
    st S;
    char password[50];
    printf("Enter Your Name: ");
    //getchar();
    scanf("%[^\n]", S.Name);
    printf("Enter ID: ");
    getchar();
    scanf("%[^\n]", S.Student_ID);
    printf("Enter Semester: ");
    scanf("%d", &S.Semester);
    printf("Enter Password: ");
    getchar();
    scanf("%[^\n]", password);

    Hash_Password(password, S.Hash_Password);

    FILE *file = fopen("Students_Information.txt", "a");
    if (file == NULL) {
        printf("Error saving information.\n");
        return;
    }
    fprintf(file, "%s %s %d %s\n", S.Name, S.Student_ID, S.Semester, S.Hash_Password);
    fclose(file);
    printf("     --> Congrats! Registration Successful!\n");
    printf("       --->  Your Information Stored Carefully.  :>) ");
}

void Log_In(char Student_ID[25]) {
    FILE *file = fopen("Students_Information.txt", "r");
    st S;
    int f = 0;
    char input_password[50], hashed_input[70];

    if (file == NULL) {
        printf("   ERROR 404! :<(  Please try again.\n");
        return;
    }
    printf("Enter Password: ");
    getchar();
    scanf("%[^\n]", input_password);
    Hash_Password(input_password, hashed_input);

    while (fscanf(file, "%s %s %d %s", S.Name, S.Student_ID, &S.Semester, S.Hash_Password) != EOF) {
        if (strcmp(S.Student_ID, Student_ID) == 0 && strcmp(S.Hash_Password, hashed_input) == 0) {
            f = 1;
            break;
        }
    }
    fclose(file);

    if (f == 1) {
        printf("\nLogin successful!\n");
        Book_Menu(Student_ID);
    } else {
        printf("\nLogin failed. Please confirm your registration. :<( \n");
    }
}

void Book_Menu(char Student_ID[25])
{
    book B;
    int b;
    while(1)
    {
    printf("       \n\n -> Book Menu -> \n\n");
    printf("1) Add a book to the list.\n2) View Books from the list.\n3) Borrow a book.\n4) View Borrow History. \n5) Brain Teaser.\n6) View reminders.\n7) Study Tips.\n8) Add a book review.\n9) View book reviews.\n10) Logout.\n11) Exit. ");
    printf("\n  -->> Select an option: ");
    scanf("%d", &b);
    //getchar();

    switch (b)
    {
    case 1:
        Book_List_Option(Student_ID);
        break;
    case 2:
        View_Books();
        break;
    case 3:
        Borrow_Book(Student_ID);
        break;
    case 4:
        View_Borrow_History(Student_ID);
        break;
    case 5:
        Brain_Teaser();
        break;
    case 6:
        Show_Reminders(Student_ID);
        break;
    case 7:
        Study_Tips();
        break;
    case 8:
        Add_Review(Student_ID);
        break;
    case 9:
        View_Reviews(Student_ID);
        break;
    case 10:
        printf("Logging out...\n");
        return;
    case 11:
        printf("Exiting the program.\n");
        exit(0);
    default:
        printf("ERROR 404! Please choose correctly.\n");
    }
        printf("\n ---> Press Enter to go back to main menu.\n");
        getchar(); getchar();
    }
}

void Book_List_Option(char Student_ID[25])
{
    book B;
    printf("Subject: ");
    scanf(" %[^\n]", B.Subject);
    printf("Enter the Title of the BOOK (No white space): ");
    scanf(" %[^\n]", B.Title);
    printf("Enter the Author: ");
    scanf(" %[^\n]", B.Author);
    printf("Condition (New/Used): ");
    scanf(" %[^\n]", B.Condition);
    printf("Availability (Yes/No): ");
    scanf(" %[^\n]", B.Availability);
    printf("Semester: ");
    scanf("%d", &B.Semester);
    getchar();

    strcpy(B.Book_Owner_ID, Student_ID);

    FILE *file = fopen("Books_Information.txt", "a");

    if(file == NULL)
    {
        printf("ERROR 404! Failed to save Book's information. Please try again. :( ");
    }
    else
    {
        fprintf(file, "%s %s %s %s %s %s %d\n", B.Subject, B.Title, B.Author, B.Condition, B.Availability, B.Book_Owner_ID, B.Semester);
        fclose(file);
        printf("  \n**Book has been successfully added to the list.**\n");
    }
}

void Borrow_Book(char Student_ID[25])
{
    borrow r;
    book B;
    int f = 0;

    printf("Enter Book Title to Borrow: ");
    getchar();
    scanf("%[^\n]", r.Book_Title);
    strcpy(r.Student_ID, Student_ID);

    FILE *original = fopen("Books_Information.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (original == NULL || temp == NULL) {
        printf("Error accessing book list.\n");
        return;
    }
    while (fscanf(original, "%s %s %s %s %s %s %d",
                  B.Subject, B.Title, B.Author, B.Condition,
                  B.Availability, B.Book_Owner_ID, &B.Semester) != EOF)
    {
        if (strcmp(B.Title, r.Book_Title) == 0 && strcmp(B.Availability, "Yes") == 0) {
            f = 1;
            strcpy(B.Availability, "No");
            printf("\n -> Book found and available. If you want to borrow it then enter your borrowing & returning date- \n");
        }
        fprintf(temp, "%s %s %s %s %s %s %d\n",
                B.Subject, B.Title, B.Author, B.Condition,
                B.Availability, B.Book_Owner_ID, B.Semester);
    }
    fclose(original);
    fclose(temp);
    if (f == 1) {
        remove("Books_Information.txt");
        rename("temp.txt", "Books_Information.txt");

        printf("Enter Borrow Date (Day-Month-Year): ");
        scanf("%s", r.Borrow_Date);
        printf("Enter Return Date (Day-Month-Year): ");
        scanf("%s", r.Return_Date);

        FILE *borrowFile = fopen("Borrow_Information.txt", "a");
        if (borrowFile == NULL) {
            printf("Error saving borrow information.\n");
            return;
        }
        fprintf(borrowFile, "%s %s %s %s\n", r.Book_Title, r.Student_ID, r.Borrow_Date, r.Return_Date);
        fclose(borrowFile);
        printf("\n---->>> Book Borrowed Successfully.\n");
    } else {
        remove("temp.txt");
        printf("\n**Sorry! Book not found or already borrowed.**\n");
    }
}
void View_Borrow_History(char Student_ID[25])
{
    borrow r;
    FILE *file = fopen("Borrow_Information.txt", "r");
    printf("\n *^^*Your Borrow History: \n");
    while(fscanf(file, "%s %s %s %s", r.Book_Title, r.Student_ID, r.Borrow_Date, r.Return_Date) != EOF)
    {
        if(strcmp(r.Student_ID, Student_ID) == 0)
        {
            printf("-->> Book: %s, From %s to %s\n", r.Book_Title, r.Borrow_Date, r.Return_Date);
        }
    }
    fclose(file);
}
void View_Books()
{
    FILE *file = fopen("Books_Information.txt", "r");
    book B;
    if (file == NULL)
    {
        printf("Error for opening the book list.\n");
        return;
    }
    printf("\n  === List of Books ===\n");
    while(fscanf(file, "%s %s %s %s %s %s %d\n", B.Subject, B.Title, B.Author, B.Condition, B.Availability, B.Book_Owner_ID, &B.Semester) != EOF)
    {
        printf("\n -> Title: %s, Availibility: %s\n", B.Title, B.Availability);
    }
    fclose(file);
}

void Brain_Teaser()
{
    int ans, score = 0;
    printf("\t \t***Ready to tickle your brain with some riddles?*** \n");

     printf("1>  What has to be broken before you can use it? \n1)A promise 2)An egg 3)A pencil 4)A code \n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 2) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");

     printf("2> What gets wetter the more it dries? \n1)Water 2)Sponge 3)Towel 4)Soap\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 3) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("3> What has a head, a tail, but no body? \n1)Snake 2)Coin 3)Nail 4)Lizard\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 2) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");



     printf("4> I have keys but no locks. I have space but no room. You can enter, but you cant go outside. What am I? \n1)A map 2)A keyboard 3)A house 4)A code\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 2) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");

     printf("5>  I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I? \n1)An echo 2)A ghost 3)A shadow 4)A breeze\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 1) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("6> What comes once in a minute, twice in a moment, but never in a thousand years? \n1)Time 2)Thought 3)M 4)Silence\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 3) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("7> Im light as a feather, yet the strongest person cant hold me for long. What am I? \n1)Air 2)Breath 3)Cloud 4)Wind\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 2) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("8> Forward I am heavy, but backward I am not. What am I? \n1)Rock 2)Truck 3)Ton 4)None\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 3) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("9>  If you drop me, Im sure to crack, but give me a smile and Ill always smile back. What am I? \n1)Mirror 2)Glass 3)Friend 4)Egg\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 1) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("10> Im not alive, but I grow. I dont have lungs, but I need air. What am I? \n1)Plant 2)Cloud 3)Balloon 4)Fire\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 4) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("11> What can be cracked, made, told, and played? \n1)Joke 2)Game 3)Story 4)Code\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 1) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("12> What has one horn and gives milk? \n1)Cow 2)Unicorn 3)Milk truck 4)Rhino\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 3) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


     printf("13> What begins with T, ends with T, and has T in it? \n1)Test 2)Tent 3)Toast 4)Teapot\n"); scanf("%d", &ans);
    if(ans < 1 || ans > 4) printf("Invalid choice!\n");
    else if(ans == 4) { score++; printf("*CORRECT!*\n"); }
    else printf("Wrong Answer!\n");


    printf("\n  ==>> HAHA! Well Played. Your Score: %d out of 13.", score);
}

void Show_Reminders(char Student_ID[25])
{
    borrow r;
    FILE *file = fopen("Borrow_Information.txt", "r");
    printf("\n <+>Reminder for overdue books (Manually checking system): \n");
    while(fscanf(file, "%s %s %s %s", r.Book_Title, r.Student_ID, r.Borrow_Date, r.Return_Date) != EOF)
    {
        if(strcmp(r.Student_ID, Student_ID) == 0)
        {
            printf("%s is due by %s.\n", r.Book_Title, r.Return_Date);
        }
    }
    fclose(file);
}

void Study_Tips()
{
    printf("\n ## ** Want Some Study Tips & Motivation... :>)  \n");
    printf("**Listen Bro/Sis 'Success is the sum of small efforts repeated day in and day out.'**\n");
    printf("--> Some tips:\n \t #Set clear goals and focus on one topic at a time.\n \t #Take short breaks every 25-30 minutes to stay fresh and focused.\n \t #Use active recall: test yourself instead of just rereading.");
    printf("\n \t #Avoid distractions: put your phone on silent or in another room.\n \t #Teach what you learn to someone else for better understanding.\n \t #Stay positive and believe in your ability to improve.");
    printf("\n \t #Prioritize your toughest subjects when your mind is fresh.\n \t #Get enough sleep - it helps memory and concentration.");
}

void Add_Review(char Student_ID[25])
{
    review R;
    printf("Enter Book title: ");
    getchar();
    scanf("%[^\n]", R.Book_Title);
    strcpy(R.Student_ID, Student_ID);
    printf("##Write down your review freely and shortly: ");
    getchar();
    scanf("%[^\n]", R.Review);
    FILE *file = fopen("Books_Review.txt", "a");
    fprintf(file, "%s %s %s\n", R.Book_Title, R.Student_ID, R.Review);
    fclose(file);
    printf("\t **Review added successfully.**");
}
void View_Reviews()
{
    review R;
    FILE *file = fopen("Books_Review.txt", "r");
    if (file == NULL) {
        printf("Error opening the reviews file.\n");
        return;
    }
    printf("---- Book Reviews: ----");
    while(fscanf(file, "%s %s %[^\n]", R.Book_Title, R.Student_ID, R.Review) != EOF)
    {
        printf("\n -->> %s was reviewed by %s: %s", R.Book_Title, R.Student_ID, R.Review);
    }
    fclose(file);
}

int main()
{
    printf(
        "      ____________________________\n"
        "     /                           /|\n"
        "    /       <<  EDULINK... >>   / |\n"
        "   /___________________________/  |\n"
        "   |                           |  |\n"
        "   |                           |  |\n"
        "   |                           |  |\n"
        "   |   Chapter 1:              |  |\n"
        "   |   Chapter 2:              |  |\n"
        "   |   Chapter 3:              |  |\n"
        "   |                           |  |\n"
        "   |___________________________| /\n"
        "   |___________________________|/\n"
    );
    while (1)
    {
    char Student_ID[25];
    int c;
    printf("---------- An Unique BOOK Sharing System ----------\n");
    printf(" 1) Register.\n 2) Login.\n 3) Exit.\n");
    printf("\n  -->> Select an option: ");
    scanf("%d", &c);
    getchar();

    switch (c)
    {
    case 1:
        Reg_Student();
        break;
    case 2:
        printf("Enter your student id: ");
        scanf(" %[^\n]", Student_ID);
        Log_In(Student_ID);
        break;
    case 3:
        printf("Successfully Exited. \n");
        return 0;
    default:
        printf("ERROR 404! Please choose correctly.\n");
    }
    return 0;
    }
}
