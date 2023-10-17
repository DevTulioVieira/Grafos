#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <stdio.h>

using namespace std;

typedef struct nolista{
    int id;
    int eixox;
    int eixoy;
    int total;
    struct nolista*prox;
    struct ligaLista *primeiro;
}no;

typedef struct Lista{
    no *inicio;
    no *fim;
}noLista;

typedef struct ligaLista{
    int peso;
    int ponto;
    struct ligaLista *pro;
}liga;

typedef struct LigaLista{
}LLista;

void inicioNo(noLista *lista){
    lista->inicio=NULL;
    lista->fim=NULL;
}

void menu(){
    cout<<"---------------------------"<<endl;
    cout<<"1.Carregar grafo"<<endl;
    cout<<"2.Criar grafo vazio"<<endl;
    cout<<"3.Exibir adjacencia"<<endl;
    cout<<"4.Verificar adjacencia"<<endl;
    cout<<"5.Inserir adjacencia"<<endl;
    cout<<"6.Remover adjacencia"<<endl;
    cout<<"7.Editar vertices"<<endl;
    cout<<"8.Consultar 1 adjacencia"<<endl;
    cout<<"9.Consultar prox adjacencia"<<endl;
    cout<<"10.Consultar todas adjacencia"<<endl;
    cout<<"11.Exporta grafo"<<endl;
    cout<<"12.Sair"<<endl;
    cout<<"---------------------------"<<endl;
}

