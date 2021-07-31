#define MAX_AEROPORTOS 1000

class Componente
{
public:
    int numeroAeroportos;
    int numeroSaidas;
    int numeroEntradas;
    int listaAeroportos[MAX_AEROPORTOS];
    Componente();
    void AdicionaAeroporto(int id);
};