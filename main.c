#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>

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


char* gera_codigo() {

  srand((unsigned int)(time(NULL)));
  char codigo[10];
	int index = 0;
  char char1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	for(index = 0; index < 10; index++)
	{
	  strncat(codigo, &char1[rand() % (sizeof char1 - 1)] ,sizeof(char));
	}
    char* r = malloc(sizeof(char*));
    strncpy(r,codigo,sizeof(codigo));
    return r;
}

void sendEmail(char* email, char* codigo) {
	char cmd[1000] = "";
	char stPart[100] = "sendemail -f TSTP32021@gmail.com -t ";
	char snPart[100] = " -u Codigo -m " ;
  strncat(snPart,codigo,strlen(codigo));
	char rdPart[100] = " -s smtp.gmail.com:587 -o tls=yes -xu TSTP32021@gmail.com -xp TSTP32021para_O_20";

	strcat(cmd, stPart);
	strcat(cmd, email);
  strcat(cmd, snPart);
	strcat(cmd, rdPart);

	system(cmd);
}


int getPermission(){
  char  email[20];
  printf("introduza email: ");
  scanf("%s", &email);
  /*
  FILE *file;
  file = fopen( "acessos.txt" , "r");*/
  char buf[100];
/*
  while((fgets(buf, 100, file)!=NULL)) {
    if(strstr(buf, email)!=NULL) {
      printf("Acesso garantido\n");
      printf("%s", buf);
      break;
    }*/
 int c;
 FILE *file;
 char string[50];
 file = fopen("acessos.txt", "r");
    if (file) {
        while ( fscanf(file,"%s", string) == 1)
                {
                        //Add a for loop till strstr(string, student) does-not returns null. 
                  for(int i = 0; strstr(string, email)!=NULL;i++){
                    if(strstr(string, email)!=0) {//if match found
                          printf("Acesso garantido\n"); 
                    }
                  }
                }
        fclose(file);
    }/*
    else
    {
      printf("O seu email não se encontra no ficheiro de acessos.\n");
      char* codigo = gera_codigo();
      printf("Um email com o código de acesso está a ser enviado!\n");
      sendEmail(email, codigo);
      char acesso[10];
      printf("Insira o código de acesso:");
      scanf("%s", &acesso);
      if(strcmp(acesso,codigo) == 0){
        printf("Acesso garantido\n");
        file = fopen( "acessos.txt" , "a");
        fputs(email,file);
      }
      else{
        printf("Código errado! Acesso negado!\n");
      }

    }
    
  }
  fclose(file);*/
  return 0;

}


int main() {
  getPermission();
  return 0;
}
