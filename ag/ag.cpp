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
	int opcao = 0;//valor_aleatorio(2);
	switch(opcao){
		case 0:		// troca simples
			
			int qtd_genes_trocados = valor_aleatorio(tamanho_cromossomo);
			
			for(int i=0; i< qtd_genes_trocados;i++){
				int loco_aleatorio = valor_aleatorio(qtd_genes_trocados);
				if(cromossomo[loco_aleatorio] == 1)
					cromossomo[loco_aleatorio] = 0;
				else
					cromossomo[loco_aleatorio] = 1;
			}
			
		break;
/*		case 1:		// inversao
			cout << "funcao vazia\n\n" << endl;
		break;
*/	}
	
}


int main(){
	int cromossomo[qtd_genes];

	srand(time(NULL));


	for(int i=0; i< qtd_genes; i++)
		cromossomo[i] =0;

	cout << "antes" << endl;
	for(int i=0; i< qtd_genes; i++)
		cout << "gene" << i+1 << ": " << cromossomo[i] << endl;


	mutacao(cromossomo,qtd_genes);
	cout << "depois" << endl;
	for(int i=0; i< qtd_genes; i++)
		cout << "gene" << i+1 << ": " << cromossomo[i] << endl;
	

return 0;
}

