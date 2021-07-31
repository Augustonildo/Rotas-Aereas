#define MAX_AEROPORTOS 1000

class Aeroporto
{
public:
    int id;
    int numeroOrigens;
    int numeroDestinos;
    int listaOrigens[MAX_AEROPORTOS];
    int listaDestinos[MAX_AEROPORTOS];
    Aeroporto();
    Aeroporto(int id);
    bool PertenceListaDestinos(int idDestino);
    void AdicionaAeroportoListaDestinos(int id);
    void AdicionaAeroportoListaOrigens(int id);
};