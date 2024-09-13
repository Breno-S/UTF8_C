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
	CODEPOINT_MAX = 0x10FFFF    /* 4-byte UTF-8 limit */
};

/**
 * @brief Ignored codepoint ranges.
 */
enum e_cp_ignored_ranges
{
	SURROGATES_START = 0xD800,
	SURROGATES_END = 0xDFFF,
	NONCHAR_START = 0xFDD0,
	NONCHAR_END = 0xFDEF
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
	uint32_t		full;
	unsigned char	octet[4];
}	t_utf8;

/******************************** FUNCTIONS ***********************************/

/**
 * @brief Encodes a Unicode codepoint into UTF-8.
 * @param cp Unicode codepoint.
 * @return The resulting UTF-8 encoding.
 */
t_utf8	utf8_encode(uint32_t cp);

/** 
 * @brief Appends UTF-8 character to a file.
 * @param utf8: UTF-8 encoded codepoint.
 * @param fp: Pointer to opened file.
 */
void	utf8_fput(t_utf8 utf8, FILE *fp);

#endif
