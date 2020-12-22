#include "..\Headers\Precom.h"
#include "..\Headers\Grafo.h"

using namespace std;
template<typename TD>
Grafo<TD>::Grafo()
{
	nuevaArista = nullptr;
	nuevoNodo = nullptr;
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

		nuevoNodo = hashNodo.at(_nodo1);//---> Para obtener la direccion del puntero donde se encuentra la clave buscada.
		
		if(nuevoNodo->setLista.empty())//----> Revisa si hay nodos en la lista.
			return false;// no hay nodos adyacentes.
		else
			return _listaBuscar(nuevoNodo, _nodo2);
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

		//--------------NODO 1 ---------------------//
	
		nuevoNodo = hashNodo.at(_nodo1);//----> obtener la direccion del nodo 1
		nuevaArista->nodo1 = nuevoNodo; //----> Se conecta el nodo 1
		nuevoNodo->setLista.insert(nuevaArista->nombreA);//Inserta la arista en la lista del nodo.
		//_pushArista(nuevoNodo, nuevaArista);//> Inserta en la lista de aristas del nodo. 
		
		//--------------NODO 2 ---------------------//

		nuevoNodo = hashNodo.at(_nodo2);//----> Obtener la direccion del nodo 2.
		nuevaArista->nodo2 = nuevoNodo;//-----> Se conecta el nodo 2.
		nuevoNodo->setLista.insert(nuevaArista->nombreA);//Inserta la arista en la lista del nodo.
		//_pushArista(nuevoNodo, nuevaArista);//> Inserta en la lista de aristas del nodo.


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
		nodoV* _p_nodo = hashNodo.at(_nodo);//-----> Para obtener la direccion del nodo a borrar.

		set<string>::iterator iter;
		for (iter = _p_nodo->setLista.cbegin(); iter != _p_nodo->setLista.cend();)// Para recorrer todo el arreglo de aristas de _p_nodo.
		{
			//nuevaArista = hashArista.at(*iter);//--> iter tiene la clave no nombre de la arista y se utiliza para saber su direccion en el arrglo.
			borrarArista(*iter);
			iter = _p_nodo->setLista.cbegin();//Se tiene que inicializar el iterador, debido que en borrar lista se modifica setLista, borrando en ella una clave.
			
		}
		
		delete _p_nodo;// -------------------------> Borra el nodo a eliminar de la heap memory.
		_p_nodo = nullptr;
		hashNodo.erase(_nodo);//-------------------> Borra el nodo de la lista hash de nodos.
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

		// --- Borra la arista en cada lista de los dos nodos----//
		nuevaArista->nodo1->setLista.erase(_claveA);
		nuevaArista->nodo2->setLista.erase(_claveA);
			
		//------- Se libera memoria heap donde se encuntra la arista a borrar.--------//
		
		nuevaArista->nodo2= nullptr;
		nuevaArista->nodo1= nullptr;
		delete nuevaArista;//--------> Se libera esa posicion de memori hash.
		nuevaArista = nullptr;//-----> Se apunta a null para evitar desreferenciar un puntero que no apunta a nada.
		hashArista.erase(_claveA);//--------------------------> Elimina la clave de la tabla hash.
		return true;
	}
	else
		return false;
}

template<typename TD>
bool Grafo<TD>::kruskalAlgorithm()
{
	if (hashArista.size() > 0)// Hay almenos una arista.
	{
		_inicializarNodo();
		_ordenarAristas();// Inserta las aristas en un multimap que ademas las ordena por peso.
		for (auto iter = aristasOrdenadas.begin(); iter != aristasOrdenadas.end(); iter++)// Recorre todo el arreglo de aristas (multimap).
		{
			// aristasOrdenadas first--> peso, second--> string;

			nuevaArista = hashArista.at(iter->second);// Se obtiene la direccion de la arista por medio de su nombre.
			_unionNodoKruskal(nuevaArista);
		}
		return true;

	}
	else
		return false;
}

