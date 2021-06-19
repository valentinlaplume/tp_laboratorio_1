
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "serializer.h"
#include "utn.h"
#include "laplume.h"

static int idMaxStatic = 0;
static int flagYaCargueArchivo = 0;
static int flagYaGuardeArchivo = 0;

static Employee* buscarPorId(LinkedList* pArrayListEmployee,int idABuscar);
static Employee* subMenuEdit(LinkedList* pArrayListEmployee);
static int bajaEmpleado(LinkedList* pArrayListEmployee);
static int preguntarCargarArchivo(int flagAbriElArchivo);
int controller_ListEmployee(LinkedList* pArrayListEmployee);

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int [-1] si path == NULL o pArrayListEmployee == NULL, 0 si OK
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;
	int respuestaAbrirArchivo;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			respuestaAbrirArchivo = preguntarCargarArchivo(flagYaCargueArchivo);
			if(!respuestaAbrirArchivo || !flagYaCargueArchivo)
			{
				idMaxStatic = parser_EmployeeFromText(pFile, pArrayListEmployee);
				if(idMaxStatic >= 0)
				{
					printf("\n\x1b[92m >\x1b[0m Los datos de los empleados fueron cargados correctamente del archivo %s"
							"\n\x1b[92m >\x1b[0m El ID maximo es %d, proximo ID %d\n", path, idMaxStatic, idMaxStatic+1);
					idMaxStatic++;
					flagYaCargueArchivo = 1;
					retorno = 0;
				}
				else
					printf("\n\x1b[31m *\x1b[0m Hubo un error al cargar los datos de los empleados del archivo %s", path);

				fclose(pFile);
			}
		}
	}
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo dataBin.csv (modo binario).
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;
	int respuestaAbrirArchivo;

	if(path != NULL)
	{
		pFile = fopen(path,"rb");
		if(pFile != NULL )
		{
			respuestaAbrirArchivo = preguntarCargarArchivo(flagYaCargueArchivo);
			if(!respuestaAbrirArchivo || !flagYaCargueArchivo)
			{
				idMaxStatic = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
				if(idMaxStatic >= 0)
				{
					printf("\n\x1b[92m >\x1b[0m Los datos de los empleados fueron cargados correctamente del archivo %s"
							"\n\x1b[92m >\x1b[0m El ID maximo es %d, el proximo es [ID %d]\n", path, idMaxStatic, idMaxStatic+1);
					idMaxStatic++;
					flagYaCargueArchivo = 1;
					retorno = 0;
				}
				else
					printf("\n\x1b[31m *\x1b[0m Hubo un error al cargar los datos de los empleados del archivo %s", path);
			}
			fclose(pFile);
		}
	}
	return retorno;
}
/** \brief Carga el ultimo ID del empleado
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int [-1] si path == NULL o pArrayListEmployee == NULL, 0 si OK
 */
