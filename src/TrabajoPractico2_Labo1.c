/*
 ============================================================================
 Name and lastname      : Valentin Laplume
 Dni                    : 42.544.147
 T.P                    : n°2
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"

#define QUANTITY_EMPLOYEES 1000

int main(void)
{
	int optionMenu;
	Employee listEmployees[QUANTITY_EMPLOYEES];
	int idEmployee = 7;
	int flagEmployee = 0;
	int idAux;
	int indexAux;
	//-------------

	if(!initEmployees(listEmployees, QUANTITY_EMPLOYEES))
	{
		printf("\n*INIT EMPLOYEES OK.");
	}
	if(!addEmployee(listEmployees, QUANTITY_EMPLOYEES, 1, "Mirtha", "Legrand", 250000, 1) &&
	   !addEmployee(listEmployees, QUANTITY_EMPLOYEES, 2, "Lionel", "Messi", 400000, 0) &&
	   !addEmployee(listEmployees, QUANTITY_EMPLOYEES, 3, "Anibal", "Pachano", 63, 2) &&
	   !addEmployee(listEmployees, QUANTITY_EMPLOYEES, 4, "Moria", "Casan", 100000, 1) &&
	   !addEmployee(listEmployees, QUANTITY_EMPLOYEES, 5, "Susana", "Gimenez", 300000, 1) &&
	   !addEmployee(listEmployees, QUANTITY_EMPLOYEES, 6, "Flavio", "Mendoza", 25, 1) &&
	   !addEmployee(listEmployees, QUANTITY_EMPLOYEES, 7, "Mauricio", "Macri", 350000, 0))
		{
			flagEmployee++;
		}
	do
	{


			if(!utn_getNumero(&optionMenu,
							"\n"
							"\n* -------------- MAIN MENU --------------- *"
							"\n| ---------------------------------------  |"
							"\n|  1 - Register Employee                   |"
							"\n|  2 - Modify Employee                     |"
							"\n|  3 - Remove Employee                     |"
							"\n|  4 - Report                              |"
							"\n|  5 - Exit                                |"
							"\n* ---------------------------------------- *"
							"\n - Option >   ",
							"\n - ERROR -"
							"\nOption invalid\n", 1, 5, 99))
			{
				switch(optionMenu)
				{
					case 1: // Register Employee
						if(!registerEmployee(listEmployees, QUANTITY_EMPLOYEES, &idEmployee))
						{
							printf("\n todo ok lo cargue");
							flagEmployee++;
						}
					break;
					case 2: // Modify Employee
						if(flagEmployee > 0)
						{
							menuModifyEmployee(listEmployees, QUANTITY_EMPLOYEES);
						}
						else
							printf("\nThere are no registered employees, please register at least one employee.");
					break;
					case 3: // Remove Employee
						if(flagEmployee > 0)
						{
							printEmployees(listEmployees, QUANTITY_EMPLOYEES);
							if(!utn_getNumero(&idAux, "\nEnter the id to delete > ", "- ERROR -", 0, 10000, 2))
							{
								indexAux = findEmployeeById(listEmployees, QUANTITY_EMPLOYEES, idAux);
								if(indexAux >= 0)
								{
									removeEmployee(listEmployees, QUANTITY_EMPLOYEES, idAux);
								}
							}
						}
						else
							printf("\nThere are no registered employees, please register at least one employee.");
					break;
					case 4: // Report
						if(flagEmployee > 0)
						{
							if(!menuSortEmployees(listEmployees, QUANTITY_EMPLOYEES))
							{
								printEmployees(listEmployees, QUANTITY_EMPLOYEES);
							}
						}
						else
							printf ("\nThere are no registered employees, please register at least one employee.");
					break;
				}
			}

	}while(optionMenu != 5);
	return EXIT_SUCCESS;
}
