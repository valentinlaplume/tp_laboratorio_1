#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "laplume.h"
#include "Employee.h"
#include "utn.h"

static int employee_pedidoDeDatos(char* nombre, int* horasTrabajadas, int* sueldo);

/* \brief Reserva espacio en memoria para un empleado
 * \param void
 * \return Employee* [direccion de memoria] si obtuvo memoria, [NULL] si no hay mas memoria
 */
Employee* employee_new()
{
	return (Employee*) malloc(sizeof(Employee) * 1);
}

/* \brief Valida los campos y convierte al tipo de dato que corresponda en cada campo, y los carga en una variable Employee
 * \param idStr char* puntero al id
 * \param nombreStr char* puntero al nombre
 * \param horasTrabajadasStr char* puntero a las horas
 * \param sueldoStr char* puntero al sueldo
 * \return Employee* Retorna puntero al empleado cargado
 */
Employee* employee_newParametrosStr(char* idStr, char* nombreStr, char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* pAuxEmpleado = NULL;

	if(idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		pAuxEmpleado = employee_new();
		if(pAuxEmpleado != NULL)
		{
			if( employee_setIdStr(pAuxEmpleado, idStr)                           <0 ||
				employee_setNombre(pAuxEmpleado, nombreStr)                      <0 ||
				employee_setHorasTrabajadasStr(pAuxEmpleado, horasTrabajadasStr) <0 ||
				employee_setSueldoStr(pAuxEmpleado, sueldoStr)                   <0)
			{
				employee_delete(pAuxEmpleado); // elimino memoria si no obtuvo los set
				pAuxEmpleado = NULL;
			}
		}
	}
	return pAuxEmpleado;
}
/* \brief Valida los campos y los carga en una variable Employee
 * \param id int id a ser validado y cargado
 * \param nombre char* puntero al nombre
 * \param horasTrabajadas int horas a ser validadas y cargadas
 * \param sueldo int sueldo a ser validado y cargado
 * \return Employee*
 */
Employee* employee_newParametros(int id,char* nombre,int horasTrabajadas, int sueldo)
{
	Employee* pAuxEmpleado;

	pAuxEmpleado = employee_new();
	if(pAuxEmpleado != NULL)
	{
		if( employee_setId(pAuxEmpleado, id)                           <0 ||
			employee_setNombre(pAuxEmpleado, nombre)                   <0 ||
			employee_setHorasTrabajadas(pAuxEmpleado, horasTrabajadas) <0 ||
			employee_setSueldo(pAuxEmpleado, sueldo)                   <0)
		{
			employee_delete(pAuxEmpleado); // elimino memoria si no obtuvo los set
			pAuxEmpleado = NULL;
		}
	}
	return pAuxEmpleado;
}

/* \brief Libera el espacio reservado en memoria para un empleado
 * \param this Employee*
 * \return void
 */
int employee_delete(Employee* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}
/* \brief Realiza el Alta de un empleado
 * \return Employee* al empleado si OK, NULL error.
 */
Employee* employee_alta(int* id)
{
	Employee buffer;
	Employee* pEmpleado;
	Employee* pRetorno = NULL;

	if(id != NULL && !employee_pedidoDeDatos(buffer.nombre, &buffer.horasTrabajadas, &buffer.sueldo))
	{
		buffer.id = (*id)++; // incremento ID
		pEmpleado = employee_newParametros(buffer.id, buffer.nombre, buffer.horasTrabajadas, buffer.sueldo);
		if(pEmpleado != NULL)
		{
			pRetorno = pEmpleado;
		}
	}
	return pRetorno;
}
//*********************************************************************** SETTER - GETTERS - ISVALID **************
int employee_setIdStr(Employee* this,char* id)
{
	int bufferId;
	int retorno = -1;
	if(this != NULL && id != NULL && employee_isValidIdStr(id))
	{
		bufferId = atoi(id);
		if(bufferId >= 0)
		{
			this->id = bufferId;
			retorno = 0;
		}
	}
	return retorno;
}
int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		this->id = id;
		retorno = 0;
	}
	return retorno;
}

int employee_getId(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL)
	{
		auxId = this->id;
		*flagError = 0;
	}
	return auxId;
}

