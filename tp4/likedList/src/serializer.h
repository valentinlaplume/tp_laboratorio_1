/*
 * serializer.h
 *
 *  Created on: 28 may. 2021
 *      Author: valentinlaplume
 */

#ifndef SERIALIZER_H_
#define SERIALIZER_H_

int serializer_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);
int serializer_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);
int serializer_IdFromText(FILE* pFile , LinkedList* pArrayListEmployee);

#endif /* SERIALIZER_H_ */
