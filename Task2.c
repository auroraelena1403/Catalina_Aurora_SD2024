#include<stdio.h>
#include<malloc.h>
#define _CRT_SECURE_NO_WARNINGS 
//construirea structurii
struct Acvariu
{
    char* numeAcvariu;
    float pretBilet;
    int nrVizitatori;
};

struct Acvariu initializeazaAcvariu(const char* numeAcvariu, float pretBilet, int nrVizitatoti) {
    struct Acvariu acvariu;
    acvariu.numeAcvariu = (char*)malloc((strlen(numeAcvariu) + 1) * sizeof(char));
    strcpy(acvariu.numeAcvariu, numeAcvariu);
    acvariu.pretBilet = pretBilet;
    acvariu.nrVizitatori = nrVizitatoti;
    return acvariu;
}
void afiseazaAcvariu(struct Acvariu acvariu) {
    printf("\nAcvariul %s are un nr de vizitatori de  %d si pretul unui bilet este de %f lei\n", acvariu.numeAcvariu, acvariu.nrVizitatori, acvariu.pretBilet);

}
//functie citire de la tastatura
struct Acvariu citireInput() {
    struct Acvariu acvariuInput;
    char nume[256];
    float pret;
    int nrViz;
    printf("\nIntroduceti numele acvariului: \n");
    fgets(nume, 256, stdin);
    printf("\nIntroduceti pretul unei vizite a acvariului: \n");
    scanf_s("%f", &pret);
    printf("\nIntroduceti numarul de vizitatori ai acvariului: \n");
    scanf_s("%d", &nrViz);
    acvariuInput = initializeazaAcvariu(nume, pret, nrViz);
    return acvariuInput;


}
//functie de calcul
int calculeazaProfit(struct Acvariu acvariu) {
    int profit;
    profit = acvariu.nrVizitatori * acvariu.pretBilet;
    return profit;
}

//functie de modificare al unui camp din obiect
void modificaCamp(struct Acvariu* acvariu, const char* numeNou) {
    if (numeNou) {
        acvariu->numeAcvariu = numeNou;
    }
    else {
        printf("Nume inexistent!");
    }

}
//functie care afiseaza un vector cu obiecte.
void afisareVector(struct Acvariu* acvariuVector, int nrAcvarii) {
    if (acvariuVector != NULL) {
        for (int i = 0; i < nrAcvarii; i++) {
            afiseazaAcvariu(acvariuVector[i]);
        }
    }
}
//functie care va creea un nou vector în care va copia dintr-un vector primit ca parametru obiectele care indeplinesc o anumita conditie
void acvariiCuPretRezonabil(struct Acvariu* acvariu, int nrAcvarii, struct Acvariu** acvariiRezultate, int* nrAcvariiRezultate, float pretDorit) {
    if (*acvariiRezultate != NULL) {
        printf("Vectorul gol contine elemenere!");
    }
    else {
        *nrAcvariiRezultate = 0;
    }
    for (int i = 0; i < nrAcvarii; i++) {
        if (acvariu[i].pretBilet < pretDorit) {
            (*nrAcvariiRezultate)++;
        }
    }
    *acvariiRezultate = (struct Acvariu*)malloc(sizeof(struct Acvariu*) * (*nrAcvariiRezultate));
    int contor = 0;
    for (int i = 0; i < nrAcvarii; i++) {
        if (acvariu[i].pretBilet < pretDorit) {
            (*acvariiRezultate)[contor++] = initializeazaAcvariu(acvariu[i].numeAcvariu, acvariu[i].pretBilet, acvariu[i].nrVizitatori);
        }
    }
}

//concatenare vectori
struct Acvariu* concatenareVect(struct Acvariu* acv1, struct Acvariu* acvrariu2, int dim1, int dim2) {
    if (dim1 == 0 || dim2 == 0) {
        printf("Unul din vectori este gol!");
    }
    int dimNoua = dim1 + dim2;
    struct Acvariu* acvariuConcatenat = (struct Acvariu*)malloc(sizeof(struct Acvariu) * dimNoua);
    for (int i = 0; i < dim1; i++) {
        acvariuConcatenat[i] = acv1[i];
    }
    for (int j = 0; j < dim2; j++) {
        acvariuConcatenat[j + dim1] = acvrariu2[j];
    }
    return acvariuConcatenat;
}

void main() {
    struct Acvariu acvariu1 = initializeazaAcvariu("Pesti fericiti", 10, 17.4);
    afiseazaAcvariu(acvariu1);
    //struct Acvariu acvInp = citireInput();
    //afiseazaAcvariu(acvInp);
    int profit = calculeazaProfit(acvariu1);
    printf("\nProfitul zilnic, in medie, al acvariului este de %d lei\n", profit);
    modificaCamp(&acvariu1, "AcvariuRedenumit");
    afiseazaAcvariu(acvariu1);

    //vector de obiecte
    printf("\nVector de obiecte: \n");
    int nrAcvarii = 5;
    struct Acvariu* acvarii = (struct Acvariu*)malloc(sizeof(struct Acvariu) * 5);
    for (int i = 0; i < nrAcvarii; i++) {
        acvarii[i] = initializeazaAcvariu("Pesti fericiti", 102 + i, 13);
    }
    afisareVector(acvarii, nrAcvarii);
    //vector obiecte rezultate care trebuie sa fie nou
    struct Acvariu* acvariiCuPretOk = NULL;
    int* acvariiRez;
    acvariiCuPretRezonabil(acvarii, 5, &acvariiCuPretOk, &acvariiRez, 104);
    printf("\nVector de acvarii cu pret sub 104 lei: \n");
    afisareVector(acvariiCuPretOk, acvariiRez);

    struct Acvariu* acvariuConcat = (struct Acvariu*)malloc(sizeof(struct Acvariu) * 5);
    int dimAcvRez = acvariiRez;
    acvariuConcat = concatenareVect(acvarii, acvariiCuPretOk, nrAcvarii, dimAcvRez);
    printf("\nVector concatenat: \n");
    afisareVector(acvariuConcat, nrAcvarii + dimAcvRez);


}
