/*
	Alumno: Valentin laplume
	Dni: 42.544.147
	Division: 1°H
	Trabajo Práctico: n°1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_uno.h"

int main (void)
{
	int menu;
	// numeroA = X ; numeroB = Y
	float numeroA,numeroB = 0;
	// Variables declaradas para alojar el resultado de las operaciones.
	float resultadoSuma,
		  resultadoResta,
		  resultadoMultiplicacion,
		  resultadoDivision,
		  resultadoFactorialA, resultadoFactorialB;
	// Variables declaradas para asegurarme que mostrar al usuario.
	int flagUno, flagDos, flagTres, flagResultado = 0;
	do
	{
		if(utn_getNumero(&menu, "\n	-- Calculadora --"
								"\nMenu:  "
								"\n1- Ingresar 1er operando."
								"\n2- Ingresar 2do operando."
								"\n3- Calcular todas  las operaciones."
								"\n4- Ver resultados."
								"\n5- Salir."
								"\nOpcion: ", "Opcion invalida.\n", 1, 5, 2)==0)
		{
			switch(menu)
			{
				case 1:
					utn_getNumeroFloat(&numeroA, "\nIngrese 1er operando: ", "\nOperando invalido.", 2);
					flagUno = 1;
					break;
				case 2:
					utn_getNumeroFloat(&numeroB, "\nIngrese 2do operando: ", "\nOperando invalido.", 2);
					flagDos = 2;
					break;
				case 3:
					sumar(&resultadoSuma, numeroA, numeroB);
					restar(&resultadoResta, numeroA, numeroB);
					multiplicar(&resultadoMultiplicacion, numeroA, numeroB);
					dividir(&resultadoDivision, numeroA, numeroB);
					elFactorial(&resultadoFactorialA, &resultadoFactorialB, numeroA, numeroB);
					flagTres = 3;
					break;
				case 4:
					flagResultado = flagUno + flagDos + flagTres;

					if(flagResultado == 6) // me hubiese gustado ponerlo todo en una funcion pero no me dio el tiempo.
					{
						printf("\n-El resultado de ( %.2f + %.2f ) es: %.2f\n",numeroA,numeroB,resultadoSuma);
						printf("\n-El resultado de ( %.2f - %.2f ) es: %.2f\n",numeroA,numeroB,resultadoResta);
						printf("\n-El resultado de ( %.2f * %.2f ) es: %.2f\n",numeroA,numeroB,resultadoMultiplicacion);
						printf("\n-El resultado de ( %.2f / %.2f ) es: %.2f\n",numeroA,numeroB,resultadoDivision);
						printf("\n-El factorial de ( %.2f! ) es: %.2f"
								"\n-El factorial de ( %.2f! ) es: %.2f\n",numeroA, resultadoFactorialA,
																		numeroB, resultadoFactorialB);
					}
					else
					{
						if(flagResultado == 0)
							printf("\nNo ingresaste nada como para ver resultados.\n");
						if(flagResultado == 1 || flagResultado == 2 )
							printf("\nPuede que hayas ingresado un operando pero no calculaste la operacion.\n");
						if(flagResultado == 3)
							printf("\n-Ingresa al menos un operando para calcular operaciones.");
						if(flagResultado == 4)
							printf("\n-Primer operando: El factorial de ( %.2f! ) es: %.2f",numeroA, resultadoFactorialA);
						if(flagResultado == 5)
							printf("\n-Segundo operando: El factorial de ( %.2f! ) es: %.2f",numeroB, resultadoFactorialB);
					}
					 break;
				case 5: // salir
					break;
			}
		}
	}while(menu != 5);

	return 	EXIT_SUCCESS;
}




