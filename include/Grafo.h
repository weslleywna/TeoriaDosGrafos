#ifndef GRAFO_H
#define GRAFO_H
#include <list>
#include "No.h"
#include <vector>
#include <limits.h>
#include <string>
#include <set>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;

class Grafo
{
public:
    //Esta struct é usada para o Dijkstra como o vetor de pesos do nó escolhido para todos os outros
    typedef struct {
        int peso;
        bool visitado;
    } Conjunto;

    //Esta struct é usada para o Kruskal para guardarmos as extremidades da aresta
    struct PesoAresta{
        int infoX;
        int infoY;
        int peso;
        bool visitado;
        int idX;
        int idY;
        string stringValue;
        PesoAresta(int k, const std::string& s) : peso(k), stringValue(s) {}

        bool operator < (const PesoAresta& str) const
        {
            return (peso < str.peso);
        }
    };

typedef struct Graus   {
        int id;
        int info;
        int grau;
inline bool operator<(Graus b)
{
    if(grau<b.grau)
        return true;
    else
        return false;
}

    }Graus;



    Grafo(bool orient);

    void leTxt(string nome);
    list<No>::iterator buscaNo(int n);
    int getNumNos()								{ return this->n; }
    list<No>* getListaNos()						{ return this->listaNos; }
    bool getOrientacao()                        { return this->orientado;}
    void insereNo(int x, int id);
    void imprimirGrafo();
    bool imprimeAresta(int x);
    bool insereAresta(int x, int y, int p);
    void buscaProfundidade(int x);
    void auxBuscaProf(int x, int nivel,bool *visitado,ofstream *myFile,int pai );
    int retornaGrau(int x);
    list<No>::iterator buscaId(int n);
    bool verificaCompleto();
    vector<int>* retornaSequenciaGraus();
    bool verificaConexo();
    bool verificaKRegular();
    bool verificaAdjacencia(int x, int y);
    int dijkstra(int n, int n2);
    int ** floyd();
    void buscaLargura(int raiz);
    bool verificaEuleriano();
    void imprimeComponenteConexa(int raiz);
    void retornaComponentesConexas();
    int numeroDeComponentesConexas();
    bool verificaSeExisteNoConjuntoDeVertices(int n, vector<int> vetor, int cont);
    Grafo *subgrafoInduzido();
    vector<int> *vizinhaAbertaFechada(int n, bool fechada);
    void removeAresta(int x, int y);
    void removeNo(int x);
    vector<int>* fechamentoTransitivoDireto(int x);
    vector<int>* fechamentoTransitivoIndireto(int x);
    vector<int>* retornaDAG();
    bool verificaNoArticulacao(int n);
    bool verificaArestaPonte(int n, int m);
    Grafo * prim();
    Grafo * kruskal();
    bool verificaMesmaComponente(int x, int y);
    int guloso();
    void quickSort(vector<PesoAresta> vetor, int inicio, int fim);
    int gulosoRandomico(float alfa, int nItera);
    void setCor(int no, int cor);
    void leTxtNosso(string nome);
    bool verificaKconexo(int k);
    int gulosoReativo(int maxIte);
    //int gulosoReativo1(int maxIte);

private:
    int n;                      ///numero de nos;
    int m;                      ///numero de arestas  ;
    bool orientado;				///se o grafo é direcionado;
    int d;                      ///grau do grafo;
    list<No> *listaNos;
    bool auxInsereAresta(int x, int y, int p, bool orient);
    void auxNumeroDeComponentesConexas(int raiz,vector<bool> *visitado);
    int retornaPesoAresta(int x, int y);
    void auxBuscaLargura(int raiz, int nivel);
    bool verificaAdjacenciaPorId(int x, int y);
    int retornaPesoArestaPorId(int x, int y);
    void atualiza(list<Grafo::Graus> *candidatos,  set<int>*solucao, int cor, list<No>::iterator it, int *cores);
    bool podeColorir(int no, int cor,int *cores);
    Conjunto* removeNoSemDiminuirOId(int n);
    int find(int u,int *parent);
    void merge(int x,int y,int *parent,int *rank);
    int auxnumeroDeComponentesConexas();
    void auxBuscaProfcomponente(int info,bool *visitado, ofstream *myFile);
    void auxauxNumeroDeComponentesConexas(int raiz);
    void imprimeGrauOrdenado();
};
#endif // GRAFO_H
