#include "Grafo.h"
#include <ostream>
#include <list>
#include "No.h"
#include "Aresta.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <stdlib.h>

using namespace std;

//Essas duas são para o Prim
typedef struct
{
    int infoX;
    int idX;
    int infoY;
    int idY;
    int peso;
} Menor;

typedef struct
{
    int info;
    int peso;
} Prox;

Grafo::Grafo(bool orient)
{
    this->n = 0;
    this->listaNos = new list<No>;
    this->m = 0;
    this->orientado = orient;
}

//Essa função recebe o nome do arquivo e lê preenchendo o grafo.
void Grafo::leTxt(string nome)
{
    int a, b;
    char c;
    ifstream arquivoLeitura;
    arquivoLeitura.open(nome.c_str());
    cout << "Wait";
    cout << endl;
    int id = 0;
    while (arquivoLeitura >> c >> a >> b )
    {
        //esses dois 'if' são para vermos se o nó já está inserido. Se não estiver, nós inserimos e
        //incrementamos o 'id'
        if( buscaNo(a) ==  getListaNos()->end() &&  getListaNos()->end()->getInfo() != a )
        {
            insereNo(a, id);
            id++;
        }
        if( buscaNo(b) ==  getListaNos()->end() &&  getListaNos()->end()->getInfo() != b )
        {
            insereNo(b, id);
            id++;
        }
        insereAresta(a, b, 1);
    }
    arquivoLeitura.close();
}
//Criamos essa outra função pois as instancias na internet são um pouco diferente do que você passou.
//Ela só foi feita por questão de conforto
void Grafo::leTxtNosso(string nome)
{
    int a, b, d;
    int c;
    ifstream arquivoLeitura;
    arquivoLeitura.open(nome.c_str());
    arquivoLeitura >> d;
    cout << "Wait";
    cout << endl;
    int id = 0;
    while (arquivoLeitura  >> a >> b >> c )
    {
        if( buscaNo(a) ==  getListaNos()->end() &&  getListaNos()->end()->getInfo() != a )
        {
            insereNo(a, id);
            id++;
        }
        if( buscaNo(b) ==  getListaNos()->end() &&  getListaNos()->end()->getInfo() != b )
        {
            insereNo(b, id);
            id++;
        }

        insereAresta(a, b, c);
    }
    arquivoLeitura.close();
}

//Esta funcao recebe o 'info' do nó vindo do txt. Simplesmente adiciona um nó na lista de nós
//e incrementa o numero de nós do grafo. Essa função é chamada pela 'leTxt'
void Grafo::insereNo(int x, int id)
{
    No *novo = new No();
    novo->setInfo(x);
    novo->setId(id);
    listaNos->push_back(*novo);
    n++;
    delete novo;
}

//Esta funcao retorna o iterador para um nó passado como parametro.
//É com certeza a função mais usada.
list<No>::iterator Grafo::buscaNo(int n)
{
    list<No>::iterator it;
    //aqui buscamos o iterador. Se o nó nao existir, retornamos o 'list->end'
    for (it = listaNos->begin(); it != listaNos->end() && (*it).getInfo() != n; it++);
    return it;
}
//Essa é parecida com a 'buscaNo', mas aqui buscamos pelo seu 'id', não seu 'info'
list<No>::iterator Grafo::buscaId(int n)
{
    list<No>::iterator it;
    for (it = listaNos->begin(); it != listaNos->end() && (*it).getId() != n; it++);
    return it;
}

//Esta função insere uma aresta 'y' na lista de adjacencia no 'x' com o peso 'p' passados por parâmetro.
//É chamada pelo 'lêTxt'
bool Grafo::insereAresta(int x, int y, int p)
{

    list<No>::iterator it = buscaNo(x);
    list<No>::iterator it1 = buscaNo(y);

    //para os digrafos, da ++ no grau de entrada do nó
    if(!this->orientado)
        it1->setGrauDeEntrada();


    //se ao usar o buscaNo temos que o it é igual ao 'listaNos->end', quer dizer que nao achamos o nó e
    //retornamos falso, já que não podemos inserir uma aresta em um nó que não existe
    if (it == listaNos->end() && (*it).getInfo() != x)
        return false;

    //se não, vamos nesse nó e chamamos o 'adicionarAresta' da classe 'No', que da um 'push_back' com o 'y' na
    // lista de Aresta (adjacencia) que há em cada nó
    else
    {

        this->m++; //aqui aumenta o numero de arestas total do grafo
        (*it).adicionarAresta(y, p, it1->getId());
        it->setGrau();

        //se o grafo nao é orientado, temos que adicionar a "volta" da aresta, então chamamos
        // 'adicionarAresta' do nó 'y' para dar um 'push_back' no 'x', passando o mesmo peso
        if (!orientado)
        {
            (*it1).adicionarAresta(x, p, it->getId());
            it1->setGrau();
        }
        return true;
    }
}

//Apenas uma funcao para imprimir o grafo para os grafos de teste que criamos, só para ver o que estava acontecendo
//ao remover um nó por exemplo
void  Grafo::imprimirGrafo()
{
    for (list<No>::iterator it = listaNos->begin(); it != listaNos->end(); it++)
    {

        cout << (*it).getInfo() << "-";
        imprimeAresta((*it).getInfo());
        cout << endl;
    }
}

//Esta função imprime a lista de adjacência de um nó passado por parametro. É 'bool' porque retornamos false
//caso nao achamos o nó
bool Grafo::imprimeAresta(int x)
{
    list<No>::iterator it;
    for (it = listaNos->begin(); it != listaNos->end() && (*it).getInfo() != x; it++);
    if (it == listaNos->end() && (*it).getInfo() != x)
        return false;
    else
        for (list<Aresta>::iterator it1 = (*it).getList()->begin(); it1 != (*it).getList()->end(); it1++)
            cout << (*it1).getInfo() << "-";
    return true;
}

//Essa é a busca em profunfidade a partir de um nó passado como parâmetro
void Grafo::buscaProfundidade(int x)
{
    ofstream myfile;
    myfile.open ("BuscaEmProfundidade.txt");
    bool *visitado=new bool[this->n];
    //Inicializa todos os 'visitado' com falso
    for(int i=0; i<this->n; i++)
        visitado[i]=false;


    list<No>::iterator it = buscaNo(x);

    auxBuscaProf(x, 0,visitado,&myfile,0);
}

void Grafo::auxBuscaProf(int x, int nivel,bool *visitado,ofstream *myFile,int pai)
{
    list<No>::iterator it;
    //buscamos o nó passado como parametro e o visitamos
    it = buscaNo(x);

    visitado[it->getId()]=true;
    *myFile << (*it).getInfo() <<"\ttem nivel: "<< nivel <<"\tPai:"<<pai<<endl;

    //agora pegamos as arestas dele, se ela nao foi visitda, chamaos o 'buscaProf' para visita-la
    for (list<Aresta>::iterator it1 = (*it).getList()->begin(); it1 != (*it).getList()->end(); it1++)
    {
        //aqui colocamos o 'it2' no nó que corresponde à aresta onde esta o 'it1', se ele ainda nao foi visitado, chamaos a funcao
        //recursivamente

        //it2 = buscaNo((*it1).getInfo());
        //if (!(*it2).visitado)
        if(!visitado[it1->getId()])
            //aqui passsamos o nivel do nó + 1 quando chamamos recursivamente
            auxBuscaProf((*it1).getInfo(), nivel + 1,visitado,myFile,x);
    }


}