template<typename TD>
bool Grafo<TD>::primsAlgorithm(const string& _inicio)
{
	// inicio--> Recibe el nombre del nodo donde se va iniciar el algoritmo.

	if (hashArista.size()>0)// Verifica que haya por lo menos una arista.
	{
		_inicializarNodo();
		unsigned int contaNodos=0;// Para saber cuantos nodos se han visitados.
		nodoV* nodop=nullptr;
		aristasOrdenadas.clear();//---------------> Incializa el contenedor en caso de que haya sido utilizado antes.
		nodop = hashNodo.at(_inicio);//-----------> Se obtiene la direccion del nodo en el que se va inciar.
		nodop->sig = nodop;//---------------------> Se auto apunta para convertirse en nodo clave del conjunto.
		_agregarAristaPrism(nodop);//-------------> Guarda en aristas ordenadas las aristas del nodo enviado.
		auto i = aristasOrdenadas.begin();//------> Se obtien el puntero a la primera posision del arreglo de aristas.
		nuevaArista = hashArista.at(i->second);//->
		contaNodos++;// Se visito el primer nodo.
		_unionNodoPrim(nuevaArista);
		if (nuevaArista->nodo1->nombreV != nodop->nombreV)// Se agregan las aristas del segundo nodo.
			_agregarAristaPrism(nuevaArista->nodo1);
		else
			_agregarAristaPrism(nuevaArista->nodo2);
		contaNodos++;//---------------------> Se visito el segundo nodo.

		//NOTA: Como no se borran las aristas repetidas, el while se va ejecutar 2 veces extra para borrarlas
				
		while (hashNodo.size()>contaNodos)// Para saber si se visitaron todos los nodos.
		{
			//multimap<int, string> iter = aristasOrdenadas.begin();
			auto iter = aristasOrdenadas.begin();// Se obtien el puntero a la primera posision del arreglo de aristas.
			aristaE *aristap = hashArista.at(iter->second);
			string claveA = iter->second;// Guarda el nombre de la arista que se va agregar.
			
			if (aristap->nodo1->sig == nullptr)
				nodop = aristap->nodo1;// Toma la direccion del nodo que se va a copiar su lista de aristas.
			else if (aristap->nodo2->sig == nullptr)
				nodop = aristap->nodo2;// Toma la direccion del nodo que se va a copiar su lista de aristas.
			
			if (_unionNodoPrim(aristap))
			{
				if (aristap->nodo1 == nodop)
					_agregarAristaPrism(aristap->nodo1);
				else if (aristap->nodo2 == nodop)
					_agregarAristaPrism(aristap->nodo2);
				else
					break;// En caso de un error.
				
				int conta = 0;
				auto interno = aristasOrdenadas.find(aristap->peso);// Busca la arista por medio de la clave del mapa, que en este caso es el peso.
				while (conta < 2)
				{
					if (interno->second == claveA)
					{
						aristasOrdenadas.erase(interno);//Borra solo la posision a la que apunta el iterador.
						interno = aristasOrdenadas.begin();
						conta++;

						
					}
					else
						interno++;
				}
				contaNodos++;// 

			}
			else
			{
				// No se pudo insertar la arista a la que apunta el iterador.
				aristasOrdenadas.erase(iter);// Se borra la clave para poder avanzar en el arreglo.
			}

		}
		return true;

		

	}
	else
		return false;
}

template<typename TD>
int Grafo<TD>::pesoKruskal()
{
	int sum = 0;
	if (listKruskal.size() > 0)
	{
		for (auto iter = listKruskal.begin(); iter != listKruskal.end(); iter++)
		{
			nuevaArista = hashArista.at(*iter);
			sum += nuevaArista->peso;
		}
		return sum;
	}
	else
		return 0;
}

template<typename TD>
int Grafo<TD>::pesoPrim()
{
	int sum = 0;
	if (listaPrim.size() > 0)
	{
		for (auto iter = listaPrim.begin(); iter != listaPrim.end(); iter++)
		{
			nuevaArista = hashArista.at(*iter);
			sum += nuevaArista->peso;
		}
		return sum;
	}
	else
		return 0;
}


//----------------------------------- FUNCIONES AUXILIARES PRIVADAS --------------------------------//

