#define MAX_AEROPORTOS 1000

class Pilha
{
public:
    int topo;
    Pilha();
    void Empilha(int i);
    int Desempilha();

private:
    int itens[MAX_AEROPORTOS];
};