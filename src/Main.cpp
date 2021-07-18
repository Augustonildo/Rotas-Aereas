#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int numeroAeroportos, numeroRotas;
    cin >> numeroAeroportos >> numeroRotas;

    int** matrizRotas = (int**) malloc(numeroAeroportos * sizeof(int));
    for(int i = 0; i < numeroAeroportos; i++){
        matrizRotas[i] = (int*) malloc(numeroAeroportos * sizeof(int));
    }

    for (int i = 0; i < numeroRotas; i++)
    {
        for(int j = 0; j < numeroRotas; j++){
            matrizRotas[i][j] = 0;
        }   
    }

    for (int i = 0; i < numeroRotas; i++)
    {
        int origem, destino;
        cin >> origem >> destino;
        matrizRotas[origem-1][destino-1] = 1;
    }

   return 0;
}