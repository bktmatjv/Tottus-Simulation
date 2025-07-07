#include "iostream"
#include "EstructurasDeDatos.h"
#include "string"
#include "queue"
#include "list"
#include "vector"
#include "fstream"
using namespace std;
    
template <typename clase>
class TablaHash {
private:
    list <clase> Tabla[100];
    int get_Indice(string codigoDeUsuario) {
        int suma = 0;
        for (int i = 0;i < codigoDeUsuario.size(); i++) {
            suma += codigoDeUsuario[i];
        }
        return abs(suma) % 100;
    }
public:
    TablaHash() {}
    void Anadir(clase* cla) {
        int indice = get_Indice(cla->codigoUsuario);

        for (auto& l : Tabla[indice]) {
            if (cla->codigoUsuario == l.codigoUsuario) {
                l.ind = cla->ind;
                return;
            }
        }
        Tabla[indice].push_back({ *cla });

    }
    int Indice_Persona(clase* cla) {
        int indice = get_Indice(cla->codigoUsuario);
        for (auto l : Tabla[indice]) {
            if (cla->codigoUsuario == l.codigoUsuario
                && cla->contrasenia == l.contrasenia
                ) {
                return l.ind;
            }
        }
    }
    void Actualizar_Indice(clase* cla, int ind) {
        int indice = get_Indice(cla->codigoUsuario);
        for (auto& l : Tabla[indice]) {
            if (cla->codigoUsuario == l.codigoUsuario) {
                l.ind = ind;
            }
        }
    }
};
class Persona {
public:
    string nombre, contrasenia, codigoUsuario, jefe;
    int ind;
    Persona(string n, string cod, string con, string jefee) {
        nombre = n; codigoUsuario = cod; contrasenia = con; jefe = jefee;
        ind = -1;
    }
};

TablaHash<Persona>* th = new TablaHash<Persona>();


template <typename clase>
class Nodo_Binario {
public:
    int n;
    clase* Informacion;
    Nodo_Binario<clase>* LEFT;
    Nodo_Binario<clase>* RIGHT;
    Nodo_Binario() {
        LEFT = RIGHT = nullptr;
        Informacion = nullptr;
        n = 0;
    }
    void add(clase* p) {
        if (n == 0) {
            LEFT = new Nodo_Binario<clase>();
            LEFT->Informacion = p;
            n++;
        }
        else if (n == 1) {
            RIGHT = new Nodo_Binario<clase>();
            RIGHT->Informacion = p;
            n++;
        }
    }
};



template <typename clase>
class Arbol_Binario {
    Nodo_Binario<clase>* cabeza;
    int cnt;
public:
    Arbol_Binario() {
        cabeza = nullptr;
        cargar_datos();
        cnt = 1;
        cout << endl;
    }
    void cargar_datos() {
        ifstream texto("ARBOL_BINARIO.txt", ios::in);
        if (!texto.is_open()) {
            ofstream crear("ARBOL_BINARIO.txt");
            crear.close();
            texto.open("ARBOL_BINARIO.txt");
        }
        if (texto.peek() == EOF) {
            texto.close();
            clase* persona = new clase("TOTTUS", "TOTTUS", "contrasenia", "-");
            Nodo_Binario<clase>* raiz = new Nodo_Binario<clase>();
            raiz->Informacion = persona;
            this->cabeza = raiz;
            cnt = 1;
            Asignar_Indice(cabeza);
            ofstream escribir("ARBOL_BINARIO.txt", ios::out);
            escribir << "TOTTUS\nTOTTUS\ncontrasenia\n-\n";
            escribir.close();
            return;
        }

        queue<Nodo_Binario<clase>*> nodos;
        string nombre, codigo, contrasenia, jefe;

        if (!getline(texto, nombre)) return;
        if (!getline(texto, codigo)) return;
        if (!getline(texto, contrasenia)) return;
        if (!getline(texto, jefe)) return;

        clase* persona = new clase(nombre, codigo, contrasenia, jefe);
        Nodo_Binario<clase>* raiz = new Nodo_Binario<clase>();
        raiz->Informacion = persona;
        this->cabeza = raiz;
        nodos.push(raiz);

        string linea;
        while (!nodos.empty()) {
            Nodo_Binario<clase>* actual = nodos.front();
            nodos.pop();
            if (!getline(texto, linea)) break;
            if (linea != "-1") {
                string codL, conL, jefL;
                if (!getline(texto, codL)) break;
                if (!getline(texto, conL)) break;
                if (!getline(texto, jefL)) break;

                clase* hijoIzq = new clase(linea, codL, conL, jefL);
                actual->LEFT = new Nodo_Binario<clase>();
                actual->LEFT->Informacion = hijoIzq;
                nodos.push(actual->LEFT);
            }
            if (!getline(texto, linea)) break;
            if (linea != "-1") {
                string codR, conR, jefR;
                if (!getline(texto, codR)) break;
                if (!getline(texto, conR)) break;
                if (!getline(texto, jefR)) break;

                clase* hijoDer = new clase(linea, codR, conR, jefR);
                actual->RIGHT = new Nodo_Binario<clase>();
                actual->RIGHT->Informacion = hijoDer;
                nodos.push(actual->RIGHT);
            }
        }

        texto.close();
        cnt = 1;
        Asignar_Indice(cabeza);
    }
    void Guardar_datos() {
        ofstream texto("ARBOL_BINARIO.txt", ios::out);
        if (!texto.is_open()) {
            cout << "No se pudo abrir el archivo para escritura.\n";
            return;
        }
        queue<Nodo_Binario<clase>*> colita;
        if (cabeza == nullptr) {
            texto.close();
            return;
        }
        colita.push(cabeza);
        texto << cabeza->Informacion->nombre << endl;
        texto << cabeza->Informacion->codigoUsuario << endl;
        texto << cabeza->Informacion->contrasenia << endl;
        texto << cabeza->Informacion->jefe << endl;
        while (!colita.empty()) {
            Nodo_Binario<clase>* actual = colita.front();
            if (actual->LEFT != nullptr) {
                texto << actual->LEFT->Informacion->nombre << endl;
                texto << actual->LEFT->Informacion->codigoUsuario << endl;
                texto << actual->LEFT->Informacion->contrasenia << endl;
                texto << actual->LEFT->Informacion->jefe << endl;
                colita.push(actual->LEFT);
            }
            else {
                texto << -1 << endl;
            }

            if (actual->RIGHT != nullptr) {
                texto << actual->RIGHT->Informacion->nombre << endl;
                texto << actual->RIGHT->Informacion->codigoUsuario << endl;
                texto << actual->RIGHT->Informacion->contrasenia << endl;
                texto << actual->RIGHT->Informacion->jefe << endl;
                colita.push(actual->RIGHT);
            }
            else {
                texto << -1 << endl;
            }

            colita.pop();
        }

        texto.close();
    }


