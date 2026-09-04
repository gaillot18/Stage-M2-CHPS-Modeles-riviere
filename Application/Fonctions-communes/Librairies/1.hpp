# ifdef __cplusplus
extern "C"{
# endif





// ../Sources/calcul-matriciel.c
double calculer_norme_L2_vecteur_difference(
    double *vecteur_1,
    double *vecteur_2,
    int taille_vecteur,
    double distance_sous_intervalle
);


double calculer_norme_infinie_vecteur_difference(
    double *vecteur_1,
    double *vecteur_2,
    int taille_vecteur
);


double calculer_norme_L2_vecteur(
    double *vecteur,
    int taille_vecteur
);


double calculer_norme_infinie_vecteur(
    double *vecteur,
    int taille_vecteur
);





// ../Sources/entree-sortie.c
double *lire_tableau_double(
    const char *nom_fichier_entree_tableau_double,
    int nombre_element_tableau_double
);


void ecrire_tableau_double(
    const char *nom_fichier_sortie_tableau_double,
    double *tableau_double,
    int nombre_element_tableau_double
);


int lire_valeur_int(
    const char *nom_fichier_entree_valeur_int
);


void ecrire_valeur_int(
    const char *nom_fichier_sortie_valeur_int,
    int valeur_int
);


double lire_valeur_double(
    const char *nom_fichier_entree_valeur_double
);


void ecrire_valeur_double(
    const char *nom_fichier_sortie_valeur_double,
    double valeur_double
);


void ecrire_resultat_performance(
    double *resultat,
    const char *entete,
    int nombre_ligne_resultat,
    const char *nom_fichier_sortie_resultat
);





// ../Sources/traitement-tableau.c
void liberer_partie_vecteur(
    int direction,
    int nombre_element_libere,
    int taille_vecteur_ancien,
    double **vecteur_ptr
);



# ifdef __cplusplus
}
# endif
# ifdef __cplusplus



// ../Sources/affichage.cpp
void afficher_matrice(
    double *matrice,
    int x_minimum,
    int x_maximum,
    int y_minimum,
    int y_maximum,
    int nombre_colonne
);


void afficher_vecteur(
    double *vecteur,
    int x_minimum,
    int x_maximum
);



# endif