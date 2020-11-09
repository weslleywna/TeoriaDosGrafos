#include "Aresta.h"
#include <list>

using namespace std;

Aresta::Aresta(int x, int p, int id) {
    this->info = x;
    this->peso = p;
    this->id = id;
    this->cor = 0;
    this->visitado = false;
}

Aresta::~Aresta()
{
    //dtor
}