    void Asignar_Indice(Nodo_Binario<clase>* actual) {
        if (actual == nullptr)return;
        if (actual->LEFT != nullptr) {
            Asignar_Indice(actual->LEFT);
        }
        actual->Informacion->ind = cnt;
        th->Anadir(actual->Informacion);
        cnt++;
        if (actual->RIGHT != nullptr) {
            Asignar_Indice(actual->RIGHT);
        }
    }

    Nodo_Binario<clase>* Busqueda(int ind) {
        Nodo_Binario<clase>* actual = cabeza;
        while (actual != nullptr) {
            //cout << actual->Informacion->ind << "   "<< ind << endl;
            if (actual->Informacion->ind == ind)return actual;
            if (actual->Informacion->ind < ind) {
                actual = actual->RIGHT;
            }
            else {
                actual = actual->LEFT;
            }
        }
        return nullptr;
    }
    bool Anadir_Nodo(clase* P, int ind) {
        Nodo_Binario<clase>* jefe = Busqueda(ind);
        if (jefe == nullptr) {
            return 0;
        }
        if (jefe->LEFT != nullptr && jefe->RIGHT != nullptr) {
            cout << jefe->LEFT->Informacion->codigoUsuario << "  " << jefe->RIGHT->Informacion->codigoUsuario << endl;
            cout << "No se pueden agregar mas subordinados directos"; return 0;
        }

        if (jefe->LEFT == nullptr) {
            jefe->LEFT = new Nodo_Binario<clase>();
            jefe->LEFT->Informacion = P;
        }
        else if (jefe->RIGHT == nullptr) {
            jefe->RIGHT = new Nodo_Binario<clase>();
            jefe->RIGHT->Informacion = P;
        }
        Asignar_Indice(cabeza);
        Guardar_datos();
        return 1;
    }

};


