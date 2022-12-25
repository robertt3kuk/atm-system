#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
  int month, day, year;
};

// all fields for each record of an account
struct Record {
  int id;
  int userId;
  char name[100];
  char country[100];
  char phone[40];
  char accountType[10];
  int accountNbr;
  double amount;
  struct Date deposit;
  struct Date withdraw;
};

struct User {
  int id;
  char name[50];
  char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);
int saveUser(struct User u);
int checkForUsername(struct User u);
int getUid(struct User u);
int chooseUserTo(struct User u, struct User *ans);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
int chooseYourAccount(struct User u);
void updateAcc(struct User u);
void checkThisAccs(struct User u);
void deleteLine(int line);
void deleteAccount(struct User u);
void showAccount(int line);
void checkOneAccount(struct User u);
void saveNewOwner(struct User u, struct User t, int line);
void transferYourAccountTo(struct User u);
