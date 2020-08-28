#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"genetic.h"

int main()
{
    srand(time(NULL));

    popSent popS; //sentinela da população

    popS.popSize = 400; //tamanho da população
    popS.geration = 0; // flag de primeira geração
    int max_generations = 100;  // quantidade de gerações
    popS.individuals = creat_population(popS.popSize);
    int k = popS.popSize/5;  // tamanho da seleção da reprodução
    indiv *in = calloc(k, sizeof(indiv));

    char goal[] = "Alo Alo Alo"; // String objetivo

    for(int i=0; i<max_generations; i++){ // gera cada geração
        printf("\n----- Generation: %d -------------------------------------------------------------------", i+1);
        generation_management(&popS, goal, &in, k);
    }
    free(in);
    free(popS.individuals);
    return 0;

}
