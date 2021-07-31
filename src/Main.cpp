#include "Aeroporto.hpp"
#include "Componente.hpp"
#include "Pilha.hpp"
#include <iostream>

#define MAX_AEROPORTOS 1000
using namespace std;

Pilha pilha = Pilha();
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
    pilha.Empilha(aeroporto.id);
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
        aeroportosVisitados[i] = 0;

    for (int i = 0; i < numeroAeroportos; i++)
        if (!aeroportosVisitados[i])
            dfsNatural(listaAeroportos[i], listaAeroportos, aeroportosVisitados);
}

int segundaDfsKosaraju(Aeroporto *listaAeroportos, int numeroAeroportos)
{
    int aeroportosVisitados[numeroAeroportos];
    for (int i = 0; i < numeroAeroportos; i++)
        aeroportosVisitados[i] = 0;

    int idAeroporto, i = 0;
    while ((idAeroporto = pilha.Desempilha()) != -1)
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
        matriz[i] = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            matriz[i][j] = 0;
    return matriz;
}

void limparEspacoMatriz(int **matriz, int M)
{
    for (int i = 0; i < M; i++)
        free(matriz[i]);
    free(matriz);
}

void ordenaComponentesFortementeConectados(Aeroporto *listaAeroportos, int numeroComponentes)
{
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
    limparEspacoMatriz(matrizComponentes, numeroComponentes);
}

int calculaRotasNecessarias(int numeroComponentes)
{
    int componentesSemEntrada = 0, componentesSemSaida = 0;
    for (int i = 0; i < numeroComponentes; i++)
    {
        if (listaComponentes[i].numeroEntradas == 0)
            componentesSemEntrada++;
        if (listaComponentes[i].numeroSaidas == 0)
            componentesSemSaida++;
    }

    if (componentesSemEntrada > componentesSemSaida)
        return componentesSemEntrada;
    return componentesSemSaida;
}

int main()
{
    int numeroAeroportos, numeroRotas;
    cin >> numeroAeroportos >> numeroRotas;

    Aeroporto listaAeroportos[numeroAeroportos];
    for (int i = 0; i < numeroAeroportos; i++)
        listaAeroportos[i] = Aeroporto(i + 1);

    for (int i = 0; i < numeroRotas; i++)
    {
        int origem, destino;
        cin >> origem >> destino;
        listaAeroportos[origem - 1].AdicionaAeroportoListaDestinos(destino);
        listaAeroportos[destino - 1].AdicionaAeroportoListaOrigens(origem);
    }

    primeiraDfsKosaraju(listaAeroportos, numeroAeroportos);
    int numeroComponentes = segundaDfsKosaraju(listaAeroportos, numeroAeroportos);
    ordenaComponentesFortementeConectados(listaAeroportos, numeroComponentes);
    cout << calculaRotasNecessarias(numeroComponentes) << endl;

    return 0;
}