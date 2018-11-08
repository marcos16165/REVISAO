#include<iostream>
using namespace std;

struct no
{
	int codigo;
	float preco = 0;
	int estoque;
	struct no *prox;
};
typedef struct no *noptr;

noptr inicio = NULL;

bool lista_vazia()
{
	if(inicio)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void inserir()
{
	int i = 0;
	while(i < 3)
	{
		noptr p;
		p = new no;
		cout << "Digite o codigo do produto: " << endl;
		cin >> p->codigo;
		cout << "Digite o preço do produto: " << endl;
		cin >> p->preco;
		cout << "Digite a quantidade em estoque desse produto: " << endl;
		cin >> p->estoque;
		if(lista_vazia())
		{
			p->prox = inicio;
			inicio = p;
			i = i + 1;
		}
		else
		{
			p->prox = inicio;
			inicio = p;
			i = i + 1;
		}
	}
}

void desconto()
{
	noptr p = inicio;
	int desc;
	cout << "Digite o valor a ser descontado: " << endl;
	cin >> desc;
	if(lista_vazia())
	{
		cout << “A lista esta vazia!” << endl;
	}
	else
	{
		while(p != NULL)
		{
			p->preco = (p->preco * (desc / 100));
cout << “Novo preco do produto:
					 \n” < preco;
			p = p->prox;
		}
	}
}

void relatorio()
{
	noptr p = inicio;
	if(lista_vazia())
	{
		cout << “A lista esta vazia.” << endl;
	}
	else
	{
		while(p != NULL)
		{
			cout << "Produto de codigo: " < codigo << endl;
			cout << "Preço do produto “<codigo<<”: " < preco << endl;
			p = p->prox;
		}
	}
}

void maior()
{
	noptr p = inicio;
	if(lista_vazia())
	{
		cout << “A lista esta vazia.” << endl;
	}
	else
	{
		while(p != NULL)
		{
			if(p->estoque > 500)
			{
				cout << “Produto de codigo “ < codigo << ” possui estoque superior a 500.” << endl;
				p = p->prox;
			}
		}
	}
}

void menu(int op)
{
	int num;

	do
	{
		cout << "---MENU---\n";
		cout << "--1--CADASTRAR PRODUTOS.\n";
		cout << "--2--APLICAR DESCONTO.\n";
		cout << "--3--EXIBIR RELATORIO.\n";
		cout << "--4--EXIBIR PRODUTOS COM ESTOQUE SUPERIOR A 500.\n";
		cout << "--0--SAIR DO PROGRAMA.\n";
		cin >> num;

		switch(num)
		{

		case 1:
			inserir();
			break;

		case 2:
			desconto();
			break;

		case 3:
			relatorio();
			break;

		case 4:
			maior();
			break;
		}
	}
	while(num != 0);
}

int main()
{

	int opcao;

	menu(opcao);

	return(0);
}
