/*
    *
    * Projeto: Projeto Agenda Eletrônica
    * Autor: Alfredo Henrique [AlfredoHAC]
    * Data: 05/11/2016
    * Versão: 1.1
    * Data da última Modificação: 19/11/2016
    *
*/

//=====Bibliotecas======//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
#endif // WIN32



//=====Declaração de constantes=====//

//=====Declaração de estruturas (registros)=====//

//Estrutura de contato
typedef struct{
    int id;
    char nome[30];
    char email[30];
    char telefone[15];
}Contato;

//Estrutura dos itens da lista
typedef struct item{
    Contato contato;
    struct item *prox;
    struct item *ant;
}Item;

//Estrutura da lista de contatos
typedef struct{
    Item *inicio;
    Item *fim;
    int qtdContatos;
}Lista_contatos;

//=====Declaração de identidades de funções=====//

//Funções de inicialização e finalização
void iniciaLista(Lista_contatos *agenda);
void esvaziaLista(Lista_contatos *agenda);

//Funções de inserção, modificação e remoção
int inserirItem(Lista_contatos *agenda, Contato novoContato);
int removerItem(Lista_contatos *agenda, int id);
int modificarItem(Lista_contatos *agenda, int id);

//Funções de busca
int buscarItemNome(Lista_contatos *agenda, char *nome);
Item* buscarItemID(Lista_contatos *agenda, int id);

//Funções de exibição
void mostraItem(Lista_contatos *agenda, Item *endItem);
void mostraLista(Lista_contatos *agenda);

//Funções de gravação em arquivo e preenchimento
void carregaLista(Lista_contatos *agenda);
void salvaLista(Lista_contatos *agenda);

//Funções auxiliares
void limpaBuffer();
void limpaTela();
void chamaMenu();

//=====Prototipagem de Funções=====//
void iniciaLista(Lista_contatos *agenda)
{
    //Inicializa a lista
    agenda->inicio = NULL; //Seta o inicio da lista para vazio
    agenda->fim = NULL; //Seta o fim da lista para vazio
    agenda->qtdContatos = 0; //Seta o tamanho da lista para vazio
}

int inserirItem(Lista_contatos *agenda, Contato novoContato)
{
    //Insere itens na lista

    //Variaveis auxliares para inserção na lista
    //aux - recebe o primeiro item da lista
    //novoItem - tem valor do item a ser inserido
    Item *aux = agenda->inicio, *novoItem = (Item *) malloc(sizeof(Item));

    //Copia para novoItem os valores do item a ser inserido
    novoItem->contato.id = novoContato.id;
    strcpy(novoItem->contato.nome, novoContato.nome);
    strcpy(novoItem->contato.email, novoContato.email);
    strcpy(novoItem->contato.telefone, novoContato.telefone);

    //Verifica se a lista está vazia
    if(aux == NULL){

        //Caso sim, o novo item
        //será inserido na lista
        agenda->inicio = novoItem;
        agenda->fim = novoItem;
        novoItem->prox = NULL;
        novoItem->ant = NULL;
        agenda->qtdContatos++;
    }else{

        //Caso não, o novo item
        //será inserido no fim da lista
        novoItem->prox = agenda->fim->prox;
        novoItem->ant = agenda->fim;
        agenda->fim->prox = novoItem;
        agenda->fim = novoItem;
        agenda->qtdContatos++;
    }

    return 1;
}

