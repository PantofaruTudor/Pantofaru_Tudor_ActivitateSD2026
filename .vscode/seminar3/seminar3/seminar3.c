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
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	printf("\n ID Masina: %d", masina.id);
	printf("\n Nr Usi: %d", masina.nrUsi);
	printf("\n Pret: %f", masina.pret);
	printf("\n Model: %s", masina.model);
	printf("\n Numele Soferului: %s", masina.numeSofer);
	printf("\n Serie: %c\n", masina.serie);

}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0;i < nrMasini; i++)
		afisareMasina(masini[i]);
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	*(nrMasini)++;
	Masina* aux = malloc(sizeof(Masina) * (*nrMasini));
	for (int i = 0;i < (*nrMasini)-1;i++)
	{
		aux[i] = (*masini)[i]; //shallow copy
	}

	aux[*nrMasini - 1] = masinaNoua;
	free(*masini);
	*masini = aux;
}

Masina citireMasinaFisier(FILE* file) {
	char linie[50];
	fgets(linie, 50, file);

	char delim[3] = ", \n";
	Masina masina;
	masina.id = atoi(strtok(linie, delim));
	masina.nrUsi = atoi(strtok(NULL, delim));
	masina.pret = atof(strtok(NULL, delim));
	char* model = strtok(NULL, delim);
	masina.model = malloc(sizeof(char) * (strlen(model) + 1));
	strcpy(masina.model, model);

	char* numeSofer= strtok(NULL, delim);
	masina.numeSofer= malloc(sizeof(char) * (strlen(numeSofer) + 1));
	strcpy(masina.numeSofer, numeSofer);

	char* serie = strtok(NULL, delim);
	masina.serie = serie[0];

	return masina;


}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	Masina* masini= NULL;
	*nrMasiniCitite = 0;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file))
	{
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	for (int i = 0;i < *nrMasini;i++)
	{
		free((*vector[i]).model);
		free((*vector[i]).numeSofer);
	}		
	free(vector);
}

int main() {

	Masina* masini;
	int nrMasini;
	masini = citireVectorMasiniFisier("masina.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);
	return 0;
}