/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __LINKEDLIST
#define __LINKEDLIST
struct Node
{
    void* pElement; // puntero que almacena ese lugar
    struct Node* pNextNode; // direccion de memoria del segundo
}typedef Node;

struct LinkedList
{
    Node* pFirstNode; // hacia donde apunta el primer nodo. el primer lugar de la lista.
    /*la primera ves va a ser NULL*/
    int size;/*PRIMERA VES: 0
    */
}typedef LinkedList;
#endif
/*3 instancias*/


//Publicas
LinkedList* ll_newLinkedList(void);
int ll_len(LinkedList* this);
Node* test_getNode(LinkedList* this, int nodeIndex);
int test_addNode(LinkedList* this, int nodeIndex,void* pElement);
int ll_add(LinkedList* this, void* pElement); // agrega elemento al final
void* ll_get(LinkedList* this, int index); // lo pedimos para agregar
/*
 Employee* pAuxEmpleado;
 pAuxEmpleado = (Employee*) ll_get(listaEmpleados,4);
 */
int ll_set(LinkedList* this, int index,void* pElement);
/* en la posicion tal, en tanto exista. guardame este elemento
 para cambiar el puntero */
int ll_remove(LinkedList* this,int index);
// le decimos un indice y elimina ese elemento
int ll_clear(LinkedList* this);
// borra todos los elementos de la lista pero la deja activa
int ll_deleteLinkedList(LinkedList* this);
// borra en memoria de la lista, primero un clear y desps delete
int ll_indexOf(LinkedList* this, void* pElement);

int ll_isEmpty(LinkedList* this);
// si la lista está vacia o podes preg al len si esta 0
int ll_push(LinkedList* this, int index, void* pElement);
// epermite elegir un lugar para agregar un elemento, set permite cambiar lo q hay en la posicion
// el push permite insertar en una posicion un eelemeento
void* ll_pop(LinkedList* this,int index);
// sacar elemento de la lista, pero al sacarlo te devuelve ese puntero
// sirve para hacer tareas, realizarla y desps ir sacando lo q ya hiciste
int ll_contains(LinkedList* this, void* pElement);
int ll_containsAll(LinkedList* this,LinkedList* this2);
LinkedList* ll_subList(LinkedList* this,int from,int to);
// de una lista original hacer una sublista para hacer algo
LinkedList* ll_clone(LinkedList* this);
// duplicar la lista en memoria, genera una lista nueva y clona lo de la original
// para laburarla y q no afecte la original
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);
// ordenar la lista
