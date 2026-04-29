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
	if (!fgets(linie, 50, file)) {
		Masina invalid = { -1, 0, 0, NULL, NULL, 0 };
		return invalid;
	}
	char delim[3] = ",\n";
	Masina masina;
	char* p = strtok(linie, delim);
	if (p == NULL) {
		Masina invalid = { -1, 0, 0, NULL, NULL, 0 };
		return invalid;
	}
	masina.id = atoi(p);

	p = strtok(NULL, delim);
	if (p == NULL) {
		Masina invalid = { -1, 0, 0, NULL, NULL, 0 };
		return invalid;
	}
	masina.nrUsi = atoi(p);

	p = strtok(NULL, delim);
	if (p == NULL) {
		Masina invalid = { -1, 0, 0, NULL, NULL, 0 };
		return invalid;
	}
	masina.pret = (float)atof(p);

	p = strtok(NULL, delim);
	if (p == NULL) {
		Masina invalid = { -1, 0, 0, NULL, NULL, 0 };
		return invalid;
	}
	masina.model = malloc(sizeof(char) * (strlen(p) + 1));
	strcpy(masina.model, p);
	
	p = strtok(NULL, delim);
	if (p == NULL) {
		free(masina.model);
		Masina invalid = { -1, 0, 0, NULL, NULL, 0 };
		return invalid;
	}
	masina.numeSofer = malloc(sizeof(char) * (strlen(p) + 1));
	strcpy(masina.numeSofer, p);

	p = strtok(NULL, delim);
	if (p == NULL) {
		free(masina.model);
		free(masina.numeSofer);
		Masina invalid = { -1, 0, 0, NULL, NULL, 0 };
		return invalid;
	}
	masina.serie = p[0];

	return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* f = fopen(numeFisier, "r");
	if (f == NULL || nrMasiniCitite == NULL) {
		return NULL;
	}

	Masina* vector = NULL;
	*nrMasiniCitite = 0;

	while (1) {
		Masina aux = citireMasinaFisier(f);
		if (aux.id == -1) {
			break;
		}
		adaugaMasinaInVector(&vector, nrMasiniCitite, aux);
	}

	fclose(f);
	return vector;
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	if(*vector==NULL || nrMasini== NULL || vector==NULL)
	return;
	for(int i=0;i<*nrMasini;i++)
	{
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
		
	}
free(*vector);
*vector=NULL;
*nrMasini=0;

}

int main() {
	int nr = 0;
	Masina* vector = citireVectorMasiniFisier("masina.txt", &nr);
	if (vector != NULL) {
		afisareVectorMasini(vector, nr);
		dezalocareVectorMasini(&vector, &nr);
	}
	afisareVectorMasini(vector, nr);
	return 0;
}