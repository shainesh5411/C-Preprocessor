#include "pre.h"
#include "file_inclusion.h"

void file_inclusion(FILE *ip, FILE *op)
{
	char file[256], line[512];
	char path[512];
	char *p, *start, *end;
	long unsigned int i;
	int ch;

	while (fgets(line, sizeof(line), ip))
	{
		if (strstr(line, "#include"))
		{
			p = line;
			start = strchr(p, '"');//found double quote
			if (start != NULL)
				end = strchr(start + 1, '"');
			else
			{
				start = strchr(p, '<');

				if (start != NULL)
					end = strchr(start + 1, '>');
				else
					end = NULL;
			}
			if (start != NULL && end != NULL)
			{
				start++;
				i = 0;
				while (start < end && i < sizeof(file) - 1)   //get the file name
				{
					file[i++] = *start++;
				}
				file[i] = '\0';
				FILE *fp = fopen(file, "r");//search for current directory
				if (fp == NULL)
				{
					snprintf(path, sizeof(path),
							"/usr/include/%s", file);

					fp = fopen(path, "r");//search for system lib
				}
				if (fp == NULL)
				{
					printf("HEADER FILE NOT FOUND: %s\n", file);
					return;
				}
				while ((ch = fgetc(fp)) != EOF)//copy header file contents
				{
					fputc(ch, op);
				}
				fclose(fp);
			}
			else
			{
				printf("INVALID INCLUDE DIRECTIVE\n");
				return;
			}
		}
		else
		{
			fputs(line, op);
		}
	}
}
