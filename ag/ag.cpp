#include <iostream>
#include <stdlib.h>
#include <time.h>

#define qtd_genes 5

using namespace std;


//retorna um valor aleatorio entre 0 e o denominador
int valor_aleatorio(int denominador){
	int valor = rand();
	
	return valor%denominador;
}
void imprime_matriz(int ** matriz_pop , int numero_cromossomos, int tamanho_pai){

	for(int i=0; i <numero_cromossomos;i++){
		cout<< "CROMOSSOMO"<< "<"<< i <<"> = ";
		for(int j=0;j<tamanho_pai;j++){
			cout<< matriz_pop[i][j] ;
		}
		cout<< endl;
	}


}
void imprime_vetor(int * vetor, int tamanho){
	cout<< "Imprimindo vetor: "<< endl;
	for(int i=0; i<tamanho;i++){
		cout<<"vetor["<<i<<"]= "<< vetor[i]<<endl;
	}

}
void imprime_vetorf(float * vetor, int tamanho){
	cout<< "Imprimindo vetor: "<< endl;
	for(int i=0; i<tamanho;i++){
		cout<<"vetor["<<i<<"]= "<< vetor[i]<<endl;
	}

}

int soma_vetor(int * vetor,int tamanho){
	int soma =0;
	for(int i=0; i<tamanho;i++){
		soma +=vetor[i];
		//cout<<soma<<endl;
	}

	return soma;
}

float soma_vetorf(float * vetor,int tamanho){
	float soma =0;
	for(int i=0; i<tamanho;i++){
		soma +=vetor[i];
		//cout<<soma<<endl;
	}

	return soma;
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
	cout<< endl<<"ponto cross pai 1>>" << ponto_cross_pai_1<<endl;
	cout<< endl <<"ponto cross pai 2>> " << ponto_cross_pai_2<<endl;
	
	
	int vetor_1[ponto_cross_pai_1];//funciona como um buffer para nao perdermos informação do PAI_1
	//int vetor_2[ponto_cross_pai_2];
	
	//FELIPE>> acho que esse laço tem que vir depos de calcular o maiot ponto cross mas ok
	
	
	//BUG corrigido
	for(int j=0; j <= ponto_cross_pai_1;j++){
		vetor_1[j]= pai_1[j];
		cout<< "PONTO CROSS"<<vetor_1[j]<< endl;
	}
	
	int maior_ponto_cross;
	if(ponto_cross_pai_1 >= ponto_cross_pai_2)
		maior_ponto_cross = ponto_cross_pai_1;
	else
		maior_ponto_cross = ponto_cross_pai_1;
	
	for(int i=maior_ponto_cross; i >= 0; i--){
		pai_1[i]= pai_2[i];
		pai_2[i]= vetor_1[i];
	}
	
	
}

//inicializa com zeros a população e em seguida infecta uma quantiodade determinada de individuos, pode ser por completo ou aleatorio
void inicia_populacao(int  ** matriz_pop , int numero_cromossomos, int tamanho_pai ,int qtd_infect){
	
	//inicializa a população com 0s
	numero_cromossomos -=1;
	cout<<endl;
	for(int i=0; i <=numero_cromossomos;i++){
		cout<< "INICIANDO população: "<< "<"<< i <<"> = "<<endl;
		for(int j=0;j<tamanho_pai;j++){
			matriz_pop[i][j]=0;
			cout<< matriz_pop[i][j] ;
		}
		cout<< endl;
	}
	
	
	//inicializa com a quantidade de infectados totalmente
	for(int i=0; i<= (qtd_infect-1); i++){
		int rand = valor_aleatorio(numero_cromossomos+1);
				for(int j=0;j<tamanho_pai;j++){
				matriz_pop[rand][j] = valor_aleatorio(2);
				//matriz_pop[rand][j] = 1; //para uma infecção total do individuo
				}
				cout<< "INFECÇÃo>> "<<rand<<endl;

			
	}
}

//apenas imprime a população
void imprime_populacao(int ** matriz_pop,int numero_cromossomos, int tamanho_pai){
	numero_cromossomos -=1;
	for(int i=0; i <=numero_cromossomos;i++){
		cout<< "INICIANDO população: "<< "<"<< i <<"> = "<<endl;
		for(int j=0;j<tamanho_pai;j++){
			cout<< matriz_pop[i][j] ;
		}
		cout<< endl;
	}


}