void carregarGrafo(noLista *lista, int *numero){
    no *novo, *aux, *auxseg,*ordem, *anterior, *verigual;
    liga *teste, *ant, *analisado;
    novo = new no;
    novo->prox = NULL;
    string palavra;
    int i, peso, pri, segundo, total=1,jok,direcionado,troca,repetido=0,valeu=0,ligfalha=0,repligacao=0, igualdade=0;
    ifstream inFile;
    inFile.open("grafo.txt", ios::in);
    if(!inFile){ 
        cout<<"Arquivo grafo.txt nao encontrado"<<endl;
        abort();
    }
    inFile>>palavra;
    if(palavra=="direcionado=nao"){
        direcionado=1;
        troca=1;
    }else{
        direcionado=0;
        troca=0;
    }
    *numero=direcionado;
    inFile>>i>>jok;
    for(total=0;total!=i;total++){    
        inFile>>novo->id>>novo->eixox>>novo->eixoy;
        novo->total=0;
        novo->primeiro = NULL;
        if (lista->inicio == NULL){
            lista->inicio = novo;
            lista->fim = novo;
        }else{
            verigual=lista->inicio;
            while(verigual!=NULL){
                if(verigual->eixox==novo->eixox && verigual->eixoy==novo->eixoy){
                    cout<<"Coordenadas iguais, 2 corpos n ocupam o mesmo espaco!!!!"<<endl;
                    cout<<"ID: "<<verigual->id<<" e ID: "<<novo->id<<" tem as coordenadas informadas igauis!"<<endl;
                    cout<<"Favor alterar a coordenadas futuramente de um dos ponto!"<<endl;
                    igualdade++;
                    break;
                }
                verigual=verigual->prox;
            }
            ordem=lista->inicio;
            anterior=ordem;
            while(ordem!=NULL){
                if(novo->id<ordem->id){
                    if(novo->id==anterior->id){
                        anterior=ordem;
                        ordem=ordem->prox;
                        repetido++;
                        cout<<"ID: "<<novo->id<<" esta duplicado, ingnorando ID igual informado, o primeiro ID cadastrado sera mantido!"<<endl;
                        break;
                    }
                    if(ordem==lista->inicio){
                        novo->prox=ordem;
                        lista->inicio=novo;
                    }else{
                        novo->prox=ordem;
                        anterior->prox=novo;
                    }
                    break;
                }
                if(ordem==lista->fim){
                    if(novo->id==anterior->id){
                        anterior=ordem;
                        ordem=ordem->prox;
                        repetido++;
                        cout<<"ID: "<<novo->id<<" esta duplicado, ingnorando ID igual informado, o primeiro ID cadastrado sera mantido!"<<endl;
                        break;
                    }
                    ordem->prox=novo;
                    novo->prox=NULL;
                    lista->fim=novo;
                }
                anterior=ordem;
                ordem=ordem->prox;
            }
        }
        novo = new no;
        novo->prox = NULL;
        novo->primeiro = NULL;
    }
    total=0;

    while(inFile>>pri>>segundo>>peso){  
        voltouuuu:
        aux=lista->inicio;
        auxseg=lista->inicio;
        valeu=0;
        while(aux!= NULL){
            teste = new liga;
            if(aux->id==pri){
                while(auxseg!= NULL){
                    if(auxseg->id==segundo){
                        valeu=1;
                        break;
                    }
                    auxseg=auxseg->prox;
                }
                if(valeu==0){
                    cout<<"Erro ao fazer ligacao! ID: "<<segundo<<" nao encontrado!"<<endl;
                    troca=0;
                    ligfalha++;
                    break;
                } 
                if(aux->primeiro == NULL){
                    aux->primeiro = teste;
                    teste->pro=NULL;
                    aux->total=1;
                }else{//
                    analisado=aux->primeiro;
                    ant=analisado;
                    while(analisado!=NULL){
                        if(segundo<analisado->ponto){
                            if(segundo==ant->ponto){
                                ant=analisado;
                                analisado=analisado->pro;
                                repligacao++;
                                troca=0;
                                cout<<"A ligacao entre o ID: "<<pri<<" e ID: "<<segundo<<" ja existir, mantendo a primeira inserida!"<<endl;
                                break;
                            }
                            if(analisado==aux->primeiro){
                                teste->pro=analisado;
                                aux->primeiro=teste;
                            }else{
                                teste->pro=analisado;
                                ant->pro=teste;
                            }
                            aux->total+=1;
                            break;
                        }
                        if(analisado->pro==NULL){
                            if(segundo==ant->ponto){
                                ant=analisado;
                                analisado=analisado->pro;
                                repligacao++;
                                troca=0;
                                cout<<"A ligacao entre o ID: "<<pri<<" e ID: "<<segundo<<" ja existir, mantendo a primeira inserida!"<<endl;
                                break;
                            }
                            aux->total+=1;
                            analisado->pro=teste;
                            teste->pro=NULL;
                            break;
                        }
                        ant=analisado;
                        analisado=analisado->pro;
                    }
                ////
                }
                teste->peso=peso;
                teste->ponto=segundo;
            }
            aux = aux->prox;
        }

        if(direcionado==1 && troca==1){//direcionado
            swap(segundo, pri);
            troca=0;
            goto voltouuuu;
        }else{
            troca=1;
        }
            
        if(total==jok) break;
        total++;
    }
    cout<<"\nDados do grafo carregados com suceso!"<<endl<<endl;
    if(repetido>0){
        cout<<"Encontrado "<<repetido<<" Nos iguais, que foram ingnorados! Favor verificar os dados de No importados!"<<endl;
    }
    if(ligfalha>0){
        cout<<"Total: "<<ligfalha<<" encontradas, por ID n encontrado, verifica a existencia do No!"<<endl;
    }
    if(repligacao>0){
        cout<<"Total: "<<repligacao<<" ligacao foram ingnoradas por erro de duplicacao de dados, verifique as ligacoes!"<<endl;
    }
    if(igualdade>0){
        cout<<"Total: "<<igualdade<<" pontos com coordenadas iguais, favor verificar!"<<endl;
    }
}

void mostrarNO(noLista *lista){
    no *aux;
    aux = lista->inicio;
    system("cls");
    if(aux==NULL){
        cout<<"\nNenhum no informado!\n";
    }else{
        cout<<"\t\tNos do grafo"<<endl<<endl;
        while(aux!= NULL){
            cout<<"NO:  "<<aux->id;
            cout<<"   Coordenada("<<aux->eixox<<","<<aux->eixoy<<")"<<endl;
            aux = aux->prox;
        }
    }
}

