/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"
#include "Controller.h"
#include "utn.h"

#define OPCION_SALIR 10

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
									"\n > Eliga opcion: ",
									"\n * Opcion invalida *\n", 1, OPCION_SALIR, 99))
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
				case OPCION_SALIR: // Salir y guardar ultimo ID si fue guardado en archivo
					controller_saveUltimoId("ultimoIdTP3.txt", listaEmpleados);
				break;
			}
		}
	}while(option != OPCION_SALIR);

	startTesting(1);  // ll_newLinkedList
	startTesting(2);  // ll_len
	startTesting(3);  // getNode - test_getNode
	startTesting(4);  // addNode - test_addNode
	startTesting(5);  // ll_add
	startTesting(6);  // ll_get
	startTesting(7);  // ll_set
	startTesting(8);  // ll_remove
	startTesting(9);  // ll_clear
	startTesting(10); // ll_deleteLinkedList
	startTesting(11); // ll_indexOf
	startTesting(12); // ll_isEmpty
	startTesting(13); // ll_push
	startTesting(14); // ll_pop
	startTesting(15); // ll_contains
	startTesting(16); // ll_containsAll
	startTesting(17); // ll_subList
	startTesting(18); // ll_clone
	startTesting(19); // ll_sort

	printf("\n\n\x1b[93m\x1b[44m - TESTING - \x1b[0m\x1b[0m");


    return 0;
}
/*int main(void)
{
	startTesting(1);  // ll_newLinkedList
	startTesting(2);  // ll_len
	startTesting(3);  // getNode - test_getNode
	startTesting(4);  // addNode - test_addNode
	startTesting(5);  // ll_add
	startTesting(6);  // ll_get
	startTesting(7);  // ll_set
	startTesting(8);  // ll_remove
	startTesting(9);  // ll_clear
	startTesting(10); // ll_deleteLinkedList
	startTesting(11); // ll_indexOf
	startTesting(12); // ll_isEmpty
	startTesting(13); // ll_push
	startTesting(14); // ll_pop
	startTesting(15); // ll_contains
	startTesting(16); // ll_containsAll
	startTesting(17); // ll_subList
	startTesting(18); // ll_clone
	startTesting(19); // ll_sort

    return 0;
}
*/
































