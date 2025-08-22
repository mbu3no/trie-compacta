#include <iostream>
#include <map>
#include <string>
using namespace std;

// Nó da Trie: pode ser interno (com filhos) ou externo (contém palavra completa)
struct No {
    bool no_externo;
    string chave;
    map<char, No*> filhos;

    No(bool externo = false, string k = "") {
        no_externo = externo;
        chave = k;
    }
};

class TrieCompacta {
private:
    No* raiz;

    // Insere palavra na Trie
    void insereRec(No*& n, const string& palavra) {
        if (!n) {
            n = new No(true, palavra);
            return;
        }

        if (n->no_externo) {
            string antiga = n->chave;
            if (antiga == palavra) return;

            n->no_externo = false;
            n->chave = "";

            No* novo = new No(true, palavra);
            No* antigo = new No(true, antiga);

            n->filhos[antiga[0]] = antigo;
            n->filhos[palavra[0]] = novo;
        } else {
            char letra = palavra[0];
            if (!n->filhos.count(letra)) {
                n->filhos[letra] = new No(true, palavra);
            } else {
                insereRec(n->filhos[letra], palavra);
            }
        }
    }

    // Busca palavra na Trie
    bool pesquisaRec(No* n, const string& palavra) {
        if (!n) return false;
        if (n->no_externo) return n->chave == palavra;

        char letra = palavra[0];
        if (!n->filhos.count(letra)) return false;

        return pesquisaRec(n->filhos[letra], palavra);
    }

    // Imprime palavras com determinado prefixo
    void palavrasPrefixoRec(No* n, const string& prefixo) {
        if (!n) return;

        if (n->no_externo) {
            if (n->chave.find(prefixo) == 0)
                cout << "- " << n->chave << "\n";
            return;
        }

        for (auto& par : n->filhos)
            palavrasPrefixoRec(par.second, prefixo);
    }

    // Remove palavra da Trie
    bool removeRec(No*& n, const string& palavra) {
        if (!n) return false;

        if (n->no_externo) {
            if (n->chave == palavra) {
                delete n;
                n = nullptr;
                return true;
            }
            return false;
        }

        char letra = palavra[0];
        if (!n->filhos.count(letra)) return false;

        bool apagou = removeRec(n->filhos[letra], palavra);

        if (apagou && n->filhos[letra] == nullptr)
            n->filhos.erase(letra);

        // Se restar apenas um filho e ele for externo, transforma nó atual em externo
        if (n->filhos.size() == 1) {
            auto it = n->filhos.begin();
            No* filho = it->second;
            if (filho->no_externo) {
                string nova = filho->chave;
                delete filho;
                n->filhos.clear();
                n->no_externo = true;
                n->chave = nova;
            }
        }

        return apagou;
    }

public:
    TrieCompacta() { raiz = nullptr; }

    void insere(const string& palavra) { insereRec(raiz, palavra); }
    void remove(const string& palavra) {
        if (!removeRec(raiz, palavra))
            cout << "Nao encontrada.\n";
    }
    bool pesquisa(const string& palavra) { return pesquisaRec(raiz, palavra); }

    void palavrasPrefixo(const string& prefixo) {
        palavrasPrefixoRec(raiz, prefixo);
    }
};

int main() {
    TrieCompacta trie;
    int op;
    string palavra, prefixo;

    do {
        cout << "\nMenu:\n1 - Inserir\n2 - Remover\n3 - Pesquisar\n4 - Prefixos\n0 - Sair\nOpcao: ";
        cin >> op;

        switch (op) {
            case 1:
                cout << "Palavra: "; cin >> palavra;
                trie.insere(palavra);
                break;
            case 2:
                cout << "Palavra: "; cin >> palavra;
                trie.remove(palavra);
                break;
            case 3:
                cout << "Palavra: "; cin >> palavra;
                cout << (trie.pesquisa(palavra) ? "Encontrada\n" : "Nao encontrada\n");
                break;
            case 4:
                cout << "Prefixo: "; cin >> prefixo;
                trie.palavrasPrefixo(prefixo);
                break;
        }
    } while (op != 0);

    return 0;
}