void exibirAdjacencia(noLista *lista){
    no *aux;
    liga *ajuda;
    aux = lista->inicio;
    system("cls");
    if(aux==NULL){
        cout<<"\nNenhum no informado!\n";
    }else{
        while(aux!= NULL){
            cout<<"NO: "<<aux->id<<endl;
            cout<<"Ajacencia->";
            ajuda=aux->primeiro;
            if(aux->primeiro==NULL){
                cout<<"Nenhuma ligacao para esse No"<<endl;
            }
            while(ajuda!=NULL){
                cout<<ajuda->ponto;
                if(ajuda->pro!=NULL){
                    cout<<"->";
                }
                ajuda=ajuda->pro;
            }
            cout<<endl<<endl;
            aux = aux->prox;
        }
    }
}

void consultarAdjacencia(noLista *lista){
    no *aux;
    liga *ajuda;
    aux = lista->inicio;
    int pri, seg;
    system("cls");
    if(aux==NULL){
        cout<<"\nNenhum no informado!\n";
    }else{
        cout<<"Informe o id do No que deseja verificar: ";
        cin>>pri;
        while(aux!= NULL){
            if(aux->id==pri){
                cout<<"Informe o id do No com o qual sera verificado: ";
                cin>>seg;
                ajuda=aux->primeiro;
                while(ajuda!=NULL){
                    if(ajuda->ponto==seg){
                        cout<<"O No de id: "<<pri<<" e adjacente ao No de id: "<<seg<<" tendo peso: "<<ajuda->peso<<endl;
                        return;
                    }
                    ajuda=ajuda->pro;
                }
                break;
            }
            aux = aux->prox;
        }
        cout<<"Nao foi encontrado esse NO! verifique os dados de todos os NO!"<<endl;
    }
}

void inserirDirecionado(noLista *lista, int pri, int seg, int peso){
    no *aux;
    liga *novo, *analisado, *ant;
    novo = new liga;
    aux = lista->inicio;
    if(aux==NULL){
        cout<<"\nNenhum no informado!\n";
    }else{
        while(aux!= NULL){
            if(aux->id==seg){
                if(aux->primeiro == NULL){
                    aux->primeiro=novo;
                    novo->ponto=pri;
                    novo->peso=peso;
                    novo->pro=NULL;
                    return;
                }
                analisado=aux->primeiro;
                ant=analisado;
                while(analisado!=NULL){
                    if(pri<analisado->ponto){
                        if(analisado==aux->primeiro){
                            novo->pro=analisado;
                            aux->primeiro=novo;
                        }else{
                            novo->pro=analisado;
                            ant->pro=novo;
                        }
                        break;
                    }
                    if(analisado->pro==NULL){
                        analisado->pro=novo;
                        novo->pro=NULL;
                    }
                    ant=analisado;
                    analisado=analisado->pro;
                }
                break;
            }
            aux = aux->prox;
        }
    }
}

