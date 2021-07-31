#include "Componente.hpp"
#include <iostream>

using namespace std;

Componente::Componente()
{
    this->numeroAeroportos = 0;
    this->numeroEntradas = 0;
    this->numeroSaidas = 0;
}

void Componente::AdicionaAeroporto(int idDestino)
{
    this->listaAeroportos[this->numeroAeroportos] = idDestino;
    this->numeroAeroportos++;
}