int buscarItemNome(Lista_contatos *agenda, char *nome)
{
    //Busca um item, baseado em seu Nome

    //Ponteiros auxiliares para a busca
    //aux - recebe o inicio da lista
    //listaBusca - lista auxiliar para conter os contatos que tem mesma ocorrencia de nome
    Item *aux = agenda->inicio;
    Lista_contatos *listaBusca = (Lista_contatos *) malloc(sizeof(Lista_contatos));
    iniciaLista(listaBusca); //Inicializa lista auxiliar

    //Verifica se a lista está vazia
    if(aux == NULL){
        //Caso não, informa ao usuário que a lista está vazia
        printf("\nA lista esta vazia!\n");
    }else{

        //Caso sim, verifica quantas ocorrencias houve
        //percorrendo toda a lista e as insere na lista auxiliar
        while(aux != NULL){
            if(strstr(aux->contato.nome, nome) != NULL){ //verifica a existência do nome informado nos contatos da lista
                inserirItem(listaBusca, aux->contato);
            }

            aux = aux->prox;
        }

        //Verifica se a lista auxiliar está vazia
        if(listaBusca->inicio == NULL){

            //Caso sim, informa ao usuário e retorna ao programa negativo
            printf("\nNenhum contato encontrado!\n");
            return 0;
        }else{

            //Caso não, mostra a lista auxiliar com os contatos
            mostraLista(listaBusca);

            //esvazia a lista auxiliar
            esvaziaLista(listaBusca);

            //libera os ponteiros da memória
            free(listaBusca);
            free(aux);

            //apaga os endereços dos ponteiros
            aux = NULL;
            listaBusca = NULL;

            return 1;
        }
    }
}

Item* buscarItemID(Lista_contatos *agenda, int id)
{
    //Busca um item da lista, baseado em seu ID
    //e retorna seu endereço na lista

    Item *aux = agenda->inicio; //aux - recebe o inicio da lista a ser percorrida

    //Verifica se a lista está vazia
    if(aux == NULL){

        //Caso sim, informa ao usuário e retorna ao programa vazio
        printf("\nA lista esta vazia\n");
        return NULL;
    }else{

        //Caso não, percorre a lista até encontrar
        //o contato com ID especificado
        while((aux != NULL) && (aux->contato.id != id)){
            aux = aux->prox;
        }

        return aux; ////Retorna o endereço do contato
    }
}

int removerItem(Lista_contatos *agenda, int id)
{
    //Remove um item da lista, baseado em seu ID

    //Ponteiros auxiliares de remoção de contatos
    //item - recebe o endereço do contato a ser removido
    //aux - auxilia na manutençao da ordem de ID's na lista
    Item *item = buscarItemID(agenda, id), *aux;

    //Verifica se o item buscado foi encontrado
    if(item == NULL){

        //Caso não, retorna falso ao programa
        return 0;
    }else{

        //Caso sim
        //verifica se o contato é o único contato da lista,
        //o primeiro, o último ou está entre a lista
        if((item->ant == NULL) && (item->prox == NULL)){ //Verifica se é o unico item da lista
            agenda->inicio = NULL;
            agenda->fim = NULL;
            agenda->qtdContatos--;

        }else if(item == agenda->fim){ //Verifica se é o último item da lista
            agenda->fim->ant->prox = item->prox;
            agenda->fim = item->ant;
            agenda->qtdContatos--;

        }else if(item == agenda->inicio){ //Verifica se é o primeiro item da lista
            agenda->inicio->prox->ant = item->ant;
            agenda->inicio = item->prox;

            //Laço que faz a manutenção dos ID's da lista
            //para que ela não fique com a ordem quebrada
            aux = agenda->inicio;
            while(aux != NULL){
                aux->contato.id--;
                aux = aux->prox;
            }

            agenda->qtdContatos--;

        }else{ //Verifica se está contido na lista
            item->ant->prox = item->prox;
            item->prox->ant = item->ant;

            //Laço que faz a manutenção dos ID's da lista
            //para que ela não fique com a ordem quebrada
            aux = item->prox;
            while(aux != NULL){
                aux->contato.id--;
                aux = aux->prox;
            }

            agenda->qtdContatos--;
        }

        //Libera os ponteiros auxiliares da memória
        free(item);
        free(aux);

        //Apaga o endereço desses ponteiros na memória
        item = NULL;
        aux = NULL;

        return 1;
    }
}

