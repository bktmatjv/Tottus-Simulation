#pragma once
#define endl "\n"
#include "Cliente.h"
#include "Grafos.h"
#include "string"		

using namespace std;

//CONTRASEÑA PARA ACCESO DE ADMINISTRADOR
const string CONTRASENA = "1";

struct RegistroProducto {
	string id;
	double precio;
	RegistroProducto(string pid, double pprecio) {
		id = pid;
		precio = pprecio;
	}
};

struct RegistroAlmacen
{
	string id;
	//string nombre; 
	double precio; 
	long cantidad; 
	TipoAlmacen tipo;
	//constructor por defecto para evitar errores
	RegistroAlmacen() {
		id = "";
		//nombre = "";
		precio = 0;
		cantidad = 0;
	}

	RegistroAlmacen(string pid, double pprecio, TipoAlmacen t) {
		id = pid; 
		precio = pprecio;
		cantidad = 500 + rand() % (500 - 10); //cantidad inicial aleatoria 
		tipo = t;
	}

	RegistroAlmacen(Producto<double>* p) {
		id = p->id;
		precio = p->precio; 
		cantidad = 500 + rand() % (500 - 10); //cantidad inicial aleatoria 
		tipo = p->tipoAlmacenamiento; 
	}



};

template <typename T>
class Almacen
{
public:

	AVL<T>* almacen_deProductos;
	string IdAlmacen;
	TipoAlmacen tipo_deAlmacen;
	Almacen(TipoAlmacen tipo) {
		tipo_deAlmacen = tipo;
		almacen_deProductos = new AVL<T>();
		int x = 1000 + rand() % (1000 - 10 + 1);
		ostringstream o;
		o << "AL" << tipo_deAlmacen << x;
		IdAlmacen = o.str();
	}
	void agregarProducto(T registro) {
		almacen_deProductos->insertarDato(registro);

	}

	void reporteProductos(int x, int y, Interfaz* canva, Color* c) {
		canva->Imprimir(x, y - 2, new Color(0,13), "Almacen ID: " + IdAlmacen);
		string tipoTexto = tipo_deAlmacen == congelador ? "Congelador" :
			tipo_deAlmacen == refrigerado ? "Refrigerado" : "Abarrotes";
		canva->Imprimir(x, y - 1, new Color(8,12), "Categoria: " + tipoTexto);

		if (almacen_deProductos->elementosInsertados == 0) {
			canva->Imprimir(x, y + 1, c, "Este almacen no contiene productos.");
		}
		else {
			almacen_deProductos->recorrerInOrden(almacen_deProductos->raiz, canva, x, y += 1, c);
		}
	}

	NodoBB<T>* buscarProductoCodigo(T codigo) {

		return almacen_deProductos->buscarDato(codigo);
	}

	void eliminarProductoCodigo(T codigo) {
		almacen_deProductos->eliminarDato(codigo);
	}

};

class Boleta {
public:
	string nombreCliente;
	string idCliente;
	double monto, montoDescuento;
	vector<RegistroProducto> boughtp;


	Boleta(string name, string id, double pmonto, double pdiscount, Nodo<Producto<double>>* produc) {
		nombreCliente = name;
		idCliente = id;
		monto = pmonto;
		montoDescuento = pdiscount;
		boughtp.push_back(RegistroProducto(produc->actual->getID(), produc->actual->precio));
	}

	Boleta(string name, string id, double pmonto, double pdiscount, vector<RegistroProducto> regis) {
		nombreCliente = name;
		idCliente = id;
		monto = pmonto;
		montoDescuento = pdiscount;
		boughtp = regis;
	}

};


//QUICK SORT 
int partirStock(vector<Pila<Nodo<Producto<double>>>*>& vec, int low, int high) {
	int pivote = vec[high]->cantPila;
	int i = low - 1;

	for (int j = low; j < high; j++)
	{
		if (vec[j]->cantPila > pivote) {
			i++;
			swap(vec[i], vec[j]);
		}
	}
	swap(vec[i + 1], vec[high]);
	return i + 1;
}

//MERGE SORT 
Nodo<Cliente<string>>* dividirLista(Nodo<Cliente<string>>* cabeza) {

	if (!cabeza || !cabeza->next) { return cabeza; }

	Nodo<Cliente<string>>* lentito = cabeza;
	Nodo<Cliente<string>>* rapidito = cabeza->next;

	while (rapidito && rapidito->next) {
		lentito = lentito->next;
		rapidito = rapidito->next->next;
	}

	Nodo<Cliente<string>>* mitad = lentito->next;
	lentito->next = nullptr;

	return mitad;
}
//MERGE SORT 
Nodo<Cliente<string>>* juntarListas(Nodo<Cliente<string>>* a, Nodo<Cliente<string>>* b) {

	if (!a) { return b; }
	if (!b) { return a; }

	Nodo<Cliente<string>>* ending = nullptr;

	if (a->actual->tipo <= b->actual->tipo) {
		ending = a;
		ending->next = juntarListas(a->next, b);
	}
	else {
		ending = b;
		ending->next = juntarListas(a, b->next);
	}

	return ending;
}

