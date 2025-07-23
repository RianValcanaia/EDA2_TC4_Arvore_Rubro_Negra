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

    bool vazia(){
        return (raiz == nullptr)? true: false;
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
                if (nodo->pai->pai == nullptr) break;

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
                            No* novoSub = rse(nodo);
                            if (novoSub->pai == nullptr) raiz = novoSub;
                            nodo = novoSub->esquerda; 
                        }

                        nodo->pai->cor = Preto;
                        nodo->pai->pai->cor = Vermelho;
                        No* novoSub = rsd(nodo->pai->pai);
                        if (novoSub->pai == nullptr) raiz = novoSub;
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
                            No* novoSub = rsd(nodo);
                            if (novoSub->pai == nullptr) raiz = novoSub;
                            nodo = novoSub->direita;
                        }
                        nodo->pai->cor = Preto;
                        nodo->pai->pai->cor = Vermelho;
                        No* novoSub = rse(nodo->pai->pai);
                        if (novoSub->pai == nullptr) raiz = novoSub;
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

        No* rsd(No* x) {
            if (x == nullptr || x->esquerda == nullptr) return x;  // proteção

            No* y = x->esquerda;
            x->esquerda = y->direita;
            if (y->direita) y->direita->pai = x;

            y->pai = x->pai;
            if (x->pai == nullptr) raiz = y;
            else if (x == x->pai->esquerda) x->pai->esquerda = y;
            else x->pai->direita = y;

            y->direita = x;
            x->pai = y;

            return y;
        }

        No* rse(No* x) {
            if (x == nullptr || x->direita == nullptr) return x;  // proteção

            No* y = x->direita;
            x->direita = y->esquerda;
            if (y->esquerda) y->esquerda->pai = x;

            y->pai = x->pai;
            if (x->pai == nullptr) raiz = y;
            else if (x == x->pai->esquerda) x->pai->esquerda = y;
            else x->pai->direita = y;

            y->esquerda = x;
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

int main() {
    Arvore_RB *arv = new Arvore_RB();

    arv->inserir(20);
    arv->inserir(10);
    arv->inserir(30);
    arv->inserir(5);
    arv->inserir(15);
    arv->inserir(25);
    arv->inserir(35);

    cout << "Árvore inicial:" << endl;
    arv->print_arvore();
    cout << "-------------------------" << endl;

    cout << "Removendo nó folha (5):" << endl;
    arv->remover(5);
    arv->print_arvore();
    cout << "-------------------------" << endl;

    cout << "Removendo raiz (20):" << endl;
    arv->remover(20);
    arv->print_arvore();
    cout << "-------------------------" << endl;

    cout << "Removendo nó interno (10):" << endl;
    arv->remover(10);
    arv->print_arvore();

    delete arv;
    return 0;
}
