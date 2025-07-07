#pragma once
#include <vector>
#include "fstream"
#include "sstream"
#include "Interfaz.h"
#include "windows.h"
#include "Grafos.h"
Interfaz* designer = new Interfaz();
enum direcciones { right, left, up, down };

using namespace std;

const int CONSOLE_WIDTH = 120;
const int CONSOLE_HEIGHT = 40;
bool screenMap[CONSOLE_HEIGHT][CONSOLE_WIDTH] = { false };

template <typename clase>
class NodoBB
{
public:
	//struct de REGISTRO (sin puntero)
	clase producto;
	int altura; 
	//int NumNodo;
	NodoBB* izquierdo; 
	NodoBB* derecho;


	NodoBB(clase* p)
	{
		producto = p; 
		altura = 1; 
		izquierdo = derecho = nullptr; 
	}
	NodoBB(clase p)
	{
		producto = p;
		altura = 1;
		izquierdo = derecho = nullptr;
	}

};





template <typename clase>
class Nodo {
public:
	Nodo* next;
	clase* actual;
	Nodo(clase* act) {
		actual = act;
		next = nullptr;
	}

	Nodo(clase* act, Nodo<clase>* nex) {
		actual = act;
		next = nex;
	}
};

template<typename clase>
class Pila {
public:
	Nodo<clase>* tope;
	int cantPila;
	string productoAlmacenado; 
	Pila(string s) {
		tope = nullptr;
		cantPila = 0;
		productoAlmacenado = s; 
	};

	bool estaVacia() {
		return (tope == nullptr);
	}

	void push(clase* nuev) {
		// si el tope esta en nullptr -> se guardará el nullptr
		tope = new Nodo<clase>(nuev, tope);
		cantPila++;
	}

	clase pop() {
		if (estaVacia()) {
			//throw "Error, pila vacía";
			return nullptr;
		}
		Nodo<clase>* NodoABorrar = tope;

		clase* elemento = NodoABorrar->actual;
		tope = (Nodo<clase>*) NodoABorrar->next;
		delete NodoABorrar;

		cantPila--;

		return *elemento;

	}

	void mostrarPila() {
		if (estaVacia()) {
			cout << "PILA VACIA !!" << endl;
			return;
		}

		Nodo<clase>* actual = tope;
		int i = cantPila;
		while (actual != nullptr) {
			cout << "Producto #" << i-- << ": ";
			actual->actual->mostrar_info();
			actual = actual->next;
		}
	}

	clase* retornarTOPE() {

		if (estaVacia()) return nullptr;
		return tope->actual;
	}
	int getNumeroElementos() {
		return cantPila;
	}

	//vaciar píla
	int vaciarPila() {
		int c = 0;
		while (!estaVacia()) {
			pop();
			c++;
		}
		return c;
	}
};

template <typename clase>
class Cola {
	clase* inicio;
	clase* final;
public:
	Cola() {
		inicio = final = nullptr;
	}
	void AgregarElemento(clase* c) {
		if (inicio == nullptr) {
			inicio = final = c;
		}
		else {
			final->next = c;
			final = c;
		}
	}
	clase* EliminarElemento() {
		if (inicio == nullptr)return nullptr;
		else {
			inicio->actual->mostrar_info(new Color(0, 2));
			clase* retorno = inicio;
			inicio = inicio->next;
			return retorno;
		}
	}
	clase* RetornoElementoAgregado(clase* c) {
		if (inicio == nullptr) {
			inicio = final = c;
			return c;
		}
		else {
			final->next = c;
			final = c;
			return final;
		}
	}
	int getN() {
		if (inicio == nullptr) {
			return 0;
		}
		else {
			clase* nodo = inicio; 
			int cnt = 0; 
			while (nodo != nullptr) {
				cnt++;
				nodo = nodo->next; 
			}
			
			return cnt; 
		}
	}

};

template <typename clase, typename typo>
class ListaEnlazada {
public:
	clase* cabeza;
	int cantidadLista; //muestra la cantidad de ELEMENTOS dentro de la LISTA
	ListaEnlazada() {
		cabeza = nullptr;
		cantidadLista = 0;
	}
	void AgregarElemento(clase* p) {
		if (cabeza == nullptr) {
			cabeza = p;
		}
		else {
			clase* act = cabeza;
			while (act->next != nullptr) {
				act = act->next;
			}
			act->next = p;
		}
		cantidadLista++;
	}

