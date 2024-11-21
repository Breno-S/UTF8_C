#include <stdio.h>
#include <stdint.h>
#include "UTF8Char.h"

int	main(void)
{
	uint32_t	cp;		// Unicode codepoint
	t_utf8		utf8;	// UTF-8 encoding
	FILE		*fp;	// File pointer (where result will be saved)

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