void inserirAdjacencia(noLista *lista, int numero){
    no *aux, *segundo;
    liga *ajuda, *novo, *analisado, *ant;
    aux = lista->inicio;

    segundo = aux;
    novo = new liga;
    int pri, seg, peso;
    system("cls");
    if(aux==NULL){
        cout<<"\nNenhum no informado!\n";
    }else{
        cout<<"Informe o id do primeiro No: ";
        cin>>pri;
        while(aux!= NULL){
            if(aux->id==pri){
                ajuda=aux->primeiro;
                cout<<"Informe o id do segundo No: ";
                cin>>seg;
                while(segundo!= NULL){
                    if(segundo->id==seg){
                        cout<<"Informe o peso da ligacao: ";
                        cin>>peso;
                        novo->ponto=seg;
                        novo->peso=peso;
                        if(ajuda == NULL){
                            aux->primeiro=novo;
                            novo->pro=NULL;
                            if(numero==1){
                                inserirDirecionado(&*lista, pri, seg, peso);
                            }
                            cout<<"Ligacao inserida"<<endl;
                            return;
                        }
                        while(ajuda!=NULL){
                            if(ajuda->ponto==seg){
                                cout<<"Conflito de adjacencia, essa ligacao ja exister!"<<endl;
                                return;
                            }
                            ajuda=ajuda->pro;
                        }

                        analisado=aux->primeiro;
                        ant=analisado;
                        while(analisado!=NULL){
                            if(seg<analisado->ponto){
                                if(analisado==aux->primeiro){
                                    novo->pro=analisado;
                                    aux->primeiro=novo;
                                }else{
                                    novo->pro=analisado;
                                    ant->pro=novo;
                                }
                                if(numero==1){
                                    inserirDirecionado(&*lista, pri, seg, peso);
                                }
                                cout<<"Ligacao inserida"<<endl;
                                return;
                            }
                            if(analisado->pro==NULL){
                                analisado->pro=novo;
                                novo->pro=NULL;
                                if(numero==1){
                                    inserirDirecionado(&*lista, pri, seg, peso);
                                }
                                cout<<"Ligacao inserida"<<endl;
                                return;
                            }
                            ant=analisado;
                            analisado=analisado->pro;
                        }                       
                        break;
                    }
                    segundo = segundo->prox;
                }
            }
            aux = aux->prox;
        }
        cout<<"Nao foi posivel localizar esse No, verifique a existencia do mesmo!"<<endl;
    }
}

void criarGrafovazio(noLista *lista, int *numero){
    no *novo, *ordem, *anterior, *verigual;
    novo = new no;
    novo->prox = NULL; 

    int i, total, repetido=0;
    cout<<"Informe o total de NO: ";
    cin>>total;
    cout<<"Digite 1 para o grafo ser direcionado ou 0 unidirecionado: "; 
    cin>>*numero;
    for(i=0; i<total;i++){
        cout<<"Informe o ID do NO: ";
        cin>>novo->id;
        cout<<"Informe a coordenado do NO, primeiro o x: ";
        cin>>novo->eixox;
        cout<<"Eixo y: ";
        cin>>novo->eixoy;
        novo->primeiro=NULL;
        if (lista->inicio == NULL){
            lista->inicio = novo;
            lista->fim = novo;
            novo->prox=NULL;
        }else{
            vigual:
            verigual=lista->inicio;
            while(verigual!=NULL){
                if(verigual->eixox==novo->eixox && verigual->eixoy==novo->eixoy){
                    cout<<"Coordenadas ja existente, 2 corpos n ocupam o mesmo lugar!!!"<<endl;
                    cout<<"Favor inserir coordenadas validas!"<<endl;
                    cout<<"Informe a coordenado do NO, primeiro o x: ";
                    cin>>novo->eixox;
                    cout<<"Eixo y: ";
                    cin>>novo->eixoy;
                    goto vigual;
                }
                verigual=verigual->prox;
            }
            ordem=lista->inicio;
            anterior=ordem;
            while(ordem!=NULL){
                if(novo->id<ordem->id){
                    if(novo->id==anterior->id){
                        anterior=ordem;
                        ordem=ordem->prox;
                        repetido++;
                        cout<<"ID: "<<novo->id<<" esta duplicado, ingnorando ID igual informado, o primeiro ID cadastrado sera mantido!"<<endl;
                        break;
                    }
                    if(ordem==lista->inicio){
                        novo->prox=ordem;
                        lista->inicio=novo;
                    }else{
                        novo->prox=ordem;
                        anterior->prox=novo;
                    }
                    break;
                }
                if(ordem==lista->fim){
                    if(novo->id==anterior->id){
                        anterior=ordem;
                        ordem=ordem->prox;
                        repetido++;
                        cout<<"ID: "<<novo->id<<" esta duplicado, ingnorando ID igual informado, o primeiro ID cadastrado sera mantido!"<<endl;
                        break;
                    }
                    ordem->prox=novo;
                    novo->prox=NULL;
                    lista->fim=novo;
                }
                anterior=ordem;
                ordem=ordem->prox;
            }
        }
        novo = new no;
        novo->prox = NULL;
        novo->primeiro = NULL;
    }
    cout<<"Nos inseridos com sucesso!"<<endl;
    
}

