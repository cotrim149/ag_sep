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
	int opcao = valor_aleatorio(2);
	int qtd_genes_trocados = valor_aleatorio(tamanho_cromossomo);

	int locus1 = valor_aleatorio(tamanho_cromossomo);
	int locus2 = valor_aleatorio(tamanho_cromossomo);


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

void crossover(int* pai_1,int tamanho_pai_1, int* pai_2, int tamanho_pai_2){

	int ponto_cross_pai_1 = valor_aleatorio(tamanho_pai_1);
	int ponto_cross_pai_2 = valor_aleatorio(tamanho_pai_2);
	
	int vetor_1[ponto_cross_pai_1];
	//int vetor_2[ponto_cross_pai_2];
	
	for(int j=0; j <= ponto_cross_pai_1;j++){
		vetor_1[j]= pai_1[j];
	}
	
	int maior_ponto_cross;
	if(ponto_cross_pai_1 >= ponto_cross_pai_2)
		maior_ponto_cross = ponto_cross_pai_1;
	else
		maior_ponto_cross = ponto_cross_pai_2;
	
	for(int i=maior_ponto_cross; i >= 0; i--){
		pai_1[i]= pai_2[i];
		pai_2[i]= vetor_1[i];
	}
	
	
}

int main(){
	int cromossomo[qtd_genes];

	srand(time(NULL));


	for(int i=0; i< qtd_genes; i++)
		cromossomo[i] =valor_aleatorio(2);
		
	cout << "antes" << endl;
	/*for(int i=0; i< qtd_genes; i++)
		cout << "gene" << i+1 << ": " << cromossomo[i] << endl;
	*/
	int tamanho_pai=4;
	int pai_1[tamanho_pai];
	int pai_2[tamanho_pai];
	
	pai_1[0]=0;
	pai_1[1]=1;
	pai_1[2]=1;
	pai_1[3]=1;
	
	pai_2[0]=0;
	pai_2[1]=1;
	pai_2[2]=0;
	pai_2[3]=0;
	
	cout << "pai 1 ";
	for(int i=0; i< tamanho_pai; i++)
		cout << " " << pai_1[i];
	
	cout << "pai 2 ";
	for(int i=0; i< tamanho_pai; i++)
		cout << " " << pai_2[i];
	
	crossover(pai_1,tamanho_pai,pai_2,tamanho_pai);	
	//mutacao(cromossomo,qtd_genes);
	cout << "depois" << endl;
	/*for(int i=0; i< qtd_genes; i++)
		cout << "gene" << i+1 << ": " << cromossomo[i] << endl;
	*/
	
	cout << "pai 1 ";
	for(int i=0; i< tamanho_pai; i++)
		cout << " " << pai_1[i];
	
	cout << "pai 2 ";
	for(int i=0; i< tamanho_pai; i++)
		cout << " " << pai_2[i];

return 0;
}

