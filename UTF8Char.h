#ifndef UTF8CHAR_H
# define UTF8CHAR_H

# include <stdint.h>
# include <stdio.h>

/********************************** ENUMS *************************************/

/**
 * @brief Codepoint limits for 1-byte, 2-byte, 3-byte and 4-byte encodings.
 */
enum e_cp_encoding_limits
{
	SEVEN_BITS = 0x7F,			/* 1-byte UTF-8 limit */
	ELEVEN_BITS = 0x7FF,		/* 2-byte UTF-8 limit */
	SIXTEEN_BITS = 0xFFFF,		/* 3-byte UTF-8 limit */
	CODEPOINT_MAX = 0x10FFFF	/* 4-byte UTF-8 limit */
};

/**
 * @brief Bit-masks for UTF-8 encodings bigger than 1-byte.
 * (leading bits checking).
 */
enum e_utf8_masks
{
	TWO_BYTE_MASK = 0b1110000011000000,
	TWO_BYTE_MASK_CHECK = 0b1100000010000000,
	THREE_BYTE_MASK = 0b111100001100000011000000,
	THREE_BYTE_MASK_CHECK = 0b111000001000000010000000,
	FOUR_BYTE_MASK = 0b11111000110000001100000011000000,
	FOUR_BYTE_MASK_CHECK = 0b11110000100000001000000010000000
};

/**
 * @brief Ignored codepoint ranges inside the Unicode table and their 
 * respective UTF-8 encodings.
 */
enum e_ignored_ranges
{
	SURRO_START_UC = 0xD800,
	SURRO_END_UC = 0xDFFF,
	NONCHAR_START_UC = 0xFDD0,
	NONCHAR_END_UC = 0xFDEF,
	SURRO_START_UTF8 = 0xEDA080,
	SURRO_END_UTF8 = 0xEDBFBF,
	NONCHAR_START_UTF8 = 0xEFB790,
	NONCHAR_END_UTF8 = 0xEFB7AF
};

/**
 * @brief Replacement character representations.
 */
enum e_replacement_characters
{
	REPLACEMENT_CHARACTER_UC = 0xFFFD,
	REPLACEMENT_CHARACTER_UTF8 = 0xEFBFBD
};

/********************************* TYPES **************************************/

/**
 * @brief 4 byte structure for a single codepoint. 
 * Each byte can be accessed via `octet[n]`.
 * 
 * `octet[0]` holds the least significant byte.
 */
typedef union u_utf8
{
	int32_t			full;
	unsigned char	octet[4];
}	t_utf8;

/******************************** FUNCTIONS ***********************************/

/**
 * @brief Encodes a Unicode codepoint into UTF-8.
 * @param cp Unicode codepoint.
 * @return The resulting UTF-8 encoding.
 */
t_utf8		utf8_encode(uint32_t cp);

/**
 * @brief Decodes a UTF-8 character to its Unicode representation.
 * @param utf8 UTF-8 encoded codepoint.
 * @return The Unicode codepoint.
 */
uint32_t	utf8_decode(t_utf8 utf8);

/** 
 * @brief Appends UTF-8 character to a file.
 * @param utf8 UTF-8 encoded codepoint.
 * @param fp Pointer to opened file.
 */
void		utf8_fput(t_utf8 utf8, FILE *fp);

/**
 * @brief Reads a single UTF-8 encoded codepoint from file.
 * @param fp Pointer to opened file.
 * @return The character read.
 */
t_utf8		utf8_fget(FILE *fp);

#endif
