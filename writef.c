#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void *getSystemTime(char *strDate)
{
	time_t mytime = time(NULL);
	char *time_str = ctime(&mytime);
	time_str[strlen(time_str) - 1] = '\0';
	strcpy(strDate, time_str);
	strDate[strlen(strDate)] = '\0';
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		for (size_t i = 0; i < argc; i++)
		{
			printf("%s\n", argv[i]);
		}

		printf("eksik veya fazla parametre girdiniz\n");
		exit(0);
	}

	if (strcmp(argv[1], "-f") != 0)
	{
		printf("hatali parametre\n");
		exit(0);
	}

	FILE *filePointer;
	filePointer = fopen(argv[2], "a+");
	char date[100];
	getSystemTime(date);

	fprintf(filePointer, "%s", date);
	fprintf(filePointer, "   ");
	fprintf(filePointer, "%d", getpid());
	fprintf(filePointer, "   ");
	fprintf(filePointer, "%d", getppid());
	fprintf(filePointer, "\n");

	fclose(filePointer);
}