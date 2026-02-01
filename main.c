#include <stdio.h>

typedef struct {
    int cod;
    int npa;
    int npt;
    int tpa;
    int tpt;
    int peso;
    int hora;
    char placa[10];
    int tipo_ferry;
} TVehiculo;

int main() {
    int orden[3];
    TVehiculo colaExpress[100];
    TVehiculo colaTradicional[100];
    int contExpress = 0;
    int contTradicional = 0;

    FILE *entrada = fopen("proy1.in", "r");
    if (entrada == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return 1;
    }

    // 1. Leer el orden inicial [cite: 131, 146]
    fscanf(entrada, "%d %d %d", &orden[0], &orden[1], &orden[2]);

    // 2. Bucle para leer todos los vehículos hasta el final del archivo [cite: 116]
    TVehiculo v_aux;
    // El fscanf debe seguir el orden: Cod, NPa, NPt, tpa, tpt, P, Hr, ID, f [cite: 117]
    while (fscanf(entrada, "%d %d %d %d %d %d %d %s %d", 
           &v_aux.cod, &v_aux.npa, &v_aux.npt, &v_aux.tpa, 
           &v_aux.tpt, &v_aux.peso, &v_aux.hora, v_aux.placa, 
           &v_aux.tipo_ferry) != EOF) {

        // 3. Clasificación según el tipo de ferry (f) [cite: 130]
        if (v_aux.tipo_ferry == 0) {
            colaExpress[contExpress] = v_aux;
            contExpress++;
        } else {
            colaTradicional[contTradicional] = v_aux;
            contTradicional++;
        }
    }

    fclose(entrada);

    // --- PRUEBA DE CONTROL ---
    printf("Vehiculos para Express: %d\n", contExpress);
    printf("Vehiculos para Tradicional: %d\n", contTradicional);

    return 0;
}