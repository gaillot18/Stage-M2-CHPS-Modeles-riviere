# include <iostream>
# include <iomanip>
# include <cmath>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>


# include <mpi.h>


# include "../../../../Fonctions-communes/Librairies/1.hpp"
# include "../../../Fonctions-communes/Librairies/1.hpp"
# include "../../Librairies/volume-fini-rusanov-mpi.hpp"


# define idx(k, n) ((n) * (K + 2) + (k))
# define idx_divise(k, n) ((n) * (K_divise + 2) + (k))


// Variables globales
int numero_processus;
int nombre_processus;
MPI_Comm communicateur_1d;
int dimension_communicateur_1d;
int numero_processus_communicateur_1d;
int voisin[2];
int nombre_bord_libre;
int coins[4];
int etiquette = 1;
MPI_Status statut;





// Programme principal
int main(int argc, char **argv){


    // Démarrage
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &numero_processus);
    MPI_Comm_size(MPI_COMM_WORLD, &nombre_processus);
    if (numero_processus == 0){
        std::cout << "——————————————————————————————————————————————————" << std::endl;
        std::cout << "Problème : Saint-Venant-cinematique" << std::endl;
        std::cout << "Version : volume-fini-rusanov-mpi" << std::endl;
        std::cout << "Nombre de processus = " << nombre_processus << std::endl;
    }


    // Déclaration des variables
    char message[512];
    int type_condition_limite_A;
    int type_condition_limite_Q;
    double CFL;
    double L_s;
    int K;
    double *Delta_s;
    double *s;
    double L_t;
    int N;
    double *Delta_t;
    double *t;
    double *b;
    double *b_prime;
    double *r;
    double *S_0;
    double *A_exact;
    double *Q_exact;
    double *A_initial;
    double *Q_initial;
    double *A;
    double *Q;
    double t_final;
    double *Delta_s_divise;
    double *b_divise;
    double *b_prime_divise;
    double *r_divise;
    double *S_0_divise;
    double *q_divise;
    double *v_divise;
    double *A_divise;
    double *Q_divise;
    int K_divise;
    int k_debut;
    int k_fin;
    int k_boucle_debut;
    int k_boucle_fin;
    int *deplacements;
    int *nombre_elements_recus;
    double temps_debut;
    double temps_fin;
    double temps_execution;
    double erreur_L2_A;
    double erreur_infinie_A;
    double erreur_L2_Q;
    double erreur_infinie_Q;
    char* nom_fichier_entree_type_condition_limite_A;
    char* nom_fichier_entree_type_condition_limite_Q;
    char* nom_fichier_entree_L_s;
    char* nom_fichier_entree_K;
    char* nom_fichier_entree_Delta_s;
    char* nom_fichier_entree_s;
    char* nom_fichier_entree_L_t;
    char* nom_fichier_entree_N;
    char* nom_fichier_entree_Delta_t;
    char* nom_fichier_entree_t;
    char* nom_fichier_entree_b;
    char* nom_fichier_entree_b_prime;
    char* nom_fichier_entree_r;
    char* nom_fichier_entree_S_0;
    char* nom_fichier_entree_A_exact;
    char* nom_fichier_entree_Q_exact;
    char* nom_fichier_entree_A_initial;
    char* nom_fichier_entree_Q_initial;
    char* nom_fichier_sortie_A;
    char* nom_fichier_sortie_Q;
    double resultats[6];
    const char *nom_fichier_sortie_resultat_performance;
    const char *entete;


    // Lecture des arguments
    CFL = atof(argv[1]);
    K = atoi(argv[2]);
    N = atoi(argv[3]);
    nom_fichier_entree_type_condition_limite_A = argv[4];
    nom_fichier_entree_type_condition_limite_Q = argv[5];
    nom_fichier_entree_L_s = argv[6];
    nom_fichier_entree_K = argv[7];
    nom_fichier_entree_Delta_s = argv[8];
    nom_fichier_entree_s = argv[9];
    nom_fichier_entree_L_t = argv[10];
    nom_fichier_entree_N = argv[11];
    nom_fichier_entree_Delta_t = argv[12];
    nom_fichier_entree_t = argv[13];
    nom_fichier_entree_b = argv[14];
    nom_fichier_entree_b_prime = argv[15];
    nom_fichier_entree_r = argv[16];
    nom_fichier_entree_S_0 = argv[17];
    nom_fichier_entree_A_exact = argv[18];
    nom_fichier_entree_Q_exact = argv[19];
    nom_fichier_entree_A_initial = argv[20];
    nom_fichier_entree_Q_initial = argv[21];
    nom_fichier_sortie_A = argv[22];
    nom_fichier_sortie_Q = argv[23];
    nom_fichier_sortie_resultat_performance = argv[24];


    // Initialisation d'une topologie cartésienne 1D
    creer_topologie();
    calculer_information_topologie();
    calculer_information_processus(
        K + 2,
        &K_divise,
        &k_debut,
        &k_fin
    );
    calculer_information_borne_boucle_espace(
        K_divise,
        0,
        0,
        &k_boucle_debut,
        &k_boucle_fin
    );
    calculer_information_regroupement_resultat(
        K + 2,
        &deplacements,
        &nombre_elements_recus
    );
    if (numero_processus == 0){
        std::cout << "Informations de chaque processus :" << std::endl;
    }
    MPI_Barrier(communicateur_1d);
    sprintf(
        message,
        "k_debut = %d, K_divise = %d, voisin[gauche] = %d, voisin[droite] = %d",
        k_debut,
        K_divise,
        voisin[0],
        voisin[1]
    );
    afficher_message_ordonne(message);


    // Initialisation des paramètres
    type_condition_limite_A = lire_valeur_int(
        nom_fichier_entree_type_condition_limite_A
    );
    type_condition_limite_Q = lire_valeur_int(
        nom_fichier_entree_type_condition_limite_Q
    );
    L_s = lire_valeur_double(
        nom_fichier_entree_L_s
    );
    K = lire_valeur_int(
        nom_fichier_entree_K
    );
    Delta_s = lire_tableau_double(
        nom_fichier_entree_Delta_s,
        K + 2
    );
    s = lire_tableau_double(
        nom_fichier_entree_s,
        K + 2
    );
    L_t = lire_valeur_double(
        nom_fichier_entree_L_t
    );
    N = lire_valeur_int(
        nom_fichier_entree_N
    );
    Delta_t = lire_tableau_double(
        nom_fichier_entree_Delta_t,
        N + 1
    );
    t = lire_tableau_double(
        nom_fichier_entree_t,
        N + 1
    );
    b = lire_tableau_double(
        nom_fichier_entree_b,
        K + 2
    );
    b_prime = lire_tableau_double(
        nom_fichier_entree_b_prime,
        K + 2
    );
    r = lire_tableau_double(
        nom_fichier_entree_r,
        K + 2
    );
    S_0 = lire_tableau_double(
        nom_fichier_entree_S_0,
        K + 2
    );
    A_initial = lire_tableau_double(
        nom_fichier_entree_A_initial,
        K + 2
    );
    Q_initial = lire_tableau_double(
        nom_fichier_entree_Q_initial,
        K + 2
    );
    if (numero_processus == 0){
        A_exact = lire_tableau_double(
            nom_fichier_entree_A_exact,
            (K + 2) * (N + 1)
        );
        Q_exact = lire_tableau_double(
            nom_fichier_entree_Q_exact,
            (K + 2) * (N + 1)
        );
    }
    else{
        A_exact = NULL;
        Q_exact = NULL;
    }
    A_divise = (double *)calloc((K_divise + 2) * (N + 1), sizeof(double));
    Q_divise = (double *)calloc((K_divise + 2) * (N + 1), sizeof(double));
    q_divise = (double *)calloc((K_divise + 2) * (N + 1), sizeof(double));
    v_divise = (double *)calloc((K_divise + 2) * (N + 1), sizeof(double));
    Delta_s_divise = (double *)calloc(K_divise + 2, sizeof(double));
    b_divise = (double *)calloc(K_divise + 2, sizeof(double));
    b_prime_divise = (double *)calloc(K_divise + 2, sizeof(double));
    r_divise = (double *)calloc(K_divise + 2, sizeof(double));
    S_0_divise = (double *)calloc(K_divise + 2, sizeof(double));
    initialiser_tableau_divise_1d(
        K,
        K_divise,
        k_debut,
        Delta_s,
        Delta_s_divise
    );
    initialiser_tableau_divise_1d(
        K,
        K_divise,
        k_debut,
        b,
        b_divise
    );
    initialiser_tableau_divise_1d(
        K,
        K_divise,
        k_debut,
        b_prime,
        b_prime_divise
    );
    initialiser_tableau_divise_1d(
        K,
        K_divise,
        k_debut,
        r,
        r_divise
    );
    initialiser_tableau_divise_1d(
        K,
        K_divise,
        k_debut,
        S_0,
        S_0_divise
    );
    initialiser_tableau_divise_2d(
        K, 
        K_divise,
        k_debut,
        A_initial,
        A_divise
    );
    initialiser_tableau_divise_2d(
        K, 
        K_divise, 
        k_debut, 
        Q_initial, 
        Q_divise
    );


    // Appel de la fonction de résolution
    MPI_Barrier(communicateur_1d);
    temps_debut = MPI_Wtime();
    resoudre_volume_fini_rusanov(
        type_condition_limite_A,
        type_condition_limite_Q,
        CFL,
        K_divise,
        k_boucle_debut,
        k_boucle_fin,
        Delta_s_divise,
        N,
        L_t,
        Delta_t,
        t,
        b_divise,
        r_divise,
        S_0_divise,
        q_divise,
        A_divise,
        Q_divise,
        &t_final
    );
    temps_fin = MPI_Wtime();


    // Regroupement des résultats
    regrouper_resultats(
        K,
        N,
        K_divise,
        deplacements,
        nombre_elements_recus,
        A_initial,
        Q_initial,
        A_divise,
        Q_divise,
        &A,
        &Q
    );


    // Calcul de l'erreur entre la solution exacte et la solution approchée
    if (numero_processus == 0){
        erreur_L2_A = calculer_norme_L2_vecteur_difference(
            A + N * (K + 2),
            A_exact + N * (K + 2),
            K + 2,
            Delta_s[1]
        );
        erreur_L2_Q = calculer_norme_L2_vecteur_difference(
            Q + N * (K + 2),
            Q_exact + N * (K + 2),
            K + 2,
            Delta_s[1]
        );
    }


    // Écriture des résultats du calcul dans un fichier
    // ...


    // Calcul et affichage des résultats de performances dans le terminal
    if (numero_processus == 0){
        temps_execution = temps_fin - temps_debut;
        std::cout << std::fixed << std::setprecision(0) << "K = " << K << std::endl;
        std::cout << std::fixed << std::setprecision(0) << "N = " << N << std::endl;
        std::cout << std::fixed << std::setprecision(5) << "A_final = " << std::endl;
        afficher_matrice(A, N, N + 1, 0, 10, K + 2);
        std::cout << std::fixed << std::setprecision(5) << "Q_final = " << std::endl;
        afficher_matrice(Q, N, N + 1, 0, 10, K + 2);
        std::cout << std::fixed << std::setprecision(10) << "t_final = " << t_final << std::endl;
        std::cout << std::fixed << std::setprecision(5) << "erreur_L2_A = " << erreur_L2_A << std::endl;
        std::cout << std::fixed << std::setprecision(5) << "erreur_L2_Q = " << erreur_L2_Q << std::endl;
        std::cout << std::fixed << std::setprecision(2) << "temps_execution = " << temps_execution << std::endl;
    }


    // Écriture des résultats de performances dans un fichier
    if (numero_processus == 0){
        resultats[0] = (double)3;
        resultats[1] = (double)-1;
        resultats[2] = (double)nombre_processus;
        resultats[3] = (double)K;
        resultats[4] = (double)N;
        resultats[5] = temps_execution;
        entete = "version,nombre_thread,nombre_processus,K,N,temps_execution";
        ecrire_resultat_performance(
            resultats,
            entete,
            6,
            nom_fichier_sortie_resultat_performance
        );
    }


    // Libération de la mémoire
    free(Delta_s);
    free(s);
    free(Delta_t);
    free(t);
    free(b);
    free(b_prime);
    free(r);
    free(S_0);
    free(A_initial);
    free(Q_initial);
    free(A_exact);
    free(Q_exact);
    free(A);
    free(Q);
    free(Delta_s_divise);
    free(b_divise);
    free(b_prime_divise);
    free(r_divise);
    free(S_0_divise);
    free(A_divise);
    free(Q_divise);
    free(q_divise);
    free(v_divise);
    free(deplacements);
    free(nombre_elements_recus);
    MPI_Finalize();


    return 0;


}