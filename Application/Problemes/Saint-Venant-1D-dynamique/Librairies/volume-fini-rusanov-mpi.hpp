# ifdef __cplusplus
extern "C"{
# endif





// Variables globales
extern int numero_processus;
extern int nombre_processus;
extern MPI_Comm communicateur_1d;
extern int dimension_communicateur_1d;
extern int numero_processus_communicateur_1d;
extern int voisin[2];
extern int nombre_bord_libre;
extern int coins[4];
extern int etiquette;
extern MPI_Status statut;





// ../Sources/volume-fini-rusanov-mpi/resolution.c
void resoudre_volume_fini_rusanov(
    int type_condition_limite_A,
    int type_condition_limite_Q,
    double CFL,
    int K,
    int k_boucle_debut,
    int k_boucle_fin,
    double *Delta_s,
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
);





// ../Sources/volume-fini-rusanov-mpi/resolution-exacte.c
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





// ../Sources/volume-fini-rusanov-mpi/parallelisation.c
void afficher_message_ordonne(
    char *message
);


void creer_topologie();


void calculer_information_topologie();


void calculer_information_processus(
    int K,
    int *K_divise_ptr,
    int *k_debut_ptr,
    int *k_fin_ptr
);


void calculer_information_borne_boucle_espace(
    int K_divise,
    int k_debut,
    int k_fin,
    int *k_boucle_debut_ptr,
    int *k_boucle_fin_ptr
);


void calculer_information_regroupement_resultat(
    int K,
    int **deplacements_ptr,
    int **nombre_elements_recus_ptr
);


void initialiser_tableau_divise_1d(
    int K,
    int K_divise,
    int k_debut,
    double *U,
    double *U_divise
);


void initialiser_tableau_divise_2d(
    int K,
    int K_divise,
    int k_debut,
    double *U_initial,
    double *U_divise
);


void communiquer_cellule_fantome(
    int K_divise,
    double *U_divise
);


void communiquer_cellule_fantome_double(
    int K_divise,
    double *U_divise,
    double *V_divise
);


void regrouper_resultats(
    int K,
    int N,
    int K_divise,
    int *deplacements,
    int *nombre_elements_recus,
    double *A_initial,
    double *Q_initial,
    double *A_divise,
    double *Q_divise,
    double **A_ptr,
    double **Q_ptr
);





# ifdef __cplusplus
}
# endif