#include<stdio.h>
#include<malloc.h>

struct Film {
	int id;
	int durata;
	char* nume;
	float buget;
	char varstaMinima;
};

struct Film initializare(int _id, int _durata, char* _nume, float _buget, char _varstaMinima) {
	struct Film s;
	s.id = _id;
	s.durata = _durata;
	s.nume = malloc(sizeof(char) * (strlen(_nume) + 1));
	strcpy(s.nume, _nume);
	s.buget = _buget;
	s.varstaMinima = _varstaMinima;
	return s;
}

struct Film copyFilm(struct Film s) {
	return initializare(s.id, s.durata, s.nume, s.buget, s.varstaMinima);
}

void afisare(struct Film s) {
	printf("Id: %d\n", s.id);
	printf("Durata: %d\n", s.durata);
	printf("Nume: %s\n", s.nume);
	printf("Buget: %.2f\n", s.buget);
	printf("Varsta minima: %d\n", s.varstaMinima);
}

void afisareVector(struct Film* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(*(vector + i));
		printf("\n");
	}
}

struct Film* copiazaPrimeleNElemente(struct Film* vector, int nrElemente, int nrElementeCopiate) {
	struct Film* vectorNou = malloc(sizeof(struct Film) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = copyFilm(vector[i]);
	}
	return vectorNou;
}

void dezalocare(struct Film** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].nume);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Film* vector, char nrElemente, float bugetMaxim, struct Film** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0;i < nrElemente;i++) {
		if (vector[i].buget < bugetMaxim)
			(*dimensiune)++;
	}
	(*vectorNou) = malloc(sizeof(struct Film) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget < bugetMaxim) {
			(*vectorNou)[k] = copyFilm(vector[i]);
			k++;
		}
	}
}

struct Film getPrimulElementConditionat(struct Film* vector, int nrElemente, const char* conditie) {
	//am iesit la activitate aici
	struct Film s;
	s.id = 1;

	return s;
}



int main() {
	struct Film f1 = initializare(1, 120, "Oppenheimer", 1000000, 18);
	int nrFilme = 3;
	struct Film* filme = malloc(sizeof(struct Film) * nrFilme);
	filme[0] = copyFilm(f1);
	*(filme + 1) = initializare(2, 150, "The Batman", 2000000, 16);
	filme[2] = initializare(3, 90, "The Flash", 1500000, 13);;
	afisareVector(filme, nrFilme);
	int nrFilmeCopiate = 2;
	struct Film* filmeCopiate = copiazaPrimeleNElemente(filme, nrFilme, nrFilmeCopiate);
	printf("Elemente copiate: \n");
	afisareVector(filmeCopiate, nrFilmeCopiate);
	//dezalocare(&filmeCopiate, &nrFilmeCopiate);
	struct Film* vectorIeftin;
	float prag = 1600000;
	int dimIeftin;
	copiazaAnumiteElemente(filme, nrFilme, prag, &vectorIeftin, &dimIeftin);
	afisareVector(vectorIeftin, dimIeftin);
	return 0;
}