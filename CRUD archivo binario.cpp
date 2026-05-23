#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Producto {
    int codigo;
    char nombre[50];
    float precio;
    int stock;
    bool activo;
};

// FUNCIONES
void registrarProducto();
void listarProductos();
void buscarPorCodigo();
void buscarPorNombre();
void modificarPrecio();
void actualizarStock();
void eliminarProducto();
void procesoVenta();

int main() {

    int opcion;

    do {

        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Gestion de productos" << endl;
        cout << "2. Proceso de venta" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1: {

                int op2;

                do {

                    cout << "\n====== GESTION DE PRODUCTOS ======" << endl;
                    cout << "1. Registrar producto" << endl;
                    cout << "2. Listar productos activos" << endl;
                    cout << "3. Buscar producto por codigo" << endl;
                    cout << "4. Buscar producto por nombre" << endl;
                    cout << "5. Modificar precio" << endl;
                    cout << "6. Actualizar stock" << endl;
                    cout << "7. Eliminar / desactivar producto" << endl;
                    cout << "8. Regresar" << endl;
                    cout << "Seleccione una opcion: ";
                    cin >> op2;

                    switch(op2) {

                        case 1:
                            registrarProducto();
                            break;

                        case 2:
                            listarProductos();
                            break;

                        case 3:
                            buscarPorCodigo();
                            break;

                        case 4:
                            buscarPorNombre();
                            break;

                        case 5:
                            modificarPrecio();
                            break;

                        case 6:
                            actualizarStock();
                            break;

                        case 7:
                            eliminarProducto();
                            break;

                        case 8:
                            cout << "\nRegresando..." << endl;
                            break;

                        default:
                            cout << "\nOpcion invalida." << endl;
                    }

                } while(op2 != 8);

                break;
            }

            case 2:
                procesoVenta();
                break;

            case 3:
                cout << "\nFin del programa." << endl;
                break;

            default:
                cout << "\nOpcion invalida." << endl;
                 break;
        }

    } while(opcion != 3);

    cout << "\nCreado por: Lisbeth Vanesa Lopez Catalan" << endl;

    return 0;
}

// REGISTRAR PRODUCTO
void registrarProducto() {

    Producto p;

    cout << "\nIngrese codigo: ";
    cin >> p.codigo;

    cin.ignore();

    cout << "Ingrese nombre: ";
    cin.getline(p.nombre, 50);

    cout << "Ingrese precio: ";
    cin >> p.precio;

    cout << "Ingrese stock: ";
    cin >> p.stock;

    p.activo = true;

    ofstream archivo("productos.dat", ios::binary | ios::app);

    archivo.write((char*)&p, sizeof(Producto));

    archivo.close();

    cout << "\nProducto registrado correctamente." << endl;
}

// LISTAR PRODUCTOS
void listarProductos() {

    Producto p;

    ifstream archivo("productos.dat", ios::binary);

    cout << "\n===== PRODUCTOS ACTIVOS =====" << endl;

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.activo == true) {

            cout << "\nCodigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
        }
    }

    archivo.close();
}

// BUSCAR POR CODIGO
void buscarPorCodigo() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo a buscar: ";
    cin >> codigo;

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo == true) {

            cout << "\nProducto encontrado:" << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << endl;

            encontrado = true;
        }
    }

    archivo.close();

    if(encontrado == false) {
        cout << "\nProducto no encontrado." << endl;
    }
}

// BUSCAR POR NOMBRE
void buscarPorNombre() {

    Producto p;
    char nombre[50];
    bool encontrado = false;

    cin.ignore();

    cout << "\nIngrese nombre a buscar: ";
    cin.getline(nombre, 50);

    ifstream archivo("productos.dat", ios::binary);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(strcmp(p.nombre, nombre) == 0 && p.activo == true) {

            cout << "\nProducto encontrado:" << endl;
            cout << "Codigo: " << p.codigo << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock: " << p.stock << endl;

            encontrado = true;
        }
    }

    archivo.close();

    if(encontrado == false) {
        cout << "\nProducto no encontrado." << endl;
    }
}

// MODIFICAR PRECIO
void modificarPrecio() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo == true) {

            cout << "Nuevo precio: ";
            cin >> p.precio;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            encontrado = true;

            cout << "\nPrecio actualizado." << endl;

            break;
        }
    }

    archivo.close();

    if(encontrado == false) {
        cout << "\nProducto no encontrado." << endl;
    }
}

// ACTUALIZAR STOCK
void actualizarStock() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo == true) {

            cout << "Nuevo stock: ";
            cin >> p.stock;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            encontrado = true;

            cout << "\nStock actualizado." << endl;

            break;
        }
    }

    archivo.close();

    if(encontrado == false) {
        cout << "\nProducto no encontrado." << endl;
    }
}

// ELIMINAR PRODUCTO
void eliminarProducto() {

    Producto p;
    int codigo;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo == true) {

            p.activo = false;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            encontrado = true;

            cout << "\nProducto desactivado." << endl;

            break;
        }
    }

    archivo.close();

    if(encontrado == false) {
        cout << "\nProducto no encontrado." << endl;
    }
}

// PROCESO DE VENTA
void procesoVenta() {

    Producto p;
    int codigo;
    int cantidad;
    bool encontrado = false;

    cout << "\nIngrese codigo del producto: ";
    cin >> codigo;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    while(archivo.read((char*)&p, sizeof(Producto))) {

        if(p.codigo == codigo && p.activo == true) {

            encontrado = true;

            cout << "\nProducto encontrado:" << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q" << p.precio << endl;
            cout << "Stock disponible: " << p.stock << endl;

            cout << "\nIngrese cantidad: ";
            cin >> cantidad;

            if(cantidad <= 0) {

                cout << "\nCantidad invalida." << endl;
                break;
            }

            if(cantidad > p.stock) {

                cout << "\nNo hay suficiente stock." << endl;
                break;
            }

            float subtotal = cantidad * p.precio;
            float iva = subtotal * 0.12;
            float total = subtotal + iva;

            cout << "\n===== FACTURA =====" << endl;
            cout << "Subtotal: Q" << subtotal << endl;
            cout << "IVA: Q" << iva << endl;
            cout << "Total: Q" << total << endl;

            // DESCONTAR STOCK
            p.stock = p.stock - cantidad;

            archivo.seekp(archivo.tellg() - (long)sizeof(Producto));

            archivo.write((char*)&p, sizeof(Producto));

            cout << "\nVenta realizada correctamente." << endl;

            break;
        }
    }

    archivo.close();

    if(encontrado == false) {

        cout << "\nProducto no encontrado." << endl;
    }
}
