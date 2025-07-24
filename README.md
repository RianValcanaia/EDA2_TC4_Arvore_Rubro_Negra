<div align="center" id="topo">

<img src="https://media.giphy.com/media/iIqmM5tTjmpOB9mpbn/giphy.gif" width="200px" alt="Gif animado"/>

# <code><strong> Implementação de Árvore Rubro-Negra</strong></code>

<em>Estrutura de Dados</em>

<!-- adicionar aqui o uso das linguagens que eu passar-->
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

### 🔸 `Cor`
Um enumerador para representar as duas cores possíveis de um nó.
```c++
enum Cor {Vermelho, Preto};
