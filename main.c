#include "tdas/list.h"
#include "funcs/funciones.h"

int main() {
  char opcion;
  List *pacientesBaja = list_create();
  List *pacientesMedia = list_create();
  List *pacientesAlta = list_create();

  do {
    mostrarMenuPrincipal();
    puts("");
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);
    limpiarBuffer();

    switch (opcion) {
    case '1':
      mostrarSubMenu(1);
      registrarPaciente(pacientesBaja);
      break;
    case '2':
      mostrarSubMenu(2);
      asignarPrioridad(pacientesBaja, pacientesMedia, pacientesAlta);
      break;
    case '3':
      mostrarSubMenu(3);
      mostrarPacientes(pacientesBaja, pacientesMedia, pacientesAlta);
      break;
    case '4':
      mostrarSubMenu(4);
      atenderPaciente(pacientesBaja, pacientesMedia, pacientesAlta);
      break;
    case '5':
      mostrarSubMenu(5);
      mostrarPrioridad(pacientesBaja, pacientesMedia, pacientesAlta);
      break;
    case '6':
      mostrarSubMenu(6);
      CYAN;
      puts("Saliendo del sistema de gestión hospitalaria...");
      BLANCO;
      break;
    default:
      ROJO;
      puts("");
      puts("ø Opción no válida ø");
      BLANCO;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  list_clean(pacientesBaja);

  return 0;
}