//Esta funcao simplemente conta quantas arestas tem um nó passado como parametro
int Grafo::retornaGrau(int x)
{
    int cont = 0;
    list<No>::iterator it;

    //colocamos um iterador no nó, enquanto nao cheguei ao fim, cont++
    it = buscaNo(x);
    for (list<Aresta>::iterator it1 = (*it).getList()->begin(); it1 != (*it).getList()->end(); it1++)
        cont++;
    return cont;
}

//Esta funcao vê os graus de cada nó e coloca num vetor, da um 'sort' para coloca-los em ordem crescente
//e depois um 'reverse' para colocar em ordem decresente. Então retornamos o vetor
vector<int>* Grafo::retornaSequenciaGraus()
{
    vector<int>* graus = new vector<int>;

    for(list<No>::iterator it = listaNos->begin(); it!= listaNos->end(); it++)
        graus->push_back(retornaGrau(it->getInfo()));

    sort(graus->begin(), graus->end());
    reverse(graus->begin(), graus->end());
    return graus;
}

//Verifica se o grafo é completo. Passamos por todos os nós vendo o numero de arestas de cada, se algum nao tiver
//grau igual à numero de nós - 1, retornamos false. Se passamos por todos sem retornar false, retornamos true
bool Grafo::verificaCompleto()
{
    for(list<No>::iterator it = listaNos->begin(); it!=listaNos->end(); it++)
        if(it->getNumAresta() != this->n-1)
            return false;
    return true;
}

//Aqui pegamos a sequencia de graus, se um grau for diferente do outro, nao é K regular e retornamos false
bool Grafo::verificaKRegular()
{
    int i = 0;
    int flag;
    vector<int>* kRegular = retornaSequenciaGraus();
    flag = *(kRegular->begin());
    for (vector<int>::iterator it = kRegular->begin(); i<n; it++, i++)
        if (flag != (*it))
            return false;
    return true;
}

//Nesta funcao usamos o 'buscaNo' com o nó 'x' passado como parametro e olhamos em sua lista de ajacência
//buscando o no 'y', se acharmos, retorna true, se chegamos no final da lista e nao retornamos true, retornamos false
bool Grafo::verificaAdjacencia(int x, int y)
{
    list<No>::iterator it = buscaNo(x);
    for (list<Aresta>::iterator it1 = (*it).getList()->begin(); it1 != (*it).getList()->end(); it1++)
        if ((*it1).getInfo() == y)
            return true;
    return false;
}

//Similiar à função 'verificaAdjacencia', mas aqui, em vez de procurarmos pelo 'info' do nó, buscamos pelo 'id'
bool Grafo::verificaAdjacenciaPorId(int x, int y)
{
    list<No>::iterator it = buscaId(x);
    for (list<Aresta>::iterator it1 = (*it).getList()->begin(); it1 != (*it).getList()->end(); it1++)
        if ((*it1).getId() == y)
            return true;
    return false;
}

//Essa função recebe o 'id' de dois e retorna o peso da aresta entre eles
int Grafo::retornaPesoArestaPorId(int x, int y)
{

    list<No>::iterator it = buscaId(x);
    list<Aresta>::iterator it1;
    for (it1 = (*it).getList()->begin(); (*it1).getId() != y; it1++);
    return (*it1).getPeso();
}
//Similar à de cima, mas buscando pelo 'info' dos nós
int Grafo::retornaPesoAresta(int x, int y)
{

    list<No>::iterator it = buscaNo(x);
    list<Aresta>::iterator it1;
    for (it1 = (*it).getList()->begin(); (*it1).getInfo() != y; it1++);
    return (*it1).getPeso();
}


//Caminho minino. Recebemos dois nós como parametro e retornamos o tamnho do menor caminho entre eles. Se
//não existir, retornamos 'MAX_INT'
int Grafo::dijkstra(int x, int y)
{
    int n = buscaNo(x)->getId();
    int n2 = buscaNo(y)->getId();
    //'Conjunto' é a struct com 'peso' e 'visitado'. Esse é o vetor que guarda os pesos do nó passado como parametro para todos os outros.
    //Usamos o indice do vetor para saber em qual nó estamos. Nó 5 esta na posicao 4 por exemplo
    vector<Conjunto> conjuntoNaoVisitados(this->n);
    int cont = 0, distancia;

    //inicializamos todos os 'peso' com infinito e 'visitado' com falso
    for (int i = 0; i < this->n; i++)
    {
        conjuntoNaoVisitados[i].peso = INT_MAX;
        conjuntoNaoVisitados[i].visitado = false;
    }

    //o no passado como parametro tem peso 0
    conjuntoNaoVisitados[n].peso = 0;


    int menor = 0;

    //enquanto os nós não foram todos visitados
    while (cont < this->n)
    {

        //aqui colocamos o 'menor' (variavel que guarda qual é o proximo nó que visitaremos) na
        //primeira posicao que nao foi visitada. Foi a maneira que encontramos para inicializar
        //o 'menor' toda vez que atualizamos o vetor

        for (int i = 0; i < this->n; i++)
        {
            if (!conjuntoNaoVisitados[i].visitado)
            {
                menor = i;
                break;
            }
        }

        //encontramos qual é o menor peso no vetor que ainda nao visitamos
        for (int i = 0; i < this->n; i++)
            if ((conjuntoNaoVisitados[i].peso < conjuntoNaoVisitados[menor].peso) && !conjuntoNaoVisitados[i].visitado)
                menor = i;

        //aqui pegamos esse nó e sua lista de ajacência

        list<No>::iterator it = buscaId(menor);
        list<Aresta> *lista = (*it).getList();

        //aqui percorremos a lista de adjacencia do nó com o menor peso
        for (list<Aresta>::iterator it1 = lista->begin(); it1 != lista->end(); it1++)
        {
            //a 'distancia' é a soma do peso que estava acumulado no vetor com o peso da aresta desse nó para o seu adjacente
            distancia = conjuntoNaoVisitados[menor].peso + (*it1).getPeso();

            //se a 'distancia' for menor que o peso acumulado anteriormente, então achamos um outro caminho para chegar nesse nó
            //e atualizamos o vetor
            if (distancia < conjuntoNaoVisitados[(*it1).getId()].peso)
            {
                conjuntoNaoVisitados[(*it1).getId()].peso = distancia;
            }
        }
        //visitamos o nó e aumentamos o 'cont' . Quando 'cont' for igual ao numero de nós menos 1, entao visitamos todos
        conjuntoNaoVisitados[menor].visitado = true;
        cont++;
    }
    return conjuntoNaoVisitados[n2].peso;
}

