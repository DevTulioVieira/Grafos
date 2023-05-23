#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <stdio.h>

using namespace std;

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
    cout<<"==========================================="<<endl;
    cout<<"=1.Calcular linhas cortadas para apagao   ="<<endl;
    cout<<"=2.Mostra matriz                          ="<<endl;
    cout<<"=3.Mostra Pontos de energia               ="<<endl;
    cout<<"=4.Mostra os dados                        ="<<endl;
    cout<<"=5.Mostra ligacao de cada ponto           ="<<endl;
    cout<<"=6.Ponto fica energia                     ="<<endl;
    cout<<"=7.Sair                                   ="<<endl;
    cout<<"==========================================="<<endl;
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

void mostraLiga(int vet[], int tam){
    vet[tam];
    for(int i=0; i<tam; i++){
       cout<<vet[i]<<" ";  
    }
    cout<<"\n";
}

void contador(int *numero, int vet[], int tamanho){
    for(int i=0; i<tamanho; i++){
        if(vet[i]==1){
            *numero=*numero+1;
        }
    }
}

void cortalinha(matrizL *lista, int vet[], int tam){
    matriz *aux;
    aux=lista->inicio;

    int x=0, numero=0;

    if(aux==NULL){
        cout<<"ERRO!"<<endl;
    }else{
        while(aux!=NULL){
            if(aux->energia==1){
                contador(&numero, &vet[x], tam);
            }
            aux=aux->prox;
            x++;
        }
    }
    cout<<"Sera preciso corta: "<<numero<<" linhas para ter um apagao"<<endl;
}

void contaPonto(int vet[], int tam){
    vet[tam];
    for(int i=0; i<tam; i++){
        if(vet[i]==1){
            cout<<(i+1)<<" ";
        }
    }
    cout<<"\n";
}

int main(){
    int opcao, tamanho=0, i, j;

    matrizL M1;

    iniciomatriz(&M1);

    carregarpontos(&M1, &tamanho);

    int mat[tamanho][tamanho];
    // |1 2 3 4 5 6
    //1|0 1 0 0 1 0
    //2|1 0 1 0 1 0
    //3|0 1 0 1 0 0
    //4|0 1 1 0 1 1
    //5|1 1 0 1 0 0
    //6|0 0 0 1 0 0
    //     1           2            3           4             5            6
    mat[0][0]=0; mat[0][1]=1; mat[0][2]=0; mat[0][3]=0; mat[0][4]=1; mat[0][5]=0;
    mat[1][0]=1; mat[1][1]=0; mat[1][2]=1; mat[1][3]=0; mat[1][4]=1; mat[1][5]=0;
    mat[2][0]=0; mat[2][1]=1; mat[2][2]=0; mat[2][3]=1; mat[2][4]=0; mat[2][5]=0;
    mat[3][0]=0; mat[3][1]=0; mat[3][2]=1; mat[3][3]=0; mat[3][4]=1; mat[3][5]=1;
    mat[4][0]=1; mat[4][1]=1; mat[4][2]=0; mat[4][3]=1; mat[4][4]=0; mat[4][5]=0;
    mat[5][0]=0; mat[5][1]=0; mat[5][2]=0; mat[5][3]=1; mat[5][4]=0; mat[5][5]=0;


    for(;;){
        system("cls");
        menu();
        cin>>opcao;
        system("cls");
        switch(opcao){
            case 1:
                cortalinha(&M1, mat[0], tamanho);
                system("pause");
            break;
            case 2:
                cout<<"         ";
                for(i=0; i<tamanho; i++){
                    cout<<(i+1)<<" ";
                }
                cout<<endl;
                for(i=0; i<tamanho; i++){
                    cout<<"Ponto "<<(i+1)<<"| ";
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
                cout<<"         Pontos conectados"<<endl;
                for(i=0; i<tamanho; i++){
                    cout<<"Ponto "<<(i+1)<<"| ";
                    contaPonto(mat[i], tamanho);
                }
                system("pause");
            break;
            case 6:
                 
            break;
            case 7:
                exit(0);
            break;
        }
    }
}