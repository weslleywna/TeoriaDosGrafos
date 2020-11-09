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

    ///Esse "l�Txt" � para as inst�ncias que possuem a letra "e" na frente.
    ///Essas s�o as instancias que foram escolhidas, para ativar basta descomentar abaixo e comentar a "lerTxtNosso"
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
    ///Esse "l�TxtNosso" � para as inst�ncias que nao possuem a letra "e" e possuem a primeira linha
    ///informando quantos n�s e arestas o grafo possui.
    G->leTxtNosso("teste.txt");

    ///Este arquivo teste � da seguinte forma:
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

    ///Fun��o 1: Excluir e incluir n� e aresta, a inclus�o de n�s e arestas � feita no "l�TXT".
    ///Para excuir n�s e arestas � s� chamar a fun��es 'G->removeNo(no)' ou "G->removeAresta(aresta)".
    ///Por exmplo vamos excluir a aresta (80,90) e os n�s 80 e 90.
    ///Vamos imprimir o grafo para sabermos como ele � antes da exclus�o.
    G->imprimirGrafo();
    cout<<endl;
    G->removeAresta(80,90);
    G->removeNo(80);
    G->removeNo(90);
    ///Agora vamo ver como o grafo ficou ap�s a exclus�o
    G->imprimirGrafo();

    ///Fun��o 2: Retornar o grau do n� passado como par�metro.
    ///Vamos passar o n� 40 como parametro, esse n� tem grau 4 de acordo com o txt.

    cout<<endl<<"Grau do no passado como parametro:"<<G->retornaGrau(40)<<endl;

    ///Fun��o 3: Retornar a sequ�ncia de graus do grafo.

    vector<int> *seq = G->retornaSequenciaGraus();
    cout<<endl<<"{";
    for(vector<int>::iterator it = seq->begin();it != seq->end();it++)
            cout<<*it<<",";
    cout<<"}"<<endl;

    ///Fun��o 4: Verificar se o grafo � kregular

    cout<<endl<<"O grafo e K-regular? "<<G->verificaKRegular()<<endl;

    ///Fun��o 5: Verificar se o grafo � completo.

    cout<<endl<<"O grafo e completo? "<<G->verificaCompleto()<<endl;

    ///Fun��o 6: Verficar se dois n�s s�o adjacentes.

    cout<<endl<<"Os nos sao adjacentes? "<<G->verificaAdjacencia(10,20)<<endl;

    ///Fun��o 7: Busca em  largura em profundidade, as buscas est�o impressas no txt junto com os seu pais
    ///e n�veis.

    G->buscaProfundidade(10);

    G->buscaLargura(30);

    ///Fun��o 8: Verifica se o grafo � conexo

    cout<<endl<<"O Grafo e conexo? "<<G->verificaConexo()<<endl;

    ///Fun��o 9: Verifica se dois n�s est�o em uma mesma componente conexa.

    cout<<endl<<"Os nos estao em uma mesma componente? "<<G->verificaMesmaComponente(30,40);

    ///Funcao 10:  verificar se um dado n� � de articula��o

    cout << "Esse no e articulacao? " << G->verificaNoArticulacao(40)<<endl;


    ///Funcao 11: Verificar se uma dada aresta � ponte

    cout << "Essa aresta e ponte? " << G->verificaArestaPonte(40,60)<<endl;


    ///Funcao 12: Retornar a vizinhan�a (aberta/fechada) de um dado n�

    cout <<endl<<"Aberta: ";
    vector<int> *aberta = G->vizinhaAbertaFechada(40,false);
    for(vector<int>::iterator it = aberta->begin(); it!= aberta->end(); it++)
        cout << *it << ",";



    cout <<endl<< "Fechada: ";
    vector<int> *fechada = G->vizinhaAbertaFechada(40,true);
    for(vector<int>::iterator it = fechada->begin(); it!= fechada->end(); it++)
        cout << *it << ",";



    ///Funcao 13: Retornar o fechamento transitivo direto/indireto de um dado n�;
    cout <<endl<<"Fechamento direto: ";
    vector<int> *direto = G->fechamentoTransitivoDireto(20);
    for(vector<int>::iterator it = direto->begin(); it!= direto->end(); it++)
        cout << *it << ",";



    cout <<endl<< "Fechamento indireto: ";
    vector<int> *indireto = G->fechamentoTransitivoDireto(30);
    for(vector<int>::iterator it = indireto->begin(); it!= indireto->end(); it++)
        cout << *it << ",";



    ///Funcao 14: Retornar a ordena��o topol�gica do DAG;
    cout <<endl<< "Retornar DAG: ";
    vector<int> *dag = G->retornaDAG();
    for(vector<int>::iterator it = dag->begin(); it!= dag->end(); it++)
        cout << *it << ",";


    ///Funcao 15: Determinar o caminho m�nimo entre dois v�rtices usando algoritmo de Dijkstra
    cout << endl << "Caminho minimo: " << G->dijkstra(10, 40);


    ///Funcao 16: Determinar o caminho m�nimo entre qualquer par de v�rtices usando o algoritmo de Floyd;
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

    ///Funcao 18: Retornar as componentes conexas do grafo. Elas est�o impressas no txt.
    G->retornaComponentesConexas();

    ///Funcao 19:Subgrafo induzido. Temos que digitar os n�s que vai formar o subgrafo induzido
    // Grafo *H = G->subgrafoInduzido();
    // H->imprimirGrafo();

    ///Funcao 20: Retornar a �rvore geradora m�nima pelo algoritmo de Kruskal.
    cout<<endl<<"KRUSKAL:"<<endl;
    Grafo *K=G->kruskal();
    K->imprimirGrafo();

    ///Funcao 21: Retornar a �rvore geradora m�nima pelo algoritmo de Prim.
    cout<<endl<<"PRIM:"<<endl;
    Grafo *P=G->prim();
    P->imprimirGrafo();

    ///Funcao 22: Verifica K-conexo.
    cout<<"O Grafo e K-conexo? "<<G->verificaKconexo(2)<<endl;

    ///Funcao 22: Verifica se o grafo � euleriano.

    cout<<"O Grafo e euleriano? "<<G->verificaEuleriano()<<endl;

    ///Segunda parte

    cout<<"Guloso:"<<G->guloso();

    cout << endl;

    cout <<"Guloso Randomico: " << G->gulosoRandomico(0.25,50);

    cout << endl;

    cout <<"Guloso Reativo: " << G->gulosoReativo(300);


    return 0;
}
