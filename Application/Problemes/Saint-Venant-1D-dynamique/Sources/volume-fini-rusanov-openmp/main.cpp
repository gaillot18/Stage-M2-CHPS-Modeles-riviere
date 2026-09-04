# include <iostream>
# include <iomanip>
# include <cmath>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>


# include <omp.h>


# include "../../../../Fonctions-communes/Librairies/1.hpp"
# include "../../../Fonctions-communes/Librairies/1.hpp"
# include "../../Librairies/volume-fini-rusanov-openmp.hpp"


# define idx(k, n) ((n) * (K + 2) + (k))





// Programme principal
int main(int argc, char **argv){


    // Démarrage
    std::cout << "——————————————————————————————————————————————————" << std::endl;
    std::cout << "Problème : Saint-Venant-dynamique" << std::endl;
    std::cout << "Version : volume-fini-rusanov-openmp" << std::endl;
    # pragma omp parallel
    {
    # pragma omp single
    {
    std::cout << "Nombre de threads = " << omp_get_num_threads() << std::endl;
    }
    }


    // Déclaration des variables
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
    double *q;
    double *v;
    double *A_exact;
    double *Q_exact;
    double *A_initial;
    double *Q_initial;
    double *A;
    double *Q;
    double t_final;
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
    struct timeval temps_debut;
    struct timeval temps_fin;
    double temps_execution;
    double erreur_L2_A;
    double erreur_infinie_A;
    double erreur_L2_Q;
    double erreur_infinie_Q;
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
    

    // Allocation de la mémoire
    A = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
    Q = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
    q = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
    v = (double *)malloc((K + 2) * (N + 1) * sizeof(double));


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
    A_exact = lire_tableau_double(
        nom_fichier_entree_A_exact,
        (K + 2) * (N + 1)
    );
    Q_exact = lire_tableau_double(
        nom_fichier_entree_Q_exact,
        (K + 2) * (N + 1)
    );
    A_initial = lire_tableau_double(
        nom_fichier_entree_A_initial,
        K + 2
    );
    Q_initial = lire_tableau_double(
        nom_fichier_entree_Q_initial,
        K + 2
    );
    for (int k = 0 ; k < K + 2 ; k ++){
        A[idx(k, 0)] = A_initial[k];
        Q[idx(k, 0)] = Q_initial[k];
    }
    for (int n = 0 ; n < N + 1 ; n ++){
        for (int k = 0 ; k < K + 2 ; k ++){
            q[idx(k, n)] = 0.0;
            v[idx(k, n)] = 0.0;
        }
    }


    // Appel de la fonction de résolution
    gettimeofday(&temps_debut, NULL);
    resoudre_volume_fini_rusanov(
        type_condition_limite_A,
        type_condition_limite_Q,
        CFL,
        K,
        Delta_s,
        N,
        L_t,
        Delta_t,
        t,
        b,
        r,
        S_0,
        q,
        v,
        A,
        Q,
        &t_final
    );
    gettimeofday(&temps_fin, NULL);


    // Calcul de l'erreur entre la solution exacte et la solution approchée
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


    // Écriture des résultats du calcul dans un fichier
    // ...


    // Calcul et affichage des résultats de performances dans le terminal
    temps_execution = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;
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



    // Écriture des résultats de performances dans un fichier
    resultats[0] = (double)2;
    # pragma omp parallel
    {
    # pragma omp single
    {
    resultats[1] = (double)omp_get_num_threads();
    }
    }
    resultats[2] = (double)-1;
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


    // Libération de la mémoire
    free(Delta_s);
    free(s);
    free(Delta_t);
    free(t);
    free(b);
    free(b_prime);
    free(r);
    free(S_0);
    free(q);
    free(v);
    free(A_exact);
    free(Q_exact);
    free(A_initial);
    free(Q_initial);
    free(A);
    free(Q);


    return 0;

}
