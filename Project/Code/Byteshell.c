#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int Byteshell_cd(char **args);
int Byteshell_help(char **args);
int Byteshell_exit(char **args);
int Byteshell_env(char **args);

char *builtin_function_names[] = {
  "cd",
  "help",
  "exit",
  "env"
};

int (*builtin_functions[]) (char **) = {
  &Byteshell_cd,
  &Byteshell_help,
  &Byteshell_exit,
  &Byteshell_env
};

int builtins() {
  return sizeof(builtin_function_names) / sizeof(char *);
}

//Implementing the builtins

//changing directory : cd

int Byteshell_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "Byteshell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("error in own_cd.c: changing dir\n");
    }
  }
  return 1;
}

//help

int Byteshell_help(char **args)
{
  int i;
  printf("This is Aadit's Byteshell_Project\n");
  printf("Type command, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < builtins(); i++) {
    printf("  %s\n", builtin_function_names[i]);
  }

  printf("Use the command for info on other programs.\n");
  return 1;
}

// exit

int Byteshell_exit(char **args)
{
  /* exit with status */
	if (args[1])
	{
		return (atoi(args[1]));
	}
	/* exit success */
	else
	{
		return (0);
	}
}

// env - function that return environment variables
extern char **environ;
int Byteshell_env(char **args)
{
	int i = 0;
	(void)(**args);

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (-1);
}

// in case any builtin is found launch it 

int launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process have fork value as 0
    if (execvp(args[0], args) == -1) {
      perror("Byteshell");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
   
    perror("Byteshell");
  } else {
    // Parent process having pid>0
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int Execute_input(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < builtins(); i++) {
    if (strcmp(args[0], builtin_function_names[i]) == 0) {
      return (*builtin_functions[i])(args);
    }
  }

  return launch(args);
}

// First step: Reading the command as a line or string of characters
// considering one character at a time and storing it in an array



char *Read_input(void)
{
 char *line = NULL;
 size_t original_size = 0;

 if (getline(&line, &original_size, stdin) == -1) /* if getline fails */
 {
  if (feof(stdin)) /* test for the eof */
  {
   free(line); /* avoid memory leaks when ctrl + d */
   exit(EXIT_SUCCESS); /* we recieved an eof */
  }
  else
  {
   free(line); /* avoid memory leaks when getline fails */
   perror("error while reading the line from stdin");
   exit(EXIT_FAILURE);
  }
 }
 return (line);
}

#define extra_space2 64
#define delimeter " \t\r\n\a"

char **Split_input(char *line){

    int original_size = extra_space2;
    int count=0;
    char **tokens = malloc(original_size* sizeof(char*));
    char *token, **tokens_backup;

    if(tokens == NULL){
            printf("Byteshell: Error in memory allocation");
            exit(1); 
        }

  token = strtok(line,delimeter);
  while (token != NULL) {
    tokens[count] = token;
    count++;

    if (count >= original_size) {
      original_size += extra_space2;
      tokens_backup = tokens;
      tokens = realloc(tokens, original_size * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, delimeter);
  }
  tokens[count] = NULL;
  return tokens;
    

}

void Byteshell(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = Read_input();
    args = Split_input(line);
    status = Execute_input(args);

    free(line);
    free(args);
  } while (status);
}


int main(int argc, char **argv)
{
 
  Byteshell();

  return EXIT_SUCCESS;
}


