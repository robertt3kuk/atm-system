#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r) {
  return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s", &r->id, &r->userId,
                name, &r->accountNbr, &r->deposit.month, &r->deposit.day,
                &r->deposit.year, r->country, r->phone, &r->amount,
                r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r) {
  fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n", r.id, u.id, u.name,
          r.accountNbr, r.deposit.month, r.deposit.day, r.deposit.year,
          r.country, r.phone, r.amount, r.accountType);
}
int getLastNumberFromFile() {
  FILE *fp;
  struct Record r;

  if ((fp = fopen("./data/records.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  int ret = 0;
  while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s", &ret, &r.userId,
                r.name, &r.accountNbr, &r.deposit.month, &r.deposit.day,
                &r.deposit.year, r.country, r.phone, &r.amount,
                r.accountType) != EOF) {
  }

  fclose(fp);
  return ret + 1;
}
int getLineByAccNbr(struct User u, int nbr) {
  FILE *fp;
  struct Record r;

  if ((fp = fopen("./data/records.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s", &r.id, &r.userId,
                r.name, &r.accountNbr, &r.deposit.month, &r.deposit.day,
                &r.deposit.year, r.country, r.phone, &r.amount,
                r.accountType) != EOF) {
    if (r.accountNbr == nbr && r.userId == u.id) {
      return r.id;
    }
  }
  fclose(fp);
  return -1;
}

void stayOrReturn(int notGood, void f(struct User u), struct User u) {
  int option;
  if (notGood == 0) {
    system("clear");
    printf("\n✖ Record not found!!\n");
  invalid:
    printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
    scanf("%d", &option);
    if (option == 0)
      f(u);
    else if (option == 1)
      mainMenu(u);
    else if (option == 2)
      exit(0);
    else {
      printf("Insert a valid operation!\n");
      goto invalid;
    }
  } else {
    printf("\nEnter 1 to go to the main menu and 0 to exit:");
    scanf("%d", &option);
  }
  if (option == 1) {
    system("clear");
    mainMenu(u);
  } else {
    system("clear");
    exit(1);
  }
}

void success(struct User u) {
  int option;
  printf("\n✔ Success!\n\n");
invalid:
  printf("Enter 1 to go to the main menu and 0 to exit!\n");
  scanf("%d", &option);
  system("clear");
  if (option == 1) {
    mainMenu(u);
  } else if (option == 0) {
    exit(1);
  } else {
    printf("Insert a valid operation!\n");
    goto invalid;
  }
}
void transferYourAccountTo(struct User u) {
  checkThisAccs(u);
  int linebr = chooseYourAccount(u);
  struct User ans;
  int accountId = chooseUserTo(u, &ans);
  ans.id = accountId;
  saveNewOwner(u, ans, linebr);
  success(u);
}
void checkOneAccount(struct User u) {
  checkThisAccs(u);
  int linenbr = chooseYourAccount(u);
  showAccount(linenbr);
  success(u);
}
void showAccount(int line) {
  FILE *fp;
  struct Record r;

  if ((fp = fopen("./data/records.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %s %lf %s", &r.id, &r.userId,
                r.name, &r.accountNbr, &r.deposit.month, &r.deposit.day,
                &r.deposit.year, r.country, r.phone, &r.amount,
                r.accountType) != EOF) {
    if (r.id == line) {
      break;
    }
  }
  system("clear");
  printf("\n\n\nYour account number - > %d \n\n", r.accountNbr);
  printf("Your account date of creation %d month %d day %d year\n",
         r.deposit.month, r.deposit.day, r.deposit.year);
  printf("Your country -> %s\n", r.country);
  printf("Your phone number -> %s\n", r.phone);
  printf("Your amount ->%f \n", r.amount);
  printf("Your account type is ");
  if (strcmp(r.accountType, "saving") == 0) {
    printf("savings: interest rate 0.07 percent\n");
  } else if (strcmp(r.accountType, "fixed01") == 0) {
    printf("fixed01(1 year account): interest rate 0.04 percent\n");
  } else if (strcmp(r.accountType, "fixed02") == 0) {
    printf("fixed02(2 year account): interest rate 0.05 percent\n");
  } else if (strcmp(r.accountType, "fixed03") == 0) {
    printf("fixed03(3 year account): interest rate 0.08 percent\n");
  } else {
    printf("is current: You will not get interests because the account is of "
           "type current\n");
  }

  fclose(fp);
}

#define BUFFER_SIZE 1000
void deleteAccount(struct User u) {
  checkThisAccs(u);
  int linenbr = chooseYourAccount(u);
  printf("%d", linenbr);
  deleteLine(linenbr);
  success(u);
}
void deleteLine(int line) {
  FILE *fPtr;
  FILE *fTemp;

  int count;

  /*  Open all required files */
  fPtr = fopen(RECORDS, "r");
  fTemp = fopen("replace.tmp", "w");

  /* fopen() return NULL if unable to open file in given mode. */
  if (fPtr == NULL || fTemp == NULL) {
    /* Unable to open file hence exit */
    printf("\nUnable to open file.\n");
    printf("Please check whether file exists and you have read/write "
           "privilege.\n");
    exit(EXIT_SUCCESS);
  }

  /*
   * Read line from source file and write to destination
   * file after replacing given line.
   */

  struct Record r;
  count = 0;
  while ((fscanf(fPtr, "%d %d %s %d %d/%d/%d %s %s %lf %s", &r.id, &r.userId,
                 r.name, &r.accountNbr, &r.deposit.month, &r.deposit.day,
                 &r.deposit.year, r.country, r.phone, &r.amount,
                 r.accountType) != EOF)) {
    count++;

    /* If current line is line to replace */
    if (count == line + 1) {
    } else {
      fprintf(fTemp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n", count, r.userId,
              r.name, r.accountNbr, r.deposit.month, r.deposit.day,
              r.deposit.year, r.country, r.phone, r.amount, r.accountType);
    }
  }

  /* Close all files to release resource */
  fclose(fPtr);
  fclose(fTemp);

  /* Delete original source file */
  remove(RECORDS);

  /* Rename temporary file as original file */
  rename("replace.tmp", RECORDS);
}
void saveNewOwner(struct User u, struct User t, int line) {
  /* File pointer to hold reference of input file */
  FILE *fPtr;
  FILE *fTemp;
  struct Record r;

  char buffer[BUFFER_SIZE];
  char newline[BUFFER_SIZE];
  int count;

  printf("Replace '%d' line with: ", line);
  fgets(newline, BUFFER_SIZE, stdin);

  /*  Open all required files */
  fPtr = fopen(RECORDS, "r");
  fTemp = fopen("replace.tmp", "w");

  /* fopen() return NULL if unable to open file in given mode. */
  if (fPtr == NULL || fTemp == NULL) {
    /* Unable to open file hence exit */
    printf("\nUnable to open file.\n");
    printf("Please check whether file exists and you have read/write "
           "privilege.\n");
    exit(EXIT_SUCCESS);
  }

  /*
   * Read line from source file and write to destination
   * file after replacing given line.
   */
  struct User decoy;
  count = 0;
  while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {
    count++;

    /* If current line is line to replace */
    if (count == line + 1) {
      fscanf(fPtr, "%d %d %s %d %d/%d/%d %s %s %lf %s\n", &r.id, &decoy.id,
             decoy.name, &r.accountNbr, &r.deposit.month, &r.deposit.day,
             &r.deposit.year, r.country, r.phone, &r.amount, r.accountType);
      fprintf(fTemp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n", r.id, t.id,
              t.name, r.accountNbr, r.deposit.month, r.deposit.day,
              r.deposit.year, r.country, r.phone, r.amount, r.accountType);
    } else {

      fputs(buffer, fTemp);
    }
  }

  /* Close all files to release resource */
  fclose(fPtr);
  fclose(fTemp);

  /* Delete original source file */
  remove(RECORDS);

  /* Rename temporary file as original file */
  rename("replace.tmp", RECORDS);

  printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);
}

void saveWithUpdate(struct Record r, struct User u, int line) {
  /* File pointer to hold reference of input file */
  FILE *fPtr;
  FILE *fTemp;

  char buffer[BUFFER_SIZE];
  char newline[BUFFER_SIZE];
  int count;

  printf("Replace '%d' line with: ", line);
  fgets(newline, BUFFER_SIZE, stdin);

  /*  Open all required files */
  fPtr = fopen(RECORDS, "r");
  fTemp = fopen("replace.tmp", "w");

  /* fopen() return NULL if unable to open file in given mode. */
  if (fPtr == NULL || fTemp == NULL) {
    /* Unable to open file hence exit */
    printf("\nUnable to open file.\n");
    printf("Please check whether file exists and you have read/write "
           "privilege.\n");
    exit(EXIT_SUCCESS);
  }

  /*
   * Read line from source file and write to destination
   * file after replacing given line.
   */
  count = 0;
  while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {
    count++;

    /* If current line is line to replace */
    if (count == line + 1) {
      fprintf(fTemp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n", r.id, u.id,
              u.name, r.accountNbr, r.deposit.month, r.deposit.day,
              r.deposit.year, r.country, r.phone, r.amount, r.accountType);
    } else {

      fputs(buffer, fTemp);
    }
  }

  /* Close all files to release resource */
  fclose(fPtr);
  fclose(fTemp);

  /* Delete original source file */
  remove(RECORDS);

  /* Rename temporary file as original file */
  rename("replace.tmp", RECORDS);

  printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);
}

void updateAcc(struct User u) {
  checkThisAccs(u);
  int linenbr = chooseYourAccount(u);
  printf("%d", linenbr);
  struct Record r;
  struct Record cr;
  char userName[50];
  FILE *pf = fopen(RECORDS, "a+");

noAccount:
  system("clear");
  printf("\t\t\t===== New record =====\n");

  printf("\nEnter today's date(mm/dd/yyyy):");
  scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
  printf("\nEnter the account number:");
  scanf("%d", &r.accountNbr);
  printf("\nEnter the country:");
  scanf("%s", r.country);
  printf("\nEnter the phone number:");
  scanf("%s", r.phone);
  printf("\nEnter amount to deposit: $");
  scanf("%lf", &r.amount);
  printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> "
         "fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 "
         "years)\n\n\tEnter your choice:");
  scanf("%s", r.accountType);
  r.id = linenbr;
  saveWithUpdate(r, u, linenbr);
}
int chooseYourAccount(struct User u) {
  int accnbr;
chooseAgain:
  printf("\t\t\t===== choose account =====\n");
  scanf("%d", &accnbr);
  printf("to get exit type 0");
  int line = getLineByAccNbr(u, accnbr);
  if (line == -1) {
    printf("\n\n\n\naccount doesn't exists or you typed wrong number\n");
    printf("\nif you want to exit: 0\n");
    printf("\nto retype the number type: 1\n\n\n\n\n\n:");
    int ch;
    scanf("%d", &ch);
    if (ch == 0) {
      exit(1);
    } else {
      goto chooseAgain;
    }
  }
  return line;
}

