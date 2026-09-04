# include <stdlib.h>
# include <math.h>


# define IDX(i, j, n) ((i) * (n) + (j))





// Calcul de la norme L2 de la différence de deux vecteurs
double calculer_norme_L2_vecteur_difference(
    double *vecteur_1,
    double *vecteur_2,
    int taille_vecteur,
    double distance_sous_intervalle
){



    double norme_L2_vecteur_difference;
    double difference;
    norme_L2_vecteur_difference = 0.0;


    for (int i = 0 ; i < taille_vecteur ; i ++){
        difference = vecteur_1[i] - vecteur_2[i];
        norme_L2_vecteur_difference += pow(difference, 2);
    }

    
    norme_L2_vecteur_difference = sqrt(distance_sous_intervalle * norme_L2_vecteur_difference);


    return norme_L2_vecteur_difference;


}






// Calcul de la norme infinie de la différence de deux vecteurs
double calculer_norme_infinie_vecteur_difference(
    double *vecteur_1,
    double *vecteur_2,
    int taille_vecteur
){


    double norme_infinie_vecteur_difference;
    double difference;
    norme_infinie_vecteur_difference = 0.0;


    for (int i = 0 ; i < taille_vecteur ; i ++){
        difference = fabs(vecteur_1[i] - vecteur_2[i]);
        if (difference > norme_infinie_vecteur_difference){
            norme_infinie_vecteur_difference = difference;
        }
    }


    return norme_infinie_vecteur_difference;


}





// Calcul de la norme L2 d'un vecteur
double calculer_norme_L2_vecteur(
    double *vecteur,
    int taille_vecteur
){


    double norme_L2_vecteur;
    norme_L2_vecteur = 0.0;


    for (int i = 0 ; i < taille_vecteur ; i ++){
        norme_L2_vecteur += pow(vecteur[i], 2);
    }
    

    norme_L2_vecteur = sqrt(norme_L2_vecteur);


    return norme_L2_vecteur;


}





// Calcul de la norme infinie d'un vecteur
double calculer_norme_infinie_vecteur(
    double *vecteur,
    int taille_vecteur
){


    double norme_infinie_vecteur;
    norme_infinie_vecteur = 0.0;


    for (int i = 0 ; i < taille_vecteur ; i ++){
        if (vecteur[i] > norme_infinie_vecteur){
            norme_infinie_vecteur = vecteur[i];
        }
    }


    return norme_infinie_vecteur;


}