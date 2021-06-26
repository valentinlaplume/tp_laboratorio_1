#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc (sizeof(LinkedList));
    if(this != NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = this->size; // retorno cantidad de elementos
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNodeAux = NULL;
	int i;
	int sizeLinkedList;

	sizeLinkedList = ll_len(this);
	if(this != NULL && nodeIndex >= 0 && nodeIndex < sizeLinkedList)
	{
		pNodeAux = this->pFirstNode; // cargo aux con el PRIMER nodo
		for(i=0; i<sizeLinkedList; i++)
		{
			if(i == nodeIndex && pNodeAux != NULL)
				break;
			else
				pNodeAux = pNodeAux->pNextNode; // cargo aux con el siguiente nodo
		}
	}
    return pNodeAux;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
	int returnAux = -1;

	if(this != NULL && (nodeIndex >= 0) && (nodeIndex <= ll_len(this)))
	{
		Node* pAux = NULL;
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		if(pNewNode != NULL)
		{

			if(nodeIndex == 0)
			{
				pAux = this->pFirstNode;
				this->pFirstNode = pNewNode;
				pNewNode->pNextNode = pAux;
			}
			else
			{
				if(nodeIndex == ll_len(this)-1)
				{
					pAux = getNode(this, nodeIndex); // cargo en aux el nodo en ese indice para no perderlo
					pAux->pNextNode = pNewNode;
					pNewNode->pNextNode = NULL;
				}
				else
				{
					pAux = getNode(this, nodeIndex-1); // el anterior nodo
					pAux->pNextNode = pNewNode; // el anterior apunta al nuevo
					pNewNode->pNextNode = getNode(this, nodeIndex); // el nuevo apunta al de la posicion
				}
			}
			pNewNode->pElement = pElement;
			this->size++;
			returnAux = 0;
		}
	}
    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 */
int ll_add(LinkedList* this, void* pElement)
{
	int returnAux = -1;
	int sizeLinkedList;

	sizeLinkedList = ll_len(this);
	if(this != NULL  && sizeLinkedList >= 0)
	{
		if(!addNode(this, sizeLinkedList, pElement)) // agrego al final (no deja agregar al principio)
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pNode = getNode(this, index);
    	if(pNode != NULL)
    	{
    		returnAux = pNode->pElement;
    	}
    }
    return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */

int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    Node* pAux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this) )
    {
        pAux = getNode(this, index);
        if(pAux != NULL)
        {
            pAux->pElement = pElement;
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pNodeActual;
    Node* pNodeAnterior;
    Node* pNodeSiguiente;

   if(this != NULL && index >= 0 && index < ll_len(this))
   {

		if(index == 0)
		{
			pNodeActual = this->pFirstNode;
			this->pFirstNode = pNodeActual->pNextNode;
			free(pNodeActual);
			this->size--;
			returnAux = 0;
		}
		else
		{
			pNodeActual = getNode(this, index); // obtengo el nodo actual
			if(pNodeActual != NULL)
			{
				pNodeAnterior = getNode(this, index-1); // obtengo el anterior
				if(pNodeAnterior != NULL)
				{
					pNodeSiguiente = getNode(this, index+1); // obtengo el siguiente
					if(pNodeSiguiente != NULL)
					{
						pNodeAnterior->pNextNode = pNodeSiguiente; // que el nodo next del anterior apunte al siguiente del actual
						free(pNodeActual);
						this->size--;
						returnAux = 0;
					}
					else
					{
						pNodeAnterior->pNextNode = NULL;
						free(pNodeActual);
						this->size--;
						returnAux = 0;
					}
				}
			}
		}
   }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	for(int i=0; i<ll_len(this); i++)
    	{
    		ll_remove(this, i);
    	}
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	ll_clear(this);
    	free(this);
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* pNodeAux;
    if(this != NULL)
    {
    	for(int i=0; i<ll_len(this); i++)
    	{
    		pNodeAux = ll_get(this, i);
    		if(pNodeAux == pElement)
    		{
    			returnAux = i;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
	{
    	if(this->size == 0)
    		returnAux = 1;
    	else
    		returnAux = 0;
	}
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
    	if(!addNode(this, index, pElement))
			returnAux = 0;
    }
    return returnAux;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* pElementAux;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pElementAux = ll_get(this, index);
    	if(pElementAux != NULL)
    	{
    		returnAux = pElementAux;
    	}
		ll_remove(this, index);
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	void* pElementAux;
    	returnAux = 0;
    	for(int i=0; i<ll_len(this); i++)
    	{
    		pElementAux = ll_get(this, i);
    		if(pElementAux != NULL)
    		{
				if(pElementAux == pElement)
				{
					returnAux = 1;
					break;
				}
    		}
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this, LinkedList* this2)
{
    int returnAux = -1;
    void* pElementThis2;

    if(this != NULL && this2 != NULL)
    {
    	if(ll_len(this) >= 0 && ll_len(this2) >= 0)
    	{
			returnAux = 1;
			int sizeThis2 = ll_len(this2); // obtengo size this2
			int returnNoEsta;

			for (int i=0; i<sizeThis2; i++)
			{
				pElementThis2 = ll_get(this2, i); // obtengo elementos this2
				returnNoEsta = ll_contains(this, pElementThis2);  // verifico si elemento this 2 se encuentra en lista this1
				if(returnNoEsta == 0)
				{
					returnAux = returnNoEsta;
					break;
				}
			}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL && from >= 0 && from < ll_len(this) && to > from && to <= ll_len(this))//&& from < ll_len(this) && to > from && to < ll_len(this)
    {
    	int i;
    	void* pElementAux;
    	cloneArray = ll_newLinkedList();
    	if(cloneArray != NULL)
    	{
			for(i = from; i < to; i++)
			{
				pElementAux = ll_get(this, i);
				ll_add(cloneArray, pElementAux);
			}
    	}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this != NULL)
    {
    	cloneArray = ll_newLinkedList();

    	if(cloneArray != NULL)
    		cloneArray = ll_subList(this, 0, ll_len(this)); // creo nueva lista de 0 a len this.
    }
    return cloneArray;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
/*int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux = -1;
    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
    	int flagSwap;
    	Node* nodeAux;
    	Node* pNode;
    	Node* pNodeDos;

    	if(order == 1)
    	{
    		do
			{
				flagSwap = 0;
				for(int i=0; i<ll_len(this)-1; i++)
				{
					pNode = getNode(this, i);
					pNodeDos = getNode(this, i);

					if(pFunc(pNode->pElement, pNodeDos->pElement) == 1)
					{
						nodeAux = pNode;
						pNode = pNodeDos;
						pNodeDos = nodeAux;

						flagSwap = 1;
					}
				}
			}while(flagSwap);
    	}
    	else
    	{
    		do
			{
				flagSwap = 0;
				for(int i=0; i<ll_len(this)-1; i++)
				{
					pNode = getNode(this, i);
					pNodeDos = getNode(this, i);

					if(pFunc(pNode->pElement, pNodeDos->pElement) == -1)
					{
						nodeAux = pNode;
						pNode = pNodeDos;
						pNodeDos = nodeAux;

						flagSwap = 1;
					}
				}
			}while(flagSwap);
    	}

    	returnAux = 0;
    }
    return returnAux;
}*/
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
        void* pElement;
		void* pElement2;
    	int flagSwap, i;
        int sizeLinkedList = ll_len(this);

        do
        {
            flagSwap = 0;
            for (i = 0; (i < sizeLinkedList-1); i++)
            {
                pElement = ll_get(this, i);
                pElement2 = ll_get(this, i+1);

                if( ((pFunc(pElement, pElement2) < 0) && !order) ||
                    ((pFunc(pElement, pElement2) > 0) &&  order) )
                {
                    ll_set(this, i, pElement2);
                    ll_set(this, i+1, pElement);
                    flagSwap = 1;
                }
            }
        }while(flagSwap);
        returnAux = 0;
    }
    return returnAux;
}
//***********************************************************
/** \brief Busca un elemento
 * \param this LinkedList* Puntero a la lista
 * \param pFuncionBuscar puntero a funcion que busca el elemento
 * \return Node* Retorna  (NULL) Error: si NO encuentró el elemento
                        (pNode) Si SI encuentró el elemento
 *
 */
Node* buscar(LinkedList* this, int (*pFuncionBuscar)(void*))
{
	Node* pNodeAux = NULL;

	if(this != NULL && pFuncionBuscar != NULL)
	{
		pNodeAux = this->pFirstNode; // cargo aux con el PRIMER nodo
		while(pNodeAux != NULL)
		{
			if(!pFuncionBuscar(pNodeAux->pElement))
				break;
			pNodeAux = pNodeAux->pNextNode;
		}
	}
    return pNodeAux;
}
/** \brief Busca un elemento
 * \param this LinkedList* Puntero a la lista
 * \param isFirst 				   	1 es el primer NODO,
 * 									0 no es el primero NODO.
 * \return Node* Retorna  (NULL) Error: si NO encuentró el elemento
                        (pNode) Si SI encuentró el elemento
 *
 */

void* ll_getNext(LinkedList* this, int isFirst)
{
	/* ------------------------ Se usa --------------------------------------

	 pEmpleado = ll_getNext(listaEmpleados, 1) // dame el de la posicion 0
	 while(pEmpleado != NULL)
	 {
		printf("nombre empleado: %s", pEmpleado->nombre); <----- editable, funcion buscar
		pEmpleado = ll_getNext(listaEmpleados, 0) // dame el next
	 }

	   ------------------------ Se usa -------------------------------------- */
    void* returnAux = NULL;
    static Node* pNodeAux;

    if(this != NULL && (isFirst == 1 || isFirst == 0))
    {
    	if(isFirst == 1)
    	{
    		pNodeAux = getNode(this, 0);
    		if(pNodeAux != NULL)
			{
				returnAux = pNodeAux->pElement;
			}
    	}
    	else
    	{
			if(pNodeAux != NULL)
			{
				pNodeAux = pNodeAux->pNextNode;
				if(pNodeAux != NULL)
				{
					returnAux = pNodeAux->pElement;
				}
			}
    	}
    }
    return returnAux;
}

int ll_reduceIntDos(LinkedList* this, int (*pFunc)(void*, void*), void* argumento)
{
	void* pAux;
	int i;
	int acumulador = 0;

	if (this != NULL && pFunc != NULL && argumento != NULL)
	{
		for(i=0; i<ll_len(this); i++)
		{
			pAux = ll_get(this, i);
			if(pAux != NULL)
			{
				acumulador += pFunc(pAux, argumento);
			}
		}
	 /* pAux = ll_getNext(this, 1); // dame el de la posicion 0
	    while(pAux != NULL)
	    {
			acumulador += pFunc(pAux, argumento);
			pAux = ll_getNext(this, 0); // dame el next
	    } */
	}
	return acumulador;
}


