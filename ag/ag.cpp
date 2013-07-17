#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#define qtd_genes 5
#define taxa_mutacao 5

using namespace std;

int infectadosAtual(int ** pop, int numero_cromossomos, int tamanho_pai)
{
	int infectados, n;
	infectados = 0;
	
	for(int i=0; i <numero_cromossomos;i++){
		n = 0;	
		for(int j=0;j<tamanho_pai;j++){
			n += pop[i][j];
		}
		if ( n > (tamanho_pai / 2) )
			infectados += 1;
		
	}
	
	return infectados;

}

void imprime_matriz(int ** matriz_pop , int numero_cromossomos, int tamanho_pai){
	cout<<endl;
	for(int i=0; i <numero_cromossomos;i++){
		cout<< "CROMOSSOMO"<< "<"<< i <<"> = ";
		for(int j=0;j<tamanho_pai;j++){
			cout<< matriz_pop[i][j] ;
		}
		cout<< endl;
	}


}


//copia a pop1 para pop2, apenas os valores e nao a referencia
void copia_matriz(int ** pop1, int ** pop2, int numero_cromossomos, int tamanho_pai){
	
	for(int i=0; i <numero_cromossomos;i++){
		//cout<< "CROMOSSOMO"<< "<"<< i <<"> = ";
		for(int j=0;j<tamanho_pai;j++){
			pop2[i][j] = pop1[i][j];
			
		}
		//cout<< endl;
	}
	
	
	
	//cout<<"#######################"<<endl;
	//imprime_matriz(pop1 , numero_cromossomos, tamanho_pai);
	//cout<<"-----------------------"<<endl;
	//imprime_matriz(pop2 , numero_cromossomos, tamanho_pai);
	//cout<<"#######################"<<endl;

}



//retorna um valor aleatorio entre 0 e o denominador

void copiaVetores( int * vetor, int * original, int tamanho)
{
	for(int i = 0; i < tamanho; i++)
	{
		vetor[i] = original[i];
	}

}

int valor_aleatorio(int denominador){
	int valor = rand();
	
	return valor%denominador;
}

void imprime_vetor(int * vetor, int tamanho){
	//cout<< "Imprimindo vetor: "<< endl;
	for(int i=0; i<tamanho;i++){
		cout<<"vetor["<<i<<"]= "<< vetor[i]<<endl;
	}

}
void imprime_vetorf(float * vetor, int tamanho){
	//cout<< "Imprimindo vetor: "<< endl;
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
	//cout<< endl<<"ponto cross pai 1>>" << ponto_cross_pai_1<<endl;
	//cout<< endl <<"ponto cross pai 2>> " << ponto_cross_pai_2<<endl;
	
	
	int vetor_1[ponto_cross_pai_1];//funciona como um buffer para nao perdermos informação do PAI_1
	//int vetor_2[ponto_cross_pai_2];
	
	//FELIPE>> acho que esse laço tem que vir depos de calcular o maiot ponto cross mas ok
	
	
	//BUG corrigido
	//cout<< "GENES TROCADOS"<<endl;
	for(int j=0; j <= ponto_cross_pai_1;j++){
		vetor_1[j]= pai_1[j];
		cout<<vetor_1[j]<< " ";
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
		//cout<< "INICIANDO população: "<< "<"<< i <<"> = "<<endl;
		for(int j=0;j<tamanho_pai;j++){
			matriz_pop[i][j]=0;
			//cout<< matriz_pop[i][j] ;
		}
		cout<< endl;
	}
	
	
	//inicializa com a quantidade de infectados totalmente
	cout<< "CROMOSSOMOS INFECTADOS>> ";
	for(int i=0; i<= (qtd_infect-1); i++){
		int rand = valor_aleatorio(numero_cromossomos+1);
				for(int j=0;j<tamanho_pai;j++){
				matriz_pop[rand][j] = valor_aleatorio(2);
				//matriz_pop[rand][j] = 1; //para uma infecção total do individuo
				}
				cout<<rand<<"  ";
	}
	cout<<endl;
}

