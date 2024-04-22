#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "../tdas/list.h"
#include <stdbool.h>
#include <time.h>


//Macro que define el tamaño máximo para un nombre, 30 caracteres.
#define MAXNOMBRE 30
//Macro que define el tamaño máximo para una descripción de síntomas, 100 caracteres.
#define MAXSINTOMA 100
//Macro que define la edad máxima permitida, en este caso, 130 años.
#define EDADMAXIMA 130
//Macros que representan las prioridades de baja, media y alta respectivamente.
#define BAJA 0
#define MEDIA 1
#define ALTA 2

//Macros para el cambio de colores del texto en la terminal
#define BLANCO printf("\033[0m")
#define GRIS printf("\033[1;30m")
#define ROJO printf("\033[0;31m")
#define VERDE printf("\033[0;32m")
#define AMARILLO printf("\033[1;43m")
#define CYAN printf("\033[1;36m")

//Estructura utilizada tipoPaciente y sus campos
typedef struct {
  char nombre[MAXNOMBRE];
  char nombreMod[MAXNOMBRE];
  int edad;
  char sintomas[MAXSINTOMA];
  int prioridad;
  time_t hora;
}tipoPaciente;


/* >>>>>>>>>>>>>>>>>>>>>>> FUNCIONES SISTEMA >>>>>>>>>>>>>>>>>>>>>>> */


// Esta función limpia la pantalla de la consola
void limpiarPantalla();

// Esta función espera a que el usuario presione una tecla
void presioneTeclaParaContinuar();

// Esta función muestra el menú principal
void mostrarMenuPrincipal();

// Esta función muestra el submenú, 
// recibe como parámetro un entero que indica la opción
void mostrarSubMenu(int );

// Esta función limpia el buffer para leer sin complicaciones
void limpiarBuffer();

// Esta función muestra un mensaje de error cuando falla alguna validación
void mensajeError();


/* >>>>>>>>>>>>>>>>>>>>>>> REGISTRAR PACIENTE >>>>>>>>>>>>>>>>>>>>>>> */


// Función general que se encarga de registrar un paciente en el sistema
void registrarPaciente(List *);

// Esta función lee el nombre, edad y síntomas de un paciente
void ingresarPaciente(tipoPaciente *);

// Función temporal para pruebas de funcionamiento
void ingresarPacienteRandom(tipoPaciente *);

// Esta función valida que una edad (cadena) sea correcta entre 1 - EDADMAXIMA
int validarEdad();

// Esta función comprueba que una cadena sea numérica
bool esNumerica(char *);

// Esta función convierte una cadena en un número entero
int cadenaNumero(char *);

// Esta función recibe un tipoPaciente, crea una cadena con formato de su nombre
// y lo almacena en la estructura
void formatearNombre(tipoPaciente *);

// Esta función convierte una cadena en minúsculas
void aMinusculas(char *, char *);


/* >>>>>>>>>>>>>>>>>>>>>>> ASIGNAR PRIORIDAD >>>>>>>>>>>>>>>>>>>>>>> */


// Función general que se encarga de asignar una prioridad a un paciente
void asignarPrioridad(List *, List *, List *);

// Búsqueda lineal de un paciente en una lista
void buscarPaciente(List *, tipoPaciente **, char *);

// Esta función compara 2 tiempos tipo time_t
int compararTiempos(void *, void *);

// Esta función inserta un paciente en una lista de prioridad específica
void insertarEnListaPrioridad(tipoPaciente *, List *, List *, List *);


/* >>>>>>>>>>>>>>>>>>>>>>> MOSTRAR LISTA DE ESPERA >>>>>>>>>>>>>>>>>>>>>>> */


// Función general que muestra los pacientes en espera
void mostrarPacientes(List *, List *, List *);

// Esta función muestra los pacientes de una lista
void mostrarUnaLista(List *);

// Esta función muestra los datos de un paciente
void mostrarUnPaciente(tipoPaciente *);


/* >>>>>>>>>>>>>>>>>>>>>>> ATENDER PACIENTE >>>>>>>>>>>>>>>>>>>>>>> */


// Función general que simula la atención de un paciente con la mayor prioridad
void atenderPaciente(List *, List *, List *);


/* >>>>>>>>>>>>>>>>>>>>>>> MOSTRAR PRIORIDAD >>>>>>>>>>>>>>>>>>>>>>> */


// Función general que muestra la lista de espera de una prioridad específica
void mostrarPrioridad(List *, List *, List *);

// Esta función valida que un número ingresado esté en un intervalo específico
int validarEnIntervalo(int , int );

#endif
