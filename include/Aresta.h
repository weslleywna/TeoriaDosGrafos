#ifndef ARESTA_H
#define ARESTA_H
#include <list>


using namespace std;

class Grafo;
class No;

class Aresta {
public:

    Aresta(int x, int p, int id);
    ~Aresta();
    int getInfo()							{ return this->info; }
    void setInfo(int val)					{ info = val; }
    int getPeso()							{ return this->peso; }
    void setId(int id)                      { this->id = id; }
    int getId()                             { return this->id; }
    void setCor(int cor)                    { this->cor = cor; }
    int getCor()                            { return this->cor; }
    void diminuiId()                        { this->id--; }
    bool verificaVisitado()                 { return this->visitado; }
    void setVisitado()                      { this->visitado = true; }
private:
    int info;
    int peso;
    int id;
    int cor;
    bool visitado;
};

#endif // ARESTA_H
