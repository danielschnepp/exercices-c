#include <stdio.h>
#define SURFACE 100
#define MAX_UNIT 100

struct unit {
	int x;
	int player_id;
	char type;
	int utile;
};

int collision(struct unit a,struct unit b);
void affichage(char tab[]);
void new_unit(int player_id,char type,struct unit units[]);
int demande_tour(char *type1,char *type2, struct unit units[]);
void initialisation (struct unit tab[], char tabl[]);
void update(char tab[],struct unit units[]);
int fin(struct unit units[]);
int compte_unit(int player_id, struct unit units[]);
void delete(int i,struct unit units[]);

int main(){
	char tab[SURFACE] = {'_'};
	struct unit units[MAX_UNIT * 2];
	int tour = 0;
	int i;

	initialisation(units,tab);

	while (1){
		char type1 = 'a';
		char type2 = 'a';
		tour++;
		demande_tour(&type1,&type2,units);
		if (type1 != '0'){
			switch (type1){
				case 'a' : new_unit(0,'a',units);
						   break;
				case 'b' : new_unit(0,'b',units);
						   break;
				case 'c' : new_unit(0,'c',units);
						   break;
				default : printf("Attention, aucune unité pour le joueur 1 !!!\n");
			}
		}
		if (type2 != '0'){
			switch (type2){
				case 'a' : new_unit(1,'a',units);
						   break;
				case 'b' : new_unit(1,'b',units);
						   break;
				case 'c' : new_unit(1,'c',units);
						   break;
				default : printf("Attention, aucune unité pour le joueur 2 !!!\n");
			}
		}
		i = fin(units);
		if (i == 0){
			update(tab,units);
			affichage(tab);
		} else if (i == 1){
			printf("Victoire du joueur 1 !!!\n");
			return 1;
		} else if (i == 2){
			printf("Victoire du joueur 2 !!!\n");
			return 2;
		} else {
			printf("Erreur test fin !\n");
			return -1;
		}
	}
}

int collision(struct unit a,struct unit b){
	if (a.x == b.x) return 1;
	return 0;
}

void affichage(char tab[SURFACE]){
	int i;

	for (i = 0;i < SURFACE;i++){
		printf("%c", tab[i]);
	}
	printf("\n");
}

void new_unit(int player_id,char type,struct unit units[MAX_UNIT * 2]){
	int i;
	int oui = 0;
	
	for (i = 0;(i < MAX_UNIT * 2) && (oui == 0);i++){
		if (units[i].utile == 0){
			oui = 1;
			units[i].utile = 1;
			units[i].player_id = player_id;
			units[i].type = type;
			if (player_id == 0){
				units[i].x = 0;
			} else {
				units[i].x = SURFACE;
			}
		}
	}
}

int demande_tour(char *type1,char *type2, struct unit units[]){
	printf("Que voulez-vous faire ??? (a, b, c ou 0) : ");
	scanf("%c %c",type1,type2);
	if (compte_unit(0,units) >= MAX_UNIT){
		*type1 = '0';
	}
	if (compte_unit(1,units) >= MAX_UNIT){
		*type2 = '0';
	}
}

void initialisation(struct unit tab[], char tabl[]){
	int i;

	for (i = 0;i < MAX_UNIT * 2;i++){
		tab[i].utile = 0;
		tab[i].player_id = -1;
		tab[i].x = -1;
		tab[i].type = ' ';
	}
	for (i = 0;i < SURFACE;i++){
		tabl[i] = '_';
	}
}

void update (char tab[],struct unit units[]){
	int i;

	for (i = 0;i < MAX_UNIT * 2;i++){
		if (units[i].utile == 1){
			int j;
			int c = 0;
			for (j = 0;j < MAX_UNIT * 2;j++){
				if (j == i) continue;
				if (collision(units[j],units[i])){
					c++;
					switch (units[j].type){
						case 'a' : switch(units[i].type){
									    case 'b' : delete(i,units);
									    	       break;
										case 'c' : delete(j,units);
									   			   break;
										case 'a' :
										default : break;
								   }
								   break;
						case 'b' : switch(units[i].type){
									    case 'c' : delete(i,units);
									    	       break;
										case 'a' : delete(j,units);
									   			   break;
										case 'b' :
										default : break;
								   }
								   break;
						case 'c' : switch(units[i].type){
									    case 'a' : delete(i,units);
									    	       break;
										case 'b' : delete(j,units);
									   			   break;
										case 'c' :
										default : break;
								   }
								   break;
					}
				}
			}
			if (c != 0) continue;
			if (units[i].player_id == 0){
				units[i].x += 1;
			} else {
				units[i].x -= 1;
			}
		}
	}
}

int fin(struct unit units[]){
	int i;
	for (i = 0;i < MAX_UNIT * 2;i++){
		if ((units[i].x == SURFACE) && (units[i].player_id == 0)){
			return 1;
		} else if ((units[i].x == 0) && (units[i].player_id == 1)){
			return 2;
		}
	}

	return 0;
}

int compte_unit(int player_id,struct unit units[]){
	int i;
	int nb = 0;

	for (i = 0;i < MAX_UNIT * 2; i++){
		if (units[i].player_id == player_id) nb++;
	}

	return nb;
}

void delete(int i,struct unit units[]){

	while (i < MAX_UNIT * 2 - 1){
		units[i].player_id = units[i + 1].player_id;
		units[i].utile = units[i + 1].utile;
		units[i].x = units[i + 1].x;
		units[i].type = units[i + 1].type;
	}
	units[i].player_id = -1;
	units[i].utile = 0;
	units[i].x = -1;
	units[i].type = ' ';

	return;
}