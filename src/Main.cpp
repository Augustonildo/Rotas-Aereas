#include "Aeroporto.hpp"
#include "Componente.hpp"
#include <iostream>

#define MAX_AEROPORTOS 1000
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

void dfsNatural(Aeroporto aeroporto, Aeroporto *listaAeroportos, int *aeroportosVisitados)
{
    aeroportosVisitados[aeroporto.id - 1] = 1;
    for (int i = 0; i < aeroporto.numeroDestinos; i++)
    {
        Aeroporto aeroportoDestino = listaAeroportos[aeroporto.listaDestinos[i] - 1];
        if (!aeroportosVisitados[aeroportoDestino.id - 1])
        {
            dfsNatural(aeroportoDestino, listaAeroportos, aeroportosVisitados);
        }
    }
    empilha(aeroporto.id);
}

Componente listaComponentes[MAX_AEROPORTOS];

void dfsReversa(Aeroporto aeroporto, Aeroporto *listaAeroportos, int *aeroportosVisitados, int componente)
{
    aeroportosVisitados[aeroporto.id - 1] = 1;
    for (int i = 0; i < aeroporto.numeroOrigens; i++)
    {
        Aeroporto aeroportoOrigem = listaAeroportos[aeroporto.listaOrigens[i] - 1];
        if (!aeroportosVisitados[aeroportoOrigem.id - 1])
        {
            dfsReversa(aeroportoOrigem, listaAeroportos, aeroportosVisitados, componente);
        }
    }
    listaComponentes[componente].AdicionaAeroporto(aeroporto.id);
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
            dfsNatural(listaAeroportos[i], listaAeroportos, aeroportosVisitados);
        }
}

int segundaDfsKosaraju(Aeroporto *listaAeroportos, int numeroAeroportos)
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
            listaComponentes[i] = Componente();
            dfsReversa(listaAeroportos[idAeroporto - 1], listaAeroportos, aeroportosVisitados, i++);
        }
    }
    return i;
}

int **alocarEspacoMatrizInt(int M, int N)
{
    int **matriz = (int **)malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++)
    {
        matriz[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

int main()
{
    int numeroAeroportos, numeroRotas;
    cin >> numeroAeroportos >> numeroRotas;
    int **matrizRotas = alocarEspacoMatrizInt(numeroAeroportos, numeroAeroportos);

    Aeroporto listaAeroportos[numeroAeroportos];
    for (int i = 0; i < numeroAeroportos; i++)
    {
        listaAeroportos[i] = Aeroporto(i + 1);
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
    int numeroComponentes = segundaDfsKosaraju(listaAeroportos, numeroAeroportos);
    int **matrizComponentes = alocarEspacoMatrizInt(numeroComponentes, numeroComponentes);
    for (int i = 0; i < numeroComponentes; i++)
    {
        Componente componente = listaComponentes[i];
        for (int j = 0; j < componente.numeroAeroportos; j++)
        {
            Aeroporto aeroporto = listaAeroportos[componente.listaAeroportos[j] - 1];
            for (int k = 0; k < numeroComponentes; k++)
            {
                Componente componenteVizinho = listaComponentes[k];
                if (k != i)
                {
                    for (int l = 0; l < componenteVizinho.numeroAeroportos; l++)
                    {
                        if (aeroporto.PertenceListaDestinos(listaAeroportos[componenteVizinho.listaAeroportos[l] - 1].id))
                        {
                            if (!matrizComponentes[i][k])
                            {
                                listaComponentes[i].numeroSaidas++;
                                listaComponentes[k].numeroEntradas++;
                            }
                            matrizComponentes[i][k] = 1;
                        }
                    }
                }
            }
        }
    }
    int componentesSemEntrada = 0, componentesSemSaida = 0;
    for (int i = 0; i < numeroComponentes; i++)
    {
        if (listaComponentes[i].numeroEntradas == 0)
            componentesSemEntrada++;
        if (listaComponentes[i].numeroSaidas == 0)
            componentesSemSaida++;
    }

    if (componentesSemEntrada > componentesSemSaida)
    {
        cout << componentesSemEntrada << endl;
    }
    else
    {
        cout << componentesSemSaida << endl;
    }

    return 0;
}