template<typename TD>
bool Grafo<TD>::_listaBuscar(nodoV*& _p_nodo, string& _nodo2) // Regresa true si se encuentra el nombre del nodo 2 en la lista de aristas de nodo1.
{
	//p_nodo--> Tiene la direccion del primer nodo que se va a comparar.
	//nodo2---> Ingresa la clave o nombre del nodo que se quiere saber si es adyacente.

	set<string>::iterator iter;

	for (iter = _p_nodo->setLista.cbegin(); iter != _p_nodo->setLista.cend(); ++iter)// Para recorrer todo el arreglo de aristas de _p_nodo.
	{
		nuevaArista = hashArista.at(*iter);//----> iter tiene la clave no nombre de la arista y se utiliza para saber su direccion en el arrglo.

		if (nuevaArista->nodo1->nombreV == _nodo2 || nuevaArista->nodo2->nombreV == _nodo2)// Si se encuntra el nombre del _nodo2 significa que es adyacente.
			return true;
	}
	return false;// Como termino de recorrer el arreglo quiere decir que no hay adyacencia.

}

template<typename TD>
bool Grafo<TD>::_ordenarAristas()
{
	aristasOrdenadas.clear();// Como este contenedor se va utilizar en diferentes funciones, se debe limpiar para evitar errores.
	typedef pair<int, string> par;
	for (auto iter = hashArista.begin(); iter!= hashArista.end(); iter++)// Recorre todo el arreglo de aristas.
	{		
		aristasOrdenadas.insert(par(iter->second->peso, iter->first));// Guarda le peso y con ese se ordena y el nombre de la clave.
	}
	return true;
}

template<typename TD>
bool Grafo<TD>::_unionNodoKruskal(aristaE*& _arista)
{

	if (_arista->nodo1->sig == nullptr && _arista->nodo2->sig == nullptr)
	{
		//Como no pertence a ningun conjunto se hace la union y se agrega a lista de kruskal 

		_arista->nodo1->sig = _arista->nodo1;//-----------> El nodo 1 se convierte en la clave de este conjunto.
		_arista->nodo2->sig = _arista->nodo1->sig;//------> El nodo 2 se une a ese conjunto apuntado a lo que apunte sig del nodo clave.
		listKruskal.push_back(_arista->nombreA);//--------> Se inserta la arista que formara parte del MST
		return true;
	}
	else
	{
		if (_arista->nodo1->sig != nullptr && _arista->nodo2->sig == nullptr)// Nodo 1 pertenece a un conjunto y nodo 2 no pertenece a ningun conjuno.
		{
			_arista->nodo2->sig = _arista->nodo1->sig;//-----> El nodo 2 apunta a el puntero sig de el nodo clave del conjunto.
			listKruskal.push_back(_arista->nombreA);//---> Se inserta la arista que formara parte del MST
			return true;
		}
		else if (_arista->nodo1->sig == nullptr && _arista->nodo2->sig != nullptr)//-------> Nodo 2 pertenece a un conjunto por eso se 
		{
			// Como nodo 1 esta vacio se conecta al conjunto de nodo 2
			_arista->nodo1->sig = _arista->nodo2->sig;//------------> Nodo 1 se conecta a sig de nodo 2, que es el nodo clave.
			listKruskal.push_back(_arista->nombreA);//---> Se inserta la arista que formara parte del MST
			return true;
		}
		else// Ambos nodos apuntan a algo diferente de nullptr.
		{
			if (_arista->nodo1->sig->nombreV != _arista->nodo2->sig->nombreV)// Verifica los nombres de los nodos claves para saber si pertence al mismo conjunto.
			{

				typedef pair<int, string> par;
				for (auto iter = hashNodo.begin(); iter != hashNodo.end(); iter++)// Recorre todo el hashNodo
				{
					if (iter->second != _arista->nodo1 && iter->second != _arista->nodo2)
					{
						if (iter->second->sig != nullptr)//En caso de que sig apunte a null, no se podria comparar con una cadena.
						{
							if (iter->second->sig->nombreV == _arista->nodo2->sig->nombreV)//Para saber si hay nodo que estan conectados al nodo que se va a unir 
								iter->second->sig = _arista->nodo1->sig;// Actualiza la direccion de los nodos que se van a unir.
						}

					}

				}
				_arista->nodo2->sig = _arista->nodo1->sig; //--> Actualiza el puntero sig.
				listKruskal.push_back(_arista->nombreA);//----------> Se inserta la arista que formara parte del MST
				return true;



			}
			else
			{
				// Como pertenecen al mismo conjunto no se agrega al MST
				return false;
			}
		}

	}
	return false;
}

