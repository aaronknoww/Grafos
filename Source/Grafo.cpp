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
bool Grafo<TD>::buscarArista(string _nombreA)
{
	// _nombreA--> Recibe el nombre de la arista que se va a buscar.

	auto iter1 = hashArista.find(_nombreA); // Se crea un iterador para buscar un nodo en la tabla hash
	if (iter1 != hashArista.end())// Para saber si existe el nodo o vertice que se busca.
		return true; // Si se encontro la Arista.
	else
		return false;// No se encontro la Arista.
	
}

template<typename TD>
bool Grafo<TD>::sonAdyacentes(string _nodo1, string _nodo2)
{
	// nodo1, nodo2--> Nombre o clave de nombre que se va analizar.

	if (buscarNodo(_nodo1) && buscarNodo(_nodo2))
	{ 
		//Entra aqui cuando existen los 2 nodos buscados.

		nuevoNodo = hashNodo.at(_nodo1);// Para obtener la direccion del puntero donde se encuentra la clave buscada.
		if(nuevoNodo->listaEdge==nullptr)
			return false;// no hay nodos adyacentes.
		else
			return _listaBuscar(nuevoNodo->listaEdge, _nodo2);
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

	if (buscarNodo(_nodo1) && buscarNodo(_nodo2) && !sonAdyacentes(_nodo1,_nodo2) && !buscarArista(_nArista))// Saber si existen los dos nodos y ademas no son adyacentes
	{
		// Entra porque existen los nodos y no estan unidos, ademas el nombre de la arista no existe.
		
		nuevaArista = new aristaE();//--------> Crea espacio en memoria Heap.
		nuevaArista->nombreA = _nArista;//----> Se le asigna nombre a la nueva arista.
		nuevaArista->peso = _peso;
	
		nuevoNodo = hashNodo.at(_nodo1);//----> obtener la direccion del nodo 1
		nuevaArista->nodo1 = nuevoNodo; //----> Se conecta el nodo 1
		_pushArista(nuevoNodo, nuevaArista);//> Inserta en la lista de aristas del nodo. 
		
		nuevoNodo = hashNodo.at(_nodo2);//----> Obtener la direccion del nodo 2.
		nuevaArista->nodo2 = nuevoNodo;//-----> Se conecta el nodo 2.
		_pushArista(nuevoNodo, nuevaArista);//> Inserta en la lista de aristas del nodo.

		hashArista[_nArista] = nuevaArista;//-> Insertar con el operador[] como si fuera un vector o arreglo.
		return true;
	}
	else// En este else, se podrian generar alertas para indicar porque no se pudo crear la union.
		return false;
}

template<typename TD>
bool Grafo<TD>::eliminarNodo(string _nodo)
{
	// _nodo---> Recibe el nombre del nodo que se quiere eliminar.
	if (buscarNodo(_nodo))
	{
		return true;
	}
	else
		return false;
}

template<typename TD>
bool Grafo<TD>::borrarArista(string _claveA)
{
	//claveA---> Ingresa el nombre o clave de la arista que se va eliminar.

	if (buscarArista(_claveA))
	{
		// Entra porque si existe esa clave o arista.
		
		nuevaArista = hashArista.at(_claveA);//--------> Para obtener la direccion del puntero donde se encuentra la clave buscada.

		//nuevaArista->nodo1->listaEdge--> la direccion del primer arista de la listaEdge.
		_desconectarA(nuevaArista->nodo1->listaEdge, _claveA);//-----> desconecta la arista del nodo1
		_desconectarA(nuevaArista->nodo2->listaEdge, _claveA);//-----> desconecta la arista del nodo2

		//------- Se libera memoria heap donde se encuntra la arista a borrar.--------//
		nuevaArista->nodo2= nullptr;
		nuevaArista->sig  = nullptr;
		nuevaArista->nodo1= nullptr;
		delete nuevaArista;//--------> Se libera esa posicion de memori hash.
		nuevaArista = nullptr;//-----> Se apunta a null para evitar desreferenciar un puntero que no apunta a nada.
		
		hashArista.erase(_claveA);//--------------------------> Elimina la clave de la tabla hash.
		return true;
	}
	else
		return false;
}


//----------------------------------- FUNCIONES AUXILIARES PRIVADAS --------------------------------//

template<typename TD>
bool Grafo<TD>::_listaBuscar(aristaE* p_arista, string& _nodo2) // Regresa true si se encuentra el nombre del nodo 2 en la lista de aristas de nodo1.
{
	//p_arista--> Tiene la direccion de la primer arista que se va a comparar.
	//nodo2---> Ingresa la clave o nombre del nodo que se quiere saber si es adyacente.

	if (p_arista == nullptr)
		return false;// no hay nodos adyacentes.
	else
	{
		
		if (p_arista->nodo1->nombreV == _nodo2 || p_arista->nodo2->nombreV == _nodo2)// Busca dentro de la arista para saber si hay conectado un nodo con el nombre de la clave que se quiere conectar.
			return true;
		else
		{
			p_arista = p_arista->sig;// Para avanzar en la lista.
			return _listaBuscar(p_arista, _nodo2);
		}
	}

}

template<typename TD>
bool Grafo<TD>::_pushArista(nodoV* _nodo, aristaE* _arista)// Inserta una arista en la lista de aristas del nodo involucrado.
{
	// _nodo----> Recibe la el puntero del nodo en el que se va a conectar la arista.
	// _arista--> Recibe el puntero de la arista que va ingresar en la lista de aristas del nodo.

	if (_nodo->listaEdge == nullptr)
	{
		_nodo->listaEdge = _arista;// Como no hay aristas, por eso se conecta directo.
		return true;
	}
	else
	{
		//nodoV* aux;
		//aux = new nodoV();
		
		aristaE* aux = nullptr;
		aux = _nodo->listaEdge;//---> Auxiliar toma la direccion de la lista del nodo para no perderla
		_nodo->listaEdge = _arista;// ----> Se inserta la Arista en al inicio de la lista.
		_nodo->listaEdge->sig = aux;//----> Se concta la arista nueva a la lista que ya existia.
		return true;
	}
	return false;
}

template<typename TD>
bool Grafo<TD>::_desconectarA(aristaE*& _inicioL, string& _nArista)// Desconecta la arista en la lista de un nodo.
{
	// inicioL---> Recibe la direccion inicial de la lista para empezar a recorrerla.
	// nArista---> Nombre de la arista que se va a desconectar de la lista de aristas del nodo.

	if (_inicioL->nombreA == _nArista)
	{
		//Entra porque es la arista que se va a desconectar.
		_inicioL = _inicioL->sig;//---> Conceta con lo que haya despues de la arista que se va a desconectar.
		return true;
	}
	else
		return _desconectarA(_inicioL = _inicioL->sig, _nArista);// Avanza a la siguiente posicion de la lista.
		
	return false;
}
