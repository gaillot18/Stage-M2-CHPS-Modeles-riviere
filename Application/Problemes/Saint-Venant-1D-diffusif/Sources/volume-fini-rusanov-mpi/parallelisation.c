# include <stdio.h>
# include <stdlib.h>
# include <string.h>


# include <mpi.h>


# include "../../Librairies/volume-fini-rusanov-mpi.hpp"


# define idx(k, n) ((n) * (K + 2) + (k))
# define idx_divise(k, n) ((n) * (K_divise + 2) + (k))





// Affichage un message ordonné
void afficher_message_ordonne(
    char *message
){


    for (int i = 0 ; i < nombre_processus ; i ++){
        if (numero_processus == i){
            printf("numero_processus = %d, %s\n", numero_processus, message);
        }
        MPI_Barrier(communicateur_1d);
    }


    return;


}





// Création de la topologie cartésienne 1D
void creer_topologie(){


    int tore = 0;
    dimension_communicateur_1d = 0;


    MPI_Dims_create(
        nombre_processus,
        1,
        &dimension_communicateur_1d
    );
    MPI_Cart_create(
        MPI_COMM_WORLD,
        1,
        &dimension_communicateur_1d,
        &tore,
        0,
        &communicateur_1d
    );


    MPI_Barrier(communicateur_1d);


    return;

    
}





// Calcul des informations sur la topologie
void calculer_information_topologie(){


    MPI_Cart_coords(
        communicateur_1d,
        numero_processus,
        1,
        &numero_processus_communicateur_1d
    );
    MPI_Cart_shift(
        communicateur_1d,
        0,
        1,
        &(voisin[0]),
        &(voisin[1])
    );


    nombre_bord_libre = 2;
    for (int i = 0 ; i < 2 ; i ++){
        if (voisin[i] == -1){
            nombre_bord_libre --;
        }
    }


    MPI_Barrier(communicateur_1d);


    return;

    
}





// Calcul des informations sur le processus
void calculer_information_processus(
    int K,
    int *K_divise_ptr,
    int *k_debut_ptr,
    int *k_fin_ptr
){


    int K_divise;
    int k_debut;
    int k_fin;


    k_debut = (
        (numero_processus_communicateur_1d * K) / 
        dimension_communicateur_1d
    );
    k_fin = (
        ((numero_processus_communicateur_1d + 1) * K) / 
        dimension_communicateur_1d - 1
    );
    K_divise = k_fin - k_debut + 1;


    *K_divise_ptr = K_divise;
    *k_debut_ptr = k_debut;
    *k_fin_ptr = k_fin;


    MPI_Barrier(communicateur_1d);


    return;


}





// Calcul des informations sur les bornes de la boucle en espace
void calculer_information_borne_boucle_espace(
    int K_divise,
    int k_debut,
    int k_fin,
    int *k_boucle_debut_ptr,
    int *k_boucle_fin_ptr
){


    int k_boucle_debut;
    int k_boucle_fin;


    k_boucle_debut = 1;
    if (voisin[0] == -1){
        k_boucle_debut ++;
    }
    k_boucle_fin = K_divise + 1;
    if (voisin[1] == -1){
        k_boucle_fin --;
    }


    *k_boucle_debut_ptr = k_boucle_debut;
    *k_boucle_fin_ptr = k_boucle_fin;


    return;


}





// Calcul des informations sur le regroupement des résultats
void calculer_information_regroupement_resultat(
    int K,
    int **deplacements_ptr,
    int **nombre_elements_recus_ptr
){


    int *deplacements;
    int *nombre_elements_recus;


    if (numero_processus == 0){


        deplacements = (int *)malloc(nombre_processus * sizeof(int));
        nombre_elements_recus = (int *)malloc(nombre_processus * sizeof(int));


        for (int i = 0 ; i < nombre_processus ; i ++){
            int k_debut_i = (i * K) / nombre_processus;
            int k_fin_i = ((i + 1) * K) / nombre_processus - 1;
            int K_divise_i = k_fin_i - k_debut_i + 1;
            deplacements[i] = k_debut_i;
            nombre_elements_recus[i] = K_divise_i;
        }


    }
    else{


        deplacements = NULL;
        nombre_elements_recus = NULL;

        
    }


    *deplacements_ptr = deplacements;
    *nombre_elements_recus_ptr = nombre_elements_recus;


    return;


}




