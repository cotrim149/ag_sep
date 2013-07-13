#include <iostream>
#include <stdlib.h>
#include <time.h>

#define qtd_genes 5

using namespace std;

int valor_aleatorio(int denominador){
	int valor = rand();
	
	return valor%denominador;
}


void mutacao(int* cromossomo,int tamanho_cromossomo){
	int opcao = 1;//valor_aleatorio(2);
	int qtd_genes_trocados = valor_aleatorio(tamanho_cromossomo);

	int locus1 = 2;//valor_aleatorio(tamanho_cromossomo);
	int locus2 = 4;//valor_aleatorio(tamanho_cromossomo);


	switch(opcao){
		case 0:		// troca simples			
			for(int i=0; i< qtd_genes_trocados;i++){
				int loco_aleatorio = valor_aleatorio(qtd_genes_trocados);
				if(cromossomo[loco_aleatorio] == 1)
					cromossomo[loco_aleatorio] = 0;
				else
					cromossomo[loco_aleatorio] = 1;
			}
			
		break;
		case 1:		// inversao
			int temp = cromossomo[locus1];
			cromossomo[locus1] = cromossomo[locus2];
			cromossomo[locus2] = temp;			
		break;
	}
	
}


int main(){
	int cromossomo[qtd_genes];

	srand(time(NULL));


	for(int i=0; i< qtd_genes; i++)
		cromossomo[i] =valor_aleatorio(2);
		
	cout << "antes" << endl;
	for(int i=0; i< qtd_genes; i++)
		cout << "gene" << i+1 << ": " << cromossomo[i] << endl;


	mutacao(cromossomo,qtd_genes);
	cout << "depois" << endl;
	for(int i=0; i< qtd_genes; i++)
		cout << "gene" << i+1 << ": " << cromossomo[i] << endl;
	

return 0;
}