int modificarItem(Lista_contatos *agenda, int id)
{

    //Modifica um item da lista, baseado na busca por ID

    //Ponteiros e variaveis auxiliares para modificação do contato
    //item - Ponteiro que receberá o endereço do contato a ser modificado
    //optCampo - Variável auxiliar para escolha do campo a ser alterado
    Item *item = buscarItemID(agenda, id);
    int optCampo;

    //Verifica se o contato foi encontrado na lista
    if(item == NULL){

        //Caso não, retorna falso ao programa
        return 0;
    }else{

        //Caso sim, inicia um laço
        //para que o usuário informe
        //o campo que ele deseja alterar
        do{

            //Solicita ao usuário o campo a ser alterado
            printf("\nQual campo deseja atualizar?\n1 - Nome\n2 - Telefone\n3 - E-mail\nDigite a opcao desejada: ");
            scanf("%d", &optCampo);
            limpaBuffer();

            if(optCampo == 1){ //Atualizar campo 'Nome'
                printf("\nNome: ");
                scanf("%30[^\n]s", item->contato.nome);
                limpaBuffer();
            }else if(optCampo == 2){ //Atualizar campo 'Telefone'
                printf("\nTelefone (xx xxxxx-xxxx): ");
                scanf("%15[^\n]s", item->contato.telefone);
                limpaBuffer();
            }else if(optCampo == 3){ //Atualizar campo 'E-mail'
                printf("\nE-mail: ");
                scanf("%30[^\n]s", item->contato.email);
                limpaBuffer();
            }else{ //Opção inexistente
                printf("\nOpcao Invalida!\n");
                limpaTela();
            }
        }while((optCampo != 1) && (optCampo != 2) && (optCampo != 3));

        return 1;
    }

    free(item); //Libera o ponteiro da memória
    item = NULL; //Apaga o endereço do ponteiro na memória
}

void mostraItem(Lista_contatos *agenda, Item *endItem)
{
        //mostra as informações sobre o item da lista
        printf("\n%5s|%30s|%15s|%30s|\n","Id.","Nome","Telefone","E-mail");
        printf("%5s|%30s|%15s|%30s|\n","-----","------------------------------","---------------","------------------------------");
        printf("%5d|%30s|%15s|%30s|\n",endItem->contato.id,endItem->contato.nome,endItem->contato.telefone, endItem->contato.email);

}

void mostraLista(Lista_contatos *agenda)
{
    Item *aux = agenda->inicio; //Ponteiro auxiliar para percorrer a lista

    //Verifica a existencia de algum item na lista
    if(aux == NULL){
        //Caso não exista, informa ao usuário
        printf("\nA lista esta vazia!\n");
    }else{

        //Encontrado pelo menos 1 item
        //mostra as informações sobre os itens da lista
        printf("\n%5s|%30s|%15s|%30s|\n","Id.","Nome","Telefone","E-mail");
        printf("%5s|%30s|%15s|%30s|\n","-----","------------------------------","---------------","------------------------------");
        while(aux != NULL){
            printf("%5d|%30s|%15s|%30s|\n",aux->contato.id,aux->contato.nome,aux->contato.telefone, aux->contato.email);
            aux = aux->prox;
        }

        printf("\nTotal: %d\n", agenda->qtdContatos); //Mostra a quantidade de itens da lista
    }
}

