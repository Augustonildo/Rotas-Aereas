#include "Aeroporto.hpp"
#include <iostream>

using namespace std;

Aeroporto::Aeroporto() {}

Aeroporto::Aeroporto(int id)
{
    this->id = id;
    this->numeroDestinos = 0;
    this->numeroOrigens = 0;
}

bool Aeroporto::PertenceListaDestinos(int idDestino)
{
    for (int i = 0; i < this->numeroDestinos; i++)
    {
        if (this->listaDestinos[i] == idDestino)
            return true;
    }
    return false;
}

bool Aeroporto::PertenceListaOrigens(int idDestino)
{
    for (int i = 0; i < this->numeroOrigens; i++)
    {
        if (this->listaOrigens[i] == idDestino)
            return true;
    }
    return false;
}

void Aeroporto::AdicionaAeroportoListaDestinos(int id)
{
    this->listaDestinos[this->numeroDestinos] = id;
    this->numeroDestinos++;
}

void Aeroporto::AdicionaAeroportoListaOrigens(int id)
{
    this->listaOrigens[this->numeroOrigens] = id;
    this->numeroOrigens++;
}