// Initialisation d'un tableau 1D divisé
void initialiser_tableau_divise_1d(
    int K,
    int K_divise,
    int k_debut,
    double *U,
    double *U_divise
){


    for (int k = 0 ; k < K_divise + 2 ; k ++){
        int k_reel = k_debut + k - 1;
        if (k_reel >= 0 && k_reel < K + 2){
            U_divise[k] = U[k_reel];
        }
    }


    return;


}





// Initialisation d'un tableau 2D divisé
void initialiser_tableau_divise_2d(
    int K,
    int K_divise,
    int k_debut,
    double *U_initial,
    double *U_divise
){


    for (int k = 1 ; k < K_divise + 1 ; k ++){
        int k_reel = k_debut + k - 1;
        U_divise[idx_divise(k, 0)] = U_initial[k_reel];
    }


    return;


}





// Communication des cellules fantômes
void communiquer_cellule_fantome(
    int K_divise,
    double *U_divise
){


    // Envoi gauche, reception droite
    MPI_Sendrecv(
        &(U_divise[1]),
        1,
        MPI_DOUBLE,
        voisin[0],
        etiquette,
        &(U_divise[K_divise + 1]),
        1,
        MPI_DOUBLE,
        voisin[1],
        etiquette,
        communicateur_1d,
        &statut
    );


    // Envoi droite, reception gauche
    MPI_Sendrecv(
        &(U_divise[K_divise]),
        1,
        MPI_DOUBLE,
        voisin[1],
        etiquette,
        &(U_divise[0]),
        1,
        MPI_DOUBLE,
        voisin[0],
        etiquette,
        communicateur_1d,
        &statut
    );


    return;


}


// Communication des cellules fantômes pour 2 tableaux
void communiquer_cellule_fantome_double(
    int K_divise,
    double *U_divise,
    double *V_divise
){


    double message_envoi_gauche[2];
    double message_envoi_droite[2];
    double message_reception_gauche[2];
    double message_reception_droite[2];


    // Définition des messages
    message_envoi_gauche[0] = U_divise[1];
    message_envoi_gauche[1] = V_divise[1];
    message_envoi_droite[0] = U_divise[K_divise];
    message_envoi_droite[1] = V_divise[K_divise];
    message_reception_gauche[0] = U_divise[0];
    message_reception_gauche[1] = V_divise[0];
    message_reception_droite[0] = U_divise[K_divise + 1];
    message_reception_droite[1] = V_divise[K_divise + 1];


    // Envoi gauche, reception droite
    MPI_Sendrecv(
        &message_envoi_gauche,
        2,
        MPI_DOUBLE,
        voisin[0],
        etiquette,
        &message_reception_droite,
        2,
        MPI_DOUBLE,
        voisin[1],
        etiquette,
        communicateur_1d,
        &statut
    );


    // Envoi droite, reception gauche
    MPI_Sendrecv(
        &message_envoi_droite,
        2,
        MPI_DOUBLE,
        voisin[1],
        etiquette,
        &message_reception_gauche,
        2,
        MPI_DOUBLE,
        voisin[0],
        etiquette,
        communicateur_1d,
        &statut
    );


    // Définition des messages de réception
    U_divise[0] = message_reception_gauche[0];
    V_divise[0] = message_reception_gauche[1];
    U_divise[K_divise + 1] = message_reception_droite[0];
    V_divise[K_divise + 1] = message_reception_droite[1];


    return;


}


