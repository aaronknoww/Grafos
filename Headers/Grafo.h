#pragma once
#include "../Headers/Precom.h"// precompiled header

constexpr auto inicial = 10; // Define la cantidad de espacios en memoria que se van a crear para las tablas.;
using namespace std;

template<typename TD>
class Grafo
{
public:
	Grafo();
	bool insertarNodo(string, TD );
	bool buscarNodo(string);//----------------------> Regresa true si se encuentra el nodo buscado.
	bool buscarArista(string);//--------------------> Regresa un true, si la arista se encuntra guaradada en su tabla.
	bool sonAdyacentes(string, string); //----------> Regresa true si los nodos estan unidos mediante una arista.
	bool unir2Nodos(string, string, string, int);//-> Recibe el nombre del nodo1 y del nodo2, ademas del nombre del vertice.
	bool eliminarNodo(string);//--------------------> Elimina un nodo(vertice) y borra todas sus aristas y conecciones.
	bool borrarArista(string);//--------------------> Elimina la arista y todos los punteros relacionados asi como actualiza la lista de edge, de los nodo. 
	bool kruskalAlgorithm();//----------------------> Ejecuta ese algoritom para calcular el MST del grafo.

	vector<string> listKruskal;//-------------------> Guarda las aristas que forman el minimum spanning tree.
private:
	class aristaE;//--> Para que el compilador sepa que existe esa clase antes de implementarla
	class nodoV //----> Clase para crear los vertices o nodos de un grafo.
	{
	public:

		//nodoV(string nombre) : nombre(nombre), nodoSig(nullptr), dato(0){}
		//~nodoV();
		
		nodoV() : nombreV(), dato(0), sig(nullptr){}
		string nombreV;
		TD dato;
		nodoV* sig;//-------> Para poder enlazar los nodos y hacer conjuntos.
		set<string> setLista;// Se guarda el nombre o clave de las aristas que tiene el nodo.
		

	
	private:

	};
	class aristaE
	{
	public:
		aristaE(): nombreA(), peso(0), nodo1(nullptr), nodo2(nullptr){}

		string nombreA;
		int peso;
		nodoV * nodo1; // Guarda la direccion del nodo1 o vertice que se conecta en esta arista
		nodoV * nodo2; // Guarda la direccion del nodo2 o vertice que se conecta en esta arista
	};
	
	unordered_map<string, nodoV*> hashNodo;//-------> Se utiliza una tabla hash para guardar los nodos utilizando su nombre.
	unordered_map<string, aristaE*> hashArista;//---> Se utiliza una tabla hash para guardar las aristas
	multimap<int, string> aristasOrdenadas;//--------> Guarda el peso y el nombre de las aristas ademas de ordenarlas. 
	
	nodoV* nuevoNodo;//Poder insertar nodos.
	aristaE* nuevaArista;// Poder insertar Aristas.
	int pos;
	
	//--------------------------------- FUNCIONES PRIVADAS -------------------------------------//

	bool _listaBuscar(nodoV*&, string&);//--------> Busca en la lista de aristas del nodo.
	bool _ordenarAristas();//---------------------> Ordena todas las aristas guardadas hasta el momento.
	bool _unionNodo(aristaE*&);//-----------------> Verifica si se puede unir los nodos y los agrega a lista kruskal
	
};