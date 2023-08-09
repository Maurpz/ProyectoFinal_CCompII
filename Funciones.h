#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<vector>
#include<memory>
#include"BoxData.h"


vector<vector<shared_ptr<BoxData>>> crearMatriz(int filas, int columnas, int lado) {
	vector<vector<shared_ptr<BoxData>>> matriz(filas);
	for (int i = 0; i < filas;i++) {
		for (int j = 0; j < columnas; j++) {
			//matriz[i].push_back(make_shared<BoxData>("#",j*lado,i*lado,lado));
            matriz[i].push_back(make_shared<BoxData>("piedra",j,i,lado,Color::Blue));
		}
		
	}
	cout << "numero de filas de la matriz : "<<matriz.size() << endl;
	return matriz;
}

vector<vector<int>>convertirMatriz_a_numerica(vector<vector<shared_ptr<BoxData>>> & matriz) {
	vector<vector<int>> matrizEntera(matriz.size());
	for (int i = 0; i < matriz.size(); i++) {
		for (int j = 0; j < matriz[0].size(); j++) {
			if (matriz[i][j]->getTipo() == "madera") {
				matrizEntera[i].push_back(1);
			}
			else if (matriz[i][j]->getTipo() == "piedra") {
				matrizEntera[i].push_back(2);
			}
			else if (matriz[i][j]->getTipo() == "expendedora") {
				matrizEntera[i].push_back(3);
			}
			else {
				matrizEntera[i].push_back(0);
			}
		}

	}
	return matrizEntera;
}

void printMatriz(vector<vector<shared_ptr<BoxData>>> & matriz) {
	for (auto& fila : matriz) {
		for (auto& columna : fila) {
			cout << "[" << columna->getTipo() << ", x: " << columna->getX() << ", y: " << columna->getY() << " ]" << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
}
#endif FUNCIONES_H