int employee_isValidIdStr(char* id)
{
	int retorno = 0;
	if(id != NULL && esNumerica(id, IDINT_LEN))
	{
		retorno = 1;
	}
	return retorno;
}
//----------------------------------------------------------------------
int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL && employee_isValidNombre(nombre))
	{
		strncpy(this->nombre,nombre,NAME_LEN);
		retorno = 0;
	}
	return retorno;
}
char* employee_getNombre(Employee* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre = NULL;
	if(this != NULL && flagError != NULL)
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}

int employee_isValidNombre(char* nombre)
{
	int retorno = 0;

	if(nombre != NULL && esNombre(nombre))
	{
		retorno = 1;
	}
	return retorno;
}
//----------------------------------------------------------------------
int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
	int bufferHsTrabajadas;
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL && employee_isValidHorasTrabajadasStr(horasTrabajadas))
	{
		bufferHsTrabajadas = atoi(horasTrabajadas);
		if(bufferHsTrabajadas >= 0)
		{
			this->horasTrabajadas = bufferHsTrabajadas;
			retorno = 0;
		}
	}
	return retorno;
}
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}
int employee_getHorasTrabajadas(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxHsTrabajadas = -1;
	if(this != NULL && flagError != NULL)
	{
		auxHsTrabajadas = this->horasTrabajadas;
		*flagError = 0;
	}
	return auxHsTrabajadas;
}

int employee_isValidHorasTrabajadasStr(char* horasTrabajadas)
{
	int retorno = 0;
	if(horasTrabajadas != NULL && esNumerica(horasTrabajadas, HS_LEN))
	{
		retorno = 1;
	}
	return retorno;
}
//----------------------------------------------------------------------
int employee_setSueldoStr(Employee* this,char* sueldo)
{
	int bufferSueldo;
	int retorno = -1;
	if(this != NULL && sueldo != NULL && employee_isValidSueldoStr(sueldo))
	{
		bufferSueldo = atoi(sueldo);
		if(bufferSueldo > 0)
		{
			this->sueldo = bufferSueldo;
			retorno = 0;
		}
	}
	return retorno;
}
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo > 0)
	{
		this->sueldo = sueldo;
		retorno = 0;
	}
	return retorno;
}
int employee_getSueldo(Employee* this,int* flagError)
{
	*flagError = -1;
	int auxSueldo = -1;
	if(this != NULL && flagError != NULL)
	{
		auxSueldo = this->sueldo;
		*flagError = 0;
	}
	return auxSueldo;
}
int employee_isValidSueldoStr(char* sueldo)
{
	int retorno = 0;
	if(sueldo != NULL && esNumerica(sueldo, SUELDO_LEN))
	{
		retorno = 1;
	}
	return retorno;
}

//************************************************************************* FUNCIONES CRITERIO

/** \brief Compara dos ID
 * \param this1 void*
 * \param this2 void*
 * \return int -1 ERROR,
 	 	 	 	 	 	  0 si los this son iguales
 	 	 	 	 	 	  1 si thisUno es mayor a thisDos
 	 	 	 	 	 	 -2 si thisUno es menor a thisDos
 */
int employee_compararId(void* this1, void* this2)
{
    int retorno=-1;

    int bufferIdUno, bufferIdDos;
    int flagErroUno, flagErroDos ;

    if(this1!=NULL && this2!=NULL)
    {
    	bufferIdUno =  employee_getId((Employee*)this1, &flagErroUno);
    	bufferIdDos = employee_getId((Employee*)this2, &flagErroDos);

    	if(!flagErroUno && !flagErroDos)
    	{
			if(bufferIdUno == bufferIdDos)
			{
				retorno = 0;
			}
			else
			{
				if(bufferIdUno > bufferIdDos)
				{
					retorno = 1;
				}
				else
				{
					if(bufferIdUno < bufferIdDos)
					{
						 retorno = -1;
					}
				}
			}
		}

    }
    return retorno;
}

/* \brief Compara dos Nombres
 * \param this1 void*
 * \param this2 void*
 * \return int -2 ERROR,
 	 	 	 	 	 	  0 si los this son iguales
 	 	 	 	 	 	  1 si thisUno es mayor a thisDos
 	 	 	 	 	 	 -1 si thisUno es menor a thisDos
 */
