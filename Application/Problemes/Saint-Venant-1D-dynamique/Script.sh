#!/bin/bash





# Variables
BIN=Binaires
DON=Donnees
ENT=Entrees
RES_CAL=Resultats-calcul
RES_PER=Resultats-performance
RES=Resultats


v1=volume-fini-rusanov
v2=volume-fini-rusanov-openmp
v3=volume-fini-rusanov-mpi
a1=solution-exacte





# Compilation
SOLUTION_EXACTE=2
export SOLUTION_EXACTE
make creation_repertoire
make nettoyage_total
make $a1 SOLUTION_EXACTE=$SOLUTION_EXACTE
make $v1
make $v2
make $v3





# Démarrage
echo " "
echo "Exécutions pour Problemes/Saint-Venant-dynamique démarrées"
echo " "
sleep 1





# Variables d'exécution
solution_exacte=2
CFL=0.1





# Exécutions
nombre_execution=1
for N in 10000; do
    for K in 10000; do


        # Variables d'exécution
        nom_fichier_entree_type_condition_limite_A="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-type_condition_limite_A.bin"
        nom_fichier_sortie_type_condition_limite_A="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-type_condition_limite_A.bin"
        nom_fichier_entree_type_condition_limite_Q="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-type_condition_limite_Q.bin"
        nom_fichier_sortie_type_condition_limite_Q="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-type_condition_limite_Q.bin"
        nom_fichier_entree_L_s="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-L_s.bin"
        nom_fichier_sortie_L_s="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-L_s.bin"
        nom_fichier_entree_K="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-K.bin"
        nom_fichier_sortie_K="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-K.bin"
        nom_fichier_entree_Delta_s="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Delta_s.bin"
        nom_fichier_sortie_Delta_s="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Delta_s.bin"
        nom_fichier_entree_s="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-s.bin"
        nom_fichier_sortie_s="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-s.bin"
        nom_fichier_entree_L_t="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-L_t.bin"
        nom_fichier_sortie_L_t="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-L_t.bin"
        nom_fichier_entree_N="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-N.bin"
        nom_fichier_sortie_N="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-N.bin"
        nom_fichier_entree_Delta_t="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Delta_t.bin"
        nom_fichier_sortie_Delta_t="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Delta_t.bin"
        nom_fichier_entree_t="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-t.bin"
        nom_fichier_sortie_t="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-t.bin"
        nom_fichier_entree_b="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-b.bin"
        nom_fichier_sortie_b="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-b.bin"
        nom_fichier_entree_b_prime="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-b_prime.bin"
        nom_fichier_sortie_b_prime="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-b_prime.bin"
        nom_fichier_entree_r="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-r.bin"
        nom_fichier_sortie_r="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-r.bin"
        nom_fichier_entree_S_0="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-S_0.bin"
        nom_fichier_sortie_S_0="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-S_0.bin"
        nom_fichier_entree_A_exact="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-A_exact.bin"
        nom_fichier_sortie_A_exact="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-A_exact.bin"
        nom_fichier_entree_Q_exact="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Q_exact.bin"
        nom_fichier_sortie_Q_exact="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Q_exact.bin"
        nom_fichier_entree_A_initial="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-A_initial.bin"
        nom_fichier_sortie_A_initial="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-A_initial.bin"
        nom_fichier_entree_Q_initial="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Q_initial.bin"
        nom_fichier_sortie_Q_initial="$ENT/solution_exacte=$solution_exacte-K=$K-N=$N-Q_initial.bin"
        nom_fichier_sortie_A="Sorties/solution_exacte=$solution_exacte-K=$K-N=$N-A.bin"
        nom_fichier_sortie_Q="Sorties/solution_exacte=$solution_exacte-K=$K-N=$N-Q.bin"
        nom_fichier_sortie_resultat_performance="Sorties/resultat_performance.csv"


        # Version solution-exacte
        "./$BIN/$a1" \
            "$K" \
            "$N" \
            "$nom_fichier_sortie_type_condition_limite_A" \
            "$nom_fichier_sortie_type_condition_limite_Q" \
            "$nom_fichier_sortie_L_s" \
            "$nom_fichier_sortie_K" \
            "$nom_fichier_sortie_Delta_s" \
            "$nom_fichier_sortie_s" \
            "$nom_fichier_sortie_L_t" \
            "$nom_fichier_sortie_N" \
            "$nom_fichier_sortie_Delta_t" \
            "$nom_fichier_sortie_t" \
            "$nom_fichier_sortie_b" \
            "$nom_fichier_sortie_b_prime" \
            "$nom_fichier_sortie_r" \
            "$nom_fichier_sortie_S_0" \
            "$nom_fichier_sortie_A_exact" \
            "$nom_fichier_sortie_Q_exact" \
            "$nom_fichier_sortie_A_initial" \
            "$nom_fichier_sortie_Q_initial"


        # Version volume-fini-rusanov
        for i in $(seq 1 $nombre_execution); do
            "./$BIN/$v1" \
                "$CFL" \
                "$K" \
                "$N" \
                "$nom_fichier_entree_type_condition_limite_A" \
                "$nom_fichier_entree_type_condition_limite_Q" \
                "$nom_fichier_entree_L_s" \
                "$nom_fichier_entree_K" \
                "$nom_fichier_entree_Delta_s" \
                "$nom_fichier_entree_s" \
                "$nom_fichier_entree_L_t" \
                "$nom_fichier_entree_N" \
                "$nom_fichier_entree_Delta_t" \
                "$nom_fichier_entree_t" \
                "$nom_fichier_entree_b" \
                "$nom_fichier_entree_b_prime" \
                "$nom_fichier_entree_r" \
                "$nom_fichier_entree_S_0" \
                "$nom_fichier_entree_A_exact" \
                "$nom_fichier_entree_Q_exact" \
                "$nom_fichier_entree_A_initial" \
                "$nom_fichier_entree_Q_initial" \
                "$nom_fichier_sortie_A" \
                "$nom_fichier_sortie_Q" \
                "$nom_fichier_sortie_resultat_performance"
        done


        # Version volume-fini-rusanov-openmp
        for nombre_thread in 1 2 4 6 8; do
            for i in $(seq 1 $nombre_execution); do
                export OMP_NUM_THREADS=$nombre_thread
                "./$BIN/$v2" \
                    "$CFL" \
                    "$K" \
                    "$N" \
                    "$nom_fichier_entree_type_condition_limite_A" \
                    "$nom_fichier_entree_type_condition_limite_Q" \
                    "$nom_fichier_entree_L_s" \
                    "$nom_fichier_entree_K" \
                    "$nom_fichier_entree_Delta_s" \
                    "$nom_fichier_entree_s" \
                    "$nom_fichier_entree_L_t" \
                    "$nom_fichier_entree_N" \
                    "$nom_fichier_entree_Delta_t" \
                    "$nom_fichier_entree_t" \
                    "$nom_fichier_entree_b" \
                    "$nom_fichier_entree_b_prime" \
                    "$nom_fichier_entree_r" \
                    "$nom_fichier_entree_S_0" \
                    "$nom_fichier_entree_A_exact" \
                    "$nom_fichier_entree_Q_exact" \
                    "$nom_fichier_entree_A_initial" \
                    "$nom_fichier_entree_Q_initial" \
                    "$nom_fichier_sortie_A" \
                    "$nom_fichier_sortie_Q" \
                    "$nom_fichier_sortie_resultat_performance"
            done
        done


        # Version volume-fini-rusanov-mpi
        for nombre_processus in 1 2 4 6 8; do
            for i in $(seq 1 $nombre_execution); do
                mpirun -np "$nombre_processus" "./$BIN/$v3" \
                    "$CFL" \
                    "$K" \
                    "$N" \
                    "$nom_fichier_entree_type_condition_limite_A" \
                    "$nom_fichier_entree_type_condition_limite_Q" \
                    "$nom_fichier_entree_L_s" \
                    "$nom_fichier_entree_K" \
                    "$nom_fichier_entree_Delta_s" \
                    "$nom_fichier_entree_s" \
                    "$nom_fichier_entree_L_t" \
                    "$nom_fichier_entree_N" \
                    "$nom_fichier_entree_Delta_t" \
                    "$nom_fichier_entree_t" \
                    "$nom_fichier_entree_b" \
                    "$nom_fichier_entree_b_prime" \
                    "$nom_fichier_entree_r" \
                    "$nom_fichier_entree_S_0" \
                    "$nom_fichier_entree_A_exact" \
                    "$nom_fichier_entree_Q_exact" \
                    "$nom_fichier_entree_A_initial" \
                    "$nom_fichier_entree_Q_initial" \
                    "$nom_fichier_sortie_A" \
                    "$nom_fichier_sortie_Q" \
                    "$nom_fichier_sortie_resultat_performance"
            done
        done


    done 
done





sleep 1
echo " "
echo "Exécutions pour Problemes/Saint-Venant-dynamique terminées"
echo " "