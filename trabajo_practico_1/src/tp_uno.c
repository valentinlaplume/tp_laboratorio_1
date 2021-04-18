#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_uno.h"

static int myGets(char cadena[], int longitud);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief Calcula la suma entre A y B de dos numeros float
\param resultadoMultiplicacion Puntero donde va alojar el resultado de la suma
\param numero_A Primero operando ingresado
\param numero_B Segundo operando ingresado
\return Retorna 0 si logro la operacion, -1 si no lo hizo.
*/
int sumar(float *resultadoSuma, float numero_A, float numero_B)
{
	int retorno = -1;
	if(resultadoSuma != NULL)
	{
		*resultadoSuma = numero_A + numero_B;
		retorno = 0;
	}
	return retorno;
}

/*
\brief Calcula la resta entre A y B de dos numeros float
\param resultadoMultiplicacion Puntero donde va alojar el resultado de la resta
\param numero_A Primero operando ingresado
\param numero_B Segundo operando ingresado
\return Retorna 0 si logro la operacion, -1 si no lo hizo.
*/
int restar(float *resultadoResta, float numero_A, float numero_B)
{
	int retorno = -1;
	if(resultadoResta != NULL)
	{
		*resultadoResta = numero_A - numero_B;
		retorno = 0;
	}
	return retorno;
}

/*
\brief Calcula la multiplicacion entre A y B de dos numeros float
\param resultadoMultiplicacion Puntero donde va alojar el resultado de la multiplicacion
\param numero_A Primero operando ingresado
\param numero_B Segundo operando ingresado
\return Retorna 0 si logro la operacion, -1 si no lo hizo.
*/
int multiplicar(float* resultadoMultiplicacion, float numero_A, float numero_B)
{
	int retorno = -1;
	if(resultadoMultiplicacion != NULL)
	{
		*resultadoMultiplicacion = numero_A * numero_B;
		retorno = 0;
	}
	return retorno;
}

/*
\brief Calcula la division entre A y B de dos numeros float
\param resultadoDivision Puntero donde va alojar el resultado de la division
\param numero_A Primero operando ingresado
\param numero_B Segundo operando ingresado
\return Retorna 0 si logro la operacion, -1 si no lo hizo.
*/
int dividir(float *resultadoDivision, float numero_A, float numero_B)
{
	int retorno = -1;
	if(resultadoDivision != NULL)
	{
		if(numero_B != 0)
		{
			*resultadoDivision = numero_A / numero_B;
			retorno = 0;
		}else
			if(numero_B == 0)
				printf("\nNo es posible dividir por cero.\n");
	}
	return retorno;
}

