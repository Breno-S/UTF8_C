#include <stdio.h>
#include "UTF8Char.h"

int main() {
    // Code point Unicode (ou UTF-32) a ser codificado em UTF-8.
    uint32_t cp = 0x1F4A9;

    // Code point codificado em UTF-8.
    union UTF8Char utf8 = UTF8_encode(cp);

    FILE *fp = NULL;
    fp = fopen("texto_utf8.txt", "a");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    } 
    
    // Copia os bytes (em ordem inversa) para o arquivo.

    for (int i = 3; i >= 0; i--) {
        if (utf8.octet[i] != 0) {
            fputc(utf8.octet[i], fp);
        }
    }
    
    fclose(fp);
    
    return 0;
}
