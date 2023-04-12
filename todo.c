#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct todo
{
    char title[40];
    char body[2000];
    char time[20];
};

//FUNCTION PROTOTYPES
//All functions are defined after the main function
    void clear_input_stream(void);
    void clear_screen(void);
    void display_todo(struct todo *todo_details);
    void add_todo(void);
    void display_all_todo(void);

int main(void)
{
    int t_opt;
    char name[20];
    char a_opt;

    printf("WELCOME, PLEASE ENTER YOUR NAME:   ");
    fgets(name, 21, stdin);
    name[strlen(name) - 1] = '\0'; //fgets function always adds '\n' character to inputs, this function gets rid of the character.

    clear_screen();
    while(1)
    {
        t_opt = 0;
        printf("===%s's TODO LIST===\n\n", strupr(name)); //The strupr() function coverts string to UPPER CASE
        start: //This is an implementation of the GOTO function in C, it's more like a loop if certain condition is not met
        printf("PRESS...\n\n");
        printf("1. To add todo\n");
        printf("2. To display all todo\n");
        printf("3. To search todo\n");
        printf("4. To quit\n");
        printf("\nYOUR CHOICE: \t");
        scanf("%d", &t_opt);
        clear_input_stream();

        if (t_opt != 1 && t_opt != 2 && t_opt != 3 && t_opt != 4) //Checking if user had selected the wromg option
        {
            clear_screen();
            printf("PLEASE SELECT THE RIGHT OPTION!\n\n");
            goto start; //The trigger of the GOTO function talked about earlier
        } else
        {
                switch(t_opt)
            {
                //Adding Todo
                case 1:
                    a_opt = 'y';
                    while (a_opt == 'y' || a_opt == 'Y')
                    {
                        clear_screen();
                        add_todo(); //Main function that adds the Todo, it's defined below

                        //After successfully adding a Todo
                        printf("Do you wish to add another TODO?(y/n):\t");
                        a_opt = getchar();
                        clear_input_stream();

                        //Checking if user had selected the wromg option
                        while (a_opt != 'y' && a_opt !='Y' && a_opt != 'n' && a_opt != 'N')
                        {
                            clear_screen();
                            printf("PLEASE ENTER THE CORRECT OPTION!\n\n");
                            printf("Do you wish to add another TODO?(y/n):\t");
                            a_opt = getchar();
                            clear_input_stream();
                        }

                        if (a_opt == 'n' || a_opt == 'N')
                        {
                            break;
                        }
                    }
                    break;

                //Disaplaying all todos saved in file
                case 2:
                    clear_screen();
                    display_all_todo(); //Function tha displays all Todo
                    printf("\nUSE THE SCREEN SCROLL BAR TO SCROLL THROUGH YOUR TODO LISTS\n");
                    printf("\nPress any key to return to the main menu\t");
                    getchar();
                    clear_input_stream();
                break;

                //Searching for todo
                case 3:
                    clear_screen();
                    printf("Delete todo\n");
                break;

                //Exiting the app
                case 4:
                    clear_screen();
                    printf("\n\n\t\t\tGOODBYE FOR NOW %s, SEE YOU AGAIN\n\n\n\n", name);
                    exit(0);
                break;
            }
        }
        clear_screen();
    }

    return (0);
}

//function that cleans the input stream after user's inputs
void clear_input_stream(void)
{
    while((getchar()) != '\n');
}

//function that clears the screen
void clear_screen(void)
{
    system("cls");
}

//function that adds todo
void add_todo(void)
{
    //Time functions from the time.h library
    time_t now;
    time(&now);
    //------------------------

    struct todo todo_details;

    //Getting todo title from the user
    printf("Enter your todo title:\t\t");
    fgets(todo_details.title, sizeof(todo_details.title), stdin);
    todo_details.title[strlen(todo_details.title) - 1] = '\0'; //fgets always adds '\n' character to inputs, this function gets read of the character

    //Getting todo message from the user
    printf("Enter your todo messsage:\t");
    fgets(todo_details.body, sizeof(todo_details.body), stdin);
    todo_details.body[strlen(todo_details.body) - 1] = '\0'; //fgets always adds '\n' character to inputs, this function gets read of the character

    //Adding the current time
    strcpy(todo_details.time, ctime(&now));

    //Saving it in a file
    FILE *fp = fopen("MyTodo.dat", "a+");
    fwrite(&todo_details, sizeof(struct todo), 1, fp);
    fclose(fp);
    clear_screen();
    printf("\t\tTODO ADDED SUCCESSFULLY\n\n");

    //Function that displays todo after creating and saving it
    //Takes in the address of the struct into which the todo details were saved
    display_todo(&todo_details);
}

//Function that displays todo from the todo struct
void display_todo(struct todo *todo_details)
{
    printf("==============================================================================\n\n");
    printf("TODO TITLE:\t%s\n\n", strupr(todo_details->title));
    printf("TODO DETAILS:\t%s\n\n", todo_details->body);
    printf("TODO TIME:\t%s\n\n", todo_details->time);
    printf("==============================================================================\n\n");
}

//Function that displays all the todo saved in the file
void display_all_todo(void)
{
    struct todo todo_disp;
    FILE *fp = fopen("MyTodo.dat", "r");
    if (fp == NULL)
    {
        printf("YOUR TODO LIST IS EMPTY OR THE SAVE FILE HAS BEEN DELETED, TRY CREATING NEW TODOS\n\n");
    } else
    {
        while (fread(&todo_disp, sizeof(struct todo), 1, fp))
        {
            display_todo(&todo_disp);
        }
    }
    fclose(fp);
}
