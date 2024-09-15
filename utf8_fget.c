#include <stdio.h>
#include <stdint.h>
#include "UTF8Char.h"

void	read_2_bytes(t_utf8 *utf8, FILE *fp);
void	read_3_bytes(t_utf8 *utf8, FILE *fp);
void	read_4_bytes(t_utf8 *utf8, FILE *fp);

/*
Simple read from file operation. It checks the leading bits of the first 
byte and then saves the corresponding amount of bytes into the t_utf8 
structure. If the resulting UTF-8 encoded codepoint is invalid, the function 
overwrites it with the replacement character.
*/

t_utf8	utf8_fget(FILE *fp)
{
	int		byte;
	t_utf8	utf8;

	utf8.full = 0;
	byte = fgetc(fp);
	if ((byte & 0b10000000) == 0b00000000 || byte == EOF)
		utf8.octet[0] = byte;
	else
	{
		ungetc(byte, fp);
		if ((byte & 0b11100000) == 0b11000000)
			read_2_bytes(&utf8, fp);
		else if ((byte & 0b11110000) == 0b11100000)
			read_3_bytes(&utf8, fp);
		else if ((byte & 0b11111000) == 0b11110000)
			read_4_bytes(&utf8, fp);
		else
			utf8.full = REPLACEMENT_CHARACTER_UTF8;
	}
	return (utf8);
}

void	read_2_bytes(t_utf8 *utf8, FILE *fp)
{
	utf8->octet[1] = fgetc(fp);
	utf8->octet[0] = fgetc(fp);
	if (((utf8->octet[0] & 0b11000000) != 0b10000000)
		|| ((utf8->octet[1] & 0b11100000) != 0b11000000)
		|| (utf8->full >= SURRO_START_UTF8 && utf8->full <= SURRO_END_UTF8)
		|| (utf8->full >= NONCHAR_START_UC && utf8->full <= NONCHAR_END_UC))
		utf8->full = REPLACEMENT_CHARACTER_UTF8;
}

void	read_3_bytes(t_utf8 *utf8, FILE *fp)
{
	utf8->octet[2] = fgetc(fp);
	utf8->octet[1] = fgetc(fp);
	utf8->octet[0] = fgetc(fp);
	if (((utf8->octet[0] & 0b11000000) != 0b10000000)
		|| ((utf8->octet[1] & 0b11100000) != 0b10000000)
		|| ((utf8->octet[2] & 0b11110000) != 0b11100000)
		|| (utf8->full >= SURRO_START_UTF8 && utf8->full <= SURRO_END_UTF8)
		|| (utf8->full >= NONCHAR_START_UC && utf8->full <= NONCHAR_END_UC))
		utf8->full = REPLACEMENT_CHARACTER_UTF8;
}

void	read_4_bytes(t_utf8 *utf8, FILE *fp)
{
	utf8->octet[3] = fgetc(fp);
	utf8->octet[2] = fgetc(fp);
	utf8->octet[1] = fgetc(fp);
	utf8->octet[0] = fgetc(fp);
	if (((utf8->octet[0] & 0b11000000) != 0b10000000)
		|| ((utf8->octet[1] & 0b11000000) != 0b10000000)
		|| ((utf8->octet[2] & 0b11000000) != 0b10000000)
		|| ((utf8->octet[3] & 0b11111000) != 0b11110000)
		|| (utf8->full >= SURRO_START_UTF8 && utf8->full <= SURRO_END_UTF8)
		|| (utf8->full >= NONCHAR_START_UC && utf8->full <= NONCHAR_END_UC))
		utf8->full = REPLACEMENT_CHARACTER_UTF8;
}