template<typename TD>
bool Grafo<TD>::_unionNodoPrim(aristaE*& _arista)
{
	if (_arista->nodo1->sig == nullptr && _arista->nodo2->sig == nullptr)
	{
		//Como no pertence a ningun conjunto se hace la union y se agrega a lista de kruskal 

		_arista->nodo1->sig = _arista->nodo1;//-----------> El nodo 1 se convierte en la clave de este conjunto.
		_arista->nodo2->sig = _arista->nodo1->sig;//------> El nodo 2 se une a ese conjunto apuntado a lo que apunte sig del nodo clave.
		listaPrim.push_back(_arista->nombreA);//--------> Se inserta la arista que formara parte del MST
		
		return true;
	}
	else
	{
		if (_arista->nodo1->sig != nullptr && _arista->nodo2->sig == nullptr)// Nodo 1 pertenece a un conjunto y nodo 2 no pertenece a ningun conjuno.
		{
			_arista->nodo2->sig = _arista->nodo1->sig;//-----> El nodo 2 apunta a el puntero sig de el nodo clave del conjunto.
			listaPrim.push_back(_arista->nombreA);//---> Se inserta la arista que formara parte del MST
			return true;
		}
		else if (_arista->nodo1->sig == nullptr && _arista->nodo2->sig != nullptr)//-------> Nodo 2 pertenece a un conjunto por eso se 
		{
			// Como nodo 1 esta vacio se conecta al conjunto de nodo 2
			_arista->nodo1->sig = _arista->nodo2->sig;//------------> Nodo 1 se conecta a sig de nodo 2, que es el nodo clave.
			listaPrim.push_back(_arista->nombreA);//---> Se inserta la arista que formara parte del MST
			return true;
		}
		else// Ambos nodos apuntan a algo diferente de nullptr.
		{
			if (_arista->nodo1->sig->nombreV != _arista->nodo2->sig->nombreV)// Verifica los nombres de los nodos claves para saber si pertence al mismo conjunto.
			{

				typedef pair<int, string> par;
				for (auto iter = hashNodo.begin(); iter != hashNodo.end(); iter++)// Recorre todo el hashNodo
				{
					if (iter->second != _arista->nodo1 && iter->second != _arista->nodo2)
					{
						if (iter->second->sig != nullptr)//En caso de que sig apunte a null, no se podria comparar con una cadena.
						{
							if (iter->second->sig->nombreV == _arista->nodo2->sig->nombreV)//Para saber si hay nodo que estan conectados al nodo que se va a unir 
								iter->second->sig = _arista->nodo1->sig;// Actualiza la direccion de los nodos que se van a unir.
						}

					}

				}
				_arista->nodo2->sig = _arista->nodo1->sig; //--> Actualiza el puntero sig.
				listaPrim.push_back(_arista->nombreA);//----------> Se inserta la arista que formara parte del MST
				return true;



			}
			else
			{
				// Como pertenecen al mismo conjunto no se agrega al MST
				return false;
			}
		}

	}
	return false;
	return false;
}

template<typename TD>
bool Grafo<TD>::_agregarAristaPrism(nodoV* _nodo)
{

	if (_nodo->setLista.size() > 0)
	{
		
		for (set<string>::iterator it = _nodo->setLista.begin(); it != _nodo->setLista.end(); it++)// Se agregan las aristas que contiene el nodo.
		{
			nuevaArista = hashArista.at(*it);// Obtengo la direccion de la arista en memoria.
			aristasOrdenadas.insert(pair<int,string>(nuevaArista->peso, nuevaArista->nombreA));// Se insertan ordenas por peso.
		}
		return true;
	}
	else
		return false;

	
}

template<typename TD>
bool Grafo<TD>::_inicializarNodo()
{
	if (hashNodo.size() > 1)
	{
		for (auto iter = hashNodo.begin(); iter != hashNodo.end(); iter++)
			iter->second->sig = nullptr;
		return true;
	}
	else
		return false;
}

