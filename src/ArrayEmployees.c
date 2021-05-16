
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"

#define TRUE 1
#define FALSE 0
#define SECTOR_LEN 50
#define BUFFER_LEN 4096


/* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int initEmployees(Employee* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i=0; i<len; i++)
		{
			list[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/* \brief add in a existing list of employees the values received as parameters * in the first empty position
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \param id int Id of Employee asignated
 * \param name[] char Name Employee
 * \param lastName[] char lastNamee Employee
 * \param salary float Salary Employee
 * \param sector int Sector Employee
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
 */
int addEmployee(Employee list[], int len, int id, char* name, char* lastName, float salary, int sector)
{
	int retorno = -1;
	int indexEmpty = -1;
	Employee buffer;

	indexEmpty = searchIndexEmpty(list, len);

	if(list != NULL && len > 0  && indexEmpty >= 0)
	{
		buffer.id = id;
		strncpy(buffer.name, name, NAME_LEN);
		strncpy(buffer.lastName, lastName, LASTNAME_LEN);
		buffer.salary = salary;
		buffer.sector = sector;
		buffer.isEmpty = FALSE;
		list[indexEmpty] = buffer;
		retorno = 0;
	}
	return retorno;
}

/* \brief find one Employee by Id en returns the index position in array.
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \param id int Id of Employee to search
 * \return Return employee index position or (-1) if [Invalid length or NULL pointer received or employee not found]
 */
int findEmployeeById(Employee list[], int len, int id)
{
	int i;
	int index = -1;

	if(list != NULL && len > 0 && id >= 0)
	{
		for(i=0; i<len; i++)
		{
			if(list[i].isEmpty == FALSE && list[i].id == id)
			{
				index = i;
				break;
			}
		}
	}
	return index;
}

/* \brief Remove a Employee by Id (put isEmpty Flag in 1) *
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \param id int Id of Employee to remove
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't find a employee] - (0) if Ok
 */
int removeEmployee(Employee list[], int len, int id)
{
	int retorno = -1;
	int index = -1;

	index = findEmployeeById(list, len, id);

	if(list != NULL && id >= 0 && len > 0 && index >= 0 && index < len && list[index].isEmpty == FALSE)
	{
		list[index].isEmpty = TRUE;
		retorno = 0;
	}
	return retorno;
}

/* \brief Sort the elements in the array of employees UP
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int menuSortEmployees(Employee list[], int len)
{
	int retorno = -1;
	int optionMenu;

	do
	{
		if(list != NULL&& len > 0)
		{

			if(!utn_getNumero(&optionMenu,
							"\n"
							"\n* ---------------- SUBMENU --------------- *"
							"\n| ---------------------------------------  |"
							"\n|  0 - Order down                           |"
							"\n|  1 - Order up                            |"
							"\n|  2 - Exit                                |"
							"\n* ---------------------------------------- *"
							"\n - Opcion >   ",
							"\n - ERROR -"
							"\nOpcion invalida\n", 0, 2, 2))
			{
				switch(optionMenu)
				{
					case 0:
						if(!sortLastnameAndSectorDown(list, len))
						{
							printf("\n* Order down ok *\n");
						}
					break;
					case 1: // Order up
						if(!sortLastnameAndSectorUp(list, len))
						{
							printf("\n* Order up ok *\n");
						}
					break;

				}
				retorno = 0;
			}
		}
	}while(optionMenu != 2);
	return retorno;
}
/* \brief Sort the elements in the array of employees, DOWN
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok *
 */
int sortLastnameAndSectorUp(Employee list[], int len)
{
	int respuesta = -1;
		int i;
		Employee buffer;
		int flagSwap;
		if(list != NULL && len>0)
		{
			do
			{
				flagSwap = 0;
				for (i=0; i<len-1; i++)
				{
					if(list [i].isEmpty == 0 && list[i+1].isEmpty== 0)
					{
						if ((list[i].sector > list [i+1].sector) || (list[i].sector == list [i+1].sector && strncmp(list[i].lastName, list[i+1].lastName, LASTNAME_LEN)>0))
						{
							flagSwap = 1;
							buffer = list[i];
							list[i] = list[i+1];
							list[i+1] = buffer;
							respuesta = 0;
						}
					}
				}
				len--;
			}while (flagSwap);
		}
	return respuesta;
}
/* \brief Sort the elements in the array of employees, the argument order indicate UP
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok *
 */
int sortLastnameAndSectorDown(Employee list[], int len)
{
	int respuesta = -1;
		int i;
		Employee buffer;
		int flagSwap;
		if(list != NULL && len>0)
		{
			do
			{
				flagSwap = 0;
				for (i=0; i<len-1; i++)
				{
					if(list [i].isEmpty == 0 && list[i+1].isEmpty== 0)
					{
						if ((list[i].sector < list [i+1].sector) || (list[i].sector == list [i+1].sector && strncmp(list[i].lastName, list[i+1].lastName, LASTNAME_LEN)<0))
						{
							flagSwap = 1;
							buffer = list[i];
							list[i] = list[i+1];
							list[i+1] = buffer;
							respuesta = 0;
						}
					}
				}
				len--;
			}while (flagSwap);
		}
	return respuesta;
}

