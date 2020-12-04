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
	G.unir2Nodos("Aaron", "Knoww","A1",10);
	G.sonAdyacentes("Aaron", "Knoww");
	if (G.buscarNodo("Aaroon"))
		cout << "\n Si existe el nodo o vertice";
	else
		cout << "\n No existe el nodo o vertice";

	cout << "\nhello mother fuckers, Aaron Knoww was here" << endl;
	
	system("pause > null");
	return 0;
}
