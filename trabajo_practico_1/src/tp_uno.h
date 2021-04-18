#ifndef TP_UNO_H_
#define TP_UNO_H_

int sumar(float *resultadoSuma, float numero_A, float numero_B);
int restar(float *resultadoResta, float numero_A, float numero_B);
int multiplicar(float *resultadoMultiplicacion, float numero_A, float numero_B);
int dividir(float *resultadoDivision, float numero_A, float numero_B);
int elFactorial(float* resultadoFactorial_A,float* resultadoFactorial_B, float numero_A, float numero_B);

int esNumerica(char str[]);
int esFlotante(char str[]);

int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError, int reintentos);
int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError, int minimo, int maximo, int reintentos);

#endif /* TP_UNO_H_ */