// Regroupement des résultats
void regrouper_resultats(
    int K,
    int N,
    int K_divise,
    int *deplacements,
    int *nombre_elements_recus,
    double *A_initial,
    double *Q_initial,
    double *A_divise,
    double *Q_divise,
    double **A_ptr,
    double **Q_ptr
    ){


    double *A;
    double *Q;
    double *A_sans_fantome;
    double *Q_sans_fantome;
    double *A_divise_sans_fantome;
    double *Q_divise_sans_fantome;
    int *nombre_elements_recus_brut;
    int *deplacements_brut;
    int decalage;
    int decalage_brut;


    if (numero_processus == 0){
        A_sans_fantome = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
        Q_sans_fantome = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
        }
    else{
        A_sans_fantome = NULL;
        Q_sans_fantome = NULL;
    }


    A_divise_sans_fantome = (double *)malloc(K_divise * (N + 1) * sizeof(double));
    Q_divise_sans_fantome = (double *)malloc(K_divise * (N + 1) * sizeof(double));


    for (int n = 0 ; n < N + 1 ; n ++){
        for (int k = 0 ; k < K_divise ; k ++){
            A_divise_sans_fantome[n * K_divise + k] = A_divise[idx_divise(k + 1, n)];
            Q_divise_sans_fantome[n * K_divise + k] = Q_divise[idx_divise(k + 1, n)];
            }
        }


    if (numero_processus == 0){
        nombre_elements_recus_brut = (int *)malloc(nombre_processus * sizeof(int));
        deplacements_brut = (int *)malloc(nombre_processus * sizeof(int));
        decalage = 0;
        for (int i = 0 ; i < nombre_processus ; i ++){
            nombre_elements_recus_brut[i] = nombre_elements_recus[i] * (N + 1);
            deplacements_brut[i] = decalage;
            decalage += nombre_elements_recus_brut[i];
            }
        }
    else{
        nombre_elements_recus_brut = NULL;
        deplacements_brut = NULL;
    }


    // Regroupement des résultats
    MPI_Gatherv(
        A_divise_sans_fantome,
        K_divise * (N + 1),
        MPI_DOUBLE,
        A_sans_fantome,
        nombre_elements_recus_brut,
        deplacements_brut,
        MPI_DOUBLE,
        0,
        communicateur_1d
    );
    MPI_Gatherv(
        Q_divise_sans_fantome,
        K_divise * (N + 1),
        MPI_DOUBLE,
        Q_sans_fantome,
        nombre_elements_recus_brut,
        deplacements_brut,
        MPI_DOUBLE,
        0,
        communicateur_1d
    );


    free(A_divise_sans_fantome);
    free(Q_divise_sans_fantome);
    if (numero_processus == 0){
        free(nombre_elements_recus_brut);
        free(deplacements_brut);
        }


    // Réorganisation des valeurs espace-temps
    if (numero_processus == 0){
        A = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
        Q = (double *)malloc((K + 2) * (N + 1) * sizeof(double));


        decalage_brut = 0;
        for (int i = 0 ; i < nombre_processus ; i ++){
            int k_debut_i = deplacements[i];
            int K_divise_i = nombre_elements_recus[i];
            for (int n = 0 ; n < N + 1 ; n ++){
                for (int k = 0 ; k < K_divise_i ; k ++){
                    A[idx(k_debut_i + k, n)] = A_sans_fantome[decalage_brut + n * K_divise_i + k];
                    Q[idx(k_debut_i + k, n)] = Q_sans_fantome[decalage_brut + n * K_divise_i + k];
                    }
                }
            decalage_brut += K_divise_i * (N + 1);
            }


        free(A_sans_fantome);
        free(Q_sans_fantome);
        }
    else{
        A = NULL;
        Q = NULL;
    }


    *A_ptr = A;
    *Q_ptr = Q;


    return;


}
