#include <iostream>
#include <limits>
#include <cstdlib>
#include <iomanip>

/*
Rubro negra
* Inserir elemento
* remover elemento
* busca elemento
* listar elementos

*realizar testes
*/

using namespace std;

struct Arvore_RB {
    enum Cor {Vermelho, Preto};

    struct Dado{
        float valor;
        //construtor
        Dado(float v): valor(v){}

        Dado(): valor(0) {}
    };

    struct No{
        Dado info;
        Cor cor;
        No *pai;
        No *esquerda;
        No *direita;

        //construtor
        No (float valor): info(valor), cor(Vermelho), pai(nullptr), esquerda(nullptr), direita(nullptr) {}

        void print(){
            cout << "{" << fixed << setprecision(2) << info.valor << "," << (cor == Vermelho ? "V" : "P") << "}" << endl;
        }
    };

    No *raiz;

    //construtor
    Arvore_RB(): raiz(nullptr) {}

    //destrutor
    ~Arvore_RB(){
        destruir(raiz);
    }

    No *buscar(float valor){ //ok
        No *aux = raiz;
        while (aux != nullptr && aux->info.valor != valor){
            if (valor < aux->info.valor) aux = aux->esquerda;
            else aux = aux->direita;
        }
        return aux;
    }

    bool inserir(float valor){  //ok
        No *novo = new No(valor);

        if (raiz == nullptr){
            novo->cor = Preto;
            raiz = novo;
            return true;
        }

        No *atual = raiz;
        No *pai = nullptr;
        while (atual != nullptr){
            pai = atual;
            if (valor < atual->info.valor) atual = atual->esquerda;
            else atual = atual->direita;
        }

        novo->pai = pai;
        if (valor < pai->info.valor) pai->esquerda = novo;
        else pai->direita = novo;

        balancear_insercao(novo);
        return true;
    }

    bool remover(float valor) {
        No* removido = buscar(valor);
        if (removido == nullptr) return false;

        No* substituto;
        Cor corOriginal = removido->cor;

        No* filho = nullptr; // será o nó que vai substituir o removido

        if (removido->esquerda == nullptr) {
            filho = removido->direita;
            transplantar(removido, removido->direita);
        } else if (removido->direita == nullptr) {
            filho = removido->esquerda;
            transplantar(removido, removido->esquerda);
        } else {
            No* sucessor = minimo(removido->direita);
            corOriginal = sucessor->cor;
            filho = sucessor->direita;

            if (sucessor->pai == removido) {
                if (filho) filho->pai = sucessor;
            } else {
                transplantar(sucessor, sucessor->direita);
                sucessor->direita = removido->direita;
                if (sucessor->direita) sucessor->direita->pai = sucessor;
            }

            transplantar(removido, sucessor);
            sucessor->esquerda = removido->esquerda;
            if (sucessor->esquerda) sucessor->esquerda->pai = sucessor;
            sucessor->cor = removido->cor;
        }

        if (corOriginal == Preto) {
            balancear_remocao(filho, removido->pai);
        }

        delete removido;
        return true;
    }

    void print_arvore(){
        print_arvore_rec(raiz, 0);
    }

    private:
        void destruir(No *nodo){  //ok
            if (nodo == nullptr) return;
            destruir(nodo->esquerda);
            destruir(nodo->direita);
            delete nodo;
        }

        No* minimo(No* nodo) {
            while (nodo->esquerda != nullptr)
                nodo = nodo->esquerda;
            return nodo;
        }

        void balancear_insercao(No* nodo) {
            while (nodo != raiz && nodo->pai->cor == Vermelho) {
                if (nodo->pai == nodo->pai->pai->esquerda) {
                    No* tio = nodo->pai->pai->direita;
                    if (tio && tio->cor == Vermelho) {
                        nodo->pai->cor = Preto;
                        tio->cor = Preto;
                        nodo->pai->pai->cor = Vermelho;
                        nodo = nodo->pai->pai;
                    } else {
                        if (nodo == nodo->pai->direita) {
                            nodo = nodo->pai;
                            nodo = rse(nodo);
                        }
                        nodo->pai->cor = Preto;
                        nodo->pai->pai->cor = Vermelho;
                        rsd(nodo->pai->pai);
                    }
                } else {
                    No* tio = nodo->pai->pai->esquerda;
                    if (tio && tio->cor == Vermelho) {
                        nodo->pai->cor = Preto;
                        tio->cor = Preto;
                        nodo->pai->pai->cor = Vermelho;
                        nodo = nodo->pai->pai;
                    } else {
                        if (nodo == nodo->pai->esquerda) {
                            nodo = nodo->pai;
                            nodo = rsd(nodo);
                        }
                        nodo->pai->cor = Preto;
                        nodo->pai->pai->cor = Vermelho;
                        rse(nodo->pai->pai);
                    }
                }
            }
            raiz->cor = Preto;
        }

