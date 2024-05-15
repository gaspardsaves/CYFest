#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define ID 100000
#define USERMAX 2

typedef struct {
    int* id;
    char* password;
} User;


int better_scan(char * message){
    int ret_var = 0;
    int value = 1;
  while (ret_var != 1 || value < 0)
    {   
        printf("%s", message);
        ret_var = scanf("%d", &value);
        while(getchar()!='\n'){} // Ligne facultative de sécurisation
    }
    return value;

}







User* user_table(int* userCount) {
    User* tab = malloc(sizeof(User) * USERMAX);
    if (tab == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    *userCount = 0;  // Initialize user count
    return tab;
}

void generate_unique_id(User* tab, int userCount, int* current_id) {
    bool unique;
    do {
        unique = true; // Admit that id is true
        *current_id = rand() % ID;  // Generate an ID
        for (int i = 0; i < userCount; i++) {// check if id is already taken  
            if (*tab[i].id == *current_id) {
                unique = false; 
                break;// stop loop and re-check
            }
        }
    } while (!unique); // do while check id is already used
}




void user_creator(User* tab, int* userCount) {
    if (*userCount >= USERMAX) {
        printf("User limit reached\n");
        return;
    }

    User newUser;
    char buffer[100];
    printf("Enter your password: ");
    fgets(buffer, sizeof(buffer), stdin);// Get password
    buffer[strcspn(buffer, "\n")] = '\0';

    newUser.password = malloc(strlen(buffer) + 1);// tab password creator
    if (newUser.password == NULL) {
        fprintf(stderr, "Memory allocation failed for password\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newUser.password, buffer);

    newUser.id = malloc(sizeof(int));
    if (newUser.id == NULL) {
        fprintf(stderr, "Memory allocation failed for ID\n");
        exit(EXIT_FAILURE);
    }
    generate_unique_id(tab, *userCount, newUser.id);// Checking if ID already used and create another one

    tab[*userCount] = newUser;
    printf("Respectively, your ID and your password are: %d %s\n", *newUser.id, newUser.password);
    (*userCount)++;
}

bool user_login(User* tab, int userCount) {
    int Id;
    char Password[100];

    Id=better_scan("Enter your Id: ");
    printf("Enter your password: ");
    fgets(Password, sizeof(Password), stdin);
    Password[strcspn(Password, "\n")] = '\0';  // Remove newline character

    for (int i = 0; i < userCount; i++) {
        if (*tab[i].id == Id && strcmp(tab[i].password, Password) == 0) {
            printf("Login successful!\n");
            return true; // correct ID and password
            }
        }

    printf("Invalid ID or password.\n");
    return false;
}

void account_check(User* tab, int* userCount) {
    int answer;
    do{
        answer=better_scan("Do you have an account: yes-1 or no-0: ");
        }
            while((answer!=1)&&(answer!=0));
    switch (answer) {
        case 1: 
            if (!user_login(tab, *userCount)) {
                printf("Authentication failed.\n");
            }// usercount: max user
            break;
        case 0:
            user_creator(tab, userCount);//Usercount: pointer in main function
            break;
        default:
            break;
    }
}

void display_users(User* tab, int userCount) {
    printf("List of all users:\n");
    for (int i = 0; i < userCount; i++) {
        printf("User %d:\n", i + 1);
        printf("  ID: %d\n", *tab[i].id);
        printf("  Password: %s\n", tab[i].password);
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    int userCount = 0;  // Initialize userCount
    User* users = user_table(&userCount);

    for(int i=0; i<USERMAX; i++){
    account_check(users, &userCount);
    }

    display_users(users, userCount);

    // Clean memory
    for (int i = 0; i < userCount; i++) {
        free(users[i].id);
        free(users[i].password);
    }
    free(users);
    return 0;
}


// Quand on met plusieurs charactère dans la console ça me mets plusieurs fois la question de 1 ou 0

// pour le 1 ou 0 fauta créer une chaine de charactère et la transformer en chiffre pour pas avoir cette répétition