int controller_loadUltimoIDFromText(char* path, LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "r");
		if(pFile != NULL)
		{
			idMaxStatic = parser_EmployeeUltimoIdFromText(pFile, pArrayListEmployee);
			if(idMaxStatic >= 0)
			{
				idMaxStatic++;
				retorno = 0;
			}
			fclose(pFile);
		}
	}
    return retorno;
}
/** \brief Alta de empleados
 *
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmpleado;

	if(flagYaCargueArchivo == 0) // si no cargué archivo, entonces cargo el ultimo id para comenzar desde allí
		controller_loadUltimoIDFromText("ultimoIdTP3.txt", pArrayListEmployee);

		pEmpleado = employee_alta(&idMaxStatic);
		if(pEmpleado != NULL &&
		   !ll_add(pArrayListEmployee, pEmpleado) &&
		   !employee_mostrarEmpleado(pEmpleado))
		{
			printf("\n   ------------------------------------------------------------------------------------  "
					"\n\x1b[92m >\x1b[0m Alta del empleado realizada con exito");
			retorno = 0;
		}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmpleadoModificado;

	if(!controller_ListEmployee(pArrayListEmployee))
	{
		pEmpleadoModificado = subMenuEdit(pArrayListEmployee);
		if(pEmpleadoModificado != NULL)
		{
			employee_mostrarEmpleado(pEmpleadoModificado);
			printf("\n\x1b[92m >\x1b[0m Modificacion del empleado con exito");
			retorno = 0;
		}
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int retornoBaja;

	if(!controller_ListEmployee(pArrayListEmployee))
	{
		retornoBaja = bajaEmpleado(pArrayListEmployee);
		if(retornoBaja == 0)
		{
			printf("\n\x1b[92m >\x1b[0m Baja del empleado con exito");
			retorno = 0;
		}
		else
		{
			if(retornoBaja == -2)
			{
				printf("\n\x1b[31m >\x1b[0m Baja del empleado cancelada");
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief Listar empleados
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i, lenLinkedList;
	Employee* pEmployee;

	lenLinkedList = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL && lenLinkedList > 0)
	{
		for(i=0; i<lenLinkedList; i++)
		{
			pEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			if(!employee_mostrarEmpleado(pEmployee))
			{
				retorno = 0;
			}
		}
		printf("\n\x1b[34m   --------------------------------------------------------------------------------------------  \x1b[0m"
				"\n\x1b[92m >\x1b[0m Listado de Empleados");
	}
	else
		printf("\n\x1b[31m *\x1b[0m Error, no hay empleados cargados");
	return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(!ll_sort(pArrayListEmployee, employee_compararPorNombre, 1))
	{
		if(!controller_ListEmployee(pArrayListEmployee))
		{
			printf(" ordenado por nombre [A - Z]");
			retorno = 0;
		}
	}
	else
		printf("\n\x1b[31m *\x1b[0m Debe haber al menos 2 empleados cargados para poder ordenarlos");

	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;
	int lenLinkedList;
	lenLinkedList = ll_len(pArrayListEmployee);

	if(path != NULL && lenLinkedList > 0)
	{
		pFile = fopen(path, "w");
		if(pFile != NULL)
		{
			if(!serializer_EmployeeFromText(pFile, pArrayListEmployee))
			{
				flagYaGuardeArchivo = 1;
				printf("\n\x1b[92m >\x1b[0m  Los datos fueron guardados correctamente en el archivo %s (modo texto)",path);
				retorno = 0;
			}
			fclose(pFile);
		}
	}
	else
		printf("\n\x1b[31m *\x1b[0m Error, hay %d empleados para ser guardados", lenLinkedList);

	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si ok, -1 error
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;
	int lenLinkedList;
	lenLinkedList = ll_len(pArrayListEmployee);

	if(path != NULL && lenLinkedList > 0)
	{
		pFile = fopen(path,"w+b");
		if(pFile != NULL)
		{
			if(!serializer_EmployeeFromBinary(pFile, pArrayListEmployee))
			{
				flagYaGuardeArchivo = 1;
				printf("\n\x1b[92m >\x1b[0m  Los datos fueron guardados correctamente en el archivo %s (modo binario)",path);
				retorno = 0;
			}
			fclose(pFile);
		}
	}
	else
		printf("\n\x1b[31m *\x1b[0m Error, hay %d empleados por guardar", lenLinkedList);
	return retorno;
}

/** \brief Guarda el ultimo ID de los empleados
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int 0 si OK, -1 ERROR
 */
int controller_saveUltimoId(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pFile;

	if(flagYaGuardeArchivo == 1 && // si guardé archivo entonces guardo ultimo ID
	   path != NULL && pArrayListEmployee != NULL)
	{
		pFile = fopen(path, "w");
		if(pFile != NULL)
		{
			if(!serializer_IdFromText(pFile, pArrayListEmployee))
				retorno = 0;

			fclose(pFile);
		}
	}
	return retorno;
}
//************************************************************************************************ Funciones estáticas

/** \brief Busca por ID al empleado
 * \param pArrayListEmployee LinkedList* puntero a la lista
 * \param idABuscar int: id a buscar
 * \return Retorna el Empleado* si OK, NULL si ERROR
 */
static Employee* buscarPorId(LinkedList* pArrayListEmployee,int idABuscar)
{
	int i, lenLinkedList, idEncontrado, flagError;
	Employee* pEmpleado;
	Employee* pRetorno = NULL;

	lenLinkedList = ll_len(pArrayListEmployee);
	if(pArrayListEmployee != NULL && idABuscar >= 0 && lenLinkedList > 0)
	{
		for(i=0; i<lenLinkedList; i++)
		{
			pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
			idEncontrado = employee_getId(pEmpleado, &flagError);

			if(!flagError &&
			   idABuscar == idEncontrado)
			{
				pRetorno = pEmpleado;
				break;
			}
		}
	}
	return pRetorno;
}

/* \brief Submenu de modificacion de campos del empleado
 * \param
 * \return -1 ERROR, 0 ok
 */

