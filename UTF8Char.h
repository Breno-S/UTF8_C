#include <stdint.h>

/* Estrutura de 4 bytes que armazena um code point UTF-8.

Cada byte pode ser acessado chamando `octet[n]`,
onde `n` é a posição do byte menos 1. */
union UTF8Char {
    // Representação do code point como um número inteiro positivo.
    uint32_t full; 

    /* Array que delimita cada um dos bytes que compõem o code point.
    
    `octet[0]` é o byte menos significativo, `octet[3]` o byte
    mais significativo. A representação final do code point segue
    a ordem do mais significativo para o menos significativo. */
    unsigned char octet[4];
};

/* Codifica um codepoint Unicode em UTF-8.

Sempre retorna uma `union UTF8Char` contendo um code point em UTF-8.
Se o argumento for um code point inválido, retorna um replacement character. */
union UTF8Char UTF8_encode(uint32_t);