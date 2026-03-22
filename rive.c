#include <stdio.h>
#include <stdbool.h>

#define FERMIER 'F'
#define CHEVRE 'C'
#define LOUP 'L'
#define CHOU 'X'

void init(char rive[4]) {
    rive[0] = FERMIER;
    rive[1] = CHEVRE;
    rive[2] = LOUP;
    rive[3] = CHOU;
}

int present(char c,char rive[4]) {
    for (int i=0;i<4;i++) {
        if (rive[i] == c)
            return i;
    }
    return -1;
}

void supprimer(char c,char rive[4]) {
    for (int i=0;i<4;i++) {
        if (rive[i] == c) {
            rive[i] = '\0';
            return;
        }
    }
}

void inserer(char c,char rive[4]) {
    for (int i=0;i<4;i++) {
        if (rive[i] == '\0') {
            rive[i] = c;
            return;
        }
    }
}

bool est_valide(char rive[4]) {
    if (present(FERMIER,rive) != -1)
        return true;
    bool chevre = present(CHEVRE,rive) != -1;
    bool loup = present(LOUP,rive) != -1;
    bool chou = present(CHOU,rive) != -1;
    return !((chevre && chou)||(chevre && loup));
}

void deplacer(char element,char gauche[4],char droite[4]) {
    char *source,*destination;
    if (present(element,gauche) != -1) {
        source = gauche;
        destination = droite;
    } else if (present(element,droite) != -1) {
        source = droite;
        destination = gauche;
    } else {
        printf("Erreur: %c n'est pas trouve!\n",element);
        return;
    }

    if (element != FERMIER && present(FERMIER,source) == -1) {
        switch (element)
        {
        case 'C':
        printf("Erreur : le fermier doit etre sur la meme rive que la chevre pour la deplacer!\n");
            break;
        case 'L':
        printf("Erreur: le fermier doit etre sur la meme rive que le loup pour le deplacer!\n");
            break;
        case 'X':
        printf("Erreur: le fermier doit etre sur la meme rive que le chou pour le deplacer!\n");
            break;
        }
        return;
    }
    supprimer(element,source);
    inserer(element,destination);

    if (element != FERMIER) {
        supprimer(FERMIER,source);
        inserer(FERMIER,destination);
    }

    if (!est_valide(source) || !est_valide(destination)) {
        printf("Deplacement invalide! Cela creerait une situation dangereuse.\n");
        
        supprimer(element,destination);
        inserer(element,source);
        
        if (element != FERMIER) {
            supprimer(FERMIER,destination);
            inserer(FERMIER,source);
        }
    }
}

void afficher_rive(char rive[4],const char* nom) {
    printf("%s : ",nom);
    for (int i=0;i<4;i++) {
        if (rive[i] != '\0') {
            printf("[%c]",rive[i]);
        } else {
            printf("[ ]");
        }
    }
    printf("\n");
}

bool victoire(char rive[4]) {
    return (present(FERMIER,rive) != -1 && present(CHEVRE,rive) != -1 &&
            present(LOUP,rive) != -1 && present(CHOU,rive) != -1);
}

int main() {
    char gauche[4]={0};
    char droite[4]={0};
    
    init(gauche);
    
    printf("Jeu du fermier, de la chevre, du loup et du chou\n");
    printf("Objectif: faire passer tout le monde sur la rive droite\n");
    printf("Regles:\n");
    printf("- La chevre ne doit pas rester seule avec le chou\n");
    printf("- Le loup ne doit pas rester seul avec la chevre\n");
    printf("- Seul le fermier peut conduire le bateau\n\n");
    
    while (1) {
        afficher_rive(gauche,"Gauche");
        afficher_rive(droite,"Droite");
        
        if (victoire(droite)) {
            printf("\nFelicitations! Vous avez reussi!\n");
            break;
        }
        
        printf("\nQue voulez-vous faire?\n");
        printf("1. Deplacer le fermier seul\n");
        printf("2. Deplacer la chevre\n");
        printf("3. Deplacer le loup\n");
        printf("4. Deplacer le chou\n");
        printf("5. Quitter\n");
        printf("Votre choix: ");
        
        int choix;
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                deplacer(FERMIER,gauche,droite);
                break;
            case 2:
                deplacer(CHEVRE,gauche,droite);
                break;
            case 3:
                deplacer(LOUP,gauche,droite);
                break;
            case 4:
                deplacer(CHOU,gauche,droite);
                break;
            case 5:
                printf("Au revoir!\n");
                return 0;
            default:
                printf("Choix invalide!\n");
        }
        
        if (!est_valide(gauche)|| !est_valide(droite)) {
            printf("\nPerdu! Une regle a ete violee.\n");
            break;
        }
    }
    return 0;
}
