#include <iostream>
#define TAM_VETOR 4

using namespace std;

int valor_aleatorio(int denominador){
	int valor = 10;
	
	return valor%denominador;
}


void mutacao(int* cromossomo){
	int opcao = valor_aleatorio(2);
	switch(opcao){
		case 0:		// troca simples
			int qtd_genes_trocados = valor_aleatorio(cromossomo.size());
			
			for(int i=0; i< qtd_genes_trocados;i++){
				int loco_aleatorio = valor_aleatorio(qtd_genes_trocados);
				if(cromossomo[loco_aleatorio] == 1)
					cromossomo[loco_aleatorio] = 0;
				else
					cromossomo[loco_aleatorio] = 1;
			}
			
		break;
		case 1:		// inversao
		break;
	}
	
}


int main(){
	int qtd_genes = 4;
	int cromossomo[qtd_genes];


	mutacao(cromossomo);

return 0;
}

