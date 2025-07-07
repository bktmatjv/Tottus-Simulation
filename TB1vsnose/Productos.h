
#pragma once


enum TipoAlmacen { congelador = 0, refrigerado = 1, Abarrotes = 2 };

template<typename T>

class Producto {

public:
	string id;
	int tipo;
	T precio;
	string nombre;
	T capacidad;
	TipoAlmacen tipoAlmacenamiento;
	Producto() {}

	~Producto() {}

	string getID() { return id; }

	virtual void mostrar_info(Color* c) = 0;

};



//LECHE GLORIA

template< typename T>

class Stock1 : public Producto<T> {

public:

	Stock1() : Producto<T>() {

		id = "A0001";

		tipo = 1;

		precio = 4.99;

		capacidad = 1;

		tipoAlmacenamiento = refrigerado;

		nombre = "Leche fresca ";

	}



	void mostrar_info(Color* c) override {

		cout << "Producto: Leche fresca" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " lata." << endl;

	}



};



//ARROZ COSTEÑO

template<typename T>

class Stock2 : public Producto<T> {

public:

	Stock2() : Producto<T>() {

		id = "A0002";

		tipo = 2;

		precio = 3.00;

		capacidad = 1;

		tipoAlmacenamiento = Abarrotes;

		nombre = "Arroz costeno";

	}

	void mostrar_info(Color* c) override {

		cout << "Producto: Arroz Costeno" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " kg." << endl;

	}

};



//ATUN FLORIDA

template<typename T>

class Stock3 : public Producto<T> {

public:

	Stock3() : Producto<T>() {

		id = "A0003";

		tipo = 3;

		precio = 1.99;

		capacidad = 1;

		tipoAlmacenamiento = Abarrotes;

		nombre = "Atun Florida";

	}

	void mostrar_info(Color* c) override {

		cout << "Producto: Atun Florida" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " pieza" << endl;

	}

};


template <typename T>
class Stock4 : public Producto<T> {

public:

	Stock4() : Producto<T>() {

		id = "A0004";

		tipo = 4;

		precio = 20.00;

		capacidad = 1;

		tipoAlmacenamiento = refrigerado;

		nombre = "Yogurt SKYR";

	}

	void mostrar_info(Color* c) override {

		cout << "Producto: Yogurt SKYR" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " pieza" << endl;

	}

};

//MANTEQUILLA 

template <typename T>
class Stock5 : public Producto<T> {

public:

	Stock5() : Producto<T>() {

		id = "A0005";

		tipo = 5;

		precio = 15.00;

		capacidad = 1;

		tipoAlmacenamiento = refrigerado;

		nombre = "Mantequilla";

	}

	void mostrar_info(Color* c) override {

		cout << "Producto: Matenquilla" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " pieza" << endl;

	}

};

//FIDEO

template <typename T>
class Stock6 : public Producto<T> {

public:

	Stock6() : Producto<T>() {

		id = "A0006";

		tipo = 6;

		precio = 8.00;

		capacidad = 1;

		tipoAlmacenamiento = Abarrotes;

		nombre = "Fideo Don Vitorio";

	}

	void mostrar_info(Color* c) override {

		cout << "Producto: Fideo Don Vitorio" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " pieza" << endl;

	}

};

//POLLO FRESCO 

template <typename T>
class Stock7 : public Producto<T> {

public:

	Stock7() : Producto<T>() {

		id = "A0007";

		tipo = 7;

		precio = 23.00;

		capacidad = 1;

		tipoAlmacenamiento = congelador;

		nombre = "Pollo Fresco Entero";

	}

	void mostrar_info(Color* c) override {

		cout << "Producto: Pollo Fresco Entero" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " pieza" << endl;

	}

};

//CARNE 
template <typename T>
class Stock8 : public Producto<T> {

public:

	Stock8() : Producto<T>() {

		id = "A0008";

		tipo = 8;

		precio = 25.00;

		capacidad = 1;

		tipoAlmacenamiento = congelador;

		nombre = "Carne Molida";

	}

	void mostrar_info(Color* c) override {

		cout << "Producto: Carne Molida" << endl;

		cout << "ID: " << id << endl;

		cout << "Precio: S/. " << precio << endl;

		cout << "Capacidad: " << capacidad << " pieza" << endl;

	}

};