//Librerias utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "funciones.h"


/* >>>>>>>>>>>>>>>>>>>>>>> FUNCIONES SISTEMA >>>>>>>>>>>>>>>>>>>>>>> */

// Esta función limpia la pantalla de la consola
void limpiarPantalla()
{ 
  system("clear"); 
}


// Esta función espera a que el usuario presione una tecla
void presioneTeclaParaContinuar()
{
  AMARILLO;
  printf("\nPresione ENTER para continuar...");
  BLANCO;
  limpiarBuffer();
}


// Esta función muestra el menú principal
void mostrarMenuPrincipal()
{
  limpiarPantalla();
  CYAN;
  puts("=========================================");
  puts("     Sistema de Gestión Hospitalaria     ");
  puts("=========================================");
  puts(" ( 1 )  Registrar paciente");
  puts(" ( 2 )  Asignar prioridad a paciente");
  puts(" ( 3 )  Mostrar lista de espera");
  puts(" ( 4 )  Atender al siguiente paciente");
  puts(" ( 5 )  Mostrar pacientes por prioridad");
  puts(" ( 6 )  Salir");
  puts("========================================");
  BLANCO;
}


// Esta función muestra el submenú, 
// recibe como parámetro un entero que indica la opción
void mostrarSubMenu(int opcion)
{
  VERDE;
  puts("");
  puts("=======================================");

  if (opcion == 1){
    puts(" ( 1 ) Registrar paciente");
  }
  else if (opcion == 2){
    puts(" ( 2 ) Asignar prioridad a paciente");
  }
  else if (opcion == 3){
    puts(" ( 3 ) Mostrar lista de espera");
  }
  else if (opcion == 4){
    puts(" ( 4 ) Atender al siguiente paciente");
  }
  else if (opcion == 5){
    puts(" ( 5 ) Mostrar pacientes por prioridad");
  }
  else if (opcion == 6){
    puts(" ( 6 ) Salir del sistema");
  }

  puts("=======================================");
  puts("");
  BLANCO;
}


// Esta función limpia el buffer para leer sin complicaciones
void limpiarBuffer()
{
  while (getchar() != '\n');
}


// Esta función muestra un mensaje de error cuando falla alguna validación
void mensajeError()
{
  ROJO;
  printf(" × ERROR - Ingresa un valor valido: ");
  BLANCO;
}


/* >>>>>>>>>>>>>>>>>>>>>>> REGISTRAR PACIENTE >>>>>>>>>>>>>>>>>>>>>>> */


// Función general que se encarga de registrar un paciente en el sistema
void registrarPaciente(List *pacientes)
{
  //ESTRUCTURA QUE ALMACENA LOS DATOS DE CADA PACIENTE
  tipoPaciente *nuevoPaciente = (tipoPaciente*) malloc(sizeof(tipoPaciente));

  //FUNCION QUE SE ENCARGA DE LEER LOS DATOS
  ingresarPaciente(nuevoPaciente);
  //Cambiar comentarios SOLO para hacer pruebas
  //ingresarPacienteRandom(nuevoPaciente);

  //DAR FORMATO A NOMBRE PARA FUTURAS COMPARACIONES
  formatearNombre(nuevoPaciente);

  nuevoPaciente->prioridad = 0;

  //ALMACENAR LA HORA ACTUAL EN LA ESTRUCTURA
  struct tm *temp;
  time(&nuevoPaciente->hora);
  temp = localtime(&nuevoPaciente->hora);
  temp->tm_hour = (temp->tm_hour + 20) % 24;
  nuevoPaciente->hora = mktime(temp);

  //ALMACENAR PACIENTE EN LA LISTA DE PRIORIDAD BAJA
  list_pushBack(pacientes, nuevoPaciente);
}


// Esta función valida que una edad (cadena) sea correcta entre 1 - EDADMAXIMA
int validarEdad()
{
  //DATOS TEMPORALES PARA ALMACENAR EDAD
  char edadStr[5];
  int edadNum;

  while (1)
  {
    //LEER 4 CARACTERES E IGNORAR EL RESTO
    scanf("%4[^\n]s", edadStr);
    limpiarBuffer();

    //COMPROBAR SI LA CADENA INGRESADA ES NUMERICA
    if (esNumerica(edadStr))
    {
      //VALIDAR QUE EDAD ESTE EN RANGO DEFINIDO
      edadNum = cadenaNumero(edadStr);
      if (edadNum <= EDADMAXIMA && edadNum > 0)
        return edadNum;
    }
    mensajeError();
  }
}


