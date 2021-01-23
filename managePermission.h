#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h> 
#include <pthread.h>

const char *getUserName();
char *gera_codigo();
void sendEmail(char *email, char *codigo);
int find_email_ficheiro(char search_string[], char *ficheiro);
void *timeToWait();
int getPermission();