#include "pre.h"
#include "macro.h"

struct macro
{
	char name[50];
	char args[10][50];
	char value[200];
	int type;
	int arg_count;
};

// Second replacement function 

void double_replace(char *temp, struct macro m[], int count, FILE *op)
{
	int i, j, k, found;

	for (i = 0; temp[i] != '\0'; i++)
	{
		found = 0;

		for (j = 0; j < count; j++)
		{
			if (m[j].type != 0)
				continue;

			if (temp[i] != m[j].name[0])
				continue;

			for (k = 0; m[j].name[k] != '\0'; k++)
			{
				if (temp[i + k] != m[j].name[k])
					break;
			}

			if (m[j].name[k] == '\0')
			{
				fputs(m[j].value, op);

				i = i + k - 1;
				found = 1;
				break;
			}
		}

		if (found == 0)
			fputc(temp[i], op);
	}
}

void macro_handler(FILE *ip, FILE *op)
{
	struct macro m[100];

	char line[512];
	char actual[10][50];
	char temp[512];

	int count = 0;
	int i, j, k, n;
	int arg, pos, f, t;

	//get macro in an array
	while (fgets(line, sizeof(line), ip))
	{
		if (strncmp(line, "#define ", 8) == 0)
		{
			if (count >= 100)
				continue;

			char *p = line + 8;

			i = 0;


			while (*p != '(' && *p != ' ' && *p != '\0')	//read macro nm
				m[count].name[i++] = *p++;

			m[count].name[i] = '\0';


			if (*p == '(')   //for fun macro
			{
				m[count].type = 1;

				p++;
				arg = 0;
				pos = 0;

				while (*p != ')' && *p != '\0')
				{
					if (*p == ',')
					{
						m[count].args[arg][pos] = '\0';
						arg++;
						pos = 0;
					}
					else
					{
						m[count].args[arg][pos++] = *p;
					}

					p++;
				}

				m[count].args[arg][pos] = '\0';

				m[count].arg_count = arg + 1;

				p++;

				while (*p == ' ')
					p++;

				strcpy(m[count].value, p);
			}

			// OBJECT-LIKE MACRO 

			else
			{
				m[count].type = 0;
				m[count].arg_count = 0;

				while (*p == ' ')
					p++;

				strcpy(m[count].value, p);
			}

			n = strlen(m[count].value);

			if (n > 0 && m[count].value[n - 1] == '\n')
				m[count].value[n - 1] = '\0';

			count++;
		}
	}

	// Substitute macros 

	rewind(ip);

	while (fgets(line, sizeof(line), ip))
	{
		if (strncmp(line, "#define ", 8) == 0)
			continue;

		for (i = 0; line[i] != '\0'; i++)
		{
			f = 0;

			for (j = 0; j < count; j++)
			{
				if (line[i] != m[j].name[0])
					continue;

				for (k = 0; m[j].name[k] != '\0'; k++)
				{
					if (line[i + k] != m[j].name[k])
						break;
				}

				if (m[j].name[k] != '\0')
					continue;

				// FUNCTION-LIKE MACRO 

				if (m[j].type == 1 && line[i + k] == '(')
				{
					i = i + k + 1;

					arg = 0;
					pos = 0;

					while (line[i] != ')' && line[i] != '\0')
					{
						if (line[i] == ',')
						{
							actual[arg][pos] = '\0';
							arg++;
							pos = 0;
						}
						else
						{
							actual[arg][pos++] = line[i];
						}

						i++;
					}

					actual[arg][pos] = '\0';

					// First replacement 

					t = 0;

					for (n = 0; m[j].value[n] != '\0'; n++)
					{
						int found = 0;

						for (k = 0; k < m[j].arg_count; k++)
						{
							if (m[j].value[n] == m[j].args[k][0])
							{
								for (int x = 0; actual[k][x] != '\0'; x++)
									temp[t++] = actual[k][x];

								found = 1;
								break;
							}
						}

						if (found == 0)
							temp[t++] = m[j].value[n];
					}

					temp[t] = '\0';

					// Second replacement 

					double_replace(temp, m, count, op);

					f = 1;
					break;
				}

				// OBJECT-LIKE MACRO 

				else if (m[j].type == 0)
				{
					fputs(m[j].value, op);

					i = i + k - 1;

					f = 1;
					break;
				}
			}

			if (f == 0)
				fputc(line[i], op);
		}
	}
}

