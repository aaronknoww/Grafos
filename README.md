# Grafos

Se implemento una clase para grafos, utilizando las siguientes estructuras de datos unordered map, multimap, set y vector; además de memoria dinámica, plantillas y punteros.
Primero se hicieron todos los métodos para poder crear un grafo, insertar nodos, poder unir dos nodos mediante la creación de una arista y métodos como buscar nodo o arista y finalmente métodos para poder borrar ya se aristas o nodos.
Cada nodo que se inserta se guarda en memoria heap, para tener control de cada nodo se guarda en una estructura unordered map, para saber cuántos nodos hay y su dirección en memoria.
Cuando se unen dos nodos, se crea una arista que se guarda en memoria dinámica ya que esta arista contiene punteros para poder enlazar a ambos. Las aristas se guardan en una estructura de tipo unordered map.
Para borrar ya se nodos o aristas, los métodos se encargan de liberar memoria dinámica, así como todos los punteros utilizados en cualquiera de los casos.

Algoritmos.
Algoritmos de Kruskal y algoritmo de Prim, cada uno de ellos genera una tabla con el nombre de todas las aristas que intervienen en el árbol de expansión mínima que generan, además de que se puede calcular el valor total de este.
Algoritmo de Dijkstra para calcular el camino mas corto de un nodo inicial a cualquier nodo del mismo grafo, se guarda una tabla de Dijkstra en el nodo donde se inicia el recorrido. 

Curso Unordered Data Structures semana 4 de Coursera 
Referencia explicación de grafos https://youtu.be/23pdz9VtIBo
Referencia algoritmo de Kruskal  https://youtu.be/OZKuWP1KxdY
Referencia algoritmo de Prim      https://youtu.be/RXL8Z-HfdHQ
Referencia algoritmo de Dijkstra https://youtu.be/j1IGeNGpg7o
