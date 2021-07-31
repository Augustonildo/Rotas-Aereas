#include "Pilha.hpp"
#include <iostream>

using namespace std;

Pilha::Pilha()
{
    topo = -1;
}

void Pilha::Empilha(int i)
{
    this->topo++;
    this->itens[this->topo] = i;
}

int Pilha::Desempilha()
{
    return this->topo <= -1 ? -1 : this->itens[this->topo--];
}
