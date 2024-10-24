#include <stdio.h>
#include <math.h>


#define BITS_DIRECCION_VIRTUAL 36
#define TAMANIO_PAGINA_KB 8
#define BITS_OFFSET_PAGINA 13 
#define TLB_HIT_RATE 0.90
#define TLB_ACCESS_TIME_NS 8
#define MEM_ACCESS_TIME_NS 70

void descomponer_direccion(unsigned long direccion_virtual) {
    unsigned long nivel1, nivel2, nivel3, offset;
    
    // Extraemos los campos de la dirección virtual
    offset = direccion_virtual & ((1 << BITS_OFFSET_PAGINA) - 1); 
    nivel3 = (direccion_virtual >> BITS_OFFSET_PAGINA) & ((1 << 7) - 1);
    nivel2 = (direccion_virtual >> (BITS_OFFSET_PAGINA + 7)) & ((1 << 8) - 1);
    nivel1 = (direccion_virtual >> (BITS_OFFSET_PAGINA + 7 + 8)) & ((1 << 8) - 1); 


    
    printf("Dirección Virtual: 0x%lx\n", direccion_virtual);
    printf("Nivel 1: 0x%lx, Nivel 2: 0x%lx, Nivel 3: 0x%lx, Offset: 0x%lx\n", nivel1, nivel2, nivel3, offset);
}

double calcular_tiempo_acceso_memoria() {
    double tiempo_acceso_con_tlb = TLB_ACCESS_TIME_NS + MEM_ACCESS_TIME_NS; 
    double tiempo_acceso_sin_tlb = TLB_ACCESS_TIME_NS + (3 * MEM_ACCESS_TIME_NS);
    

    double tiempo_medio = (TLB_HIT_RATE * tiempo_acceso_con_tlb) + 
                          ((1 - TLB_HIT_RATE) * tiempo_acceso_sin_tlb);
    
    return tiempo_medio;
}

int main() {
    unsigned long direccion_virtual;

    // Ejemplo de dirección virtual de 36 bits
    direccion_virtual = 0x123456789;

    // Descomponemos la dirección
    descomponer_direccion(direccion_virtual);

    // Calculamos y mostramos el tiempo de acceso promedio
    double tiempo_acceso_medio = calcular_tiempo_acceso_memoria();
    printf("Tiempo promedio de acceso a memoria: %.2f ns\n", tiempo_acceso_medio);

    return 0;
}