static Employee* subMenuEdit(LinkedList* pArrayListEmployee)
{
	Employee buffer;
	Employee* pEmpleado;
	Employee* pRetorno = NULL;
	int opcionMenu, idBuscado;
	int flagModificado = 0;

	if(!utn_getNumero(&idBuscado, "\n\n > Ingrese ID del empleado a modificar: ", "\x1b[31m * ERROR \x1b[0m", 0, 999999999, 2))
	{
		pEmpleado = buscarPorId(pArrayListEmployee, idBuscado);
		if(pEmpleado == NULL)
			printf("\n * No existe empleado con ese ID\n");
		else
		{
			employee_mostrarEmpleado(pEmpleado);
			do
			{
				if(!utn_getNumero(&opcionMenu,
									"\n\n * =============  \x1b[30m\x1b[46mSUBMENU MODIFICAR\x1b[0m\x1b[0m  ============= *"
									"\n | =============================================== |"
									"\n | 1 -  Modificar nombre                           |"
									"\n | 2 -  Modificar hs trabajadas                    |"
									"\n | 3 -  Modificar sueldo                           |"
									"\n | 4 -  Salir                                      |"
									"\n * ----------------------------------------------- *"
									"\n > Eliga opcion: ",
									"\n * Opcion invalida *\n", 1, 4, 2))
				{
					switch(opcionMenu)
					{
						case 1: // Modificar nombre
							printf("\n - MODIFICACION DEL NOMBRE -");
							if(!utn_getNombre(buffer.nombre, NAME_LEN, "\n > Ingrese su nombre: ", "\n\x1b[31m * ERROR \x1b[0m\n", 2) &&
							   !laplume_confirmarAccion("\n > Desea confimar la modificacion del nombre?"))
							{
								if(!employee_setNombre(pEmpleado, buffer.nombre))
									flagModificado = 1;
							}
						break;
						case 2: // Modificar hs trabajadas
							printf("\n - MODIFICACION DE LAS HORAS TRABAJADAS -");
							if(!utn_getNumero(&buffer.horasTrabajadas,  "\n > Ingrese hs trabajadas: ",  "\n\x1b[31m * ERROR \x1b[0m\n", 0, 999 , 2) &&
							   !laplume_confirmarAccion("\n > Desea confimar la modificacion de las horas trabajadas?"))
							{
								if(!employee_setHorasTrabajadas(pEmpleado, buffer.horasTrabajadas))
									flagModificado = 1;
							}
						break;
						case 3: // Modificar sueldo
							printf("\n - MODIFICACION DEL SUELDO -");
							if(!utn_getNumero(&buffer.sueldo,  "\n > Ingrese su sueldo: $ ",  "\x1b[31m * ERROR \x1b[0m", 0, 99999 , 2) &&
							   !laplume_confirmarAccion("\n > Desea confimar la modificacion del sueldo?"))
							{
								if(!employee_setSueldo(pEmpleado, buffer.sueldo))
									flagModificado = 1;
							}
						break;
					}
				}
			}while(opcionMenu != 4);

			if(flagModificado == 1) // Se modificó el empleado, entonces lo guardamos.
			{
				pRetorno = pEmpleado;
			}
		}
	}
	return pRetorno;
}

/* \brief Realiza la baja de un empleado
 * \param
 * \return -1 ERROR, 0 si confirmó la baja, -2 si canceló la baja
 */
static int bajaEmpleado(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int idBaja, indiceBaja, respuestaConfirm;
	Employee* pEmpleado = NULL;

	if(!utn_getNumero(&idBaja, "\n\n > Ingrese ID del empleado a dar de baja: ", "\x1b[31m * ERROR \x1b[0m", 0, 999999999, 2))
	{
		pEmpleado = buscarPorId(pArrayListEmployee, idBaja);

		if(pEmpleado == NULL)
			printf("\n * El ID ingresado no corresponde a ningun empleado\n");
		else
		{
			if(!employee_mostrarEmpleado(pEmpleado))
			{
				respuestaConfirm = laplume_confirmarAccion("\n > Desea confimar la baja del empleado?");
				indiceBaja = ll_indexOf(pArrayListEmployee, pEmpleado);

			   if(indiceBaja >= 0 && respuestaConfirm == 0 &&
				  !ll_remove(pArrayListEmployee, indiceBaja) && !employee_delete(pEmpleado))
				   retorno = 0;
			   else
			   {
					if(respuestaConfirm == 1) // si respuesta es 1 [NO], canceló la baja
						retorno = -2;
			   }
			}
		}
	}
	return retorno;
}
/* \brief Pregunta si desea cargar archivo si anteriormenetee ya fue cargado uno
 * \param flagAbriArchivo int: flag estatico de si fue abierto un archivo
 * \return -1 ERROR, 0 si SI quiere abrir el archivo, 1 si NO quiere abrir el archivo
 */
static int preguntarCargarArchivo(int flagAbriArchivo)
{
	int retorno = -1;
	int respuesta;
	if(flagAbriArchivo == 1)
	{
		respuesta = laplume_confirmarAccion("\n\x1b[33m **************************** ATENCION **************************** \x1b[0m"
                							"\n > Ya hay un archivo cargado, si carga otro denuevo puede que haya IDs que se repitan y que causen problemas futuros"
											"\n > De todas formas, desea cargar archivo? (no recomendable)");
		retorno = respuesta;
	}
	return retorno;
}
