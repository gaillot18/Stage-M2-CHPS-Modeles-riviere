# include <iostream>
# include <iomanip>
# include <cmath>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>


# include "../../../../Fonctions-communes/Librairies/1.hpp"
# include "../../../Fonctions-communes/Librairies/1.hpp"
# include "../../Librairies/solution-exacte.hpp"


# define idx(k, n) ((n) * (K + 2) + (k))





// Programme principal
int main(int argc, char **argv){


    // Démarrage
    std::cout << "——————————————————————————————————————————————————" << std::endl;
    std::cout << "Problème : Saint-Venant-diffusif" << std::endl;
    std::cout << "Version : solution-exacte" << std::endl;


    // Déclaration des variables
    int type_condition_limite_A;
    int type_condition_limite_Q;
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
    double *h;
    double *u;
    double *A_exact;
    double *Q_exact;
    double *A_initial;
    double *Q_initial;
    const char *nom_fichier_sortie_type_condition_limite_A;
    const char *nom_fichier_sortie_type_condition_limite_Q;
    const char *nom_fichier_sortie_L_s;
    const char *nom_fichier_sortie_N;
    const char *nom_fichier_sortie_Delta_s;
    const char *nom_fichier_sortie_s;
    const char *nom_fichier_sortie_L_t;
    const char *nom_fichier_sortie_K;
    const char *nom_fichier_sortie_Delta_t;
    const char *nom_fichier_sortie_t;
    const char *nom_fichier_sortie_b;
    const char *nom_fichier_sortie_b_prime;
    const char *nom_fichier_sortie_r;
    const char *nom_fichier_sortie_S_0;
    const char *nom_fichier_sortie_A_exact;
    const char *nom_fichier_sortie_Q_exact;
    const char *nom_fichier_sortie_A_initial;
    const char *nom_fichier_sortie_Q_initial;
    struct timeval temps_debut;
    struct timeval temps_fin;
    double temps_execution;


    // Lecture des arguments
    K = atoi(argv[1]);
    N = atoi(argv[2]);
    nom_fichier_sortie_type_condition_limite_A = argv[3];
    nom_fichier_sortie_type_condition_limite_Q = argv[4];
    nom_fichier_sortie_L_s = argv[5];
    nom_fichier_sortie_K = argv[6];
    nom_fichier_sortie_Delta_s = argv[7];
    nom_fichier_sortie_s = argv[8];
    nom_fichier_sortie_L_t = argv[9];
    nom_fichier_sortie_N = argv[10];
    nom_fichier_sortie_Delta_t = argv[11];
    nom_fichier_sortie_t = argv[12];
    nom_fichier_sortie_b = argv[13];
    nom_fichier_sortie_b_prime = argv[14];
    nom_fichier_sortie_r = argv[15];
    nom_fichier_sortie_S_0 = argv[16];
    nom_fichier_sortie_A_exact = argv[17];
    nom_fichier_sortie_Q_exact = argv[18];
    nom_fichier_sortie_A_initial = argv[19];
    nom_fichier_sortie_Q_initial = argv[20];


    // Allocation de la mémoire
    Delta_s = (double *)malloc((K + 2) * sizeof(double));
    s = (double *)malloc((K + 2) * sizeof(double));
    Delta_t = (double *)malloc((N + 1) * sizeof(double));
    t = (double *)malloc((N + 1) * sizeof(double));
    b = (double *)malloc((K + 2) * sizeof(double));
    b_prime = (double *)malloc((K + 2) * sizeof(double));
    r = (double *)malloc((K + 2) * sizeof(double));
    S_0 = (double *)malloc((K + 2) * sizeof(double));
    A_exact = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
    Q_exact = (double *)malloc((K + 2) * (N + 1) * sizeof(double));
    A_initial = (double *)malloc((K + 2) * sizeof(double));
    Q_initial = (double *)malloc((K + 2) * sizeof(double));


    // Appel de la fonction de résolution
    gettimeofday(&temps_debut, NULL);
    resolution(
        &type_condition_limite_A,
        &type_condition_limite_Q,
        &L_s,
        &K,
        Delta_s,
        s,
        &L_t,
        &N,
        Delta_t,
        t,
        b,
        b_prime,
        r,
        S_0,
        A_exact,
        Q_exact,
        A_initial,
        Q_initial
    );
    gettimeofday(&temps_fin, NULL);



    // Écriture des résultats
    ecrire_valeur_int(
        nom_fichier_sortie_type_condition_limite_A,
        type_condition_limite_A
    );
    ecrire_valeur_int(
        nom_fichier_sortie_type_condition_limite_Q,
        type_condition_limite_Q
    );
    ecrire_valeur_double(
        nom_fichier_sortie_L_s,
        L_s
    );
    ecrire_valeur_int(
        nom_fichier_sortie_K,
        K
    );
    ecrire_tableau_double(
        nom_fichier_sortie_Delta_s,
        Delta_s,
        K + 2
    );
    ecrire_tableau_double(
        nom_fichier_sortie_s,
        s,
        K + 2
    );
    ecrire_valeur_double(
        nom_fichier_sortie_L_t,
        L_t
    );
    ecrire_valeur_int(
        nom_fichier_sortie_N,
        N
    );
    ecrire_tableau_double(
        nom_fichier_sortie_Delta_t,
        Delta_t,
        N + 1
    );
    ecrire_tableau_double(
        nom_fichier_sortie_t,
        t,
        N + 1
    );
    ecrire_tableau_double(
        nom_fichier_sortie_b,
        b,
        K + 2
    );
    ecrire_tableau_double(
        nom_fichier_sortie_b_prime,
        b_prime,
        K + 2
    );
    ecrire_tableau_double(
        nom_fichier_sortie_r,
        r,
        K + 2
    );
    ecrire_tableau_double(
        nom_fichier_sortie_S_0,
        S_0,
        K + 2
    );
    ecrire_tableau_double(
        nom_fichier_sortie_A_exact,
        A_exact,
        (K + 2) * (N + 1)
    );
    ecrire_tableau_double(
        nom_fichier_sortie_Q_exact,
        Q_exact,
        (K + 2) * (N + 1)
    );
    ecrire_tableau_double(
        nom_fichier_sortie_A_initial,
        A_initial,
        K + 2
    );
    ecrire_tableau_double(
        nom_fichier_sortie_Q_initial,
        Q_initial,
        K + 2
    );
    

    // Calcul et affichage des résultats de performances dans le terminal

    temps_execution = (temps_fin.tv_sec - temps_debut.tv_sec) + (temps_fin.tv_usec - temps_debut.tv_usec) / (double)1000000;
    std::cout << std::fixed << std::setprecision(0) << "K = " << K << std::endl;
    std::cout << std::fixed << std::setprecision(0) << "N = " << N << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "temps_execution = " << temps_execution << std::endl;


    // Libération de la mémoire
    free(Delta_s);
    free(s);
    free(Delta_t);
    free(t);
    free(b);
    free(b_prime);
    free(r);
    free(S_0);
    free(A_exact);
    free(Q_exact);
    free(A_initial);
    free(Q_initial);


    return 0;


}