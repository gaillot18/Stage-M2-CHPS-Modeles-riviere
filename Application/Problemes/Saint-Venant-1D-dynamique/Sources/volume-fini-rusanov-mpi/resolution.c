# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <float.h>


# include <mpi.h>


# include "../../Librairies/volume-fini-rusanov-mpi.hpp"


# define idx(k, n) ((n) * (K_divise + 2) + (k))
# define max(a, b) ((a) > (b) ? (a) : (b))
# define g (9.80665)





// Calcul de Delta_t_n
static inline __attribute__((always_inline))
void calculer_Delta_t_n(
    double CFL,
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    int n,
    double *Delta_s_divise,
    double *b_divise,
    double *A_divise,
    double *Q_divise,
    double *Delta_t
){


    if (CFL <= 0){
        return;
    }


    double Delta_t_n_local;
    double Delta_t_n;
    double Delta_t_n_global;


    Delta_t_n = DBL_MAX;
    

    for (int k = k_boucle_debut ; k < k_boucle_fin ; k ++){
        Delta_t_n_local = (
            Delta_s_divise[k] /
            (
                fabs(Q_divise[idx(k, n)] / A_divise[idx(k, n)]) +
                sqrt(g * A_divise[idx(k, n)] / b_divise[k])
            )
        );
        if (Delta_t_n_local < Delta_t_n){
            Delta_t_n = Delta_t_n_local;
        }
    }


    MPI_Allreduce(&Delta_t_n, &Delta_t_n_global, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
    Delta_t[n] = CFL * Delta_t_n_global;


    return;


}





// Calcul de P_n_divise
static inline __attribute__((always_inline))
void calculer_P_n_divise(
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    int n,
    double *b_divise,
    double *A_divise,
    double *P_n_divise
){


    for (int k = k_boucle_debut ; k < k_boucle_fin ; k ++){
        P_n_divise[k] = b_divise[k] + 2 * A_divise[idx(k, n)] / b_divise[k];
    }


    return;


}





// Calcul de R_n_divise
static inline __attribute__((always_inline))
void calculer_R_n_divise(
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    int n,
    double *P_n_divise,
    double *A_divise,
    double *R_n_divise
){


    for (int k = k_boucle_debut ; k < k_boucle_fin ; k ++){
        R_n_divise[k] = A_divise[idx(k, n)] / P_n_divise[k];
    }


    return;


}





// Calcul de S_f_n_divise
static inline __attribute__((always_inline))
void calculer_S_f_n_divise(
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    int n,
    double *b_divise,
    double *r_divise,
    double *R_n_divise,
    double *A_divise,
    double *Q_divise,
    double *S_f_n_divise
){


    for (int k = k_boucle_debut ; k < k_boucle_fin ; k ++){
        S_f_n_divise[k] = (
            Q_divise[idx(k, n)] * fabs(Q_divise[idx(k, n)]) * pow(r_divise[k], 2) /
            pow(A_divise[idx(k, n)], 2) * pow(R_n_divise[k], 4.0 / 3.0)
        );
    }


    return;


}





// Calcul de lambda_star_n_divise
static inline __attribute__((always_inline))
void calculer_lambda_star_n_n_divise(
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    int n,
    double *b_divise,
    double *A_divise,
    double *Q_divise,
    double *lambda_star_n_divise
){


    double *lambda_star_gauche;
    double *lambda_star_droite;


    lambda_star_gauche = (double *)malloc((K_divise + 2) * sizeof(double));
    lambda_star_droite = (double *)malloc((K_divise + 2) * sizeof(double));


    for (int k = k_boucle_debut - 1 ; k < k_boucle_fin + 1 ; k ++){


        lambda_star_gauche[k] = (
            fabs(Q_divise[idx(k, n)] / A_divise[idx(k, n)]) +
            sqrt(g * A_divise[idx(k, n)] / b_divise[k])
        );
        lambda_star_droite[k] = (
            fabs(Q_divise[idx(k + 1, n)] / A_divise[idx(k + 1, n)]) +
            sqrt(g * A_divise[idx(k + 1, n)] / b_divise[k + 1])
        );
        lambda_star_n_divise[k] = max(
            lambda_star_gauche[k],
            lambda_star_droite[k]
        );


    }


    free(lambda_star_gauche);
    free(lambda_star_droite);


    return;


}





// Appliquer le schéma A
static inline __attribute__((always_inline))
void appliquer_schema_A(
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    double *Delta_s_divise,
    double *Delta_t,
    int n,
    double *lambda_star_n_divise,
    double *q_divise,
    double *A_divise,
    double *Q_divise
){


    for (int k = k_boucle_debut ; k < k_boucle_fin ; k ++){


        A_divise[idx(k, n + 1)] = (
            -0.5 * (Delta_t[n] / Delta_s_divise[k]) * (
                Q_divise[idx(k + 1, n)] -
                Q_divise[idx(k - 1, n)] -
                lambda_star_n_divise[k] * (A_divise[idx(k + 1, n)] - A_divise[idx(k, n)]) +
                lambda_star_n_divise[k - 1] * (A_divise[idx(k, n)] - A_divise[idx(k - 1, n)])
            ) +
            A_divise[idx(k, n)] +
            Delta_t[n] * q_divise[idx(k, n)]
        );


    }


    return;


}





// Appliquer le schéma Q
static inline __attribute__((always_inline))
void appliquer_schema_Q(
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    double *Delta_s_divise,
    double *Delta_t,
    int n,
    double *S_f_n_divise,
    double *lambda_star_n_divise,
    double *b_divise,
    double *S_0_divise,
    double *q_divise,
    double *v_divise,
    double *A_divise,
    double *Q_divise
){


    for (int k = k_boucle_debut ; k < k_boucle_fin ; k ++){


        Q_divise[idx(k, n + 1)] = (
            -0.5 * (Delta_t[n] / Delta_s_divise[k]) * (
                pow(Q_divise[idx(k + 1, n)], 2) / A_divise[idx(k + 1, n)] -
                pow(Q_divise[idx(k - 1, n)], 2) / A_divise[idx(k - 1, n)] +
                0.5 * g * (
                    pow(A_divise[idx(k + 1, n)], 2) / b_divise[k + 1] -
                    pow(A_divise[idx(k - 1, n)], 2) / b_divise[k - 1]
                ) -
                lambda_star_n_divise[k] * (Q_divise[idx(k + 1, n)] - Q_divise[idx(k, n)]) +
                lambda_star_n_divise[k - 1] * (Q_divise[idx(k, n)] - Q_divise[idx(k - 1, n)])
            ) +
            Q_divise[idx(k, n)] +
            Delta_t[n] * (
                g * 
                (S_0_divise[k] - S_f_n_divise[k]) *
                A_divise[idx(k, n)] + q_divise[idx(k, n)] * v_divise[idx(k, n)]
            )
        );


    }


    return;


}





// Appliquer les conditions aux limites
static inline __attribute__((always_inline))
void appliquer_condition_limite(
    int type_condition_limite_A,
    int type_condition_limite_Q,
    int K_divise,
    int n,
    double *A_divise,
    double *Q_divise
){


    if (voisin[0] == -1){
        if (type_condition_limite_A == 0){ // Dirichlet amont, Dirichlet aval
            A_divise[idx(1, n + 1)] = A_divise[idx(1, n)];
        }
        else if (type_condition_limite_A == 1){ // Neumann amont, Neumann aval
            A_divise[idx(1, n + 1)] = A_divise[idx(2, n + 1)];
        }
        else if (type_condition_limite_A == 2){ // Neumann amont, Dirichlet aval
            A_divise[idx(1, n + 1)] = A_divise[idx(2, n + 1)];
        }
        else if (type_condition_limite_A == 3){ // Dirichlet amont, Neumann aval
            A_divise[idx(1, n + 1)] = A_divise[idx(1, n)];
        }
        if (type_condition_limite_Q == 0){ // Dirichlet amont, Dirichlet aval
            Q_divise[idx(1, n + 1)] = Q_divise[idx(1, n)];
        }
        else if (type_condition_limite_Q == 1){ // Neumann amont, Neumann aval
            Q_divise[idx(1, n + 1)] = Q_divise[idx(2, n + 1)];
        }
        else if (type_condition_limite_Q == 2){ // Neumann amont, Dirichlet aval
            Q_divise[idx(1, n + 1)] = Q_divise[idx(2, n + 1)];
        }
        else if (type_condition_limite_Q == 3){ // Dirichlet amont, Neumann aval
            Q_divise[idx(1, n + 1)] = Q_divise[idx(1, n)];
        }
    }


    if (voisin[1] == -1){
        if (type_condition_limite_A == 0){ // Dirichlet amont, Dirichlet aval
            A_divise[idx(K_divise, n + 1)] = A_divise[idx(K_divise - 1, n + 1)];
        }
        else if (type_condition_limite_A == 1){ // Neumann amont, Neumann aval
            A_divise[idx(K_divise, n + 1)] = A_divise[idx(K_divise, n)];
        }
        else if (type_condition_limite_A == 2){ // Neumann amont, Dirichlet aval
            A_divise[idx(K_divise, n + 1)] = A_divise[idx(K_divise - 1, n + 1)];
        }
        else if (type_condition_limite_A == 3){ // Dirichlet amont, Neumann aval
            A_divise[idx(K_divise, n + 1)] = A_divise[idx(K_divise - 1, n)];
        }
        if (type_condition_limite_Q == 0){ // Dirichlet amont, Dirichlet aval
            Q_divise[idx(K_divise, n + 1)] = Q_divise[idx(K_divise - 1, n + 1)];
        }
        else if (type_condition_limite_Q == 1){ // Neumann amont, Neumann aval
            Q_divise[idx(K_divise, n + 1)] = Q_divise[idx(K_divise, n)];
        }
        else if (type_condition_limite_Q == 2){ // Neumann amont, Dirichlet aval
            Q_divise[idx(K_divise, n + 1)] = Q_divise[idx(K_divise - 1, n + 1)];
        }
        else if (type_condition_limite_Q == 3){ // Dirichlet amont, Neumann aval
            Q_divise[idx(K_divise, n + 1)] = Q_divise[idx(K_divise - 1, n)];
        }
    }


    return;


}





// Fonction principale
void resoudre_volume_fini_rusanov(
    int type_condition_limite_A,
    int type_condition_limite_Q,
    double CFL,
    int K_divise,
    int k_boucle_debut,
    int k_boucle_fin,
    double *Delta_s_divise,
    int N,
    double L_t,
    double *Delta_t,
    double *t,
    double *b_divise,
    double *r_divise,
    double *S_0_divise,
    double *q_divise,
    double *v_divise,
    double *A_divise,
    double *Q_divise,
    double *t_final_ptr
){


    double t_actuel;
    int n;
    double *S_f_n_divise;
    double *lambda_star_n_divise;
    double *P_n_divise;
    double *R_n_divise;
    double t_final;


    t_actuel = 0.0;
    n = 0;
    S_f_n_divise = (double *)malloc((K_divise + 2) * sizeof(double));
    lambda_star_n_divise = (double *)malloc((K_divise + 2) * sizeof(double));
    P_n_divise = (double *)malloc((K_divise + 2) * sizeof(double));
    R_n_divise = (double *)malloc((K_divise + 2) * sizeof(double));


    while (n < N){


        communiquer_cellule_fantome_double(
            K_divise,
            &(A_divise[idx(0, n)]), 
            &(Q_divise[idx(0, n)])
        );
        calculer_Delta_t_n(
            CFL,
            K_divise,
            k_boucle_debut,
            k_boucle_fin,
            n,
            Delta_s_divise,
            b_divise,
            A_divise,
            Q_divise,
            Delta_t
        );
        calculer_P_n_divise(
            K_divise,
            k_boucle_debut,
            k_boucle_fin,
            n,
            b_divise,
            A_divise,
            P_n_divise
        );
        calculer_R_n_divise(
            K_divise,
            k_boucle_debut,
            k_boucle_fin,
            n,
            P_n_divise,
            A_divise,
            R_n_divise
        );
        calculer_S_f_n_divise(
            K_divise,
            k_boucle_debut,
            k_boucle_fin,
            n,
            b_divise,
            r_divise,
            R_n_divise,
            A_divise,
            Q_divise,
            S_f_n_divise
        );
        calculer_lambda_star_n_n_divise(
            K_divise,
            k_boucle_debut,
            k_boucle_fin,
            n,
            b_divise,
            A_divise,
            Q_divise,
            lambda_star_n_divise
        );
        appliquer_schema_A(
                K_divise,
                k_boucle_debut,
                k_boucle_fin,
                Delta_s_divise,
                Delta_t,
                n,
                lambda_star_n_divise,
                q_divise,
                A_divise,
                Q_divise
        );
        appliquer_schema_Q(
                K_divise,
                k_boucle_debut,
                k_boucle_fin,
                Delta_s_divise,
                Delta_t,
                n,
                S_f_n_divise,
                lambda_star_n_divise,
                b_divise,
                S_0_divise,
                q_divise,
                v_divise,
                A_divise,
                Q_divise
        );
        appliquer_condition_limite(
            type_condition_limite_A,
            type_condition_limite_Q,
            K_divise,
            n,
            A_divise,
            Q_divise
        );


        t_actuel += Delta_t[n];
        t[n] = t_actuel;
        n ++;


    }


    t_final = t_actuel;
    *t_final_ptr = t_final;
    free(P_n_divise);
    free(R_n_divise);
    free(S_f_n_divise);
    free(lambda_star_n_divise);
    

    return;


}