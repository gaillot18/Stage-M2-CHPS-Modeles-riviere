# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <float.h>


# define idx(k, n) ((n) * (K + 2) + (k))
# define max(a, b) ((a) > (b) ? (a) : (b))
# define g (9.80665)





// Calcul de Delta_t_n
static inline __attribute__((always_inline))
void calculer_Delta_t_n(
    double CFL,
    int K,
    int n,
    double *Delta_s,
    double *b,
    double *A,
    double *Q,
    double *Delta_t
){


    if (CFL <= 0){
        return;
    }


    double Delta_t_n_local;
    double Delta_t_n;


    Delta_t_n = DBL_MAX;
    

    for (int k = 1 ; k < K + 1 ; k ++){


        Delta_t_n_local = (
            Delta_s[k] /
            (
                fabs(Q[idx(k, n)] / A[idx(k, n)]) +
                sqrt(g * A[idx(k, n)] / b[k])
            )
        );
        if (Delta_t_n_local < Delta_t_n){
            Delta_t_n = Delta_t_n_local;
        }


    }


    Delta_t[n] = CFL * Delta_t_n;


    return;


}





// Calcul de P_n
static inline __attribute__((always_inline))
void calculer_P_n(
    int K,
    int n,
    double *b,
    double *A,
    double *P_n
){


    for (int k = 0 ; k < K + 2 ; k ++){
        P_n[k] = b[k] + 2 * A[idx(k, n)] / b[k];
    }


    return;


}





// Calcul de R_n
static inline __attribute__((always_inline))
void calculer_R_n(
    int K,
    int n,
    double *P_n,
    double *A,
    double *R_n
){


    for (int k = 0 ; k < K + 2 ; k ++){
        R_n[k] = A[idx(k, n)] / P_n[k];
    }


    return;


}





// Calcul de S_f_n
static inline __attribute__((always_inline))
void calculer_S_f_n(
    int K,
    int n,
    double *b,
    double *r,
    double *R_n,
    double *A,
    double *Q,
    double *S_f_n
){


    for (int k = 0 ; k < K + 2 ; k ++){
        S_f_n[k] = (
            Q[idx(k, n)] * fabs(Q[idx(k, n)]) * pow(r[k], 2) /
            pow(A[idx(k, n)], 2) * pow(R_n[k], 4.0 / 3.0)
        );
    }


    return;


}





// Calcul de lambda_star
static inline __attribute__((always_inline))
void calculer_lambda_star_n(
    int K,
    int n,
    double *b,
    double *A,
    double *Q,
    double *lambda_star_n
){


    double lambda_star_gauche;
    double lambda_star_droite;


    for (int k = 0 ; k < K + 1 ; k ++){


        lambda_star_gauche = (
            fabs(Q[idx(k, n)] / A[idx(k, n)])
            + sqrt(g * A[idx(k, n)] / b[k])
        );
        lambda_star_droite = (
            fabs(Q[idx(k + 1, n)] / A[idx(k + 1, n)])
            + sqrt(g * A[idx(k + 1, n)] / b[k + 1])
        );
        lambda_star_n[k] = max(
            lambda_star_gauche,
            lambda_star_droite
        );


    }


    return;


}





// Appliquer le schéma A
static inline __attribute__((always_inline))
void appliquer_schema_A(
    int K,
    double *Delta_s,
    double *Delta_t,
    int n,
    double *lambda_star_n,
    double *q,
    double *A,
    double *Q
){


    for (int k = 1 ; k < K + 1 ; k ++){


        A[idx(k, n + 1)] = (
            -0.5 * (Delta_t[n] / Delta_s[k]) * (
                Q[idx(k + 1, n)] -
                Q[idx(k - 1, n)] -
                lambda_star_n[k] * (A[idx(k + 1, n)] - A[idx(k, n)]) +
                lambda_star_n[k - 1] * (A[idx(k, n)] - A[idx(k - 1, n)])
            ) +
            A[idx(k, n)] +
            Delta_t[n] * q[idx(k, n)]
        );


    }


    return;


}





// Appliquer le schéma Q
static inline __attribute__((always_inline))
void appliquer_schema_Q(
    int K,
    double *Delta_s,
    double *Delta_t,
    int n,
    double *S_f_n,
    double *lambda_star_n,
    double *b,
    double *b_prime,
    double *r,
    double *S_0,
    double *q,
    double *v,
    double *A,
    double *Q
){


    double d_sur_ds_A_n_plus_1_k;
    double Q_1_n_plus_1_k;
    double Q_2_n_plus_1_k;
    double sgn_Q_2_n_plus_1_k;


    for (int k = 1 ; k < K + 1 ; k ++){


        if (k == 1){
            d_sur_ds_A_n_plus_1_k = (
                (A[idx(k + 1, n + 1)] - A[idx(k, n + 1)]) /
                (0.5 * (Delta_s[k] + Delta_s[k + 1]))
            );
        }
        else if (k == K){
            d_sur_ds_A_n_plus_1_k = (
                (A[idx(k, n + 1)] - A[idx(k - 1, n + 1)]) /
                (0.5 * (Delta_s[k - 1] + Delta_s[k]))
            );
        }
        else{
            d_sur_ds_A_n_plus_1_k = (
                (A[idx(k + 1, n + 1)] - A[idx(k - 1, n + 1)]) /
                (0.5 * Delta_s[k - 1] + Delta_s[k] + 0.5 * Delta_s[k + 1])
            );
        }


        Q_1_n_plus_1_k = (
            pow(A[idx(k, n + 1)], 10.0 / 3.0) /
            (
                b[k] * pow(r[k], 2) * 
                pow((b[k] + 2.0 * A[idx(k, n + 1)] / b[k]), 4.0 / 3.0)
            )
        );


        Q_2_n_plus_1_k = (
            -d_sur_ds_A_n_plus_1_k +
            0.5 * (A[idx(k, n + 1)] / b[k]) * b_prime[k] +
            b[k] * (
                S_0[k] + 
                (q[idx(k, n + 1)] * v[idx(k, n + 1)]) / 
                (g * A[idx(k, n + 1)])
            )
        );


        if (Q_2_n_plus_1_k > 0){
            sgn_Q_2_n_plus_1_k = 1.0;
        }
        else{
            sgn_Q_2_n_plus_1_k = -1.0;
        }


        Q[idx(k, n + 1)] = (
            sgn_Q_2_n_plus_1_k *
            sqrt(Q_1_n_plus_1_k) *
            sqrt(fabs(Q_2_n_plus_1_k))
        );


    }


    return;


}





