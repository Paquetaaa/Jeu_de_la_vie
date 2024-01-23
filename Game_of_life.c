#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define LONGUEUR 100
#define LARGEUR 150 //Taille de notre matrice de cellules
#define BACKGROUND '.' //Case vide
#define CELL 'o' //Cellule
#define TIME 10 // Temps actualisation 

typedef enum {
	DEAD,
	ALIVE,
} State;

typedef struct {
	State state;
} Cell;

Cell grid[LONGUEUR][LARGEUR] = {0}; //Tableau de cellules, initialisée a 0

void grid_update(){
	Cell new_grid[LONGUEUR][LARGEUR] = {0}; //Pour eviter de modifier la grille en cours de parcours et fausser la simulation on crée une nouvelle grille.
	for(size_t i = 0;i<LONGUEUR;i++){
		for(size_t j = 0;j<LARGEUR;j++){
			int Neighbor_count = 0;
			//On va essayer de régler les effets de bords
			if(i == 0 && j == 0){
				Neighbor_count = grid[i][j+1].state + grid[i+1][j].state + grid[i+1][j+1].state; //Up left corner
			}
			else if(i == LONGUEUR-1 && j == 0){
				Neighbor_count = grid[i][j+1].state + grid[i-1][j].state + grid[i-1][j+1].state;  //Bottom left corner
			}
			else if(i == LONGUEUR-1 && j == LARGEUR-1){
				Neighbor_count = grid[i][j-1].state + grid[i-1][j-1].state + grid[i-1][j].state;  //Bottom Right corner
			}
			else if(i == 0 && j == LARGEUR-1){
				Neighbor_count = grid[i][j-1].state + grid[i+1][j-1].state + grid[i+1][j].state;  //Top Right corner
			}
			else if(i == 0 && (j !=0 && j!= LARGEUR-1)){ //Ligne 0
				Neighbor_count = grid[i][j-1].state + grid[i+1][j-1].state +grid[i+1][j].state +grid[i+1][j+1].state +grid[i][j+1].state;
			}
			else if(i == LONGUEUR-1 && (j !=0 && j!= LARGEUR-1)){//Ligne LONGUEUR-1
				Neighbor_count = grid[i][j-1].state + grid[i-1][j-1].state +grid[i-1][j].state +grid[i-1][j+1].state +grid[i][j+1].state;
			}
			else if(j == 0 && (i !=0 && i!= LONGUEUR-1)){//Colone 0
				Neighbor_count = grid[i-1][j].state + grid[i-1][j+1].state +grid[i][j+1].state +grid[i+1][j+1].state +grid[i+1][j].state;
			}
			else if(j == LARGEUR-1 && (i !=0 && i!= LONGUEUR-1)){//Colone LARGEUR-1
				Neighbor_count = grid[i-1][j].state + grid[i-1][j-1].state +grid[i][j-1].state +grid[i+1][j-1].state +grid[i+1][j].state;
			}
			else{ //Cases centrales 
			Neighbor_count = grid[i-1][j].state + grid[i-1][j-1].state + grid[i][j-1].state + grid[i][j+1].state + grid[i-1][j+1].state + grid[i+1][j+1].state + grid[i+1][j-1].state + grid[i+1][j].state;  
			}
			//On dirait que ça fonctionne 
			if(grid[i][j].state == ALIVE){
				if(Neighbor_count<2){
					new_grid[i][j].state = DEAD; //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
				}
				else if(Neighbor_count == 2 || Neighbor_count == 3){
					new_grid[i][j].state = ALIVE; //Any live cell with two or three live neighbours lives on to the next generation.
				}
				else if(Neighbor_count>3){
					new_grid[i][j].state = DEAD; //Any live cell with more than three live neighbours dies, as if by overpopulation.
				}
			} else{
				if(Neighbor_count == 3){
					new_grid[i][j].state = ALIVE; //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
				}
			}
		}
	}
	for(size_t i = 0;i<LONGUEUR;i++){
        for(size_t j = 0;j<LARGEUR;j++){
            grid[i][j].state = new_grid[i][j].state;
        }
    }
}


