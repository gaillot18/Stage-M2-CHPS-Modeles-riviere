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


    double s_a;
    double s_b;
    double s_c;
    double s_d;
    double s_e;
    double S;
    double u_2;
    double c_2;
    double *h_exact_n;
    double *u_exact_n;
    S = 2.957918120187525;
    u_2 = S - (g / (8 * S)) * (1 + sqrt(1 + (16 * pow(S, 2)) / g));
    c_2 = sqrt((g / 4) * (sqrt(1 + (16 * pow(S, 2)) / g) - 1));
    h_exact_n = (double *)malloc((K + 2) * sizeof(double));
    u_exact_n = (double *)malloc((K + 2) * sizeof(double));


    for (int n = 0 ; n < N + 1 ; n ++){


        if (t[n] == 0.0){


            for (int k = 1 ; k < K + 1 ; k ++){


                if (s[k] <= 0.5){
                    h_exact_n[k] = 1.0;
                }
                else{
                    h_exact_n[k] = 0.5;
                }
                u_exact_n[k] = 0.0;


            }


        }


        else{


            s_a = 0.0;
            s_b = 0.5 - t[n] * sqrt(g);
            s_c = (u_2 - c_2) * t[n] + 0.5;
            s_d = S * t[n] + 0.5;
            s_e = 1.0;


            for (int k = 1 ; k < K + 1 ; k ++){


                if (s[k] >= s_a && s[k] < s_b){
                    h_exact_n[k] = 1.0;
                    u_exact_n[k] = 0.0;
                }
                else if (s[k] >= s_b && s[k] <= s_c){
                    h_exact_n[k] = pow(2.0 * sqrt(g) - (2.0 * s[k] - 1) / (2.0 * t[n]), 2) / (9.0 * g);
                    u_exact_n[k] = (2.0 * s[k] - 1.0 + 2.0 * t[n] * sqrt(g)) / (3.0 * t[n]);
                }
                else if (s[k] > s_c && s[k] <= s_d){
                    h_exact_n[k] = 0.25 * (sqrt(1.0 + 16.0 * pow(S, 2) / g) - 1.0);
                    u_exact_n[k] = u_2;
                }
                else if (s[k] > s_d && s[k] <= s_e){
                    h_exact_n[k] = 0.5;
                    u_exact_n[k] = 0.0;
                }


            }


        }


        h_exact_n[0] = h_exact_n[1];
        u_exact_n[0] = -u_exact_n[1];
        h_exact_n[K + 1] = h_exact_n[K];
        u_exact_n[K + 1] = -u_exact_n[K];


        for (int k = 0 ; k < K + 2 ; k ++){
            A_exact[idx(k, n)] = b[k] * h_exact_n[k];
            Q_exact[idx(k, n)] = A_exact[idx(k, n)] * u_exact_n[k];
        }


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


    // Initialisation des paramètres
    type_condition_limite_A = 2;
    type_condition_limite_Q = 3;


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


    L_t = 0.000001;
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
        r[k] = 0.0;
        S_0[k] = 0.0;
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