//apenas imprime a população
void imprime_populacao(int ** matriz_pop,int numero_cromossomos, int tamanho_pai){
	numero_cromossomos -=1;
	for(int i=0; i <=numero_cromossomos;i++){
		cout<< "CROMOSSOMO"<< "<"<< i <<"> = ";
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
	
	//imprime_vetor(notas,numero_cromossomos);
	
	
	//cout <<endl<< "PASSOU"<<endl;
	
	return notas;
}
float *calcula_pesos(int * fitness , int numero_cromossomos){

	float * pesos = new float[numero_cromossomos];
	float soma_fitness = soma_vetor(fitness,numero_cromossomos);
	cout<<"Soma dos valores de fitness: "<<soma_fitness<<endl;
	for(int i=0; i<numero_cromossomos;i++){
		pesos[i]= ( 1 * fitness[i] )/soma_fitness;
		//cout<<pesos[i]<<endl;
	}
	
	
	return pesos;
}

//colocar e corrigir as matrizes, pois eles está utilizando a mesma e perdendo a referencia anterior ,
//quando na verdade deve se fazer uma copia antes de realizar as operações para que os valores do inicio nao sejam perdidos
void seleciona_cruza(int ** pop , int * fitness, int numero_cromossomos, int tamanho_pai){
	int aux=0;
	int selected_a=-1 , selected_b=-1;
	int first=0;
	int next = 0;
	int soma = soma_vetor(fitness,numero_cromossomos);
	
	//criando matriz temporaria
	int **pop2;
	pop2 = new int *[numero_cromossomos];
	for(int i = 0; i <numero_cromossomos; i++)
    pop2[i] = new int[tamanho_pai];	
	
	
	//cout<<"THAIANE FERREIRA BRAGA OWNA TODO MUNDO NO LOL"<<endl;
	copia_matriz(pop,pop2,numero_cromossomos,tamanho_pai);
	//pop[0][0]=126543;
	//pop2[3][0]=126543;
	
	
	//cout<<"#######################"<<endl;
	//imprime_matriz(pop , numero_cromossomos, tamanho_pai);
	//cout<<"-----------------------"<<endl;
	//imprime_matriz(pop2 , numero_cromossomos, tamanho_pai);
	//cout<<"#######################"<<endl;
	
	
	
	
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
		

		//if(selected_a == selected_b) cout<< endl <<"AAAAAAAAAAAAAAAAAAAAAAAAAA";
		//criterio de desempate
		if(selected_a == selected_b && selected_a>0 ) selected_a -=1;
		if(selected_a == selected_b && selected_a<(numero_cromossomos-1) ) selected_a +=1;
		if(selected_a == selected_b && selected_a==(numero_cromossomos-1)) selected_a -=1;
		if(selected_a == selected_b && selected_a==0) selected_a +=1;
		
		//cout<< endl<< endl<< "1 - >>>>>>>>>>>>>>>  "<< selected_a<<endl;
		//cout<< endl<< endl<< "2 - >>>>>>>>>>>>>>>  "<< selected_b<<endl;
		//cout<<endl<< "<><><><><><>  "<< i;
		
		int *filho_a;
		filho_a = new int[tamanho_pai];
		int *filho_b;
		filho_b = new int[tamanho_pai];
		
		//int filho_a[tamanho_pai];
		//int filho_b[tamanho_pai];
		
		copiaVetores(filho_a, pop2[selected_a], tamanho_pai);
		copiaVetores(filho_b, pop2[selected_b], tamanho_pai);
		

		if((rand()%101)==5){
			mutacao(filho_a, tamanho_pai);
			mutacao(filho_b, tamanho_pai);
			//cout<<"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
		}else
			crossover(filho_a, tamanho_pai,filho_b,tamanho_pai);
		
		//Alterando pop
		
		pop[i] = filho_a;
		pop[i+1] = filho_b;
		
		//cout<<endl;
		//imprime_matriz(pop,numero_cromossomos,tamanho_pai);
		//cout<<endl;



	}
	
		//cout<< endl<< endl<< ">>>>>>>>>>>>>>>  "<< selected_b<<endl;
		
	

}




int main(){
	system("cls");
	srand(time(NULL));		

//VALORES DEFINIDOS PARA INICIALIZAÇÃO
	int numero_cromossomos = 8;//numero de individuos
	int tamanho_pai=4;//numero de genes
	int qtd_infect = 5;
	ofstream file;
	file.open ("geracao_infect.txt");	
	int **pop;
	pop = new int *[numero_cromossomos];
	for(int i = 0; i <numero_cromossomos; i++)
    pop[i] = new int[tamanho_pai];// adicionar FLAG para infecção total ou randomica
	//int pop[numero_cromossomos][tamanho_pai]; inicializando a matriz de elementos
	//cout<< "Digite a quantidade de cromossomos: "<<endl; cin>> numero_cromossomos;
	//cout<< "Digite a quantidade de genes: "<<endl; cin>> tamanho_pai;
	//cout<< "Digite a quantidade de infectados: "<<endl; cin>> qtd_infect;
	


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
	
	
	
	inicia_populacao(pop,numero_cromossomos,tamanho_pai,qtd_infect);
	cout<<"Populacao Inicial: "<<endl;
	imprime_populacao(pop,numero_cromossomos,tamanho_pai);

	int * fitness;
	float * pesos;
	int geracao = 0;
	int geracao_max = 5;
	int total_infectados=0;
	
	
	//inicia o loop
	while(geracao!=geracao_max){

		cout<<"Fitness Calculados: "<<endl;
		fitness = calcula_fitness(pop,numero_cromossomos,tamanho_pai);
		imprime_vetor(fitness, numero_cromossomos);
	
		pesos = calcula_pesos(fitness,numero_cromossomos);
		cout<<"Pesos Calculados: "<<endl;
		imprime_vetorf(pesos,numero_cromossomos);
	
		//a soma TEM que dar 1, ou seja 100%	d .d dddd
		cout<<"Soma dos pesos: " <<soma_vetorf(pesos,numero_cromossomos)<<endl;
	
	
		seleciona_cruza(pop,fitness,numero_cromossomos, tamanho_pai);
		
		imprime_matriz(pop,numero_cromossomos,tamanho_pai);
	
		cout << "Geracao: "<< geracao << endl;
		cout << "Quantidade de infectados: " << infectadosAtual(pop, numero_cromossomos, tamanho_pai) << endl;
	
		total_infectados = infectadosAtual(pop, numero_cromossomos, tamanho_pai);
		file<<geracao<<" "<<total_infectados <<"\n";
		geracao++;

	}//FIM DO LOOP PRINCIPAL 
	
	
	file.close();
	free(pesos);
	free(fitness);
	// FELIPE para COTRIM, ADICIONAR CRITERIO DE PARADA APENAS!!!! provavelmente será apenas numero de gerações.
return 0;
}






