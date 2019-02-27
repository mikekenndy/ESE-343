// Mike Kennedy - 108715992
// ESE 333.01 Project 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFERSIZE 500
#define LONGEST_CMD_LEN 7

// Commands recognized
char *COMMANDS[] =
  {"echo", "cat", "man info", "xterm", "cd", "ls"};
int numCMDs = sizeof(COMMANDS)/sizeof(COMMANDS[0]);

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
void findCMDs(char input[])
{
  // Look for known commands and add to list if found
  char *ptr;
  for(int i = 0; i < numCMDs; i++)
    {
      ptr = strstr(input, COMMANDS[i]);
      if (ptr != NULL)
	addToList(COMMANDS[i], input);
    }
}

// Check to see if string contains any commands
int containsCMD(char str[])
{
  char *ptr;
  for(int i = 0; i < numCMDs; i++)
    {
      ptr = strstr(str, COMMANDS[i]);
      if (ptr != NULL)
	return 1;
    }
  return 0;
}


// Delete linked list
void deleteList(struct command** start)
{
  struct command* current = *start;
  struct command* next;
  while (current != NULL)
    {
      next = current->nextCMD;
      free(current);
      current=next;
    }
  *start = NULL;
}


// --Main--
int main()
{
  init_shell();

  //String where user input is stored
  char buff[BUFFERSIZE];

  // Continually get user input
  while(1)
    {
      deleteList(&head);
      printf("\n>>> ");
      fgets(buff, BUFFERSIZE, stdin);
      //Remove trailing \n character
      buff[strcspn(buff, "\n")] = 0;

      // Search for commands
      if(containsCMD(buff))
	{
	  // Find commands and add to linked-list
	  findCMDs(buff);

	  // Print commands	 
	  struct command *cursor;
	  cursor = (struct command *)malloc(sizeof(struct command));
	  cursor = head;
	  printf("\n---------------------------------------------");
	  printf("\n Commands: ");
	  while (cursor->nextCMD != NULL)
	    {
	      printf("  %s", cursor->commandName);
	      cursor = cursor->nextCMD;
	    }
	  printf("  %s", cursor->commandName);

	  // Print args
	  cursor = head;
	  while (cursor->nextCMD != NULL)
	    {
	      printf("\n %s: %s", cursor->commandName, cursor->argument);
	      cursor = cursor->nextCMD;
	    }
	  printf("\n %s: %s", cursor->commandName, cursor->argument);
	  printf("\n---------------------------------------------\n");
	}
      else
	printf("\nCommand '%s' not found", buff);
    }

  return(0);      
}


