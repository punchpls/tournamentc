#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#define WINCOEF 10
#define LOSECOEF -10

struct results{
    int teamNumber;
    int points;
} *totalResults;

int n; //Amount of teams. Decided to leave simple n instead of any detailed name, seems 
//more readable for me

void arrangeTournament(struct results *totalResults, int *AmountArray, int coef);
void bubbleSort(struct results *totalResults, int n);


int main(int argc, char *argv[]){
    srand(time(NULL)); //wonderful C without normal random generator
    n = atoi(argv[1]);
    int teamAmount[n];
    totalResults = malloc(n * sizeof(struct results));
    arrangeTournament(totalResults, teamAmount, WINCOEF); //1st round of home games. Coefficient for win
    arrangeTournament(totalResults, teamAmount, LOSECOEF); //2nd round of home games. Coefficient for lose
    bubbleSort(totalResults, n); //sort the array of structures in order to arrange the sorted output
    //the array is not so difficult, I think it's ok to use bubblesort in this case
    for (int i = n - 1; i >= 0; i--){
        printf("%d -    %d\n", totalResults[i].teamNumber+1, totalResults[i].points); /* +1 in teamNumber 
        is added for appropriate output of team number*/
    }
    return 0;
}


void arrangeTournament(struct results *totalResults, int *AmountArray, int coef)
{
    for (int i = 0; i < n; i++){
        totalResults[i].teamNumber = i;
        for (int j = 0; j < n; j++){
            AmountArray[i] = (rand()%100) + coef;
            AmountArray[j] = rand()%100;
            if (i != j){
                if (AmountArray[i] == AmountArray[j]){
                    totalResults[i].points += 1;
                    totalResults[j].points += 1;
                }
                else if (AmountArray[i] > AmountArray[j]){
                    totalResults[i].points += 3;
                }
                else{
                    totalResults[j].points += 3;
                }
            }
        }
    }
    return;
}


void bubbleSort(struct results *totalResults, int n)
{
    struct results tmp;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (totalResults[j].points > totalResults[j+1].points)
            {
                tmp = totalResults[j];
                totalResults[j] = totalResults[j+1];
                totalResults[j+1] = tmp;
            }
        }
    }
    return;
}