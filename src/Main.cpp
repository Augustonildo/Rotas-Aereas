#include "Aeroporto.hpp"
#include <iostream>

#define MAX_AEROPORTOS 20
using namespace std;

struct Pilha
{
    int topo;
    int itens[MAX_AEROPORTOS];
} pilha = {-1, {}};

void empilha(int i)
{
    pilha.topo++;
    pilha.itens[pilha.topo] = i;
}

int desempilha()
{
    return pilha.topo <= -1 ? -1 : pilha.itens[pilha.topo--];
}

void dfs(Aeroporto aeroporto, Aeroporto *listaAeroportos, int *aeroportosVisitados, bool reversa)
{
    aeroportosVisitados[aeroporto.id - 1] = 1;
    if (!reversa)
    {
        for (int i = 0; i < aeroporto.numeroDestinos; i++)
        {
            Aeroporto aeroportoDestino = listaAeroportos[aeroporto.listaDestinos[i] - 1];
            if (!aeroportosVisitados[aeroportoDestino.id - 1])
            {
                dfs(aeroportoDestino, listaAeroportos, aeroportosVisitados, reversa);
            }
        }
        empilha(aeroporto.id);
    }
    else
    {
        for (int i = 0; i < aeroporto.numeroOrigens; i++)
        {
            Aeroporto aeroportoOrigem = listaAeroportos[aeroporto.listaOrigens[i] - 1];
            if (!aeroportosVisitados[aeroportoOrigem.id - 1])
            {
                dfs(aeroportoOrigem, listaAeroportos, aeroportosVisitados, reversa);
            }
        }
        cout << aeroporto.id << " ";
    }
}

void primeiraDfsKosaraju(Aeroporto *listaAeroportos, int numeroAeroportos)
{
    int aeroportosVisitados[numeroAeroportos];
    for (int i = 0; i < numeroAeroportos; i++)
    {
        aeroportosVisitados[i] = 0;
    }

    for (int i = 0; i < numeroAeroportos; i++)
        if (!aeroportosVisitados[i])
        {
            dfs(listaAeroportos[i], listaAeroportos, aeroportosVisitados, false);
        }
}

void segundaDfsKosaraju(Aeroporto *listaAeroportos, int numeroAeroportos)
{
    int aeroportosVisitados[numeroAeroportos];
    for (int i = 0; i < numeroAeroportos; i++)
    {
        aeroportosVisitados[i] = 0;
    }

    int idAeroporto, i = 0;
    while ((idAeroporto = desempilha()) != -1)
    {
        if (!aeroportosVisitados[idAeroporto - 1])
        {
            printf("scc %d: ", ++i);
            dfs(listaAeroportos[idAeroporto - 1], listaAeroportos, aeroportosVisitados, true);
            printf("\n");
        }
    }
}

int main()
{
    int numeroAeroportos, numeroRotas;
    cin >> numeroAeroportos >> numeroRotas;
    int **matrizRotas = (int **)malloc(numeroAeroportos * sizeof(int *));
    for (int i = 0; i < numeroAeroportos; i++)
    {
        matrizRotas[i] = (int *)malloc(numeroAeroportos * sizeof(int));
    }

    Aeroporto listaAeroportos[numeroAeroportos];
    for (int i = 0; i < numeroAeroportos; i++)
    {
        listaAeroportos[i] = Aeroporto(i + 1);
        for (int j = 0; j < numeroAeroportos; j++)
        {
            matrizRotas[i][j] = 0;
        }
    }

    for (int i = 0; i < numeroRotas; i++)
    {
        int origem, destino;
        cin >> origem >> destino;
        matrizRotas[origem - 1][destino - 1] = 1;
        listaAeroportos[origem - 1].AdicionaAeroportoListaDestinos(destino);
        listaAeroportos[destino - 1].AdicionaAeroportoListaOrigens(origem);
    }

    primeiraDfsKosaraju(listaAeroportos, numeroAeroportos);
    segundaDfsKosaraju(listaAeroportos, numeroAeroportos);

    return 0;
}