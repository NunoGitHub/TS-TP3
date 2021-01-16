#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

const char *getUserName()
{
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw)
  {
    return pw->pw_name;
  }

  return "";
}

char *gera_codigo()
{

  srand((unsigned int)(time(NULL)));
  char codigo[10];
  int index = 0;
  char char1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  for (index = 0; index < 10; index++)
  {
    strncat(codigo, &char1[rand() % (sizeof char1 - 1)], sizeof(char));
  }
  char *r = (char*)malloc(sizeof(char *));
  strncpy(r, codigo, sizeof(codigo));
  return r;
}

void sendEmail(char *email, char *codigo)
{
  char cmd[1000] = "";
  char stPart[100] = "sendemail -f TSTP32021@gmail.com -t ";
  char snPart[100] = " -u Codigo -m ";
  strncat(snPart, codigo, strlen(codigo));
  char rdPart[100] = " -s smtp.gmail.com:587 -o tls=yes -xu TSTP32021@gmail.com -xp TSTP32021para_O_20";

  strcat(cmd, stPart);
  strcat(cmd, email);
  strcat(cmd, snPart);
  strcat(cmd, rdPart);

  system(cmd);
}

int find_email_ficheiro(char search_string[], char *ficheiro)
{
  FILE *fp;
  char ch, temp[25];
  int i = 0, k, search_len;
  long int count = 0;
  search_len = strlen(search_string);

  if ((fp = fopen(ficheiro, "r")) == NULL)
  {
    puts("open error");
    exit(0);
  }

  while ((ch = fgetc(fp)) != EOF)
  {
    if (i < search_len)
    {
      temp[i] = ch;
      ++i;
    }

    if (i == search_len)
    {

      count++;
      temp[i] = '\0';
      k = strcmp(search_string, temp);
      if (k == 0)
      {
        return 0;
      }
      i = 0;
      fseek(fp, count, SEEK_SET);
    }
  }
  return -1;
}

int getPermission()
{
  char email[20]={0};
  printf("introduza email: ");
  scanf("%s", &email);
  if (find_email_ficheiro(email, "acessos.txt") == 0)
  {
    printf("Acesso garantido\n");
  }
  else
  {
    printf("O seu email não se encontra no ficheiro de acessos.\n");
    char *codigo = (char*)(malloc(sizeof(char)*10));
    codigo = gera_codigo();
    printf("Um email com o código de acesso está a ser enviado!\n");
    sendEmail(email, codigo);
    char *acesso= NULL;
    acesso=(char*)malloc(sizeof(char)*30);
    printf("Insira o código de acesso:");
    scanf("%s", acesso);
    printf("Rmaillllll %s", email);
    if (strcmp(acesso, codigo) == 0)
    {
      printf("Acesso garantido\n");
      FILE *file;
      file = fopen("acessos.txt", "a");
      fputs("\n", file);
      fputs(email, file);
      fclose(file);
    }
    else
    {
      printf("Código errado! Acesso negado!\n");
     
    }
  }
  return 0;
}

int main()
{
  getPermission();
  return 0;
}