//Caminho minimo entre todos os nós do grafo. Retornamos a matriz gerada
int** Grafo::floyd()
{
    int **menorDistancia = new int*[this->n];

    //aqui criamos a matriz
    for (int i = 0; i < this->n; i++)
    {
        menorDistancia[i] = new int[this->n];
    }

    //aqui inicializamos a matriz: se 'i'for igual a 'j', estamos na posicao que "vai" de um nó para ele mesmo, então o peso é zero
    //se não, se existe uma aresta entre 'i' e 'j', colocamos o peso dela
    //se não, colocamos infinito/2, ja é com infinito estavamos enfrentando problemas pois infinito mais 1 é igual a -infinito.
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            if (i == j)
            {
                menorDistancia[i][j] = 0;
            }
            else if ((verificaAdjacenciaPorId(i, j)))
                menorDistancia[i][j] = retornaPesoArestaPorId(i, j);
            else
            {
                menorDistancia[i][j] = INT_MAX/2;
            }
        }
    }


    // esta 'distancia' tem a mesma utilidade que no Dijkstra
    int distancia;
    for (int k = 0; k < this->n; k++)
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
            {
                //ela é a soma dos pesos de 'i' a 'k' e de 'k' a 'j'. Se ela for menor que o caminha direto
                //(de 'i' a 'j'), então achamos um melhor caminho
                distancia = menorDistancia[i][k] + menorDistancia[k][j];
                if (distancia < menorDistancia[i][j])
                    menorDistancia[i][j] = distancia;
            }

    return menorDistancia;
}
bool Grafo::verificaConexo()
{
    if(numeroDeComponentesConexas()==1)
        return true;
    else
        return false;
}
void Grafo::buscaLargura(int raiz)
{
    //aqui criamos o arquivo txt
    ofstream myfile;
    myfile.open ("BuscaEmLargura.txt");
    list<No>::iterator it;
    // colocamos o it no nó passado por parametro
    it = buscaNo(raiz);
    // usamos o vetor visitado para sabermos se o nó ja foi visitado, inicializamos com false
    vector<bool> visitado(this->n, false);
    // vetor nivel é usado para sabermos o nivel do no na busca
    vector<int> nivel(this->n, 0);
    // e o vetor pai oara sabermos o pai do no
    vector<int> pai(this->n, 0);
    // marcamos como visitado a posição passada por parametro
    visitado[it->getId()] = true;
    queue<int> fila;
    // e colocamos na fila
    fila.push(raiz);
    while(!fila.empty())
    {
        int v;
        v = fila.front();
        list<No>::iterator guarda = buscaNo(v);
        fila.pop();
        //colocamos o front da fila no txt
        myfile << v << " tem nivel: " << nivel[guarda->getId()]<<"  Pai:"<<pai[guarda->getId()] << endl;
        list<No>::iterator it1 = buscaNo(v);
        list<Aresta>* lista = it1->getList();
        //percorremos a lista de adjacencia do front da fila
        for(list<Aresta>::iterator itA = lista->begin(); itA!=lista->end() ; itA++)
        {
            // se encontramos algum no nao visitado colocamos ele na fila, marcamos como visitado, marcamos o pai dele como front e seu nivel recebe o nivel
            // do front mais 1
            if(!visitado[itA->getId()])
            {
                visitado[itA->getId()] = true;
                fila.push(itA->getInfo());
                pai[itA->getId()] = v;
                nivel[itA->getId()] = nivel[it1->getId()] + 1;
            }
        }
    }
}

//Um grafo é Euleriano se e somente se todos os graus dos vertices são pares
bool Grafo::verificaEuleriano()
{
    vector<int> *sequencia = retornaSequenciaGraus();

    //percorremos o vetor com a sequencia de graus, se algum não for par, retorna false
    for (vector<int>::iterator it = sequencia->begin(); it != sequencia->end(); it++)
        if ((*it) % 2 != 0)
            return false;
    return true;

}
//nessa função fazemos somente a busca em largura do nó da componente conexa a ser imprimida
void Grafo::imprimeComponenteConexa(int raiz)
{
    queue<int> fila;
    list<No>::iterator it;

    it = buscaNo(raiz);
    if(it == listaNos->end() && it->getInfo()!= raiz)
    {
        cout << "nao existe esse nó";
        return;
    }

    for (it = listaNos->begin(); it != listaNos->end(); it++)
    {
        it->visitado = false;
    }
    it = buscaNo(raiz);
    it->visitado = true;
    fila.push(raiz);
    while (!(fila.empty()))
    {
        it = buscaNo(fila.front());
        list<Aresta> *lista = it->getList();
        list<Aresta>::iterator it1;
        list<No>::iterator auxIt;
        for (it1 = lista->begin(); it1 != lista->end(); it1++)
        {
            auxIt = buscaNo(it1->getInfo());
            if (!(auxIt->visitado))
            {
                auxIt->visitado = true;
                fila.push(it1->getInfo());
            }
        }
        cout << fila.front() << " ";
        fila.pop();
    }
    cout << endl;
}

int Grafo::numeroDeComponentesConexas()
{
    // a variavel cont sera usada para contar as componentes
    int cont = 0;
    list<No>::iterator it;
    // usamos o vetor de visitados para marcar se um nó ja foi visitado
    vector<bool> visitado(this->n, false);
    // neste for percorremos a listas de nós, se em uma busca em largura todos os nós nao forem visitados significa que existem mais de uma compontente
    // e toda vez que a busca é chamada o cont é incrementado
    for (it = listaNos->begin(); it != listaNos->end(); it++)
    {
        if(!visitado[it->getId()])
        {
            int x=it->getInfo();
            auxNumeroDeComponentesConexas(x,&visitado);
            cont++;
        }
    }
    return cont;
}
// esta função é somente uma busca em largura auxiliar que nao cria um txt
void Grafo::auxNumeroDeComponentesConexas(int raiz,vector<bool>*visitado)
{


    list<No>::iterator it;
    it = buscaNo(raiz);

    visitado->at(it->getId()) = true;
    queue<int> fila;
    fila.push(raiz);

    while(!fila.empty())
    {
        int v;
        v = fila.front();
        fila.pop();
        list<No>::iterator it1 = buscaNo(v);
        list<Aresta>* lista = it1->getList();
        for(list<Aresta>::iterator itA = lista->begin(); itA!=lista->end() ; itA++)
        {
            if(!visitado->at(itA->getId()))
            {
                visitado->at(itA->getId()) = true;
                fila.push(itA->getInfo());

            }
        }
    }
}

bool Grafo::verificaSeExisteNoConjuntoDeVertices(int n, vector<int> vetor, int cont)
{

    for (int i = 0; i < cont; i++)
        if (n == vetor[i])
            return true;
    return false;
}

//Subgrafo induzido é aquele que é gerado por um subconjunto de vertices e todas as arestas que pertencem à esses vértices
Grafo* Grafo::subgrafoInduzido()
{

    //Criamos o novo grafo e pegamos os vertices que vão gera-lo
    Grafo *H = new Grafo(true);
    cout << "digite o subconjunto de vertices para gerar o grafo induzido H, 0 para sair" << endl;
    int x;
    int cont = 0;
    int id = 0;
    vector<int> idDosNosGrafoInduzido;
    do
    {
        cin >> x;
        if (x != 0)
        {
            H->insereNo(x, id);
            id++;
            idDosNosGrafoInduzido.push_back(x);
        }
    }
    while (x != 0);

    list<No>::iterator itInduzido;
    list<No>::iterator itOriginal;
    list<Aresta>::iterator itAresta;

    //agora vamos inserir as arestas. O primeiro 'for' percorre a lista de nós subgrafo. O segundo, os nós do grafo "original". Se existe uma
    //aresta entre os nós do subgrafo no grafo original, entao deve tambem existir no subgrafo
    for (itInduzido = H->getListaNos()->begin(); itInduzido != H->getListaNos()->end(); itInduzido++)
    {
        for (itOriginal = listaNos->begin(); itOriginal != listaNos->end(); itOriginal++)
        {
            if (verificaAdjacencia((*itOriginal).getInfo(), (*itInduzido).getInfo())
                    && verificaSeExisteNoConjuntoDeVertices((*itOriginal).getInfo(), idDosNosGrafoInduzido, cont))
            {
                H->insereAresta((*itInduzido).getInfo(), (*itOriginal).getInfo(), 1);
            }
        }
        cont++;
    }

    return H;
}


