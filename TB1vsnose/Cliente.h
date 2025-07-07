#include "iostream"
#include "string"
#include "EstructurasDeDatos.h"
#include "Productos.h"

using namespace std;




void heapify(vector<Nodo<Producto<double>>*>& vec, int n, int i) {
	int smallest = i;

	int l = 2 * i + 1, r = 2 * i + 2;

	if (l < n && vec[l]->actual->precio < vec[smallest]->actual->precio) smallest = l;
	if (r < n && vec[r]->actual->precio < vec[smallest]->actual->precio) smallest = r;

	if (smallest != i) {
		swap(vec[i], vec[smallest]);
		heapify(vec, n, smallest);
	}
}

// Main function to do heap sort
void heapSort(vector<Nodo<Producto<double>>*>& arr) {
	int n = arr.size();

	// Build heap (rearrange vector)
	for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i = n - 1; i > 0; i--) {

		// Move current root to end
		swap(arr[0], arr[i]);

		// Call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

//____________________ vector
void heapifyVector(vector<double>& vec, int n, int i) {
	int lar = i;

	int l = 2 * i + 1, r = 2 * i + 2;

	if (l < n && vec[l] > vec[lar]) lar = l;
	if (r < n && vec[r] > vec[lar]) lar = r;

	if (lar != i) {
		swap(vec[i], vec[lar]);
		heapifyVector(vec, n, lar);
	}
}





auto insertSortProducto = [](Nodo<Producto<double>>** n, int cantidad) {

	for (int i = 1; i < cantidad; i++) {
		Nodo<Producto<double>>* key = n[i];
		int j = i - 1;

		while (j >= 0 && n[j]->actual->precio < key->actual->precio) {
			n[j + 1] = n[j];
			j--; using namespace System;
			using namespace std;
		}
		n[j + 1] = key;
	}
	};

template <typename T>
class Cliente {
public:
	T nombre;
	ListaEnlazada <Nodo<Producto<double>>, int>* carrito;
	T tipo;
	bool cupon;
	camVec* ruta; // ? AQUI AGREGAMOS TU VARIABLE
	char nodIn;
	char NodFin;

	double montoTotalAPagar; // 
	double monto;
	double resto;


	Cliente() {
		Interfaz* canva = new Interfaz();
		canva->Imprimir(35, 15, new Color(9, 8), "Nombre del cliente: "); cin >> nombre;
		canva->Imprimir(35, 17, new Color(9, 8), "Codigo: "); cin >> tipo;
		canva->Imprimir(35, 19, new Color(9, 8), "Tiene cupon? (Si=1 : No=0): "); cin >> cupon;

		montoTotalAPagar = 0;
		monto = 0;
		resto = 0;
		//EN ESE APARTADO SE CREA EL CLIENTE EN EL TXT
		fstream archivo("RegistroClientes.txt", ios::in | ios::out | ios::app);

		if (archivo.is_open()) {

			archivo << "Codigo: " << tipo << endl;
			archivo << "Cliente: " << nombre << endl;
			archivo << "Tiene cupon? " << ((cupon) ? "SI" : "NO") << endl;
			archivo << "Carrito: " << endl;
			archivo << "A0001" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>
			archivo << "A0002" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>
			archivo << "A0003" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>
			archivo << "A0004" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>
			archivo << "A0005" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>
			archivo << "A0006" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>
			archivo << "A0007" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>
			archivo << "A0008" << endl; //sirve como identificador del ultimo :>
			archivo << "0" << endl; //sirve como identificador del ultimo :>


			archivo.close();
		}
		else {
			cout << "No se pudo abrir el archivo :(" << endl;
		}


		carrito = new ListaEnlazada<Nodo<Producto<double>>, int >();
	}

	Cliente(T t, T n, bool cup, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8) {
		this->tipo = t;
		this->nombre = n;
		this->cupon = cup;

		montoTotalAPagar = 0;
		monto = 0;

		carrito = new ListaEnlazada<Nodo<Producto<double>>, int >();

		for (int i = 0; i < c1; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock1<double>));
		for (int i = 0; i < c2; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock2<double>));
		for (int i = 0; i < c3; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock3<double>));
		for (int i = 0; i < c4; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock4<double>));
		for (int i = 0; i < c5; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock5<double>));
		for (int i = 0; i < c6; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock6<double>));
		for (int i = 0; i < c7; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock7<double>));
		for (int i = 0; i < c8; i++) carrito->AgregarElemento(new Nodo<Producto<double>>(new Stock8<double>));

	}

