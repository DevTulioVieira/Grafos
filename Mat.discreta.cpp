#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <stdio.h>

using namespace std;
const int cols = 3;
//Informacoes de cada ponto
typedef struct matrizlista{
    int ponto;//numero do ponto
    int energia;//1 para se reservatorio 0 para somente ponto normal
    int analisado;
    string nome;//nome para indentifica melho o ponto
    struct matrizlista*prox;
    struct matrizlista*liga;
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
    cout<<"=2.Mostra pontos e suas ligacao         ="<<endl;
    cout<<"=3.Mostra Pontos de energia             ="<<endl;
    cout<<"=4.Mostra os dados                      ="<<endl;
    cout<<"=5.Sair                                 ="<<endl;
    cout<<"========================================="<<endl;
}
//nessa funcao estou induzindo os ponto que existem puxando seus dados de pontos.txt edeixando eles
//em uma lista encadeada para que estejam conectados e possam se removidos ou alterado
void carregarpontos(matrizL *lista, int *tam){
    matriz *novo;
    novo = new matriz;
    novo->prox=NULL;

    ifstream inFile;
    inFile.open("pontos.txt", ios::in);
    if (!inFile){ 
        cout<<"Arquivo pontos.txt nao pode ser aberto"<<endl;
        abort();
    }
    *tam=0;
    while(inFile>>novo->ponto>>novo->energia>>novo->nome){
        novo->analisado=0;
        if (lista->inicio == NULL){
            lista->inicio = novo;
            lista->fim = novo;
        }else{
            lista->fim->prox=novo;
            lista->fim=novo;
        }
        novo = new matriz;
        novo->prox = NULL;
        *tam=*tam+1;
    }
}
//mostra as informacao de cada ponto
void mostraTotal(matrizL *lista){
    matriz *aux;
    aux=lista->inicio;

    if(aux==NULL){
        cout<<"ERRO!"<<endl;
    }else{
        while(aux!=NULL){
            cout<<"Ponto:      "<<aux->ponto<<endl;
            cout<<"energia:    "<<aux->energia<<endl;
            cout<<"nome:       "<<aux->nome<<endl<<endl;
            aux=aux->prox;
        }
    }
}

void mostraEnergia(matrizL *lista){
    matriz *aux;
    aux=lista->inicio;

    if(aux==NULL){
        cout<<"ERRO!"<<endl;
    }else{
        while(aux!=NULL){
            if(aux->energia==1){
                cout<<"Ponto:      "<<aux->ponto<<endl;
                cout<<"nome:       "<<aux->nome<<endl<<endl;
            }
            aux=aux->prox;
        }
    }
}

void mostraLiga(matrizL *lista, int vet[3]){
    int i;
    for(i=0; i<3; i++){
        if(i==0){
            vet[i]=3;
        }
        cout<<vet[i];
    }
    cout<<"\n";
}

int main(){
    int opcao, tamanho=0, i, j;

    matrizL M1;

    iniciomatriz(&M1);

    carregarpontos(&M1, &tamanho);
    tamanho=3;
    int mat[tamanho][tamanho];

    mat[0][0]=0;
    mat[0][1]=0;
    mat[0][2]=0;
    mat[1][0]=1;
    mat[1][1]=1;
    mat[1][2]=1;
    mat[2][0]=0;
    mat[2][1]=0;
    mat[2][2]=0;


    for(;;){
        system("cls");
        menu();
        cin>>opcao;
        system("cls");
        switch(opcao){
            case 1:

            break;
            case 2:
                for(i=0; i<tamanho; i++){
                    mostraLiga(&M1, mat[i]);
                }
                system("pause");
                cout<<mat[0][0];
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
                exit(0);
            break;
        }
    }
}