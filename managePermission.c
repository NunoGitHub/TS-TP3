#include "managePermission.h"

static int timer = 0;
static pthread_t thread_id;
#define MAX_TIME 30000

//obter o nome do utilizador dono
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
//gera o codigo que vai ser enviado por email para obter a permissão 
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
  char *r = (char *)malloc(sizeof(char *));
  strcpy(r, codigo);
  return r;
}
//envia o código para o email passado por argumento 
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

//verifica se um email e nome existe no ficheiro acessos.txt
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
//Conta o tempo maximo que o utilizador tem para por o codigo recebido
void *timeToWait()
{
  clock_t before = clock();
  int msec = 0, trigger = MAX_TIME;
  do
  {

    clock_t difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;
    timer = msec;
  } while (msec <= trigger);
  pthread_kill(&thread_id);
  return 0;
}

//verifica se um determinado utilizador tem acesso ao ficheiro, caso contrário envia um código para o seu email
//se o utilizador for o dono do ficheiro pode aceder diretamente
//caso o código colocado não seja correto ou o tempo ultrapassar 30 segundos, então é feito exit
int getPermission()
{
  char *email=(char *)(malloc(sizeof(char) * 20));
  char *nome=(char *)(malloc(sizeof(char) * 20));
  char *nomeAux=(char *)(malloc(sizeof(char) * 20));
  printf("Introduza nome: ");
  scanf("%s", nome);
  
  printf("introduza email: ");
  scanf("%s", email);
  strcpy(nomeAux,nome);
  char * nome_email= (char*)(malloc(sizeof(email)+sizeof(nome)));
  nome_email= strcat(nomeAux,"-");
  strncat(nome_email, email,(sizeof(char*))*(sizeof(email)+sizeof(nomeAux)));

  if(strcmp(getUserName(), nome)==0 || (find_email_ficheiro(nome_email, "/home/np/Desktop/mestrado/CSI/Tecnologia de Segurança/tp3/acessos.txt") == 0) ){
    printf("Acesso garantido\n");
    return 0;
  }
  else
  {
    printf("O seu email não se encontra no ficheiro de acessos.\n");
    char *codigo = (char *)(malloc(sizeof(char) * 10));
    codigo = gera_codigo();
    printf("Um email com o código de acesso está a ser enviado!\n");
    sendEmail(email, codigo);
    //Call thread
    pthread_create(&thread_id, NULL, timeToWait, NULL);
    char *acesso = NULL;
    acesso = (char *)malloc(sizeof(char) * 30);

    printf("Insira o código de acesso:");
    scanf("%s", acesso);
    if (timer >= MAX_TIME)
    {
      printf("\ntempo excedido = %f segundos \n", ((float)timer/(float)1000));
      pthread_kill(&thread_id);
      exit(0);
    }

    if (strcmp(acesso, codigo) == 0)
    {
      pthread_kill(&thread_id);
      printf("Acesso garantido\n");
      FILE *file;
      file = fopen("/home/np/Desktop/mestrado/CSI/Tecnologia de Segurança/tp3/acessos.txt", "a");
      fputs("\n", file);
      fputs(nome_email, file);
      fclose(file);
      return 0;
    }
    else
    {
      
      printf("Código errado! Acesso negado!\n");
      exit(0);
    }
  }
  return 0;
}