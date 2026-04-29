#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod{
    struct Nod* stanga;
    struct Nod* dreapta;
    Masina masina;
};
typedef struct Nod Nod;


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


void adaugaMasinaInArbore(Nod** radacina ,Masina masinaNoua) {

    if(*radacina == NULL){
        Nod* nod = malloc(sizeof(Nod));
        nod->masina = masinaNoua;
        nod->dreapta = NULL;
        nod->stanga = NULL;
        *radacina = nod;
        return;
    }

    if (masinaNoua.id < (*radacina)->masina.id){
        adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
    }
    else
        adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
    


}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f= fopen(numeFisier, "r");
    Masina masina;
    Nod* radacina = NULL;
    while(!feof(f)){

        adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));

    }
    fclose(f);
    return radacina;
}

void afisareMasiniDinArbore(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere

    if(radacina){
        afisareMasiniDinArbore(radacina->stanga);
        afisareMasina(radacina->masina);
        afisareMasiniDinArbore(radacina->dreapta);
    }
}

// void afisarePostOrdine(Nod* radacina){

// }

void dezalocareArboreDeMasini(Nod** radacina) {
    if(radacina){
        dezalocareArboreDeMasini(&(*radacina)->stanga);
        dezalocareArboreDeMasini(&(*radacina)->dreapta);
    
        free((*radacina)->masina.model);
        free((*radacina)->masina.numeSofer);
        free((*radacina));

        *radacina == NULL;
    }



}

Masina getMasinaByID(Nod* radacina,int id) {
	Masina m;

    if(radacina){
        if (radacina->masina.id == id){
            m = radacina->masina;
            
            m.model = malloc(strlen(radacina->masina.model)+1);
            strcpy(m.model, radacina->masina.model);
        
            m.numeSofer= malloc(strlen(radacina->masina.numeSofer)+1);
            strcpy(m.numeSofer, radacina->masina.numeSofer);
        }
        else{
            if(radacina->masina.id <= id){
                m = getMasinaByID(radacina->dreapta,id);
            }
            else{
                m = getMasinaByID(radacina->stanga,id);
            }
        }

    }
    else{
        m.id = -1;
    }

	return m;
}

int determinaNumarNoduri(Nod* radacina) {
    if(radacina){
        int nrNoduriStanga = determinaNumarNoduri(radacina->stanga);
        int nrNoduriDreapta = determinaNumarNoduri(radacina->dreapta);
        return 1 + nrNoduriStanga + nrNoduriDreapta;
    }
    return 0;
}

int calculeazaInaltimeArbore(Nod* radacina) {
    if(radacina == NULL) return -1;
    else{
        return 1 + max(calculeazaInaltimeArbore(radacina->stanga), calculeazaInaltimeArbore(radacina->dreapta));
    }
}


float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {

    Nod* arbore = citireArboreDeMasiniDinFisier("masini_arbore.txt");
    //afisareMasiniDinArbore(arbore);
    Masina masina = getMasinaByID(arbore, 5);
    afisareMasina(masina);

    dezalocareArboreDeMasini(&arbore);

	return 0;
}