	clase* EliminarElemento(typo tipo, string no) {
		clase* retorno;
		if (cabeza == nullptr)return nullptr;
		else {
			clase* act = cabeza;
			if (cabeza->actual->tipo == tipo) {
				if (no != "") {
					cout << "\n" << no << " eliminado: ";
					cabeza->actual->mostrar_info(new Color(0,2));
				}
				retorno = cabeza;
				cabeza = cabeza->next;

				cantidadLista--;

				return retorno;
			}
			else {
				while (act->next != nullptr) {
					if (act->next->actual->tipo == tipo)break;
					act = act->next;
				}
				if (act->next == nullptr)return nullptr;
				else {
					if (no != "") {
						cout << "\n" << no << " eliminado: ";
						act->next->actual->mostrar_info(new Color(0, 2));
					}
					retorno = act->next;
					act->next = act->next->next;
					cantidadLista--;
					return retorno;
				}
			}
		}
	}
	double CarroMontoTotal() {
		double cBruto = 0; //cantidad a pagar
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {
				cBruto += act->actual->precio;
				act = act->next;
			}
		}
		return cBruto;
	}

	int getNdeLista() { //retorna la cantidad de elementos dentro de la lista
		return cantidadLista;
	}

	void eliminarClienteDeTxt(typo c) { //codigo del cliente
		fstream lectura("RegistroClientes.txt", ios::in | ios::out | ios::app);
		ofstream nuevo("nuevo.txt");
		string linea, lineaELiminar = "Codigo: " + c;
		int cont = 1;
		bool entrado = false;

		while (getline(lectura, linea)) {
			if (linea == lineaELiminar) {
				entrado = true;
				cont++;
				continue;
			}
			if (entrado && cont <= 10) {
				cont++;
				continue;
			}
			nuevo << linea << endl;
		}
		lectura.close();
		nuevo.close();

		remove("RegistroClientes.txt");
		rename("nuevo.txt", "RegistroClientes.txt");
	}
	clase* buscar(typo tipo) {
		if (cabeza == nullptr) {
			return nullptr;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {
				if (act->actual->getCodigo() == tipo) {
					return act;
				}
				act = act->next;
			}

		}

		return nullptr;
	}

	void mostrarTodosLosElementos() {
		if (cabeza == nullptr) return;
		clase* act = cabeza;

		while (act != nullptr) {

			cout << act->actual->getCodigo() << " ";
			act = act->next;
		}

	}
	void VerConcord(Interfaz* i) {
		
		if (cabeza == nullptr) {
			i->Imprimir(50, 2, new Color(9, 10), "No hay informacion ");
			return;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {
				act->actual->mostrar_info(i);
				act = act->next;
				cout << endl;
			}


		}
	}
	void Ver(Color* c) {

		designer->Imprimir(40, 15, c);

		if (cabeza == nullptr) {

			designer->Imprimir(40, 15, new Color(8, 12), "No hay informacion.");

			return;

		}

		else {

			clase* act = cabeza;

			int cnt = 0;

			int i = 0;

			while (act != nullptr) {

				designer->Imprimir(40, 20, new Color(8, 12));

				con->cursor(37 + i, 17); cout << " " << act->actual->nombre;

				con->cursor(40 + i, 20);cout << colores->BG_grisoscuro << act->actual->id;

				con->cursor(40 + i, 21);cout << colores->BG_grisoscuro << act->actual->precio;

				cnt++;

				i = i + 20;

				if (cnt >= 3) {

					designer->Imprimir(40, 24, new Color(8, 12), "y mas..."); break;

				}

				act = act->next;

				cout << endl;

			}



		}

	}

	//retornar la cantidad de stock 1 q hay en el carrito
	int getCantidadStock1() {
		int c = 0;
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {

				if (act->actual->id == "A0001") c++;
				act = act->next;
			}
		}
		return c;
	}
	int getCantidadStock2() {
		int c = 0;
		if (cabeza == nullptr) {

			cout << "hola";
			system("pause>0");

			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {
				if (act->actual->id == "A0002") c++;
				act = act->next;
			}
		}
		return c;
	}
	int getCantidadStock3() {
		int c = 0;
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {

				if (act->actual->id == "A0003") c++;


				act = act->next;
			}
		}
		return c;
	}

	int getCantidadStock4() {
		int c = 0;
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {

				if (act->actual->id == "A0004") c++;


				act = act->next;
			}
		}
		return c;
	}

	int getCantidadStock5() {
		int c = 0;
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {

				if (act->actual->id == "A0005") c++;


				act = act->next;
			}
		}
		return c;
	}

	int getCantidadStock6() {
		int c = 0;
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {

				if (act->actual->id == "A0006") c++;


				act = act->next;
			}
		}
		return c;
	}

	int getCantidadStock7() {
		int c = 0;
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {

				if (act->actual->id == "A0007") c++;


				act = act->next;
			}
		}
		return c;
	}

	int getCantidadStock8() {
		int c = 0;
		if (cabeza == nullptr) {
			return 0;
		}
		else {
			clase* act = cabeza;
			while (act != nullptr) {

				if (act->actual->id == "A0008") c++;


				act = act->next;
			}
		}
		return c;
	}

	bool HayStock1() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0001") return true;
			act = act->next;
		}

		return false;
	}

	bool HayStock2() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0002") return true;
			act = act->next;
		}

		return false;
	}
	bool HayStock3() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0003") return true;
			act = act->next;
		}

		return false;
	}

	bool HayStock4() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0004") return true;
			act = act->next;
		}

		return false;
	}

	bool HayStock5() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0005") return true;
			act = act->next;
		}

		return false;
	}

	bool HayStock6() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0006") return true;
			act = act->next;
		}

		return false;
	}

	bool HayStock7() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0007") return true;
			act = act->next;
		}

		return false;
	}

	bool HayStock8() {
		if (cabeza == nullptr) return false;

		clase* act = cabeza;
		while (act != nullptr) {

			if (act->actual->id == "A0008") return true;
			act = act->next;
		}

		return false;
	}
	//______________________


	//para utilizar un vector en el HEAPSORT
	vector<double> obtenerVectorDePrecios() {
		vector<double> re;

		if (cabeza == nullptr) return {};

		clase* act = cabeza;
		while (act != nullptr) {
			re.push_back(act->actual->precio);
			act = act->next;
		}

		return re;
	}



};

