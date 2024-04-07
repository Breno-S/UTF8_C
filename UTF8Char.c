#include <stdint.h>
#include "UTF8Char.h"

union UTF8Char UTF8_encode(uint32_t cp) {
    // Codepoint final, codificado em UTF-8.
    union UTF8Char final_cp;

    // Checa se o codepoint é maior do que o valor máximo permitido pelo Unicode
    if (cp > 0x10FFFF) {
        final_cp.full = 0xEFBFBD; // Unicode replacement character
        return final_cp;
    }
    
    // Checa se é um surrogate pair (UTF-16) ou se está na faixa noncharacter
    if ((cp >= 0xD800 && cp <= 0xDFFF) || (cp >= 0xFDD0 && cp <= 0xFDEF)) {
        final_cp.full = 0xEFBFBD;
        return final_cp;
    }

    // Se o codepoint é menor que 128, então pertence à tabela ASCII
    if (cp < 0x80) {
        final_cp.full = cp;
    } else {
        // Variável auxiliar para manipulação de bytes.
        union UTF8Char aux_cp = {cp};
    
        // Se possuir dentre 8 a 11 bits, aplica-se a lógica de 2 bytes
        if (cp < 0x800) {
            // Prepara os octetos com os leading bits
            final_cp.octet[0] = 0b10000000; // 10######
            final_cp.octet[1] = 0b11000000; // 110#####
            final_cp.octet[2] = 0b00000000;
            final_cp.octet[3] = 0b00000000;

            // 6 primeiros bits do primeiro octeto preenchem o primeiro byte
            final_cp.octet[0] |= (aux_cp.octet[0] & 0b00111111);

            // Outros 2 bits do primeiro octeto vão pro começo do segundo byte
            final_cp.octet[1] |= ((aux_cp.octet[0] & 0b11000000) >> 6);

            // 3 bits restantes vão no segundo byte com offset de duas posições
            final_cp.octet[1] |= ((aux_cp.octet[1] & 0b00000111) << 2);
        }

        // Se possuir dentre 12 a 16 bits, é codificado em 3 bytes
        else if (cp < 0x10000) {
            // Prepara os octetos com os leading bits
            final_cp.octet[0] = 0b10000000; // 10######
            final_cp.octet[1] = 0b10000000; // 10######
            final_cp.octet[2] = 0b11100000; // 1110####
            final_cp.octet[3] = 0b00000000;

            // 6 primeiros bits do primeiro octeto preenchem o primeiro byte
            final_cp.octet[0] |= (aux_cp.octet[0] & 0b00111111);

            // Outros 2 bits do primeiro octeto vão pro começo do segundo byte
            final_cp.octet[1] |= ((aux_cp.octet[0] & 0b11000000) >> 6);

            // 4 primeiros bits do segundo octeto completam o segundo byte
            final_cp.octet[1] |= ((aux_cp.octet[1] & 0b00001111) << 2);

            // 4 bits finais do segundo octeto vão para o terceiro byte
            final_cp.octet[2] |= ((aux_cp.octet[1] & 0b11110000) >> 4);
        }

        // Se possuir dentre 17 e 21 bits, é codificado em 4 bytes
        else if (cp < 0x10FFFF) {
            // Prepara os octetos com os leading bits
            final_cp.octet[0] = 0b10000000; // 10######
            final_cp.octet[1] = 0b10000000; // 10######
            final_cp.octet[2] = 0b10000000; // 10######
            final_cp.octet[3] = 0b11110000; // 11110###

            // 6 primeiros bits do primeiro octeto preenchem o primeiro byte
            final_cp.octet[0] |= (aux_cp.octet[0] & 0b00111111);

            // Outros 2 bits do primeiro octeto vão pro começo do segundo byte
            final_cp.octet[1] |= ((aux_cp.octet[0] & 0b11000000) >> 6);

            // 4 primeiros bits do segundo octeto completam o segundo byte
            final_cp.octet[1] |= ((aux_cp.octet[1] & 0b00001111) << 2);

            // 4 bits finais do segundo octeto vão pro começo do terceiro byte
            final_cp.octet[2] |= ((aux_cp.octet[1] & 0b11110000) >> 4);

            // 2 primeiros bits do último octeto completam o terceiro byte
            final_cp.octet[2] |= ((aux_cp.octet[2] & 0b00000011) << 4);

            // 3 últimos bits vão para o quarto byte
            final_cp.octet[3] |= (aux_cp.octet[2] >> 2);
        }
    }
    return final_cp;
}