//Esta funcao retorna um vetor com os nós vizinhos do nó passado como parametro. Ela tambem recebe um bool: se 'true', retorno
//a vizinhanca fechada, se 'false', a vizinhanca aberta
vector<int> * Grafo::vizinhaAbertaFechada(int n, bool fechada)
{
    vector<int> *vizinho = new vector<int>;
    list<No>::iterator it = buscaNo(n);
    if (fechada)
        vizinho->push_back(n);
    for (list<Aresta>::iterator itA = (*it).getList()->begin(); itA != (*it).getList()->end(); itA++)
        vizinho->push_back((*itA).getInfo());
    return vizinho;
}

//Esta função remove uma aresta passada como parâmetro
void Grafo::removeAresta(int x, int y)
{
    list<No>::iterator itNo;
    list<Aresta>::iterator itAresta;
    list<Aresta> *lista;
    bool achou = false;
    //aqui buscamos o nó 'x' passado como parametro e pegamos a lista de adjacencia dele
    itNo = buscaNo(x);
    this->m--;
    lista = (*itNo).getList();

    //percorremos a lista do nó 'x' até acharmos o nó 'y' ou a lista chegar no fim
    for (itAresta = lista->begin(); itAresta != lista->end() && (*itAresta).getInfo() != y; itAresta++);
    if ((*itAresta).getInfo() == y)
    {
        //se encontramos, chamamos o 'erase' na lista de adjacencia do nó 'x' com a posicao do nó 'y'
        (*itNo).getList()->erase(itAresta);
        achou = true;
    }

    //se o grafo não é orientado, então temos que remover a "volta" do nó. Então repetimos o processo, agora removendo o
    //'x' da lista de adjacencia do 'y'
    if (!orientado && achou)
    {
        itNo = buscaNo(y);
        lista = (*itNo).getList();
        for (itAresta = lista->begin(); itAresta != lista->end() && (*itAresta).getInfo() != x; itAresta++);
        if ((*itAresta).getInfo() == x)
        {
            (*itNo).getList()->erase(itAresta);
        }

    }

}

//Essa função verifica se dois nós passados por paramêtro estão na mesma componente conexa. Para isso
//fazemos uma busca em largura. Se acharmos o nó 'y' a partir de uma busca começando da 'raiz', então
//eles estão na mesma componente. Se terminarmos a busca e não acharmos, não estão na mesma componente
bool Grafo::verificaMesmaComponente(int raiz, int y)
{
    list<No>::iterator it;
    it = buscaNo(raiz);
    vector<bool> visitado(this->n, false);
    visitado[it->getId()] = true;
    queue<int> fila;
    fila.push(raiz);

    while(!fila.empty())
    {
        int v;
        v = fila.front();
        list<No>::iterator guarda = buscaNo(v);
        fila.pop();

        list<No>::iterator it1 = buscaNo(v);
        list<Aresta>* lista = it1->getList();
        for(list<Aresta>::iterator itA = lista->begin(); itA!=lista->end() ; itA++)
        {
            if(!visitado[itA->getId()])
            {
                visitado[itA->getId()] = true;
                fila.push(itA->getInfo());
                if(itA->getInfo() == y)
                    return true;
            }
        }

    }
    return false;
}

//Remove o nó passado por parâmetro e removemos todas as arestas que inciadiam nele
void Grafo::removeNo(int n)
{
    //buscamos o nó passado por parametro e pegamos sua lista de adjacencia

    list<No>::iterator itX = buscaNo(n);
    int id = itX->getId();
    if(itX == listaNos->end() && itX->getInfo()!= n)
    {
        cout << "nao existe esse nó";
        return;
    }

    list<No>::iterator it = buscaNo(n), it1;
    it1 = it;
    list<Aresta> *l = it->getList();

    for(; it1!=listaNos->end(); it1++)
        it1->diminuiId();

    //aqui apagamos toda a lista de adjacencia do nó
    l->erase(it->getList()->begin(), it->getList()->end());

    //e aqui o nó propriamente dito
    listaNos->erase(it);
    this->n--;

    //agora temos que percorrer todoo o grafo para apagar esse nó da lista de adjacencia dos seus antigos vizinhos
    list<No>::iterator itNo, itNo1;
    list<Aresta>::iterator itAresta;
    for(itNo=listaNos->begin(); itNo!=listaNos->end(); itNo++)
        for (itAresta = itNo->getList()->begin(); itAresta != itNo->getList()->end();)
        {
            if (itAresta->getInfo() == n)
            {
                itNo->getList()->erase(itAresta++);
            }
            else
                ++itAresta;
        }
    //aqui percorremos todos os nós que estavam depois do removido para diminuir os seus 'id's, para não perdermos
    //as função que utilizao vetores como o Dikjstra por exemplo
    for(itNo=listaNos->begin(); itNo!=listaNos->end(); itNo++)
        for (itAresta = itNo->getList()->begin(); itAresta != itNo->getList()->end(); itAresta++)
            if(itAresta->getId() > id)
                itAresta->diminuiId();


}

//Similiar a 'removeNo', mas sem diminuir os 'id's dos nós posteriores. Usamos ela para verificar se um nó é de articulação
Grafo::Conjunto* Grafo::removeNoSemDiminuirOId(int n)
{
    //buscamos o nó passado como parametro e pegamos sua lista de adjacencia

    list<No>::iterator it = buscaNo(n);
    Conjunto *adj= new Conjunto[this->n];
    //aqui inicializamos  a struct
    for(int i=0; i<this->n; i++)
    {
        adj[i].visitado = false;
        adj[i].peso = 0;
    }

    if (it == listaNos->end() && it->getInfo() != n)
    {
        cout << "nao existe esse nó";
        return NULL;
    }
    int id = it->getId();

    list<No>::iterator  it1;
    it1 = it;
    list <Aresta> *l = it->getList();




    //apagos o  nó propriamente dito
    listaNos->erase(it);
    this->n--;

    //agora temos que percorrer todoo o grafo para apagar esse nó da lista de adjacencia dos seus antigos vizinhos
    list<No>::iterator itNo, itNo1;
    list<Aresta>::iterator itAresta;
    for (itNo = listaNos->begin(); itNo != listaNos->end(); itNo++)
        for (itAresta = itNo->getList()->begin(); itAresta != itNo->getList()->end();)
        {
            // se existe aresta com o nó, colocamos na struct seu peso e a posição visitado como true e excluimos do grafo
            if (itAresta->getInfo() == n)
            {
                adj[itNo->getId()].peso=itAresta->getPeso();
                adj[itNo->getId()].visitado=true;
                itNo->getList()->erase(itAresta++);
            }
            else
                ++itAresta;


        }
    //retornarmos a struct que contém com quem o nó tinha aresta e o peso da aresta
    return adj;
}

