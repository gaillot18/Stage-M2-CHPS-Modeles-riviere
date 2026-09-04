# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <float.h>


# define idx(k, n) ((n) * (K + 2) + (k))
# define max(a, b) ((a) > (b) ? (a) : (b))
# define g (9.80665)





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





// Calcul de Delta_t_n
static inline __attribute__((always_inline))
void calculer_Delta_t_n(
    double CFL,
    int K,
    int n,
    double *Delta_s,
    double *b,
    double *r,
    double *S_0,
    double *P_n,
    double *R_n,
    double *A,
    double *Delta_t
){


    if (CFL <= 0.0){
        return;
    }


    double Delta_t_n_local;
    double Delta_t_n;
    double c_k_n;


    Delta_t_n = DBL_MAX;
    

    for (int k = 1 ; k < K + 1 ; k ++){


        c_k_n = (
            (S_0[k] / r[k]) *
            (
                pow(R_n[k], 2.0 / 3.0) +
                (2.0 / 3.0) * (
                    b[k] * pow(A[idx(k, n)], 2.0 / 3.0) /
                    pow(P_n[k], 5.0 / 3.0)
                )
            )
        );


        Delta_t_n_local = Delta_s[k] / c_k_n;
        if (Delta_t_n_local < Delta_t_n){
            Delta_t_n = Delta_t_n_local;
        }


    }


    Delta_t[n] = CFL * Delta_t_n;


    return;


}





// Appliquer le schéma A
static inline __attribute__((always_inline))
void appliquer_schema_A(
    int K,
    double *Delta_s,
    double *Delta_t,
    int n,
    double *q,
    double *A,
    double *Q
){


    for (int k = 1 ; k < K + 1 ; k ++){


        A[idx(k, n + 1)] = (
            A[idx(k, n)] -
            (Delta_t[n] / Delta_s[k]) * (Q[idx(k, n)] - Q[idx(k - 1, n)]) +
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
    double *b,
    double *r,
    double *S_0,
    double *R_n,
    double *q,
    double *A,
    double *Q
){


    for (int k = 1 ; k < K + 1 ; k ++){


        Q[idx(k, n + 1)] = (
            (sqrt(S_0[k]) * A[idx(k, n + 1)] * pow(R_n[k], 2.0 / 3.0)) /
            r[k]
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
    double *r,
    double *S_0,
    double *q,
    double *A,
    double *Q,
    double *t_final_ptr
){


    double t_actuel;
    int n;
    double *P_n;
    double *R_n;
    double t_final;


    t_actuel = 0.0;
    n = 0;
    P_n = (double *)malloc((K + 2) * sizeof(double));
    R_n = (double *)malloc((K + 2) * sizeof(double));


    while (n < N){


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
        calculer_Delta_t_n(
            CFL,
            K,
            n,
            Delta_s,
            b,
            r,
            S_0,
            P_n,
            R_n,
            A,
            Delta_t
        );
        appliquer_schema_A(
                K,
                Delta_s,
                Delta_t,
                n,
                q,
                A,
                Q
        );
        appliquer_schema_Q(
                K,
                Delta_s,
                Delta_t,
                n,
                b,
                r,
                S_0,
                R_n,
                q,
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
    

    return;


}