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
	utf8.octet[0] |= utf8.octet[1] << 6;
	utf8.octet[1] >>= 2;
	*cp = utf8.full;
}

void	decode_3_bytes(uint32_t *cp, t_utf8 utf8)
{
	utf8.full &= ~TWO_BYTE_MASK;
	utf8.octet[0] |= utf8.octet[1] << 6;
	utf8.octet[1] >>= 2;
	utf8.octet[1] |= utf8.octet[2] << 4;
	*cp = utf8.full;
}

void	decode_4_bytes(uint32_t *cp, t_utf8 utf8)
{
	utf8.full &= ~TWO_BYTE_MASK;
	utf8.octet[0] |= utf8.octet[1] << 6;
	utf8.octet[1] >>= 2;
	utf8.octet[1] |= utf8.octet[2] << 4;
	utf8.octet[2] >>= 4;
	utf8.octet[2] |= utf8.octet[3] << 2;
	*cp = utf8.full;
}