//As funções de fechamento transitivo recebem um nó por parametro e retornam o vetor com a soluão.
//As duas geram uma matriz de adjacencias, similar à do 'Floyd', mas de booleanos em vez da distancia.
//Então, no caso do transitivo direto, percorremos a linha do nó, se 'true', então temos um caminho
//do nó passado por parametro para o nó que estamos vendo. No caso do indireto, olhamos a coluna do nó
//passado. Se for 'true', quer dizer que temos um caminho do nó que estamos vendo para o nó passado.
vector<int>* Grafo::fechamentoTransitivoDireto(int x)
{
    bool **adjacencias = new bool*[this->n];
    //aqui criamos a matriz
    for (int i = 0; i < this->n; i++)
    {
        adjacencias[i] = new bool[this->n];
    }

    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            adjacencias[i][j] =  verificaAdjacenciaPorId(i, j);
        }
    }

    for (int k = 0;  k < this->n ; ++ k)
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
                if(!adjacencias[i][j])
                    adjacencias[i][j] = adjacencias[i][k] && adjacencias[k][j];

    list<No>::iterator it = buscaNo(x);
    vector<int> *fechamento = new vector<int>;
    for (int i = 0; i < this->n; i++)
        if(adjacencias[it->getId()][i])
        {
            list<No>::iterator it1 = buscaId(i);
            fechamento->push_back(it1->getInfo());
        }

    return fechamento;
}

//Explicado em cima
vector<int>* Grafo::fechamentoTransitivoIndireto(int x)
{
    bool **adjacencias = new bool*[this->n];
    //aqui criamos a matriz
    for (int i = 0; i < this->n; i++)
    {
        adjacencias[i] = new bool[this->n];
    }

    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            adjacencias[i][j] =  verificaAdjacenciaPorId(i, j);
        }
    }

    for (int k = 0;  k < this->n ; ++ k)
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->n; j++)
                if(!adjacencias[i][j])
                    adjacencias[i][j] = adjacencias[i][k] && adjacencias[k][j];

    list<No>::iterator it = buscaNo(x);
    vector<int> *fechamento = new vector<int>;
    for (int i = 0; i < this->n; i++)
        if(adjacencias[i][it->getId()])
        {
            list<No>::iterator it1 = buscaId(i);
            fechamento->push_back(it1->getInfo());
        }

    return fechamento;
}


vector<int> * Grafo::retornaDAG()
{

    vector<int> *vetor = new vector<int>;
    vector<int> s;
    bool flag = true;
    int n;
    for (list<No>::iterator it = listaNos->begin(); it != listaNos->end(); it++)
    {
        if (!it->getGrauDeEntrada())
            s.push_back(it->getInfo());
    }

    while (!s.empty())
    {
        n = s.back();
        vetor->push_back(n);
        s.pop_back();
        list<No>::iterator it = buscaNo(n);
        list<No>::iterator it2;
        for (list<Aresta>::iterator it1 = it->getList()->begin(); it1 != it->getList()->end(); it1++)
        {
            it2 = buscaNo(it1->getInfo());
            it2->diminuiGrauDeEntrada();
            if (!it2->getGrauDeEntrada())
                s.push_back(it2->getInfo());
        }
    }
    return vetor;
}


bool Grafo::verificaNoArticulacao(int n)
{
    //aqui guardamos o núemro de componentes conexas antes de remover o no
    int numCompConexas = auxnumeroDeComponentesConexas();
    //aqui guardamos o iterator do no
    list<No>::iterator it = buscaNo(n);
    //aqui o id do no
    int idNo = it->getId();
    //aqui o ponteiro para sua lista de adjacencia
    list<Aresta> *listaAdj = it->getList();
    //usamos a funçao remover nó sem diminuir o id para que quando inserirmos o nó novamente nao exista conflitos de ids, essa função retorna
    //uma struct com todas as arestas que tinham o nó a ser excluido
    Conjunto *adj=removeNoSemDiminuirOId(n);
    //aqui guardamos o numero de componentes após a exclusão
    int numComConexasDepois = auxnumeroDeComponentesConexas();
    //inserimos o nó novamente
    insereNo(n, idNo);
    //e inserimos todas as arestas com esse nó novamente
    for(it=listaNos->begin(); it!=listaNos->end(); it++)
        if(adj[it->getId()].visitado)
            it->adicionarAresta(n,adj[it->getId()].peso,idNo);
    it=buscaNo(n);
    it->setList(listaAdj);

    //se o numero de compomentes depois for diferente do numero antes retornarmos true
    return numComConexasDepois != numCompConexas;
}


//Para verificar se a aresta é ponte, removemos esta aresta. Se o numero de componentes conexas aumenta, então é ponte. Depois inserimos
//a aresta novamente
bool Grafo::verificaArestaPonte(int n, int m)
{
    if(verificaAdjacencia(n,m))
    {
        int numCompConexas = numeroDeComponentesConexas();
        int peso = retornaPesoAresta(n, m);
        removeAresta(n, m);
        int numCompConexas2 = numeroDeComponentesConexas();
        insereAresta(n, m, peso);
        return numCompConexas != numCompConexas2;
    }
    else
        return false;
}

//Arvore de custo minimo. O 'prim' vai retornar um grafo aciclico de custo minimo
Grafo* Grafo::prim()
{
    Grafo *AGM = new Grafo(this->orientado);
    //Aqui 'Prox' é uma struct para guardarmos o proximo e o peso entre o nó e seu proximo.
    // Lembrando que proximo é o nó com a menor distancia de onde estamos
    vector<Prox> prox(this->n);

    Menor menorAresta;
    //Essa struct 'menorAresta' guarda a primeira aresta que vamos inserir. Aqui inicializamos ela
    menorAresta.infoX = listaNos->begin()->getInfo();
    menorAresta.infoY = listaNos->begin()->getList()->begin()->getInfo();
    menorAresta.idX   = listaNos->begin()->getId();
    menorAresta.idY   = listaNos->begin()->getList()->begin()->getId();
    menorAresta.peso  = listaNos->begin()->getList()->begin()->getPeso();
    int menorPeso = menorAresta.peso;

    //inicializamos o vetor de 'prox' com infinito em tudo
    for (int i = 0; i < this->n; ++i)
    {
        prox[i].info = INT_MAX;
        prox[i].peso = INT_MAX;
    }

    //aqui pegamos qual vai ser a primeira aresta que vamos inserir
    for (list<No>::iterator it = listaNos->begin(); it != listaNos->end(); it++)
    {
        for (list<Aresta>::iterator itA = it->getList()->begin(); itA != it->getList()->end(); itA++)
        {
            if (itA->getPeso() < menorPeso)
            {
                menorAresta.infoX = it->getInfo();
                menorAresta.infoY = itA->getInfo();
                menorAresta.peso = itA->getPeso();
                menorAresta.idX = it->getId();
                menorAresta.idY = itA->getId();
                menorPeso = itA->getPeso();
            }
        }
    }

    //inserimos seus nós e a aresta entre eles
    AGM->insereNo(menorAresta.infoX, 0);
    AGM->insereNo(menorAresta.infoY, 0);
    AGM->insereAresta(menorAresta.infoX, menorAresta.infoY, menorAresta.peso);

    //Agora atualizamos o vetor de 'prox' visto que adicionamos dois nós

    list<No>::iterator it = buscaId(menorAresta.idX);
    list<Aresta>::iterator itA = it->getList()->begin();

    for (; itA != it->getList()->end(); itA++)
    {
        prox[itA->getId()].info = it->getInfo();
        prox[itA->getId()].peso = itA->getPeso();
    }

    it = buscaId(menorAresta.idY);
    itA = it->getList()->begin();
    for (; itA != it->getList()->end(); itA++)
    {
        if (itA->getPeso() < prox[itA->getId()].peso)
        {
            prox[itA->getId()].info = it->getInfo();
            prox[itA->getId()].peso = itA->getPeso();
        }
    }

    //zeramos o prox dos nós ja inseridos
    prox[menorAresta.idX].info = 0;
    prox[menorAresta.idY].info = 0;
    prox[menorAresta.idX].peso = 0;
    prox[menorAresta.idY].peso = 0;

    int cont = this->n - 2;
    int menorProx = 0;
    while (cont--)
    {
        //aqui inicializamos o 'menorProx' com o primeiro nó que não esta na arvore
        for (int i = 0; i < this->n; i++)
            if (prox[i].info != 0)
            {
                menorProx = i;
                break;
            }
        //e aqui buscamos dentre todos os 'prox' o menor para inserirmos
        for (int i = 0; i < this->n; i++)
            if (prox[i].peso < prox[menorProx].peso && prox[i].info != 0)
            {
                menorProx = i;
            }

        //se a menor distancia é infinito, entçao o nó esta em outra componente conexa, então vamos pra a proxima
        //iteracao
        if(prox[menorProx].info == INT_MAX)
            continue;

        list<No>::iterator it1 = buscaId(menorProx), it2 = buscaNo(prox[menorProx].info);

        //inserimos esse nó e a aresta entre ele e o que ja estava na arvore
        AGM->insereNo(it1->getInfo(), 0);
        AGM->insereAresta(it1->getInfo(), it2->getInfo(), prox[menorProx].peso);
        prox[menorProx].info = 0;
        prox[menorProx].peso = 0;
        itA = it1->getList()->begin();

        //agora atualizamos o vetor de 'prox' visto que inserimos um novo nó
        for (; itA != it1->getList()->end(); itA++)
        {
            if (itA->getPeso() < prox[itA->getId()].peso)
            {
                prox[itA->getId()].info = it1->getInfo();
                prox[itA->getId()].peso = itA->getPeso();
            }
        }
    }
    return AGM;
}