void salvaLista(Lista_contatos *agenda)
{
    //Função para salvar os contatos em um arquivo binário

    FILE *arq_lista = fopen("Lista_Contatos.dat", "wb"); //Ponteiro para o arquivo a ser salvo os contatos

    //Verifica se o arquivo foi aberto com sucesso
    if(arq_lista == NULL){
        //Caso não, informa erro ao usuário
        printf("\nErro ao salvar!\n");
    }else{

        //Caso sim, inicia um laço, salvando todos os contatos da lista
        //no arquivo

        Item *aux = agenda->inicio; //Ponteiro auxiliar para percorrer a lista
        while(aux != NULL){ //Laço que percorre a lista de contatos
            fwrite(&(aux->contato), sizeof(Contato), 1, arq_lista); //Salva o contato no arquivo
            aux = aux->prox; //Passa para o próximo item da lista
        }

        free(aux); //Libera o ponteiro da memória
        aux = NULL; //Apaga o endereço do ponteiro
    }

    fclose(arq_lista); //Fecha o arquivo, liberando-o da memória
    arq_lista = NULL; //Apaga o endereço do ponteiro do arquivo
}

void carregaLista(Lista_contatos *agenda)
{
    //Função para carregar os contatos de um arquivo binário
    //e salva-los na memória principal

    FILE *arq_lista = fopen("Lista_Contatos.dat", "rb"); //Ponteiro para o arquivo a ser lido os contatos

    //Verifica se o arquivo foi aberto com sucesso
    if(arq_lista == NULL){
        //Caso não, informa erro ao usuário
        printf("\nErro ao carregar!\n");
    }else{

        //Caso sim, inicia um laço, obtendo todos os contatos da lista
        //e salvando-os na memória principal

        Item *aux = (Item *) malloc(sizeof(Item)); //Ponteiro auxiliar que receberá o contato obtido do arquivo
        while(fread(&(aux->contato), sizeof(Contato), 1, arq_lista)){ //Laço que percorrerá o arquivo e salvará os contatos na memória
                inserirItem(agenda, aux->contato); //Insere contato na lista
        }

        free(aux); //Libera o ponteiro da memória
        aux = NULL; //Apaga o endereço do ponteiro
    }

    fclose(arq_lista); //Fecha o arquivo, liberando-o da memória
    arq_lista = NULL; //Apaga o endereço do ponteiro do arquivo
}

void esvaziaLista(Lista_contatos *agenda)
{
    //Apaga todos os contatos da lista

    Item *aux = agenda->inicio; //Ponteiro auxiliar para percorrer a lista

    //Verifica se a lista já está vazia
    if(aux == NULL){
        //Se sim, informa ao usuário
        printf("\nA lista esta vazia\n");
    }else{

        //Se não, percorrerá a lista
        while(aux != NULL){
            agenda->inicio = agenda->inicio->prox;

            free(aux); //Libera o contato da memória
            aux = NULL; //Apaga o endereço do contato na memória

            agenda->qtdContatos--;
            aux = agenda->inicio;
        }

        agenda->fim = NULL; //O fim da lista será vazio
    }
}

void chamaMenu()
{
    //Menu de opções básico
	printf("\n -------%-17s------\n", "Agenda Eletronica");
	printf("|%-30s|\n"," ");
	printf("|%5s%-25s|\n", " ","[1] Adicionar Contato");
	printf("|%5s%-25s|\n", " ","[2] Atualizar Contato");
	printf("|%5s%-25s|\n", " ","[3] Remover Contato");
	printf("|%5s%-25s|\n", " ","[4] Buscar Contato");
	printf("|%5s%-25s|\n", " ","[5] Mostrar Agenda");
	printf("|%5s%-25s|\n", " ","[6] Esvaziar Agenda");
	printf("|%-30s|\n"," ");
	printf("|%-30s|\n","------------------------------");
	printf("|%-30s|\n"," ");
	printf("|%5s%-25s|\n", " ","[0] Sair");
	printf("|%-30s|\n"," ");
	printf(" ------------------------------\n");
}

void limpaBuffer(){
    char c;
    while(((c = getchar()) != '\n') && (c != EOF));
}

void limpaTela()
{
    //Prepara o console para outras operações
    printf("\nPressione ENTER para continuar...");
    getchar();
    system("cls || clear");
}

