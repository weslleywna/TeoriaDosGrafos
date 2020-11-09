#include <iostream>
#include "Grafo.h"
#include <vector>
#include <limits.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main()
{
    srand(time(NULL));
    Grafo *G = new Grafo(false);

    ///Esse "lêTxt" é para as instâncias que possuem a letra "e" na frente.
    ///Essas são as instancias que foram escolhidas, para ativar basta descomentar abaixo e comentar a "lerTxtNosso"
    ///Pequenas
    ///G->leTxt("miles250.col");
    ///G->leTxt("miles500.col");
    ///G->leTxt("miles1000.col");
    ///G->leTxt("miles1500.col");
    ///Medias
    ///G->leTxt("le450_5c.col");
    ///G->leTxt("le450_15a.col");
    ///G->leTxt("le450_25b.col");
    ///Grandes
    ///G->leTxt("qg.order30.col");
    ///G->leTxt("qg.order40.col");
    ///G->leTxt("r1000.1.col");
    ///Esse "lêTxtNosso" é para as instâncias que nao possuem a letra "e" e possuem a primeira linha
    ///informando quantos nós e arestas o grafo possui.
    G->leTxtNosso("teste.txt");

    ///Este arquivo teste é da seguinte forma:
    /*  9
        10 20 4
        20 30 5
        40 30 6
        10 50 8
        40 60 3
        30 70 6
        40 70 2
        50 40 1
        80 90 2
        10 80 3
        60 80 4
    */

    ///Função 1: Excluir e incluir nó e aresta, a inclusão de nós e arestas é feita no "lêTXT".
    ///Para excuir nós e arestas é só chamar a funções 'G->removeNo(no)' ou "G->removeAresta(aresta)".
    ///Por exmplo vamos excluir a aresta (80,90) e os nós 80 e 90.
    ///Vamos imprimir o grafo para sabermos como ele é antes da exclusão.
    G->imprimirGrafo();
    cout<<endl;
    G->removeAresta(80,90);
    G->removeNo(80);
    G->removeNo(90);
    ///Agora vamo ver como o grafo ficou após a exclusão
    G->imprimirGrafo();

    ///Função 2: Retornar o grau do nó passado como parâmetro.
    ///Vamos passar o nó 40 como parametro, esse nó tem grau 4 de acordo com o txt.

    cout<<endl<<"Grau do no passado como parametro:"<<G->retornaGrau(40)<<endl;

    ///Função 3: Retornar a sequência de graus do grafo.

    vector<int> *seq = G->retornaSequenciaGraus();
    cout<<endl<<"{";
    for(vector<int>::iterator it = seq->begin();it != seq->end();it++)
            cout<<*it<<",";
    cout<<"}"<<endl;

    ///Função 4: Verificar se o grafo é kregular

    cout<<endl<<"O grafo e K-regular? "<<G->verificaKRegular()<<endl;

    ///Função 5: Verificar se o grafo é completo.

    cout<<endl<<"O grafo e completo? "<<G->verificaCompleto()<<endl;

    ///Função 6: Verficar se dois nós são adjacentes.

    cout<<endl<<"Os nos sao adjacentes? "<<G->verificaAdjacencia(10,20)<<endl;

    ///Função 7: Busca em  largura em profundidade, as buscas estão impressas no txt junto com os seu pais
    ///e níveis.

    G->buscaProfundidade(10);

    G->buscaLargura(30);

    ///Função 8: Verifica se o grafo é conexo

    cout<<endl<<"O Grafo e conexo? "<<G->verificaConexo()<<endl;

    ///Função 9: Verifica se dois nós estão em uma mesma componente conexa.

    cout<<endl<<"Os nos estao em uma mesma componente? "<<G->verificaMesmaComponente(30,40);

    ///Funcao 10:  verificar se um dado nó é de articulação

    cout << "Esse no e articulacao? " << G->verificaNoArticulacao(40)<<endl;


    ///Funcao 11: Verificar se uma dada aresta é ponte

    cout << "Essa aresta e ponte? " << G->verificaArestaPonte(40,60)<<endl;


    ///Funcao 12: Retornar a vizinhança (aberta/fechada) de um dado nó

    cout <<endl<<"Aberta: ";
    vector<int> *aberta = G->vizinhaAbertaFechada(40,false);
    for(vector<int>::iterator it = aberta->begin(); it!= aberta->end(); it++)
        cout << *it << ",";



    cout <<endl<< "Fechada: ";
    vector<int> *fechada = G->vizinhaAbertaFechada(40,true);
    for(vector<int>::iterator it = fechada->begin(); it!= fechada->end(); it++)
        cout << *it << ",";



    ///Funcao 13: Retornar o fechamento transitivo direto/indireto de um dado nó;
    cout <<endl<<"Fechamento direto: ";
    vector<int> *direto = G->fechamentoTransitivoDireto(20);
    for(vector<int>::iterator it = direto->begin(); it!= direto->end(); it++)
        cout << *it << ",";



    cout <<endl<< "Fechamento indireto: ";
    vector<int> *indireto = G->fechamentoTransitivoDireto(30);
    for(vector<int>::iterator it = indireto->begin(); it!= indireto->end(); it++)
        cout << *it << ",";



    ///Funcao 14: Retornar a ordenação topológica do DAG;
    cout <<endl<< "Retornar DAG: ";
    vector<int> *dag = G->retornaDAG();
    for(vector<int>::iterator it = dag->begin(); it!= dag->end(); it++)
        cout << *it << ",";


    ///Funcao 15: Determinar o caminho mínimo entre dois vértices usando algoritmo de Dijkstra
    cout << endl << "Caminho minimo: " << G->dijkstra(10, 40);


    ///Funcao 16: Determinar o caminho mínimo entre qualquer par de vértices usando o algoritmo de Floyd;
    int **floyd = G->floyd();
    for(int i = 0; i < G->getNumNos(); i++){
        cout << endl;
        for(int j = 0; j < G->getNumNos(); j++){
            if(floyd[i][j] == INT_MAX /2 )
                cout << "INF" << "\t";
            else
                cout << floyd[i][j] << "\t";

            }
    }

    ///Funcao 18: Retornar as componentes conexas do grafo. Elas estão impressas no txt.
    G->retornaComponentesConexas();

    ///Funcao 19:Subgrafo induzido. Temos que digitar os nós que vai formar o subgrafo induzido
    // Grafo *H = G->subgrafoInduzido();
    // H->imprimirGrafo();

    ///Funcao 20: Retornar a árvore geradora mínima pelo algoritmo de Kruskal.
    cout<<endl<<"KRUSKAL:"<<endl;
    Grafo *K=G->kruskal();
    K->imprimirGrafo();

    ///Funcao 21: Retornar a árvore geradora mínima pelo algoritmo de Prim.
    cout<<endl<<"PRIM:"<<endl;
    Grafo *P=G->prim();
    P->imprimirGrafo();

    ///Funcao 22: Verifica K-conexo.
    cout<<"O Grafo e K-conexo? "<<G->verificaKconexo(2)<<endl;

    ///Funcao 22: Verifica se o grafo é euleriano.

    cout<<"O Grafo e euleriano? "<<G->verificaEuleriano()<<endl;

    ///Segunda parte

    cout<<"Guloso:"<<G->guloso();

    cout << endl;

    cout <<"Guloso Randomico: " << G->gulosoRandomico(0.25,50);

    cout << endl;

    cout <<"Guloso Reativo: " << G->gulosoReativo(300);


    return 0;
}
