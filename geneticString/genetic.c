#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "genetic.h"

indiv *creat_population(int size_of_population)
{
    indiv *individuals = calloc(size_of_population, sizeof(struct individual));
    return individuals;
}

void generate_random_solution(char* stringInput, int i) //gera uma solução aleatoria
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alfabeto para gerar soluções
    char* p;
    p = stringInput;
    while(i){
        *p = alphabet[rand()%52];
        p++;
        i--;
    }
}

int evaluate(char* stringInput, char* goal) //Avalia o fitness com a distancia das letras em ascii
{
    int dist = 0;
    char* p1 = stringInput;
    char* p2 = goal;
    while (*p2){
        dist += abs(*p1 - *p2);
        p1++;
        p2++;
    }
    return dist;
}

void generation_management (popSent *popS, char *goal, indiv **in, int k) //Administra as gerações da popuação
{
    int i;
    popS->avgFitness = 0;
    if( popS->geration == 0 ){
        generate_random_solution(popS->individuals[0].solution, strlen(goal)); //primeiro individuo para inicializar a variavel de melhor solução e melhor fitness
        popS->individuals[0].fitness = evaluate(popS->individuals[0].solution, goal);
        strcpy(popS->best_solution, popS->individuals[0].solution);
        popS->best_fitness = popS->individuals[0].fitness;
        popS->avgFitness += popS->individuals[0].fitness;
        fill_best_individuals(in, k, &popS->individuals[0]);

        for(i=1; i<popS->popSize; i++){ //Gera Soluções para os individuos e os avalia na primeira solução
           generate_random_solution(popS->individuals[i].solution, strlen(goal));
           popS->individuals[i].fitness = evaluate(popS->individuals[i].solution, goal);
               if ( popS->individuals[i].fitness < popS->best_fitness) {
                    strcpy(popS->best_solution, popS->individuals[i].solution);
                    popS->best_fitness = popS->individuals[i].fitness;
                }
           popS->avgFitness += popS->individuals[i].fitness;
           fill_best_individuals(in, k, &popS->individuals[i]);
        }

    popS->geration = 1;
    }else {
        //char *aux;
        for(i=0; i<popS->popSize; i++){

            reproduction(*in, k, &popS->individuals[i], (int)strlen(goal));
            popS->individuals[i].fitness = evaluate(popS->individuals[i].solution, goal);
            if(popS->individuals[i].fitness != 0){

                /*aux = popS->individuals[i].solution;
                mutate(aux);
                    if (evaluate(aux, goal) < (popS->individuals[i].fitness )){
                        popS->individuals[i].fitness = evaluate(aux, goal);
                        strcpy(popS->individuals[i].solution, aux);
                    }*/
            if(rand() % 4 == 0){ //25% de ocorrer uma mutação
                mutate(popS->individuals[i].solution);
                popS->individuals[i].fitness = evaluate(popS->individuals[i].solution, goal);}
            }
            popS->avgFitness += popS->individuals[i].fitness;
            fill_best_individuals(in, k, &popS->individuals[i]);

            if ( popS->individuals[i].fitness < popS->best_fitness) {
                    strcpy(popS->best_solution, popS->individuals[i].solution);
                    popS->best_fitness = popS->individuals[i].fitness;
                }
        }
    }

    printf("\n----- Best fitness so far: %i ----- Best Solution: %s ----- Avg Fitness: %d -----\n", popS->best_fitness, popS->best_solution, popS->avgFitness/popS->popSize);

}

void mutate(char* stringInput) //muda apenas um caractere aleatorio
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = rand()%strlen(stringInput);
    stringInput[i] = alphabet[rand()%52];
}

void reproduction( indiv *in, int inSize, indiv *offspring, int i) // combina duas soluções e gera uma nova
{

    char *p1 = in[ rand()%inSize ].solution;
    char *p2 = in[ rand()%inSize ].solution;

    while(p1 == p2)
        p2 = in[ rand()%inSize ].solution;
    strcpy(offspring->solution, p1);
    p1 = offspring->solution;


    p1 += i/2;
    p2 += i/2;

    while(*p1) {
        *p1 = *p2;
        p1++;
        p2++;
    }
}

void fill_best_individuals(indiv **in, int array_size, indiv *key) // administra um vetor com 20% da população com os melhores fitness
{
    if( (*in)->solution[0] == '\0' ){
        **in = *key;
        return;
    }
    int i;

   if( ( (*in)[array_size - 1].solution[0]) != '\0' ){ //caso cheio

         if( key->fitness < (*in)->fitness ) {

            for(i=0; i<array_size; i++){

                if(i == array_size - 1){    //caso ultimo elemento
                    ( (*in)[array_size - 1] ) = *key;
                    break;
                }
                if(key->fitness <= (*in)[i+1].fitness){
                    (*in)[i] = (*in)[i+1];
                }else{
                    (*in)[i] = *key;
                break;
                }

            }
        }
        return;
    }
    indiv *aux = malloc(sizeof(indiv));
    for(i=0; i<array_size; i++){
        if((*in)[i].solution[0] == '\0' ){
            (*in)[i] = *key;
            break;
        }

        if((key->fitness > (*in)[i].fitness) ){
               *aux = (*in)[i];
               (*in)[i] = *key;
               *key = *aux;
               }
        }
    free(aux);
}


