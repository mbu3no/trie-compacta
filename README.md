Árvore Trie Compacta em C++

Este projeto é uma implementação da estrutura de dados **Árvore Trie Compacta** (também conhecida como Árvore Patricia), desenvolvida em C++ para armazenar e gerenciar um dicionário de palavras de forma eficiente.

A principal vantagem de uma Trie Compacta sobre uma Trie padrão é a otimização de espaço: caminhos com nós que teriam apenas um filho são comprimidos, fazendo com que cada nó interno tenha sempre ao menos dois filhos.

O programa assume que todas as palavras inseridas estão em **minúsculo e não possuem acentos ou tils**, simplificando a implementação.

## Conceito e Estrutura

A lógica da árvore é baseada em dois tipos de nós, diferenciados por uma flag booleana `no_externo`.

* **Nó Externo (`no_externo = true`):**
    * Representa o fim de um caminho e armazena uma palavra completa (a `chave`).
    * Funciona como uma "folha" da árvore.

* **Nó Interno (`no_externo = false`):**
    * Atua como um ponto de ramificação (ou decisão) na árvore.
    * Não armazena uma palavra completa. Em vez disso, possui um mapa de ponteiros (`std::map<char, No*>`) que aponta para outros nós, usando o primeiro caractere de uma subsequência como chave de acesso.

Quando uma nova palavra é inserida e seu prefixo corresponde parcialmente a uma chave em um nó externo, este nó é convertido em um nó interno, e seus filhos são criados para acomodar tanto a palavra antiga quanto a nova.

## Funcionalidades

O programa oferece um menu interativo com as seguintes operações:

* **Inserir (`insere`):** Adiciona uma nova palavra à árvore.
* **Remover (`remove`):** Apaga uma palavra existente. A estrutura é reajustada (compactada) se um nó interno ficar com apenas um filho.
* **Pesquisar (`pesquisa`):** Verifica se uma palavra existe na árvore.
* **Listar por Prefixo (`palavrasPrefixo`):** Exibe todas as palavras armazenadas que começam com um determinado prefixo.

## ⚙️ Como Compilar e Executar

Você precisará de um compilador C++ (como o g++) para executar o projeto.

1.  **Salve o código** em um arquivo, por exemplo `main.cpp`.
2.  **Abra seu terminal** e navegue até o diretório onde o arquivo foi salvo.
3.  **Compile o código** com o seguinte comando:
    ```bash
    g++ main.cpp -o trie_compacta
    ```
4.  **Execute o programa:**
    ```bash
    ./trie_compacta
    ```

## Exemplo de Uso

```console
Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Prefixos
0 - Sair
Opcao: 1
Palavra: bombeiro

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Prefixos
0 - Sair
Opcao: 1
Palavra: bom

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Prefixos
0 - Sair
Opcao: 3
Palavra: bom
Encontrada

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Prefixos
0 - Sair
Opcao: 4
Prefixo: bo
- bom
- bombeiro

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Prefixos
0 - Sair
Opcao: 2
Palavra: bom

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Prefixos
0 - Sair
Opcao: 3
Palavra: bom
Nao encontrada

Menu:
1 - Inserir
2 - Remover
3 - Pesquisar
4 - Prefixos
0 - Sair
Opcao: 0
