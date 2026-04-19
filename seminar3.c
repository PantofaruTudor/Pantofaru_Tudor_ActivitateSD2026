#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina; //mereu cand intalneste masina sa stie ca este o structura de tip StructuraMasina

void afisareMasina(Masina masina) {
	printf("\nId masina: %d", masina.id);
	printf("\nNr usi: %d", masina.nrUsi);
	printf("\nPret: %f", masina.pret);
	printf("\nModel: %s", masina.model);
	printf("\nNume sofer: %s", masina.numeSofer);
	printf("\nSerie masina : %c", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for(int i = 0; i < nrMasini; i++){
		afisareMasina(*(masini + i));
	}
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	(*nrMasini)++;
	Masina* aux = malloc(sizeof(Masina) * (*nrMasini));
	for(int i = 0; i < (*nrMasini)-1; i++){
		aux[i] = (*masini)[i]; //dereferetniere + deplasare + dereferentiere (ultimele 2 pt index)
	}
	aux[(*nrMasini) - 1] = masinaNoua;
	free(*masini);
	*masini = aux;
}
 
Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
	char linie[50];
	fgets(linie, 50, file);
	char delim[3] = ",\n";
	Masina masina;
	masina.id = atoi(strtok(linie, delim));
	masina.nrUsi = atoi(strtok(NULL, delim));
	masina.pret = atof(strtok(NULL, delim));

	char* p = strtok(NULL, delim);
	masina.model = malloc(sizeof(char) * (strlen(p) + 1));
	strcpy(masina.model, p);
	
	p = strtok(NULL, delim);
	masina.numeSofer = malloc(sizeof(char) * (strlen(p) + 1));
	strcpy(masina.numeSofer, p);

	p = strtok(NULL, delim);
	masina.serie = p[0];

	return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {
	Masina masina1;
	FILE* file = fopen("masini.txt", "r");
	masina1 = citireMasinaFisier(file);
	afisareMasina(masina1);
	return 0;
}