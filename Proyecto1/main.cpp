#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;
/*********************************************************COMPONENTES DE LA MATRIZ****************************************************************************/
/*------------------------------------------------------NODO CONTENIDO-------------------------------------------------------------------------*/
class nodoContenido
{
public:
    string color;
    int c,y,id;
    nodoContenido *arriba;
    nodoContenido *abajo;
    nodoContenido *izq;
    nodoContenido *der;

    nodoContenido(string color,int c,int y,int id)
    {
        this->color = color;
        this->c = c;
        this->y = y;
        this->id = id;
        arriba = NULL;
        abajo = NULL;
        izq = NULL;
        der = NULL;
    }
};
/*-------------------------------------------------------LISTA FILAS------------------------------------------------------------------------*/
class listaFilas
{
public:
    nodoContenido *primero;
    nodoContenido *ultimo;

    listaFilas()
    {
        primero = NULL;
        ultimo = NULL;
    }

    bool vacio()
    {
        if(primero == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void insertar(nodoContenido *ins)
    {
        if(vacio())
        {
            primero = ultimo = ins;
        }
        else
        {
            if(ins->y<primero->y)
            {
                insertarFrente(ins);
            }
            else if(ins->y>ultimo->y)
            {
                insertarFinal(ins);
            }
            else
            {
                insertarMedio(ins);
            }
        }
    }

    void insertarFrente(nodoContenido *ins)
    {
        primero->arriba = ins;
        ins->abajo = primero;
        primero = primero->arriba;
    }

    void insertarFinal(nodoContenido *ins)
    {
        ultimo->abajo = ins;
        ins->arriba = ultimo;
        ultimo = ultimo->abajo;
    }
    void insertarMedio(nodoContenido *ins)
    {
        nodoContenido *temp1;
        nodoContenido *temp2;
        temp1 = primero;
        while(temp1->y<ins->y)
        {
            temp1 = temp1->abajo;
        }
        temp2 = temp1->arriba;

        temp2->abajo = ins;
        temp1->arriba = ins;
        ins->abajo = temp1;
        ins->arriba = temp2;

    }

    void recorrer()
    {
        if(!vacio())
        {
            nodoContenido *aux = primero;
            while(aux != NULL)
            {
                cout<<"y="<<aux->y<<endl;
                aux = aux->abajo;
            }
        }
    }
};
/*-----------------------------------------------------LISTA COLUMNAS-----------------------------------------------------*/
class listaColumnas
{
public:
    nodoContenido *primero;
    nodoContenido *ultimo;

    listaColumnas()
    {
        primero = NULL;
        ultimo = NULL;
    }

    bool vacio()
    {
        if(primero == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void insertar(nodoContenido *ins)
    {
        if(vacio())
        {
            primero = ultimo = ins;
        }
        else
        {
            if(ins->c<primero->c)
            {
                insertarFrente(ins);
            }
            else if(ins->c>ultimo->c)
            {
                insertarFinal(ins);
            }
            else
            {
                insertarMedio(ins);
            }
        }
    }

    void insertarFrente(nodoContenido *ins)
    {
        primero->izq = ins;
        ins->der = primero;
        primero = primero->izq;
    }

    void insertarFinal(nodoContenido *ins)
    {
        ultimo->der = ins;
        ins->izq = ultimo;
        ultimo = ultimo->der;
    }

    void insertarMedio(nodoContenido *ins)
    {
        nodoContenido *temp1;
        nodoContenido *temp2;
        temp1 = primero;
        while(temp1->c<ins->c)
        {
            temp1 = temp1->der;
        }
        temp2 = temp1->izq;

        temp2->der = ins;
        temp1->izq = ins;
        ins->der = temp1;
        ins->izq = temp2;

    }

    void recorrer()
    {
        if(!vacio())
        {
            nodoContenido *aux = primero;
            while(aux != NULL)
            {
                cout<<"x="<<aux->c<<endl;
                aux = aux->der;
            }
        }
    }
};
/*--------------------------------------------------------NODO COLUMNA------------------------------------------------------------------*/
class nodoColumna
{
public:
    int x;
    int grupo;
    nodoColumna *siguiente;
    nodoColumna *anterior;
    listaFilas *columna;

    nodoColumna(int x,int ng)
    {
        this->x = x;
        this->grupo = ng;
        columna = new listaFilas();
        siguiente = NULL;
        anterior = NULL;
    }

};
/*-------------------------------------------------------NODO FILA-------------------------------------------------------------------*/
class nodoFila
{
public:
    int y;
    nodoFila *siguiente;
    nodoFila *anterior;
    listaColumnas *filas;

    nodoFila(int y)
    {
        this->y = y;
        filas = new listaColumnas();
        siguiente = NULL;
        anterior = NULL;
    }

};
/*------------------------------------------------------LISTA DE COLUMNAS----------------------------------------------------*/
class columnas
{
public:
    nodoColumna *primero;
    nodoColumna *ultimo;

    columnas()
    {
        primero = NULL;
        ultimo = NULL;
    }

    bool vacio()
    {
        if(primero == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void insertar(nodoColumna *ins)
    {
        if(vacio())
        {
            primero = ultimo = ins;
        }
        else
        {
            if(ins->x<primero->x)
            {
                insertarFrente(ins);
            }
            else if(ins->x>ultimo->x)
            {
                insertarFinal(ins);
            }
            else
            {
                insertarMedio(ins);
            }
        }
    }

    void insertarFrente(nodoColumna *ins)
    {
        primero->anterior = ins;
        ins->siguiente = primero;
        primero = primero->anterior;
    }

    void insertarFinal(nodoColumna *ins)
    {
        ultimo->siguiente = ins;
        ins->anterior = ultimo;
        ultimo = ultimo->siguiente;
    }

    void insertarMedio(nodoColumna *ins)
    {
        nodoColumna *temp1;
        nodoColumna *temp2;
        temp1 = primero;
        while(temp1->x<ins->x)
        {
            temp1 = temp1->siguiente;
        }
        temp2 = temp1->anterior;

        temp2->siguiente = ins;
        temp1->anterior = ins;
        ins->siguiente = temp1;
        ins->anterior = temp2;

    }

    void recorrer()
    {
        if(!vacio())
        {
            nodoColumna *aux = primero;
            while(aux != NULL)
            {
                cout<<"columna="<<aux->x<<endl;
                aux = aux->siguiente;
            }
        }
    }

    int getTam()
    {
        int contador = 0;
        if(!vacio())
        {
            nodoColumna *aux = primero;
            while(aux != NULL)
            {
                contador++;
                aux = aux->siguiente;
            }
        }
        return contador;
    }

    bool existe(int x)
    {
        if(vacio())
        {
            return false;
        }
        else
        {
            nodoColumna *aux;
            aux = primero;
            while(aux != NULL)
            {
                if(aux->x == x)
                {
                    return true;
                }
                else if(aux->siguiente == NULL)
                {
                    return false;
                }
                aux = aux->siguiente;
            }
        }
        return false;
    }

    nodoColumna *busqueda(int x)
    {

        if(existe(x))
        {

            nodoColumna *aux;
            aux = primero;

            while(aux->x != x)
            {
                aux = aux->siguiente;
            }

            return aux;
        }
        else
        {
            return(new nodoColumna(-1,-1));
        }
    }

};
/*------------------------------------------------------LISTA DE FILAS----------------------------------------------------*/
class filas
{
public:
    nodoFila *primero;
    nodoFila *ultimo;

    filas()
    {
        primero = NULL;
        ultimo = NULL;
    }

    bool vacio()
    {
        if(primero == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void insertar(nodoFila *ins)
    {
        if(vacio())
        {
            primero = ultimo = ins;
        }
        else
        {
            if(ins->y<primero->y)
            {
                insertarFrente(ins);
            }
            else if(ins->y>ultimo->y)
            {
                insertarFinal(ins);
            }
            else
            {
                insertarMedio(ins);
            }
        }
    }

    int getTam()
    {
        int contador = 0;
        if(!vacio())
        {
            nodoFila *aux = primero;
            while(aux != NULL)
            {
                contador++;
                aux = aux->siguiente;
            }
        }
        return contador;
    }

    void insertarFrente(nodoFila *ins)
    {
        primero->anterior = ins;
        ins->siguiente = primero;
        primero = primero->anterior;
    }

    void insertarFinal(nodoFila *ins)
    {
        ultimo->siguiente = ins;
        ins->anterior = ultimo;
        ultimo = ultimo->siguiente;
    }

    void insertarMedio(nodoFila *ins)
    {
        nodoFila *temp1;
        nodoFila *temp2;
        temp1 = primero;
        while(temp1->y<ins->y)
        {
            temp1 = temp1->siguiente;
        }
        temp2 = temp1->anterior;

        temp2->siguiente = ins;
        temp1->anterior = ins;
        ins->siguiente = temp1;
        ins->anterior = temp2;

    }

    void recorrer()
    {
        if(!vacio())
        {
            nodoFila *aux = primero;
            while(aux != NULL)
            {
                cout<<"fila="<<aux->y<<endl;
                aux = aux->siguiente;
            }
        }
    }

    bool existe(int y)
    {
        if(vacio())
        {
            return false;
        }
        else
        {
            nodoFila *aux;
            aux = primero;
            while(aux != NULL)
            {
                if(aux->y == y)
                {
                    return true;
                }
                else if(aux->siguiente == NULL)
                {
                    return false;
                }
                aux = aux->siguiente;
            }
        }
        return false;
    }

    nodoFila *busqueda(int y)
    {
        if(existe(y))
        {
            nodoFila *aux;
            aux = primero;
            while(aux->y != y)
            {
                aux = aux->siguiente;
            }
//                    cout<<"encontrado "<<aux->y<<endl;
            return aux;
        }
        else
        {
            //          cout<<"NO SE ENCONTRO"<<endl;
            return(new nodoFila(-1));
        }
    }
};
/*--------------------------------------------------------CLASE MATRIZ--------------------------------------------------*/
class Matriz
{
public:
    int identificador;
    columnas *c;
    filas *f;

    Matriz(int id)
    {
        this->identificador = id;
        c = new columnas();
        f = new filas();
    }

    void insertar(int y, int x, string ins, int ide)
    {
        nodoContenido *insercion;
        insercion = new nodoContenido(ins,x,y,ide);
        for(int i = 0; i<=x; i++)
        {
            if(!(c->existe(i)))
            {
                c->insertar(new nodoColumna(i,i+2));
            }
        }
        for(int j = 0; j<=y; j++)
        {
            if(!(f->existe(j)))
            {
                f->insertar(new nodoFila(j));
            }
        }
        nodoColumna *caux;
        nodoFila *faux;
        caux = c->busqueda(x);
        faux = f->busqueda(y);
        caux->columna->insertar(insercion);
        faux->filas->insertar(insercion);
    }
    /*++++++++++++++++++++++++++++++++++++++GRAFICAR CAPA LOGICA+++++++++++++++++++++++++++++++++++++++*/
    void graficar()
    {
        int posx = 0;
        int posy = 0;
        stringstream rut;
        rut<<"C:\\Graficas\\";
        rut<<identificador<<".dot";
        string ruta = rut.str();
        stringstream escribir;
        stringstream s2;
        stringstream comando;
        stringstream extra;
        nodoColumna *aux;
        aux = c->primero;
        nodoFila *aux2;
        aux2 = f->primero;
        escribir<<"digraph Matrix{"<<endl<<endl;
        escribir<<"General [shape = box, width = 2,height = 1, label = \"Matriz\",pos = \"-144,144\"];"<<endl;
        posx = -144;
        while(aux2 != NULL)
        {
            escribir<<"Y"<<aux2->y<<"[shape = box,width = 2,height = 1, label = \""<<aux2->y<<"\",pos = \" "<<posx<<","<<posy<<" \"];"<<endl;
            posy = posy-144;
            aux2 = aux2->siguiente;
        }
        escribir<<endl<<endl;
        aux2 = f->primero;
        posx = 0;
        posy = 0;
        while(aux2 != NULL)
        {
            if(aux2->siguiente != NULL)
            {
                escribir<<"Y"<<aux2->y<<"->"<<"Y"<<aux2->siguiente->y<<";"<<endl;
            }
            if(aux2->anterior != NULL)
            {
                escribir<<"Y"<<aux2->y<<"->"<<"Y"<<aux2->anterior->y<<";"<<endl;
            }
            aux2 = aux2->siguiente;
        }
        escribir<<endl<<endl;

        posy = 144;
        posx = 72;
        while(aux != NULL)
        {
            escribir<<"X"<<aux->x<<"[shape = box,width = 2,height = 1, label = \""<<aux->x<<"\",pos = \" "<<posx<<","<<posy<<" \"];"<<endl;
            posx = posx+216;
            aux = aux->siguiente;
        }
        escribir<<endl<<endl;
        aux = c->primero;
        while(aux != NULL)
        {
            if(aux->siguiente != NULL)
            {
                escribir<<"X"<<aux->x<<"->"<<"X"<<aux->siguiente->x<<";"<<endl;
            }
            if(aux->anterior != NULL)
            {
                escribir<<"X"<<aux->x<<"->"<<"X"<<aux->anterior->x<<";"<<endl;
            }
            aux = aux->siguiente;
        }
        escribir<<endl<<endl;
        escribir<<"General->Y0;"<<endl;
        escribir<<"General->X0"<<endl;


        aux = c->primero;
        aux2 = f->primero;
        nodoContenido *col;
        posx = 0;
        posy = 0;
        while(aux != NULL)
        {
            if(!aux->columna->vacio())
            {
                col = aux->columna->primero;
                while(col != NULL)
                {
                    escribir<<"C"<<col->id<<" [shape = box,width = 2,height = 1, label = \""<<col->color<<"\",pos = \" "<<(col->c*216)+72<<","<<(col->y*-144)<<" \"];"<<endl;
                    col = col->abajo;
                }
                col = aux->columna->primero;
                escribir<<"X"<<aux->x<<"->"<<"C"<<col->id<<";"<<endl;
                escribir<<"C"<<col->id<<"->"<<"X"<<aux->x<<";"<<endl;
                while(col != NULL)
                {
                    if(col->abajo != NULL)
                    {
                        escribir<<"C"<<col->id<<"->"<<"C"<<col->abajo->id<<";"<<endl;
                    }
                    if(col->arriba != NULL)
                    {
                        escribir<<"C"<<col->id<<"->"<<"C"<<col->arriba->id<<";"<<endl;
                    }
                    if(col->izq != NULL)
                    {
                        escribir<<"C"<<col->id<<"->"<<"C"<<col->izq->id<<";"<<endl;
                    }
                    if(col->der != NULL)
                    {
                        escribir<<"C"<<col->id<<"->"<<"C"<<col->der->id<<";"<<endl;
                    }
                    col = col->abajo;
                }
            }
            aux = aux->siguiente;
        }

        nodoContenido *fil;
        while(aux2 != NULL)
        {
            if(!aux2->filas->vacio())
            {
                fil = aux2->filas->primero;
                escribir<<"Y"<<aux2->y<<"->"<<"C"<<fil->id<<";"<<endl;
                escribir<<"C"<<fil->id<<"->"<<"Y"<<aux2->y<<";"<<endl;
            }
            aux2 = aux2->siguiente;
        }
        escribir<<endl<<endl;
        escribir<<"}"<<endl;
        string resultado = escribir.str();
        ofstream file(ruta.c_str());
        file<<resultado;
        file.close();
        comando<<"neato -n -Tpng "<<ruta<<" -o C:\\Graficas\\"<<identificador<<".png";
        string comand = comando.str();
        char cstr[comand.size()+1];
        strcpy(cstr,comand.c_str());
        system(cstr);
        stringstream img;
        img<<"C:\\Graficas\\"<<identificador<<".png";
        string rim = img.str();
        ShellExecute(NULL,"open",rim.c_str(),NULL,NULL,SW_SHOWNORMAL);
    }

    /*+++++++++++++++++++++++++++++++++++GRAFICAR LOS CUADRO EN BLANCO+++++++++++++++++++++++++++++++++*/
    string graficarCapaTexto()
    {
        int gx = 0;
        int gxaux = 0;
        int gy = 0;
        int gyaux = 0;
        stringstream escribir;
        stringstream s2;
        stringstream comando;
        stringstream extra;
        nodoColumna *aux;
        aux = c->primero;
        nodoFila *aux2;
        aux2 = f->primero;
        while(aux2 != NULL)
        {
            gxaux  = -36;
            escribir<<"Y"<<aux2->y<<" [shape = box,width = 0.5,height = 0.5, label = \""<<aux2->y<<"\",style = filled,fillcolor = white, pos = \""<<gxaux<<","<<gyaux<<"\"];"<<endl;
            gyaux = gyaux-36;
            aux2 = aux2->siguiente;
        }
        gyaux = gy;
        gxaux = gx;
        escribir<<endl<<endl;

        escribir<<endl<<endl;
        while(aux != NULL)
        {
            gyaux = 36;
            escribir<<"X"<<aux->x<<" [shape = box,width = 0.5,height = 0.5, label = \""<<aux->x<<"\",style = filled,fillcolor = white, pos = \""<<gxaux<<","<<gyaux<<"\"];"<<endl;//cada nodo cabezera
            gxaux = gxaux+36;
            aux = aux->siguiente;
        }
        gyaux = gy;
        gxaux = gx;
        escribir<<endl<<endl;

        for(int i = 0; i<c->getTam(); i++)
        {
            for(int j = 0; j<f->getTam(); j++)
            {
                gxaux = i*36;
                gyaux = j*-36;
                escribir<<"C"<<i<<j<<" [shape = box,width = 0.5,height = 0.5, label = \"\",style = filled, fillcolor = white, pos = \""<<gxaux<<","<<gyaux<<"\"];"<<endl;
            }

        }

        escribir<<endl<<endl;
        string resultado = escribir.str();
        return resultado;
    }

    /*++++++++++++++++++++++++++++++++++GRFICAR LOS COLORES++++++++++++++++++++++++++++++++++++++++++*/
    string sobreescribir()
    {
        string res = "";
        stringstream escribir;
        nodoColumna *aux;
        aux = c->primero;
        nodoContenido *col;
        while(aux != NULL)
        {
            if(!aux->columna->vacio())
            {
                col = aux->columna->primero;
                while(col != NULL)
                {
                    escribir<<"C"<<col->c<<col->y<<" [shape = box,width = 0.5,height = 0.5, label = \"\" ,style = filled, fillcolor = \""<<col->color<<"\", pos = \""<<(col->c*36)<<","<<(col->y*-36)<<"\"];"<<endl;
                    col = col->abajo;
                }
            }
            aux = aux->siguiente;
        }
        res = escribir.str();
        return res;
    }

    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++GRAFICAR LA CAPA COMPLETA+++++++++++++++++++++++++++++++++++++++++++*/
    void graficarCapa()
    {
        int gx = 0;
        int gxaux = 0;
        int gy = 0;
        int gyaux = 0;
        stringstream rut;
        rut<<"C:\\Graficas\\capa";
        rut<<identificador<<".dot";
        string ruta = rut.str();
        stringstream escribir;
        stringstream s2;
        stringstream comando;
        stringstream extra;
        nodoColumna *aux;
        aux = c->primero;
        nodoFila *aux2;
        aux2 = f->primero;
        escribir<<"graph Capa{"<<endl<<endl;
        /*escribir<<"General"<<" [shape = box,width = 0.5,height = 0.5, label = \""<<identificador<<"\",style = filled,fillcolor = gray, pos = \"-72,72\"];"<<endl;
        while(aux2 != NULL)
        {
            gxaux  = -36;
            escribir<<"Y"<<aux2->y<<" [shape = box,width = 0.5,height = 0.5, label = \""<<aux2->y<<"\",style = filled,fillcolor = white, pos = \""<<gxaux<<","<<gyaux<<"\"];"<<endl;
            gyaux = gyaux-36;
            aux2 = aux2->siguiente;
        }*/
        gyaux = gy;
        gxaux = gx;
        escribir<<endl<<endl;

        escribir<<endl<<endl;
        /*while(aux != NULL)
        {
            gyaux = 36;
            escribir<<"X"<<aux->x<<" [shape = box,width = 0.5,height = 0.5, label = \""<<aux->x<<"\",style = filled,fillcolor = white, pos = \""<<gxaux<<","<<gyaux<<"\"];"<<endl;//cada nodo cabezera
            gxaux = gxaux+36;
            aux = aux->siguiente;
        }
        gyaux = gy;
        gxaux = gx;
        escribir<<endl<<endl;

        for(int i = 0; i<c->getTam(); i++)
        {
            for(int j = 0; j<f->getTam(); j++)
            {
                gxaux = i*36;
                gyaux = j*-36;
                escribir<<"C"<<i<<j<<" [shape = box,width = 0.5,height = 0.5, label = \"\",style = filled, fillcolor = white, pos = \""<<gxaux<<","<<gyaux<<"\"];"<<endl;
            }

        }*/
        gxaux = gx;
        gyaux = gy;
        aux = c->primero;
        aux2 = f->primero;
        escribir<<endl<<endl;

        nodoContenido *col;
        while(aux != NULL)
        {
            if(!aux->columna->vacio())
            {
                col = aux->columna->primero;
                while(col != NULL)
                {
                    escribir<<"C"<<col->c<<col->y<<" [shape = box,width = 0.5,height = 0.5, label = \"\" ,style = filled,fillcolor = \""<<col->color<<"\", pos = \""<<(col->c*36)<<","<<(col->y*-36)<<"\"];"<<endl;
                    col = col->abajo;
                }
            }
            aux = aux->siguiente;
        }
        escribir<<endl<<endl;

        escribir<<"}"<<endl;
        string resultado = escribir.str();
        ofstream file(ruta.c_str());
        file<<resultado;
        file.close();
        comando<<"neato -n -Tpng "<<ruta<<" -o C:\\Graficas\\capa"<<identificador<<".png";
        string comand = comando.str();
        char cstr[comand.size()+1];
        strcpy(cstr,comand.c_str());
        system(cstr);
        stringstream img;
        img<<"C:\\Graficas\\capa"<<identificador<<".png";
        string rim = img.str();
        ShellExecute(NULL,"open",rim.c_str(),NULL,NULL,SW_SHOWNORMAL);
    }

};
/***************************************************************ESTRUCTURAS EXTRAS********************************************************************/
class Nodo
{
public:
    int id;
    Nodo *next;
};
class pila
{
    Nodo *head;
public:
    pila()
    {
        head = NULL;
    }
    void push(int dato)
    {
        Nodo *aux = new Nodo;
        aux->id = dato;
        aux->next = NULL;
        if(head != NULL)
            aux->next = head;
        head = aux;
    }

    int pop()
    {
        int resultado = 0;
        Nodo *temp = new Nodo;
        if(head!=NULL)
        {
            temp = head;
            head = head->next;
            resultado = temp->id;
            delete temp;
        }
        return resultado;
    }

    int top()
    {
        int dato;
        Nodo *aux = head;
        if(head != NULL)
        {
            dato = aux->id;
        }

        return dato;

    }

    int tam()
    {
        int contador = 0;
        Nodo *aux = head;
        if(head != NULL)
        {
            while(aux)
            {
                contador++;
                aux = aux->next;
            }

        }
        return contador;
    }

    bool vacia()
    {
        if(head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
/****************************************************************ABB DE CAPAS*****************************************************************************/
class ABB
{
public:
    int tam = 0;
    int profundidad = 1;

    struct nodoabb
    {
        Matriz *data;
        int id;
        nodoabb *izq;
        nodoabb *der;
    };

    nodoabb *raiz;

    ABB()
    {
        raiz = NULL;
    }

    nodoabb *insertar(Matriz *x, nodoabb *t)
    {
        if(t == NULL)
        {
            t = new nodoabb;
            t->data = x;
            t->id = x->identificador;
            t->izq = t->der = NULL;
        }
        else if(x->identificador < t->data->identificador)
        {
            t->izq = insertar(x,t->izq);
        }
        else if(x->identificador>t->data->identificador)
        {
            t->der = insertar(x,t->der);
        }
        return t;
    }

    nodoabb *insertarEspejo(Matriz *x, nodoabb *t)
    {
        if(t == NULL)
        {
            t = new nodoabb;
            t->data = x;
            t->id = x->identificador;
            t->izq = t->der = NULL;
        }
        else if(x->identificador < t->data->identificador)
        {
            t->der = insertarEspejo(x,t->der);
        }
        else if(x->identificador>t->data->identificador)
        {
            t->izq = insertarEspejo(x,t->izq);
        }
        return t;
    }

    void prof(nodoabb *arbol)
    {
        if(arbol != NULL)
        {
            if(arbol->izq != NULL || arbol->der != NULL)
            {
                profundidad++;
            }
            if(arbol->izq != NULL)
            {
                if(arbol->izq->izq != NULL)
                {
                    prof(arbol->izq->izq);
                }
                else if(arbol->der->der)
                {
                    prof(arbol->izq->der);
                }
            }
            else if(arbol->der != NULL)
            {
                if(arbol->der->izq != NULL)
                {
                    prof(arbol->der->izq);
                }
                else if(arbol->der->der)
                {
                    prof(arbol->der->der);
                }
            }
        }
    }

    void hojas(nodoabb *arbol)
    {
        if(arbol != NULL)
        {
            hojas(arbol->izq);
            if(arbol->izq == NULL && arbol->der == NULL)
            {
                cout<<"La capa: "<<arbol->id<<" es una hoja del arbol"<<endl;
            }
            hojas(arbol->der);
        }
    }

    void preorden(nodoabb *arbol)
    {
        if(arbol != NULL)
        {
            cout<<arbol->data->identificador<<"----";
            preorden(arbol->izq);
            preorden(arbol->der);
        }
    }

    void inorder(nodoabb *arbol)
    {
        if(arbol != NULL)
        {
            inorder(arbol->izq);
            cout<<arbol->id<<"----";
            inorder(arbol->der);
        }
    }

    void postOrden(nodoabb *arbol)
    {
        if(arbol != NULL)
        {
            postOrden(arbol->izq);
            postOrden(arbol->der);
            cout<<arbol->data->identificador<<"----";
        }
    }

    /*-------------------------- ORDENES LIMITADOS-----------------------------------------*/
    int limite = 0;
    int limiteExtra = 0;

    void reset()
    {
        limite = 0;
        limiteExtra = 0;
    }


    string preordenLimitado(nodoabb *arbol)
    {
        string res = "";
        stringstream aux;
        if(arbol != NULL)
        {
            if(limite > 0)
            {
                aux<<arbol->data->graficarCapaTexto()<<endl<<endl;
                //cout<<"grafico la capa: "<<arbol->id<<endl;
                limite--;
                aux<<preordenLimitado(arbol->izq);
                aux<<preordenLimitado(arbol->der);
            }
        }
        res = aux.str();
        return res;
    }

    string preordenLimitadoExtra(nodoabb *arbol)
    {
        string res = "";
        stringstream aux;
        if(arbol != NULL)
        {
            if(limiteExtra > 0)
            {
                aux<<arbol->data->sobreescribir()<<endl<<endl;
                limiteExtra--;
                aux<<preordenLimitadoExtra(arbol->izq);
                aux<<preordenLimitadoExtra(arbol->der);
            }
        }
        res = aux.str();
        return res;
    }

    string inorderLimitado(nodoabb *arbol)
    {
        string res = "";
        stringstream aux;

        pila *s = new pila;
        nodoabb *actual = arbol;
        while((actual != NULL || s->vacia() == false) && limite>0)
        {
            while(actual != NULL)
            {
                s->push(actual->id);
                actual  = actual->izq;
            }

            int act = s->top();
            actual = buscar(raiz,act);
            s->pop();

            //cout<<"grafico la capa:  "<<actual->id;
            aux<<actual->data->graficarCapaTexto()<<endl;

            actual = actual->der;
            limite--;
        }

        res = aux.str();
        return res;
    }

    string inorderLimitadoExtra(nodoabb *arbol)
    {
        string res = "";
        stringstream aux;
        pila *s = new pila;
        nodoabb *actual = arbol;
        while((actual != NULL || s->vacia() == false) && limiteExtra>0)
        {
            while(actual != NULL)
            {
                s->push(actual->id);
                actual  = actual->izq;
            }

            int act = s->top();
            actual = buscar(raiz,act);
            s->pop();

            aux<<actual->data->sobreescribir()<<endl;

            actual = actual->der;
            limiteExtra--;
        }

        res = aux.str();
        return res;
    }

    string postOrdenLimitado(nodoabb *arbol)
    {
        string res = "";
        stringstream aux;
        if(arbol == NULL)
        {
            return res;
        }
        else
        {

            pila *s1 = new pila;
            pila *s2 = new pila;

            s1->push(arbol->id);
            nodoabb *actual;

            while(!s1->vacia())
            {
                int naux = s1->top();
                actual = buscar(raiz,naux);
                int no = s1->pop();
                s2->push(actual->id);

                if(actual->izq)
                {
                    s1->push(actual->izq->id);
                }
                if(actual->der)
                {
                    s1->push(actual->der->id);
                }
            }

            while(!s2->vacia() && limite>0)
            {
                int naux = s2->top();
                actual = buscar(raiz,naux);
                s2->pop();
                aux<<actual->data->graficarCapaTexto()<<endl;
                limite--;
            }


        }
        res = aux.str();
        return res;
    }

    string postOrdenLimitadoExtra(nodoabb *arbol)
    {
        string res = "";
        stringstream aux;
        if(arbol == NULL)
        {
            return res;
        }
        else
        {

            pila *s1 = new pila;
            pila *s2 = new pila;

            s1->push(arbol->id);
            nodoabb *actual;

            while(!s1->vacia())
            {
                int naux = s1->top();
                actual = buscar(raiz,naux);
                int no = s1->pop();
                s2->push(actual->id);

                if(actual->izq)
                {
                    s1->push(actual->izq->id);
                }
                if(actual->der)
                {
                    s1->push(actual->der->id);
                }
            }

            while(!s2->vacia() && limiteExtra>0)
            {
                int naux = s2->top();
                actual = buscar(raiz,naux);
                s2->pop();
                aux<<actual->data->sobreescribir()<<endl;
                limiteExtra--;
            }
        }

        res = aux.str();
        return res;
    }

    void ordenesLimitados(int n)
    {
        string ruta = "C:\\Graficas\\Limitado.dot";
        stringstream ss;
        ss<<"graph Limitado{"<<endl<<endl;
        string capa = " ";
        string sobre = " ";
        switch(n)
        {
        case 1:
        {
            capa = preordenLimitado(raiz);
            sobre = preordenLimitadoExtra(raiz);
            break;
        }
        case 2:
        {
            capa = inorderLimitado(raiz);
            sobre = inorderLimitadoExtra(raiz);
            break;
        }
        case 3:
        {
            capa = postOrdenLimitado(raiz);
            sobre = postOrdenLimitadoExtra(raiz);
            break;
        }
        }
        ss<<capa<<endl;
        ss<<sobre<<endl;
        ss<<"}";
        string resultado = ss.str();
        ofstream file(ruta.c_str());
        file<<resultado;
        file.close();
        system("neato -n -Tpng C:\\Graficas\\Limitado.dot -o C:\\Graficas\\Limitado.png");
        ShellExecute(NULL,"open","C:\\Graficas\\Limitado.png",NULL,NULL,SW_SHOWNORMAL);
    }
    /*-------------------------- ORDENES LIMITADOS-----------------------------------------*/

    void ordenes(int n)
    {
        switch(n)
        {
        case 1:
        {
            preorden(raiz);
            break;
        }
        case 2:
        {
            inorder(raiz);
            break;
        }
        case 3:
        {
            postOrden(raiz);
            break;
        }
        }
    }

    string getnodos(nodoabb *arbol,int color)
    {
        stringstream info;
        string col;
        if(color == 0)
        {
            col = "gray";
        }
        else if(color == 1)
        {
            col = "lightblue";
        }
        else
        {
            col = "green";
        }
        if(arbol == NULL)
        {
            info<<"nodo"<<arbol->data->identificador<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->data->identificador<<"\"];"<<endl;
        }
        else
        {
            info<<"nodo"<<arbol->data->identificador<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->data->identificador<<"\"];"<<endl;
        }
        if(arbol->izq != NULL)
        {
            info<<getnodos(arbol->izq,1)<<endl;
            info<<"nodo"<<arbol->data->identificador<<"->nodo"<<arbol->izq->data->identificador<<endl;
        }
        if(arbol->der != NULL)
        {
            info<<getnodos(arbol->der,2)<<endl;
            info<<"nodo"<<arbol->data->identificador<<"->nodo"<<arbol->der->data->identificador<<endl;
        }

        return info.str();
    }

    string getnodosEspejo(nodoabb *arbol,int color)
    {
        stringstream info;
        string col;
        if(color == 0)
        {
            col = "gray";
        }
        else if(color == 1)
        {
            col = "lightblue";
        }
        else
        {
            col = "green";
        }
        if(arbol == NULL)
        {
            info<<"nodo"<<arbol->data->identificador<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->data->identificador<<"\"];"<<endl;
        }
        else
        {
            info<<"nodo"<<arbol->data->identificador<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->data->identificador<<"\"];"<<endl;
        }
        if(arbol->izq != NULL)
        {
            info<<getnodos(arbol->izq,2)<<endl;
            info<<"nodo"<<arbol->data->identificador<<"->nodo"<<arbol->izq->data->identificador<<endl;
        }
        if(arbol->der != NULL)
        {
            info<<getnodos(arbol->der,1)<<endl;
            info<<"nodo"<<arbol->data->identificador<<"->nodo"<<arbol->der->data->identificador<<endl;
        }

        return info.str();
    }

    string getcodigog(nodoabb *arbol)
    {
        stringstream info;
        info<<"digraph ABB{"<<endl;
        info<<"rankdir = TB;"<<endl;
        info<<"node [shape = circle];"<<endl;
        info<<getnodos(arbol,0);
        info<<"}"<<endl;
        return info.str();
    }

    string getcodigogEspejo(nodoabb *arbol)
    {
        stringstream info;
        info<<"digraph ABB{"<<endl;
        info<<"rankdir = TB;"<<endl;
        info<<"node [shape = circle];"<<endl;
        info<<getnodos(arbol,0);
        info<<"}"<<endl;
        return info.str();
    }

    string grafArbol(nodoabb *arbol,int color)
    {
        stringstream info;
        string col;
        if(color == 0)
        {
            col = "gray";
        }
        else if(color == 1)
        {
            col = "lightblue";
        }
        else
        {
            col = "green";
        }
        if(arbol == NULL)
        {
            info<<"nodo"<<arbol->data->identificador<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->data->identificador<<"\"];"<<endl;
        }
        else
        {
            info<<"nodo"<<arbol->data->identificador<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->data->identificador<<"\"];"<<endl;
        }
        if(arbol->izq != NULL)
        {
            info<<grafArbol(arbol->izq,1)<<endl;
            info<<"nodo"<<arbol->data->identificador<<"->nodo"<<arbol->izq->data->identificador<<endl;
        }
        if(arbol->der != NULL)
        {
            info<<grafArbol(arbol->der,2)<<endl;
            info<<"nodo"<<arbol->data->identificador<<"->nodo"<<arbol->der->data->identificador<<endl;
        }

        return info.str();
    }

    bool existe(int n)
    {
        nodoabb *bus = buscar(raiz,n);
        if(bus != NULL)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    void insertarn(Matriz *x)
    {
        raiz = insertar(x,raiz);
        tam++;
    }

    void insertarnEspejo(Matriz *x)
    {
        raiz = insertarEspejo(x,raiz);
    }

    nodoabb *buscar(nodoabb *root,int key)
    {
        if(root == NULL || root->id == key)
        {
            return root;
        }
        if(root->id < key)
        {
            return buscar(root->der,key);
        }

        return buscar(root->izq,key);

    }

    int devolver(int key)
    {
        nodoabb *sip = buscar(raiz,key);
        return sip->id;
    }

    void GraficarCapa(int key)
    {
        nodoabb *capa = buscar(raiz,key);
        if(capa != NULL)
        {
            capa->data->graficarCapa();
        }
        else
        {
            cout<<"La Capa no existe \a"<<endl;
        }
    }

    string GraficarCapaTexto(int key)
    {
        string res = "";
        nodoabb *capa = buscar(raiz,key);
        if(capa != NULL)
        {
            res = capa->data->graficarCapaTexto();
        }
        else
        {
            cout<<"La Capa no existe \a"<<endl;
        }

        return res;
    }

    string gs(int key)
    {
        string res = "";
        nodoabb *capa = buscar(raiz,key);
        if(capa != NULL)
        {
            res = capa->data->sobreescribir();
        }
        else
        {
            cout<<"La Capa no existe \a"<<endl;
        }

        return res;
    }

    void GraficarCapaLogica(int key)
    {
        nodoabb *capa = buscar(raiz,key);
        if(capa != NULL)
        {
            capa->data->graficar();
        }
        else
        {
            cout<<"La Capa no existe \a"<<endl;
        }
    }

    void graficar(string id)
    {
        string resultado = getcodigog(raiz);
        stringstream rut;
        stringstream comando;
        rut<<"C:\\Graficas\\";
        rut<<id<<".dot";
        string ruta = rut.str();
        ofstream file(ruta.c_str());
        file<<resultado;
        file.close();
        comando<<"dot -Tpng "<<ruta<<" -o C:\\Graficas\\"<<id<<".png";
        string comand = comando.str();
        char cstr[comand.size()+1];
        strcpy(cstr,comand.c_str());
        system(cstr);
    }

    void graficarEspejo(string id)
    {
        string resultado = getcodigogEspejo(raiz);
        stringstream rut;
        stringstream comando;
        rut<<"C:\\Graficas\\";
        rut<<id<<"Espejo.dot";
        string ruta = rut.str();
        ofstream file(ruta.c_str());
        file<<resultado;
        file.close();
        comando<<"dot -Tpng "<<ruta<<" -o C:\\Graficas\\"<<id<<"Espejo.png";
        string comand = comando.str();
        char cstr[comand.size()+1];
        strcpy(cstr,comand.c_str());
        system(cstr);
    }
};
/******************************************************************LISTA CIRCULAR DE IMAGENES***************************************************************/
class nodoCapa
{
public:
    int id;
    int aux;
    string nombre;
    nodoCapa *siguiente;
};
class listaSimple
{
public:
    nodoCapa *primero;
    int num;
    listaSimple()
    {
        primero  = NULL;
        num = 0;
    }

    void insertar(int id)
    {
        num++;
        nodoCapa *nuevo = new nodoCapa;
        nuevo->id = id;
        nuevo->siguiente = primero;
        primero = nuevo;
    }

    void insertarAux(int id,int ax)
    {
        num++;
        nodoCapa *nuevo = new nodoCapa;
        nuevo->id = id;
        nuevo->aux = ax;
        nuevo->siguiente = primero;
        primero = nuevo;
    }

    void insertarAux2(int id,string ax)
    {
        num++;
        nodoCapa *nuevo = new nodoCapa;
        nuevo->id = id;
        nuevo->nombre = ax;
        nuevo->siguiente = primero;
        primero = nuevo;
    }

    void mostrar()
    {
        nodoCapa *aux;
        aux = primero;
        while(aux != NULL)
        {
            cout<<aux->id<<endl;
            aux = aux->siguiente;
        }
    }

    void mostrarAux()
    {
        nodoCapa *auxx;
        auxx = primero;
        int top = 1;
        for(int i = 0; i<5; i++)
        {
            if(auxx != NULL)
            {
                cout<<"Top "<<top<<" Imagen->"<<auxx->aux<<"  No. Capas->"<<auxx->id<<endl;
                top++;
                auxx = auxx->siguiente;
            }
        }
    }

    void mostrarAux2()
    {
        nodoCapa *auxx;
        auxx = primero;
        int top = 1;
        for(int i = 0; i<5; i++)
        {
            if(auxx != NULL)
            {
                cout<<"Top "<<top<<" Usuario->"<<auxx->nombre<<"  No. Imagenes->"<<auxx->id<<endl;
                top++;
                auxx = auxx->siguiente;
            }
        }
    }

    void ordenar()
    {
        nodoCapa *t,*s;
        int v, i,x;
        string nombaux;
        if(primero == NULL)
        {
            cout<<"LA LISTA ESTA VACIA"<<endl;
            return;
        }
        s = primero;
        for(i = 0; i < num; i++)
        {
            t = s->siguiente;
            while(t != NULL)
            {
                if(s->id < t->id)
                {
                    v = s->id;
                    x = s->aux;
                    nombaux = s->nombre;

                    s->id = t->id;
                    s->aux = t->aux;
                    s->nombre = t->nombre;

                    t->id = v;
                    t->aux = x;
                    t->nombre = nombaux;
                }
                t = t->siguiente;
            }
            s = s->siguiente;
        }
    }

    bool vacio()
    {

        if(primero == NULL)
        {
            return true;
        }
        return false;
    }
};
class Nodoimagen
{
public:
    int id;
    int numcapas;
    listaSimple *capas;
    Nodoimagen *next;
    Nodoimagen *prev;
};
class listaSimpleImagenes
{
public:
    Nodoimagen *primero;
    listaSimpleImagenes()
    {
        primero  = NULL;
    }

    void insertar(int id)
    {
        Nodoimagen *nuevo = new Nodoimagen;
        nuevo->id = id;
        nuevo->next = primero;
        primero = nuevo;
    }

    int tam()
    {
        int contador = 0;
        Nodoimagen *aux = primero;
        while(aux != NULL)
        {
            contador++;
            aux = aux->next;
        }

        return contador;
    }

    void mostrar()
    {
        Nodoimagen *aux;
        aux = primero;

        while(aux != NULL)
        {
            cout<<aux->id<<endl;
            aux = aux->next;
        }

    }



    void eliminar(Nodoimagen *&li, int n)
    {
        if(li != NULL)
        {
            Nodoimagen *aux;
            Nodoimagen *anterior = NULL;
            aux = li;

            while((aux != NULL) && (aux->id != n))
            {
                anterior = aux;
                aux = aux->next;
            }

            if(aux == NULL)
            {
                //cout<<"La imagen no existe"<<endl;
            }
            else if(anterior == NULL)
            {
                li = li->next;
                delete aux;
            }
            else
            {
                anterior->next = aux->next;
                delete aux;
            }
        }
    }

    bool vacio()
    {

        if(primero == NULL)
        {
            return true;
        }
        return false;
    }
};
class Lista_circular
{
public:
    Nodoimagen *head;
    Nodoimagen *last;
    int num;

    Lista_circular()
    {
        head = NULL;
        last = NULL;
        num = 0;
    }

    Nodoimagen *crearnodo(int v)
    {
        num++;
        Nodoimagen *t;
        t = new Nodoimagen;
        t->id = v;
        t->numcapas = 0;
        t->next = NULL;
        t->prev = NULL;
        t->capas = new listaSimple;
        return t;
    }

    void insertarInicio(int id)
    {
        Nodoimagen *nuevo;
        nuevo = crearnodo(id);
        if(head == NULL)
        {
            head = last = nuevo;
            head->next = last->next = nuevo;
            head->prev = last->prev = nuevo;
        }
        else
        {
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
            head->prev = last;
            last->next = head;
        }
    }

    void ordenar()
    {
        Nodoimagen *t,*s;
        listaSimple *aux;
        int v, i,x;
        if(head == NULL)
        {
            cout<<"LA LISTA ESTA VACIA"<<endl;
            return;
        }

        s = head;
        for(i = 0; i < num; i++)
        {
            t = s->next;
            while(t != head)
            {
                if(s->id > t->id)
                {
                    v = s->id;
                    aux = s->capas;
                    x = s->numcapas;

                    s->id = t->id;
                    s->capas = t->capas;
                    s->numcapas = t->numcapas;

                    t->id = v;
                    t->capas = aux;
                    t->numcapas = x;
                }
                t = t->next;
            }
            s = s->next;
        }

    }

    void mostrarc()
    {
        Nodoimagen *aux = new Nodoimagen;
        aux  = head;
        if(head != NULL)
        {
            do
            {
                cout<<"["<<aux->id<<"]---";
                aux = aux->next;
            }
            while(aux!=head);
        }
        else
        {
            cout<<"la lista esta vacia"<<endl;
        }
    }

    void insertarCapa(int idimagen, int capa)
    {
        Nodoimagen *aux;
        aux = head;
        if(head != NULL)
        {
            do
            {
                if(idimagen == aux->id)
                {
                    aux->capas->insertar(capa);
                    aux->numcapas = aux->numcapas+1;
                }
                aux = aux->next;
            }
            while(aux != head);
        }
    }

    void TopmasCapas()
    {
        listaSimple *solotop = new listaSimple;
        Nodoimagen *aux = head;
        if(head != NULL)
        {
            do
            {
                solotop->insertarAux(aux->numcapas,aux->id);
                aux = aux->next;
            }
            while(aux != head);
        }
        solotop->ordenar();
        solotop->mostrarAux();
    }

    bool vacia()
    {

        if(head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int tam()
    {
        int tam = 0;
        Nodoimagen *aux = new Nodoimagen;
        aux = head;
        if(head != NULL)
        {
            do
            {
                tam++;
                aux = aux->next;
            }
            while(aux != head);

        }
        return tam;
    }

    void graficar()
    {
        Nodoimagen *aux = new Nodoimagen;
        nodoCapa *temp;
        aux = head;
        stringstream ss;
        ss<<"digraph LC{"<<endl;
        ss<<"rankdir = LR;"<<endl;
        if(head != NULL)
        {
            do
            {
                ss<<"i_"<<aux->id<<" [label=\"Imagen: "<<aux->id<<"\",style = filled, fillcolor = Turquoise];"<<endl;
                aux = aux->next;
            }
            while(aux != head);
            aux = head;
            ss<<endl<<endl;
            do
            {
                ss<<"i_"<<aux->id<<"->i_"<<aux->next->id<<" [color = cyan];"<<endl;
                ss<<"i_"<<aux->id<<"->i_"<<aux->prev->id<<" [color = cyan];"<<endl;
                aux = aux->next;
            }
            while(aux != head);
            aux = head;
            ss<<endl<<endl;
            do
            {
                if(aux->capas->primero != NULL)
                {
                    nodoCapa *cap = aux->capas->primero;
                    ss<<"i_"<<aux->id<<"->I"<<aux->id<<"C"<<cap->id<<";"<<endl;
                    while(cap!= NULL)
                    {
                        ss<<"I"<<aux->id<<"C"<<cap->id<<" [label = \""<<cap->id<<"\"];"<<endl;
                        if(cap->siguiente != NULL)
                        {
                            ss<<"I"<<aux->id<<"C"<<cap->id<<"->"<<"I"<<aux->id<<"C"<<cap->siguiente->id<<";"<<endl;
                        }
                        cap = cap->siguiente;
                    }
                }

                aux = aux->next;
            }
            while(aux != head);

        }

        ss<<"}"<<endl;
        string resultado = ss.str();
        ofstream file("C:\\Graficas\\ListaImagenes.dot");
        file<<resultado;
        file.close();
        system("dot -Tpng C:\\Graficas\\ListaImagenes.dot -o C:\\Graficas\\ListaImagenes.png");
    }

    void graficarImagen(int ide, ABB *&arbol)
    {
        stringstream rut;
        rut<<"C:\\Graficas\\Imagen";
        rut<<ide<<".dot";
        string ruta = rut.str();
        /*----------------------*/
        Nodoimagen *aux;
        aux = head;
        stringstream ss;
        ss<<"graph Imagen{"<<endl<<endl;
        if(head != NULL)
        {
            do
            {
                if(aux->id == ide)
                {
                    if(aux->capas->primero == NULL)
                    {
                        ss<<"Nulo"<<" [shape = box,width = 1,height = 1,style = filled,fillcolor = black, pos = \"-72,72\"];"<<endl;
                    }
                    else
                    {
                        //ss<<"General"<<" [shape = box,width = 0.5,height = 0.5,label = \"Img: "<<aux->id<<" \",style = filled,fillcolor = white, pos = \"-36,36\"];"<<endl;
                        nodoCapa *tmp = aux->capas->primero;
                        /*while(tmp != NULL)
                        {
                            ss<<"//Capa: "<<tmp->id<<endl;
                            string capa = arbol->GraficarCapaTexto(tmp->id);
                            ss<<capa<<endl<<endl;
                            tmp = tmp->siguiente;
                        }
                        tmp = aux->capas->primero;*/
                        while(tmp != NULL)
                        {
                            string ex = arbol->gs(tmp->id);
                            ss<<ex<<endl<<endl;
                            tmp = tmp->siguiente;
                        }

                    }
                }
                aux = aux->next;
            }
            while(aux != head);
        }
        ss<<"}";
        stringstream comando;
        string resultado = ss.str();
        ofstream file(ruta.c_str());
        file<<resultado;
        file.close();
        comando<<"neato -n -Tpng "<<ruta<<" -o C:\\Graficas\\Imagen"<<ide<<".png";
        string comand = comando.str();
        char cstr[comand.size()+1];
        strcpy(cstr,comand.c_str());
        system(cstr);
        stringstream img;
        img<<"C:\\Graficas\\Imagen"<<ide<<".png";
        string rim = img.str();
        ShellExecute(NULL,"open",rim.c_str(),NULL,NULL,SW_SHOWNORMAL);
    }

    bool buscar(int id)
    {
        Nodoimagen *aux = new Nodoimagen;
        aux = head;
        if(head != NULL)
        {
            do
            {
                if(aux->id == id)
                {
                    return true;
                    break;
                }
                aux = aux->next;
            }
            while(aux != head);
        }

        return false;
    }

    void sacarElemento(int id)
    {
        Nodoimagen *aux = new Nodoimagen;
        aux = head;
        Nodoimagen *pre = new Nodoimagen;
        pre = NULL;
        if(head != NULL)
        {
            do
            {
                if(aux->id == id)
                {
                    if(aux == head)
                    {
                        head = head->next;
                        head->prev = last;
                        last->next = head;
                    }
                    else if(aux == last)
                    {
                        last = pre;
                        last->next = head;
                        head->prev = last;
                    }
                    else
                    {
                        pre->next = aux->next;
                        aux->next->prev = pre;
                    }
                }
                pre = aux;
                aux = aux->next;
            }
            while(aux != head);
        }
    }
};
/*************************************************************************ARBOL AVL**************************************************************************/
class nodoavl
{
public:
    string dato;
    int factoreq;
    nodoavl *izq;
    nodoavl *der;
    nodoavl *padre;
    listaSimpleImagenes *imagenes;

    nodoavl(string dat, nodoavl *padr = NULL, nodoavl *iz = NULL, nodoavl *de = NULL)
    {
        this->dato = dat;
        this->factoreq = 0;
        this->izq = iz;
        this->der = de;
        this->padre = padr;
        imagenes = new listaSimpleImagenes;
    }
};
class nodocola
{
public:
    nodoavl *dato;
    nodocola *next;
    nodocola *prev;
};
class cola
{
    nodocola *head;
    nodocola *tail;
public:
    cola()
    {
        head = NULL;
        tail = NULL;
    }

    void encolar(nodoavl *a)
    {
        nodocola *aux  = new nodocola;
        aux->dato = a;
        aux->next = NULL;

        if(head == NULL)
        {
            head = aux;
        }
        else
        {
            tail->next = aux;
        }
        tail = aux;
    }

    nodoavl  *desencolar()
    {
        nodoavl *tmp;
        nodocola *aux;
        aux = head;
        tmp = aux->dato;
        head = head->next;
        delete aux;
        return tmp;
    }

    void verCola()
    {
        nodocola *aux;
        aux = head;
        if(head != NULL)
        {
            while(aux != NULL)
            {
                cout<<aux->dato->dato<<"-----";
                aux = aux->next;
            }
        }
        else
        {
            cout<<"La cola esta vacia!"<<endl;
        }
    }

    bool colavacia()
    {
        if(head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class AVL
{
public:
    nodoavl *raiz;
    nodoavl *actual;
    int contador;
    int altura;

    bool bandera = false;
    listaSimpleImagenes *modificada= new listaSimpleImagenes;

    AVL()
    {
        raiz = NULL;
        actual = NULL;
    }

    void insertar(string dato)
    {
        nodoavl *padre = NULL;
        //cout<<"NUEVO USUARIO "<<dato<<endl;
        actual = raiz;

        while(!vacio(actual) && dato != actual->dato)
        {
            padre = actual;
            if(dato > actual->dato)
            {
                actual = actual->der;
            }
            else if(dato < actual->dato)
            {
                actual = actual->izq;
            }
            else
            {
                cout<<"NO SE PUEDEN REPETIR NOMBRES DE USUARIO"<<endl;
            }
        }

        if(!vacio(actual))
        {
            return;
        }

        if(vacio(padre))
        {
            raiz = new nodoavl(dato);
        }
        else if(dato < padre->dato)
        {
            padre->izq = new nodoavl(dato,padre);
            //if(bandera){
            //    padre->izq->imagenes = modificada;
            //}
            Balancear(padre,0,true);
        }
        else if(dato > padre->dato)
        {
            padre->der = new nodoavl(dato,padre);
            //if(bandera){
            //    padre->der->imagenes = modificada;
            //}
            Balancear(padre,1,true);
        }
        else
        {
            cout<<"NO SE PUEDEN REPETIR NOMBRES DE USUARIO"<<endl;
        }
    }

    void Balancear(nodoavl *nodo, int r, bool nuevo)
    {
        bool salir = false;

        while(nodo && !salir)
        {
            if(nuevo)
            {
                if(r == 0)
                {
                    nodo->factoreq--;
                }
                else
                {
                    nodo->factoreq++;
                }
            }
            else
            {
                if(r == 0)
                {
                    nodo->factoreq++;
                }
                else
                {
                    nodo->factoreq--;
                }
            }

            if(nodo->factoreq == 0)
            {
                salir = true;
            }
            else if(nodo->factoreq == -2)
            {
                if(nodo->izq->factoreq == 1)
                {
                    RDD(nodo);
                }
                else
                {
                    RSD(nodo);
                }
                salir = true;
            }
            else if(nodo->factoreq == 2)
            {
                if(nodo->der->factoreq == -1)
                {
                    RDI(nodo);
                }
                else
                {
                    RSI(nodo);
                }
                salir = true;
            }

            if(nodo->padre)
            {
                if(nodo->padre->der == nodo)
                {
                    r = 1;
                }
                else
                {
                    r = 0;
                }
            }
            nodo = nodo->padre;
        }//cierre while
    }

    void RDD(nodoavl *nodo)
    {
        nodoavl *padre = nodo->padre;
        nodoavl *n1 = nodo;
        nodoavl *n2 = n1->izq;
        nodoavl *n3 = n2->der;
        nodoavl *n4 = n3->izq;
        nodoavl *n5 = n3->der;

        if(padre)
        {
            if(padre->der == nodo)
            {
                padre->der = n3;
            }
            else
            {
                padre->izq = n3;
            }
        }
        else
        {
            raiz = n3;
        }

        n2->der = n4;
        n1->izq = n5;
        n3->izq = n2;
        n3->der = n1;

        n3->padre = padre;
        n1->padre = n2->padre = n3;

        if(n4)
        {
            n4->padre = n2;
        }
        if(n5)
        {
            n5->padre = n1;
        }

        switch(n3->factoreq)
        {
        case -1:
            n2->factoreq = 0;
            n1->factoreq = 1;
            break;
        case 0:
            n2->factoreq = 0;
            n1->factoreq = 0;
            break;
        case 1:
            n2->factoreq = -1;
            n1->factoreq = 0;
            break;
        }
        n3->factoreq = 0;
    }

    void RSD(nodoavl *nodo)
    {
        nodoavl *padre = nodo->padre;
        nodoavl *p = nodo;
        nodoavl *q = p->izq;
        nodoavl *b = q->der;

        if(padre)
        {
            if(padre->der == p)
            {
                padre->der = q;
            }
            else
            {
                padre->izq = q;
            }
        }
        else
        {
            raiz = q;
        }

        p->izq = b;
        q->der  =p;

        p->padre = q;
        if(b)
        {
            b->padre =p;
        }
        q->padre = padre;

        p->factoreq = 0;
        q->factoreq = 0;
    }

    bool vacio(nodoavl *r)
    {
        return r == NULL;
    }

    void RSI(nodoavl *nodo)
    {
        nodoavl *padre = nodo->padre;
        nodoavl *p = nodo;
        nodoavl *q = p->der;
        nodoavl *b = q->izq;

        if(padre)
        {
            if(padre->der == p)
            {
                padre->der = q;
            }
            else
            {
                padre->izq = q;
            }
        }
        else
        {
            raiz  = q;
        }


        p->der = b;
        q->izq = p;

        p->padre  = q;
        if(b)
        {
            b->padre = p;
        }
        q->padre = padre;

        p->factoreq = 0;
        q->factoreq = 0;
    }

    bool eshoja(nodoavl *r)
    {
        return !r->der && !r->izq;
    }

    void Raiz()
    {
        actual  = raiz;
    }

    void RDI(nodoavl *nodo)
    {
        nodoavl *padre   = nodo->padre;
        nodoavl *p = nodo;
        nodoavl *q = p->der;
        nodoavl *r = q->izq;
        nodoavl *b = r->izq;
        nodoavl *c = r->der;

        if(padre)
        {
            if(padre->der == nodo)
            {
                padre->der = r;
            }
            else
            {
                padre->izq = r;
            }
        }
        else
        {
            raiz = r;
        }

        p->der = b;
        q->izq = c;
        r->izq = p;
        r->der = q;

        r->padre = padre;
        p->padre = q->padre = r;
        if(b)
        {
            b->padre = p;
        }
        if(c)
        {
            c->padre = q;
        }

        switch(r->factoreq)
        {
        case -1:
            p->factoreq = 0;
            q->factoreq = 1;
            break;
        case 0:
            p->factoreq = 0;
            q->factoreq = 0;
            break;
        case 1:
            p->factoreq = -1;
            q->factoreq = 0;
            break;
        }
        r->factoreq = 0;
    }

    void eliminar(string dato)
    {
        nodoavl *padre = NULL;
        nodoavl *nodo;
        string aux;

        actual = raiz;
        while(!vacio(actual))
        {
            if(dato == actual->dato)
            {
                if(eshoja(actual))
                {
                    if(padre)
                    {
                        if(padre->der == actual)
                        {
                            padre->der = NULL;
                        }
                        else if(padre->izq == actual)
                        {
                            padre->izq = NULL;
                        }
                        actual->imagenes->primero = NULL;
                        delete actual;
                        actual = NULL;
                    }
                    if((padre->der == actual && padre->factoreq == 1)||(padre->izq == actual && padre->factoreq == -1))
                    {
                        padre->factoreq = 0;
                        actual = padre;
                        padre = actual->padre;
                    }
                    if(padre)
                    {
                        if(padre->der == actual)
                        {
                            Balancear(padre,1,false);
                        }
                        else
                        {
                            Balancear(padre,0,false);
                        }
                        return;
                    }
                }
                else
                {
                    padre = actual;
                    if(actual->der)
                    {
                        nodo = actual->der;
                        padre->imagenes->primero = NULL;
                        while(nodo->izq)
                        {
                            padre = nodo;
                            nodo = nodo->izq;
                        }
                    }
                    else
                    {
                        nodo = actual->izq;
                        padre->imagenes->primero = NULL;
                        while(nodo->der)
                        {
                            padre = nodo;
                            nodo = nodo->der;
                        }
                    }

                    aux = actual->dato;
                    actual->dato = nodo->dato;
                    nodo->dato = aux;
                    actual = nodo;
                }
            }
            else
            {
                padre = actual;
                if(dato>actual->dato)
                {
                    actual = actual->der;
                }
                else if(dato <actual->dato)
                {
                    actual = actual->izq;
                }
            }
        }//cierre while
    }

    bool buscar(string dato)
    {
        actual = raiz;

        while(!vacio(actual))
        {
            if(dato == actual->dato)
            {
                return true;
            }
            else if(dato > actual->dato)
            {
                actual = actual->der;
            }
            else if(dato < actual->dato)
            {
                actual = actual->izq;
            }
        }
        return false;
    }

    void VerImagenes(string dato)
    {
        actual = raiz;
        while(!vacio(actual))
        {
            if(dato == actual->dato)
            {
                if(actual->imagenes->primero != NULL)
                {
                    Nodoimagen *aux = actual->imagenes->primero;
                    while(aux != NULL)
                    {
                        cout<<aux->id<<endl;
                        aux = aux->next;
                    }
                    break;
                }
                else
                {
                    cout<<"El usuario seleccionado no tiene imagenes en su cuenta."<<endl;
                    break;
                }

            }
            else if(dato > actual->dato)
            {
                actual = actual->der;
            }
            else if(dato < actual->dato)
            {
                actual = actual->izq;
            }
        }
    }


    void GraficarImagen(string dato, int nimg, Lista_circular *& imgs, ABB *&arbol)
    {
        actual = raiz;
        while(!vacio(actual))
        {
            if(dato == actual->dato)
            {
                if(actual->imagenes->primero != NULL)
                {
                    Nodoimagen *aux = actual->imagenes->primero;
                    while(aux != NULL)
                    {
                        if(aux->id == nimg)
                        {
                            imgs->graficarImagen(nimg,arbol);
                        }
                        aux = aux->next;
                    }
                    break;
                }
                else
                {
                    cout<<"El usuario seleccionado no tiene imagenes en su cuenta."<<endl;
                    break;
                }

            }
            else if(dato > actual->dato)
            {
                actual = actual->der;
            }
            else if(dato < actual->dato)
            {
                actual = actual->izq;
            }
        }
    }

    nodoavl *buscarnodo(string dato)
    {
        actual = raiz;
        while(!vacio(actual))
        {
            if(dato == actual->dato)
            {
                return actual;
            }
            else if(dato > actual->dato)
            {
                actual = actual->der;
            }
            else if(dato < actual->dato)
            {
                actual = actual->izq;
            }
        }
        return NULL;
    }





    void modificar(string dato,string nuevo)
    {
        nodoavl *cambiar = buscarnodo(dato);
        modificada = cambiar->imagenes;
        bandera = true;
        if(cambiar != NULL)
        {
            eliminar(dato);
            insertar(nuevo);
        }
    }

    int nimg  = 0;

    void reset()
    {
        nimg = 0;
        bandera = false;
        modificada->primero = NULL;
    }

    void elimimg(nodoavl *arbol)
    {

        if(arbol != NULL)
        {
            arbol->imagenes->eliminar(arbol->imagenes->primero,nimg);
            elimimg(arbol->izq);
            elimimg(arbol->der);
        }

    }

    void preorden(nodoavl *arbol)
    {
        if(arbol != NULL)
        {
            cout<<arbol->dato<<"----";
            preorden(arbol->izq);
            preorden(arbol->der);
        }
    }

    void inorder(nodoavl *arbol)
    {
        if(arbol != NULL)
        {
            inorder(arbol->izq);
            cout<<arbol->dato<<"----";
            inorder(arbol->der);
        }
    }

    listaSimple *aux;
    void crear()
    {

        aux = new listaSimple;
    }

    void topusers(nodoavl *arbol)
    {
        if(arbol != NULL)
        {
            topusers(arbol->izq);
            aux->insertarAux2(arbol->imagenes->tam(),arbol->dato);
            topusers(arbol->der);
        }
    }

    void devolvertop()
    {
        aux->ordenar();
        aux->mostrarAux2();
    }

    void postOrden(nodoavl *arbol)
    {
        if(arbol != NULL)
        {
            postOrden(arbol->izq);
            postOrden(arbol->der);
            cout<<arbol->dato<<"----";
        }
    }

    void Niveles(nodoavl *arbol)
    {
        cola *col;
        cola *aux;
        nodoavl *tmp;

        if(arbol != NULL)
        {
            col = new cola;
            aux = new cola;
            col->encolar(arbol);
            while(!col->colavacia())
            {
                aux->encolar(tmp = col->desencolar());
                if(tmp->izq != NULL)
                {
                    col->encolar(tmp->izq);
                }
                if(tmp->der != NULL)
                {
                    col->encolar(tmp->der);
                }
            }//cierre del while
            aux->verCola();
        }//cierre del if null
    }//cierre del metodo


    void espejo(nodoavl *arbol)
    {
        if(arbol != NULL)
        {
            nodoavl *tmp;

            espejo(arbol->izq);
            espejo(arbol->der);

            tmp = arbol->izq;
            arbol->izq = arbol->der;
            arbol->der = tmp;
        }
    }

    void ordenes(int n)
    {
        switch(n)
        {
        case 1:
        {
            preorden(raiz);
            break;
        }
        case 2:
        {
            inorder(raiz);
            break;
        }
        case 3:
        {
            postOrden(raiz);
            break;
        }
        case 4:
        {
            Niveles(raiz);
            break;
        }
        case 5:
        {
            espejo(raiz);
            graficar("avlespejo");
            break;
        }
        case 6:
        {
            topusers(raiz);
            break;
        }
        case 7:
        {
            elimimg(raiz);
            break;
        }
        }
    }


    void asignarImagen(string dato,int nimagen)
    {
        nodoavl *encontrado = buscarnodo(dato);
        if(encontrado != NULL)
        {
            encontrado->imagenes->insertar(nimagen);
        }
    }

    int Altura(string dato)
    {
        altura = 0;
        actual = raiz;

        while(!vacio(actual))
        {
            if(dato == actual->dato)
                return altura;
            else
            {
                altura++;
                if(dato>actual->dato)
                    actual = actual->der;
                else if(dato<actual->dato)
                    actual = actual->izq;
            }
        }
        return -1;
    }

    int numnodos()
    {
        contador = 0;
        auxcontador(raiz);
        return contador;
    }

    void auxcontador(nodoavl *nodo)
    {
        contador++;
        if(nodo->izq)
            auxcontador(nodo->izq);
        if(nodo->der)
            auxcontador(nodo->der);
    }

    int alturaArbol()
    {
        altura = 0;
        auxAltura(raiz,0);
        return altura;
    }

    void auxAltura(nodoavl *nodo, int alt)
    {
        if(nodo->izq)
        {
            auxAltura(nodo->izq,alt+1);
        }
        if(nodo->der)
        {
            auxAltura(nodo->der,alt+1);
        }
        if(eshoja(nodo) && alt>altura)
        {
            altura = alt;
        }
    }

    string getnodos(nodoavl *arbol,int color)
    {
        stringstream info;
        string col;
        if(color == 0)
        {
            col = "gray";
        }
        else if(color == 1)
        {
            col = "lightblue";
        }
        else
        {
            col = "green";
        }
        if(arbol == NULL)
        {
            info<<"avl"<<arbol->dato<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->dato<<"\"];"<<endl;
        }
        else
        {
            info<<"avl"<<arbol->dato<< " [style = filled, fillcolor ="<<col<<",label = \""<<arbol->dato<<"\"];"<<endl;
        }
        /*****************************/
        if(arbol->imagenes != NULL)
        {
            if(!(arbol->imagenes->vacio()))
            {
                Nodoimagen *auxg = arbol->imagenes->primero;
                info<<"avl"<<arbol->dato<<"->img"<<arbol->dato<<"_"<<auxg->id<<";"<<endl;
                while(auxg != NULL)
                {
                    info<<"img"<<arbol->dato<<"_"<<auxg->id<<" [ label = \""<<auxg->id<<"\"];"<<endl;
                    if(auxg->next != NULL)
                    {
                        info<<"img"<<arbol->dato<<"_"<<auxg->id<<"->img"<<arbol->dato<<"_"<<auxg->next->id<<";"<<endl;
                    }
                    auxg = auxg->next;
                }
            }
        }
        /*****************************/
        if(arbol->izq != NULL)
        {
            info<<getnodos(arbol->izq,1)<<endl;
            info<<"avl"<<arbol->dato<<"->avl"<<arbol->izq->dato<<endl;
        }
        if(arbol->der != NULL)
        {
            info<<getnodos(arbol->der,2)<<endl;
            info<<"avl"<<arbol->dato<<"->avl"<<arbol->der->dato<<endl;
        }

        return info.str();
    }

    string getcodigog(nodoavl *arbol)
    {
        stringstream info;
        info<<"digraph AVL{"<<endl;
        info<<"rankdir = TB;"<<endl;
        info<<"node [shape = circle];"<<endl;
        info<<getnodos(arbol,0);
        info<<"}"<<endl;
        return info.str();
    }

    void graficar(string id)
    {
        string resultado = getcodigog(raiz);
        stringstream rut;
        stringstream comando;
        rut<<"C:\\Graficas\\";
        rut<<id<<".dot";
        string ruta = rut.str();
        ofstream file(ruta.c_str());
        file<<resultado;
        file.close();
        comando<<"dot -Tpng "<<ruta<<" -o C:\\Graficas\\"<<id<<".png";
        string comand = comando.str();
        char cstr[comand.size()+1];
        strcpy(cstr,comand.c_str());
        system(cstr);
    }
};
/*************************************************************************PRINCIPAL**************************************************************************/
void graficarLA(int numimagen,Lista_circular * &imagenes,ABB * &arbol)
{
    stringstream ss;
    ss<<"digraph LA{"<<endl;
    /*-------------------------------------------------------------*/
    Nodoimagen *aux = imagenes->head;
    nodoCapa *temp;
    if(aux != NULL)
    {
        do
        {
            if(aux->id == numimagen)
            {
                ss<<"i_"<<aux->id<<" [shape = box, label = \"Imagen: "<<aux->id<<"\"];"<<endl;
                if(aux->capas != NULL)
                {
                    if(!aux->capas->vacio())
                    {

                        ss<<"i_"<<aux->id<<"->c_"<<aux->capas->primero->id<<endl;
                        temp = aux->capas->primero;
                        while(temp != NULL)
                        {
                            ss<<"c_"<<temp->id<<" [shape = box, label = \"Capa: "<<temp->id<<"\"];"<<endl;

                            if(temp->siguiente != NULL)
                            {
                                ss<<"c_"<<temp->id<<"->c_"<<temp->siguiente->id<<";"<<endl;
                            }
                            temp = temp->siguiente;
                        }
                    }
                }


            }
            aux = aux->next;
        }
        while(aux != imagenes->head);
    }
    /*-------------------------------------------------------------*/
    ss<<endl<<endl<<endl;
    ss<<arbol->grafArbol(arbol->raiz,0);
    /*-------------------------------------------------------------*/
    ss<<endl<<endl<<endl;
    aux = imagenes->head;
    do
    {
        if(aux->id == numimagen)
        {
            if(aux->capas != NULL)
            {
                if(!aux->capas->vacio())
                {
                    temp = aux->capas->primero;
                    while(temp != NULL)
                    {

                        if(arbol->existe(temp->id))
                        {
                            ss<<"c_"<<temp->id<<"->nodo"<<arbol->devolver(temp->id)<<endl;
                        }
                        temp = temp->siguiente;
                    }
                }
            }

            break;
        }
        aux = aux->next;
    }
    while(aux != imagenes->head);

    /*-------------------------------------------------------------*/
    ss<<"}"<<endl;
    string res = ss.str();
    ofstream file("C:\\Graficas\\LA.dot");
    file<<res;
    file.close();
    system("dot -Tpng C:\\Graficas\\LA.dot -o C:\\Graficas\\LA.png");
    ShellExecute(NULL,"open","C:\\Graficas\\LA.png",NULL,NULL,SW_SHOWNORMAL);

}
vector<string> split(const string& s, char del)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while(getline(tokenStream,token,del))
    {
        tokens.push_back(token);
    }
    return tokens;
}
int main()
{

    ABB *ArbolCapas = new ABB();
    ABB *ArbolEspejo = new ABB();
    Lista_circular *imagenes = new Lista_circular();
    AVL *users = new AVL;
    AVL *usaux = new AVL;

    bool bandera = false;
    char opcionmenu = '0';
    bool flag = false;
    char opcion2  = '0';
    bool flag2 = false;
    char opcionuser = '0';
    bool flag3  = false;
    char opcionre = '0';
    bool flag4 = false;
    char otra = '0';
    string imagenArbol;
    string imagenArbol2;
    do
    {
        flag = false;
        flag2 = false;
        flag3 = false;
        system("color 02");
        cout<<":-----------------------------------------------------------------------:"<<endl;
        cout<<":--------------------------DRAWING-CANVAS-------------------------------:"<<endl;
        cout<<":-----------------------------------------------------------------------:"<<endl;
        cout<<"\t 1.Cargar archivos"<<endl;
        cout<<"\t 2.Generar imagenes"<<endl;
        cout<<"\t 3.Control de Usuarios"<<endl;
        cout<<"\t 4.Ver reportes"<<endl;
        cout<<"\t 5.Otros reportes"<<endl;
        cout<<"\t 6.Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcionmenu;
        switch(opcionmenu)
        {
        case '1':
        {
            system("color 03");
            cout<<"\t\t Ingrese el archivo de capas"<<endl;
            ifstream archivo;
            stringstream ss;
            string texto;
            string rut;
            cin>>rut;
            archivo.open(rut.c_str(),ios::in);
            if(archivo.fail())
            {
                cout<<"No se pudo abrir el archivo"<<endl;
                break;
            }
            else
            {
                while(!archivo.eof())
                {
                    getline(archivo,texto);
                    ss<<texto<<endl;
                }
            }
            archivo.close();
            texto = ss.str();
            vector<string> p1 = split(texto,'}');
            for(int i = 0; i<p1.size()-1; i++)
            {
                vector<string> p2 = split(p1[i],'{');
                for(int j = 0; j<p2.size(); j++)
                {
                    int ide = atoi(p2[0].c_str());
                    Matriz *actual = new Matriz(ide);
                    ArbolCapas->insertarn(actual);
                    ArbolEspejo->insertarnEspejo(actual);
                    vector<string> lineas = split(p2[1].c_str(),';');
                    for(int z = 0; z<lineas.size(); z++)
                    {
                        cout<<lineas[z]<<endl;
                        vector<string> datos = split(lineas[z].c_str(),',');
                        for(int h = 0; h<datos.size()-1; h++)
                        {
                            int cox = atoi(datos[0].c_str());
                            int coy = atoi(datos[1].c_str());
                            actual->insertar(cox,coy,datos[2],z);
                            break;
                        }
                    }
                    break;
                }
            }
            cout<<"\t\t Ingrese el archivo de imagenes"<<endl;
            ifstream archivoimg;
            ss.str("");
            texto = "";
            cin>>rut;
            archivoimg.open(rut.c_str(),ios::in);
            if(archivoimg.fail())
            {
                cout<<"No se pudo abrir el archivo"<<endl;
                break;
            }
            else
            {
                while(!archivoimg.eof())
                {
                    getline(archivoimg,texto);
                    ss<<texto<<endl;
                }
            }
            archivoimg.close();
            texto = ss.str();
            vector<string> imgv = split(texto,'\n');
            for(int k = 0; k<imgv.size(); k++)
            {
                vector<string> img1 = split(imgv[k],'}');
                for(int i  = 0; i<img1.size(); i++)
                {
                    vector<string> img2 = split(img1[i].c_str(),'{');
                    for(int j = 0; j<img2.size(); j++)
                    {
                        int ide =atoi(img2[0].c_str());
                        imagenes->insertarInicio(ide);
                        if(img2.size()>1)
                        {
                            vector<string> img3 = split(img2[1].c_str(),',');
                            for(int z = 0; z<img3.size(); z++)
                            {
                                int capa = atoi (img3[z].c_str());
                                imagenes->insertarCapa(ide,capa);
                            }
                        }
                        break;
                    }
                }
            }
            imagenes->ordenar();
            cout<<"\t\t Ingrese el archivo de usuarios"<<endl;
            ifstream archivousers;
            ss.str("");
            texto = "";
            cin>>rut;
            archivousers.open(rut.c_str(),ios::in);
            if(archivousers.fail())
            {
                cout<<"No se pudo abrir el archivo"<<endl;
                break;
            }
            else
            {
                while(!archivousers.eof())
                {
                    getline(archivousers,texto);
                    ss<<texto<<endl;
                }
            }
            archivousers.close();
            texto = ss.str();
            vector<string> u = split(texto,'\n');
            for(int i = 0; i< u.size(); i++)
            {
                vector<string> uu = split(u[i],';');
                for(int j = 0; j<uu.size(); j++)
                {
                    vector<string> uuu = split(uu[j],':');
                    for(int z = 0; z<uuu.size(); z++)
                    {
                        string nombre = uuu[0];
                        users->insertar(nombre);
                        if(uuu.size()>1)
                        {
                            vector<string> uuuu = split(uuu[1],',');
                            for(int k = 0; k<uuuu.size(); k++)
                            {
                                int nimg = atoi(uuuu[k].c_str());
                                users->asignarImagen(nombre,nimg);
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
        case '2':
        {
            do
            {
                system("color 04");
                cout<<"\t\t 1.Por recorrido limitado"<<endl;
                cout<<"\t\t 2.Por lista de imagenes"<<endl;
                cout<<"\t\t 3.Por capa"<<endl;
                cout<<"\t\t 4.Por Usuario"<<endl;
                cout<<"\t\t 5.Regresar"<<endl;
                cout<<"Ingrese Una opcion:";
                cin>>opcion2;
                switch(opcion2)
                {
                case '1':
                {
                    int lim = 0;
                    int tipo = 0;
                    cout<<"\t Ingrese el numero de capas a utilizar: ";
                    cin>>lim;
                    cout<<"\t Ingrese el numero del tipo de recorrido: "<<endl;
                    cout<<"\t 1. Preorden"<<endl;
                    cout<<"\t 2. Inorden"<<endl;
                    cout<<"\t 3. Postorden"<<endl;
                    cin>>tipo;
                    ArbolCapas->limite = lim;
                    ArbolCapas->limiteExtra = lim;
                    if(lim > ArbolCapas->tam)
                    {
                        cout<<"EL ARBOL SOLO TIENE: "<<ArbolCapas->tam<<" CAPAS!! \a"<<endl;
                    }
                    switch(tipo)
                    {
                    case 1:
                    {
                        ArbolCapas->ordenesLimitados(tipo);
                        ArbolCapas->reset();
                        cout<<endl;
                        break;
                    }
                    case 2:
                    {
                        ArbolCapas->ordenesLimitados(tipo);
                        ArbolCapas->reset();
                        cout<<endl;
                        break;
                    }
                    case 3:
                    {
                        ArbolCapas->ordenesLimitados(tipo);
                        ArbolCapas->reset();
                        cout<<endl;
                        break;
                    }
                    default:
                    {
                        cout<<"No es una opcion valida intente de nuevo!!!  \a"<<endl;
                        break;
                    }
                    }

                    break;
                }
                case '2':
                {
                    int ni;
                    cout<<"\t Las imagenes disponibles son: "<<endl;
                    imagenes->mostrarc();
                    cout<<endl;
                    cout<<"\t Ingrese el Numero de la imagen que desea graficar"<<endl;
                    cin>>ni;
                    imagenes->graficarImagen(ni,ArbolCapas);
                    break;
                }
                case '3':
                {
                    int numcapa;
                    cout<<"\t Las capas disponibles son: "<<endl;
                    ArbolCapas->ordenes(2);
                    cout<<endl;
                    cout<<"\t Seleccione una capa para visualizarla ";
                    cin>>numcapa;
                    ArbolCapas->GraficarCapa(numcapa);
                    break;
                }
                case '4':
                {
                    cout<<"\t Los usuarios registrados son: "<<endl;
                    cout<<endl;
                    users->ordenes(2);
                    string nombre;
                    int nimg;
                    cout<<endl;
                    cout<<"\t Ingrese el nombre del usuario para ver sus imagenes"<<endl;
                    cin>>nombre;
                    if(users->buscar(nombre))
                    {
                        system("color 06");
                        cout<<"\t\t Este usuario cuenta con las siguientes imagenes"<<endl;
                        users->VerImagenes(nombre);
                        cout<<"Ingrese el numero de la imagen a graficar"<<endl;
                        cin>>nimg;
                        users->GraficarImagen(nombre,nimg,imagenes,ArbolCapas);
                    }
                    else
                    {
                        cout<<"El usuario que ingreso no existe"<<endl;
                    }
                    break;
                }
                case '5':
                {
                    flag = true;
                    break;
                }
                default:
                {
                    cout<<"OPCION INVALIDA"<<endl;
                    break;
                }
                }
            }
            while(flag == false);
            break;
        }
        case '3':
        {
            do
            {
                system("color 0f");
                cout<<"\t\t 1.Agregar Usuario"<<endl;
                cout<<"\t\t 2.Eliminar Usuario"<<endl;
                cout<<"\t\t 3.Modificar Usuario"<<endl;
                cout<<"\t\t 4.Agregar Imagen"<<endl;
                cout<<"\t\t 5.Eliminar Imagen"<<endl;
                cout<<"\t\t 6.Regresar"<<endl;
                cout<<"Ingrese Una opcion:";
                cin>>opcionuser;
                switch(opcionuser)
                {
                case '1':
                {
                    string nombre;
                    cout<<"Ingrese el nuevo nombre de usuario"<<endl;
                    cin>>nombre;
                    users->insertar(nombre);
                    cout<<"LISTO"<<endl;
                    break;
                }
                case '2':
                {
                    string nomelim;
                    cout<<"Ingrese el nombre del usuario a eliminar"<<endl;
                    cin>>nomelim;
                    users->eliminar(nomelim);
                    cout<<"LISTO"<<endl;
                    break;
                }
                case '3':
                {
                    string nommod;
                    string nuevo;
                    cout<<"Ingrese el nombre a modificar"<<endl;
                    cin>>nommod;
                    cout<<"Ingrese el nuevo nombre"<<endl;
                    cin>>nuevo;
                    users->modificar(nommod,nuevo);
                    users->reset();
                    cout<<"LISTO"<<endl;
                    break;
                }
                case '4':
                {
                    int nid;
                    cout<<"Ingrese el identificador numerico de la nueva imagen"<<endl;
                    cin>>nid;
                    imagenes->insertarInicio(nid);
                    imagenes->ordenar();
                    cout<<"LISTO"<<endl;
                    break;
                }
                case '5':
                {
                    int nelim;
                    cout<<"Ingrese el id de la imagen a eliminar"<<endl;
                    cin>>nelim;
                    imagenes->sacarElemento(nelim);
                    users->nimg = nelim;
                    users->ordenes(7);
                    users->reset();
                    cout<<"LISTO"<<endl;
                    break;
                }
                case '6':
                {
                    flag2 = true;
                    break;
                }
                default:
                    cout<<"OPCION INVALIDA"<<endl;
                    break;
                }
            }
            while(flag2 == false);
            break;
        }
        case '4':
        {
            do
            {
                system("color 09");
                cout<<"\t\t 1.Ver lista de imagenes"<<endl;
                cout<<"\t\t 2.Ver arbol de capas"<<endl;
                cout<<"\t\t 3.Ver arbol de capas espejo"<<endl;
                cout<<"\t\t 4.Ver capa"<<endl;
                cout<<"\t\t 5.Ver imagen y arbol de capas"<<endl;
                cout<<"\t\t 6.Ver arbol de usuarios"<<endl;
                cout<<"\t\t 7.Regresar"<<endl;
                cout<<"Ingrese Una opcion:";
                cin>>opcionre;
                switch(opcionre)
                {
                case '1':
                {
                    cout<<"Mostrando Imagen"<<endl;
                    imagenes->graficar();
                    ShellExecute(NULL,"open","C:\\Graficas\\ListaImagenes.png",NULL,NULL,SW_SHOWNORMAL);
                    break;
                }
                case '2':
                {
                    cout<<"Mostrando Imagen"<<endl;
                    ArbolCapas->graficar("Arbol_capas");
                    ShellExecute(NULL,"open","C:\\Graficas\\Arbol_capas.png",NULL,NULL,SW_SHOWNORMAL);
                    break;
                }
                case '3':
                {
                    cout<<"Mostrando Imagen"<<endl;
                    ArbolEspejo->graficarEspejo("Arbol_capas");
                    ShellExecute(NULL,"open","C:\\Graficas\\Arbol_capasEspejo.png",NULL,NULL,SW_SHOWNORMAL);
                    break;
                }
                case '4':
                {
                    int numcapa;
                    cout<<"Las capas disponibles son: "<<endl;
                    ArbolCapas->ordenes(2);
                    cout<<endl;
                    cout<<"Seleccione una capa para visualizarla ";
                    cin>>numcapa;
                    ArbolCapas->GraficarCapaLogica(numcapa);
                    break;
                }
                case '5':
                {
                    int ni;
                    cout<<"Las imagenes disponibles son: "<<endl;
                    imagenes->mostrarc();
                    cout<<"Ingrese el numero de la imagen que desea ver:"<<endl;
                    cin>>ni;
                    graficarLA(ni,imagenes,ArbolCapas);
                    break;
                }
                case '6':
                {
                    cout<<"Mostrando Imagen"<<endl;
                    users->graficar("avl");
                    ShellExecute(NULL,"open","C:\\Graficas\\avl.png",NULL,NULL,SW_SHOWNORMAL);
                    break;
                }
                case '7':
                {
                    flag3 = true;
                    break;
                }
                default:
                {
                    cout<<"OPCION INVALIDA"<<endl;
                    break;
                }
                }
            }
            while(flag3 == false);
            break;
        }
        case '5':
        {
            do
            {
                system("color 0a");
                cout<<"\t\t 1.Top 5 imagenes con mas capas"<<endl;
                cout<<"\t\t 2.Capas que son hojas"<<endl;
                cout<<"\t\t 3.Profundidad del arbol de capas"<<endl;
                cout<<"\t\t 4.Capas en postorden"<<endl;
                cout<<"\t\t 5.Listar las capas"<<endl;
                cout<<"\t\t 6.Top 5 usuarios con mas imagenes"<<endl;
                cout<<"\t\t 7.Arbol espejo de Usuarios"<<endl;
                cout<<"\t\t 8.Listar usuarios"<<endl;
                cout<<"\t\t 9.Regresar"<<endl;
                cout<<"Ingrese Una opcion:";
                cin>>otra;
                switch(otra)
                {
                case '1':
                {
                    imagenes->TopmasCapas();
                    break;
                }
                case '2':
                {
                    ArbolCapas->hojas(ArbolCapas->raiz);
                    break;
                }
                case '3':
                {
                    ArbolCapas->prof(ArbolCapas->raiz);
                    cout<<"La profundidad del arbol es de: "<<ArbolCapas->profundidad<<endl;
                    break;
                }
                case '4':
                {
                    cout<<"MOSTRANDO TODAS LAS CAPAS EN POSTORDEN"<<endl;
                    ArbolCapas->limite = ArbolCapas->tam;
                    ArbolCapas->limiteExtra = ArbolCapas->tam;
                    ArbolCapas->ordenesLimitados(3);
                    ArbolCapas->reset();
                    break;
                }
                case '5':
                {
                    cout<<"\t PREORDEN"<<endl;
                    ArbolCapas->ordenes(1);
                    cout<<endl;
                    cout<<"\t INORDEN"<<endl;
                    ArbolCapas->ordenes(2);
                    cout<<endl;
                    cout<<"\t POSTORDEN"<<endl;
                    ArbolCapas->ordenes(3);
                    cout<<endl;
                    break;
                }
                case '6':
                {
                    cout<<"El Top 5 de Usuarios con mas imagenes es:"<<endl;
                    users->crear();
                    users->ordenes(6);
                    users->devolvertop();
                    break;
                }
                case '7':
                {
                    cout<<"Convirtiendo el arbol de usuarios en su reflejo"<<endl;
                    usaux = users;
                    users->ordenes(5);
                    users = usaux;
                    ShellExecute(NULL,"open","C:\\Graficas\\avlespejo.png",NULL,NULL,SW_SHOWNORMAL);
                    break;
                }
                case '8':
                {
                    cout<<"\t PREORDEN"<<endl;
                    users->ordenes(1);
                    cout<<endl;
                    cout<<"\t INORDEN"<<endl;
                    users->ordenes(2);
                    cout<<endl;
                    cout<<"\t POSTORDEN"<<endl;
                    users->ordenes(3);
                    cout<<endl;
                    cout<<"\t NIVELES"<<endl;
                    users->ordenes(4);
                    cout<<endl;
                    break;
                }
                case '9':
                {
                    flag4 = true;
                    break;
                }
                default:
                {
                    cout<<"OPCION INVALIDA"<<endl;
                    break;
                }
                }
            }
            while(flag4 == false);
            break;
        }
        case '6':
        {
            system("exit");
            bandera = true;
            break;
        }
        default:
        {
            cout<<"Opcion Invalida."<<endl;
            break;
        }
        }
    }
    while(bandera == false);
    return 0;
}


