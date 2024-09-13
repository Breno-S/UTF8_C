#include <stdio.h>
#include <stdint.h>
#include "UTF8Char.h"

/*
Bytes are copied from the most significant to the least significant. Zeroed 
octets are ignored unless it's the least significant. 

TODO: Stop this backwards copying (?)
*/

void	utf8_fput(t_utf8 utf8, FILE *fp)
{
	int	i;

	if (fp)
	{
		i = 3;
		while (i >= 0)
		{
			if (utf8.octet[i] || i == 0)
				fputc(utf8.octet[i], fp);
			i--;
		}
	}
}
