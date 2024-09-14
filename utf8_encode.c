#include <stdint.h>
#include "UTF8Char.h"

void	encode_2_bytes(t_utf8 *utf8, uint32_t cp);
void	encode_3_bytes(t_utf8 *utf8, uint32_t cp);
void	encode_4_bytes(t_utf8 *utf8, uint32_t cp);

/*
Checks if the integer is a valid codepoint (small enough and outside of the 
noncharacter or UTF-16 surrogates range), then encodes it in UTF8. The 
replacement character is returned when the argument is invalid.

Each encoding size has its own procedure, except 1-byte. Values up to 127 
(ASCII) don't need encoding.
*/

t_utf8	utf8_encode(uint32_t cp)
{
	t_utf8	utf8;

	utf8.full = 0xEFBFBD;
	if ((cp > CODEPOINT_MAX)
		|| ((cp >= SURROGATES_START && cp <= SURROGATES_END)
			|| (cp >= NONCHAR_START && cp <= NONCHAR_END)))
		return (utf8);
	if (cp <= SEVEN_BITS)
		utf8.full = cp;
	else
	{
		if (cp <= ELEVEN_BITS)
			encode_2_bytes(&utf8, cp);
		else if (cp <= SIXTEEN_BITS)
			encode_3_bytes(&utf8, cp);
		else if (cp <= CODEPOINT_MAX)
			encode_4_bytes(&utf8, cp);
	}
	return (utf8);
}

/**
 * Encodes 8-11 bit codepoints.
 */
void	encode_2_bytes(t_utf8 *utf8, uint32_t cp)
{
	utf8->octet[0] = 0b10000000;
	utf8->octet[0] |= cp & 0b00111111;
	cp >>= 6;
	utf8->octet[1] = 0b11000000;
	utf8->octet[1] |= cp & 0b00011111;
	utf8->octet[2] = 0b00000000;
	utf8->octet[3] = 0b00000000;
}

/**
 * Encodes 12-16 bit codepoints.
 */
void	encode_3_bytes(t_utf8 *utf8, uint32_t cp)
{
	utf8->octet[0] = 0b10000000;
	utf8->octet[0] |= cp & 0b00111111;
	cp >>= 6;
	utf8->octet[1] = 0b10000000;
	utf8->octet[1] |= cp & 0b00111111;
	cp >>= 6;
	utf8->octet[2] = 0b11100000;
	utf8->octet[2] |= cp & 0b00001111;
	utf8->octet[3] = 0b00000000;
}

/** 
 * Encodes 17-21 bit codepoints.
 */
void	encode_4_bytes(t_utf8 *utf8, uint32_t cp)
{
	utf8->octet[0] = 0b10000000;
	utf8->octet[0] |= cp & 0b00111111;
	cp >>= 6;
	utf8->octet[1] = 0b10000000;
	utf8->octet[1] |= cp & 0b00111111;
	cp >>= 6;
	utf8->octet[2] = 0b10000000;
	utf8->octet[2] |= cp & 0b00111111;
	cp >>= 6;
	utf8->octet[3] = 0b11110000;
	utf8->octet[3] |= cp & 0b00000111;
}
