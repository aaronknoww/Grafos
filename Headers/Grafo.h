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
private:
	class aristaE;//--> Para que el compilador sepa que existe esa clase antes de implementarla
	class nodoV //----> Clase para crear los vertices o nodos de un grafo.
	{
	public:

		//nodoV(string nombre) : nombre(nombre), nodoSig(nullptr), dato(0){}
		//~nodoV();
		
		nodoV() : nombreV(), nodoSig(nullptr), listaEdge(nullptr), dato(0){}
		string nombreV;
		TD dato;
		nodoV* nodoSig; // por si es nencesario enlazar  un nodo
		aristaE* listaEdge;
	
	private:

	};
	class aristaE
	{
	public:
		aristaE(): nombreA(), peso(0), nodo1(nullptr), nodo2(nullptr), sig(nullptr){}

		string nombreA;
		int peso;
		nodoV * nodo1; // Guarda la direccion del nodo1 o vertice que se conecta en esta arista
		nodoV * nodo2; // Guarda la direccion del nodo2 o vertice que se conecta en esta arista
		aristaE* sig; //  Para poder enlazar otro nodo.
	};
	
	unordered_map<string, nodoV*> hashNodo; // Se utiliza una tabla hash para guardar los nodos utilizando su nombre.
	unordered_map<string, aristaE*> hashArista;// Se utiliza una tabla hash para guardar las aristas
	
	nodoV* nuevoNodo;//Poder insertar nodos.
	aristaE* nuevaArista;// Poder insertar Aristas.
	int pos;
	
	//--------------------------------- FUNCIONES PRIVADAS -------------------------------------//

	bool _listaBuscar(aristaE*, string&);// Busca en la lista de aristas del nodo.
	bool _pushArista(nodoV*, aristaE*); // Regresa true cuando la arista se conceta en la pila del nodo.
	bool _desconectarA(aristaE*&, string&);// Recorre lista de arista y ademas borra la arista buscada, ademas reconecta en caso de ser necesario.
	
};