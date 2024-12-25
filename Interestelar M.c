#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//As funções acompanham <nome da função> underline 'f' "_f"

int rng_f() //certo
{
	/* Utiliza a biblioteca <time.h> e <stdlib.h> para
	gerar números aleatórios de -100 até 100 que serão
	manipulados da forma que melhor servir-nos  */

    int sinal, change, a;

	    srand(time(NULL));
	    sinal = rand() %100;

	    if(sinal %2 == 0)
	    {
	        change = -1;
	    }
	    else
	    {
	        change = 1;
	    }

	    srand(time(NULL));
	    a = rand() %100;

	    a = a * change;

    return a;
}

double day_period_f (double Rp) //certo
{
    /* Função que calcula a duração do dia no planeta
	visitado em função do raio "Rp" do mesmo.  */

	double Tdia;

    	Tdia = (24 * Rp)/6000;

    return Tdia;
}

double period_f (double M) //certo
{
    /* Função que calcula o período das Ondas no planeta
	visitado em função da massa da matéria escura "M". */

	double T, G, c;

    	c = 3 * pow(10, 8);
    	G = 6.67 * pow(10, -11);

    	T = (2 * 3.14 * G * M)/(sqrt(5) * pow(c, 3));

    return T;
}

double waves_f(double Tdia, double Tondas) //certo
{
	double NOndas = (Tdia/Tondas);

	return NOndas;
}

double elapsed_time_f(double tp, double D, double M) //certo
{
	/* Tempo decorrido no planeta aonde estão em função de D e M  */

	double tt, G, c;

	c = 3 * pow(10, 8);
    G = 6.67 * pow(10, -11);

	tt = tp/sqrt(1 - ((2 * G * M)/(D * pow(c, 2))));

	return tt;
}

double MedMaxMin_f (double NOndas, double *Max, double *Min, double M)
{
	int i;

	double Med = 0, altura, H, p, G, c;

        G = 6.67 * pow(10, -11);
    	p = 5 * pow(10, 3);
    	c = 3 * pow(10, 8);

    	H =  (9 / ((4 * 3.14 * p * pow(G, 3) * pow(M, 2)) / pow(c, 6)));

        double variacao = H * 0.1;

    for(i=1; i < NOndas; i++){

        altura = H + H * rng_f()/1000;

        Med = Med + altura;

    }

    *Max = H + variacao;
    *Min = H - variacao;

    Med = Med/NOndas;

    return Med;

}

double BlackRadius_f (double M) //certo
{
    /*Função que calcula o raio do buraco negro em função da massa fornecida pelo arquivo.*/

    double G, c, Rsch;

		G = 6.67 * pow(10, -11);
    	c = 3 * pow(10, 8);

    	Rsch= 2 * G * M/pow(c, 2);
    return Rsch;
}

void tidalForce_f (double M, double Mp, double Rp, double D, double* ownGravity, double* tidalForce) //certo
{
    /*Função que calcula a força de maré, ponteiros foram utilizados para cópia por referência.*/

    double G;

    	G = 6.67 *pow(10, -11);

    	*ownGravity = ((G * Mp)/pow(Rp, 2));
    	*tidalForce = ((2 * G * M)/pow(D, 3));
}


int main()
{

    FILE* F1 = fopen("dados_entrada.txt", "r");
    if (F1==NULL){
        printf("erro ao executar o arquivo. abortando o programa.");
        exit(1); //finaliza o programa
    }
    double dg=0,M=0,R=0,Mp=0,Rp=0,D=0,tp=0;
    while(fscanf(F1, " %lf %lf %lf %lf %lf %lf %lf", &dg,&M,&R,&Mp,&Rp,&D,&tp) != EOF){


/*Tarefa 1 -  Verificar se o gato está vivo ou morto*/

	printf("Tarefa 1:\n");

	double catProb;
    int rng;                     //distancia do gato, probabilidade dele estar morto e randomizador

    catProb = (1/(1 + pow(M_E, -dg)));
    catProb = catProb * 100;
    printf("Probabilidade do gato morrer %.2lf %\n", catProb);

    srand(time(NULL));
    rng = rand() %100;

    if(rng <= catProb)
    {
       printf("Estado do gato: morto\n");
    }
    else
    {
       printf("Estado do gato: vivo\n");
    }

/*tarefa 2 - verificar se o planeta*/

    printf("\nTarefa 2:\n");

    double Rsch = BlackRadius_f(M);

	    printf("O raio de Schwarzchild: %.2lf\n",Rsch);
	    printf("Existe um buraco negro? ");

	    if(R > Rsch)
	    {
	        printf("sim\n");
	    }
	    if(R < Rsch)
	    {
	        printf("sim\n");
	    }

/*Tarefa 3*/

	printf("\nTarefa 3:\n");

	double tF, oG;

		tidalForce_f(M, Mp, Rp, D, &oG, &tF);

		printf("Forca de mare: %.2lf\n", tF);
		printf("Gravidade do planeta: %.2lf\n", oG);

	    if(oG > tF)
	    {
	        printf("Planeta resiste? sim\n");
	    }
	    else
	    {
	        printf("Planeta resiste? nao\n");
	    }

/*Tarefa 4*/
	printf("\nTarefa 4:\n");

	double wavesAdaymain, Tdia, Tondas, HOndas, Max, Min, Media;

        Tdia=day_period_f(Rp);

        Tondas=period_f(M);

		wavesAdaymain = waves_f(Tdia, Tondas);

		Media=MedMaxMin_f(wavesAdaymain, &Max, &Min, M);

		int ONDAS = wavesAdaymain;


		printf("Periodo das ondas: %.2lf\n", Tondas);

		printf("Duracao do dia: %.2lf\n", Tdia);

		printf("Numero de ondas por dia: %i\n", ONDAS);

		printf("Tamanho medio: %.2lf\n", Media);

		printf("Tamanho max: %.2lf\n", Max);

		printf("Tamanho min: %.2lf\n", Min);


/*Tarefa 5*/

	double elapsed;
		printf("\nTarefa 5:\n");

		elapsed = elapsed_time_f(tp, D, M);

		printf("Tempo transcorrido no planeta: %.2lf\n", tp);
		printf("Tempo transcorrido na terra: %.2lf\n", elapsed);

    }

fclose(F1);
getch();
return 0;
}
