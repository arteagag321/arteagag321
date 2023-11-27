#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Repuesto {
    char nombre[50];
    int cantidad;
    float precio;
    char numeroParte[50];
};

struct Nodo {
    struct Repuesto repuesto;
    struct Nodo *siguiente;
};

struct Lista {
    struct Nodo *primero;
    struct Nodo *ultimo;
};

void crearLista(struct Lista *lista) {
    lista->primero = NULL;
    lista->ultimo = NULL;
}

void insertarRepuesto(struct Lista *lista, struct Repuesto repuesto) {
    struct Nodo *nuevoNodo = (struct Nodo*) malloc(sizeof(struct Nodo));
    nuevoNodo->repuesto = repuesto;
    nuevoNodo->siguiente = NULL;

    if (lista->primero == NULL) {
        lista->primero = nuevoNodo;
        lista->ultimo = nuevoNodo;
    } else {
        lista->ultimo->siguiente = nuevoNodo;
        lista->ultimo = nuevoNodo;
    }
}

void listarRepuestos(struct Lista *lista) {
    if (lista->primero == NULL) {
        printf("No hay repuestos ingresados.\n");
    } else {
        struct Nodo *nodoActual = lista->primero;
        while (nodoActual != NULL) {
            printf("Nombre: %s, Cantidad: %d, Precio: %.2f, Numero de Parte: %s\n",
                   nodoActual->repuesto.nombre, nodoActual->repuesto.cantidad, nodoActual->repuesto.precio, nodoActual->repuesto.numeroParte);
            nodoActual = nodoActual->siguiente;
        }
    }
}

void editarRepuesto(struct Lista *lista, char *nombreRepuesto) {
    struct Nodo *nodoActual = lista->primero;
    while (nodoActual != NULL) {
        if (strcmp(nodoActual->repuesto.nombre, nombreRepuesto) == 0) {
            printf("Ingrese la nueva cantidad del repuesto: ");
            scanf("%d", &nodoActual->repuesto.cantidad);

            printf("Ingrese el nuevo precio del repuesto: ");
            scanf("%f", &nodoActual->repuesto.precio);

            printf("Repuesto editado con exito.\n");
            return;
        }
        nodoActual = nodoActual->siguiente;
    }
    printf("Repuesto no encontrado.\n");
}

void eliminarRepuesto(struct Lista *lista, char *nombreRepuesto) {
    struct Nodo *nodoActual = lista->primero;
    struct Nodo *nodoAnterior = NULL;
    while (nodoActual != NULL) {
        if (strcmp(nodoActual->repuesto.nombre, nombreRepuesto) == 0) {
            if (nodoAnterior == NULL) {
                lista->primero = nodoActual->siguiente;
            } else {
                nodoAnterior->siguiente = nodoActual->siguiente;
            }
            free(nodoActual);
            printf("Repuesto eliminado con exito.\n");
            return;
        }
        nodoAnterior = nodoActual;
        nodoActual = nodoActual->siguiente;
    }
    printf("Repuesto no encontrado.\n");
}

int main() {
    struct Lista lista;
    crearLista(&lista);

    int opcion;
    do {
        printf("\n--- Sistema de Inventarios ---\n");
        printf("1. Ingresar repuesto\n");
        printf("2. Listar repuestos\n");
        printf("3. Editar repuesto\n");
        printf("4. Eliminar repuesto\n");
        printf("5. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: {
                struct Repuesto repuesto;
                printf("Ingrese el nombre del repuesto: ");
                scanf("%s", repuesto.nombre);

                printf("Ingrese la cantidad del repuesto: ");
                scanf("%d", &repuesto.cantidad);

                printf("Ingrese el precio del repuesto: ");
                scanf("%f", &repuesto.precio);

                printf("Ingrese el numero de parte del repuesto: ");
                scanf("%s", repuesto.numeroParte);

                insertarRepuesto(&lista, repuesto);
                break;
            }
            case 2:
                listarRepuestos(&lista);
                break;
            case 3: {
                char nombreRepuesto[50];
                printf("Ingrese el nombre del repuesto a editar: ");
                scanf("%s", nombreRepuesto);
                editarRepuesto(&lista, nombreRepuesto);
                break;
            }
            case 4: {
                char nombreRepuesto[50];
                printf("Ingrese el nombre del repuesto a eliminar: ");
                scanf("%s", nombreRepuesto);
                eliminarRepuesto(&lista, nombreRepuesto);
                break;
            }
            case 5:
                printf("Adios. Vuelve pronto\n");
                break;
            default:
                printf("Opcion no valida. Por favor, ingrese una opcion valida.\n");
        }
    } while (opcion != 5);

    return 0;
}
