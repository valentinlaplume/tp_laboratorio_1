
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param pFile FILE*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmpleado;
	int idProximo, idMax, flagErrorId;
	int i = 0;
	//------------------------------- BUFFERS
	char bufferId[STR_LEN];
	char bufferNombre[STR_LEN];
	char bufferHsTrabajadas[STR_LEN];
	char bufferSueldo[STR_LEN];

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^,],"
							"%[^,],"
							"%[^,],"
							"%[^\n]\n", bufferId, bufferNombre, bufferHsTrabajadas, bufferSueldo ) == 4)
			{
				pEmpleado = employee_newParametrosStr(bufferId, bufferNombre, bufferHsTrabajadas, bufferSueldo);
				if(pEmpleado != NULL &&
				   !ll_add(pArrayListEmployee, pEmpleado)) // agrego a la lista
				{
					pEmpleado = (Employee*) ll_get(pArrayListEmployee, 0);
					idMax = employee_getId(pEmpleado, &flagErrorId);

					idProximo = atoi(bufferId);

					if(!flagErrorId && idProximo >= idMax)
					{
						idMax = idProximo;
						i++;
					}
				}
				else
				{
					printf("\n\x1b[31m *\x1b[0m Error al validar los datos del empleado en la posicion [%d]",i);
					continue;
				}
			}
		}while(!feof(pFile));
		retorno = idMax;
		printf("\n\n\x1b[92m >\x1b[0m Fueron cargados %d empleados (modo texto)", i);
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo dataBin.csv (modo binario).
 *
 * \param pFile FILE*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmpleado = NULL;
	Employee auxEmpleado;
	int idMax;
	int flag = 0;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			if(fread(&auxEmpleado, sizeof(Employee), 1, pFile) == 1)
			{
				pEmpleado = employee_newParametros(auxEmpleado.id, auxEmpleado.nombre, auxEmpleado.horasTrabajadas, auxEmpleado.sueldo);

				if(!ll_add(pArrayListEmployee, pEmpleado) &&
				  (flag == 0 || auxEmpleado.id > idMax))
				{
					flag = 1;
					idMax = auxEmpleado.id;
				}
			}
		}while(!feof(pFile));
		retorno = idMax;
	}
    return retorno;
}

/** \brief Parsea el ultimo ID
 *
 * \param pFile FILE*
 * \param pArrayListEmployee LinkedList*
 * \return int retorna ultimo ID >= 0 si OK,retorna ID -1 ERROR
 *
 */
int parser_EmployeeUltimoIdFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int ultimoId = -1;
	int bufferID;
	char auxIdStr[STR_LEN];

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			if(fscanf(pFile,"%[^\n]\n", auxIdStr ) == 1)
			{
				if(employee_isValidIdStr(auxIdStr))
				{
					bufferID = atoi(auxIdStr);

					if(bufferID >= 0)
						ultimoId = bufferID;
				}
			}
		}while(!feof(pFile));
		retorno = ultimoId;
	}
    return retorno;
}