//merge sort boleta
void mergeDescendente(vector<Boleta*>& boletas, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<Boleta*> izquierda(n1);
	vector<Boleta*> derecha(n2);

	for (int i = 0; i < n1; i++)
		izquierda[i] = boletas[left + i];
	for (int j = 0; j < n2; j++)
		derecha[j] = boletas[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (izquierda[i]->montoDescuento > derecha[j]->montoDescuento) {
			boletas[k] = izquierda[i];
			i++;
		}
		else {
			boletas[k] = derecha[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		boletas[k] = izquierda[i];
		i++;
		k++;
	}

	while (j < n2) {
		boletas[k] = derecha[j];
		j++;
		k++;
	}
}

void mergeSortBoletasDescendente(vector<Boleta*>& boletas, int left, int right) {
	if (left >= right) return;

	int mid = left + (right - left) / 2;

	mergeSortBoletasDescendente(boletas, left, mid);
	mergeSortBoletasDescendente(boletas, mid + 1, right);

	mergeDescendente(boletas, left, mid, right);
}



template<typename T>
class Sistema {
public:
	Pila<Nodo<Producto<double>>>* ListaDeStock_1;
	Pila<Nodo<Producto<double>>>* ListaDeStock_2;
	Pila<Nodo<Producto<double>>>* ListaDeStock_3;
	Pila<Nodo<Producto<double>>>* ListaDeStock_4;
	Pila<Nodo<Producto<double>>>* ListaDeStock_5;
	Pila<Nodo<Producto<double>>>* ListaDeStock_6;
	Pila<Nodo<Producto<double>>>* ListaDeStock_7;
	Pila<Nodo<Producto<double>>>* ListaDeStock_8;
	vector<Pila<Nodo<Producto<double>>>*> listas;
	vector<Producto<double>*> productosBase; 

	ListaEnlazada <Nodo<Cliente<string>>, string >* clientes;
	Cola<Nodo<Cliente<string>>>* CajaRegistradora;
	Cola<Nodo<Cliente<string>>>* CajaVirtual;
	
	Nodo<Cliente<string>>* nodo;

	vector<Boleta*> boletas;

	Almacen<RegistroAlmacen>* almacen1;
	Almacen<RegistroAlmacen>* almacen2;
	Almacen<RegistroAlmacen>* almacen3;
	T ingresosBrutos; //con descuento
	T ingresosNetos; //sin descuento/cupon
	T descuentoTotalProducido;

	Sistema() {

		//nuevos archivos txt para LEER LA CANTIDAD DE INGRESOS BRUTOS Y NETOS :>
		ListaDeStock_1 = new Pila<Nodo<Producto<double>>>("Leche Fresca");
		ListaDeStock_2 = new Pila<Nodo<Producto<double>>>("Arroz Costenio");
		ListaDeStock_3 = new Pila<Nodo<Producto<double>>>("Atun Florida");
		ListaDeStock_4 = new Pila<Nodo<Producto<double>>>("Yogurt SKYR");
		ListaDeStock_5 = new Pila<Nodo<Producto<double>>>("Mantequilla");
		ListaDeStock_6 = new Pila<Nodo<Producto<double>>>("Fideo Don Vitorio");
		ListaDeStock_7 = new Pila<Nodo<Producto<double>>>("Pollo Fresco Entero");
		ListaDeStock_8 = new Pila<Nodo<Producto<double>>>("Carne Molida");
		

		//productos para repartir (facil de añadir y ver registro del total (no se utiliza en otra parte como listaPILAS))
		productosBase = {
			new Stock1<double>(),
			new Stock2<double>(),
			new Stock3<double>(),
			new Stock4<double>(),
			new Stock5<double>(),
			new Stock6<double>(),
			new Stock7<double>(),
			new Stock8<double>()
		};

		almacen1 = new Almacen<RegistroAlmacen>(congelador);
		almacen2 = new Almacen<RegistroAlmacen>(refrigerado);
		almacen3 = new Almacen<RegistroAlmacen>(Abarrotes);

		//ProductosdelAlmacen ---- NO DISPONIBLES EN TOTTUS
		int i = 0;

		while (i < productosBase.size()) {

			switch (productosBase[i]->tipoAlmacenamiento) {
			case congelador: almacen1->agregarProducto(RegistroAlmacen(productosBase[i]));  break;
			case refrigerado: almacen2->agregarProducto(RegistroAlmacen(productosBase[i])); break;
			case Abarrotes: almacen3->agregarProducto(RegistroAlmacen(productosBase[i])); break;

			}
			i++;

		}

		ifstream adminis("ADMIN.txt");

		if (adminis.good()) {

			string linea;

			getline(adminis, linea);
			ingresosBrutos = stod(linea); //con descuento
			getline(adminis, linea);
			ingresosNetos = stod(linea); //sin descuento/cupon
			getline(adminis, linea);
			descuentoTotalProducido = stod(linea);

			getline(adminis, linea);
			int stock1 = stoi(linea);
			getline(adminis, linea);
			int stock2 = stoi(linea);
			getline(adminis, linea);
			int stock3 = stoi(linea);
			getline(adminis, linea);
			int stock4 = stoi(linea);
			getline(adminis, linea);
			int stock5 = stoi(linea);
			getline(adminis, linea);
			int stock6 = stoi(linea);
			getline(adminis, linea);
			int stock7 = stoi(linea);
			getline(adminis, linea);
			int stock8 = stoi(linea);

			Stock1<double>* p1;
			Stock2<double>* p2;
			Stock3<double>* p3;
			Stock4<double>* p4;
			Stock5<double>* p5;
			Stock6<double>* p6;
			Stock7<double>* p7;
			Stock8<double>* p8;
			Nodo<Producto<double>>* NodoPila; //
			
			// Stock 1
			while (stock1--) {
				p1 = new Stock1<double>();
				NodoPila = new Nodo<Producto<double>>(p1);
				ListaDeStock_1->push(NodoPila);
			}

			// Stock 2
			while (stock2--) {
				p2 = new Stock2<double>();
				NodoPila = new Nodo<Producto<double>>(p2);
				ListaDeStock_2->push(NodoPila);
			}

			// Stock 3
			while (stock3--) {
				p3 = new Stock3<double>();
				NodoPila = new Nodo<Producto<double>>(p3);
				ListaDeStock_3->push(NodoPila);  // <- ¿Esto debería ser ListaDeStock_3?
			}

			while (stock4--) {
				p4 = new Stock4<double>();
				NodoPila = new Nodo<Producto<double>>(p4);
				ListaDeStock_4->push(NodoPila);  // <- ¿Esto debería ser ListaDeStock_3?
			}
			while (stock5--) {
				p5 = new Stock5<double>();
				NodoPila = new Nodo<Producto<double>>(p5);
				ListaDeStock_5->push(NodoPila);  // <- ¿Esto debería ser ListaDeStock_3?
			}
			while (stock6--) {
				p6 = new Stock6<double>();
				NodoPila = new Nodo<Producto<double>>(p6);
				ListaDeStock_6->push(NodoPila);  // <- ¿Esto debería ser ListaDeStock_3?
			}
			while (stock7--) {
				p7 = new Stock7<double>();
				NodoPila = new Nodo<Producto<double>>(p7);
				ListaDeStock_7->push(NodoPila);  // <- ¿Esto debería ser ListaDeStock_3?
			}
			while (stock8--) {
				p8 = new Stock8<double>();
				NodoPila = new Nodo<Producto<double>>(p8);
				ListaDeStock_8->push(NodoPila);  // <- ¿Esto debería ser ListaDeStock_3?
			}

			listas = getPilas();
			adminis.close();
		}
		else {
			ofstream nuevooo("ADMIN.txt");
			for(int i =0; i<6; i++) nuevooo << 0<<endl;

			ingresosBrutos = 0; //con descuento
			ingresosNetos = 0; //sin descuento/cupon
			descuentoTotalProducido = 0;


			nuevooo.close();
			adminis.close();

		}


		clientes = new ListaEnlazada<Nodo<Cliente<string>>, string>();
		CajaRegistradora = new Cola<Nodo<Cliente<string>>>();
		CajaVirtual = new Cola<Nodo<Cliente<string>>>();
		ifstream archivo("RegistroClientes.txt");

		if (archivo.good()) {

			string linea;
			
			while (getline(archivo, linea)) {
				if (linea.find("Codigo:") != string::npos) {
					// Extraer código
					string codigo = linea.substr(linea.find(":") + 2);

					// Leer línea del nombre
					getline(archivo, linea);
					string nombre = linea.substr(linea.find(":") + 2); // +2 para omitir ": "

					// Leer línea del cupón
					getline(archivo, linea);
					string cuponStr = linea.substr(linea.find("?") + 2); // +2 para omitir "? "
					bool tieneCupon = (cuponStr == "SI");


					//carrito :>
					getline(archivo, linea);
					//A0001
					getline(archivo, linea);
					getline(archivo, linea);
					int can1 = stoi(linea);

					//A0002
					getline(archivo, linea);
					getline(archivo, linea);
					int can2 = stoi(linea);
					
					//A0003
					getline(archivo, linea);
					getline(archivo, linea);
					int can3 = stoi(linea);

					//A0004
					getline(archivo, linea);
					getline(archivo, linea);
					int can4 = stoi(linea);

					//A0005
					getline(archivo, linea);
					getline(archivo, linea);
					int can5 = stoi(linea);

					//A0006
					getline(archivo, linea);
					getline(archivo, linea);
					int can6 = stoi(linea);

					//A0007
					getline(archivo, linea);
					getline(archivo, linea);
					int can7 = stoi(linea);

					//A0008
					getline(archivo, linea);
					getline(archivo, linea);
					int can8 = stoi(linea);


					auto* cl = new Cliente<string>(codigo, nombre, tieneCupon, can1, can2, can3,can4,can5,can6,can7,can8);
					auto* nodo = new Nodo<Cliente<string>>(cl);
					clientes->AgregarElemento(nodo);

					//GUARDAR EL CARRITO DEL TXT :>
					// Mostrar resultado
					cout << "LEIDO: Código: " << codigo << ", Nombre: " << nombre
						<< ", Cupon: " << (tieneCupon ? "Sí" : "No") << endl;

					system("pause>0");
				}
			}

			archivo.close();
		}
		else {
			ofstream nuevo("RegistroClientes.txt");
			nuevo << "Registro de clientes: " << endl;
			nuevo.close();
			archivo.close();
		}

		ifstream archive("historial_compras.txt");

		if (archive.good()) {
			string linea, nombre, id;
			double total = 0.0, conDescuento = 0.0;
			vector<RegistroProducto> pro;

			while (getline(archive, linea)) {
				if (linea.find("Cliente: ") != string::npos) {
					nombre = linea.substr(linea.find(":") + 2);
				}
				else if (linea.find("id: ") != string::npos) {
					id = linea.substr(linea.find(":") + 2);
				}
				else if (linea.find("Monto Total: ") != string::npos) {
					total = stod(linea.substr(linea.find(":") + 2));
				}
				else if (linea.find("Monto a pagar: ") != string::npos) {
					conDescuento = stod(linea.substr(linea.find(":") + 2));
				}
				else if (linea == "-----------------------------") {
					Boleta* boleta = new Boleta(nombre, id, total, conDescuento, pro);
					boletas.push_back(boleta);
					pro.clear();
				}
				else if (linea.find("A0001") != string::npos ||
					linea.find("A0002") != string::npos ||
					linea.find("A0003") != string::npos ||
					linea.find("A0004") != string::npos || 
					linea.find("A0005") != string::npos ||
					linea.find("A0006") != string::npos ||
					linea.find("A0007") != string::npos ||
					linea.find("A0008")	!= string::npos)
					{

					// Extraer ID y precio
					string idProducto = linea.substr(0, linea.find(" |"));
					size_t pos = linea.find("Costo: ");
					double precio = stod(linea.substr(pos + 7)); // luego de "Costo: "

					pro.push_back(RegistroProducto(idProducto, precio));
				}
			}

			archive.close();
		}
		else {
			cout << "No se pudo abrir el archivo." << endl;
		}


	}



	void spriteStockCon3productos(Interfaz* canva, string nombrePrimerProd, string nombreSegProd, string nombreTerProd, TipoAlmacen tipo1, TipoAlmacen tipo2 = congelador, TipoAlmacen tipo3= congelador) {
		Color* newCol = new Color(9, 13);
		canva->ProductosStock();
		if (nombrePrimerProd != "") { 
			if (tipo1 == congelador) canva->carneSprite(16, 18);
			if (tipo1 == refrigerado) canva->Productogrande1(16, 18);
			if (tipo1 == Abarrotes) {
				int x = rand() % 2;
				if (x == 0) canva->Productogrande2(16, 18);
				else canva->Productogrande3(16, 18);
			}
		}
		if (nombreSegProd != "") {
			if (tipo2 == congelador) canva->carneSprite(47, 18);
			if (tipo2 == refrigerado) canva->Productogrande1(47, 18);
			if (tipo2 == Abarrotes) {
				int x = rand() % 2;
				if (x == 0) canva->Productogrande2(47, 18);
				else canva->Productogrande3(47, 18);
			}
		}
		if (nombreTerProd != "") {
			if (tipo3 == congelador) canva->carneSprite(82, 18);
			if (tipo3 == refrigerado) canva->Productogrande1(82, 18);
			if (tipo3 == Abarrotes) {
				int x = rand() % 2;
				if (x == 0) canva->Productogrande2(82, 18);
				else canva->Productogrande3(82, 18);
			}
		}
		canva->Imprimir(20, 27, newCol, nombrePrimerProd); 
		canva->Imprimir(52, 27, newCol, nombreSegProd);
		canva->Imprimir(84, 27, newCol, nombreTerProd);
	}

	void modificarListasStock(Producto<double>* p, int c, int acum, Interfaz* canva) {
		Nodo<Producto<double> >* NodoPila;
		NodoPila = new Nodo<Producto<double>>(p);
		if (p->tipo == 1) {
			while (c--) {
				ListaDeStock_1->push(NodoPila);
			}
		}
		if (p->tipo == 2) {
			while (c--) {
				ListaDeStock_2->push(NodoPila);
			}

		}
		if (p->tipo == 3) {
			while (c--) {
				ListaDeStock_3->push(NodoPila);
			}
		}
		if (p->tipo == 4) {
			while (c--) {
				ListaDeStock_4->push(NodoPila);
			}
		}
		if (p->tipo == 5) {
			while (c--) {
				ListaDeStock_5->push(NodoPila);
			}
		}
		if (p->tipo == 6) {
			while (c--) {
				ListaDeStock_6->push(NodoPila);
			}
		}
		if (p->tipo == 7) {
			while (c--) {
				ListaDeStock_7->push(NodoPila);
			}
		}
		if (p->tipo == 8) {
			while (c--) {
				ListaDeStock_8->push(NodoPila);
			}
		}
		canva->Imprimir(30, 30, new Color(9, 13), "Se han agregado " + to_string(acum) + " productos...:"); cout << "";
	}
	//el administrador agrega Stock MANUALMENTE AL SISTEMA
	void agregarStockDesdeAlmacen(Interfaz* canva, Color* col) {
		Color* newCol = new Color(9, 13);
		Color* colo = new Color(0, 2);
		Color* verde = new Color(8, 10);
		Color* marronbg = new Color(8, 16);
		Color* m = new Color(8, 14);
		int op;
		do {
			canva->almacenMenu();
			canva->Imprimir(41, 1, verde, "Categoria de los almacenes");
			canva->Imprimir(43, 3, colo, "Almacen 1: Congelador ");
			canva->Imprimir(43, 4, colo, "Almacen 2: Refrigerado ");
			canva->Imprimir(43, 5, colo, "Almacen 3: Abarrotes ");
			canva->Imprimir(43, 6, colo, "Almacen 4: Abarrotes ");


			canva->Imprimir(45, 15, colo, "[1] Buscar producto ");
			canva->Imprimir(41, 18, colo, "[2] Reporte productos de ");
			canva->Imprimir(48, 19, colo, "c/ almacen ");
			canva->Imprimir(39, 21, colo, "[3] Inventario de Productos ");
			canva->Imprimir(48, 24, colo, "[4] salir");
			canva->Imprimir(45, 27, verde, "Eliga opcion: ");
			cin >> op;

			if (op == 1) {
				int pagina = 0;
				int total = productosBase.size();
				int totalPaginas = (total + 2) / 3;
				string codigo;

				while (true) {
					system("cls");
					canva->ProductosStock(); // marco del menú

					// Mostrar productos por página
					int inicio = pagina * 3;
					int posx;
					for (int i = 0; i < 3 && (inicio + i) < total; ++i) {
						posx = 15 + i * 35;
						canva->Imprimir(posx, 26, newCol,
							productosBase[inicio + i]->nombre + " (" + productosBase[inicio + i]->id + ")");
					}

					canva->Imprimir(30, 14, verde, "[n] Siguiente | [p] Anterior | Ingrese código del producto:");
					cout << colores->BG_verdeMUYscuro;
					cin >> codigo;
					transform(codigo.begin(), codigo.end(), codigo.begin(), toupper);
					if (codigo == "N" && pagina < totalPaginas - 1) {
						pagina++;
						continue;
					}
					else if (codigo == "P" && pagina > 0) {
						pagina--;
						continue;
					}

					// Validación del código ingresado
					bool productoValidado = false;
					int i = 0;
					while (i < productosBase.size()) {
						if (codigo == productosBase[i]->id) {
							productoValidado = true;
							break;
						}
						i++;
					}
					if (!productoValidado) {
						canva->Imprimir(25, 19, new Color(0, 11), "Código incorrecto. Presione para continuar.");
						system("pause>0");
						continue;
					}

					// Buscar producto en su almacén
					NodoBB<RegistroAlmacen>* encontrado = new NodoBB<RegistroAlmacen>(RegistroAlmacen());
					switch (productosBase[i]->tipoAlmacenamiento) {
					case congelador: encontrado = almacen1->buscarProductoCodigo(RegistroAlmacen(productosBase[i])); break;
					case refrigerado: encontrado = almacen2->buscarProductoCodigo(RegistroAlmacen(productosBase[i])); break;
					case Abarrotes: encontrado = almacen3->buscarProductoCodigo(RegistroAlmacen(productosBase[i])); break;
					}

					if (encontrado) {
						int c, acum;
						do {
							system("cls");
							canva->ProductoConsultaTranseferencia();
							canva->Imprimir(37, 16, m, "Cantidad a transferir del almacen: ");
							cin >> c;

							if (encontrado->producto.cantidad >= c && c > 0) {
								acum = c;
								encontrado->producto.cantidad -= c;
								modificarListasStock(productosBase[i], c, acum, canva);
								canva->Imprimir(30, 18, m, "¡Transferencia completada! Presione para continuar.");
								system("pause>0");
								break;
							}
							else {
								canva->Imprimir(35, 25, m, "Cantidad inválida. Disponible: " + to_string(encontrado->producto.cantidad));
								system("pause>0");
							}
						} while (true);
					}
					else {
						canva->Imprimir(30, 26, m, "Producto no encontrado en el almacén.");
						system("pause>0");
					}
					break;
				}
			}

			if (op == 2) {

				canva->reporteAlmacen();
				almacen1->reporteProductos(12, 14, canva, colo);
				almacen2->reporteProductos(45, 14, canva, colo);
				almacen3->reporteProductos(83, 14, canva, colo);
				system("pause>0");
			}

			if (op == 3) {
				canva->Imprimir(21, 13, verde, "Mostrando Inventario...");
				int i = 0;
				int restantes;
				while (i < productosBase.size()) {
					system("cls");
					restantes = productosBase.size() - i;

					if (restantes >= 3) {
						spriteStockCon3productos(canva,
							productosBase[i]->nombre + "(" + productosBase[i]->id + ")",
							productosBase[i + 1]->nombre + "(" + productosBase[i+1]->id + ")",
							productosBase[i + 2]->nombre + "(" + productosBase[i+2]->id + ")",
							productosBase[i]->tipoAlmacenamiento,productosBase[i+1]->tipoAlmacenamiento,productosBase[i+2]->tipoAlmacenamiento);
					}
					else if (restantes == 2) {
						spriteStockCon3productos(canva,
							productosBase[i]->nombre + "(" + productosBase[i]->id + ")",
							productosBase[i + 1]->nombre + "(" + productosBase[i+1]->id + ")", 
							"", productosBase[i]->tipoAlmacenamiento, productosBase[i + 1]->tipoAlmacenamiento);
					}
					else if (restantes == 1) {
						spriteStockCon3productos(canva,
							productosBase[i]->nombre + "(" + productosBase[i]->id + ")",
							"",
							"", productosBase[i]->tipoAlmacenamiento);
					}
					i += 3;
					system("pause>0");
				}
					
			}


		} while (op != 4);


	}
	void eliminarTodoStock(Interfaz* canva) {
		Color* col = new Color(8, 10);
		Color* newCol = new Color(9, 13);

		// Crear lista de nombres y total de productos
		vector<string> nombres = {
			"Leche Gloria", "Arroz Costeño", "Atun Florida",
			"Yogurt SKYR", "Mantequilla", "Fideo Don Vitorio",
			"Pollo Fresco Entero", "Carne Molida"
		};

		int total = nombres.size();
		int pagina = 0;
		int totalPaginas = (total + 2) / 3; // redondeo hacia arriba

		while (true) {
			system("cls");
			canva->ProductosStock();
				canva->Productogrande1(16, 18);
				canva->Productogrande2(50, 18);
				canva->Productogrande3(82, 21);

			// Imprimir solo 3 productos por página
			int inicio = pagina * 3;
			for (int i = 0; i < 3 && (inicio + i) < total; ++i) {
				int posX = 20 + i * 32; // espacio horizontal entre productos
				canva->Imprimir(posX, 28, newCol, "[" + to_string(inicio + i + 1) + "] " + nombres[inicio + i]);

				// Opcional: imprimir sprite si ya tienes uno por producto
				// canva->ProductograndeX(posX, 18);
			}

			canva->Imprimir(26, 14, col, "Ingrese tipo (1-8) o [9] para eliminar todos.");
			canva->Imprimir(26, 15, col, "[n] Siguiente pagina | [p] Pagina anterior | [e] Eliminar");
			cout << colores->BG_verdeMUYscuro;

			string opcion;
			cin >> opcion;

			if (opcion == "n" && pagina < totalPaginas - 1) {
				pagina++;
			}
			else if (opcion == "p" && pagina > 0) {
				pagina--;
			}
			else if (opcion == "e") {
				int tipo;
				canva->Imprimir(26, 16, col, "Ingrese el número del producto a eliminar (1-8 o 9): ");
				cin >> tipo;

				int can = 0;
				switch (tipo) {
				case 1: can += ListaDeStock_1->vaciarPila(); break;
				case 2: can += ListaDeStock_2->vaciarPila(); break;
				case 3: can += ListaDeStock_3->vaciarPila(); break;
				case 4: can += ListaDeStock_4->vaciarPila(); break;
				case 5: can += ListaDeStock_5->vaciarPila(); break;
				case 6: can += ListaDeStock_6->vaciarPila(); break;
				case 7: can += ListaDeStock_7->vaciarPila(); break;
				case 8: can += ListaDeStock_8->vaciarPila(); break;
				case 9:
					can += ListaDeStock_1->vaciarPila();
					can += ListaDeStock_2->vaciarPila();
					can += ListaDeStock_3->vaciarPila();
					can += ListaDeStock_4->vaciarPila();
					can += ListaDeStock_5->vaciarPila();
					can += ListaDeStock_6->vaciarPila();
					can += ListaDeStock_7->vaciarPila();
					can += ListaDeStock_8->vaciarPila();
					break;
				default:
					canva->Imprimir(26, 17, col, "Opción no válida.");
					break;
				}

				canva->Imprimir(26, 18, col, "Se ha eliminado " + to_string(can) + " productos.");
				system("pause");
				break;
			}
		}
	}

	//uso de lambda
	void retornarSTOCKordenado() {
		system("cls");
		designer->interfazStockOrdenadoproduct(); cout << colores->RESET;
		int f = 18;
		auto ordenarSTOCK = [](auto orden, vector<Pila<Nodo<Producto<double>>>*>& vec, int low, int high) {
			if (vec.size() <= 1) { designer->Imprimir(30, 25, new Color(0, 2), "No hay suficientes stocks para odernar! "); return; }
			if (low < high) {
				int pi = partirStock(vec, low, high);
				orden(orden, vec, low, pi - 1);
				orden(orden, vec, pi + 1, high);
			}

			};

		vector<Pila<Nodo<Producto<double>>>*> v = getPilas();
		ordenarSTOCK(ordenarSTOCK, v, 0, v.size() - 1);
		if (v.size() >= 1) {
			for (int i = 0; i < v.size(); i++) {
				
				designer->Imprimir(38, f, new Color(0, 2), "Stock de " + v[i]->productoAlmacenado + " tiene " + to_string(v[i]->cantPila) + " unidades");

				f++;
			}
		}
	}

	void guardarCompraEnHistorial(Nodo<Cliente<string>>* cliente, ListaEnlazada<Nodo<Producto<double>>, int>* productos, double monto, double montoConDescuento) {
		Boleta* boleta = new Boleta(cliente->actual->nombre, cliente->actual->getCodigo(), monto, montoConDescuento, productos->cabeza);
		boletas.push_back(boleta);

		ofstream archivo("historial_compras.txt", ios::app);
		if (archivo.is_open()) {
			archivo << "Cliente: " << cliente->actual->nombre << "\n";
			archivo << "id: " << cliente->actual->tipo << endl;
			archivo << "Monto Total: " << monto << "\n";
			archivo << "Monto a pagar: " << montoConDescuento << "\n";
			archivo << "Productos comprados:\n";

			Nodo<Producto<double>>* temp = productos->cabeza;
			while (temp != nullptr) {
				archivo << temp->actual->id << " | Costo: " << temp->actual->precio << endl;
				temp = temp->next;
			}
			archivo << "-----------------------------\n";
			archivo.close();
		}
		else {
			cout << "No se pudo abrir el archivo de historial.\n";
		}
	}
	// version 1
	void MostrarComponentesDeINgresosCorporativos(Interfaz* canva, Color* c) {
		canva->mostrarIngresosCorporativo();
		int i = 0, j = 4;
		canva->Imprimir(44, 6 + (j * 0), c, "Cantidad De Productos Tipo 1: " + to_string(ListaDeStock_1->cantPila));
		canva->Imprimir(44, 6 + (j * 1), c, "Cantidad De Productos Tipo 2: " + to_string(ListaDeStock_2->cantPila));
		canva->Imprimir(44, 6 + (j * 2), c, "Cantidad De Productos Tipo 3: " + to_string(ListaDeStock_3->cantPila));
		canva->Imprimir(44, 6 + (j * 3), c, "Ingresos Brutos: " + to_string(ingresosBrutos));
		canva->Imprimir(44, 6 + (j * 4), c, "Ingresos Netos: " + to_string(ingresosNetos));
		canva->Imprimir(44, 6 + (j * 5), c, "Descuento Total Producido: " + to_string(descuentoTotalProducido));system("pause>0");
	}

	void mostrarClientes_Activos(Nodo<Cliente<string>>* head, Interfaz* canva, Color* c) {
		int j = 0; //para mover las columnas
		canva->interfazClientesActivosTienda();
		if (head != nullptr) {
			Nodo<Cliente<string>>* temp = head;
			canva->Imprimir(18, 20, c, "Clientes registrados activos en tienda:");
			while (temp != nullptr) {
				canva->Imprimir(18 + (j * 20), 22, c, "Nombre: " + temp->actual->nombre);
				canva->Imprimir(18 + (j * 20), 23, c, "Id: " + temp->actual->tipo);
				j++;
				temp = temp->next;
			}
		}
	}

	void generarBoletaElectronica(Interfaz* canva) {
		canva->AdminBoletas();
		ifstream compras("historial_compras.txt");

		if (!compras.is_open()) {
			cerr << "No se pudo abrir el archivo." << endl;
			return;
		}
		canva->Imprimir(0,0, new Color(0, 8));
		int x = 1, y = 15;
		int cant = 0; //solo se puede mostrar 3 boletas

		string linea;
		while (getline(compras, linea)) {
			// Mostrar cada línea del archivo
			if (cant == 4) {
				system("pause>0"); 
				cant = 0; 
				canva->AdminBoletas();
				x = 1; y = 15; 	
			}
			if (linea == "-----------------------------") {
				y = 15;
				x += 28;
				cant++;
				continue;
			}

			canva->Imprimir(x, y, new Color(0, 8), linea);
			y++;
		}

		compras.close();

		system("pause>0");

	}

	void ordenarBoletasDescendentemente(Interfaz* canva) {
		//canva->AdminBoletas(); --- matriz de boletas ordenadas 
		vector<Boleta*> temp = boletas;

		mergeSortBoletasDescendente(temp, 0, temp.size() - 1);
		canva->AdminBoletas();
		canva->Imprimir(0, 0, new Color(0, 8));
		int x = 1, y = 15;
		int cant = 0; //solo se puede mostrar 3 boletas

		int i = 0;
		while (i < temp.size()) {

			if (cant == 4) {
				system("pause>0");
				cant = 0;
				canva->AdminBoletas();
				x = 1, y = 15;
			}


			canva->Imprimir(x, y, new Color(0, 8), "Cliente: " + temp[i]->nombreCliente);
			canva->Imprimir(x, y + 1, new Color(0, 8), "id : " + temp[i]->idCliente);
			canva->Imprimir(x, y + 2, new Color(0, 8), "monto: " + to_string(temp[i]->monto));
			canva->Imprimir(x, y + 3, new Color(0, 8), "montofinal: " + to_string(temp[i]->montoDescuento));
			canva->Imprimir(x, y + 4, new Color(0, 8), "Productos comprados: ");

			for (size_t j = 0; j < temp[i]->boughtp.size(); j++)
			{
				canva->Imprimir(x, y + 5 + j, new Color(0, 8));
				cout << temp[i]->boughtp[j].id;
				cout << "| costo: ";
				cout << temp[i]->boughtp[j].precio;

				canva->Imprimir(x, y + 6 + j, new Color(0, 8));
			}
			x = x + 28;
			y = 15;
			i++;
			cant++;

		}

	}



	Nodo<Cliente<string>>* ordenadosClientes(Nodo<Cliente<string>>* client) {

		//Nodo<Cliente<string>>* client = clientes->cabeza;

		if (!client || !client->next) { return client; }

		Nodo<Cliente<string>>* mitad = dividirLista(client);
		Nodo<Cliente<string>>* izq = ordenadosClientes(client);
		Nodo<Cliente<string>>* der = ordenadosClientes(mitad);

		return juntarListas(izq, der);
	}

	T& valIngresosBrutos() {
		return ingresosBrutos;
	}
	T& valIngresosNetos() {
		return ingresosNetos;
	}
	T& valdescuentoTotalProducido() {
		return descuentoTotalProducido;
	}

	vector<Pila<Nodo<Producto<double>>>*> getPilas() {
		vector<Pila<Nodo<Producto<double>>>*> stocks;
		if (!ListaDeStock_1->estaVacia()) { stocks.push_back(ListaDeStock_1); }
		if (!ListaDeStock_2->estaVacia()) { stocks.push_back(ListaDeStock_2); }
		if (!ListaDeStock_3->estaVacia()) { stocks.push_back(ListaDeStock_3); }
		if (!ListaDeStock_4->estaVacia()) { stocks.push_back(ListaDeStock_4); }
		if (!ListaDeStock_5->estaVacia()) { stocks.push_back(ListaDeStock_5); }
		if (!ListaDeStock_6->estaVacia()) { stocks.push_back(ListaDeStock_6); }
		if (!ListaDeStock_7->estaVacia()) { stocks.push_back(ListaDeStock_7); }
		if (!ListaDeStock_8->estaVacia()) { stocks.push_back(ListaDeStock_8); }
		return stocks;
	}


};