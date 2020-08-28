#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void generate_random_solution(char* stringInput, int i); // gera novas soluções
int evaluate(char* stringInput, char* goal); // avalia a solução quanto menor o valor, melhor é a solução (até 0)
int check_if_valid_string(char* stringInput); // aceita apenas strings com letras e espaços
void mutate(char* stringInput); // Função para variar uma solução

int main()
{

    srand(time(NULL));

    char *best = calloc(31, sizeof(char));

    char new_solution[31];

    char string_input[31];

    do{
        printf("Type an input:(up to 30 characters and only letters)");
        scanf("%[^\n]s", string_input);
        getchar();
    }while(!check_if_valid_string(string_input));

    generate_random_solution(best, strlen(string_input));// inicialização com uma solução

    int best_score = evaluate( best, string_input), new_score;

    do {
        printf("\n----- Best score so far: %i ----- Best Solution: %s ------------ \n", best_score, best);

        if( !best_score ) // Teste se encontrou solução
            break;

        strcpy(new_solution, best);
        mutate(new_solution);

        new_score = evaluate(new_solution, string_input);

        if ( new_score < best_score) {
            strcpy( best, new_solution );
            best_score = new_score;
        }

    }while(1);

    free(best);

    return 0;
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

int check_if_valid_string(char* inputString)
{
    char* p = inputString;
    if ( p == NULL )
        return 0;

    while(*p){
        if(!((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || ( *p == ' ' ) ))
            return 0;
        p++;
    }

    return 1;
}

void mutate(char* stringInput) //  Função para variar uma solução
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = rand()%strlen(stringInput);
    stringInput[i] = alphabet[rand()%52];
}