bool Grafo::verificaKconexo(int k)
{
    //aqui vemos se o grafo é conexo, se nao for podemos retornar false pois ele nao é k-conexo
    if(numeroDeComponentesConexas()>1)
        return false;
    else
    {
        //aqui verificamos se o grafo é completo, se ele for e o k for igual a n-1 retornamos true
        if(k==this->n-1)
            if(!this->orientado)
                if(this->m==(this->n*this->n -this->n)/2)
                    return true;
                else if(this->m==(this->n*this->n -this->n))
                    return true;
        //se o grafo nao for completo nada podemos afirmar sobre a k-conexidade
                else
                {

                    cout<<"Não é possivel afirmar nada sobre a k-conexidade desse grafo."<<endl;
                    return false;
                }
    }
}

void Grafo::retornaComponentesConexas()
{
    bool *visitado=new bool[this->n];
    //aqui marcamos false para todos os nós
    for (int j = 0; j <this->n; j++)
    {
        visitado[j]=false;
    }
    //aqui criamos o arquivo no qual as componentes serao impressas
    ofstream myFile;
    myFile.open ("RetornaComponentesConexas.txt");
    int j=1;
    // neste for percorremos a listas de nós, se em uma busca em profundidade todos os nós nao forem visitados significa que existem mais de uma compontente

    for(list<No>::iterator it=listaNos->begin(); it!=listaNos->end(); it++)
        if(!visitado[it->getId()])
        {
            // a cada busca chamada imprimos qual o numero da componente conexa no arquivo e a busca escreve os nós da componente no arquivo
            myFile<<"Componente Conexa "<<j<<endl;
            j++;
            auxBuscaProfcomponente(it->getInfo(), visitado, &myFile);
        }




}
//esta função é basicanmente umas busca em profundidade que processa o nó escrevendo no arquivo que é passsado por parametro
void Grafo::auxBuscaProfcomponente(int x,bool* visitado, ofstream *myFile)
{
    list<No>::iterator it;
    //buscamos o nó passado como parametro e o visitamos
    it = buscaNo(x);
    visitado[it->getId()]=true;
    *myFile << (*it).getInfo()<<endl;


    //agora pegamos as arestas dele, se ela nao foi visitda, chamaos o 'buscaProf' para visita-la
    for (list<Aresta>::iterator it1 = (*it).getList()->begin(); it1 != (*it).getList()->end(); it1++)
    {
        //aqui colocamos o 'it2' no nó que corresponde à aresta onde esta o 'it1', se ele ainda nao foi visitado, chamaos a funcao
        //recursivamente

        //it2 = buscaNo((*it1).getInfo());
        //if (!(*it2).visitado)
        if(!visitado[it1->getId()])
            //aqui passsamos o nivel do nó + 1 quando chamamos recursivamente
            auxBuscaProfcomponente((*it1).getInfo(),visitado,myFile);
    }
}



//A função find é uma função recursiva na qual sempre retorna a qual arvore o nó pertence, por ela ser recursiva
//O número que a ultima chamada da função retornar  é o numero  de  todas os nós das chamadas da recursão, isso é usado para evitar ter que mudar
//várias posições do vetor quando árvores forem unificadas
int Grafo::find(int u,int *parent)
{
    if(u!=parent[u])
        parent[u]=find(parent[u],parent);
    return parent[u];
}

//A função merge é usada para unificar duas árvores distintas, de acordo com o rank  correspondente aquela árvore
// a função junta as duas arvores, a árvore que tiver menor rank vai ter seu valor mudado para a árvore de maior rank
void Grafo::merge(int x, int y,int *parent,int *rank)
{

    int xR=find(x,parent);
    int yR=find(y,parent);

    if(rank[xR]>rank[yR])
        parent[yR]=xR;
    else
        parent[xR]=yR;

    if(parent[yR]==rank[xR])
        rank[xR]++;

}


Grafo * Grafo::kruskal()
{
    Grafo *T = new Grafo(false);
    int i = 0;
    vector<PesoAresta> pesoAresta;
    //Aqui colocamos no std::vector<PesoAresta> todas as arestas do grafo, esse vetor possui os Infos e os
    //Ids dos nós e o peso da aresta
    for (list<No>::iterator itNo = listaNos->begin(); itNo != listaNos->end(); itNo++)
    {
        for (list<Aresta>::iterator it = itNo->getList()->begin(); it != itNo->getList()->end(); it++)
        {
            PesoAresta *peso=new PesoAresta(0,"0");
            peso->infoX = itNo->getInfo();
            peso->infoY = it->getInfo();
            peso->peso = it->getPeso();
            peso->idX = itNo->getId();
            peso->idY= it->getId();
            peso->visitado=false;
            pesoAresta.push_back(*peso);
        }
    }
    //Ordenamos em ordem crescente a partir do atributo peso da Struct PesoAresta
    sort(pesoAresta.begin(),pesoAresta.end());
    //Parents é o vetor que guarda em qual arvore o nó está
    int *parents= new int[this->n];
    //Rank é o vetor onde se guarda qual árvore possui mais nós inseridos
    int *rank= new int[this->n];
    //O vetor visitados é usado para saber se um nó já foi ou nao inserido na AGM
    bool *visitado =new bool[this->n];
    //Aqui o vetor parents é inicializado como se todo nó fosse uma arvore
    //O ventor rank recebe 0 em todas as suas posições
    //E visitado false para todas suas posições
    for (int k = 0; k < this->n; k++)
    {
        parents[k]=k;
        rank[k]=0;
        visitado[k]=false;
    }
    //Aqui o loop de inserção na AGM é iniciado, e vamos percorrer o vetor pesoAresta
    for (int k = 0; k < pesoAresta.size(); k++)
    {
        int x = pesoAresta.at(k).idX;
        int y = pesoAresta.at(k).idY;
        //Usamos a função Find para saber se  os Nós da aresta estão na mesma arvore, se eles estiverem na
        //mesma árvore significa que um ciclo é formado e entao a aresta é descartada.
        if(find(x,parents)!=find(y,parents))
        {
            //se o No não está visitado ele é inserido na AGM
            if(!visitado[x])
            {
                T->insereNo(pesoAresta.at(k).infoX, pesoAresta.at(k).idX);
                visitado[x]=true;
            }
            if(!visitado[y])
            {
                T->insereNo(pesoAresta.at(k).infoY, pesoAresta.at(k).idY);
                visitado[y]=true;
            }
            //Aqui inserimos a aresta entre os dois nós
            T->insereAresta(pesoAresta.at(k).infoX, pesoAresta.at(k).infoY, pesoAresta.at(k).peso);
            //Usamos a função merge para juntar as árvores de dois nós que foram inseridos
            merge(x, y, parents, rank);
        }
    }
    delete [] rank;
    delete [] parents;
    return T;
}

