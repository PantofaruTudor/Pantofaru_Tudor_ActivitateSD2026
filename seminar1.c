#include<stdio.h>
#include<stdlib.h>

struct Joc {
	int id;
	int nrJucatoriMin;
	char* denumire;
	float pret;
	char rating;
};

struct Joc initializare(int _id, int _nrJucatoriMin, char *_denumire, float _pret, char _rating) {
	struct Joc s;
	s.id = _id;
	s.nrJucatoriMin = _nrJucatoriMin;
	s.denumire = malloc(sizeof(char) * (strlen(_denumire)+1));
	strcpy(s.denumire, _denumire);
	s.pret = _pret;
	s.rating = _rating;
	return s;
}

void afisare(struct Joc s) {
	printf("\nId joc: %d", s.id);
	printf("\nNume: %s", s.denumire);
	printf("\nNumar minim de jucatori: %d", s.nrJucatoriMin);
	printf("\nPret: %5.2f", s.pret);
	printf("\nRating: %c", s.rating);
}

void modificaDenumire(struct Joc *s, char *_denumire) {
	free((*s).denumire);
	(*s).denumire = malloc(sizeof(char) * (strlen(_denumire) + 1));
	strcpy((*s).denumire, _denumire);
}

void dezalocare(struct Joc *s) {
	free(s->denumire);
}

float calcPretIndividual(struct Joc s){
	float pr;
	pr = s.pret/s.nrJucatoriMin;
	return pr;
}

int main() {
	struct Joc s;
	s = initializare(1, 2, "monopoly", 120, 'A');
	afisare(s);
	modificaDenumire(&s, "Secret Hitler");
	afisare(s);
	float pret;
	pret = calcPretIndividual(s);
	printf("\n%5.2f", pret);
	dezalocare(&s);
	return 0;
}