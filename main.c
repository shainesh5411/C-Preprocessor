#include "pre.h"
#include "comment.h"
#include "file_inclusion.h"
#include"macro.h"
int main(int argc, char **argv)
{
	char fnm[256];
	char *dot;

	if (argc != 2)
	{
		printf("USAGE: ./mypreprocessor inputfile.c\n");
		return 1;
	}

	FILE *ip = fopen(argv[1], "r");

	if (ip == NULL)
	{
		printf("FILE NOT FOUND\n");
		return 1;
	}

	snprintf(fnm, sizeof(fnm), "%s", argv[1]);

	dot = strrchr(fnm, '.');

	if (dot != NULL)
		strcpy(dot, ".i");
	else
		strcat(fnm, ".i");

	FILE *temp1 = tmpfile();
	FILE *temp2 = tmpfile();
	FILE *op = fopen(fnm, "w");

	if (op == NULL)
	{
		printf("OUTPUT FILE CREATION FAILED\n");
		fclose(ip);
		fclose(temp1);
		return 1;
	}
	printf("1. Comment removal started\n");
	comment_removal(ip, temp1);

	printf("2. File inclusion started\n");
	rewind(temp1);
	file_inclusion(temp1, temp2);

	printf("3. Macro handler started\n");
	rewind(temp2);
	macro_handler(temp2, op);

	printf("4. Preprocessing completed\n");
	fclose(ip);
	fclose(temp1);
	fclose(temp2);
	fclose(op);

	printf("Preprocessing completed: %s\n", fnm);

	return 0;
}

