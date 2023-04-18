#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct todo
{
    char body[2000];
    char title[100];
    char time[50];
};

//FUNCTION PROTOTYPES
//All functions are defined after the main function
    void clear_input_stream(void);
    void clear_screen(void);
    void display_todo(struct todo *todo_details);
    void add_todo(void);
    void display_all_todo(void);
    void search_todo();
    void action_control(char *ch, char *str);
    char *strupper(char *s);
    void update_todo(void);

int main(void)
{
    int t_opt;
    char name[20];
    char a_opt;

    printf("WELCOME, PLEASE ENTER YOUR NAME:   ");
    fgets(name, 21, stdin);
    name[strlen(name) - 1] = '\0'; //fgets function always adds '\n' character to inputs, this function gets rid of the character.

    clear_screen(); //clears the screen, it is defined below main function
    while(1)
    {
        printf("===%s's TODO LIST===\n\n", strupper(name)); //The strupper() function coverts string to UPPERCASE, it is defined below the main function

        t_opt = 0;
        while (t_opt != 1 && t_opt != 2 && t_opt != 3 && t_opt != 4 && t_opt != 5 && t_opt != 6) //Checking if user had selected the wromg option
        {
            printf("PRESS...\n\n");
            printf("1. To add todo\n");
            printf("2. To display all todo\n");
            printf("3. To search todo\n");
            printf("4. To update todo\n");
            printf("5. To delete todo\n");
            printf("6. To quit\n");
            printf("\nYOUR CHOICE: \t");
            scanf("%d", &t_opt);
            clear_input_stream();//cleans the input stream after user's inputs, it is defined below main function
            clear_screen();

            if (t_opt != 1 && t_opt != 2 && t_opt != 3 && t_opt != 4 && t_opt != 5 && t_opt != 6)
            {
                printf("PLEASE SELECT THE RIGHT OPTION!\n\n");
            } else
            {
                break;
            }
        }
        switch(t_opt)
        {
            //Adding Todo
            case 1:
                a_opt = 'y';
                while (a_opt == 'y' || a_opt == 'Y')
                {
                    clear_screen();
                    add_todo(); //Main function that adds the Todo, it's defined below

                    //The 'action_control' function is defined below main function
                    //It asks user if they want to add another todo and ensure they enter the right option
                    //I passed in the address of "a_opt" into the function bcoz you can only modify a variable declared outside a function through its address except if it's a global variable
                    action_control(&a_opt, "Do you wish to add another TODO?");
                }
                break;

            //Disaplaying all todos saved in file
            case 2:
                clear_screen();
                display_all_todo(); //Function that displays all Todo
                printf("\nPress ENTER key to return to the main menu\t");
                getchar();
                //clear_input_stream();
            break;

            //Searching for todo
            case 3:
                a_opt = 'y';
                while (a_opt == 'y' || a_opt == 'Y')
                {
                    clear_screen();
                    search_todo(); //Function that searches Todo, it's defined below

                    action_control(&a_opt, "Do you wish to perform another SEARCH?");
                }
            break;

            case 4:
                clear_screen();
                update_todo(); //Function that updates todo
            break;

            case 5:
                clear_screen();
                printf("\n\n\t\t\tdelete todo\n\n\n\n", name);
            break;

            case 6:
                clear_screen();
                printf("\n\n\t\t\tGOODBYE FOR NOW %s, SEE YOU AGAIN\n\n\n\n", name);
                exit(0);
            break;
        }
        clear_screen();
    }

    return (0);
}


//BELOW ARE THE DEFINITIONS OF ALL THE FUNCTIONS USED IN THE CODE, PLEASE CALMLY GO THROUGH THEM