// Esta función comprueba que una cadena sea numérica
bool esNumerica(char *cadena)
{
  //RECORRER TODA LA CADENA
  while (*cadena != '\0')
  {
    COMPROBAR QUE SOLO TENGA DIGITOS
    if (!isdigit(*cadena))
      return false;
    cadena++;
  }
  return true;
}


// Esta función convierte una cadena en un número entero
int cadenaNumero(char *cadena)
{
  int numero = 0;
  int digito;

  //RECORRER TODA LA CADENA
  while ((*cadena) != '\0')
  {
    //ALGEBRA DE CADENAS PARA OBTENER LOS DIGITOS
    digito = (*cadena) - '0';
    numero = numero * 10 + digito;
    cadena++;
  }
  return numero;
}


// Esta función convierte una cadena en minúsculas
void aMinusculas(char *cadena, char *cadenaMod)
{
  int i = 0;
  int k = 0;
  while (cadena[i] != '\0')
  {
    if (isalpha(cadena[i]))
    {
      cadenaMod[k] = tolower(cadena[i]);
      k++;
    }
    i++;
  }
  cadenaMod[k] = '\0';
}


// Esta función recibe un tipoPaciente, crea una cadena con formato de su nombre y lo almacena en la estructura
void formatearNombre(tipoPaciente *paciente)
{
  //problemas con tildes
  aMinusculas(paciente->nombre, paciente->nombreMod);
}


// Función temporal para pruebas de funcionamiento
void ingresarPacienteRandom(tipoPaciente *paciente)
{
  CYAN;
  puts(" ... Paciente Random ...");
  BLANCO;

  //VECTORES NOMBRES AUXILIARES
  char nombres[20][MAXNOMBRE] = {
          "Juan\0", "Pedro\0", "Carlos\0", "Luis\0",
          "Javier\0", "Antonio\0", "Miguel\0", "Jose\0",
          "Pablo\0", "Fernando\0","Maria\0", "Ana\0",
          "Laura\0", "Sofia\0", "Elena\0", "Lucia\0",
          "Isabel\0", "Paula\0", "Carmen\0", "Marta\0"};

  //VECTOR SINTOMAS AUXILIARES
  char sintomas[10][MAXSINTOMA] = {
          "Congestión nasal, Tos\0",
          "Fiebre alta, Dolor de cabeza\0",
          "Dolor abdominal, Vómitos\0",
          "Dificultad para respirar, Sibilancias\0",
          "Dolor al orinar, Necesidad frecuente de orinar\0",
          "Estornudos, Picazón en los ojos\0",
          "Dolor de garganta, Ganglios inflamados\0",
          "Ardor estomacal, Indigestión\0",
          "Reflujo ácido, Dolor en el pecho\0",
          "Tos persistente, Dolor en el pecho al toser\0"};

  srand(time(NULL));

  //VARIABLE AUXILIAR RANDOM
  int aux;
  aux = rand() % 20;
  strcpy(paciente->nombre, nombres[aux]);

  aux = rand() % 100 + 1;
  paciente->edad = aux;

  aux = rand() % 10;
  strcpy(paciente->sintomas, sintomas[aux]);
}


// Esta función lee el nombre, edad y síntomas de un paciente
void ingresarPaciente(tipoPaciente *paciente)
{
  //LEER NOMBRE
  printf(" ■ Ingrese el nombre del paciente: ");
  scanf("%29[^\n]s", paciente->nombre);
  limpiarBuffer();

  //LEER EDAD
  printf(" ■ Ingrese la edad del paciente: ");
  paciente->edad = validarEdad();

  //LEER SINTOMAS
  printf(" ■ Ingrese los síntomas del paciente: ");
  scanf("%99[^\n]s", paciente->sintomas);
  limpiarBuffer();
}


/* >>>>>>>>>>>>>>>>>>>>>>> ASIGNAR PRIORIDAD >>>>>>>>>>>>>>>>>>>>>>> */

