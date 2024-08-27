#include "../include/Set.hpp"

StringSet::StringSet(int tamanho)
{
    this->tamanhoOriginal = tamanho;
    this->tamanhoTabela = tamanho;
    this->tamanhoConjunto = 0;
    this->tabela = new ElementoTabela[tamanhoTabela];
    for (int i = 0; i < tamanhoTabela; ++i)
    {
        tabela[i].dado = "";
        tabela[i].vazio = true;
        tabela[i].retirada = false;
    }
}

StringSet::~StringSet()
{
    delete[] tabela;
}

int StringSet::Hash(string s)
{
    int hashValue = 0;
    for (std::string::size_type i = 0; i < s.size(); i++)
    {
        hashValue += (s[i] - 'a') * i;
    }
    return hashValue;
}

void StringSet::Resize(size_t tamanho)
{

    ElementoTabela *tabelaAux = tabela;
    int tamanhoAntigo = tamanhoOriginal;

    this->tamanhoOriginal = tamanho;
    this->tamanhoTabela = tamanho;
    this->tabela = new ElementoTabela[tamanho];
    for (size_t i = 0; i < tamanho; ++i)
    {
        tabela[i].dado = "";
        tabela[i].vazio = true;
        tabela[i].retirada = false;
    }
    this->tamanhoConjunto = 0;

    for (int i = 0; i < tamanhoAntigo; ++i)
    {
        if (!tabelaAux[i].vazio && !tabelaAux[i].retirada)
        {
            Inserir(tabelaAux[i].dado);
        }
    }

    delete[] tabelaAux;
}

void StringSet::Inserir(string s)
{
    if (tamanhoConjunto + 1 >= tamanhoTabela)
    {
        Resize(tamanhoTabela * 2);
    }

    int pos = Hash(s);
    int i = 0;
    while ((i < tamanhoTabela) && tabela[(pos + i) % tamanhoTabela].dado != s && !tabela[(pos + i) % tamanhoTabela].vazio)
    {
        i++;
    }

    tabela[(pos + i) % tamanhoTabela].dado = s;
    tabela[(pos + i) % tamanhoTabela].vazio = false;
    tabela[(pos + i) % tamanhoTabela].retirada = false;
    tamanhoConjunto++;
}

void StringSet::Remover(string s)
{
    int pos = Hash(s);
    int i = 0;
    while ((i < tamanhoTabela) && tabela[(pos + i) % tamanhoTabela].dado != s && !tabela[(pos + i) % tamanhoTabela].vazio)
    {
        i++;
    }

    if (tabela[(pos + i) % tamanhoTabela].dado == s && !tabela[(pos + i) % tamanhoTabela].retirada)
    {
        tabela[(pos + i) % tamanhoTabela].retirada = true;
        tamanhoConjunto--;
    }

    return;
}

bool StringSet::Pertence(string s)
{
    int pos = Hash(s);
    int i = 0;
    while ((i < tamanhoTabela) && tabela[(pos + i) % tamanhoTabela].dado != s && !tabela[(pos + i) % tamanhoTabela].vazio)
    {
        i++;
    }

    if (tabela[(pos + i) % tamanhoTabela].dado == s && !tabela[(pos + i) % tamanhoTabela].retirada)
    {
        return true;
    }
    return false;
}

StringSet *StringSet::Intersecao(StringSet *S)
{
    StringSet *intersecao = new StringSet(tamanhoOriginal);
    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (!tabela[i].vazio && !tabela[i].retirada && S->Pertence(tabela[i].dado))
        {
            intersecao->Inserir(tabela[i].dado);
        }
    }
    return intersecao;
}

StringSet *StringSet::Uniao(StringSet *S)
{
    StringSet *uniao = new StringSet(tamanhoTabela + S->tamanhoTabela);
    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (!tabela[i].vazio && !tabela[i].retirada)
        {
            uniao->Inserir(tabela[i].dado);
        }
    }
    for (int i = 0; i < S->tamanhoTabela; ++i)
    {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada)
        {
            uniao->Inserir(S->tabela[i].dado);
        }
    }
    return uniao;
}

StringSet *StringSet::DiferencaSimetrica(StringSet *S)
{
    StringSet *diferencaSimetrica = new StringSet(tamanhoTabela + S->tamanhoTabela);
    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (!tabela[i].vazio && !tabela[i].retirada && !S->Pertence(tabela[i].dado))
        {
            diferencaSimetrica->Inserir(tabela[i].dado);
        }
    }
    for (int i = 0; i < S->tamanhoTabela; i++)
    {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada && !Pertence(S->tabela[i].dado))
        {
            diferencaSimetrica->Inserir(S->tabela[i].dado);
        }
    }
    return diferencaSimetrica;
}

void StringSet::Imprimir()
{
    cout << "{ ";
    bool primeiro = true;
    for (int i = 0; i < tamanhoTabela; i++)
    {
        if (!tabela[i].vazio && !tabela[i].retirada)
        {
            if (!primeiro)
            {
                cout << ", ";
            }
            cout << tabela[i].dado;
            primeiro = false;
        }
    }
    cout << " }" << endl;
}