// Appliquer les conditions aux limites
static inline __attribute__((always_inline))
void appliquer_condition_limite(
    int type_condition_limite_A,
    int type_condition_limite_Q,
    int K,
    int n,
    double *A,
    double *Q
){


    if (type_condition_limite_A == 0){ // Dirichlet amont, Dirichlet aval
        A[idx(0, n + 1)] = A[idx(0, n)];
        A[idx(K + 1, n + 1)] = A[idx(K, n + 1)];
    }
    else if (type_condition_limite_A == 1){ // Neumann amont, Neumann aval
        A[idx(0, n + 1)] = A[idx(1, n + 1)];
        A[idx(K + 1, n + 1)] = A[idx(K + 1, n)];
    }
    else if (type_condition_limite_A == 2){ // Neumann amont, Dirichlet aval
        A[idx(0, n + 1)] = A[idx(1, n + 1)];
        A[idx(K + 1, n + 1)] = A[idx(K, n + 1)];
    }
    else if (type_condition_limite_A == 3){ // Dirichlet amont, Neumann aval
        A[idx(0, n + 1)] = A[idx(0, n)];
        A[idx(K + 1, n + 1)] = A[idx(K, n)];
    }
    if (type_condition_limite_Q == 0){ // Dirichlet amont, Dirichlet aval
        Q[idx(0, n + 1)] = Q[idx(0, n)];
        Q[idx(K + 1, n + 1)] = Q[idx(K, n + 1)];
    }
    else if (type_condition_limite_Q == 1){ // Neumann amont, Neumann aval
        Q[idx(0, n + 1)] = Q[idx(1, n + 1)];
        Q[idx(K + 1, n + 1)] = Q[idx(K + 1, n)];
    }
    else if (type_condition_limite_Q == 2){ // Neumann amont, Dirichlet aval
        Q[idx(0, n + 1)] = Q[idx(1, n + 1)];
        Q[idx(K + 1, n + 1)] = Q[idx(K, n + 1)];
    }
    else if (type_condition_limite_Q == 3){ // Dirichlet amont, Neumann aval
        Q[idx(0, n + 1)] = Q[idx(0, n)];
        Q[idx(K + 1, n + 1)] = Q[idx(K, n)];
    }


    return;


}





// Fonction principale
void resoudre_volume_fini_rusanov(
    int type_condition_limite_A,
    int type_condition_limite_Q,
    double CFL,
    int K,
    double *Delta_s,
    int N,
    double L_t,
    double *Delta_t,
    double *t,
    double *b,
    double *b_prime,
    double *r,
    double *S_0,
    double *q,
    double *v,
    double *A,
    double *Q,
    double *t_final_ptr
){


    double t_actuel;
    int n;
    double *S_f_n;
    double *lambda_star_n;
    double *P_n;
    double *R_n;
    double t_final;


    t_actuel = 0.0;
    n = 0;
    S_f_n = (double *)malloc((K + 2) * sizeof(double));
    lambda_star_n = (double *)malloc((K + 2) * sizeof(double));
    P_n = (double *)malloc((K + 2) * sizeof(double));
    R_n = (double *)malloc((K + 2) * sizeof(double));


    while (n < N){


        calculer_Delta_t_n(
            CFL,
            K,
            n,
            Delta_s,
            b,
            A,
            Q,
            Delta_t
        );
        calculer_P_n(
            K,
            n,
            b,
            A,
            P_n
        );
        calculer_R_n(
            K,
            n,
            P_n,
            A,
            R_n
        );
        calculer_S_f_n(
            K,
            n,
            b,
            r,
            R_n,
            A,
            Q,
            S_f_n
        );
        calculer_lambda_star_n(
            K,
            n,
            b,
            A,
            Q,
            lambda_star_n
        );
        appliquer_schema_A(
                K,
                Delta_s,
                Delta_t,
                n,
                lambda_star_n,
                q,
                A,
                Q
        );
        appliquer_schema_Q(
                K,
                Delta_s,
                Delta_t,
                n,
                S_f_n,
                lambda_star_n,
                b,
                b_prime,
                r,
                S_0,
                q,
                v,
                A,
                Q
        );
        appliquer_condition_limite(
            type_condition_limite_A,
            type_condition_limite_Q,
            K,
            n,
            A,
            Q
        );


        t_actuel += Delta_t[n];
        t[n] = t_actuel;
        n ++;


    }


    t_final = t_actuel;
    *t_final_ptr = t_final;
    free(P_n);
    free(R_n);
    free(S_f_n);
    free(lambda_star_n);
    

    return;


}