        void balancear_remocao(No* nodo, No* pai) {
            while ((nodo == nullptr || nodo->cor == Preto) && nodo != raiz) {
                if (nodo == pai->esquerda) {
                    No* irmao = pai->direita;

                    if (irmao && irmao->cor == Vermelho) {
                        irmao->cor = Preto;
                        pai->cor = Vermelho;
                        pai = rse(pai);
                        irmao = pai->direita;
                    }

                    if ((irmao->esquerda == nullptr || irmao->esquerda->cor == Preto) &&
                        (irmao->direita == nullptr || irmao->direita->cor == Preto)) {
                        irmao->cor = Vermelho;
                        nodo = pai;
                        pai = nodo->pai;
                    } else {
                        if (irmao->direita == nullptr || irmao->direita->cor == Preto) {
                            if (irmao->esquerda) irmao->esquerda->cor = Preto;
                            irmao->cor = Vermelho;
                            irmao = rsd(irmao);
                            pai->direita = irmao;
                        }
                        
                        irmao->cor = pai->cor;
                        pai->cor = Preto;
                        if (irmao->direita) irmao->direita->cor = Preto;
                        pai = rse(pai);
                        nodo = raiz;
                    }
                } else {
                    No* irmao = pai->esquerda;

                    if (irmao && irmao->cor == Vermelho) {
                        irmao->cor = Preto;
                        pai->cor = Vermelho;
                        pai = rsd(pai);
                        irmao = pai->esquerda;
                    }

                    if ((irmao->esquerda == nullptr || irmao->esquerda->cor == Preto) &&
                        (irmao->direita == nullptr || irmao->direita->cor == Preto)) {
                        irmao->cor = Vermelho;
                        nodo = pai;
                        pai = nodo->pai;
                    } else {
                        if (irmao->esquerda == nullptr || irmao->esquerda->cor == Preto) {
                            if (irmao->direita) irmao->direita->cor = Preto;
                            irmao->cor = Vermelho;
                            irmao = rse(irmao);
                            pai->esquerda = irmao;
                        }
                        irmao->cor = pai->cor;
                        pai->cor = Preto;
                        if (irmao->esquerda) irmao->esquerda->cor = Preto;
                        pai = rsd(pai);
                        nodo = raiz;
                    }
                }
            }
            if (nodo) nodo->cor = Preto;
        }

        No* rse(No* x) {
            No* y = x->direita;
            x->direita = y->esquerda;
            if (y->esquerda != nullptr)
                y->esquerda->pai = x;

            y->pai = x->pai;

            if (x->pai == nullptr)
                raiz = y;
            else if (x == x->pai->esquerda)
                x->pai->esquerda = y;
            else
                x->pai->direita = y;

            y->esquerda = x;
            x->pai = y;

            return y;
        }

        No* rsd(No* x) {
            No* y = x->esquerda;
            x->esquerda = y->direita;
            if (y->direita != nullptr)
                y->direita->pai = x;

            y->pai = x->pai;

            if (x->pai == nullptr)
                raiz = y;
            else if (x == x->pai->direita)
                x->pai->direita = y;
            else
                x->pai->esquerda = y;

            y->direita = x;
            x->pai = y;

            return y;
        }

        No* rde(No* nodo) {
            nodo->direita = rsd(nodo->direita);
            if (nodo->direita) nodo->direita->pai = nodo;
            return rse(nodo);
        }

        No* rdd(No* nodo) {
            nodo->esquerda = rse(nodo->esquerda);
            if (nodo->esquerda) nodo->esquerda->pai = nodo;
            return rsd(nodo);
        }

        void transplantar(No* u, No* v) {  //substitui u por v
            if (u->pai == nullptr)
                raiz = v;
            else if (u == u->pai->esquerda)
                u->pai->esquerda = v;
            else
                u->pai->direita = v;

            if (v != nullptr)
                v->pai = u->pai;
        }

        void print_arvore_rec(No* nodo, int nivel) {
            if (nodo == nullptr) return;

            print_arvore_rec(nodo->direita, nivel + 1);

            for (int i = 0; i < nivel; ++i) cout << "        ";
            nodo->print();

            print_arvore_rec(nodo->esquerda, nivel + 1);
        }
};


// FUNCOES SECUNDARIAS
void limpa_tela(){ 
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void limpa_buffer() { 
    cin.clear();               
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void entrada(int ini, int fim, int *opcao){  
    int a;
    cout << "Digite uma opção: ";
    cin >> a;
    while (a < ini || a > fim){
        cout << "Digite nomamente, intervalo aceito [" << ini << ',' << fim << ']' << endl;
        cout << "Digite uma opção: ";
        cin >> a;
    }
    *opcao = a;
}

int main(){
    bool continuar = true;
    int opcao;
    int valor;
    Arvore_RB *arv = new Arvore_RB();

    while(continuar){
        limpa_tela();
        cout << "1 - Inserir nodo" << endl
             << "2 - Remover nodo" << endl
             << "3 - Buscar nodo" << endl
             << "4 - Listar nodos" << endl
             << "5 - sair" << endl;

        entrada(1, 5, &opcao);
        limpa_tela();
        switch(opcao){
            case 1:
                cout << "Digite o valor que deseja inserir: ";
                cin >> valor;
                if (arv->inserir(valor)) cout << "\u2714 Valor inserido com sucesso." << endl;
                else cout << "\u274C Erro ao inserir nodo" << endl;
            break;
            case 2:
                cout << "Digite o valor que deseja remover: ";
                cin >> valor;
                if (arv->remover(valor)) cout << "\u2714 Removido com sucesso." << endl;
                else cout << "\u274C Erro ao remover o nodo." << endl;
            break;
            case 3:
                cout << "Digite o valor que deseja buscar: ";
                cin >> valor;
                if(arv->buscar(valor)) cout << "\u2714 " << valor << " encontrado com sucesso. " << endl;
                else cout << "\u274C " << valor << "não encontrado." << endl;
            break;
            case 4:
                cout << "Arvore Rubro Negra" << endl;
                arv->print_arvore();
            break;
            case 5:
                continuar = false;
            break;
        }

        if (continuar){
            cout << "Aperte enter para voltar.";
            cin.ignore();
            cin.get();
        }
    }

    delete arv;
}