#ifndef GENETIC_H_INCLUDED
#define GENETIC_H_INCLUDED


struct individual{
    char solution[31];
    int fitness;
};
typedef struct individual indiv;

struct pop_sentinel{
    indiv *individuals;
    int best_fitness;
    int geration;
    int popSize;
    int avgFitness;
    char best_solution[31];
};

typedef struct pop_sentinel popSent;

indiv *creat_population(int size_of_population); // aloca numero de individuos
void generate_random_solution(char* stringInput, int i); // gera uma solução aleatoria
int evaluate(char* stringInput, char* goal); // avalia uma solução, 0 é o objetivo
void mutate(char* stringInput); //muda apenas um caractere aleatorio
void reproduction(indiv *in, int inSize, indiv *offspring, int i); // combina duas soluções e gera uma nova
void generation_management (popSent *popS, char *goal, indiv **in, int k); //Administra as gerações da popuação
void fill_best_individuals(indiv **in, int array_size, indiv *key); // administra um vetor com 20% da população com os melhores fitness

#endif // GENETIC_H_INCLUDED
