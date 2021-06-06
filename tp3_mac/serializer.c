/*
 * serializer.c
 *
 *  Created on: 28 may. 2021
 *      Author: valentinlaplume
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "serializer.h"

int serializer_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i, lenLinkedList;
	Employee* pEmpleado;
	int idAux, hsTrabajadasAux, sueldoAux; 	//---AUXILIARES
	char* nombreAux = NULL;
	int flagId, flagHs, flagSueldo, flagNombre; //--- FLAGS ERRORES

	lenLinkedList = ll_len(pArrayListEmployee);
	if(lenLinkedList > 0)
	{
		fprintf(pFile,"id,nombre,horasTrabajadas,sueldo\n");
		for(i=0; i<lenLinkedList; i++)
		{
			pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
			idAux = employee_getId(pEmpleado, &flagId);
			nombreAux = employee_getNombre(pEmpleado, &flagNombre);
			hsTrabajadasAux =  employee_getHorasTrabajadas(pEmpleado, &flagHs);
			sueldoAux = employee_getSueldo(pEmpleado, &flagSueldo);

			if(!flagId && !flagHs && !flagSueldo && !flagNombre)
			{
				fprintf(pFile,"%d,%s,%d,%d\n",idAux, nombreAux, hsTrabajadasAux, sueldoAux);
			}
		}
		retorno = 0;
	}
	return retorno;
}
int serializer_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	Employee* pEmpleado;
	int retorno = -1;
	int lenLinkedList, i;

	lenLinkedList = ll_len(pArrayListEmployee);
	if(lenLinkedList > 0)
	{
		for(i=0; i<lenLinkedList; i++)
		{
			pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);
			fwrite(pEmpleado, sizeof(Employee), 1, pFile);
		}
		retorno = 0;
	}
	return retorno;
}
