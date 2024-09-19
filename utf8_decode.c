#include <stdint.h>
#include "UTF8Char.h"

void	decode_2_bytes(uint32_t *cp, t_utf8 utf8);
void	decode_3_bytes(uint32_t *cp, t_utf8 utf8);
void	decode_4_bytes(uint32_t *cp, t_utf8 utf8);

uint32_t	utf8_decode(t_utf8 utf8)
{
	uint32_t	cp;

	cp = 0;
	if ((utf8.full & 0b10000000) == 0b00000000 || utf8.full == EOF)
		cp = utf8.full;
	else if ((utf8.full & TWO_BYTE_MASK) == TWO_BYTE_MASK_CHECK)
		decode_2_bytes(&cp, utf8);
	else if ((utf8.full & THREE_BYTE_MASK) == THREE_BYTE_MASK_CHECK)
		decode_3_bytes(&cp, utf8);
	else if ((utf8.full & FOUR_BYTE_MASK) == FOUR_BYTE_MASK_CHECK)
		decode_4_bytes(&cp, utf8);
	else
		cp = REPLACEMENT_CHARACTER_UC;
	return (cp);
}

void	decode_2_bytes(uint32_t *cp, t_utf8 utf8)
{
	utf8.full &= ~TWO_BYTE_MASK;
	if (utf8.octet[1] <= 1)
		*cp = REPLACEMENT_CHARACTER_UC;
	else
	{
		*cp = 0;
		*cp |= utf8.octet[0];
		*cp |= utf8.octet[1] << 6;
	}
}

void	decode_3_bytes(uint32_t *cp, t_utf8 utf8)
{
	utf8.full &= ~THREE_BYTE_MASK;
	if (utf8.octet[2] == 0
		&& utf8.octet[1] <= 0b00011111)
		*cp = REPLACEMENT_CHARACTER_UC;
	else
	{
		*cp = 0;
		*cp |= utf8.octet[0];
		*cp |= utf8.octet[1] << 6;
		*cp |= utf8.octet[2] << 12;
	}
}

void	decode_4_bytes(uint32_t *cp, t_utf8 utf8)
{
	utf8.full &= ~FOUR_BYTE_MASK;
	if (utf8.octet[3] == 0
		&& utf8.octet[2] <= 0b00001111)
		*cp = REPLACEMENT_CHARACTER_UC;
	else
	{
		*cp = 0;
		*cp |= utf8.octet[0];
		*cp |= utf8.octet[1] << 6;
		*cp |= utf8.octet[2] << 12;
		*cp |= utf8.octet[3] << 18;
	}
}
