#include "No.h"
#include <list>
#include "Grafo.h"

using namespace std;

No::No() {
    this->listaAresta = new list <Aresta>;
    this->visitado = false;
    this->grauDeEntrada = 0;
    this->cor = 0;
    this->grau = 0;
}

No::~No()
{
    //dtor
}

int No::getNumAresta()
{
    int i = 0;
    for (list<Aresta>::iterator it = listaAresta->begin(); it != listaAresta->end(); it++, i++);
    return i;
}

//Essa funcao é chamada pelo 'inserirAresta' do Grafo para colocar na lista de adjacencia do nó uma aresta passada como parametro
void No::adicionarAresta(int x, int p, int id) {
    Aresta *m = new Aresta(x, p, id);
    listaAresta->push_back(*m);
    delete m;
}
void No::setList(list<Aresta> *lista)
{
    listaAresta = lista;
}
