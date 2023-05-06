#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>

using namespace std;
//Informacoes de cada ponto
typedef struct matrizlista{
    int ponto;//numero do ponto
    int verificado;//1 para se reservatorio 0 para somente ponto normal
    string nome;//nome para indentifica melho o ponto
    struct matrizlista*prox;
}matriz;

typedef struct lista{
    matriz *inicio;
    matriz *fim;
}matrizL;
//inicia a lista dos pontos
void iniciomatriz(matrizL *lista){
    lista->inicio=NULL;
    lista->fim=NULL;
}


void menu(){
    cout<<"========================================="<<endl;
    cout<<"=1.Calcular linhas cortadas para apagao ="<<endl;
    cout<<"=4.Mostra os dados                      ="<<endl;
    cout<<"=5.Sair                                 ="<<endl;
    cout<<"========================================="<<endl;
}
//nessa funcao estou induzindo os ponto que existem puxando seus dados de pontos.txt edeixando eles
//em uma lista encadeada para que estejam conectados e possam se removidos ou alterado
void carregarpontos(matrizL *lista){
    matriz *novo;
    novo = new matriz;
    novo->prox=NULL;

    ifstream inFile;
    inFile.open("pontos.txt", ios::in);
    if (!inFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }

    while(inFile>>novo->ponto>>novo->verificado>>novo->nome){
        if (lista->inicio == NULL){
            lista->inicio = novo;
            lista->fim = novo;
        }else{
            lista->fim->prox=novo;
            lista->fim=novo;
        }
        novo = new matriz;
        novo->prox = NULL;
    }
}
//mostra as informacao de cada ponto
void mostra(matrizL *lista){
    matriz *aux;
    aux=lista->inicio;

    if(aux==NULL){
        cout<<"ERRO!"<<endl;
    }else{
        while(aux!=NULL){
            cout<<"numero:     "<<aux->ponto<<endl;
            cout<<"verificado: "<<aux->verificado<<endl;
            cout<<"nome:       "<<aux->nome<<endl<<endl;
            aux=aux->prox;
        }
    }
}

void carregardados(matrizL *lista){
    matriz *novo;
    novo = new matriz;
    novo->prox=NULL;

    ifstream inFile;
    inFile.open("dados.txt", ios::in);
    if (!inFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }

    while(inFile>>novo->ponto>>novo->verificado>>novo->nome){
        
        novo = new matriz;
        novo->prox = NULL;
    }
}

int main(){
    int opcao;

    matrizL M1;

    iniciomatriz(&M1);

    carregarpontos(&M1);

    for(;;){
        menu();
        cin>>opcao;
        switch(opcao){
            case 1:

            break;

            case 4:
                mostra(&M1);
                system("pause");
                system("cls");
            break;

            case 5:
                exit(0);
            break;
        }
    }
}