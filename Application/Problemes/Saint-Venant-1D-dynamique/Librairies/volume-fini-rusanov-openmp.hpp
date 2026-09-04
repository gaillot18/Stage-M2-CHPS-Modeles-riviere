# ifdef __cplusplus
extern "C"{
# endif





// ../Sources/volume-fini-rusanov/resolution.c
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
    double *v,
    double *A,
    double *Q,
    double *t_final_ptr
);





// ../Sources/volume-fini-rusanov/resolution-exacte.c
void calculer_solution_exacte_1(
    int calculer_temps_intermediaire,
    int K,
    double *s,
    int N,
    double *t,
    double *b,
    double *A,
    double *Q,
    double *h,
    double *u
);


void initialiser_solution_approchee_1(
    int K,
    double *s,
    double *b,
    double *A,
    double *Q
);





# ifdef __cplusplus
}
# endif
# ifdef __cplusplus





//





# endif