void AgregarEnCarrito(Interfaz* F, vector<Pila<Nodo<Producto<double>>>*>& pilas) {
    int pagina = 0;
    int totalPaginas = (pilas.size() + 2) / 3; // 3 por página
	bool hizooperacion = false; 
    int opcion;
    bool salir = false;
    do {
		system("cls");
        F->ProductosStock();

        Color* c = new Color(8, 13);
        Color* vacio = new Color(13, 10);
		Color* verde = new Color(8, 10); 
        int base = pagina * 3;
        for (int i = 0; i < 3 && base + i < pilas.size(); ++i) {
            int posX = 16 + i * 34;
            int posY = 18;
            string nombre = pilas[base + i]->productoAlmacenado;

            F->Imprimir(posX, 27, c, "[" + to_string(base + i + 1) + "] " + nombre);

            if (!pilas[base + i]->estaVacia()) {
				if (pilas[base + i]->retornarTOPE()->actual->tipoAlmacenamiento == congelador) F->carneSprite(posX,posY);
				if (pilas[base + i]->retornarTOPE()->actual->tipoAlmacenamiento == refrigerado) F->Productogrande1(posX,posY);
				if (pilas[base + i]->retornarTOPE()->actual->tipoAlmacenamiento == Abarrotes) F->Productogrande3(posX,posY);
            } else {
                F->Imprimir(posX, posY, vacio, "Sin stock.");
            }
        }

        F->Imprimir(26, 13, verde, "[9] Pagina anterior  [0] Siguiente pagina  [-1] Cancelar");
        F->Imprimir(24, 14, verde, "Seleccione producto a agregar al carrito: ");

		while (true) {
			cin >> opcion;

			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(1000, '\n'); // descartar el resto de la línea
				cout << "Por favor, ingrese un dato valido." << endl;
			}
			else {
				break; // entrada válida, salir del bucle
			}
		}
		int idx;
        if (opcion == -1) {
            salir = true;
        } else if (opcion == 0 && pagina + 1 < totalPaginas) {
            pagina++;
        } else if (opcion == 9 && pagina > 0) {
            pagina--;
        } else if (opcion >= 1 && opcion <= pilas.size()) {
            idx = opcion - 1;
            if (pilas[idx]->estaVacia()) {
                F->Imprimir(10, 35, vacio, "Producto sin stock.");
            } else {
                // Obtener producto del tope y agregar al carrito
				Producto<double>* producto = pilas[idx]->retornarTOPE()->actual;
				Nodo<Producto<double>>* nodo = new Nodo<Producto<double>>(producto);
				carrito->AgregarElemento(nodo);
				pilas[idx]->pop();

                F->Imprimir(40, 27, verde, "Producto agregado al carrito.");
				hizooperacion = true; 
				system("pause>0");
            }
        }

		if (hizooperacion) {
						fstream lectura("RegistroClientes.txt", ios::in | ios::out | ios::app);
						ofstream nuevo("nuevo.txt");
						string linea, lineaELiminar = "Codigo: " + tipo;
						int cont = 1;
						bool clienteEncontrado = false;

						while (getline(lectura, linea)) {
							if (linea == lineaELiminar) {
								clienteEncontrado = true;

								nuevo << linea << endl;
								for (int i = 0; i < 3; ++i) {
									getline(lectura, linea);
									nuevo << linea << endl; // nombre, etc.
								}

								nuevo << "A0001" << endl;
								nuevo << carrito->getCantidadStock1() << endl;

								getline(lectura, linea);
								getline(lectura, linea);


								nuevo << "A0002" << endl;
								nuevo << carrito->getCantidadStock2() << endl;

								getline(lectura, linea);
								getline(lectura, linea);

								nuevo << "A0003" << endl;
								nuevo << carrito->getCantidadStock3() << endl;

								getline(lectura, linea);
								getline(lectura, linea);

								nuevo << "A0004" << endl;
								nuevo << carrito->getCantidadStock4() << endl;

								getline(lectura, linea);
								getline(lectura, linea);

								nuevo << "A0005" << endl;
								nuevo << carrito->getCantidadStock5() << endl;

								getline(lectura, linea);
								getline(lectura, linea);

								nuevo << "A0006" << endl;
								nuevo << carrito->getCantidadStock6() << endl;

								getline(lectura, linea);
								getline(lectura, linea);

								nuevo << "A0007" << endl;
								nuevo << carrito->getCantidadStock7() << endl;

								getline(lectura, linea);
								getline(lectura, linea);

								nuevo << "A0008" << endl;
								nuevo << carrito->getCantidadStock8() << endl;

								getline(lectura, linea);
								getline(lectura, linea);
							}
							else {
								nuevo << linea << endl;
							}
						}
						lectura.close();
						nuevo.close();

						remove("RegistroClientes.txt");
						rename("nuevo.txt", "RegistroClientes.txt");

					}

    } while (!salir);
}
	void EliminarElemento(Interfaz* F, Pila<Nodo<Producto<double>>>* L1, Pila<Nodo<Producto<double>>>* L2, Pila<Nodo<Producto<double>>>* L3, Pila<Nodo<Producto<double>>>* L4, Pila<Nodo<Producto<double>>>* L5, Pila<Nodo<Producto<double>>>* L6, Pila<Nodo<Producto<double>>>* L7, Pila<Nodo<Producto<double>>>* L8, vector<Pila<Nodo<Producto<double>>>*>& pilas) {

		Color* c = new Color(8, 14);
		Color* c2 = new Color(13, 13);
		
		F->ProductoConsultaTranseferencia(); 
		int t;
		F->Imprimir(0, 0, new Color(8, 10), "Que producto se elimina al carrito?  "); cin >> t;
		bool elimino = carrito->EliminarElemento(t, "Producto");
		Nodo <Producto<double>>* nodo;
		Stock1<double>* s1;
		Stock2<double>* s2;
		Stock3<double>* s3;
		Stock4<double>* s4;
		Stock5<double>* s5;
		Stock6<double>* s6;
		Stock7<double>* s7;
		Stock8<double>* s8;

		//variable
		bool entro = false;

		if (!elimino) return;
		switch (t) {
		case 1:


			s1 = new Stock1<double>();
			nodo = new Nodo<Producto<double>>(s1);
			L1->push(nodo);
			entro = true;

			if (carrito->getNdeLista()) {
				F->Productogrande1(16, 18);
			}
			else {
				F->Imprimir(16, 18, c, "No hay productos.");
			}

			break;
		case 2:


			s2 = new Stock2<double>();
			nodo = new Nodo<Producto<double>>(s2);
			L2->push(nodo);
			entro = true;


			break;
		case 3:

			s3 = new Stock3<double>();
			nodo = new Nodo<Producto<double>>(s3);
			L3->push(nodo);
			entro = true;

			break;

		case 4:

			s4 = new Stock4<double>();
			nodo = new Nodo<Producto<double>>(s4);
			L4->push(nodo);
			entro = true;

			break;

		case 5:

			s5 = new Stock5<double>();
			nodo = new Nodo<Producto<double>>(s5);
			L5->push(nodo);
			entro = true;

			break;
		case 6:

			s6 = new Stock6<double>();
			nodo = new Nodo<Producto<double>>(s6);
			L6->push(nodo);
			entro = true;

			break;
		case 7:

			s7 = new Stock7<double>();
			nodo = new Nodo<Producto<double>>(s7);
			L7->push(nodo);
			entro = true;

			break;
		case 8:

			s8 = new Stock8<double>();
			nodo = new Nodo<Producto<double>>(s8);
			L8->push(nodo);
			entro = true;

			break;
		}
		//ELIMINAR DEL ARCHIVO

		if (elimino) {
			F->ProductosStock();
			if (carrito->HayStock1()) {
			}
			else {
				F->Imprimir(16, 18, c, "No hay productos.");
			}
			if (carrito->HayStock2()) {
			}
			else {
				F->Imprimir(50, 18, c, "No hay productos.");
			}
			if (carrito->HayStock3()) {
			}
			else {
				F->Imprimir(82, 18, c, "No hay productos.");
			}
			if (carrito->HayStock4()) {
			}
			else {
				F->Imprimir(82, 18, c, "No hay productos.");
			}
			if (carrito->HayStock5()) {
			}
			else {
				F->Imprimir(82, 18, c, "No hay productos.");
			}
			if (carrito->HayStock7()) {
			}
			else {
				F->Imprimir(82, 18, c, "No hay productos.");
			}
			if (carrito->HayStock8()) {
			}
			else {
				F->Imprimir(82, 18, c, "No hay productos.");
			}


			fstream lectura("RegistroClientes.txt", ios::in | ios::out | ios::app);
			ofstream nuevo("nuevo.txt");
			string linea, lineaELiminar = "Codigo: " + tipo;
			int cont = 1;
			bool clienteEncontrado = false;

			while (getline(lectura, linea)) {
				if (linea == lineaELiminar) {
					clienteEncontrado = true;

					nuevo << linea << endl;
					for (int i = 0; i < 3; ++i) {
						getline(lectura, linea);
						nuevo << linea << endl; // nombre, etc.
					}

					nuevo << "A0001" << endl;
					nuevo << carrito->getCantidadStock1() << endl;
					getline(lectura, linea);
					getline(lectura, linea);


					nuevo << "A0002" << endl;
					nuevo << carrito->getCantidadStock2() << endl;
					getline(lectura, linea);
					getline(lectura, linea);

					nuevo << "A0003" << endl;
					nuevo << carrito->getCantidadStock3() << endl;
					getline(lectura, linea);
					getline(lectura, linea);

					nuevo << "A0004" << endl;
					nuevo << carrito->getCantidadStock4() << endl;

					getline(lectura, linea);
					getline(lectura, linea);

					nuevo << "A0005" << endl;
					nuevo << carrito->getCantidadStock5() << endl;

					getline(lectura, linea);
					getline(lectura, linea);

					nuevo << "A0006" << endl;
					nuevo << carrito->getCantidadStock6() << endl;

					getline(lectura, linea);
					getline(lectura, linea);

					nuevo << "A0007" << endl;
					nuevo << carrito->getCantidadStock7() << endl;

					getline(lectura, linea);
					getline(lectura, linea);

					nuevo << "A0008" << endl;
					nuevo << carrito->getCantidadStock8() << endl;

					getline(lectura, linea);
					getline(lectura, linea);

				}
				else {
					nuevo << linea << endl;
				}
			}
			lectura.close();
			nuevo.close();

			remove("RegistroClientes.txt");
			rename("nuevo.txt", "RegistroClientes.txt");
		}

	}
	void mostrar_info(Color* c) {
		//define color, no imprimir como tal
		designer->Imprimir(50, 10, c);
		cout << "\nNombre: " << nombre;
		cout << "\nCodigo: " << tipo;
		cout << "\nCupon: " << ((cupon) ? "Si" : "No") << endl;
		cout << "CARRITO: " << endl;
		cout << colores->RESET;
		VerLista(c);

	}
	void VerLista(Color* c) {
		designer->interfazCarritoCliente();
		carrito->Ver(c);
	}

	void PagarCarrito(double& ingBrutos, double& ingNetos, double& desc) {
		designer->Imprimir(0, 0, new Color(3, 8));

		//inicializacion de variables
		Console::ReadKey();
		//MONTO TOTAL BRUTO DEL CARRITO: SIN DESCUENTO
		resto = 0;
		monto = carrito->CarroMontoTotal();
		bool promocionValidada5x2 = false;


		cout << "ordenando de mayor a menor para evaluar el descuento... " << endl;
		_sleep(1000);

		//ORDENAR EL ARREGLO ANTES DE CUALQUIER DESCUENTO
		int n = carrito->getNdeLista();
		Nodo<Producto<double>>* temp = carrito->cabeza;

		vector<Nodo<Producto<double>>*> vecNodos(n);

		//vector
		for (int i = 0; i < n; i++) {
			vecNodos[i] = temp;
			temp = temp->next;
		}
		heapSort(vecNodos);
		for (int i = 0; i < n - 1; ++i) {
			vecNodos[i]->next = vecNodos[i + 1];
		}
		vecNodos[n - 1]->next = nullptr;
		carrito->cabeza = vecNodos[0];

		
		//promocion del cupon
		if (this->cupon && carrito->cabeza != nullptr) {
			
			double* ordenar;
			cout << "como cuenta con un cupon, se le aplicara descuento a los 5 productos mas caros! " << endl;
			
			//SE LE RESTA DIRECTAMENTE A LOS NODOS DE LOS PRODUCTOS
			Nodo<Producto<double>>* descuento = carrito->cabeza;
			int maximosDescuentos = 0;
			while (maximosDescuentos < 5 && descuento != nullptr) {
				double original = descuento->actual->precio;
				descuento->actual->precio = original * 0.85;
				resto += original * 0.15;
				descuento = descuento->next;
				maximosDescuentos++;
			}
			
		}
		
		//promocion 5x2 en productos mas baratos para los que no tengan cupon UNICAMENTE
		bool cincoIguales = true;
		if(n > 4 && !cupon && carrito->cabeza != nullptr){
			//ingresando directamente al nodo

			vector<double> precios = carrito->obtenerVectorDePrecios(); //vector para guardar los precios más bajos 

			


			auto heapiSort = [](vector<double>& arr) { //heap sort pero solo para vector con parametro double
				int n = arr.size();

				for (int i = n / 2 - 1; i >= 0; i--) heapifyVector(arr, n, i);

				for (int i = n - 1; i > 0; i--) {
					swap(arr[0], arr[i]);
					heapifyVector(arr, i, 0);
				}
				}; 

			heapiSort(precios);

			
			double precioProd = precios[0];
			for (int i = 1; i < 5; i++) {
				if (precios[i] != precios[i - 1]) {
					cincoIguales = false;
					break;
				}
			}

			if (cincoIguales) {

				Nodo<Producto<double>>* promochiquis = carrito->cabeza;
				int finded = 0;
				while (promochiquis != nullptr && finded < 3) {
					if (promochiquis->actual->precio == precioProd) {
						resto += precioProd;
						promochiquis->actual->precio = 0;
						finded++;
					}
					
					promochiquis = promochiquis->next;
				}


			}
			
		}
		

		system("pause>0");
		designer->Pantalla(new Color(1, 2));
		montoTotalAPagar = carrito->CarroMontoTotal();
		designer->Imprimir(0, 0, new Color(3, 8));
		cout << "Monto Total Bruto: " << monto << endl;
		cout << "Monto Total a pagar: "; cout << ((this->cupon || cincoIguales) ? montoTotalAPagar : monto) << endl;
		cout << "Descuento realizado: " << resto << endl;

		auto añadirMontosAlSistema = [](double& bruto, double& neto, double& desco, double mon, double monne, double dem) {
			bruto += mon;
			neto += monne;
			desco += dem;
			};
		añadirMontosAlSistema(ingBrutos, ingNetos, desc, monto, montoTotalAPagar, resto);

		system("pause>0");

	}

	T getCodigo() { return tipo; }
	T getNombre() { return nombre; }
	bool getCupon() { return cupon; }

	double retornarMonto() {
		return monto;
	}
	//CON DESCUENTO SI ES QUE TIENE 
	double retornoMontoAPagar() {
		return montoTotalAPagar;
	}


};
