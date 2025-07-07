#include "pch.h"
#include "Cuentas_Personal.h"
#include "iostream"
#include "Admin.h"
#include "conio.h"
using namespace System;
using namespace std;

Usuarios* usuarios = new Usuarios();
Mapa* mapita = new Mapa;

int menuCliente(Nodo <Cliente<string>>* nodo) {

    system("cls");

    designer->interfazPerspectivaCliente();

    int x, y;

    x = 40;

    y = 15;

    designer->Imprimir(39, 15, new Color(8, 10), "   CARRITO DEL CLIENTE : ");  con->cursor(x + 23, y); cout << nodo->actual->nombre << " |\n";

    designer->Imprimir(40, 15, new Color(0, 2));

    con->cursor(x - 15, y + 4); cout << "[1] Volver\n";

    con->cursor(x - 25, y + 8); cout << "[2] Agregar producto al carrito\n";

    con->cursor(x + 29, y + 4); cout << "[3] Eliminar producto del carrito\n";

    con->cursor(x + 32, y + 8); cout << "[4] Ver lista de carrito\n";

    int t;

    designer->Imprimir(x, y, new Color(8, 10));

    con->cursor(x, y + 12);cout << "Seleccione una opcion: "; cin >> t;

    return t;

}
auto validacionAdministrador = [](Interfaz *d) {
    Color* c = new Color(0, 11);
    string ingreso;
    //designer->interfazContra();
    //system("cls");
    string nombre, con; 
    d->Imprimir(30, 20, c, "Ingrese el nombre de usuario: "); cin >> nombre;
    d->Imprimir(30, 26, c, "Ingrese la contrasenia: "); cin >> con;

    //designer->PosicionarCord(50, 15);
    //designer->Imprimir(50, 15, c);
    //cin >> ingreso;
    cout << colores->RESET;

    return (usuarios->Econtrar_Contrasenia(nombre, con));

    };