void createNewAcc(struct User u) {
  struct Record r;
  struct Record cr;
  char userName[50];
  FILE *pf = fopen(RECORDS, "a+");

noAccount:
  system("clear");
  printf("\t\t\t===== New record =====\n");

  printf("\nEnter today's date(mm/dd/yyyy):");
  scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
  printf("\nEnter the account number:");
  scanf("%d", &r.accountNbr);

  while (getAccountFromFile(pf, userName, &cr)) {
    if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr) {
      printf("✖ This Account already exists for this user\n\n");
      goto noAccount;
    }
  }
  printf("\nEnter the country:");
  scanf("%s", r.country);
  printf("\nEnter the phone number:");
  scanf("%s", r.phone);
  printf("\nEnter amount to deposit: $");
  scanf("%lf", &r.amount);
  printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> "
         "fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 "
         "years)\n\n\tEnter your choice:");
  scanf("%s", r.accountType);
  r.id = getLastNumberFromFile();

  saveAccountToFile(pf, u, r);

  fclose(pf);
  success(u);
}

void checkAllAccounts(struct User u) {
  char userName[100];
  struct Record r;

  FILE *pf = fopen(RECORDS, "r");

  system("clear");
  printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
  while (getAccountFromFile(pf, userName, &r)) {
    if (strcmp(userName, u.name) == 0) {
      printf("_____________________\n");
      printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone "
             "number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
             r.accountNbr, r.deposit.day, r.deposit.month, r.deposit.year,
             r.country, r.phone, r.amount, r.accountType);
    }
  }
  fclose(pf);
  success(u);
}
void checkThisAccs(struct User u) {
  char userName[100];
  struct Record r;

  FILE *pf = fopen(RECORDS, "r");

  system("clear");
  printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
  while (getAccountFromFile(pf, userName, &r)) {
    if (strcmp(userName, u.name) == 0) {
      printf("_____________________\n");
      printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone "
             "number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
             r.accountNbr, r.deposit.day, r.deposit.month, r.deposit.year,
             r.country, r.phone, r.amount, r.accountType);
    }
  }
  fclose(pf);
}
