/*
TAREA N°1 - ALGORITMO Y ESTRUCTURA DE DATOS
AUTOR: Felipe Ochoa
NRC = 8148
Docente a cargo: Alvaro Sanchez Colmenares
Fecha de entrega: 29/08/2025


REGLAS: Cada infracción vale 100 dolares.
Si un vehiculo tiene k infracciones, paga 100 * k
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>


#define MAX_REGISTROS 1000 /* Definición del máximo de registros */
#define MAX_MATRICULA 32 /* Definición del máximo de caracteres en una matrícula */
#define MULTA_BASE 100.0 /* Definición del valor base de la multa */

/* leerArchivo: recibe el nombre del archivo de texto y el arreglo vacío, retorna la cantidad de datos almacenados en el arreglo.*/
int leerArchivo(const char *nombre, char patentes[][MAX_MATRICULA]) {
    FILE *f;
    char linea[256];
    int n = 0;
    size_t len;

    f = fopen(nombre, "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'\n", nombre);
        return 0;
    }

    while (n < MAX_REGISTROS && fgets(linea, sizeof(linea), f)) {
        len = strcspn(linea, "\r\n");
        linea[len] = '\0';

        /* Guardar en el arreglo de patentes */
        strncpy(patentes[n], linea, MAX_MATRICULA - 1);
        patentes[n][MAX_MATRICULA - 1] = '\0';
        n++;
    }

    fclose(f);
    return n;
}

/*
ImprimirArreglo
Propósito: Imprime el contenido del arreglo de patentes y la cantidad de infracciones y multa correspondiente.
Parámetros: El arreglo de patentes y la cantidad de datos en el arreglo.
*/

void imprimirArreglo(char patentes[][MAX_MATRICULA], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("[%03d] %s\n", i, patentes[i]);
    }
}


/*
construirFrecuencias
Propósito: Construye un arreglo de frecuencias a partir del arreglo de patentes.
Parámetros: El arreglo de patentes, la cantidad de datos en el arreglo, el arreglo de frecuencias y el arreglo de patentes únicas.
Retorna: La cantidad de patentes únicas encontradas (k).
*/

static int construirFrecuencias(char patentes[][MAX_MATRICULA], int n, char unicas[][MAX_MATRICULA], int conteos[]) {
    int i, j, k = 0;
    int encontrada;

    for (i = 0; i < n; i++) {
        encontrada = 0;
        for (j = 0; j < k; j++) {
            if (strcmp(patentes[i], unicas[j]) == 0) {
                conteos[j]++;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strncpy(unicas[k], patentes[i], MAX_MATRICULA - 1);
            unicas[k][MAX_MATRICULA - 1] = '\0';
            conteos[k] = 1;
            k++;
        }
    }
    return k;
}


/* 
visualizarCantidadMultasPorPatente
Propósito: Imprime la cantidad de infracciones y multa correspondiente por cada patente única.
Parámetros: El arreglo de patentes únicas, el arreglo de frecuencias y la cantidad de patentes únicas.
Retorna: (void)
*/

void visualizarCantidadMultasPorPatente(char patentes[][MAX_MATRICULA], int n) {
    char unicas[MAX_REGISTROS][MAX_MATRICULA];
    int conteos[MAX_REGISTROS];
    int i, k;

    k = construirFrecuencias(patentes, n, unicas, conteos);

    printf("Patente                Cantidad de multas\n");
    printf("-----------------------------------------\n");

    for (i = 0; i < k; i++){
        printf("%-20s %7d\n", unicas[i], conteos[i]);
    }
}


/*
  calcularVisualizarMontoMultas
  Propósito:
    Calcular el monto total a recaudar y mostrar el detalle por patente.
  Parámetros:
    - patentes: arreglo de entrada
    - n: cantidad de elementos
  Retorno:
    - Monto total (double)
*/

double calcularVisualizarMontoMultas(char patentes[][MAX_MATRICULA], int n) {
    char unicas[MAX_REGISTROS][MAX_MATRICULA];
    int conteos[MAX_REGISTROS];
    int i, k;
    double total = 0.0, subtotal;

    k = construirFrecuencias(patentes, n, unicas, conteos);

 printf("Detalle de cobro por patente:\n");
    printf("Patente                Cant.   Subtotal ($)\n");
    printf("-------------------------------------------\n");
    for (i = 0; i < k; i++) {
        subtotal = MULTA_BASE * conteos[i];
        printf("%-20s %5d   %12.2f\n", unicas[i], conteos[i], subtotal);
        total += subtotal;
    }
    printf("-------------------------------------------\n");
    printf("TOTAL DE MULTAS:                %12.2f\n", total);

    return total;
}


/* MAIN */

int main(void) {
    char archivo[256];
    char patentes[MAX_REGISTROS][MAX_MATRICULA];
    int n;
    double total;

    printf("Ingrese el nombre del archivo de texto: ");
    if (scanf("%255s", archivo) != 1){
        printf("Error al leer el nombre del archivo.\n");
        return 1;
    }

    n = leerArchivo(archivo, patentes);
    if (n <= 0) {
        printf("No se leyeron datos del archivo.\n");
        return 1;
    }

    printf("\n Arreglo cargado (%d registros)\n", n);
    imprimirArreglo(patentes, n);

    printf("\n Cantidad de multas por patente\n");
    visualizarCantidadMultasPorPatente(patentes, n);

    printf("\n Monto total de multas\n");
    total = calcularVisualizarMontoMultas(patentes, n);

    (void)total; 
    getch();
    return 0;


}