int BloquearAcceso(int fallos, Interfaz* d) {
    //fallo 3 veces 

    d->iniciasSesionADMIN();

    if (fallos == 0) { return 0; }
    // Ingreso la contraseña correcta 
    if (validacionAdministrador(d)) {
        return 1;
    }
    else {
        system("cls");

        Color* c = new Color(0, 2);
        designer->Imprimir(30, 15, c, "Contraseña incorrecta. Intentos restantes: ");
        cout << (fallos - 1) << " restantes.";
        _sleep(5000);
        cout << colores->RESET;
        //system("cls");
        return BloquearAcceso(fallos - 1, d);
    }

}
void habilitarColoresAnsi() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
int main()
{
    // Dibujar la interfaz
    Console::ResetColor();
    Console::CursorVisible = 0;

    auto menuPrincipal = []() {
        designer->interfazPresentacion();
        int x, y, i;
        x = 50;
        y = 16;
        i = 4;
        Color* c = new Color(0, 2);
        designer->Imprimir(x, y, c, "[1] Administrador");
        designer->Imprimir(x + 3, y + i, c, "[2] Cliente");
        designer->Imprimir(x + 2, y + 2 * i, c, "[3] Personal");
        designer->Imprimir(x - 20, y + 3 * i, c, "Seleccione el tipo de usuario en el que pertenece : ");
        int t; cin >> t; cout << colores->RESET;
        return t;
        };

    auto menuPersonal = [](Sistema <double>* ADMIN) {
        int opcion;
        do {
            designer->interfazPersonal();
            designer->Imprimir(45, 18, new Color(0, 2), "[1] Cerrar Sesion");
            designer->Imprimir(45, 22, new Color(0, 2), "[2] Atender cola ");
            designer->Imprimir(45, 23, new Color(0, 2), "de Caja Registradora");
            designer->Imprimir(45, 27, new Color(0, 2), "[3] Atender Delivery");

            designer->Imprimir(0, 0, new Color(8, 10), "Seleccione una opcion: ");
            cin >> opcion;
            if (opcion == 2) {
                designer->CajaAtiendeCola();
                int n = ADMIN->CajaRegistradora->getN();
                int x = 35, y = 16;
                for (int i = 0; i < min(n, 4); i++) {
                    designer->dibujarClienteEnCarrito(x, y);
                    x += 18;
                }
                system("pause>0");
                Nodo<Cliente<string>>* caja = ADMIN->CajaRegistradora->EliminarElemento();

                if (caja != nullptr) {
                    caja->actual->PagarCarrito(ADMIN->valIngresosBrutos(), ADMIN->valIngresosNetos(), ADMIN->valdescuentoTotalProducido());
                    if (caja->actual->carrito->cantidadLista > 0)ADMIN->guardarCompraEnHistorial(caja, caja->actual->carrito, caja->actual->retornarMonto(), caja->actual->montoTotalAPagar);
                    ADMIN->generarBoletaElectronica(designer);
                }
            }


            if (opcion == 3) {

                int n = ADMIN->CajaVirtual->getN();

                designer->menuAtenderCaja();
                designer->Imprimir(20, 15, new Color(0, 2), "[1] Volver");
                designer->Imprimir(20, 20, new Color(0, 2), "[2] Ver mapa ");
                designer->Imprimir(20, 23, new Color(0, 2), "[3] Pagar Delivery");



                int x = 35, y = 16;
                int option; cin >> option;
                Nodo<Cliente<string>>* caja = ADMIN->CajaVirtual->EliminarElemento();

                if (caja->actual == nullptr) {
                    designer->Imprimir(70, 10, new Color(0, 2), "No hay clientes disponibles.");

                }
                else {
                    cursor(70, 10);
                    caja->actual->mostrar_info(new Color(0, 2));
                }

                do {


                    if (option == 2) {
                        
                        system("cls");
                        designer->mapa_Tottus();

                        if (caja->actual == nullptr) {
                            designer->Imprimir(40, 20, new Color(0, 2), "No hay clientes disponibles.");
                        }
                        else {
                            mapita->dibujarCamino(*caja->actual->ruta, caja->actual->nodIn, caja->actual->NodFin);
                            system("pause>0");
                            system("cls");


                            caja->actual->ruta->mostrarINFO_de_Grafo();

                        }

                        system("pause>0");




                    }
                    if (option == 3) {

                        if (caja != nullptr) {
                            caja->actual->PagarCarrito(ADMIN->valIngresosBrutos(), ADMIN->valIngresosNetos(), ADMIN->valdescuentoTotalProducido());
                            if (caja->actual->carrito->cantidadLista > 0)ADMIN->guardarCompraEnHistorial(caja, caja->actual->carrito, caja->actual->retornarMonto(), caja->actual->montoTotalAPagar);
                            ADMIN->generarBoletaElectronica(designer);
                        }

                        system("pause>0");
                    }
                    system("cls");
                    designer->menuAtenderCaja();
                    designer->Imprimir(20, 15, new Color(0, 2), "[1] Volver");
                    designer->Imprimir(20, 20, new Color(0, 2), "[2] Ver mapa ");
                    designer->Imprimir(20, 23, new Color(0, 2), "[3] Pagar Delivery");


                    cin >> option;
                } while (option != 1);



            }


            system("pause>0");
        } while (opcion != 1);
        };

    //ADMINISTRADOR
    auto menuAdministrador = [](Sistema<double>* ADMIN) {
        int opcion;
        do {
            designer->interfazAdmin();
            Color* c = new Color(0, 2);
            int i, j;
            i = 4;
            j = 48;
            int mul = 0;
            designer->Imprimir(18, 14, c, " [1] Cerrar Sesion");
            designer->Imprimir(22 + j, 11, c, "  [2] Monitorear los ");
            designer->Imprimir(22 + j, 12, c, "   clientes en tienda");
            designer->Imprimir(16, 13 + i, c, "[3] Mostrar a los clientes por");
            designer->Imprimir(16, 14 + i, c, " codigo en orden ascendente");
            designer->Imprimir(22 + j, 12 + i, c, "   [4] Modulo de Almacen ");
            designer->Imprimir(18, 14 + i + i, c, "[5] Eliminar todo el stock");
            designer->Imprimir(22 + j, 11 + i + i, c, "[6] Ordenar stock de mayor a");
            designer->Imprimir(22 + j, 12 + i + i, c, "           menor");
            designer->Imprimir(18, 13 + i + i + i, c, "[7] Mostrar componentes de");
            designer->Imprimir(18, 14 + i + i + i, c, "Ingresos Corporativos");
            designer->Imprimir(22 + j, 12 + i + i + i, c, "[8] Historial de Boletas");
            designer->Imprimir(22 + j, 15 + i + i + i, c, "[9] Agregar empleado");
            //OPCION 9 = AGREGAR EMPLEADO 
            //cout << "\n________ MENU ADMINISTRADOR _________\n";
            designer->PosicionarCord(60, 28);
            cin >> opcion;

            switch (opcion) {
            case 1:
           
                return;
            case 2:ADMIN->mostrarClientes_Activos(ADMIN->clientes->cabeza, designer, c); cout << colores->RESET;  break;
            case 3:
                designer->interfazClientesActivosTienda();
                ADMIN->clientes->cabeza = ADMIN->ordenadosClientes(ADMIN->clientes->cabeza);
                ADMIN->mostrarClientes_Activos(ADMIN->clientes->cabeza, designer, c); cout << colores->RESET;  break;
            case 4: ADMIN->agregarStockDesdeAlmacen(designer, c);  cout << colores->RESET;  break;
            case 5: ADMIN->eliminarTodoStock(designer);   cout << colores->RESET; break;
            case 6: ADMIN->retornarSTOCKordenado(); cout << colores->RESET;  break;
            case 7: ADMIN->MostrarComponentesDeINgresosCorporativos(designer, c); cout << colores->RESET;   break;
            case 8: /*ADMIN->generarBoletaElectronica(designer); */ 
                ADMIN->ordenarBoletasDescendentemente(designer);
                cout << colores->RESET; break;
            case 9:
                usuarios->Anadir_Empleado(designer); 
                break; 
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
            system("pause>0");

        } while (opcion != 1);

        };

    //CLIENTES

    auto menuClientes = []() {

        Interfaz* canva = new Interfaz;

        canva->interfazCliente();

        Color* col = new Color(9, 2);
        canva->Imprimir(20, 20, col, "[1] Cerrar Sesion");
        canva->Imprimir(70, 20, col, "[2] Agregar cliente");
        canva->Imprimir(20, 24, col, "[3] Cliente sale de Tottus");
        canva->Imprimir(70, 24, col, "[4] Carrito del cliente");
        canva->Imprimir(20, 28, col, "[5] Cliente va a pagar");
        canva->Imprimir(70, 28, col, "[6] Mostrar informacion ");
        canva->Imprimir(70, 29, col, "de todos los clientes ");
        int t;
        canva->Imprimir(50, 30, col, "Seleccione una opcion : "); cin >> t;
        cout << colores->RESET;
        return t;
        };

    auto EleccionCliente = [](int op, Cliente<string>* cliente, Cola<Nodo<Cliente<string>>>* CajaRegistradora, Pila<Nodo<Producto<double>>>* L1, Pila<Nodo<Producto<double>>>* L2, Pila<Nodo<Producto<double>>>* L3, Pila<Nodo<Producto<double>>>* L4, Pila<Nodo<Producto<double>>>* L5, Pila<Nodo<Producto<double>>>* L6, Pila<Nodo<Producto<double>>>* L7, Pila<Nodo<Producto<double>>>* L8, Sistema<double>* ADMIN) {
        //Cliente<string>* cliente = 
       
        switch (op) {
        case 2:
            designer->ProductosStock();
            cliente->AgregarEnCarrito(designer,ADMIN->listas);
            cout << colores->RESET;
            break;
        case 3:
            designer->ProductosStock();
            cliente->EliminarElemento(designer, L1, L2, L3,L4,L5,L6,L7,L8,ADMIN->listas);
            cout << colores->RESET;
            break;
        case 4:
            cliente->VerLista(new Color(0, 2));
            cout << colores->RESET;
            break;

        }
        };
    auto EleccionClientes = [](int op, ListaEnlazada <Nodo<Cliente<string>>, string >* clientes, auto EleccionCliente, Cola<Nodo<Cliente<string>>>* CajaRegistradora, Cola<Nodo<Cliente<string>>>* CajaVirtual, Pila<Nodo<Producto<double>>>* L1, Pila<Nodo<Producto<double>>>* L2, Pila<Nodo<Producto<double>>>* L3, Pila<Nodo<Producto<double>>>* L4, Pila<Nodo<Producto<double>>>* L5, Pila<Nodo<Producto<double>>>* L6, Pila<Nodo<Producto<double>>>* L7, Pila<Nodo<Producto<double>>>* L8, Sistema<double>* ADMIN) {

        Cliente<string>* cl;
        Interfaz* designer = new Interfaz();
        Nodo <Cliente<string>>* nodo;
        string cod;
        Nodo<Cliente<string>>* nodo_temporal;
        int cont = 0;
        int i = 19;

        switch (op) {
        case 2:
            cout << "\nCliente entra a Tottus. ";
            designer->INTERFAZAGREGARCLIENTE();
            cl = new Cliente<string>();
            nodo = new Nodo<Cliente<string>>(cl);
            clientes->AgregarElemento(nodo);
            cout << colores->RESET;
            break;
        case 3:

            designer->clienteSaleInter();


            nodo_temporal = clientes->cabeza;

            while (nodo_temporal != nullptr) {
                if (cont % 5 == 0) i++;
                designer->Imprimir(2 + (23 * cont), i, new Color(9, 11), nodo_temporal->actual->nombre + ": " + nodo_temporal->actual->tipo);
                nodo_temporal = nodo_temporal->next;
                cont++;

            }


            designer->Imprimir(30, 25, new Color(9, 2), "Ingrese el codigo del cliente: "); cin >> cod;



            clientes->eliminarClienteDeTxt(cod);
            clientes->EliminarElemento(cod, "Cliente");
            cout << colores->RESET;
            break;
        case 4:
            designer->ingresarCarrito();
            designer->Imprimir(50, 18, new Color(9, 2), "Clientes ya registrados (CODIGO): ");

            nodo_temporal = clientes->cabeza;

            while (nodo_temporal != nullptr) {
                if (cont % 5 == 0) i++;
                designer->Imprimir(2 + (23 * cont), i, new Color(9, 11), nodo_temporal->actual->nombre + ": " + nodo_temporal->actual->tipo);
                nodo_temporal = nodo_temporal->next;
                cont++;

            }
            designer->Imprimir(40, 25, new Color(9, 2), "Ingrese el codigo del cliente: "); cin >> cod;
            nodo = clientes->buscar(cod);

            if (nodo != nullptr) {
                int op2;
                do {
                    op2 = menuCliente(nodo);
                    EleccionCliente(op2, nodo->actual, CajaRegistradora, L1, L2, L3,L4,L5,L6,L7,L8, ADMIN);
                    system("pause>0");
                } while (op2 != 1);
            }
            cout << colores->RESET;
            break;

        case 5:
            designer->codigoClientes();

            designer->Imprimir(40, 20, new Color(0, 2), "Ingrese el codigo del cliente: "); cin >> cod;

            nodo = clientes->buscar(cod);

            if (nodo != nullptr) {

                //AQUI ENTRA EL SISTEMA DELIVERY

                int met; //metodo de pago, caja o delivery
                designer->Imprimir(40, 20, new Color(0, 2), "Metodo de pago -> [1] Caja [2] Delivery :              ");
                cursor(40, 21); cin >> met;

                if (met == 2) {
                    designer->Imprimir(40, 20, new Color(0, 2), "En instantes se mostrará el mapa para que eliga la direccion de su hogar...             ");
                    _sleep(700);
                    system("cls");
                    designer->mapa_Tottus();

                    system("pause>0");
                    system("cls");

                    char ini;
                    cout << "Ingrese la direccion de su casa (NODO): "; cin >> ini;

                    designer->mapa_Tottus();

                    camVec* nuev = new camVec(mapita->tiendaMasCercana(ini));
                    nodo->actual->ruta = nuev;

                    nodo->actual->nodIn = ini;
                    nodo->actual->NodFin = nuev->lastVertex;

                    system("pause>0");



                    CajaVirtual->AgregarElemento(nodo);
                }
                else CajaRegistradora->AgregarElemento(nodo);


                clientes->eliminarClienteDeTxt(cod);
                clientes->EliminarElemento(cod, "");

            }

            cout << colores->RESET;

            break;


        case 6:

            Nodo<Cliente<string>>*nodito = clientes->cabeza;

            ADMIN->mostrarClientes_Activos(nodito, designer, new Color(0, 2));

            Console::ReadKey();

            cout << colores->RESET;

            break;

        }
        };
    habilitarColoresAnsi();
    con->AjustarTamanoConsola(120, 40);
    //INICIALIZACION DE LISTAS/PILAS/COLAS

    Sistema<double>* SAP = new Sistema<double>(); //sistema

    int acceso = 1;

    while (1) {

        system("cls");

        int opcion = menuPrincipal();

        int opcionP;

        int fallos = 3;

        switch (opcion) {

        case 1:



            if (acceso == 0) {

                designer->Imprimir(42, 15, new Color(0, 2), "Acceso DENEGADO.Por favor, cierre el sistema");

                break;
            }

            system("cls");

            acceso = BloquearAcceso(fallos, designer); cout << colores->RESET;



            //acceso valido

            if (acceso == 1) {

                designer->Imprimir(42, 15, new Color(0, 2), "Acceso permitido...");
                _sleep(500);
                menuAdministrador(SAP);
            }
            else {
                cout << "Seguridad activada. Acceso denegado hasta que vuelva a abrir el sistema. ";
                Console::ReadKey();
                _sleep(100);
            }
            _sleep(1000);
            system("cls");
            continue;

            break;
        case 2:
            do {
                opcionP = menuClientes();
                EleccionClientes(opcionP, SAP->clientes, EleccionCliente, SAP->CajaRegistradora,SAP->CajaVirtual, SAP->ListaDeStock_1, SAP->ListaDeStock_2, SAP->ListaDeStock_3, SAP->ListaDeStock_4, SAP->ListaDeStock_5, SAP->ListaDeStock_6, SAP->ListaDeStock_7, SAP->ListaDeStock_8, SAP);
            } while (opcionP != 1);

            //EleccionCliente(opcionP, t);
            break;
        case 3:
            menuPersonal(SAP);
            break;


            //MODULO DEL MAPA: POR MIENTRAS
        case 4:
            system("cls");

            cout << "Este es el modulo para grafos. " << endl;

            

            //Lugar<char>* place = new Lugar<char>('T', 0, 1,1,"Tottus");

            //cout << place->tipo << " " << place->nombre << " " << place->id;

            Mapa* mapita = new Mapa;

            char ini; cin >> ini;

            
            while (ini != 0) {
                

                designer->mapa_Tottus();

                mapita->tiendaMasCercana(ini);

                cin >> ini;
            }
            
            //mapita->dibCam();
            system("pause>0");
            break;

        }
        
        system("pause>0");
    }

    return 0;
}
