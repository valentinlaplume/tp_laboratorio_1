#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

#define STR_LEN 4096
#define NAME_LEN 128
#define IDINT_LEN 10
#define HS_LEN 10
#define SUELDO_LEN 15

typedef struct
{
    int id;
    char nombre[NAME_LEN];
    int horasTrabajadas;
    int sueldo;
}Employee;

//*********************************************************************************** Crear empleado
Employee* employee_new();
Employee* employee_newParametros(int id,char* nombre,int horasTrabajadas, int sueldo);
Employee* employee_newParametrosStr(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);

//*********************************************************************************** Destructor Empleado
int employee_delete(Employee* this);

//*********************************************************************************** Set - Get - isValid
int employee_setIdStr(Employee* this,char* id);
int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* flagError);
int employee_isValidIdStr(char* id);

int employee_setNombre(Employee* this,char* nombre);
char* employee_getNombre(Employee* this,int* flagError);
int employee_isValidNombre(char* nombre);

int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas);
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* flagError);
int employee_isValidHorasTrabajadasStr(char* horasTrabajadas);

int employee_setSueldoStr(Employee* this,char* sueldo);
int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* flagError);
int employee_isValidSueldoStr(char* sueldo);

//*********************************************************************************** Listar
int employee_mostrarEmpleado(Employee* pEmployee);

//*********************************************************************************** Alta del empleado
Employee* employee_alta(int* id);

//*********************************************************************************** Comparar por criterio
int employee_compararId(void* punteroI, void* punteroJ);
int employee_compararPorNombre(void* thisUno, void* thisDos);

#endif // employee_H_INCLUDED
