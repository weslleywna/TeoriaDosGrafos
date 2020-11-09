#ifndef NO_H
#define NO_H
#include <list>
#include "Aresta.h"

using namespace std;

class No
{
public:

    No();
    ~No();
    int getInfo()							{ return info; }
    void setInfo(int val)					{ info = val; }
    void adicionarAresta(int x, int p, int id);
    list<Aresta>* getList()					 { return listaAresta; }
    bool visitado;
    int getNumAresta();
    int getGrauDeEntrada()					 { return grauDeEntrada; }
    void setGrauDeEntrada()					 { grauDeEntrada++; }
    void diminuiGrauDeEntrada()				 { grauDeEntrada--; }
    void setGrau()							 { this->grau++; }
    void setId(int id)                       { this->id = id; }
    int getId()                              { return this->id; }
    void diminuiId()                         { this->id--; }
    void setCor(int cor)                     { this->cor = cor; }
    int getCor()                             { return this->cor; }
    void setList(list<Aresta> *lista);
private:
    int info; /// numero do No
    list<Aresta> *listaAresta;
    int grauDeEntrada;
    int peso;
    int cor;
    int grau;
    int id; /// id do no começa no 1 e vai ate n , usamos id para funçoes que eram necessarios uso de vetores
};

#endif // NO_H
