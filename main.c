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

typedef struct {
    char nombre[30];
    int tipo;          // 0: Express, 1: Tradicional
    int cap_v;         // Capacidad vehiculos (16, 20 o 18)
    int cap_p;         // Capacidad pasajeros (50, 70 o 60)
    float peso_max;    // 60.0 o 80.0 Toneladas
    int tiempo_viaje;  // <--- ¡NUEVO! (35 o 65 min)
    
    // Variables de control de la carga actual (se reinician en cada viaje)
    int v_actuales;
    int p_actuales;
    float peso_actual;
    
    int estado;        // 1: Carga, 2: Viaje, 3: Espera
    int tiempo_restante_viaje; // Opcional: para saber cuánto le falta para volver
} TFerry;

int main() {
    int orden[3];
    int contExpress = 0;
    int contTradicional = 0;
    TVehiculo colaExpress[100];
    TVehiculo colaTradicional[100];

    // Inicialización manual de los 3 ferrys
    TFerry flota[3] = {
        // Nombre, Tipo, CV, CP, P_Max, T_Viaje, V_Act, P_Act, Peso_Act, Estado
        {"Lilia Concepcion", 0, 16, 50, 60.0, 35, 0, 0, 0.0, 3},
        {"La Isabela",       1, 20, 70, 80.0, 65, 0, 0, 0.0, 3},
        {"La Margariteña",   1, 18, 60, 80.0, 65, 0, 0, 0.0, 3}
    };

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

        //Comprobando leectura de datos.
        //printf("%d %d %d %d %d %d %d %s %d \n", v_aux.cod, v_aux.npa, v_aux.npt, v_aux.tpa, v_aux.tpt, v_aux.peso, v_aux.hora, v_aux.placa, v_aux.tipo_ferry);

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