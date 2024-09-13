#include <stdio.h>
#include <stdint.h>
#include "UTF8Char.h"

int	main(void)
{
	uint32_t	cp;
	t_utf8		utf8;
	FILE		*fp;

	cp = 0x1F4A9;
	utf8 = utf8_encode(cp);
	fp = fopen("text_output.txt", "a");
	if (fp == NULL)
	{
		perror("Error opening file");
		return (1);
	}
	utf8_fput(utf8, fp);
	fclose(fp);
	fp = NULL;
	return (0);
}