template<typename clase>
class AVL
{
public:
	NodoBB<clase>* raiz;
	int elementosInsertados;
	AVL()
	{
		raiz = nullptr;
		elementosInsertados = 0;
	}

	void insertarDato(clase product) {
		raiz = insertar(raiz, product);
	}

	NodoBB<clase>* buscarDato(clase product) {

		bool pillado = false;
		return buscar(raiz, product, pillado);

	}

	void eliminarDato(clase product) {
		//raiz = eliminar
	}

	void recorrerInOrden(NodoBB<clase>* nodo, Interfaz* canva, int x, int& y, Color* c) {
		if (!nodo) return;

		recorrerInOrden(nodo->izquierdo, canva, x, y, c);

		// Imprimir cada producto con etiquetas claras
		canva->Imprimir(x, y++, c, "ID: " + nodo->producto.id);
		canva->Imprimir(x, y++, c, "Precio: S/. " + to_string(nodo->producto.precio));
		canva->Imprimir(x, y++, c, "Stock disponible: " + to_string(nodo->producto.cantidad));
		// Línea de separación
		canva->Imprimir(x, y++, c, "--------------------");

		recorrerInOrden(nodo->derecho, canva, x, y, c);
	}
private:

	//ingreso el nodo que quiero hallar la altura
	int altura(NodoBB<clase>* nodo) {
		return (nodo == nullptr) ? 0 : nodo->altura;
	}
	void actualizarAltura(NodoBB<clase>* nodo) {
		if (nodo) {
			nodo->altura = 1 + max(altura(nodo->izquierdo),
				altura(nodo->derecho)); //obtiene alturo con método max...
		}
	}
	//ingreso nodo que quiero hallar el balance
	int balance(NodoBB<clase>* nodo) {
		return (nodo == nullptr) ? 0 : altura(nodo->izquierdo) - altura(nodo->derecho);
	}

