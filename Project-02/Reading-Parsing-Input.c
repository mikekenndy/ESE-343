// Mike Kennedy - 108715992
// ESE 333.01 Project 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFERSIZE 500
#define LONGEST_CMD_LEN 7

// Greeting
void init_shell()
{
  printf("\n\n\n\n****************************************");
  printf("\n\t**** Custom Shell ****");
  printf("\n\t**** Mike Kennedy ****");
  printf("\n\t****  108715992   ****");
  printf("\n****************************************");
  char* username = getenv("USER");
  printf("\n\nUSER is: @%s", username);
  printf("\n");
}


// Linked-list object containing:
// commandName - name of command entered into terminal
// *next - pointer to next object in list
struct command
{
  char commandName[LONGEST_CMD_LEN];
  struct command *nextCMD;
};


// Adds newest command to linked list
struct command *finder(struct command* prev, char CMD[LONGEST_CMD_LEN])
{
  // Create list obj to return and allocate memory
  struct command* found = NULL;
  found = (struct command*)malloc(sizeof(struct command));

  strcpy(found->commandName, CMD);
  prev->nextCMD = found;

  return found;
}


// Finds commands in a string
char *findCMDs(char input[])
{
  static char result[BUFFERSIZE] = "";
  strcpy(result, "\0");
  char *ptr;
  
  // Look for ECHO
  ptr = strstr(input, "echo ");
  if(ptr != NULL)
    strcat(result, "  echo");
    
  // Look for "cat"
  ptr = strstr(input, "cat ");
  if(ptr != NULL)
    strcat(result, "  cat");

  // Look for "man info"
  ptr = strstr(input, "man info ");
  if(ptr != NULL)
    strcat(result, "  man info");

  // Look for "xterm"
  ptr = strstr(input, "xterm ");
  if(ptr != NULL)
    strcat(result, "  xterm");

  // Look for "cd"
  ptr = strstr(input, "cd ");
  if(ptr != NULL)
    strcat(result, "  cd");


  return result;
}


int main()
{
  init_shell();
  
  // Test declaration of struct:
  struct command* t1 = NULL;
  struct command* t2 = NULL;
  struct command* t3 = NULL;

  // Allocate memory for objects
  t1 = (struct command*)malloc(sizeof(struct command));
  t2 = (struct command*)malloc(sizeof(struct command));
  t3 = (struct command*)malloc(sizeof(struct command));

  t2 = finder (t1, "cmd1");
  t3 = finder (t2, "cmd2");

  //String where user input is stored
  char buff[BUFFERSIZE];

  // Continually get user input
  while(1)
    {
      printf("\n>>> ");
      fgets(buff, BUFFERSIZE, stdin);
      //Remove trailing \n character
      buff[strcspn(buff, "\n")] = 0;

      // Search for commands
      if(strstr(buff, "echo ") != NULL ||
	 strstr(buff, "cat ") != NULL ||
	 strstr(buff, "man info ") != NULL ||
	 strstr(buff, "xterm & ") != NULL ||
	 strstr(buff, "cd") != NULL)
	{
	  char *foundCMD = findCMDs(buff);
	  printf("\nCommands:%s", foundCMD);
	} else {
	printf("\nCommand '%s' not found", buff);
      }
    }

  return(0);      
}