void removerAdjacenciaDirecionada(noLista *lista, int pri, int seg){
    no *aux;
    liga *anterior, *atual;
    aux=lista->inicio;
    swap(pri, seg);

    if(aux==NULL){
        cout<<"Nenhum ponto inserido!"<<endl;
    }else{
        while(aux!=NULL){
            if(aux->id==pri){
                atual=aux->primeiro;
                anterior=atual;
                while(atual!=NULL){
                    if(atual->ponto==seg){
                        if(atual==aux->primeiro){
                            aux->primeiro=atual->pro;
                            free(atual);
                            return;
                        }else{
                            if(atual->pro==NULL){
                                anterior->pro=NULL;
                            }
                            anterior->pro=atual->pro;
                            free(atual);
                            return;
                        }
                    }
                    anterior=atual;
                    atual=atual->pro;
                }
                cout<<"Nao foi possivel encontra o ID informado!"<<endl;
            }
            aux= aux->prox;
        }
        cout<<"Nao foi possivel encontra o ID informado!"<<endl;
    }

}

void removerAdjacencia(noLista *lista, int numero){
    no *aux;
    liga *anterior, *atual;

    aux=lista->inicio;
    int pri, seg;

    if(aux==NULL){
        cout<<"Nenhum ponto inserido!"<<endl;
    }else{
        cout<<"Informe o ID do primeiro no: ";
        cin>>pri;
        while(aux!=NULL){
            if(aux->id==pri){
                cout<<"Informe o ID do segundo no: ";
                cin>>seg;
                atual=aux->primeiro;
                anterior=atual;
                while(atual!=NULL){
                    if(atual->ponto==seg){
                        if(atual==aux->primeiro){
                            aux->primeiro=atual->pro;
                            free(atual);
                            if(numero==1){
                                removerAdjacenciaDirecionada(&*lista, pri, seg);
                            }
                            cout<<"Removido com sucesso!"<<endl;
                            return;
                        }else{
                            if(atual->pro==NULL){
                                anterior->pro=NULL;
                            }
                            anterior->pro=atual->pro;
                            cout<<"Removido com sucesso!"<<endl;
                            free(atual);
                            return;
                        }
                    }
                    anterior=atual;
                    atual=atual->pro;
                }
                cout<<"Nao foi possivel encontra o ID informado!"<<endl;
            }
            aux= aux->prox;
        }
        cout<<"Nao foi possivel encontra o ID informado!"<<endl;
    }
}

void alterarVertices(noLista *lista){
    no *aux, *ajuda;

    aux=lista->inicio;
    int id, x, y;

    if(aux==NULL){
        cout<<"Nenhum no cadastrado!"<<endl;
    }else{
        cout<<"Insira o ID que deseja altera o vertice!"<<endl;
        cin>>id;
        while(aux!=NULL){
            if(aux->id==id){
                voltoucoordenadas:
                cout<<"Insira as coordenadas: valor do X: ";
                cin>>x;
                cout<<"Insira o valor de Y: ";
                cin>>y;
                ajuda=lista->inicio;
                while(ajuda!=NULL){
                    if(ajuda->eixox==x && ajuda->eixoy==y){
                        cout<<"Coordenadas ja existente, favor inserir coordenadas validas!"<<endl;
                        goto voltoucoordenadas;
                    }
                    ajuda=ajuda->prox;
                }
                aux->eixox=x;
                aux->eixoy=y;
                cout<<"Coordenadas alteradas com sucesso!"<<endl;
                return;
            }
            aux=aux->prox;
        }
    }
}

void consultarPrimeiro(noLista *lista){
    no *aux;

    aux=lista->inicio;
    int id;

    if(aux==NULL){
        cout<<"Nenhum no cadastrado!"<<endl;
    }else{
        cout<<"Insira o ID que deseja verificar a adjacencia!"<<endl;
        cin>>id;
        while(aux!=NULL){
            if(aux->id==id){
                cout<<"ID: "<<aux->id<<" tem como primeiro adjacencia: "<<aux->primeiro->ponto<<" com peso: "<<aux->primeiro->peso<<endl;
                return;
            }
            aux=aux->prox;
        }
    }
}