/* \brief print the content of employees array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int printEmployees(Employee list[], int length)
{
	int i;
	int retorno = -1;

	if(list != NULL && length > 0 )
	{
		for(i=0; i<length; i++)
		{
			printOneEmployee(&list[i]);
			retorno = 0;
		}
	}
	return retorno;
}

//********************************************************************************************************
/* \brief print the content of one employees
 * \param list Employee* Pointer to array of employees
 * \param index int Employee index
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 */
int printOneEmployee(Employee* OneEmployee)
{
	int retorno = -1;
	char bufferSector[SECTOR_LEN];

	if(OneEmployee != NULL && OneEmployee->isEmpty == FALSE &&
	   !getStringSector(OneEmployee->sector, SECTOR_LEN , bufferSector))
	{
		printf("\n--------------------------------------------------------------------------------------"
				"----------------------------------------\n");
		printf( "ID: %-8d"
				"NAME: %-13s"
				"LASTNAME: %-13s"
				"SALARY: $%-13.2f"
				"SECTOR: %-15s",
				OneEmployee->id,
				OneEmployee->name,
				OneEmployee->lastName,
				OneEmployee->salary,
				bufferSector);
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Get a string according to the option (Charged or Pending)
 * \param int option: Int number, the case options
 * \param int stringLen: Limit of the string to copy
 * \param char sector: pointer to the char array to be copied the string
 * \return int Return (-1) if Error [Invalid stringLen or sector NULL pointer or option invalid ] - (0) if Ok
 */
int getStringSector(int option, int stringLen , char sector[])
{
	char bufferSector[BUFFER_LEN];
	int retorno = -1;

	if(option >= 0 && stringLen > 0 && sector != NULL)
	{
		switch(option)
		{
			case 0:
				strncpy(bufferSector, "Finance", stringLen);
				break;
			case 1:
				strncpy(bufferSector, "Human Resources", stringLen);
				break;
			case 2:
				strncpy(bufferSector, "Sales", stringLen);
				break;
		}
		strncpy(sector, bufferSector, stringLen);
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief Look for an empty position / index of the array
 * \param list Employee* Pointer to array of employees
 * \param index int Employee index
 * \return Returns (index) if it finds an empty index, (-1) there is no more place in the array or Error.
 */
int searchIndexEmpty(Employee list[], int limite)
{
    int i;
    int indexEmpty = -1;

    if(list != NULL && limite > 0)
    {
    	for(i=0; i<limite; i++)
    	{
    		if(list[i].isEmpty == TRUE)
    		{
    			indexEmpty = i;
    			break;
    		}
    	}
    }
    return indexEmpty;
}
/*
 * \brief Register one Employee
 * \param list Employee* Pointer to array of employees
 * \param index int Employee index
 *\return int Return (-1) if Error  - (0) if Ok
 */
int registerEmployee(Employee list[], int len, int* id) // no comentarios
{
	int retorno = -1;
	Employee buffer;

	if(list != NULL && len > 0 &&  id != NULL)
	{
		if( !utn_getNombre(buffer.name, NAME_LEN, "\nEnter name >  ", "\n- ERROR -\n", 2) &&
			!utn_getNombre(buffer.lastName, LASTNAME_LEN, "Enter lastName >  ", "\n- ERROR -\n", 2) &&
			!utn_getNumeroFloat(&buffer.salary, "Enter salary [$1 - $500.000] >  ", "\n- ERROR -\n", 1, 500000, 2) &&
			!utn_getNumero(&buffer.sector, "Enter sector [0]Finance - [1]Human Resources - [2]Sales >  ", "\n- OPTION INVALID -\n", 0, 2, 2))
		{
			(*id)++;
			buffer.id = (*id);
			if(!addEmployee(list, len, buffer.id, buffer.name, buffer.lastName, buffer.salary, buffer.sector))
			{
				retorno = 0;
			}
			else
				(*id)--;
		}

	}
	return retorno;
}

/*
 * \brief Menu modify Employee
 * \param list Employee* Pointer to array of employees
 * \param index int Employee index
 *\return int Return (-1) if Error  - (0) if Ok
 */
int menuModifyEmployee(Employee list[], int len)// no comentarios
{
	int retorno = -1;
	int optionMenu;
	int indexModify = -1;
	int idModify;

	printEmployees(list, len);
	if(list != NULL && len > 0 && !utn_getNumero(&idModify, "\nEnter ID modify > ", "\n*ERROR*\n", 0, 1000000, 2))
	{
		indexModify = findEmployeeById(list, len, idModify);
		if(indexModify >= 0)
		{
			do
			{
				if(!utn_getNumero(&optionMenu,
								"\n"
								"\n* ---------------- SUBMENU --------------- *"
								"\n| ---------------------------------------  |"
								"\n|  0 - Modify Name                         |"
								"\n|  1 - Modify LastName                     |"
								"\n|  2 - Modify Salary                       |"
								"\n|  3 - Modify Sector                       |"
								"\n|  4 - Exit                                |"
								"\n* ---------------------------------------- *"
								"\n - Opcion >   ",
								"\n - ERROR -"
								"\nOpcion invalida\n", 0, 4, 99))
				{
					switch(optionMenu)
					{
						case 0:
							if(!utn_getNombre(list[indexModify].name, NAME_LEN, "\nEnter name >  ", "\n- ERROR -\n", 2))
							{
								printf("\n*Modify name ok");
							}
						break;
						case 1:
							if(!utn_getNombre(list[indexModify].lastName, LASTNAME_LEN, "Enter lastName >  ", "\n- ERROR -\n", 2))
							{
								printf("\n*Modify lastname ok");
							}
						break;
						case 2:
							if(!utn_getNumeroFloat(&list[indexModify].salary, "Enter salary [$1 - $500.000] >  ", "\n- ERROR -\n", 1, 500000, 2))
							{
								printf("\n*Modify salary ok");
							}
						break;
						case 3:
							if(!utn_getNumero(&list[indexModify].sector, "Enter sector [0]Finance - [1]Human Resources - [2]Sales >  ", "\n- OPTION INVALID -\n", 0, 2, 2))
							{
								printf("\n*Modify sector ok");
							}
						break;
					}
				}

			}while(optionMenu != 4);
			retorno = 0;
		}
	}
	return retorno;
}