/*
\brief Calcula el factorial de dos numeros y devuelve por parametro el resultado
\param resultadoFactorial_A Puntero donde va alojar el resultado del primero operando
\param resultadoFactorial_B Puntero donde va alojar el resultado del segundo operando
\param numero_A Primero operando ingresado
\param numero_B Segundao operando ingresado
\return Retorna 0 si logro la operacion, -1 si no lo hizo.
*/
int elFactorial(float* resultadoFactorial_A,float* resultadoFactorial_B, float numero_A, float numero_B)
{
	int retorno = -1;
	float i;
	float factorialA = 1;
	float factorialB = 1;
	if(resultadoFactorial_A != NULL && resultadoFactorial_B != NULL)
	{
		if(numero_A > 0.99)
		{
			for(i=1; i <= numero_A; i++)
			factorialA = factorialA * i;
			retorno = 0;
		}else
			if(numero_A == 0)
				printf("\nPrimer operando: No es posible el factorial de 0.\n");
		if(numero_B > 0.99)
		{
			for(i=1; i <= numero_B; i++)
			factorialB = factorialB * i;
			retorno = 0;
		}else
			if(numero_B == 0)
				printf("\nSegundo operando: No es posible el factorial de 0.\n");

		*resultadoFactorial_A = factorialA;
		*resultadoFactorial_B = factorialB;
	}
	return retorno;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief obtiene la cadena de forma segura utilizando la funcion 'fgets' y elimina el 'ENTER' de su ultimo indice.
\param char cadena[] es el puntero al array
\param longitud es la longitud hasta donde escribe el array.
\return 0 si obtuvo correctamente la cadena, -1 si no lo obtuvo.
*/
static int myGets(char cadena[], int longitud) //
{
	int retorno = -1;
	if(cadena != NULL && longitud > 0)
	{
		fpurge(stdin);
		fgets(cadena, longitud, stdin);

		if(cadena[ (strnlen(cadena,longitud) - 1) ] == 10)
		{
			cadena[ (strnlen(cadena,longitud) - 1) ] = 0;
			retorno = 0;
		}
	}
	return retorno;
}
/*
\brief de una cadena verifica si es flotante
\param char str[] cadena a ser verificada
\return Retorna 1 si esflotante, 0 si no lo es.
*/
int esFlotante(char str[])
{
	int retorno = 1;
	int i = 0;
	int contadorPuntos = 0;

	if(str != NULL )
	{
		for( ; str[i] != '\0'; i++)
		{
			if(i==0 && (str[i] == '-' || str[i] == '+') )
			{
				continue;
			}
			if(str[i] < '0' || str [i] > '9' )
			{
				if(str[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

/*
 * \brief de la una cadena obtiene un flotante. Utiliza la funcion 'atof'
 * \param resultado Puntero al espacio de memoria donde se dejara el flotante
 * \return Retorna 0 si ok, -1 si no pudo transformar la cadena a flotante
 */
static int getFloat(float* resultado) //
{
	int retorno = -1;
	char bufferString[555];

	if(myGets(bufferString, sizeof(bufferString))==0)
	{
		if( (esFlotante(bufferString) == 1) )
		{
			*resultado = atof(bufferString);
			retorno = 0;
		}
	}
	return retorno;
}
/*\brief Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser un operando valido
 * \param reintentos Es la cantidad de reintentos en ingresar operando
 * \return Retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError, int reintentos)
{
	int retorno = -1;
	float bufferFloat;
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getFloat(&bufferFloat)==0) && (pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) && (reintentos >= 0) )
		{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
		}
		else
			printf("%s",mensajeError);
	} // fin ciclo for.

	return retorno;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
\brief Verifica si el valor recibido es numerico.
\param Char str[] array con la cadena a ser analizada.
\return Retorna 1 si es numerico, 0 si no lo es.
*/
int esNumerica(char str[])
{
	int retorno = 1;
	int i = 0;


	if(str != NULL )
	{
		if(str[0] == '-')
		{
			i = 1;
		}
		for( ; str[i] != '\0'; i++)
		{
			if(str[i] < '0' || str [i] > '9' )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*
\brief De una cadena obtiene un numero entero con la funcion 'atoi'
\param bufferString cadena de intercambio
\param resultado puntero donde se va alojar la cadena ya tranformada a entero
\return Retorna 0 si OK, -1 ERROR.
*/
static int getInt(int* resultado) // obtengo el int
{
	int retorno = -1;
	char bufferString[555];

	if(myGets(bufferString, sizeof(bufferString))==0)
	{
		if( (esNumerica(bufferString) == 1) )
		{
			*resultado = atoi(bufferString);
			retorno = 0;
		}
	}
	return retorno;
}

/*\brief Solicita Un numero entero al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje El mensaje a ser mostrado
 * \param mensajeError Mensaje a ser mostrado en caso de no ser una opcion valida
 * \param reintentos Es la cantidad de reintentos en ingresar operando
 * \return retorna 0 si OK, -1 si hay ERROR.
 */
int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	for(int i=0 ; i<=reintentos ; i++)
	{
		printf("%s",mensaje);
		fpurge(stdin);

		if((getInt(&bufferInt)==0) && (pResultado != NULL) && (mensaje != NULL) && (mensajeError != NULL) && (minimo <= maximo) && (reintentos >= 0) )
		{
			if((bufferInt >= minimo) && (bufferInt <= maximo))
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			else
				printf("%s",mensajeError);
		}
	}
	return retorno;
}
