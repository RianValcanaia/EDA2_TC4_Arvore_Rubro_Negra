<div align="center" id="topo">

<img src="https://media.giphy.com/media/iIqmM5tTjmpOB9mpbn/giphy.gif" width="200px" alt="Gif animado"/>

# <code><strong> Implementação de Árvore Rubro-Negra</strong></code>

<em>Implementação de Árvore Rubro-Negra, trabalho complementar da disciplica Estrutura de Dados 2</em>

[![CPP Usage](https://img.shields.io/badge/C%2B%2B-100%25-blue?style=for-the-badge&logo=c%2B%2B)]()
[![Status](https://img.shields.io/badge/Status-Concluído-green?style=for-the-badge)]()
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Visite%20meu%20perfil-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/rian-carlos-valcanaia-b2b487168/)

</div>


## Índice

- [📌 Objetivos](#-objetivos)
- [📥 Entradas do sistema](#-entradas-do-sistema)
- [🧱 Estruturas de Dados](#-estruturas-de-dados)
- [🧰 Funcionalidades](#-funcionalidades)
- [📊 Exemplo de Execução](#-exemplo-de-execução)
- [📂 Como executar](#-como-executar)
- [👨‍🏫 Envolvidos](#-envolvidos)
- [📅 Curso](#-curso)
- [📄 Código-fonte](#-código-fonte)

## 📌 Objetivos
O trabalho consiste na implementação e demonstração de uma Árvore Rubro-Negra, dividido em duas partes: um programa interativo e um script de teste.
* Implementar uma Árvore Rubro-Negra.
* Criar funcionalidades para inserir novos elementos na árvore.
* Desenvolver uma função para remover elementos, mantendo as propriedades da árvore.
* Implementar uma função de busca de elementos.
* Criar uma função para listar todos os elementos da árvore de forma ordenada.
* Demonstrar o funcionamento da remoção em três casos específicos: um nó folha, o nó raiz e um nó interno (que não é folha nem raiz).
* Exibir a estrutura da árvore antes e depois de cada operação de remoção no script de teste.

[⬆ Voltar ao topo](#topo)

## 📥 Entradas do sistema
O sistema (`questao1.cpp`) opera através de um menu interativo no console, onde o usuário fornece as seguintes entradas:
* **Seleção de Opção:** Um número inteiro de 1 a 5 para escolher a operação desejada (Inserir, Remover, Buscar, Listar, Sair).
* **Valor do Nó:** Um número de ponto flutuante (float) para ser inserido, removido ou buscado na árvore.

[⬆ Voltar ao topo](#topo)

## 🧱 Estruturas de Dados
As principais estruturas de dados utilizadas para construir a Árvore Rubro-Negra são:

### 🔸 `Arvore_RB`
Classe principal que encapsula todos os métodos da Árvore Rubro Negra.
```cpp
struct Arvore_RB {
    enum Cor {Vermelho, Preto};
    struct Dado{ ... };
    struct No{ ... };
    No *raiz;

    // Contrutor
    Arvore_RB(): raiz(nullptr) {}

    // Destrutor
    ~Arvore_RB(){
        destruir(raiz);
    }

    // Métodos
    bool vazia(){ ... } 
    No *buscar(float valor){ ... }
    bool inserir(float valor){ ... }
    bool remover(float valor) { ... }
    void print_arvore(){ ... }
    private:
        void destruir(No *nodo){ ... }
        No* minimo(No* nodo) { ... }
        void balancear_insercao(No* nodo) { ... }
        void balancear_remocao(No* nodo, No* pai) { ... }
        No* rsd(No* x) { ... }
        No* rse(No* x) { ... }
        No* rde(No* nodo) { ... }
        No* rdd(No* nodo) { ... }
        void transplantar(No* u, No* v){ ... }
        void print_arvore_rec(No* nodo, int nivel) { ... }
};
```

### 🔸 `Cor`
Um enumerador para representar as duas cores possíveis de um nó.
```c++
enum Cor {Vermelho, Preto};
```

### 🔸 `Dado`
Estrutura que armazena a informação do nó.
```c++
struct Dado {
    float valor;

    // Construtores
    Dado(float v): valor(v){}
    Dado(): valor(0) {}
};
```

### 🔸 `No`
Estrutura que representa um nó da árvore, contendo o dado, a cor e ponteiros para os nós pai, filho à esquerda e filho à direita.
```c++
struct No {
    Dado info;
    Cor cor;
    No *pai;
    No *esquerda;
    No *direita;

    // Construtor
    No (float valor): info(valor), cor(Vermelho), pai(nullptr), esquerda(nullptr), direita(nullptr) {}

    // Métodos
    void print(){ ... }
};
```
[⬆ Voltar ao topo](#topo)

## 🧰 Funcionalidades

### 🔹 Funções Principais
Funções da classe `Arvore_RB` que realizam as operações centrais.
* `inserir()`: Insere um novo valor na árvore e chama as rotinas de balanceamento.
* `remover()`: Remove um valor da árvore e chama as rotinas de balanceamento.
* `buscar()`: Procura por um valor específico na árvore.
* `print_arvore()`: Exibe a estrutura da árvore no console de forma hierárquica.
* `vazia()`: Verifica se a árvore não possui nós.

### 🔸 Funções Secundárias
Funções auxiliares para o gerenciamento da árvore e da interface do programa.
* `balancear_insercao()`: Corrige violações das propriedades da Árvore Rubro-Negra após uma inserção.
* `balancear_remocao()`: Corrige violações das propriedades da Árvore Rubro-Negra após uma remoção.
* `rsd()`, `rse()`, `rdd()`, `rde()`: Funções de rotação para o balanceamento.
* `transplantar()`: Função utilitária para substituir um nó por outro durante a remoção.
* `minimo()`: Encontra o nó com o menor valor em uma sub-árvore.
* `destruir()`: Libera a memória alocada para os nós da árvore de forma recursiva.
* `limpa_tela()`, `limpa_buffer()`, `entrada()`: Funções de utilidade para a interface de linha de comando.

[⬆ Voltar ao topo](#topo)

## 📊 Exemplo de Execução
O projeto é dividido em dois executáveis com propósitos diferentes:
1.  **`questao1.cpp` (Programa Interativo):**
    *   O usuário compila e executa o programa, que exibe um menu com opções.
    *   É possível inserir, remover e buscar valores na árvore.
    *   A qualquer momento, o usuário pode listar a estrutura atual da árvore, que é impressa no console com as cores de cada nó (V para Vermelho, P para Preto).

2.  **`questao2.cpp` (Script de Teste):**
    *   Este programa não requer interação do usuário.
    *   Ele cria uma árvore pré-definida com os valores: `20, 10, 30, 5, 15, 25, 35`.
    *   Em seguida, demonstra as remoções solicitadas:
        *   Remove um **nó folha (5)** e imprime a árvore resultante.
        *   Remove o **nó raiz (20)** e imprime a árvore resultante.
        *   Remove um **nó interno (10)** e imprime a árvore final.

[⬆ Voltar ao topo](#topo)

## 📂 Como executar
Para compilar e executar os arquivos, é necessário um compilador C++ (como o g++). Execute os seguintes comandos no seu terminal:

**Para o programa interativo (Questão 1):**
```bash
g++ questao1.cpp -o questao1 && ./questao1
```

**Para o script de teste de remoção (Questão 2):**
```bash
g++ questao2.cpp -o questa2 && ./questao2
```

## 👨‍🏫 Envolvidos
* **Professor**: André Tavares da Silva
* **Estudantes**:
  * [Rian Valcanaia](https://github.com/RianValcanaia)

[⬆ Voltar ao topo](#topo)

## 📅 Curso

* **Universidade**: Universidade do Estado de Santa Catarina (UDESC)
* **Disciplina**: Estrutura de Dados 2
* **Semestre**: 4º

[⬆ Voltar ao topo](#topo)

## 📄 Código-fonte

🔗 [https://github.com/RianValcanaia/EDA2_TC5_Arvore_Rubro_Negra](https://github.com/RianValcanaia/EDA2_TC5_Arvore_Rubro_Negra)

[⬆ Voltar ao topo](#topo)
