#include "..\Headers\Precom.h"
#include "..\Headers\Grafo.h"

using namespace std;
template<typename TD>
Grafo<TD>::Grafo()
{
	hashNodo.max_load_factor(.65f);// Se estable un valor de carga maximo del 65%, para evitar colisiones.
	hashArista.max_load_factor(.65f);// Se estable un valor de carga maximo del 65%, para evitar colisiones.
	pos = 0;
				
	return;
}

template<typename TD>
bool Grafo<TD>::insertarNodo(string _nombreN, TD _dato)// Inserta nodos(verticies) en una tabla hash.
{
	
	typedef pair<string, nodoV*> par;// sustituye todo lo que esta antes de par, por ese mismo nombre.
	auto iter = hashNodo.find(_nombreN); //unordered_map<string, nodoV*>::iterator iter; pero no funciono por eso utilice auto.	
	
	if (iter == hashNodo.end())
	{// Como no se encotro la clave en la tabla, entonces se crea un nodo o verticie.

		nuevoNodo = new nodoV();// Se crea espacio en memoria heap para guardar un nuevo nodo.
		nuevoNodo->nombreV = _nombreN;
		nuevoNodo->dato = _dato;
		hashNodo.insert(par (_nombreN, nuevoNodo));// Insertar utilizando un metodo de la clase y usando typedef.
		//hashNodo.insert({ "a",nuevoNodo }); // Insertar utilizando metodo pero haciendo el par con llaves	
		//hashNodo["merga"] = nuevoNodo; // Insertar con el operador[] como si fuera un vector o arreglo.
		return true;
	}
	else
	{
		// Como se encontro una clave o nombre igual no se puede insertar, por eso genera un false.
		return false;
	}
	
}

template<typename TD>
bool Grafo<TD>::buscarNodo(string _nombreN)
{
	// Ingresa el nombre o clave del nodo que se busca.

	auto iter1 = hashNodo.find(_nombreN); // Se crea un iterador para buscar un nodo en la tabla hash
	if (iter1 != hashNodo.end() )// Para saber si existe el nodo o vertice que se busca.
		return true; // Si se encontro el nodo buscado 
	else
		return false;// No se encontro el nodo.
}

template<typename TD>
bool Grafo<TD>::sonAdyacentes(string _nodo1, string _nodo2)
{
	// nodo1, nodo2--> Nombre o clave de nombre que se va analizar.

	if (buscarNodo(_nodo1) && buscarNodo(_nodo2))
	{ 
		//Entra aqui cuando existen los 2 nodos buscados.

		nuevoNodo = hashNodo.at(_nodo1);// Para obtener la direccion del puntero donde se encuentra la clave buscada.
		if(nuevoNodo->edge==nullptr)
			return false;// no hay nodos adyacentes.
		else
			return _recorrerLista(nuevoNodo->edge, _nodo2);
	}
	else
		return false;// Como almenos uno de los dos nodos no exite por eso no puede haber adyacencia.
}

template<typename TD>
bool Grafo<TD>::unir2Nodos(string _nodo1, string _nodo2, string _nArista, int _peso)
{
	// nodo1-----> Ingresa el nombre de un nodo que ya debe de estar en el grafo.
	// nodo2-----> Ingresa el nombre de un nodo que ya debe de estar en el grafo.
	// nVertice--> Ingresa el nombre que se le va asignar al vertice que se va a crear.

	if (buscarNodo(_nodo1) && buscarNodo(_nodo2) && !sonAdyacentes(_nodo1,_nodo2))// Saber si existen los dos nodos y ademas no son adyacentes
	{
		// Entra porque existen los nodos y no estan unidos.
		
		nuevaArista = new aristaE();//--------> Crea espacio en memoria Heap.
		nuevaArista->nombreA = _nArista;//----> Se le asigna nombre a la nueva arista.
		nuevaArista->peso = _peso;
	
		nuevoNodo = hashNodo.at(_nodo1);// obtener la direccion del nodo 1
		nuevaArista->nodo1 = nuevoNodo; //----> Se conecta el nodo 1
		nuevoNodo->edge = nuevaArista;  //----> El nodo apunta a su arista.

		nuevoNodo = hashNodo.at(_nodo2);//----> Obtener la direccion del nodo 2.
		nuevaArista->nodo2 = nuevoNodo;//-----> Se conecta el nodo 2.
		nuevoNodo->edge = nuevaArista;  //----> El nodo apunta a su arista.


		return true;
	}
	else
		return false;
}


//------------------------------- FUNCIONES AUXILIARES PRIVADAS ---------------------------//

template<typename TD>
bool Grafo<TD>::_recorrerLista(aristaE*& p_arista, string& _nodo2) // Regresa true si se encuentra el nombre del nodo 2 en la lista de aristas de nodo1.
{
	//p_arista--> Tiene la direccion de la primer arista que se va a comparar.
	//nodo2---> Ingresa la clave o nombre del nodo que se quiere saber si es adyacente.

	if (p_arista == nullptr)
		return false;// no hay nodos adyacentes.
	else
	{
		//p_nodo->edge->nodo1->nombreV
		if (p_arista->nodo1->nombreV == _nodo2 || p_arista->nodo2->nombreV == _nodo2)// Busca dentro de la arista para saber si hay conectado un nodo con el nombre de la clave que se quiere conectar.
			return true;
		else
		{
			p_arista = p_arista->sig;// Para avanzar en la lista.
			return _recorrerLista(p_arista, _nodo2);
		}
	}

}