void init_grid(){
	for(size_t i = 0;i<LONGUEUR;i++){
		for(size_t j = 0;j<LARGEUR;j++){
			if(rand() % 2 == 0 && rand() %10 == 0){
				grid[i][j].state = ALIVE;
				continue;
			}
			grid[i][j].state = DEAD;
		}
	}
}

int print_grid(){
	int alive_cell_count = 0;

	for(size_t i = 0;i<LONGUEUR;i++){
		for(size_t j = 0;j<LARGEUR;j++){
			if(grid[i][j].state == ALIVE){
				alive_cell_count += 1;
				printf("%c",CELL);
			}
			else{
				printf("%c",BACKGROUND);
			}
				
		}
		printf("\n");
		
	}
	return alive_cell_count;


}
int main() {
	srand(time(NULL));

	//Permet de generer une grille aléatoire : 
	//init_grid();

	//Permet de génerer un planeur

	/*
	grid[50][6].state = ALIVE;
	grid[50][7].state = ALIVE;
	grid[51][5].state = ALIVE;
	grid[51][7].state = ALIVE;
	grid[52][7].state = ALIVE;
	*/

	//Permet de génerer un vaisseau léger
	/*
	grid[50][6].state = ALIVE;
	grid[50][7].state = ALIVE;
	grid[50][8].state = ALIVE;
	grid[51][5].state = ALIVE;
	grid[51][8].state = ALIVE;
	grid[52][8].state = ALIVE;
	grid[53][5].state = ALIVE;
	grid[53][7].state = ALIVE;
	grid[53][8].state = ALIVE;
	grid[54][5].state = ALIVE;
	grid[54][6].state = ALIVE;
	grid[54][7].state = ALIVE;
	grid[54][8].state = ALIVE;
	*/

	//Permet de generer un clignotant
	/*
	grid[50][6].state = ALIVE;
	grid[50][7].state = ALIVE;
	grid[50][8].state = ALIVE;
	*/




	//Permet de génerer un canon à planeurs
	
	
	grid[50][6].state = ALIVE;
	grid[50][7].state = ALIVE;
	grid[51][6].state = ALIVE;
	grid[51][7].state = ALIVE;
	grid[60][6].state = ALIVE;
	grid[60][7].state = ALIVE;
	grid[60][8].state = ALIVE;
	grid[61][5].state = ALIVE;
	grid[61][9].state = ALIVE;
	grid[62][4].state = ALIVE;
	grid[62][10].state = ALIVE;
	grid[63][4].state = ALIVE;
	grid[63][10].state = ALIVE;
	grid[64][7].state = ALIVE;
	grid[65][5].state = ALIVE;
	grid[65][9].state = ALIVE;
	grid[66][6].state = ALIVE;
	grid[66][7].state = ALIVE;
	grid[66][8].state = ALIVE;
	grid[67][7].state = ALIVE;
	grid[70][4].state = ALIVE;
	grid[70][5].state = ALIVE;
	grid[70][6].state = ALIVE;
	grid[71][4].state = ALIVE;
	grid[71][5].state = ALIVE;
	grid[71][6].state = ALIVE;
	grid[72][3].state = ALIVE;
	grid[72][7].state = ALIVE;
	grid[74][2].state = ALIVE;
	grid[74][3].state = ALIVE;
	grid[74][7].state = ALIVE;
	grid[74][8].state = ALIVE;
	grid[84][4].state = ALIVE;
	grid[84][5].state = ALIVE;
	grid[85][4].state = ALIVE;
	grid[85][5].state = ALIVE;
	




	while(print_grid() != 0){
		usleep(TIME*1000); //Temps d'attente avant nouvelle génération 
		grid_update(); //Nouvelle génération
		system("clear");
	};

}



