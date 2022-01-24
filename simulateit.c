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

void arrangeTournament(struct results *totalResults, int coef, int totalTeams);
void bubbleSort(struct results *totalResults, int totalTeams);


int main(int argc, char *argv[]){
    srand(time(NULL)); //wonderful C without normal random generator
    int totalTeams = atoi(argv[1]);
    totalResults = malloc(totalTeams * sizeof(struct results));
    arrangeTournament(totalResults, WINCOEF, totalTeams); //1st round of home games. Coefficient for win
    arrangeTournament(totalResults, LOSECOEF, totalTeams); //2nd round of home games. Coefficient for lose
    bubbleSort(totalResults, totalTeams); //sort the array of structures in order to arrange the sorted output
    //the array is not so difficult, I think it's ok to use bubblesort in this case
    for (int i = 0; i < totalTeams; i++){
        printf("%d -    %d\n", totalResults[i].teamNumber+1, totalResults[i].points); /* +1 in teamNumber 
        is added for appropriate output of team number*/
    }
    return 0;
}


void arrangeTournament(struct results *totalResults, int coef, int totalTeams)
{
    int teamOneCoef;
    int teamTwoCoef;

    for (int i = 0; i < totalTeams; i++){
        totalResults[i].teamNumber = i;
        for (int j = 0; j < totalTeams; j++){
            teamOneCoef = (rand()%100) + coef;
            teamTwoCoef = rand()%100;
            if (i != j){
                if (teamOneCoef == teamTwoCoef){
                    totalResults[i].points += 1;
                    totalResults[j].points += 1;
                }
                else if (teamOneCoef > teamTwoCoef){
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


void bubbleSort(struct results *totalResults, int totalTeams)
{
    struct results tmp;

    for (int i = 0; i < totalTeams; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (totalResults[j].points < totalResults[j+1].points)
            {
                tmp = totalResults[j];
                totalResults[j] = totalResults[j+1];
                totalResults[j+1] = tmp;
            }
        }
    }
    return;
}