# include <stdio.h>
# include <stdlib.h>





// Libération de la partie gauche ou droite d'un vecteur
void liberer_partie_vecteur(
    int direction,
    int nombre_element_libere,
    int taille_vecteur_ancien,
    double **vecteur_ptr
){


    int nouvelle_taille;
    double *vecteur;
    double *vecteur_temporaire;
    nouvelle_taille = taille_vecteur_ancien - nombre_element_libere;
    vecteur = *vecteur_ptr;
    vecteur_temporaire = (double *)malloc(nouvelle_taille * sizeof(double));


    if (direction == 0){
        for (int i = 0 ; i < nouvelle_taille ; i ++){
            vecteur_temporaire[i] = vecteur[i + nombre_element_libere];
        }
    }
    else if (direction == 1){
        for (int i = 0 ; i < nouvelle_taille ; i ++){
            vecteur_temporaire[i] = vecteur[i];
        }
    }


    free(vecteur);
    *vecteur_ptr = vecteur_temporaire;


    return;


}