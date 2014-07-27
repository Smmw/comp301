/*
 * Dan Shell - dsh
 *
 * The Dan Shell is an extremely limited shell for unix operating
 * systems.  It supports execution of commands that don't depend on
 * using stdin, and it will allow multiple commands using semi-colons
 * to delimit them.
 *
 * Dan Collins 2014
 * COMP301-14B
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Display the shell prompt.
 * 'user@hostname:directory $ '
 */
static void prompt(void) {
  char *user;
  char buf[256];

  /* Get username */
  user = getenv("USER");
  if (user)
    printf("%s@", user);

  /* Output hostname */
  gethostname(buf, 256);
  printf("%s", buf);

  /* Output working directory */
  getcwd(buf, 256);
  printf(":%s", buf);

  /* Make the end pretty */
  printf(" $ ");
}


/**
 * Remove leading spaces from a string.
 * @param str The string to remove spaces from
 * @returns The string without leading spaces
 */
static char *trim(char *str) {
  char *ret = str;

  /* Ignore NULL input */
  if (ret == NULL)
    return NULL;

  while (isspace(*ret))
    ret++;

  return ret;
}


int main(int argc, char **argv) {
  /* Input buffer */
  char buf[10000];
  /* Command to execute */
  char *command;
  /* Pipe to child */
  FILE *child;
  /* Character read from child */
  int c;

  prompt();

  while (1) {
    /* Get a line from stdin */
    fgets(buf, 10000, stdin);
    if (ferror(stdin)) {
      fprintf(stderr, "Error reading from stdin.\n");
      return EXIT_FAILURE;
    }

    /* Catch Ctrl+D on empty lines */
    if (feof(stdin))
      return EXIT_SUCCESS;

    /* Process the commands.
     * Delimiting on \n will remove it from commands. */
    command = strtok(buf, ";\n");
    while (command != NULL) {
      /* Remove whitespace */
      command = trim(command);

      /*
       * Exit command
       */
      if (strcmp(command, "exit") == 0)
	return EXIT_SUCCESS;

      /*
       * Welcome command
       */
      else if (strncmp(command, "welcome", 7) == 0) {
	/* Skip past 'welcome' and trim spaces */
	command += 8;
        command = trim(command);

	/* Greet! */
	printf("Hello, %s!\n", command);
      }

      /*
       * Other commands
       */
      else {
	/* Create the child process, opening a pipe to read from */
	child = popen((const char *)command, "r");
	if (child == NULL) {
	  fprintf(stderr, "Failed to create child process.\n");
	  fprintf(stderr, "Error number (%d)\n", errno);
	  return EXIT_FAILURE;
	}

        /* Until the child is done, display all characters set to the
	 * pipe. */
	while ((c = fgetc(child)) != EOF)
	  printf("%c", c);

	/* Check for errors */
	if (ferror(child)) {
	  fprintf(stderr, "Child terminated with errors.");
	  fprintf(stderr, "Error number (%d)\n", ferror(child));
	}

	/* Close the child process pipe */
	pclose(child);
      }

      /* Prepare for the next command */
      command = strtok(NULL, ";\n");
    }

    prompt();
  }
}

