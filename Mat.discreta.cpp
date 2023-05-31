#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <stdio.h>

using namespace std;

// Informacoes de cada ponto
typedef struct matrizlista
{
    int ponto;   // numero do ponto
    int energia; // 1 para se reservatorio 0 para somente ponto normal
    int analisado;
    string nome; // nome para indentifica melho o ponto
    struct matrizlista *prox;
    struct matrizlista *liga;
} matriz;

typedef struct lista
{
    matriz *inicio;
    matriz *fim;
} matrizL;
// inicia a lista dos pontos
void iniciomatriz(matrizL *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

void menu()
{
    cout << "===========================================" << endl;
    cout << "=1.Calcular linhas cortadas para apagao   =" << endl;
    cout << "=2.Mostra matriz                          =" << endl;
    cout << "=3.Mostra Pontos de energia               =" << endl;
    cout << "=4.Mostra os dados                        =" << endl;
    cout << "=5.Mostra ligacao de cada ponto           =" << endl;
    cout << "=6.Ponto fica sem energia                 =" << endl;
    cout << "=7.Alterar informacao do ponto            =" << endl;
    cout << "=8.Alterar ligacoes do ponto              =" << endl;
    cout << "=9.Sair                                   =" << endl;
    cout << "===========================================" << endl;
}
// nessa funcao estou induzindo os ponto que existem puxando seus dados de pontos.txt edeixando eles
// em uma lista encadeada para que estejam conectados e possam se removidos ou alterado
void carregarpontos(matrizL *lista, int *tam)
{
    matriz *novo;
    novo = new matriz;
    novo->prox = NULL;

    ifstream inFile;
    inFile.open("pontos.txt", ios::in);
    if (!inFile)
    {
        cout << "Arquivo pontos.txt nao pode ser aberto" << endl;
        abort();
    }
    *tam = 0;
    while (inFile >> novo->ponto >> novo->energia >> novo->nome)
    {
        novo->analisado = 0;
        if (lista->inicio == NULL)
        {
            lista->inicio = novo;
            lista->fim = novo;
        }
        else
        {
            lista->fim->prox = novo;
            lista->fim = novo;
        }
        novo = new matriz;
        novo->prox = NULL;
        *tam = *tam + 1;
    }
}
// mostra as informacao de cada ponto
void mostraTotal(matrizL *lista)
{
    matriz *aux;
    aux = lista->inicio;

    if (aux == NULL)
    {
        cout << "ERRO!" << endl;
    }
    else
    {
        while (aux != NULL)
        {
            cout << "Ponto:      " << aux->ponto << endl;
            cout << "energia:    " << aux->energia << endl;
            cout << "nome:       " << aux->nome << endl
                 << endl;
            aux = aux->prox;
        }
    }
}
// mostra todos os pontos
void mostraEnergia(matrizL *lista)
{
    matriz *aux;
    aux = lista->inicio;

    if (aux == NULL)
    {
        cout << "ERRO!" << endl;
    }
    else
    {
        while (aux != NULL)
        {
            if (aux->energia == 1)
            {
                cout << "Ponto:      " << aux->ponto << endl;
                cout << "nome:       " << aux->nome << endl
                     << endl;
            }
            aux = aux->prox;
        }
    }
}
// mostra matriz completa dos garfos
void mostraLiga(int vet[], int tam)
{
    vet[tam];
    for (int i = 0; i < tam; i++)
    {
        cout << vet[i] << " ";
    }
    cout << "\n";
}
// conta os as linhas para corte
void contador(int *numero, int vet[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (vet[i] == 1)
        {
            *numero = *numero + 1;
        }
    }
}
// ver onde é reservatorio e corta as linhas
void cortalinha(matrizL *lista, int vet[], int tam)
{
    matriz *aux;
    aux = lista->inicio;

    int x = 0, numero = 0;

    if (aux == NULL)
    {
        cout << "ERRO!" << endl;
    }
    else
    {
        while (aux != NULL)
        {
            if (aux->energia == 1)
            {
                contador(&numero, &vet[x], tam);
            }
            aux = aux->prox;
            x++;
        }
    }
    cout << "Sera preciso corta: " << numero << " linhas para ter um apagao" << endl;
}
// mostra qual ponto liga com qual ponto
void contaPonto(int vet[], int tam)
{
    vet[tam];
    for (int i = 0; i < tam; i++)
    {
        if (vet[i] == 1)
        {
            cout << (i + 1) << " ";
        }
    }
    cout << "\n";
}
// altera os dados dos pontos informados
void alteraPonto(matrizL *lista)
{
    matriz *aux;
    aux = lista->inicio;

    int x, opcao;

    if (aux == NULL)
    {
        cout << "Nenhum dado para se alterado!" << endl;
    }
    else
    {
        cout << "Informe o numero do ponto que deseja altera: ";
        cin >> x;
        while (aux != NULL)
        {
            if (aux->ponto == x)
            {
                cout << "Ponto:        " << aux->ponto << endl;
                cout << "nome:         " << aux->nome << endl;
                cout << "Reservatorio: " << aux->energia << " 0=ponto de controle, 1=reservatorio" << endl
                     << endl;
                cout << "Deseja muda o nome: (1.sim/2.nao) ";
                cin >> opcao;
                if (opcao == 1)
                {
                    cout << "Digite um novo nome: ";
                    cin >> aux->nome;
                    opcao = 0;
                    cout << "Suceso!" << endl;
                }
                cout << "Deseja altera para reservatorio ou deixa de se reservatorio: (1.sim/2.nao) ";
                cin >> opcao;
                if (opcao == 1)
                {
                    if (aux->energia == 1)
                    {
                        aux->energia = 0;
                    }
                    else
                    {
                        aux->energia = 1;
                    }
                    cout << "Suceso!" << endl;
                }
            }
            aux = aux->prox;
        }
        cout << "Salvando dados novos...!" << endl;
    }
}
// altera as ligação dos pontos
void alteraliga(int vet[], int tam)
{
    vet[tam];
    int opcao, ajuda, x;
    cout << "Pontos que esta conectado: ";
    for (int i = 0; i < tam; i++)
    {
        if (vet[i] == 1)
        {
            cout << (i + 1) << " ";
        }
    }
    cout << "\n Deseja adciona um nova ligacao: (1.sim/2.nao) ";
    cin >> opcao;
    if (opcao == 1)
    {
        cout << "Liga com qual ponto: ";
        cin >> ajuda;
        for (int i = 0; i < tam; i++)
        {
            if (i == ajuda && vet[i] == 0)
            {
                vet[i] = 1;
                cout << "sucesso!" << endl;
            }
            else
            {
                cout << "Ja existir essa ligacao" << endl;
            }
        }
        return;
    }
    opcao = 0;
    cout << "\n Deseja remover um nova ligacao: (1.sim/2.nao) ";
    cin >> opcao;
    if (opcao == 1)
    {
        cout << "remover qual ponto: ";
        cin >> ajuda;
        for (int i = 0; i < tam; i++)
        {
            if (i == ajuda && vet[i] == 1)
            {
                vet[i] = 0;
                cout << "sucesso!" << endl;
            }
        }
    }
}
// ponto fica sem energia
void pontosemeneria(int vet[], int tam)
{
    vet[tam];
    int x = 0;
    for (int i = 0; i < tam; i++)
    {
        if (vet[i] == 1)
        {
            x += 1;
        }
    }
    cout << "Tem que corta " << x << " pontos para fica sem energia" << endl;
}

int main()
{
    int opcao, tamanho = 0, i, ajuda;

    matrizL M1;

    iniciomatriz(&M1);

    carregarpontos(&M1, &tamanho);

    int mat[tamanho][tamanho];
    // |1 2 3 4 5 6
    // 1|0 1 0 0 1 0
    // 2|1 0 1 0 1 0
    // 3|0 1 0 1 0 0
    // 4|0 1 1 0 1 1
    // 5|1 1 0 1 0 0
    // 6|0 0 0 1 0 0
    //     1           2            3           4             5            6            7           8           9           10          11          12          13          14          15          16          17              18              19              20          21          22          23          24          25          26          27          28             29             30            31          32          33            34            35          36          37           38           39            40          41            42            43          44          45            46            47
    mat[0][0] = 0;
    mat[0][1] = 1;
    mat[0][2] = 0;
    mat[0][3] = 0;
    mat[0][4] = 1;
    mat[0][5] = 0;
    mat[0][6] = 0;
    mat[0][7] = 0;
    mat[0][8] = 0;
    mat[0][9] = 0;
    mat[0][10] = 0;
    mat[0][11] = 0;
    mat[0][12] = 0;
    mat[0][13] = 0;
    mat[0][14] = 0;
    mat[0][15] = 0;
    mat[0][16] = 0;
    mat[0][17] = 0;
    mat[0][18] = 0;
    mat[0][19] = 0;
    mat[0][20] = 0;
    mat[0][21] = 0;
    mat[0][22] = 0;
    mat[0][23] = 0;
    mat[0][24] = 0;
    mat[0][25] = 0;
    mat[0][26] = 0;
    mat[0][27] = 0;
    mat[0][28] = 0;
    mat[0][29] = 0;
    mat[0][30] = 0;
    mat[0][31] = 0;
    mat[0][32] = 0;
    mat[0][33] = 0;
    mat[0][34] = 0;
    mat[0][35] = 0;
    mat[0][36] = 0;
    mat[0][37] = 0;
    mat[0][38] = 0;
    mat[0][39] = 0;
    mat[0][40] = 0;
    mat[0][41] = 0;
    mat[0][42] = 0;
    mat[0][43] = 0;
    mat[0][44] = 0;
    mat[0][45] = 0;
    mat[0][46] = 0;
    mat[1][0] = 1;
    mat[1][1] = 0;
    mat[1][2] = 1;
    mat[1][3] = 0;
    mat[1][4] = 1;
    mat[1][5] = 0;
    mat[1][6] = 0;
    mat[1][7] = 0;
    mat[1][8] = 0;
    mat[1][9] = 0;
    mat[1][10] = 0;
    mat[1][11] = 0;
    mat[1][12] = 0;
    mat[1][13] = 0;
    mat[1][14] = 0;
    mat[1][15] = 0;
    mat[1][16] = 0;
    mat[1][17] = 0;
    mat[1][18] = 0;
    mat[1][19] = 0;
    mat[1][20] = 0;
    mat[1][21] = 0;
    mat[1][22] = 0;
    mat[1][23] = 0;
    mat[1][24] = 0;
    mat[1][25] = 0;
    mat[1][26] = 0;
    mat[1][27] = 0;
    mat[1][28] = 0;
    mat[1][29] = 0;
    mat[1][30] = 0;
    mat[1][31] = 0;
    mat[1][32] = 0;
    mat[1][33] = 0;
    mat[1][34] = 0;
    mat[1][35] = 0;
    mat[1][36] = 0;
    mat[1][37] = 0;
    mat[1][38] = 0;
    mat[1][39] = 0;
    mat[1][40] = 0;
    mat[1][41] = 0;
    mat[1][42] = 0;
    mat[1][43] = 0;
    mat[1][44] = 0;
    mat[1][45] = 0;
    mat[1][46] = 0;
    mat[2][0] = 0;
    mat[2][1] = 1;
    mat[2][2] = 0;
    mat[2][3] = 1;
    mat[2][4] = 0;
    mat[2][5] = 0;
    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 1;
    mat[3][3] = 0;
    mat[3][4] = 1;
    mat[3][5] = 1;
    mat[4][0] = 1;
    mat[4][1] = 1;
    mat[4][2] = 0;
    mat[4][3] = 1;
    mat[4][4] = 0;
    mat[4][5] = 0;
    mat[5][0] = 0;
    mat[5][1] = 0;
    mat[5][2] = 0;
    mat[5][3] = 1;
    mat[5][4] = 0;
    mat[5][5] = 0;

    for (;;)
    {
        system("cls");
        menu();
        cin >> opcao;
        system("cls");
        switch (opcao)
        {
        case 1:
            cortalinha(&M1, mat[0], tamanho);
            system("pause");
            break;
        case 2:
            cout << "         ";
            for (i = 0; i < tamanho; i++)
            {
                cout << (i + 1) << " ";
            }
            cout << endl;
            for (i = 0; i < tamanho; i++)
            {
                cout << "Ponto " << (i + 1) << "| ";
                mostraLiga(mat[i], tamanho);
            }
            system("pause");
            break;
        case 3:
            mostraEnergia(&M1);
            system("pause");
            break;
        case 4:
            mostraTotal(&M1);
            system("pause");
            break;
        case 5:
            cout << "         Pontos conectados" << endl;
            for (i = 0; i < tamanho; i++)
            {
                cout << "Ponto " << (i + 1) << "| ";
                contaPonto(mat[i], tamanho);
            }
            system("pause");
            break;
        case 6:
            cout << "Qual ponto deseja verificar: ";
            cin >> ajuda;
            pontosemeneria(mat[ajuda], tamanho);
            system("pause");
            break;
        case 7:
            mostraTotal(&M1);
            alteraPonto(&M1);
            system("pause");
            break;
        case 8:
            mostraTotal(&M1);
            cout << "Qual ponto deseja altera: ";
            cin >> ajuda;
            alteraliga(mat[ajuda], tamanho);
            system("pause");
            break;
        case 9:
            exit(0);
            break;
        }
    }
}