void consultarAdjacendiaAdjacendia(noLista *lista){
    no *aux;
    liga *ajuda;
    aux=lista->inicio;
    int id, local;

    if(aux==NULL){
        cout<<"Nenhum no cadastrado!"<<endl;
    }else{
        cout<<"Insira o ID que deseja verificar a adjacencia!"<<endl;
        cin>>id;
        while(aux!=NULL){
            if(aux->id==id){
                cout<<"Insira o adjacencente para verificar proximo: ";
                cin>>local;
                ajuda=aux->primeiro;
                while(ajuda!=NULL){
                    if(ajuda->ponto==local){
                        if(ajuda->pro==NULL){
                            cout<<"Esse adjacencia nao tem conexao, sendo o ultimo"<<endl;
                            return;
                        }
                        cout<<"O proximo adjacente e: "<<ajuda->pro->ponto<<" com peso: "<<ajuda->pro->peso<<endl;
                    }
                    ajuda=ajuda->pro;
                }
                return;
            }
            aux=aux->prox;
        }
        cout<<"ID nao localizado!"<<endl;
    }
}

void exportarGrafo(noLista *lista, int numero){
    no *aux;
    liga *ajuda;

    aux=lista->inicio;

    int noid=0, aresta=0;

    while(aux!=NULL){
        noid++;
        aresta+=aux->total;
        aux=aux->prox;
    }

    ofstream outFile;
    outFile.open("salvar.txt", ios::out); // abre o arquivo para escrita
    if (!outFile){ 
        cout<<"Arquivo saida.txt nao pode ser aberto"<<endl;
        abort();
    }

    if(numero==1){
        aresta=aresta/2;
        outFile<<"direcionado=nao"<<endl;
    }else{
        outFile<<"direcionado=nao"<<endl;
    }

    outFile<<noid<<" "<<aresta<<endl;

    aux=lista->inicio;
    if(aux==NULL){
        cout<<"Nenhum dado a salvar!"<<endl;
    }else{
        while(aux!= NULL){
            outFile<<aux->id<<" "<<aux->eixox<<" "<<aux->eixoy<<endl;
            aux = aux->prox;
        }
    }

    aux=lista->inicio;
    if(aux==NULL){
        cout<<"Nenhum dado a salvar!"<<endl;
    }else{
        while(aux!= NULL){
            ajuda=aux->primeiro;
            while(ajuda!=NULL){
                if(numero==1 && ajuda->ponto<aux->id){
                }else{
                    outFile<<aux->id<<" "<<ajuda->ponto<<" "<<ajuda->peso<<endl;
                }
                ajuda=ajuda->pro;
            }
            aux = aux->prox;
        }
    }
 
    outFile.close();
}

int main(){
    int opcao, direcionado;
    
    noLista L1;

    inicioNo(&L1);

    for(;;){
        menu();
        cin>>opcao;
        system("cls");
        switch(opcao){
            case 1:
                carregarGrafo(&L1, &direcionado);
            break;

            case 2:
                criarGrafovazio(&L1, &direcionado);
            break;
                
            case 3:
                exibirAdjacencia(&L1);
            break;
                
            case 4:
                consultarAdjacencia(&L1);
            break;

            case 5:
                inserirAdjacencia(&L1, direcionado);
            break;

            case 6:
                removerAdjacencia(&L1, direcionado);
            break;

            case 7:
                alterarVertices(&L1);
            break;

            case 8:
                consultarPrimeiro(&L1);
            break;
            
            case 9:
                consultarAdjacendiaAdjacendia(&L1);
            break;

            case 10:
                mostrarNO(&L1);
            break;

            case 11:
                exportarGrafo(&L1, direcionado);
            break;

            case 12:
                exit(0);
            break;

            default:
            break;
        }
    }
    return 0;
}