int employee_compararPorNombre(void* thisUno, void* thisDos)
{
    int retorno= -2;
    char* bufferNombreUno;
    char* bufferNombreDos;
    int flagErrorUno, flagErrorDos;

    if(thisUno != NULL && thisDos != NULL)
    {
    	bufferNombreUno = employee_getNombre((Employee*)thisUno, &flagErrorUno);
    	bufferNombreDos = employee_getNombre((Employee*)thisDos, &flagErrorDos);

    	if(!flagErrorUno && !flagErrorDos)
    	{
    		if(strcmp(bufferNombreUno, bufferNombreDos) > 0)
    		{
    			retorno = 1;
    		}
    		else
    		{
				if(strcmp(bufferNombreUno, bufferNombreDos) < 0)
				{
					retorno = -1;
				}
    			else
    			{
    				if(strcmp(bufferNombreUno, bufferNombreDos) == 0)
    				{
    					retorno = 0;
    				}
    			}
    		}
    	}
    }
    return retorno;
}

//----------------------------------------------------------------------- LISTAR

/** \brief Lista un empleado
 * \param int indice indice del empleado a ser mostrado
 * \param pArrayListEmployee LinkedList*
 * \return -1 ERROR, 0 OK
 */
int employee_mostrarEmpleado(Employee* pEmpleado)
{
	int retorno = -1;
	//------------------------------- AUXILIARES
	int auxId, auxHsTrabajadas, auxSueldo;
	char* bufferNombre = NULL;
	//------------------------------- FLAGS ERRORES
	int flagErrorUno, flagErrorDos, flagErrorTres, flagErrorCuatro;

	if(pEmpleado != NULL)
	{
		auxId = employee_getId(pEmpleado, &flagErrorUno);
		bufferNombre = employee_getNombre(pEmpleado, &flagErrorDos);
		auxHsTrabajadas = employee_getHorasTrabajadas(pEmpleado, &flagErrorTres);
		auxSueldo = employee_getSueldo(pEmpleado, &flagErrorCuatro);

		if(!flagErrorUno && !flagErrorDos && !flagErrorTres && !flagErrorCuatro)
		{
			printf("\n\x1b[34m   --------------------------------------------------------------------------------------------  \x1b[0m"
				   "\n"
				   "\x1b[33m | \x1b[0m  "
				   "\x1b[47m\x1b[35m ID \x1b[0m\x1b[0m: %-10d"
				   "\x1b[47m\x1b[30m NOMBRE \x1b[0m\x1b[0m: %-15s"
				   "\x1b[47m\x1b[30m HS TRABAJADAS \x1b[0m\x1b[0m: %-10d"
				   "\x1b[47m\x1b[30m SUELDO \x1b[0m\x1b[0m: $ %-10d"
				   "\x1b[33m | \x1b[0m",auxId,
						 bufferNombre,
						 auxHsTrabajadas,
						 auxSueldo);
			retorno = 0;
		}
	}
	return retorno;
}

//********************************************************************************* STATIC FUNCION
/* \brief Pide los datos del empleado al usuario
 * \param char* nombre puntero al nombre a ser escrito
 * \param int* horasTrabajadas puntero a las horas trabajadas
 * \param int* sueldo puntero al sueldo
 * \return -1 ERROR, 0 ok
 */
static int employee_pedidoDeDatos(char* nombre, int* horasTrabajadas, int* sueldo)
{
	int retorno = -1;

	if(nombre != NULL && horasTrabajadas != NULL && sueldo != NULL)
	{
		if(!utn_getNombre(nombre, NAME_LEN, "\n > Ingrese su nombre: ", "\n\x1b[31m * ERROR \x1b[0m\n", 2) &&
		   !utn_getNumero(horasTrabajadas,  "\n > Ingrese hs trabajadas: ",  "\n\x1b[31m * ERROR \x1b[0m\n", 0, 999 , 2) &&
		   !utn_getNumero(sueldo,  "\n > Ingrese su sueldo: $ ",  "\x1b[31m * ERROR \x1b[0m", 0, 99999999, 2))
		{
			retorno = 0;
		}
	}
	return retorno;
}