//function that cleans the input stream after user's inputs
void clear_input_stream(void)
{
    //This is a standard library function that clears the input stream
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//function that clears the screen
void clear_screen(void)
{
    system("cls");
}

//FGunction that convert string to uppercase
char *strupper(char *s)
{
    if (s == 0)
        return 0;
    for (int i = 0; s[i] != 0; i++)
    {
        s[i] = toupper(s[i]); //toupper is string.h library function that converts a character to uppercase
    }
    return s;
}


//This function is not important, I only used it to avoid code repetition and to make our code neater
//It asks user if they want to perform another operation and ensure they input the correct option
//The first arguement(*ch) is the pointer to user's option
//The second arguement(*str) is a pointer to a string wich is the message to display to the user
void action_control(char *ch, char *str)
{
    printf("\n%s?(y/n):\t", str);
    *ch = getchar();
    clear_input_stream();

    while (*ch != 'y' && *ch !='Y' && *ch != 'n' && *ch != 'N')
    {
        clear_screen();
        printf("PLEASE ENTER THE CORRECT OPTION!\n\n");
        printf("%s(y/n):\t", str);
        *ch = getchar();
        clear_input_stream();
    }
}

//function that adds todo
void add_todo(void)
{
    //Time functions from the time.h library
    time_t now;
    time(&now);
    //------------------------

    struct todo todo_details;

    //Getting todo message from the user
    printf("ENTER YOUR TODO DETAILS:\t\t");
    fgets(todo_details.body, sizeof(todo_details.body), stdin);
    todo_details.body[strlen(todo_details.body) - 1] = '\0'; //fgets always adds '\n' character to inputs, this function gets read of the character

    //Getting todo title from the user
    printf("ENTER YOUR TODO TITLE(e.g FOOTBALL):\t");
    fgets(todo_details.title, sizeof(todo_details.title), stdin);
    todo_details.title[strlen(todo_details.title) - 1] = '\0'; //fgets always adds '\n' character to inputs, this function gets read of the character

    //Adding the current time
    strcpy(todo_details.time, ctime(&now));

    //Saving it in a file
    FILE *fp = fopen("MyTodo.dat", "a+");
    if (fp == NULL)
    {
        printf("FAIL TO SAVE TODO, PLEASE TRY AGAIN\n\n");
    } else
    {
        fwrite(&todo_details, sizeof(struct todo), 1, fp);
        clear_screen();
        printf("\t\tTODO ADDED SUCCESSFULLY\n\n");

        //Function that displays todo after creating and saving it
        //Takes in the address of the struct into which the todo details were saved
        display_todo(&todo_details);
    }
    fclose(fp);
}

//Function that displays todo from the todo struct
void display_todo(struct todo *todo_details)
{
    printf("==============================================================================\n\n");
    printf("TODO TITLE:\t%s\n\n", strupper(todo_details->title));
    printf("TODO DETAILS:\t%s\n\n", todo_details->body);
    printf("TODO TIME:\t%s\n\n", todo_details->time);
    printf("==============================================================================\n\n");
}

//Function that displays all the todo saved in the file
void display_all_todo(void)
{
    int found;
    struct todo todo_disp;
    FILE *fp = fopen("MyTodo.dat", "r");
    if (fp == NULL)
    {
        printf("YOUR TODO LIST IS EMPTY OR THE SAVE FILE HAS BEEN DELETED, TRY CREATING NEW TODOS\n\n");
    } else
    {
        found = 0;
        while (fread(&todo_disp, sizeof(struct todo), 1, fp) != 0)
        {
            display_todo(&todo_disp);
            found++;
        }

        if (found == 0)
        {
            printf("YOUR TODO LIST IS EMPTY\n");
        }
        else
        {
            printf("TOTAL SAVED TODOS ON FILE:  (%d)\n\n", found);
            printf("USE THE SCREEN SCROLL BAR TO SCROLL THROUGH YOUR TODOS\n\n");
        }
    }
    fclose(fp);
}

//funtion that searches for todo
void search_todo()
{
    FILE *fp;
    char str[50];
    int found;
    struct todo stodo;

    printf("Please enter any word from the title of the todo you want to search:\t");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0'; //fgets always adds '\n' character to inputs, this function gets read of the character
    fp = fopen("MyTodo.dat", "r");

    if (fp == NULL)
    {
        printf("\nFAILED TO OPEN FILE, PLEASE TRY AGAIN\n\n");
    } else
    {
            //This checks if the user input matches with any todo title from the saved file we're looping through
            //The strstr function is from string.h library, it searches for a sub-string in a string and returns 0 if not found
            //The strupper function converts string to uppercase, it is defined below the main function
        found = 0; //This keeps track of the number of matched todo from the search
        clear_screen();
        while (fread(&stodo, sizeof(struct todo), 1, fp) != 0)
        {
            if (strstr(strupper(stodo.title), strupper(str)) != 0)
            {
                display_todo(&stodo); //Recall this function that prints or displays todo from struct?
                found++;
            }
        }
        if (found == 0)
        {
            printf("\nNO MATCH FOUND, PLEASE ENSURE THAT YOUR INPUT IS CORRECT AND TODO IS SAVED ON FILE\n\n");
        } else
        {
            printf("%d MATCH FOUND\n", found);
            printf("\nUSE THE SCREEN SCROLL BAR TO SCROLL THROUGH THE SEARCH RESULT IF NEEDED\n\n");
        }
    }
}

//Function that updates todo
void update_todo(void)
{

    FILE *fp;
    FILE *fp2;
    char title[100];
    char opt;
    int found;
    struct todo update_t;

    printf("ENTER THE COMPLETE AND CORRECT TITLE OF THE TODO YOU WISH TO UPDATE:\t");
    fgets(title, sizeof(title), stdin);
    title[strlen(title) - 1] = '\0'; //fgets function always adds '\n' character to inputs, this function gets rid of the character.
    fp = fopen("MyTodo.dat", "r");
    if (fp == NULL)
    {
        printf("\nTODO LIST IS EMPTY OR SAVE FILE HAS BEEN DELETED\n");
    } else
    {
        fp2 = fopen("tempfile.dat", "a");
        found = 0;

        //Here we loop through all the TODOS in the saved file and copy each TODO to a new file except the todo we want to change change
        while (fread(&update_t, sizeof(struct todo), 1, fp) != 0)
        {
            clear_screen();

            //This checks the file for the title the user entered to see if it matches with any of the TODO TITLE in the file
            //If there's a match, user would be prompted for new inputs and these would be saved in the new file in place of the matched todo
            //The strcmp() comapares two strings together and returns 0 only if they are the same
            //The strupper converts strings to uppercase
            if (strcmp(strupper(update_t.title), strupper(title)) == 0)
            {
                display_todo(&update_t);//display the todo for confirmation
                action_control(&opt, "Is that the TODO you wish to edit?");
                if (opt == 'y' || opt == 'Y')
                {
                    clear_screen();
                    printf("\nENTER YOUR NEW TODO DETAILS:\t\t");
                    fgets(update_t.body, sizeof(update_t.body), stdin);
                    update_t.body[strlen(update_t.body) - 1] = '\0';
                    printf("ENTER A NEW TITLE OR THE OLD ONE:\t");
                    fgets(update_t.title, sizeof(update_t.title), stdin);
                    update_t.title[strlen(update_t.title) - 1] = '\0';
                    found = 1; //Confirms that a todo was edited

                    fwrite(&update_t, sizeof(struct todo), 1, fp2); //saving the new iput to the new file
                } else
                {
                    fwrite(&update_t, sizeof(struct todo), 1, fp2);
                }

            } else
            {
                fwrite(&update_t, sizeof(struct todo), 1, fp2);
            }
        }
        fclose(fp);
        fclose(fp2);

        clear_screen();
        //After the search, if there is a match, that means we'd surely edit a todo, so the old file is deleted and the new file is renamed to the old file
        //If we do not rename the newfile to the old file, we won't be able to access the file content later on in our program
        if (found == 1)//That means we succefully edited a TODO
        {
            remove("MyTodo.dat");
            rename("tempfile.dat", "MyTodo.dat");
            printf("TODO EDITED SUCCESSFULLY\n");

        }else
        {
            //The tempfile is removed bcoz it's not different from the old file since we edited no todo
            remove("tempfile.dat");
            printf("No match found for the title you entered!\n");
        }
    }
    printf("\n\nPRESS ENTER KEY TO RETURN TO THE MAIN MENU");
    getchar();
}