int * calcula_fitness(int ** matriz_pop,int numero_cromossomos, int tamanho_pai){
	int  * notas;
	notas = new int[numero_cromossomos];
	//inicializando vetor de notas
	for(int i=0; i<numero_cromossomos;i++){
		notas[i]=0;
	}
	
	//somando a quantidades de 1s em cada cromossomo (FUNÇÂO FITNESS)
	for(int i=0; i<numero_cromossomos;i++){
		for(int j=0;j<tamanho_pai;j++){
			notas[i] += matriz_pop[i][j];// função fitness, pode seralterada aqui
			
		}
		if(notas[i]==0) notas[i]=1;// para que quem nao tenha sintomas tenha chance de ser selecionado
	}
	
	imprime_vetor(notas,numero_cromossomos);
	
	
	cout <<endl<< "PASSOU"<<endl;
	
	return notas;
}
float *calcula_pesos(int * fitness , int numero_cromossomos){

	float * pesos = new float[numero_cromossomos];
	float soma_fitness = soma_vetor(fitness,numero_cromossomos);
	cout<< soma_fitness;
	for(int i=0; i<numero_cromossomos;i++){
		pesos[i]= ( 1 * fitness[i] )/soma_fitness;
		cout<<pesos[i]<<endl;
	}
	
	
	return pesos;
}

void seleciona_cruza(int ** pop , int * fitness, int numero_cromossomos){
	int aux=0;
	int selected_a=-1 , selected_b=-1;
	int first=0;
	int next = 0;
	int soma = soma_vetor(fitness,numero_cromossomos);
	
	
	for(int i=0;i<(numero_cromossomos);i+=2){
		aux=rand()%soma;
		//cout<<endl <<"========="<< aux;
		first = 0;
		next = 0;
		
		for(int j=0;j<numero_cromossomos;j++){
			next +=fitness[j];
			//cout<<endl<<"-------------"<<next;
			if(aux>=first && aux<next) selected_a = j;
			first = next;			
		}
		cout<< endl<< endl<< "1 - >>>>>>>>>>>>>>>  "<< selected_a<<endl;
		
		
		aux=rand()%soma;
		//cout<<endl <<"========="<< aux;
		first = 0;
		next = 0;
		
		for(int j=0;j<numero_cromossomos;j++){
			next +=fitness[j];
			//cout<<endl<<"-------------"<<next;
			if(aux>=first && aux<next) selected_b = j;
			first = next;			
		}
		cout<< endl<< endl<< "2 - >>>>>>>>>>>>>>>  "<< selected_b<<endl;

		if(selected_a == selected_b) cout<< endl <<"AAAAAAAAAAAAAAAAAAAAAAAAAA";
		//criterio de desempate
		if(selected_a == selected_b && selected_a>0 ) selected_a -=1;
		if(selected_a == selected_b && selected_a<(numero_cromossomos-1) ) selected_a +=1;
		if(selected_a == selected_b && selected_a==(numero_cromossomos-1)) selected_a -=1;
		if(selected_a == selected_b && selected_a==0) selected_a +=1;
		
		cout<<endl<< "<><><><><><>  "<< i;
		crossover(pop[i], 4,pop[i+1],4);
		
	}
	
		//cout<< endl<< endl<< ">>>>>>>>>>>>>>>  "<< selected_b<<endl;
		
	

}


int main(){
	system("cls");
	srand(time(NULL));		

//VALORES DEFINIDOS PARA INICIALIZAÇÃO
	int numero_cromossomos = 10;//numero de individuos
	int tamanho_pai=10;//numero de genes
	//int pop[numero_cromossomos][tamanho_pai]; inicializando a matriz de elementos
	int **pop;
	pop = new int *[numero_cromossomos];
	for(int i = 0; i <10; i++)
    pop[i] = new int[tamanho_pai];	


	//int pai_1[tamanho_pai];
	//int pai_2[tamanho_pai];
	
	//inicialização de teste
	//testando crossover
	//crossover(pai_1,tamanho_pai,pai_2,tamanho_pai);	
	//mutacao(pai_1,tamanho_pai);
	//mutacao(pai_2,tamanho_pai);
	
	//cout << "depois" << endl;
	/*for(int i=0; i< qtd_genes; i++)
		cout << "gene" << i+1 << ": " << cromossomo[i] << endl;
	*/
	
	
	
	inicia_populacao(pop,numero_cromossomos,tamanho_pai,3);
	imprime_populacao(pop,numero_cromossomos,tamanho_pai);
	
		
	//inicia o loop
	int * fitness;
	float * pesos;

	fitness = calcula_fitness(pop,numero_cromossomos,tamanho_pai);
	imprime_vetor(fitness, numero_cromossomos);
	
	pesos = calcula_pesos(fitness,numero_cromossomos);
	
	imprime_vetorf(pesos,numero_cromossomos);
	
	//a soma TEM que dar 1, ou seja 100%
	cout<< soma_vetorf(pesos,numero_cromossomos);
	
	
	seleciona_cruza(pop,fitness,numero_cromossomos);
	
	imprime_matriz(pop,numero_cromossomos,tamanho_pai);
	free(fitness);
	free(pesos);
	//FIM DO LOOP PRINCIPAL 
	// FELIPE para COTRIM, ADICIONAR CRITERIO DE PARADA APENAS!!!! provavelmente será apenas numero de gerações.
return 0;
}






