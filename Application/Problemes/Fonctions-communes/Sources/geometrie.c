# include <stdlib.h>
# include <math.h>


# define idx(k, n) ((n) * (K + 2) + (k))





// Calcul de h_n
void calculer_h_n(
    int K,
    double *b,
    double *A_n,
    double *h_n
){


    for (int k = 0 ; k < K + 2 ; k ++){
        h_n[k] = A_n[k] / b[k];
    }


    return;


}




// Calcul de h
void calculer_h(
    int K,
    int N,
    double *b,
    double *A,
    double *h
){


    for (int n = 0 ; n < N + 1 ; n ++){
        calculer_h_n(
            K,
            b,
            &A[idx(0, n)],
            &h[idx(0, n)]
        );
    }


    return;


}





// Calcul de u_n
void calculer_u_n(
    int K,
    double *A_n,
    double *Q_n,
    double *u_n
){


    for (int k = 0 ; k < K + 2 ; k ++){
        u_n[k] = Q_n[k] / A_n[k];
    }


    return;


}





// Calcul de u
void calculer_u(
    int K,
    int N,
    double *A,
    double *Q,
    double *u
){


    for (int n = 0 ; n < N + 1 ; n ++){
        calculer_u_n(
            K,
            &A[idx(0, n)],
            &Q[idx(0, n)],
            &u[idx(0, n)]
        );
    }


    return;


}