#include "../Headers/Precom.h"// precompiled header
#include "../Headers/Grafo.h"
#include "..\Source\Grafo.cpp"

//By Aaron Knoww

using namespace std;

int main()
{
	//Myhash<int> tabla;
	
	Grafo<int> G;
	vector<int> vec;
	vec.push_back(1125);

	
	G.insertarNodo("Aaron", 19);
	G.insertarNodo("Knoww", 14);
	G.insertarNodo("Cruz", 19);
	G.insertarNodo("Azul", 14);
	G.unir2Nodos("Aaron", "Knoww","A1",10);
	G.unir2Nodos("Aaron", "Azul","A2",10);
	//NOTA
	//probar si se inserta nodo A-B y B-A que solo se pueda insertar 1.------ LISTO
	//falta probar cuando se insertan mas de dos nodos y saber si son adyacentes.---- LISTO
	//Ejecutar el programa asi como esta y ver si se borra la listaEdge de Aaron.-- listo

	//Falta eliminar nodo y arista. borrando todos los punteros que sea nesesario borrar.


	
	if (G.unir2Nodos("Aaron", "Cruz", "A3", 10))
		cout << "\n\n union correcta" << endl;
	else
		cout << "\n\nNo se pudo unir esos nodos" << endl;
	if (G.unir2Nodos("Azul", "Cruz", "A4", 10))
		cout << "\n\n union correcta" << endl;
	else
		cout << "\n\nNo se pudo unir esos nodos" << endl;
	
	/*G.insertarNodo("Knoww", 14);
	G.sonAdyacentes("Aaron", "Knoww");
	if (G.buscarNodo("Aaroon"))
		cout << "\n Si existe el nodo o vertice";
	else
		cout << "\n No existe el nodo o vertice";*/

	cout << "\nhello mother fuckers, Aaron Knoww was here" << endl;
	
	system("pause > null");
	return 0;
}
