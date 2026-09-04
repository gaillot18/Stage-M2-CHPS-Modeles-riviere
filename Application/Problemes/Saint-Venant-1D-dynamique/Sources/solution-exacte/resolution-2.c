# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>


# include "../../../../Fonctions-communes/Librairies/1.hpp"


# define idx(k, n) ((n) * (K + 2) + (k))
# define max(a, b) ((a) > (b) ? (a) : (b))
# define g (9.80665)





// Calcul de la solution exacte
void calculer_solution_exacte(
    int K,
    double *s,
    int N,
    double *t,
    double *b,
    double *A_exact,
    double *Q_exact
){


    for (int n = 0 ; n < N + 1 ; n ++){


        if (t[n] == 0.0){


            for (int k = 1 ; k < K + 1 ; k ++){


                A_exact[idx(k, n)] = 1.0;
                Q_exact[idx(k, n)] = 0.0;


            }


        }


        else{


            for (int k = 1 ; k < K + 1 ; k ++){


                A_exact[idx(k, n)] = 1.0;
                Q_exact[idx(k, n)] = 0.0;


            }


        }


        A_exact[idx(0, n)] = A_exact[idx(1, n)];
        A_exact[idx(K + 1, n)] = A_exact[idx(K, n)];
        Q_exact[idx(0, n)] = Q_exact[idx(1, n)];
        Q_exact[idx(K + 1, n)] = Q_exact[idx(K, n)];


    }


    return;


}





//
void resolution(
    int *type_condition_limite_A_ptr,
    int *type_condition_limite_Q_ptr,
    double *L_s_ptr,
    int *K_ptr,
    double *Delta_s,
    double *s,
    double *L_t_ptr,
    int *N_ptr,
    double *Delta_t,
    double *t,
    double *b,
    double *b_prime,
    double *r,
    double *S_0,
    double *A_exact,
    double *Q_exact,
    double *A_initial,
    double *Q_initial
){


    int type_condition_limite_A;
    int type_condition_limite_Q;
    double L_s;
    int K;
    double L_t;
    int N;
    double CFL;


    printf("Cette solution n'est pas exacte.\n");
    printf("Les erreurs sont incorrectes.\n");
    printf("Ce test permet de tester le schéma sur les performances.\n");


    // Initialisation des paramètres
    type_condition_limite_A = 3;
    type_condition_limite_Q = 2;


    L_s = 1.0;
    K = *K_ptr;
    s[0] = 0.0;
    for (int k = 1 ; k < K + 1 ; k ++){
        s[k] = 0.5 * L_s / K + (k - 1) * (L_s / K);
    }
    s[K + 1] = L_s;
    Delta_s[0] = -1.0;
    for (int k = 1 ; k < K + 1 ; k ++) {
        Delta_s[k] = L_s / K;
    }
    Delta_s[K + 1] = -1.0;


    L_t = 1.0;
    N = *N_ptr;
    for (int n = 0 ; n < N + 1 ; n ++) {
        t[n] = n * (L_t / N);
    }
    for (int n = 0 ; n < N + 1 ; n ++) {
        Delta_t[n] = L_t / N;
    }


    for (int k = 0 ; k < K + 2 ; k ++){
        b[k] = 1.0;
        b_prime[k] = 0.0;
        r[k] = 0.035;
        S_0[k] = 0.01;
    }


    // Calcul de la solution exacte
    calculer_solution_exacte(
        K,
        s,
        N,
        t,
        b,
        A_exact,
        Q_exact
    );



    // Calcul des conditions initiales de la solution exacte
    for (int k = 0 ; k < K + 2 ; k ++){
        A_initial[k] = A_exact[idx(k, 0)];
        Q_initial[k] = Q_exact[idx(k, 0)];
    }


    *type_condition_limite_A_ptr = type_condition_limite_A;
    *type_condition_limite_Q_ptr = type_condition_limite_Q;
    *L_s_ptr = L_s;
    *K_ptr = K;
    *L_t_ptr = L_t;
    *N_ptr = N;


}