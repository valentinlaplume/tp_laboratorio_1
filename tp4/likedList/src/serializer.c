
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"
#include "Employee.h"
#include "serializer.h"

/** \brief Escribe los datos de los empleados al archivo data.csv (modo texto).
 *
 * \param pFile FILE*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
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
/** \brief Escribe los datos de los empleados al archivo dataBin.csv (modo binario).
 *
 * \param pFile FILE*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
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

/** \brief Escribe el ultimo ID de los empleados al archivo ultimoIdTP3.txt (modo texto).
 *
 * \param pFile FILE*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int serializer_IdFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i, lenLinkedList, idAux, flagId, idMaximo;
	Employee* pEmpleado;

	lenLinkedList = ll_len(pArrayListEmployee);
	if(pFile != NULL && pArrayListEmployee != NULL && lenLinkedList > 0)
	{
		for(i=0; i<lenLinkedList; i++)
		{
			pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
			idAux = employee_getId(pEmpleado, &flagId);

			if(!flagId)
			{
				if( (i == 0) || (idAux > idMaximo) )
					idMaximo = idAux;
			}
		}

		fprintf(pFile,"%d\n",idMaximo); // GUARDO ULTIMO ID
		retorno = 0;
	}
	return retorno;
}