class Usuarios {
private:
    vector <pair< string, string>> usuario;
    Persona* persona_Actual;
    Arbol_Binario<Persona>* arbol;
public:
    Usuarios() {
        cargar_datos();
        arbol = new Arbol_Binario<Persona>();
        persona_Actual = nullptr;
    }
    void merge(vector<pair<string, string>>& c, int lo, int mid, int hi) {
        vector <pair<string, string>> VRIGHT, VLEFT;
        for (int i = lo; i <= mid; i++)VLEFT.push_back({ c[i].first, c[i].second });
        for (int i = mid + 1; i <= hi; i++)VRIGHT.push_back({ c[i].first, c[i].second });

        int indLEFT = 0, ind = lo, indRIGHT = 0;
        while (ind <= hi) {
            if (indLEFT != VLEFT.size() && indRIGHT != VRIGHT.size()) {
                if (VLEFT[indLEFT].first < VRIGHT[indRIGHT].first) {
                    c[ind] = VLEFT[indLEFT];
                    indLEFT++;
                }
                else {
                    c[ind] = VRIGHT[indRIGHT];
                    indRIGHT++;
                }
            }
            else if (indLEFT != VLEFT.size()) {
                c[ind] = VLEFT[indLEFT];
                indLEFT++;
            }
            else {
                c[ind] = VRIGHT[indRIGHT];
                indRIGHT++;
            }
            ind++;
        }
    }
    void merge_sort(vector<pair<string, string>>& usuario, int lo, int hi) {
        if (usuario.size() == 0)return;
        if (lo == hi)return;
        int mid = lo + (hi - lo) / 2;
        merge_sort(usuario, lo, mid);
        merge_sort(usuario, mid + 1, hi);
        merge(usuario, lo, mid, hi);
    }
    bool Econtrar_Contrasenia(string codigo, string contrasenia) {
        string rpt = "\nEl Usuario y/o contrasenia incorrecta";
        int mid, lo = 0, hi = usuario.size() - 1;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (usuario[mid].first == codigo) {
                if (usuario[mid].second == contrasenia) {
                    persona_Actual = arbol->Busqueda(th->Indice_Persona(new Persona("k", codigo, contrasenia, "-")))->Informacion;
                    // cout << persona_Actual->ind; 
                    cout << "\nBienvenido! "; return 1;
                }
                cout << "\nContrasenia incorrecta "; return 0;
            }
            else if (usuario[mid].first > codigo) {
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }
        cout << "Usuario no encontrado" << endl; 
        return 0;
    }
    bool Buscar_Empleado(string codigo) {
        int mid, lo = 0, hi = usuario.size() - 1;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (usuario[mid].first == codigo) {
                return 1;
            }
            else if (usuario[mid].first > codigo) {
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }
        return 0;
    }
    void guardar_datos(string e, string cod, string con, string jefe) {
        ofstream txt;
        txt.open("EMPLEADOS.txt", ios::out | ios::app);
        if (txt.is_open()) {
            txt << e << endl;
            txt << cod << endl;
            txt << con << endl;
            txt << jefe << endl;
        }
        usuario.push_back({ cod, con });
        merge_sort(usuario, 0, usuario.size() - 1);
    }

    void curss(int x, int y) {
        Console::SetCursorPosition(x, y);
    }

    void Anadir_Empleado(Interfaz* d) {
        system("cls");

        d->MENUAGREGAREMPLEADOS();

        if (persona_Actual == nullptr) {
            cout << "NO EXITSE\n";
            return;
        }
        string empleado, contra, codigo;

        d->Imprimir(6, 20, new Color(0, 2), "Ingrese el nombre del empleado: "); 
        curss(6, 21);
        cin.ignore(); getline(cin, empleado);

        d->Imprimir(60, 19, new Color(0, 2), "Ingrese codigo de usuario: "); cin >> codigo;

       d->Imprimir(60, 25, new Color(0, 2), "Ingrese contrasenia: "); cin >> contra;

   
        if (!Buscar_Empleado(codigo) && arbol->Anadir_Nodo(new Persona(empleado, codigo, contra, this->persona_Actual->codigoUsuario), th->Indice_Persona(persona_Actual))) {
            guardar_datos(empleado, codigo, contra, this->persona_Actual->codigoUsuario);
            cout << "Anadido con exito" << endl; 
            //cout << th->Indice_Persona(new Persona(empleado, codigo, contra, this->persona_Actual->codigoUsuario)) << endl;
        }
        else {
            cout << "YA HAY ESE EMPLEADO." << endl;
        }

    }

    void cargar_datos() {
        ifstream texto;
        ofstream txt;
        Persona* per;
        int cnt = 0;
        texto.open("EMPLEADOS.txt", ios::in);
        if (texto.is_open()) {
            while (!texto.eof()) {
                cnt++;
                string e, con, jef, cod;
                getline(texto, e);
                getline(texto, cod);
                getline(texto, con);
                getline(texto, jef);
                usuario.push_back({ cod,con });
            }
            texto.close();
        }
        if (cnt == 0) {
            txt.open("EMPLEADOS.txt", ios::out);
            if (txt.is_open()) {
                txt << "TOTTUS" << endl;
                txt << "TOTTUS" << endl;
                txt << "contrasenia" << endl;
                txt << "-" << endl;
                usuario.push_back({ "TOTTUS", "contrasenia" });
            }
            txt.close();
        }
        merge_sort(usuario, 0, usuario.size() - 1);
    }
};