	NodoBB<clase>* rotarDerecha(NodoBB<clase>* y) {
		NodoBB<clase>* x = y->izquierdo;
		NodoBB<clase>* T2 = x->derecho;

		x->derecho = y;
		y->izquierdo = T2;

		y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));
		x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));

		return x;
	}

	NodoBB<clase>* rotarIzquierda(NodoBB<clase>* x) {
		NodoBB<clase>* y = x->derecho;
		NodoBB<clase>* T2 = y->izquierdo;

		y->izquierdo = x;
		x->derecho = T2;

		x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));
		y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));

		return y;
	}

	NodoBB<clase>* insertar(NodoBB<clase>* nodo, clase c) {
		if (!nodo) {
			elementosInsertados++;
			NodoBB<clase>* n = new NodoBB<clase>(c);
			return n;
		}
		//ordeno por codigo del producto (es string, se puede)
		if (c.id < nodo->producto.id) {
			nodo->izquierdo = insertar(nodo->izquierdo, c);
		}
		else if (c.id > nodo->producto.id) {
			nodo->derecho = insertar(nodo->derecho, c);
		}
		else {
			return nodo; //bloqueo el chance, no genera otro nodo
		}

		actualizarAltura(nodo);
		int b = balance(nodo);

		//rotaciones
		if (b > 1 && c.id < nodo->izquierdo->producto.id)
			return rotarDerecha(nodo); // Izquierda Izquierda

		if (b < -1 && c.id > nodo->derecho->producto.id)
			return rotarIzquierda(nodo); // Derecha Derecha

		if (b > 1 && c.id > nodo->izquierdo->producto.id) {
			nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
			return rotarDerecha(nodo); // Izquierda Derecha
		}

		if (b < -1 && c.id < nodo->derecho->producto.id) {
			nodo->derecho = rotarDerecha(nodo->derecho);
			return rotarIzquierda(nodo); // Derecha Izquierda
		}

		return nodo;
	};

	NodoBB<clase>* eliminar(NodoBB<clase>* nodo, clase c, bool& eliminado) {
		if (!nodo) { return nullptr; } //en vez de crear, retorna null 

		// Paso 1: búsqueda como BST
		if (c.id < nodo->producto.id)
			nodo->izquierdo = eliminar(nodo->izquierdo, c, eliminado);
		else if (c.id > nodo->producto.id)
			nodo->derecho = eliminar(nodo->derecho, c, eliminado);
		else {
			// Nodo encontrado
			eliminado = true;
			// Caso 1 y 2: Uno o ningún hijo
			if (!nodo->izquierdo || !nodo->derecho) {
				Nodo* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
				delete nodo;
				return temp;
			}
			else {
				// Caso 3: Dos hijos
				Nodo* sucesor = obtenerMinimo(nodo->derecho);
				nodo->dato = sucesor->dato;
				nodo->derecho = eliminar(nodo->derecho, sucesor->dato, eliminado);
			}
		}

		// Paso 2: actualizar altura
		actualizarAltura(nodo);

		int balance = factorBalance(nodo);
		// Casos de desbalance
		// Izquierda Izquierda
		if (balance > 1 && c.id < nodo->izquierdo->producto.id) {
			return rotacionDerecha(nodo);
		}
		// Derecha Derecha
		if (balance < -1 && c.id > nodo->derecho->producto.id) {
			return rotacionIzquierda(nodo);
		}
		// Izquierda Derecha
		if (balance > 1 && c.id > nodo->izquierdo->producto.id) {
			nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
			return rotacionDerecha(nodo);
		}
		// Derecha Izquierda
		if (balance < -1 && c.id < nodo->derecho->producto.id) {
			nodo->derecho = rotacionDerecha(nodo->derecho);
			return rotacionIzquierda(nodo);
		}
		return nodo;

	}

	//busca por codigo
	NodoBB<clase>* buscar(NodoBB<clase>* nodo, clase c, bool& encontrado) {
		if (nodo == nullptr) {
			return nullptr; //no hubo nada
		}
		else {
			if (c.id == nodo->producto.id) {
				return nodo;
			}

			//ordeno por codigo del producto (es string, se puede)

			if (c.id < nodo->producto.id) return buscar(nodo->izquierdo, c, encontrado);
			else
				return buscar(nodo->derecho, c, encontrado);

		}
	}
};
