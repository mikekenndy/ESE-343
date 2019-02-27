// C program to design a shell in linux
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>


// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

 void init_shell()
 {
   clear();
   printf("\n\n\n\n**********************************");
   printf("\n\n\n\t**** MY SHELL ****");
   printf("\n\n\t -USE AT YOUR OWN RISK-");
   printf("\n\n\n\n**********************************");

   char* username = getenv("USER");
   printf("\n\n\nUSER is: @%s", username);
   printf("\n");
   sleep(1);
   clear();
 }

// Function to take input
int takeInput(char* str)
{
  char* buf;

  buf = readline("\n>>> ");
  if (strlen(buf) != 0)
    {
      add_history(buf);
      strcpy(str, buf);
      return 0;
    }
  else
    return 1;
}

void printDir()
{
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("\nDir: %s", cwd);
}

// Function where the system command is executed
void execArgs(char** parsed)
{
  // Forking a child
  pid_t pid = fork();

  if (pid == -1)
    {
      printf("\nFailed forking child..");
      return;
    }
  else if (pid ==0)
    {
      if (execvp(parsed[0], parsed) < 0)
	printf("\nCould not execute command..");
      exit(0);
    }
  else
    {
      // Waiting for child to terminate
      wait(NULL);
      return;
    }
}

// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe)
{
  // 0 is read end, 1 is write end
  int pipefd[2];
  pid_t p1, p2;

  if (pipe(pipefd) < 0)
    {
      printf("\nPipe could not be initialized");
      return;
    }
  p1 = fork();
  if (p1 < 0)
    {
      printf("\nCould not fork");
      return;
    }

  if (p1 == 0)
    { // Child 1 is executing
      //It only needs to write at the write end
      close(pipefd[0]);
      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[1]);

      if (execvp(parsed[0], parsed) < 0)
	{
	  printf("\nCould not execute command 1..");
	  exit(0);
	}
    }
  else
    { // Parent executing
      p2 = fork();

      if (p2 < 0)
	{
	  printf("\n Could not fork");
	  return;
	}

      // Child 2 executing..
      // It only needs to read at the read end
      if (p2 == 0)
	{
	  close(pipefd[1]);
	  dup2(pipefd[0], STDIN_FILEN0);
	  close(pipefd[0]);
	  if (execvp(parsedpipe[0], parsedpipe) < 0)
	    {
	      printf("\nCould not execute command 2..");
	      exit(0);
	    }
	}
      else
	{
	  // parent executing, waiting for two children
	  wait(NULL);
	  wait(NULL);
	}
    }
  