int Grafo::auxnumeroDeComponentesConexas()
{
    int cont = 0;
    list<No>::iterator it;
    for (it = listaNos->begin(); it != listaNos->end(); it++)
    {
        it->visitado = false;
    }
    for (it = listaNos->begin(); it != listaNos->end(); it++)
    {
        if(!(it->visitado))
        {
            auxauxNumeroDeComponentesConexas(it->getInfo());
            cont++;
        }
    }
    return cont;
}

void Grafo::auxauxNumeroDeComponentesConexas(int raiz)
{
    queue<int> fila;
    list<No>::iterator it;
    it = buscaNo(raiz);
    it->visitado = true;
    fila.push(raiz);
    while (!(fila.empty()))
    {
        it = buscaNo(fila.front());
        list<Aresta> *lista = it->getList();
        list<Aresta>::iterator it1;
        list<No>::iterator auxIt;
        for (it1 = lista->begin(); it1 != lista->end(); it1++)
        {
            auxIt = buscaNo(it1->getInfo());
            if (!(auxIt->visitado))
            {
                auxIt->visitado = true;
                fila.push(it1->getInfo());
            }
        }
        fila.pop();
    }
    cout << endl;
}

/*
 *
 *
 *
 *  Aqui começa a segunda parte do trabalho
 *
 *
 *
 */

int Grafo::guloso()
{

    set<int> *solucao = new set<int>;
    list<Grafo::Graus> *candidatos= new list<Grafo::Graus>;
    int *cores= new int[this->n];
    for(int i=0; i<this->n; i++)
        cores[i]=0;

    ///Aqui inicializamos de candidatos com todos os nós do grafo
    for(list<No>::iterator it = listaNos->begin(); it!=listaNos->end(); it++)
    {
        Graus *grau= new Graus;;
        grau->info = it->getInfo();
        grau->id = it->getId();
        grau->grau = it->getNumAresta();
        candidatos->push_back(*grau);

    }

    ///Ordenamos os caditados em ordem crescente
    candidatos->sort();


    int cont=1;

    while(!candidatos->empty())
    {

        ///Se estamos na primeira iteracao, nós pegamos o nó de maior graus para colorir, se não, nós pegamos os de menor
        if(cont==1)
        {
            ///'candidatos->back' porque é o de maior grau
            list<No>::iterator it = buscaNo(candidatos->back().info);
            ///colocamos a cor 1 e chamamos a funcao atualiza
            cores[it->getId()]=1;
            atualiza(candidatos,solucao,1,it,cores);
            cont++;
            continue;
        }
        ///A partir da segunda iteracao, pegamos os nós de menor grau
        int cor=1;
        ///aqui achamos a menor cor com a qual podemos colorir tal nó
        while (true)
        {
            if (podeColorir(candidatos->begin()->info, cor, cores))
            {
                cores[candidatos->begin()->id] = cor;
                solucao->insert(cor);
                break;
            }
            else
                cor++;
        }
        list<No>::iterator it = buscaNo(candidatos->begin()->info);

        ///e depois chamamos a funcao atualiza
        atualiza(candidatos, solucao, cor, it, cores);

    }
    int s=(int)solucao->size();
    delete solucao;
    delete []cores;
    delete candidatos;
    return s;
}

///Essa funcao pega todos os vizinhos do nó que passamos por parametro da funcao 'guloso' e tenta pintá-los com a menor cor possivel, começando
///pelo de menor grau. Quando escolhemos a cor do nó de menor grau, tetamos pintar os outros. Os que nao conseguimos pintar com essa cor, não fazemos nada
void Grafo::atualiza(list<Grafo::Graus> *candidatos,  set<int>*solucao, int cor, list<No>::iterator it, int *cores)
{
    list<Grafo::Graus>::iterator itG;
    list<Grafo::Graus> listaAjacentes;

    ///Aqui fazemos a lista com os adjacentos do nó que pintamos no 'guloso'
    for(list<Aresta>::iterator itA = it->getList()->begin(); itA!=it->getList()->end(); itA++)
    {
        if(cores[itA->getId()] != 0)
            continue;
        Graus grau;
        grau.info = itA->getInfo();
        grau.id = itA->getId();
        list<No>::iterator it1 = buscaNo(itA->getInfo());
        grau.grau =it1->getNumAresta();
        listaAjacentes.push_back(grau);
    }

    ///excluimos o nó passado dos candidatos
    for (itG = candidatos->begin(); itG != candidatos->end() && itG->info != it->getInfo(); itG++);
    candidatos->erase(itG);

    if(!listaAjacentes.empty())
    {

        listaAjacentes.sort();
        ///aqui excluimos o menor nó da lista de candidatos, já que com certeza será pintado
        int x=listaAjacentes.begin()->info;
        list<Graus>::iterator itF= candidatos->begin();
        for (; itF != candidatos->end();)
            if(itF->info == x)
                itF=candidatos->erase(itF);
            else
                ++itF;

        ///agora tentamos achar a menor cor possivel para pintar o nó de menor grau
        int colorir = 1;
        while (true)
        {
            if (podeColorir(listaAjacentes.begin()->info, colorir, cores))
            {
                break;
            }
            else
                colorir++;
        }
        ///colocamos a cor na solucao e atualizamos os vetor de cores
        solucao->insert(colorir);
        cores[listaAjacentes.begin()->id]=colorir;

        ///aqui excluimos todos os nós adjacentes ao de menor grau, já que com certeza eles precisarão de outra cor
        ///e nem precisaremos tentar pintá-lo
        list<No>::iterator it1 = buscaNo(listaAjacentes.begin()->info);
        for (list<Aresta>::iterator itA = it1->getList()->begin(); itA != it1->getList()->end(); itA++)
            if(listaAjacentes.begin()==listaAjacentes.end())
                if (listaAjacentes.begin()->info == itA->getInfo())
                    listaAjacentes.pop_back();
                else
                    for (list<Graus>::iterator itV = listaAjacentes.begin(); itV != listaAjacentes.end();)
                    {
                        if (itV->info == itA->getInfo())
                            itV=listaAjacentes.erase(itV);
                        else
                            ++itV;
                    }

        listaAjacentes.pop_back();

        ///agora vamos pintar o resto da lista de adjacentes.
        if(!listaAjacentes.empty())
        {
            ///percorremos a lista de ajacentes
            for (list<Graus>::iterator itV = listaAjacentes.begin(); itV != listaAjacentes.end(); itV++)
                ///se eu posso colorir
                if (podeColorir(itV->info, colorir, cores))
                {
                    ///eu pinto
                    cores[itV->id] = colorir;
                    ///e apagamos ele da lista de candiatos
                    if(!candidatos->empty())
                    {
                        for (list<Graus>::iterator itX = candidatos->begin(); itX != candidatos->end();)
                        {
                            if (itX->info == itV->info)
                                itX = candidatos->erase(itX);
                            else
                                ++itX;
                        }
                    }
                }
        }
    }
}

