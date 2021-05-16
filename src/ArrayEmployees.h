
#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

#define NAME_LEN 51
#define LASTNAME_LEN 51

typedef struct
{
	int id;
	char name[NAME_LEN];
	char lastName[LASTNAME_LEN];
	float salary;
	int sector;

	int isEmpty;

}Employee;

int initEmployees(Employee list[], int len);
int addEmployee(Employee list[], int len, int id, char* name, char* lastName, float salary, int sector);
int findEmployeeById(Employee list[], int len, int id);
int removeEmployee(Employee list[], int len, int id);
int menuSortEmployees(Employee list[], int len);
int printEmployees(Employee list[], int length);

//********************************************************************************************************
int printOneEmployee(Employee* OneEmployee);
int getStringSector(int option,int stringLen ,char sector[]);
int searchIndexEmpty(Employee list[], int limite);
int registerEmployee(Employee list[], int len, int* id);
int menuModifyEmployee(Employee list[], int len);
int sortLastnameAndSectorUp(Employee list[], int len);
int sortLastnameAndSectorDown(Employee list[], int len);

#endif /* ARRAYEMPLOYEES_H_ */
