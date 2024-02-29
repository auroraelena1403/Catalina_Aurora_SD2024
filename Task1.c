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
    printf("\nAcvariul %s are un nr de vizitatori de  %d si pretul unui bilet este de %f lei", acvariu.numeAcvariu, acvariu.nrVizitatori, acvariu.pretBilet);

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

void main() {
    struct Acvariu acvariu1 = initializeazaAcvariu("Pesti fericiti", 102, 13.4);
    afiseazaAcvariu(acvariu1);
    struct Acvariu acvInp = citireInput();
    afiseazaAcvariu(acvInp);
    int profit = calculeazaProfit(acvariu1);
    printf("\nProfitul zilnic, in medie, al acvariului este de %d lei", profit);
    modificaCamp(&acvariu1, "AcvariuRedenumit");
    afiseazaAcvariu(acvariu1);


}
