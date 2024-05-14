#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>



#define ID 100000
#define FESTIVALIER 5
#define P 8
#define USERMAX 5

typedef struct{
int admin; //0
int* id; 
char* password;
int resa; // double tableau qui contient les concerts et les sièges associés à ces derniers;
int porte_feuille;
} User;



// Table user creator
User* user_table( int* Usercount){
User* tab=NULL;

  tab=malloc(sizeof(User)*USERMAX);
  if (tab == NULL){
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  if(*Usercount>=USERMAX){
    printf("User limit reached ");
  }
  return tab;
}


void generate_unique_id(User* tab, int Usercount, int* current_id) {
bool check_id;
do {
   check_id = true; // Admit that id is true

    for (int i = 0; i < Usercount; i++) {
        if (*tab[i].id == *current_id) { // check if id is already taken 
          check_id = false;
          *current_id = rand() % ID; // generate new id
            break; // à vérif stop loop and re-check
}
}
} 
while (!check_id); // do while check id is already used
}






// User creator
void user_creator(User* tab, int* usercount){

User Newuser;
char buffer[100];



if(*usercount>USERMAX){
printf("user limit reached");
exit(EXIT_FAILURE);
  
}


  
printf("enter your password");
fgets(buffer, 100, stdin);// Get password
  
Newuser.password=malloc(strlen(buffer));// tab password creator
  
  if (Newuser.password == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
  }
  
strcpy(Newuser.password, buffer);  

  Newuser.id = malloc(sizeof(int));   
  
  if (Newuser.id == NULL) {
      fprintf(stderr, "Memory allocation failed for ID\n");
      exit(1);
  }
  
  *Newuser.id = rand() % ID; 
  
  tab[*usercount] = Newuser;

generate_unique_id(tab, *usercount, Newuser.id);// Cheking if ID already used and create another one

printf("Respectively, your id and your password are: %d %s\n", *Newuser.id, Newuser.password);
printf("Le tableau newuser: %d %s\n", *tab[*usercount].id, tab[*usercount].password);// voir si c'est bien correct
  
  (*usercount)++;
}


bool user_login(User* tab) {
int Id;
  
char Password[100];

printf("Enter your ID: ");
scanf("%d", &Id);  
printf("Enter your password: ");
scanf("%s", Password);  

  
for (int i = 0; i < USERMAX; i++) { // search for user
  if (*tab[i].id == Id && strcmp(tab[i].password, Password) == 0) {
    printf("Login successful!\n");
    return true;  // correct ID and password
}
}
printf("Invalid ID or password.\n");
return false;  // no macth
}



void account_check(User* tab, int* Usercount){
int answer;
printf("Do you have an account: yes-1 or no-0\n");
scanf("%d", &answer);
switch (answer){
    case 1: user_login(tab);// usercount: max user
  break; 

  case 0:user_creator(tab, Usercount); //Usercount: pointer in main function
    break;

   default: 
     break;
  }
}



void display_users(User* tab) {
printf("List of all users:\n");
  for (int i = 0; i < USERMAX; i++) {
    printf("User %d:\n", i + 1);
    printf("  ID: %d\n", *tab[i].id);
    printf("  Password: %s\n", tab[i].password);
    printf("\n");  
    }
}



int main(){

int* Usercount=0; 
User* users=user_table( Usercount);

account_check(users, Usercount);

bool loginSuccess = user_login(users);
if (loginSuccess) {
  printf("User authenticated successfully.\n"); // Find out if the execution was successful
} 
else {
  printf("Authentication failed.\n");
}

display_users(users);// vérifier si tableau et programme bien foutu
  

 // Clean memory
for (int i = 0; i < *Usercount; i++) {
  free(users[i].id);
  free(users[i].password);
}
  return 0;
}