// Función general que se encarga de asignar una prioridad a un paciente
void asignarPrioridad(List *listaBaja, List *listaMedia, List *listaAlta)
{
  int prioridad;
  char nombreBuscado[MAXNOMBRE];
  char nombreFormato[MAXNOMBRE];

  //LEER NOMBRE BUSCADO
  printf(" ■ Ingrese nombre de paciente: ");
  scanf("%29[^\n]s", nombreBuscado);
  limpiarBuffer();

  //DAR FORMATO PARA LA CORRECTA COMPARACION
  aMinusculas(nombreBuscado, nombreFormato);

  tipoPaciente *paciente = NULL;

  //BUSCARLO EN LA LISTA DE PRIORIDAD BAJA
  buscarPaciente(listaBaja, &paciente, nombreFormato);
  if (paciente != NULL)
  {
    //LEER PRIORIDAD A ASIGNAR
    puts(" ■ Ingrese prioridad");
    printf("   (Baja = 0 | Media = 1 | Alta = 2) : ");

    //VALIDAR Y ASIGNAR PRIORIDAD
    prioridad = validarEnIntervalo(0,2);
    paciente->prioridad = prioridad;

    //INSERTAR EN LA LISTA CORRESPONDIENTE
    insertarEnListaPrioridad(paciente, listaBaja, listaMedia, listaAlta);
  }
  else
  {
    //MANEJO DE ERROR
    ROJO;
    printf(" × Paciente no encontrado :(\n");
    BLANCO;
    return;
  }
}


// Esta función inserta un paciente en una lista de prioridad específica
void insertarEnListaPrioridad(tipoPaciente *paciente, List *listaBaja, List *listaMedia, List *listaAlta)
{
  //COMPROBAR PRIORIDAD Y INSERTAR A LISTA CORRESPONDIENTE
  //ELIMINAR DE LISTA BAJA SI CORRESPONDE
  if (paciente->prioridad == BAJA)
    return;
  else if (paciente->prioridad == MEDIA)
  {
    list_sortedInsert(listaMedia, paciente, compararTiempos);
    list_popCurrent(listaBaja);
  }
  else if (paciente->prioridad == ALTA)
  {
    list_sortedInsert(listaAlta, paciente, compararTiempos);
    list_popCurrent(listaBaja);
  }
  else
  {
    puts("§_ERROR_ASIGNAR_PRIORIDAD_§");
    exit(EXIT_FAILURE);
  }
  return;
}


// Búsqueda lineal de un paciente en una lista
void buscarPaciente(List *listaBaja, tipoPaciente **ptrPaciente, char *nombreBuscado)
{
  //PUNTERO AUXILIAR PARA RECORRER LA LISTA
  *ptrPaciente = list_first(listaBaja);
  while ((*ptrPaciente) != NULL)
  {
    //COMPARAR NOMBRE
    if (strcmp((*ptrPaciente)->nombreMod, nombreBuscado) == 0)
      return;
    (*ptrPaciente) = list_next(listaBaja);
  }
  (*ptrPaciente) = NULL;
}


// Esta función compara 2 tiempos tipo time_t
int compararTiempos(void *dato1, void *dato2)
{
  //CASTING A TIPOPERSONA
  tipoPaciente *ptr1 = (tipoPaciente *) dato1;
  tipoPaciente *ptr2 = (tipoPaciente *) dato2;

  //COMPARACION DE TIEMPOS
  if (ptr1->hora < ptr2->hora)
    return 1;
  return 0;
}


/* >>>>>>>>>>>>>>>>>>>>>>> MOSTRAR LISTA DE ESPERA >>>>>>>>>>>>>>>>>>>>>>> */

// Función general que muestra los pacientes en espera
void mostrarPacientes(List *listaBaja, List *listaMedia , List *listaAlta)
{
  CYAN;
  puts("   Lista prioridad Alta");
  puts("   ====================");
  BLANCO;
  mostrarUnaLista(listaAlta);

  CYAN;
  puts("   Lista prioridad Media");
  puts("   ====================");
  BLANCO;
  mostrarUnaLista(listaMedia);

  CYAN;
  puts("   Lista prioridad Baja");
  puts("   ====================");
  BLANCO;
  mostrarUnaLista(listaBaja);
}


