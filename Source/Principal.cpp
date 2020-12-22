#include "../Headers/Precom.h"// precompiled header
#include "../Headers/Grafo.h"
#include "..\Source\Grafo.cpp"

//By Aaron Knoww

using namespace std;

int main()
{
	//Myhash<int> tabla;
	
	Grafo<int> G,gNum;
	vector<int> vec;
	vec.push_back(1125);
	
	gNum.insertarNodo("0", 10);
	gNum.insertarNodo("1", 11);
	gNum.insertarNodo("2", 22);
	gNum.insertarNodo("3", 33);
	gNum.insertarNodo("4", 44);
	gNum.insertarNodo("5", 55);
	gNum.insertarNodo("6", 66);
	gNum.insertarNodo("7", 77);

	gNum.unir2Nodos("0", "1", "01", 10);
	gNum.unir2Nodos("0", "2", "02", 1);
	gNum.unir2Nodos("0", "3", "03", 4);
	gNum.unir2Nodos("2", "1", "21", 3);
	gNum.unir2Nodos("2", "5", "25", 8);
	gNum.unir2Nodos("2", "3", "23", 2);
	gNum.unir2Nodos("3", "5", "35", 2);
	gNum.unir2Nodos("3", "6", "36", 7);
	gNum.unir2Nodos("5", "4", "54", 1);
	gNum.unir2Nodos("5", "7", "57", 9);
	gNum.unir2Nodos("5", "6", "56", 7);
	gNum.unir2Nodos("4", "1", "41", 0);
	gNum.unir2Nodos("4", "7", "47", 8);

	gNum.kruskalAlgorithm();
	gNum.buscarNodo("4");

	G.insertarNodo("A",14);
	G.insertarNodo("B",10);
	G.insertarNodo("C",9);
	G.insertarNodo("D",2);
	G.insertarNodo("E",4);
	G.insertarNodo("F",4);
	G.insertarNodo("G",4);
	G.insertarNodo("H",4);
	G.insertarNodo("I",4);
	
	// KRUSKAL GRAFO 1 FUNCIONA
	/*G.unir2Nodos("A", "B","AB", 4);
	G.unir2Nodos("A", "E","AE", 5);
	G.unir2Nodos("B", "E","AB", 6);
	G.unir2Nodos("B", "C","BC", 8);
	G.unir2Nodos("A", "C","AC", 9);
	G.unir2Nodos("C", "D","CD", 10);
	G.unir2Nodos("A", "D","AD", 11);
	G.unir2Nodos("D", "E","DE", 12);*/

	//KRUSKAL GRAFO 2 FUNCIONA
	/*G.unir2Nodos("A", "B", "AB", 4);
	G.unir2Nodos("A", "E", "AE", 4);
	G.unir2Nodos("B", "E", "AB", 4);
	G.unir2Nodos("B", "C", "BC", 4);
	G.unir2Nodos("A", "C", "AC", 4);
	G.unir2Nodos("C", "D", "CD", 4);
	G.unir2Nodos("A", "D", "AD", 4);
	G.unir2Nodos("D", "E", "DE", 4);*/

	
	// GRAFO 3 FUNCIONA.
	G.unir2Nodos("A", "B", "AB", 6);
	G.unir2Nodos("A", "D", "AD", 10);
	G.unir2Nodos("A", "G", "AG", 8);
	G.unir2Nodos("B", "C", "BC", 11);
	G.unir2Nodos("B", "E", "BE", 15);
	G.unir2Nodos("B", "H", "BH", 13);
	G.unir2Nodos("C", "H", "CH", 4);
	G.unir2Nodos("D", "E", "DE", 6);
	G.unir2Nodos("E", "F", "EF", 2);
	G.unir2Nodos("F", "G", "FG", 4);
	G.unir2Nodos("F", "I", "FI", 6);
	G.unir2Nodos("G", "H", "GH", 5);
	G.unir2Nodos("G", "I", "GI", 5);
	G.unir2Nodos("H", "I", "HI", 7);

	G.kruskalAlgorithm();
	G.primsAlgorithm("A");
	cout << "\nEl peso de kruskal es " << G.pesoKruskal() << endl;
	cout << "\nEl peso de Prim es " << G.pesoPrim() << endl;

				
	
	G.buscarNodo("A");
	/*G.insertarNodo("Aaron", 19);
	G.insertarNodo("Knoww", 14);
	G.insertarNodo("Cruz", 19);
	G.insertarNodo("Azul", 14);
	G.sonAdyacentes("Aaron", "Knoww");
	G.unir2Nodos("Aaron", "Knoww","A1",10);
	G.unir2Nodos("Aaron", "Azul","A2",10);
	G.unir2Nodos("Aaron", "Cruz","A3",10);
	G.unir2Nodos("Knoww", "Azul","A4",10);
	G.unir2Nodos("Knoww", "Azul","A4",10);*/
	//G.eliminarNodo("Aaron");
	//G.borrarArista("A1");
	//NOTA
	//Despues de borrar Arista y tratar de insertar otra arista marca error por desreferenciar un puntero. revisar.
	
	//Falta eliminar nodo y arista. borrando todos los punteros que sea nesesario borrar.


	
	/*if (G.unir2Nodos("Cruz", "Aaron", "A8", 10))
		cout << "\n\n union correcta" << endl;
	else
		cout << "\n\nNo se pudo unir esos nodos" << endl;
	if (G.unir2Nodos("Azul", "Cruz", "A4", 10))
		cout << "\n\n union correcta" << endl;
	else
		cout << "\n\nNo se pudo unir esos nodos" << endl;
	*/
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
