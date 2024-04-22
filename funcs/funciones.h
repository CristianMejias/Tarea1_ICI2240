//Librerias utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "funciones.h"


/* >>>>>>>>>>>>>>>>>>>>>>> FUNCIONES SISTEMA >>>>>>>>>>>>>>>>>>>>>>> */


void limpiarPantalla()
{ 
  system("clear"); 
}


void presioneTeclaParaContinuar()
{
  AMARILLO;
  printf("\nPresione ENTER para continuar...");
  BLANCO;
  limpiarBuffer();
}


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


void limpiarBuffer()
{
  while (getchar() != '\n');
}


void mensajeError()
{
  ROJO;
  printf(" × ERROR - Ingresa un valor valido: ");
  BLANCO;
}


/* >>>>>>>>>>>>>>>>>>>>>>> REGISTRAR PACIENTE >>>>>>>>>>>>>>>>>>>>>>> */


void registrarPaciente(List *pacientes)
{
  tipoPaciente *nuevoPaciente = (tipoPaciente*) malloc(sizeof(tipoPaciente));

  ingresarPaciente(nuevoPaciente);
  //Cambiar comentarios SOLO para hacer pruebas
  //ingresarPacienteRandom(nuevoPaciente);

  formatearNombre(nuevoPaciente);

  nuevoPaciente->prioridad = 0;

  struct tm *temp;
  time(&nuevoPaciente->hora);
  temp = localtime(&nuevoPaciente->hora);
  temp->tm_hour = (temp->tm_hour + 20) % 24;
  nuevoPaciente->hora = mktime(temp);

  list_pushBack(pacientes, nuevoPaciente);
}


int validarEdad()
{
  char edadStr[5];
  int edadNum;

  while (1)
  {
    scanf("%4[^\n]s", edadStr);
    limpiarBuffer();

    if (esNumerica(edadStr))
    {
      edadNum = cadenaNumero(edadStr);
      if (edadNum <= EDADMAXIMA && edadNum > 0)
        return edadNum;
    }
    mensajeError();
  }
}


bool esNumerica(char *cadena)
{
  while (*cadena != '\0')
  {
    if (!isdigit(*cadena))
      return false;
    cadena++;
  }
  return true;
}


int cadenaNumero(char *cadena)
{
  int numero = 0;
  int digito;

  while ((*cadena) != '\0')
  {
    digito = (*cadena) - '0';
    numero = numero * 10 + digito;
    cadena++;
  }
  return numero;
}


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


void formatearNombre(tipoPaciente *paciente)
{
  //problemas con tildes
  aMinusculas(paciente->nombre, paciente->nombreMod);
}


void ingresarPacienteRandom(tipoPaciente *paciente)
{
  CYAN;
  puts(" ... Paciente Random ...");
  BLANCO;

  char nombres[20][MAXNOMBRE] = {
          "Juan\0", "Pedro\0", "Carlos\0", "Luis\0",
          "Javier\0", "Antonio\0", "Miguel\0", "Jose\0",
          "Pablo\0", "Fernando\0","Maria\0", "Ana\0",
          "Laura\0", "Sofia\0", "Elena\0", "Lucia\0",
          "Isabel\0", "Paula\0", "Carmen\0", "Marta\0"};

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

  int aux;
  aux = rand() % 20;
  strcpy(paciente->nombre, nombres[aux]);

  aux = rand() % 100 + 1;
  paciente->edad = aux;

  aux = rand() % 10;
  strcpy(paciente->sintomas, sintomas[aux]);
}


void ingresarPaciente(tipoPaciente *paciente)
{
  printf(" ■ Ingrese el nombre del paciente: ");
  scanf("%29[^\n]s", paciente->nombre);
  limpiarBuffer();

  printf(" ■ Ingrese la edad del paciente: ");
  paciente->edad = validarEdad();

  printf(" ■ Ingrese los síntomas del paciente: ");
  scanf("%99[^\n]s", paciente->sintomas);
  limpiarBuffer();
}


/* >>>>>>>>>>>>>>>>>>>>>>> ASIGNAR PRIORIDAD >>>>>>>>>>>>>>>>>>>>>>> */


