
# Tarea 1 | Estructura de datos | ICI2240 - 1
# Sistema de Gestión de Pacientes en Hospital

## Descripción del Programa
Este sistema permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera, y más. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.


## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/CristianMejias/Tarea1_ICI2240.git`
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Done" en la opción de comandos de compilación
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad.
- Ver la lista de los pacientes según su prioridad.
- Salir del sistema
- Validaciones para evitar errores de ingreso

### Problemas conocidos:

- Problemas al manejar nombres con tildes
- Problemas al manejar cadenas vacias
- Si 2 pacientes tienen el mismo nombre el programa le asignara la prioridad al primero que encuentre
- ~Problemas al interactuar ciertas funciones con la función "presioneTeclaParaContinuar()"~
- ~Error (Bucle infinito) si el usuario ingresa un caracter no valido durante la opción de mostrar una única lista de prioridad~
- ~Hora configurada en horatio GMT 0~

### A mejorar:

- Permitir almacenar en un archivo los usuarios registrados
- Permitir la edición de los datos de los pacientes ya ingresados
- Una lista rapida con el nombre de los pacientes registrado para facilitar la asignacion de prioridad


## Ejemplo de uso

**Paso 0: Interfaz**

- Al ejecutar el programa se mostrara una interfaz con las 6 opciones.
- El usuario debe ingresar una de las 6 opciones
- En caso de no ingresar una opción valida el programa dará un aviso y volverá a ejecutar el menú
- Ejemplo:
	````
	=========================================
	     Sistema de Gestión Hospitalaria 
	=========================================
	 ( 1 )  Registrar paciente");
	 ( 2 )  Asignar prioridad a paciente
	 ( 3 )  Mostrar lista de espera
	 ( 4 )  Atender al siguiente paciente
	 ( 5 )  Mostrar pacientes por prioridad
	 ( 6 )  Salir
	========================================"
	````

**Paso 1: Registrar un Nuevo Paciente** 

- El usuario ingresa la opcion 1
- Se comienza registrando los nuevos pacientes que acaban de llegar al hospital.
- Se piden 3 datos por paciente
  - Nombre $\rightarrow$ Hasta 29 caracteres, se almacena su nombre y una cadena auxiliar con un formato especifico
  - Edad $\rightarrow$ Se comprueba que sea una edad valida, entre 1 y 130
  - Síntomas $\rightarrow$ Hasta 99 caracteres

- Ejemplo 1
  ````
  Opcion seleccionada: 1
  Registrar Paciente
  
  Ingrese el nombre del paciente: Juan
  Ingrese la edad del paciente : 33
  Ingrese el sintoma del paciente : Congestión nasal, Tos
  ````
  - El sistema registra a Juan con una prioridad inicial "Bajo", guarda la hora actual de registro y una cadena con un formato especifico de su nombre
  - La prioridad inicial puede ser ajustada más tarde basada en una evaluación médica más detallada.

- Ejemplo 2
  ```
  Opcion seleccionada: 1
  Registrar Paciente
  
  Ingrese el nombre del paciente: Marta
  Ingrese la edad del paciente : 22
  Ingrese el sintoma del paciente : Dolor de garganta, Ganglios inflamados
  ```
  - El sistema registra a Marta con una prioridad inicial "Bajo", guarda la hora actual de registro y una cadena con un formato especifico de su nombre
  - La prioridad inicial puede ser ajustada más tarde basada en una evaluación médica más detallada.


**Paso 2: Asignar Prioridad a un Paciente**
- El usuario ingresa la opción 2
- Tras una evaluación inicial, el médico determina que el estado de juan requiere atención prioritaria.
- Se incluye una verificación que permite al usuario cometer errores de mayúsculas y minúsculas
- Se incluye una validación para ingresar un numero entre 0 y 2
- Ejemplo
	````
	Opción seleccionada: 2
	Asignar Prioridad
	
	Asignar prioridad a paciente
	Ingrese el nombre del paciente para asignar prioridad : JuAn
	Ingrese la nueva prioridad del paciente (0 = BAJA , 1 = MEDIA , 2 = ALTA) = 2
	````
	- El sistema actualiza la prioridad de Juan a "Alto", asegurando que será uno de las próximos pacientes en ser atendido.


**Paso 3: Ver la Lista de Espera**
- El usuario ingresa la opción 3
- El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.
- Ejemplo

	````
	Opción seleccionada: 3
	Mostrar lista de espera
	
	Lista prioridad Alta
	====================
	Paciente 1
	  ¤ Nombre: Juan
	  ¤ Edad: 33
	  ¤ Síntomas: Congestión nasal, Tos
	  ¤ Hora: Sun Apr 21 05:11:39 2024

	Lista prioridad Media
	====================
	No hay pacientes en esta prioridad :)

	Lista prioridad Baja
	====================
	Paciente 1
	  ¤ Nombre: Marta
	  ¤ Edad: 22
	  ¤ Síntomas: Dolor de garganta, Ganglios inflamados
	  ¤ Hora: Sun Apr 21 05:12:56 2024
	````
	- La lista muestra a Juan en la parte superior y a Marte en la parte inferior, indicando la prioridad alta y baja respectivamente


**Paso 4: Atender al Siguiente Paciente**
- El usuario ingresa la opción 4
- Ejemplo
	````
	Opción seleccionada: 4
	Atender al siguiente paciente
	
	Atendiendo al paciente con mayor prioridad
	Paciente prioridad ALTA
		¤ Nombre: Juan
		¤ Edad: 33
		¤ Síntomas: Congestión nasal, Tos
		¤ Hora: Sun Apr 21 05:11:39 2024
	````
  - Juan es llamado para ser atendido basándose en su prioridad y es eliminado de la lista de espera respectiva


**Paso 5: Mostrar pacientes por prioridad**
- El usuario ingresa la opción 5
- El usuario ingresa una prioridad y el programa le mostrara una lista con todos los pacientes en esa prioridad junto con sus datos
- Se incluye una validación para ingresar un numero entre 0 y 2
- Ejemplo
	````
	Opción seleccionada: 5
	Mostrar pacientes por prioridad
	
	Ingrese la prioridad del paciente 
	(0 = BAJA , 1 = MEDIA , 2 = ALTA): 0
	
	Mostrando pacientes por prioridad:  BAJA
	
   Paciente 1
    ¤ Nombre: Marta
    ¤ Edad: 22
	¤ Síntomas: Dolor de garganta, Ganglios inflamados
	¤ Hora: Sun Apr 21 05:12:56 2024
	````
	- El sistema muestra a Marta como la siguiente en ser atendida con prioridad Baja

**Paso 5: Salir**
- El usuario ingresa la opción 6
- Se libera la memoria y cierra el programa
- Ejemplo
	````
	Opción seleccionada: 6
	Salir
	
	Fin del programa.
	````
