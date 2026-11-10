#include "pre.h"
#include"comment.h"
void comment_removal(FILE *ip, FILE *op)
{
	int ch, next;

	while ((ch = fgetc(ip)) != EOF)
	{
		if (ch == '/')
		{
			next = fgetc(ip);

			if (next == '/')
			{
				while ((ch = fgetc(ip)) != EOF && ch != '\n'); //single line

				if (ch == '\n')
					fputc('\n', op);
			}
			else if (next == '*')
			{
				while ((ch = fgetc(ip)) != EOF)//multiline
				{
					if (ch == '\n')
						fputc('\n', op);

					if (ch == '*')
					{
						next = fgetc(ip);

						if (next == '/')
							break;

						if (next == EOF)
							break;

						if (next == '\n')
							fputc('\n', op);
					}
				}
			}
			else
			{
				fputc('/', op);//not an comment

				if (next != EOF)
					fputc(next, op);
			}
		}
		else
		{
			fputc(ch, op);
		}
	}
}
