
#include <stdlib.h>
#include <iostream>
using namespace std;
struct Aluno{
    string nome;
    int faltas;
 	double nota[4];
    };

Aluno *alocaTurma(size_t tam){
    return new Aluno[tam];
    }
    
void desalocaTurma(Aluno*turma){
    delete[]turma;
    }

void leDadosAluno(Aluno*a){
    cout<<"Digite o nome do aluno: ";
    cin>>(*a).nome;
    cout<<"Digite o número de faltas do aluno";
    cin>>a->faltas;
    cout<<"Digite as tres notas do aluno";
    cin>>a->nota[0]>>a->nota[1]>>a->nota[2];
    }

int main(){
   Aluno *turmaA;
   turmaA=alocaTurma(2);
   leDadosAluno(&turmaA[0]);
   leDadosAluno(&turmaA[1]);
   desalocaTurma(turmaA);
   return 0; 
    }