//=====Função main()=====//
void main(void)
{

    Lista_contatos *agenda = (Lista_contatos *) malloc(sizeof(Lista_contatos)); //Declaração da lista de contatos
    iniciaLista(agenda); //Chama a iniciação da lista

    Contato novoContato; //Declaração do novo item a ser inserido

    carregaLista(agenda); //Carrega os contatos do arquivo de contatos na lista

    int opt, optSubMenu, id; //Declaração de auxiliares para menu e busca
    Item *endItem; //Auxiliar para receber o endereço do item buscado
    char nomeBusca[30]; //Auxiliar para busca através de Nome

    //Laço principal do programa
    do{

        //Chama função para exibir menu na tela
        chamaMenu();

        //Solicita ao usuário uma opção do menu
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &opt);
        limpaBuffer();

        //Verifica se a opção é válida
        //e executa uma ação
        switch(opt){

            //Ação de adicionar contato à lista
            case 1:

                system("cls || clear"); //Limpa a tela
                printf("\n ------%-15s------\n", "Inserir Contato");

                novoContato.id = agenda->qtdContatos+1; //Insere o ID automaticamente, de acordo com o tamanho da lista

                //Solicita ao usuário nome, telefone e e-mail
                //do novo contato a ser inserido
                printf("\nNome: ");
                scanf("%30[^\n]s", novoContato.nome);
                limpaBuffer();

                printf("\nTelefone (xx xxxxx-xxxx): ");
                scanf("%15[^\n]s", novoContato.telefone);
                limpaBuffer();

                printf("\nE-mail: ");
                scanf("%30[^\n]s", novoContato.email);
                limpaBuffer();

                //Verifica se a inserção foi efetuada com sucesso
                inserirItem(agenda, novoContato)? printf("\nContato inserido com sucesso!") : printf("\nNao foi possivel inserir contato");

                limpaTela();

                break;

            //Modificar um item da lista
            case 2:

                system("cls || clear"); //Limpa a tela
                printf("\n ------%-18s------\n", "Atualizar Contato");

                //Dá ao usuário duas opções
                //Busca por nome
                //Busca por ID
                printf("\n1 - Busca por ID\n2 - Busca por Nome\nDigite a opcao desejada: ");
                scanf("%d", &optSubMenu);
                limpaBuffer();

                //Verifica escolha do usuário
                if(optSubMenu == 1){ //Busca por ID

                    //Solicita ao usuário o ID do contato a ser alterado
                    printf("\nDigite o ID do contato que deseja atualizar: ");
                    scanf("%d", &id);
                    limpaBuffer();

                    //Verifica se o contato foi alterado com sucesso
                    modificarItem(agenda, id)? printf("\nContato Atualizado!\n") : printf("\nContato nao encontrado!\n");

                }else if(optSubMenu == 2){ //Busca por Nome

                    //Solicita o nome do contato a ser buscado
                    printf("\nDigite o nome do contato: ");
                    scanf("%30[^\n]s", nomeBusca);
                    limpaBuffer();

                    //Busca o contato
                    if(buscarItemNome(agenda, nomeBusca)){

                        //caso encontrado, solicita ao usuário o ID
                        //para efetuar modificações
                        printf("\nDigite o ID do contato que deseja atualizar: ");
                        scanf("%d", &id);
                        limpaBuffer();

                        //Verifica se o contato foi alterado com sucesso
                        modificarItem(agenda, id)? printf("\nContato Atualizado!\n") : printf("\nContato nao encontrado!\n");
                    }else{
                        //Caso não, informa ao usuário
                        printf("\nNenhum resultado encontrado!\n");
                    }

                }else{ //Opção inexistente
                    printf("\nOpcao Invalida!\n");
                }

                limpaTela();

                break;

            //Remover um item da lista
            case 3:

                system("cls || clear"); //Limpa a tela
                printf("\n ------%-15s------\n", "Remover Contato");

                //Dá ao usuário duas opções
                //Remover por nome
                //Remover por ID
                printf("\n1 - Remover por ID\n2 - Remover por Nome\nDigite a opcao desejada: ");
                scanf("%d", &optSubMenu);
                limpaBuffer();

                if(optSubMenu == 1){ //Remove por ID

                    //Solicita id do contato a ser excluido
                    printf("\nDigite o ID do contato que deseja remover: ");
                    scanf("%d", &id);
                    limpaBuffer();

                    //Verifica se a remoção aconteceu
                    removerItem(agenda, id)? printf("\nContato Removido!\n") : printf("\nContato nao encontrado!\n");

                }else if(optSubMenu == 2){ //Remove por nome

                    //Solicita id do contato a ser excluido
                    printf("\nDigite o nome do contato: ");
                    scanf("%30[^\n]s", nomeBusca);
                    limpaBuffer();

                    //Busca o contato
                    if(buscarItemNome(agenda, nomeBusca)){

                        //Caso encontrado, solicita ao usuário
                        //o ID do contato a ser removido
                        printf("\nDigite o ID do contato que deseja remover: ");
                        scanf("%d", &id);
                        limpaBuffer();

                        //Verifica se a remoção aconteceu
                        removerItem(agenda, id)? printf("\nContato Removido!\n") : printf("\nContato nao encontrado!\n");
                    }else{
                        //Caso não, informa ao usuário
                        printf("\nNenhum resultado encontrado!\n");
                    }

                }else{ //Opção inexistente
                    printf("\nOpcao Invalida!\n");
                }

                limpaTela();

                break;

            //Buscar item na lista
            case 4:

                system("cls || clear"); //Limpa a tela
                printf("\n ------%-14s------\n", "Buscar Contato");

                //Dá ao usuário duas opções
                //Buscar por nome
                //Buscar por ID
                printf("\n1 - Busca por ID\n2 - Busca por Nome\nDigite a opcao desejada: ");
                scanf("%d", &optSubMenu);
                limpaBuffer();

                if(optSubMenu == 1){ //Buscar por ID

                    //Solicita ao usuário o ID do contato a ser buscado
                    printf("\nDigite o ID do contato que deseja buscar: ");
                    scanf("%d", &id);
                    limpaBuffer();

                    //Verifica se a busca por ID retornou
                    //algum contato, caso sim, mostra o item encontrado
                    endItem = buscarItemID(agenda, id);
                    endItem != NULL? mostraItem(agenda, endItem) : printf("\nContato nao encontrado!\n");

                }else if(optSubMenu == 2){ //Buscar por Nome

                    //Solicita ao usuário o nome do contato a ser buscado
                    printf("\nDigite o nome do contato que deseja buscar: ");
                    scanf("%30[^\n]s", nomeBusca);
                    limpaBuffer();

                    //Busca o contato pelo nome informado
                    buscarItemNome(agenda, nomeBusca);


                }else{ //Opção inexistente
                    printf("\nOpcao Invalida!\n");
                }

                limpaTela();

                break;

            //Ação de mostrar a lista completa
            case 5:

                system("cls || clear"); //Limpa a tela

                //Mostra na tela todos os itens da lista
                mostraLista(agenda);

                limpaTela();

                break;

            //Ação de esvaziar a lista
            case 6:

                system("cls || clear"); //Limpa a tela

                //Torna a lista vazia
                //apagando todos os itens dela
                esvaziaLista(agenda);

                printf("\nAgenda esvaziada\n");
                limpaTela();

                break;

            //Ação para comandos inválidos (exceto o de sair)
            default:
                if(opt != 0){
                    printf("\nOpcao invalida\n");

                    limpaTela();
                }

        }
     }while(opt != 0); //Verifica se a opção escolhida é a de sair

     printf("\nGo with honor, friend!\n");
     salvaLista(agenda); //Salva os itens da agenda no arquivo de contatos

     free(agenda); //Libera a agenda da memória
     agenda = NULL; //Apaga o endereço da agenda na memória
}
