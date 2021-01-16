#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#define cknull(x) if((x)==NULL) {perror(""); exit(EXIT_FAILURE);}
#define cknltz(x) if((x)<0) {perror(""); exit(EXIT_FAILURE);}
#define LIST_LEN 4 

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
int GetPermission(){
  char  email[20];
  printf("introduza email: ");
  scanf("%s", &email);
  FILE *file;
  file = fopen( "acessos.txt" , "r");
  char buf[100];

  while((fgets(buf, 100, file)!=NULL)) {
    if(strstr(buf, email)!=NULL) {
      //printf("encontrou");
      //printf("%s", buf);
      printf("\nacesso garantido\n");
      break;
    }
    else
    {
      fclose(file);
      email_it(file);
      
    }
    
  }
  

  return 0;

}

int main() {

    //char myvariable=  $(whoami)
    //printf("%s",getUserName());
    //GetPermission();
    //sendmail("a85166@alunos.uminho.pt","123");
    //SendEmail();
    //email_it("acessos.txt");

    
    return 0;
}
