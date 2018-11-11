#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct Dados
{
	int mat[10];
	char Nome[20];
	float N1, N2, N3;
} D1

typedef struct Reg
{
	D1 info;
	Reg *prox;
} Celula;

Celula* inicializa(void)
{

	return NULL;
}

int main (void)
{
	int tam;
	Celula *L1;
	L1 = new Celula; 
	L1 = inicializa(); 

}


#include <iostream>

using namespace std;

typedef struct Dados{
	int Mat;
	char Nome[30];
	float n1;
	float n2;
	float n3;
	float media;
}Diario;

typedef struct Reg{
	Diario info;
	Reg *prox;
}Celula;

Celula *inicializa(void){
	return NULL;
}

Celula *insere (Celula *L){ 
	Celula  *novo;
	novo = new Celula;
	cout<<"\nDADOS DOS ALUNOS: "<<endl;
	cout<<"MATRICULA: ";
	cin>>novo->info.Mat;
	cout<<"NOME: ";
	cin.ignore();
	cin.getline(novo->info.Nome,30);
	cout<<"PRIMEIRA NOTA: ";
	cin>>novo->info.n1;
	cout<<"SEGUNDA NOTA: ";
	cin>>novo->info.n2;
	cout<<"TERCEIRA NOTA: ";
	cin>>novo->info.n3;
	novo->info.media = ((novo->info.n1*4+novo->info.n2*5+novo->info.n3*6)/15);
	L = novo;
	novo ->prox = NULL;
	L->prox = novo->prox;
	return L;
}

void imprime(Celula *L){
	Celula *p;
	//p = new Celula;
	for (p = L; p!= NULL; p = p->prox){
		cout<<"\n DADOS"<<endl;
		cout<<"MATRICULA = "<<p->info.Mat<<endl;
		cout<<"NOME = "<<p->info.Nome<<endl;
		cout<<"NOTA 1 = "<<p->info.n1<<endl;
		cout<<"NOTA 2 = "<<p->info.n2<<endl;
		cout<<"NOTA 3 = "<<p->info.n3<<endl;
		cout<<"MEDIA = "<<p->info.media<<endl;
	}
	}

void busca( Celula *L, int mat){
	Celula* p;
	for (p = L; p!= NULL; p = p->prox)
		if (p->info.Mat == mat) cout<< p->info.Nome<<endl;
		
		else cout<<"ERRO! Matricula não encontrada."<<endl;

	}
	
void excluir(Celula *L, int mat){
	Celula *guarda, *lixo;
	guarda = L;
	lixo = L->prox;
	while (lixo != NULL && (lixo->info.Mat != mat)) {
		guarda = lixo;
		lixo = lixo->prox;
	}
	if (lixo != NULL) {
		guarda->prox = lixo->prox;
		delete lixo;
	}
}


int main(){
	Celula *L1;
	L1 = new Celula;
	L1 = inicializa();
	int N;
	cout<<"QUANTOS ALUNOS DESEJA CADASTRAR? "<<endl;
	cin>>N;
	for(int i=0; i<N; i++)
		L1 = insere(L1);
	//imprime(L1);
	//busca(L1,12); //O segundo parametro é o da matrículo do usuário, do tipo inteiro.
	excluir(L1, 12);
	imprime(L1);
	


	return 0;
}