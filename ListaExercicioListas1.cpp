#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Reg{
	int info;
	Reg *prox, *ant;
}No;

typedef struct Lista{
	Reg *inicio, *fim;
	int tam;
}ListaD;

ListaD *inicializa(ListaD *LD){
	LD->inicio=LD->fim=NULL;
	LD->tam=0;
	return LD;
}

bool listaVazia(ListaD *LD){
	return ((LD->inicio == LD->fim) && (LD->tam==0));
}

ListaD *insereInicio(ListaD *LD){
	system("cls");
	int elemento;
	cout << "Qual elemento deseja inserir: ";
	cin >> elemento;
	
	No *novo;
	novo = new No;
	novo->info = elemento;
	novo->ant = NULL;
	if(listaVazia(LD)){
		novo->prox=NULL;
		LD->inicio=LD->fim = novo;
		LD->tam++;
	}else{
		novo->prox = LD->inicio;
		LD->inicio->ant = novo;
		LD->inicio = novo;
		LD->tam++;
	}
	system("cls");
	return LD;
}

ListaD *insereFim(ListaD *LD){
	system("cls");
	int elemento;
	cout << "Qual elemento deseja inserir: ";
	cin >> elemento;
	
	No *novo;
	novo = new No;
	novo->info = elemento;
	novo->prox = NULL;
	if(listaVazia(LD)){
		novo->ant=NULL;
		LD->inicio=LD->fim = novo;
		LD->tam++;
	}else{
		novo->ant = LD->fim;
		LD->fim->prox = novo;
		LD->fim = novo;
		LD->tam++;
	}
	system("cls");
	return LD;
}

ListaD *insereQualquerLugar(ListaD *LD){
	system("cls");
	int elemento;
	cout << "Qual elemento deseja inserir: ";
	cin >> elemento;
	
	No *novo;
	novo = new No;
	novo->info = elemento;
	int posicao;
	cout << "Em qual posicao da lista voce quer adicionar o elemento? " << endl;
	cin >> posicao;
	system("cls");
	
	if(posicao == 1){
		LD = insereInicio(LD);
	}else if(posicao > LD->tam){
		LD = insereFim(LD);
	}else{
		int aux=0;
		No *copia;
		copia = LD->inicio;
		while(copia!=NULL){
			aux++;
			if(aux == posicao){
				novo->prox = copia;
				novo->ant = copia->ant;
				copia->ant->prox = novo;
				copia->ant = novo;
				break;
			}
			copia = copia->prox;
		}
	}
	return LD;
}


ListaD *excluirInicio(ListaD *LD){
	No *CP;
	CP = LD->inicio;
	LD->inicio = CP->prox;
	CP->prox->ant = NULL;
	LD->tam--;
	delete CP;
	cout << "--------------------" << endl;
	cout << " Elemento excluido!" << endl;
	cout << "--------------------" << endl;
return LD;
}

ListaD *excluirFim(ListaD *LD){
	No *CP;
	CP = LD->fim;
	LD->fim = CP->ant;
	CP->ant->prox = NULL;
	LD->tam--;
	delete CP;
	cout << "--------------------" << endl;
	cout << " Elemento excluido!" << endl;
	cout << "--------------------" << endl;
return LD;
}

ListaD *excluirQualquerLugar(ListaD *LD){
	int elemento;
	cout << "Qual elemento deseja excluir: ";
	cin >> elemento;
	
	No *CP;
	CP = LD->inicio;
	while((CP!=NULL)&&(CP->info!=elemento)){
		if(CP==NULL){
			cout << "Elemento não esta na lista!" << endl;
		}else if((CP->ant==NULL)&&(CP->prox!=NULL)){
			excluirInicio(LD);
		}else if((CP->prox==NULL)&&(CP->ant!=NULL)){
			excluirFim(LD);
		}else{
			if(CP->info == elemento){
				CP->ant->prox = CP->prox;
				CP->prox->ant = CP->ant;
				LD->tam--;
			}
		}
		CP = CP->prox;
	}
return LD;
}

void Imprime(ListaD *LD){
	system("cls");
	No *copia;
	copia = LD->inicio;
	int cont = 1;
	if(listaVazia(LD)){
		cout << "Lista vazia!" << endl;
	}else{
		cout << "===== LISTA =====" << endl;
		while(copia!=NULL){
			cout << "[" << cont <<"]:" << copia->info << endl;
			copia = copia->prox;
			cont++;
		}
		cout << "=================" << endl;
	}
}

int main(){
	ListaD *L1;
	L1 = new ListaD;
	L1 = inicializa(L1);
	
	int opcao;
	do{
		
		cout << "=================================================" << endl;
		cout << "                       MENU" << endl;
		cout << "=================================================" << endl;
		cout << " 1) Inserir elemento no inicio." << endl;
		cout << " 2) Inserir elemento no fim." << endl;
		cout << " 3) Inserir elemento em qualquer lugar da lista." << endl;
		cout << " 4) Excluir elemento no inicio. " << endl;
		cout << " 5) Excluir elemento no fim." << endl;
		cout << " 6) Excluir elemento em qualquer lugar da lista." << endl;
		cout << " 7) Imprime lista." << endl;
		cout << " 0) Sair." << endl;
		cout << "_________________________________________________" << endl;
		cout << " Escolha uma opcao: ";
		cin >> opcao;
		
		switch(opcao){
			case 1: L1 = insereInicio(L1);
					break;
			
			case 2: L1 = insereFim(L1); 
					break;
			
			case 3: L1 = insereQualquerLugar(L1);
					break;
			
			case 4: excluirInicio(L1);		
					break;
		
			case 5: excluirFim(L1);
					break;
			
			case 6: excluirQualquerLugar(L1);
					break;
			
			case 7: Imprime(L1); 
					break;
		
		}
	}while(opcao!=0);
		
return 0;
}
