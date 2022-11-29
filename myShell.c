
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *readLineByLine();
int giveInput(char *str);
void Clear();
void showFiles();
void cat(char *str);
void callWithName(char **parsed);
void Tekrar(char **parsed);
void execx(char **parsed);
void Help();
int executeCommand(char **parsed);
void processString(char *str, char **parsed);

int main()
{
	char inputString[500], *Args[100];

	while (1)
	{ // infinite loop
		printf("myshell>>");
		if (giveInput(inputString))
			continue;
		processString(inputString, Args);
		executeCommand(Args);
	}
	return 0;
}

// Input
int giveInput(char *str)
{
	char *buf;
	buf = readLineByLine();
	if (strlen(buf) != 0)
	{
		strcpy(str, buf);
		return 0;
	}
	else
	{
		return 1;
	}
}

// read from args
char *readLineByLine()
{
	char *line = (char *)malloc(sizeof(char) * 1024); //  memory allocation
	char read;
	int index = 0;
	int bufferSize = 1024;

	if (!line)
	{
		printf("\n Buffer Could Not Allocated.");
		exit(1);
	}
	while (1)
	{
		read = getchar();
		if (read == EOF || read == '\n')
		{
			line[index] = '\0';
			return line;
		}
		else
		{
			line[index] = read;
		}
		index++;

		// if size of buffer not enough
		if (index >= bufferSize)
		{
			bufferSize += 1024;
			line = realloc(line, sizeof(char) * bufferSize);
			if (!line)
			{ // Fail
				printf("\nbuffer not allocated");
				exit(1);
			}
		}
	}
}

// Clear
void Clear()
{
	printf("\033[H\033[J");
}

// ls function
void showFiles()
{
	system("/bin/ls");
}

// cat Function
void cat(char *str)
{
	printf("\ncat : %s\n", str);
}
// Command Execution by file name
void callWithName(char **tokenized)
{
	// Child process
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("\nFailed to fork");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(tokenized[0], tokenized) < 0)
		{
			printf("\nInvalid command..");
		}
		exit(0);
	}
	else
	{
		// waiting for child
		return;
	}
}

// Run execx program
void execx(char **tokenized)
{
	pid_t pid = fork();
	char *path;
	path = "execx";

	if (pid == -1)
	{
		printf("\nFailed to fork");
		return;
	}
	else if (pid == 0)
	{
		if (execv(path, tokenized) < 0)
		{
			printf("\nInvalid command..");
		}
		exit(0);
	}
	else
	{
		// waiting for child
		wait(NULL);
		return;
	}
}

// Help command
void Help()
{
	puts("\nThe commands you can use are listed: "
		 "\n>cat -- print arguments "
		 "\n>ls -- list files"
		 "\n>exit -- exist from program"
		 "\n>clear -- clear Screen"
		 "\n>bash -- open standard bash terminal"
		 "\n>execx -- execute Writef program to writing to a file, time and pids");

	return;
}

// Execute commands
int executeCommand(char **tokenized)
{
	int numberOfCommands = 7;
	int i;
	int cursor = 0;
	char *commandList[numberOfCommands];

	commandList[0] = "exit";
	commandList[1] = "cat";
	commandList[2] = "help";
	commandList[3] = "clear";
	commandList[4] = "ls";
	commandList[5] = "bash";
	commandList[6] = "execx";

	for (i = 0; i < numberOfCommands; i++)
	{
		if (strcmp(tokenized[0], commandList[i]) == 0)
		{
			cursor = i + 1;
			break;
		}
	}

	switch (cursor)
	{
	case 1:
		exit(0);
	case 2:
		cat(tokenized[1]);
		return 1;
	case 3:
		Help();
		return 1;
	case 4:
		Clear();
		return 1;
	case 5:
		showFiles();
		return 1;
	case 6:
		callWithName(tokenized);
		return 1;
	case 7:
		execx(tokenized);
		return 1;
	default:
		puts("giving command is invalid");
		break;
	}

	return 0;
}

// string parsing and taking as args
void processString(char *str, char **tokenized)
{
	int i;
	for (i = 0; i < 100; i++)
	{
		tokenized[i] = strsep(&str, " ");

		if (tokenized[i] == NULL)
			break;
		if (strlen(tokenized[i]) == 0)
			i--;
	}
}
