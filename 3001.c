#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>


struct teamRresults{
    int teamNumber;
    int points;
} *tournamentResults;

void createTeamList(struct teamRresults *tournamentResults, int totalTeams);
void arrangeTournament(struct teamRresults *tournamentResults, int totalTeams);
void bubbleSort(struct teamRresults *tournamentResults, int totalTeams);
void printFinalResults(struct teamRresults *tournamentResults, int totalTeams);
void gameSimulation(struct teamRresults *tournamentResults, int eventProbability, int i, int j);


int main(int argc, char *argv[]){
    srand(time(NULL)); //wonderful C without normal random generator
    int totalTeams = atoi(argv[1]);
    tournamentResults = malloc(totalTeams * sizeof(struct teamRresults));
	createTeamList(tournamentResults, totalTeams);
    arrangeTournament(tournamentResults, totalTeams); //1st round of home games. Coefficient for win
    arrangeTournament(tournamentResults, totalTeams); //2nd round of home games. Coefficient for lose
    bubbleSort(tournamentResults, totalTeams); //sort the array of structures in order to arrange the sorted output
    //the array is not so difficult, I think it's ok to use bubblesort in this case
	printFinalResults(tournamentResults, totalTeams);
    free(tournamentResults);
    return 0;
}


void createTeamList(struct teamRresults *tournamentResults, int totalTeams)
{
    for (int i = 0; i < totalTeams; i++){
        tournamentResults[i].teamNumber = i;
    }
    return;
}


void gameSimulation(struct teamRresults *tournamentResults, int eventProbability, int i, int j)
{
   
	if (eventProbability > 0 && eventProbability <= 33){/*1/3 of total probability for draw scenario*/
		tournamentResults[i].points += 1;
		tournamentResults[j].points += 1;
	}
	else if (eventProbability > 33 && eventProbability < 77){/*more than 1/3 of total probability 
	for home game scenario*/
		tournamentResults[i].points += 3;
	}
	else{ /*less than 1/3 of total probability for guest game scenario*/
		tournamentResults[j].points += 3;
	}
	return;
}


void arrangeTournament(struct teamRresults *tournamentResults, int totalTeams)
{
    int eventProbability;

    for (int i = 0; i < totalTeams; i++){
        for (int j = 0; j < totalTeams; j++){
            if (i != j){
                eventProbability = rand()%100;
                printf("%d\n", eventProbability);
		        gameSimulation(tournamentResults, eventProbability, i, j);
	            eventProbability = rand()%100;
	            printf("%d\n", eventProbability);
                gameSimulation(tournamentResults, eventProbability, i, j);
            }
        }
    }
    return;
}


void bubbleSort(struct teamRresults *tournamentResults, int totalTeams)
{
    struct teamRresults tmp;

    for (int i = 0; i < totalTeams; i++)
    {
        for (int j = 0; j < totalTeams; j++)
        {
            if (tournamentResults[j].points < tournamentResults[j+1].points)
            {
                tmp = tournamentResults[j];
                tournamentResults[j] = tournamentResults[j+1];
                tournamentResults[j+1] = tmp;
            }
        }
    }
    return;
}


void printFinalResults(struct teamRresults *tournamentResults, int totalTeams)
{
    for (int i = 0; i < totalTeams; i++){
        printf("%4d -    %4d\n", tournamentResults[i].teamNumber+1, tournamentResults[i].points); /* +1 in teamNumber 
        is added for appropriate output of team number*/
    }
	return;
}