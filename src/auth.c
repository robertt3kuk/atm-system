#include "header.h"
#include <termios.h>

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50]) {
  struct termios oflags, nflags;

  system("clear");
  printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
  scanf("%s", a);

  // disabling echo
  tcgetattr(fileno(stdin), &oflags);
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;
  nflags.c_lflag |= ECHONL;

  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
  printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
  scanf("%s", pass);

  // restore terminal
  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
};
void registerMenu(char a[50], char pass[50]) {
  struct termios oflags, nflags;

  system("clear");
  printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t Username To "
         "REgister:");
  scanf("%s", a);

  // disabling echo
  tcgetattr(fileno(stdin), &oflags);
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;
  nflags.c_lflag |= ECHONL;

  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
  printf("\n\n\n\n\n\t\t\t\tEnter the password to register:");
  scanf("%s", pass);

  // restore terminal
  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
    perror("tcsetattr");
    return exit(1);
  }
};
int getUid(struct User u) {
  FILE *fp;
  struct User userChecker;

  if ((fp = fopen("./data/users.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  int id = 0;

  while (fscanf(fp, "%d %s %s", &id, userChecker.name, userChecker.password) !=
         EOF) {
    if (strcmp(userChecker.name, u.name) == 0) {
      fclose(fp);
      return id;
    }
  }

  fclose(fp);
  return -1;
}

const char *getPassword(struct User u) {
  FILE *fp;
  struct User userChecker;

  if ((fp = fopen("./data/users.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  int id = 0;

  while (fscanf(fp, "%d %s %s", &id, userChecker.name, userChecker.password) !=
         EOF) {
    if (strcmp(userChecker.name, u.name) == 0) {
      fclose(fp);
      char *buff = userChecker.password;
      return buff;
    }
  }

  fclose(fp);
  return "no user found";
}
int saveUser(struct User u) {
  FILE *fp;

  if ((fp = fopen("./data/users.txt", "a+")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  int lastId = checkForUsername(u);

  if (lastId == 0) {
    return 0;
  }
  fprintf(fp, "%d %s %s\n", lastId, u.name, u.password);
  u.id = lastId;
  return 1;
}
int chooseUserTo(struct User u, struct User *ans) {
  FILE *fp;
  struct User userChecker;
  if ((fp = fopen("./data/users.txt", "a+")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  system("clear");
  printf("\nchoose users from the list\n");
  int ret = 0;
  while (fscanf(fp, "%d %s %s", &ret, userChecker.name, userChecker.password) !=
         EOF) {
    if (strcmp(userChecker.name, u.name) == 0) {
    } else {
      printf("\n%s\n", userChecker.name);
    }
  }
  printf("\nenter the name\n:");
  scanf("%s", ans->name);
  while (fscanf(fp, "%d %s %s", &ret, userChecker.name, userChecker.password) !=
         EOF) {
    if (strcmp(userChecker.name, ans->name) == 0) {
      fclose(fp);
      return ret;
    }
  }

  fclose(fp);
  return -1;
}

int checkForUsername(struct User u) {
  FILE *fp;
  struct User userChecker;

  if ((fp = fopen("./data/users.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  int ret = 0;
  while (fscanf(fp, "%d %s %s", &ret, userChecker.name, userChecker.password) !=
         EOF) {
    if (strcmp(userChecker.name, u.name) == 0) {
      fclose(fp);
      char *buff = userChecker.password;
      return 0;
    }
  }

  fclose(fp);
  return ret + 1;
}