// Esta función muestra los pacientes de una lista
void mostrarUnaLista(List *lista)
{
  tipoPaciente *pacienteActual = list_first(lista);

  //COMPROBAR QUE EXISTAN PACIENTES
  if (pacienteActual == NULL)
  {
    printf("   No hay pacientes en esta prioridad :)\n\n");
    return;
  }

  //MOSTRAR CADA PACIENTE DE LA LISTA
  int i = 0;
  while (pacienteActual != NULL)
  {
    i++;
    printf("   Paciente %i\n", i);
    mostrarUnPaciente(pacienteActual);

    pacienteActual = list_next(lista);
  }
}


// Esta función muestra los datos de un paciente
void mostrarUnPaciente(tipoPaciente *paciente)
{
  printf("    ¤ Nombre: %s\n", paciente->nombre);
  printf("    ¤ Edad: %d\n", paciente->edad);
  printf("    ¤ Síntomas: %s\n", paciente->sintomas);
  printf("    ¤ Hora: %s\n", ctime(&paciente->hora));
}


/* >>>>>>>>>>>>>>>>>>>>>>> ATENDER PACIENTE >>>>>>>>>>>>>>>>>>>>>>> */

// Función general que simula la atención de un paciente con la mayor prioridad
void atenderPaciente(List *listaBaja, List *listaMedia, List *listaAlta)
{
  tipoPaciente *pacienteActual = list_first(listaAlta);
  CYAN;
  printf("   Atendiendo al paciente de mayor prioridad\n\n");
  BLANCO;

  //RECORRE CADA LISTA DESDE ALTA A BAJA
  if (pacienteActual != NULL)
  {
    printf("   Paciente en prioridad ALTA\n");
    mostrarUnPaciente(pacienteActual);
    list_popCurrent(listaAlta);
  }
  else
  {
    pacienteActual = list_first(listaMedia);
    if (pacienteActual != NULL)
    {
      printf("   Paciente en prioridad MEDIA\n");
      mostrarUnPaciente(pacienteActual);
      list_popCurrent(listaMedia);
    }
    else
    {
      pacienteActual = list_first(listaBaja);
      if (pacienteActual != NULL)
      {
        printf("   Paciente en prioridad BAJA\n");
        mostrarUnPaciente(pacienteActual);
        list_popCurrent(listaBaja);
      }
      else
      {
        puts("   ¤ No hay pacientes en espera :)");
        return;
      }
    }
  }
  return;
}


/* >>>>>>>>>>>>>>>>>>>>>>> MOSTRAR PRIORIDAD >>>>>>>>>>>>>>>>>>>>>>> */

// Función general que muestra la lista de espera de una prioridad específica
void mostrarPrioridad(List *listaBaja, List *listaMedia, List *listaAlta)
{
  //LECTURA DE LA PRIORIDAD A MOSTRAR
  int prioridad;
  puts(" ■ Ingrese prioridad");
  printf("   (Baja = 0 | Media = 1 | Alta = 2): ");
  prioridad = validarEnIntervalo(0,2);
  
  puts("");
  CYAN;
  printf("   Mostrando pacientes por prioridad: ");

  //MOSTRAR LA LISTA CORRESPONDIENTE
  if (prioridad == BAJA)
  {
    printf("BAJA\n\n");
    BLANCO;
    mostrarUnaLista(listaBaja);
  }
  else if (prioridad == MEDIA)
  {
    printf("MEDIA\n\n");
    BLANCO;
    mostrarUnaLista(listaMedia);
  }
  else
  {
    printf("ALTA\n\n");
    BLANCO;
    mostrarUnaLista(listaAlta);
  }
}


// Esta función valida que un número ingresado esté en un intervalo específico
int validarEnIntervalo(int limiteInf, int limiteSup)
{
  int num;
  char numStr[2];
  
  while (true)
  {
    LECTURA DE CADENA
    scanf("%1[^\n]s", numStr);
    limpiarBuffer();

    //COMPARA SI ES UNA CADENA VALIDA
    if (strcmp(numStr,"0") == 0 || strcmp(numStr,"1") == 0 || strcmp(numStr,"2") == 0);
      num = cadenaNumero(numStr);
    //VERIFICA QUE ESTA EN EL INTERVALO
    if (num >= limiteInf && num <= limiteSup)
      return num;
    
    mensajeError();
  }
}