void asignarPrioridad(List *listaBaja, List *listaMedia, List *listaAlta)
{
  int prioridad;
  char nombreBuscado[MAXNOMBRE];
  char nombreFormato[MAXNOMBRE];

  printf(" ■ Ingrese nombre de paciente: ");
  scanf("%29[^\n]s", nombreBuscado);
  limpiarBuffer();

  aMinusculas(nombreBuscado, nombreFormato);

  tipoPaciente *paciente = NULL;

  buscarPaciente(listaBaja, &paciente, nombreFormato);
  if (paciente != NULL)
  {
    puts(" ■ Ingrese prioridad");
    printf("   (Baja = 0 | Media = 1 | Alta = 2) : ");

    prioridad = validarEnIntervalo(0,2);
    paciente->prioridad = prioridad;
    insertarEnListaPrioridad(paciente, listaBaja, listaMedia, listaAlta);
  }
  else
  {
    ROJO;
    printf(" × Paciente no encontrado :(\n");
    BLANCO;
    return;
  }
}


void insertarEnListaPrioridad(tipoPaciente *paciente, List *listaBaja, List *listaMedia, List *listaAlta)
{
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


void buscarPaciente(List *listaBaja, tipoPaciente **ptrPaciente, char *nombreBuscado)
{
  *ptrPaciente = list_first(listaBaja);
  while ((*ptrPaciente) != NULL)
  {
    if (strcmp((*ptrPaciente)->nombreMod, nombreBuscado) == 0)
      return;
    (*ptrPaciente) = list_next(listaBaja);
  }
  (*ptrPaciente) = NULL;
}




int compararTiempos(void *dato1, void *dato2)
{
  tipoPaciente *ptr1 = (tipoPaciente *) dato1;
  tipoPaciente *ptr2 = (tipoPaciente *) dato2;
  
  if (ptr1->hora < ptr2->hora)
    return 1;
  return 0;
}


/* >>>>>>>>>>>>>>>>>>>>>>> MOSTRAR LISTA DE ESPERA >>>>>>>>>>>>>>>>>>>>>>> */


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


void mostrarUnaLista(List *lista)
{
  tipoPaciente *pacienteActual = list_first(lista);

  if (pacienteActual == NULL)
  {
    printf("   No hay pacientes en esta prioridad :)\n\n");
    return;
  }

  int i = 0;
  while (pacienteActual != NULL)
  {
    i++;
    printf("   Paciente %i\n", i);
    mostrarUnPaciente(pacienteActual);

    pacienteActual = list_next(lista);
  }
}


void mostrarUnPaciente(tipoPaciente *paciente)
{
  printf("    ¤ Nombre: %s\n", paciente->nombre);
  printf("    ¤ Edad: %d\n", paciente->edad);
  printf("    ¤ Síntomas: %s\n", paciente->sintomas);
  printf("    ¤ Hora: %s\n", ctime(&paciente->hora));
}


/* >>>>>>>>>>>>>>>>>>>>>>> ATENDER PACIENTE >>>>>>>>>>>>>>>>>>>>>>> */


void atenderPaciente(List *listaBaja, List *listaMedia, List *listaAlta)
{
  tipoPaciente *pacienteActual = list_first(listaAlta);
  CYAN;
  printf("   Atendiendo al paciente de mayor prioridad\n\n");
  BLANCO;

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


void mostrarPrioridad(List *listaBaja, List *listaMedia, List *listaAlta)
{
  int prioridad;
  puts(" ■ Ingrese prioridad");
  printf("   (Baja = 0 | Media = 1 | Alta = 2): ");
  prioridad = validarEnIntervalo(0,2);
  
  puts("");
  CYAN;
  printf("   Mostrando pacientes por prioridad: ");

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


int validarEnIntervalo(int limiteInf, int limiteSup)
{
  int num;
  char numStr[2];
  
  while (true)
  {
    scanf("%1[^\n]s", numStr);
    limpiarBuffer();

    if (strcmp(numStr,"0") == 0 || strcmp(numStr,"1") == 0 || strcmp(numStr,"2") == 0);
      num = cadenaNumero(numStr);
    if (num >= limiteInf && num <= limiteSup)
      return num;
    
    mensajeError();
  }
}
