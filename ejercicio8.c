#include <stdio.h>
#include <math.h>

#define TAMANIO_PAGINA 4096 
#define BITS_OFFSET_PAGINA 12 // 4 KB = 2^12

// tabla de estructura
typedef struct {
    int bit_presencia;
    int bit_modificado;
    int marco_o_swap;
} EntradaTablaPaginas;

// convertimos direccion virtual a fisica
unsigned long convertir_direccion_virtual_a_fisica(unsigned long direccion_virtual, EntradaTablaPaginas tabla_paginas[], int num_paginas) {
    // Extraemos el número de página y el offset
    unsigned long numero_pagina = direccion_virtual >> BITS_OFFSET_PAGINA;
    unsigned long offset = direccion_virtual & (TAMANIO_PAGINA - 1); // ultimos 12 digitos

    // Verificamos si el número de página es válido
    if (numero_pagina >= num_paginas || tabla_paginas[numero_pagina].bit_presencia == 0) {
        printf("Error: La página solicitada no está en memoria o es inválida.\n");
        return -1;
    }

    // Obtener el marco de página y calcular la dirección física
    unsigned long marco_de_pagina = tabla_paginas[numero_pagina].marco_o_swap;
    unsigned long direccion_fisica = (marco_de_pagina << BITS_OFFSET_PAGINA) | offset;

    return direccion_fisica;
}

// Función para calcular el tamaño del espacio de direcciones virtuales
unsigned long calcular_tamano_espacio_virtual(EntradaTablaPaginas tabla_paginas[], int num_paginas) {
    unsigned long paginas_en_memoria = 0;

    for (int i = 0; i < num_paginas; i++) {
        if (tabla_paginas[i].bit_presencia == 1) {
            paginas_en_memoria++;
        }
    }

    return paginas_en_memoria * TAMANIO_PAGINA;
}

int main() {
    // Definimos la tabla de páginas (según el ejercicio)
    EntradaTablaPaginas tabla_paginas[6] = {
        {1, 0, 1},
        {0, 1, 8},
        {1, 0, 9},
        {1, 0, 14},
        {1, 0, 7},
        {0, 1, 16}
    };

    unsigned long direccion_virtual = 0x00005B83; // Dirección virtual de ejemplo

    // Convertir la dirección virtual a física
    unsigned long direccion_fisica = convertir_direccion_virtual_a_fisica(direccion_virtual, tabla_paginas, 6);
    if (direccion_fisica != -1) {
        printf("Dirección física correspondiente: 0x%lx\n", direccion_fisica);
    }

    // Calcular el tamaño del espacio de direcciones virtuales
    unsigned long tamano_espacio_virtual = calcular_tamano_espacio_virtual(tabla_paginas, 6);
    printf("Tamaño del espacio de direcciones virtuales: %lu bytes\n", tamano_espacio_virtual);

    return 0;
}
