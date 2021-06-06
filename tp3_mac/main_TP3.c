#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main()
{
    int option;
    LinkedList* listaEmpleados = ll_newLinkedList();

	do
	{
		if(!utn_getNumero(&option,
									"\n"
									"\n * ====================== \x1b[93m\x1b[44m MENU PRINCIPAL \x1b[0m\x1b[0m ====================== *"
									"\n | ============================================================== |"
									"\n |  1  -  Cargar los datos de los empleados (modo texto)          |"
									"\n |  2  -  Cargar los datos de los empleados (modo binario)        |"
									"\n |  3  -  Alta de empleado                                        |"
									"\n |  4  -  Modificar datos de empleado                             |"
									"\n |  5  -  Baja de empleado                                        |"
									"\n |  6  -  Listar empleados                                        |"
									"\n |  7  -  Ordenar empleados                                       |"
									"\n |  8  -  Guardar los datos de los empleados (modo texto)         |"
									"\n |  9  -  Guardar los datos de los empleados (modo binario)       |"
									"\n | 10  -  Salir                                                   |"
									"\n * -------------------------------------------------------------- *"
									"\n > Opcion: ",
									"\n * Opcion invalida *\n", 1, 10, 99))
		{
			switch(option)
			{
				case 1: // Cargar los datos de los empleados (modo texto)
					controller_loadFromText("data.csv", listaEmpleados);
				break;
				case 2: // Cargar los datos de los empleados (modo binario)
					controller_loadFromBinary("dataBin.csv", listaEmpleados);
				break;
				case 3: // Alta de empleado
					controller_addEmployee(listaEmpleados);
				break;
				case 4: // Modificar datos de empleado
					controller_editEmployee(listaEmpleados);
				break;
				case 5: // Baja de empleado
					controller_removeEmployee(listaEmpleados);
				break;
				case 6: // Listar empleados
					controller_ListEmployee(listaEmpleados);
				break;
				case 7: // Ordenar empleados
					controller_sortEmployee(listaEmpleados);
				break;
				case 8: // Guardar los datos de los empleados (modo texto)
					controller_saveAsText("data.csv", listaEmpleados);
				break;
				case 9: // Guardar los datos de los empleados (modo binario)
					controller_saveAsBinary("dataBin.csv", listaEmpleados);
				break;
			}
		}
	}while(option != 10);
    return 0;
}