///Esta funcao simplemente diz se podemos colorir o nó passado por parametro com a cor passada por parametro
bool Grafo::podeColorir(int no, int cor,int*cores)
{

    list<No>::iterator it = buscaNo(no);
    for(list<Aresta>::iterator itA = it->getList()->begin(); itA != it->getList()->end(); itA++)
        if(cores[itA->getId()] == cor)
            return false;
    return true;
}

int Grafo::gulosoRandomico(float alfa,int nItera)
{
    set<int> *solucao = new set<int>;
    list<Grafo::Graus> *candidatos= new list<Grafo::Graus>;
    int *cores= new int[this->n];
    int index;
    int best=INT_MAX;

    while(nItera--)
    {
        solucao->clear();
        for(int i=0; i<this->n; i++)
            cores[i]=0;

        for(list<No>::iterator it = listaNos->begin(); it!=listaNos->end(); it++)
        {
            Graus *grau= new Graus;;
            grau->info = it->getInfo();
            grau->id = it->getId();
            grau->grau = it->getNumAresta();
            candidatos->push_back(*grau);

        }
        candidatos->sort();

        int cont=1;

        while(!candidatos->empty())
        {


            if(cont==1)
            {
                list<No>::iterator it = buscaNo(candidatos->back().info);
                cores[it->getId()]=1;
                atualiza(candidatos,solucao,1,it,cores);
                cont++;
                continue;
            }

            ///a diferença do randomizado é que, em vez de pegarmos o nó de menor grau sempre, escolhemos um aleatorio baseado no alfa
            ///pasado por parametro

            int num=alfa*candidatos->size();
            if(num>0)
                index=rand()%num;
            else
                index=0;
            list<Grafo::Graus>::iterator it;
            int i;

            ///Como usamos list, precisamos desse 'for' para pegarmos a posicao do nó que foi sorteado
            ///o resto é exatamente igual
            for(it=candidatos->begin(),i=0; i<index; it++,i++);

            int cor=1;
            while (true)
            {
                if (podeColorir(it->info, cor, cores))
                {
                    cores[it->id] = cor;
                    solucao->insert(cor);
                    break;
                }
                else
                    cor++;
            }
            list<No>::iterator it1 = buscaNo(it->info);


            atualiza(candidatos, solucao, cor, it1, cores);

        }

        if(solucao->size()<best)
            best=solucao->size();


    }
    delete solucao;
    delete candidatos;
    delete []cores;
    return best;
}


int Grafo::gulosoReativo(int maxIte)
{
    //aqui os vetores  alphas e  prob são inicializados
    float alpha[]= {0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50};
    float prob[]= {1,1,1,1,1,1,1,1,1,1};
    //somProb será sempre a soma das probabilidades
    int somProb=10;
    //best começa com infinito
    int best=INT_MAX;
    //contRep é a variável que conta quantas vezes a solução nao melhorou
    int contRep=0;


    //essa repetição vai ser feita até que o maximo de iterações seja atingido ou que a solução nao melhore durante 40 iterações
    while(maxIte--)
    {

        //aqui um valor aleatorio é gerado de 0 até a soma das probabilidades
        int index=rand()%somProb;
        int i;
        //neste 'for' a posição do alpha será escolhida através de sua probabilidade, quanto mais alta for a probabilidade de um alpha
        //mais chance terá dele ser escolhido
        //essa escolha da probabilidade  é feita diminuindo o numero aleatorio gerado de cada posição do vetor prob, se a subtração do
        //index(valor aleatorio) com o prob[i] for menor ou igual a 0 o alpha[i] é escolhido, se caso essa subtração seja maior que 0
        //entao o index recebera index-prob[i] e a repetição continuará
        for(i=0; i<10; i++)
            if(index-prob[i]<=0)
                break;
            else
                index-=prob[i];
        //aqui fazemos o gulosoRandomico com o alpha escolhido
        int atual=gulosoRandomico(alpha[i],100);

        //aqui testamos se a solução atual é melhor do que a melhor solução anterior, se for a probabilidade do alpha escolhido aumentará
        // e o best se tornará o atual
        if(atual<best)
        {
            prob[i]++;
            best=atual;
        }
        somProb=0;
        //aqui a soma das probabilidades é atualizada, já que a probabilidade de um alpha pode ter aumentado
        for(i=0; i<10; i++)
            somProb+=prob[i];
        //se o atual nao for menor que o best aumentamos a variável contRep, se caso atual seja menor a variável é zerada
        if(atual>=best)
            contRep++;
        else
            contRep=0;
        //se contRep alcançar 40 iterações o laço é quebrado
        if(contRep>=40)
            break;

    }

    return  best;
}

/*
int Grafo::gulosoReativo(int maxIte) {
    double alpha[] = {0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55};
    double prob[] = {1.0/10.0, 1.0/10.0, 1.0/10.0, 1.0/10.0, 1.0/10.0, 1.0/10.0, 1.0/10.0, 1.0/10.0, 1.0/10.0, 1.0/10.0};
    double q[10];
    int bests[10];
    int acumSol[10];
    int somProb = 10;
    int best = INT_MAX;
    int contRep = 0;
    int cont1=0;
    int bloco=0;
    int numIte[]={0,0,0,0,0,0,0,0,0,0};
    for(int i=0;i<10;i++) {
        bests[i] = gulosoRandomico(alpha[i], 50);
        acumSol[i]=bests[i];
    }

    while(maxIte--)
    {
        bloco++;
        if(bloco%30==0) {
            for (int i = 0; i < 10; i++)
                if(numIte[i]>0)
                    q[i] =(double) bests[i] / (acumSol[i] / numIte[i]);
                else
                    q[i] =(double) bests[i] / (acumSol[i]);
            int soma=0;
            for(int i=0;i<10;i++)
                soma+=q[i];
            for (int i = 0; i < 10; i++)
                prob[i]=q[i]/(soma-q[i]);
        }
        double index=(double((rand()%10))/10);
        cout<<"Index:"<<index<<endl;
        int i;
        double acum=prob[0];
        for(i=0;i<9;i++)
            if(acum>=index)
                break;
            else
            {
                acum+=prob[i+1];
                cout<<"Acum:"<<acum<<endl;
            }


        int solucao=gulosoRandomico(alpha[i],50);
        cout<<".";
        acumSol[i]+=solucao;
        numIte[i]++;
        if(solucao<best)
        {
            best=solucao;
            bests[i]=solucao;
            cont1=0;
        }
        else
            cont1++;

        if(cont1>=40)
            break;

    }
    cout<<"Vetor de prob:";
    cout<<"{";
    for(int i=0;i<10;i++)
        cout<<prob[i]<<endl;
    cout<<"}";


    return best;
}
*/


