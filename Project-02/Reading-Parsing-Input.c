// Mike Kennedy - 108715992
// ESE 333.01 Project 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFERSIZE 500
#define LONGEST_CMD_LEN 7

// Linked-list object containing:
// commandName - name of command entered into terminal
// argument - argument following command
// *next - pointer to next object in list
struct command
{
  char commandName[LONGEST_CMD_LEN];
  char argument[BUFFERSIZE];
  struct command *nextCMD;
};

// Creat command head for linked list
struct command *head;


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

// Add command to linked list
void addToList(char cmd[LONGEST_CMD_LEN], char input[BUFFERSIZE])
{  
  // Find argument after command
  char *c = strstr(input, cmd);
  char arg[BUFFERSIZE];
  int i = strlen(cmd) + 1;
  int j = 0;
  while(c[i] != '\0' && c[i] != '|')
    {
      arg[j] = c[i];
      i++;
      j++;
    }

  // Create object
  struct command *add = NULL;
  add = (struct command *)malloc(sizeof(struct command));
  
  strcpy(add->commandName, cmd);
  strcpy(add->argument, arg);

  // Check whether head was initialized
  if(head == NULL)
    head = add;
  else
    {
      struct command *cursor;
      cursor = (struct command *)malloc(sizeof(struct command));
      cursor = head;

      // Move to end of list
      while(cursor->nextCMD != NULL)
      	  cursor = cursor->nextCMD;
      cursor->nextCMD = add;

    }

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
    addToList("echo", input);
    
  // Look for "cat"
  ptr = strstr(input, "cat ");
  if(ptr != NULL)
    addToList("cat", input);    

  // Look for "man info"
  ptr = strstr(input, "man info ");
  if(ptr != NULL)
    addToList("man info", input);

  // Look for "xterm"
  ptr = strstr(input, "xterm ");
  if(ptr != NULL)
    addToList("xterm", input);

  // Look for "cd"
  ptr = strstr(input, "cd ");
  if(ptr != NULL)
    addToList("cd", input);

  return result;
}


// Main
int main()
{
  init_shell();

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

	  // Print commands	 
	  struct command *cursor;
	  cursor = (struct command *)malloc(sizeof(struct command));
	  cursor = head;
	  printf("\n---------------------------------------------");
	  printf("\n Commands: ");
	  do
	    {
	      printf("  %s", cursor->commandName);
	      cursor = cursor->nextCMD;
	    } while (cursor->nextCMD != NULL);
	}
      else
	printf("\nCommand '%s' not found", buff);
    }

  return(0);      
}


