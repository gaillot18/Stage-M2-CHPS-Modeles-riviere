# include <stdio.h>
# include <stdlib.h>


# define IDX(i, j, pas) ((i) * (pas) + (j))





// Lecture d'un vecteur depuis un fichier
double *lire_tableau_double(
    const char *nom_fichier_entree_tableau_double,
    int nombre_element_tableau_double
){


    FILE *descripteur;
    double *tableau_double;
    

    tableau_double = (double *)malloc(nombre_element_tableau_double * sizeof(double));
    descripteur = fopen(nom_fichier_entree_tableau_double, "rb");
    fread(tableau_double, sizeof(double), nombre_element_tableau_double, descripteur);
    fclose(descripteur);


    return tableau_double;


}





// Ecriture d'un vecteur dans un fichier
void ecrire_tableau_double(
    const char *nom_fichier_sortie_tableau_double,
    double *tableau_double,
    int nombre_element_tableau_double
){


    FILE *descripteur;
    

    descripteur = fopen(nom_fichier_sortie_tableau_double, "wb");
    fwrite(tableau_double, sizeof(double), nombre_element_tableau_double, descripteur);
    fclose(descripteur);


    return;


}





// Lecture d'un entier depuis un fichier
int lire_valeur_int(
    const char *nom_fichier_entree_valeur_int
){


    FILE *descripteur;
    int valeur_int;
    

    descripteur = fopen(nom_fichier_entree_valeur_int, "rb");
    fread(&valeur_int, sizeof(int), 1, descripteur);
    fclose(descripteur);


    return valeur_int;


}





// Ecriture d'un entier dans un fichier
void ecrire_valeur_int(
    const char *nom_fichier_sortie_valeur_int,
    int valeur_int
){


    FILE *descripteur;
    

    descripteur = fopen(nom_fichier_sortie_valeur_int, "wb");
    fwrite(&valeur_int, sizeof(int), 1, descripteur);
    fclose(descripteur);


    return;


}





// Lecture d'un double depuis un fichier
double lire_valeur_double(
    const char *nom_fichier_entree_valeur_double
){


    FILE *descripteur;
    double valeur_double;
    

    descripteur = fopen(nom_fichier_entree_valeur_double, "rb");
    fread(&valeur_double, sizeof(double), 1, descripteur);
    fclose(descripteur);


    return valeur_double;


}





// Ecriture d'un double dans un fichier
void ecrire_valeur_double(
    const char *nom_fichier_sortie_valeur_double,
    double valeur_double
){


    FILE *descripteur;
    

    descripteur = fopen(nom_fichier_sortie_valeur_double, "wb");
    fwrite(&valeur_double, sizeof(double), 1, descripteur);
    fclose(descripteur);


    return;


}





// Ecriture des résultats de performance dans un fichier csv
void ecrire_resultat_performance(
    double *resultat,
    const char *entete,
    int nombre_ligne_resultat,
    const char *nom_fichier_sortie_resultat_performance
){


    FILE *descripteur;
    long taille;


    descripteur = fopen(nom_fichier_sortie_resultat_performance, "a+");


    // Entête
    fseek(descripteur, 0, SEEK_END);
    taille = ftell(descripteur);
    if (taille == 0) {
        fprintf(descripteur, "%s\n", entete);
    }


    for (int i = 0 ; i < nombre_ligne_resultat ; i ++){
        fprintf(descripteur, "%.10f", resultat[i]);
        if (i < nombre_ligne_resultat - 1)
            fprintf(descripteur, ",");
    }
    fprintf(descripteur, "\n");


    fclose(descripteur);


    return;


}