# Variables de répertoires
BIN = Binaires
DON = Donnees
ENT = Entrees
SOR = Sorties
LIB = Librairies
OBJ = Objets
SOU = Sources


FCC = Fonctions-communes


a1 = solution-exacte
v1 = volume-fini-rusanov
v2 = volume-fini-rusanov-openmp
v3 = volume-fini-rusanov-mpi





# Variables de compilation
CC = gcc
CCP = g++
MPICC = mpicc
MPICCP = mpic++
CCFLAGS = -O3 -Wall -fopenmp -Wno-unused
CCPFLAGS = -O3 -Wall -std=c++17 -fopenmp -Wno-unused
MPICCFLAGS = -O3 -Wall -Wno-unused
MPICPPFLAGS = -O3 -Wall -std=c++17 -Wno-unused
PGFLAGS =
SOLUTION_EXACTE = 2





# Création des objets et du binaire pour solution-exacte
$(BIN)/$(a1): $(OBJ)/$(a1)/main.o $(OBJ)/$(a1)/resolution-$(SOLUTION_EXACTE).o ../../$(FCC)/$(LIB)/1.a
	$(CCP) $(CCPFLAGS) $^ -o $@ -lm


$(OBJ)/$(a1)/main.o: $(SOU)/$(a1)/main.cpp
	$(CCP) $(CCPFLAGS) -c $< -o $@


$(OBJ)/$(a1)/resolution-$(SOLUTION_EXACTE).o: $(SOU)/$(a1)/resolution-$(SOLUTION_EXACTE).c
	$(CC) $(CCFLAGS) -DSOLUTION_EXACTE=$(SOLUTION_EXACTE) -c $< -o $@





# Création des objets et du binaire pour volume-fini-rusanov
$(BIN)/$(v1): $(OBJ)/$(v1)/main.o $(OBJ)/$(v1)/resolution.o $(OBJ)/$(v1)/geometrie.o ../../$(FCC)/$(LIB)/1.a
	$(CCP) $(CCPFLAGS) $(PGFLAGS) $^ -o $@ -lm


$(OBJ)/$(v1)/main.o: $(SOU)/$(v1)/main.cpp
	$(CCP) $(CCPFLAGS) $(PGFLAGS) -c $< -o $@


$(OBJ)/$(v1)/resolution.o: $(SOU)/$(v1)/resolution.c
	$(CC) $(CCFLAGS) $(PGFLAGS) -c $< -o $@


$(OBJ)/$(v1)/geometrie.o: ../$(FCC)/$(SOU)/geometrie.c
	$(CC) $(CCFLAGS) $(PGFLAGS) -c $< -o $@





# Création des objets et du binaire pour volume-fini-rusanov-openmp
$(BIN)/$(v2): $(OBJ)/$(v2)/main.o $(OBJ)/$(v2)/resolution.o $(OBJ)/$(v2)/geometrie.o ../../$(FCC)/$(LIB)/1.a
	$(CCP) $(CCPFLAGS) $^ -o $@ -lm -lgomp


$(OBJ)/$(v2)/main.o: $(SOU)/$(v2)/main.cpp
	$(CCP) $(CCPFLAGS) -c $< -o $@


$(OBJ)/$(v2)/resolution.o: $(SOU)/$(v2)/resolution.c
	$(CC) $(CCFLAGS) -c $< -o $@


$(OBJ)/$(v2)/geometrie.o: ../$(FCC)/$(SOU)/geometrie.c
	$(CC) $(CCFLAGS) -c $< -o $@





# Création des objets et du binaire pour volume-fini-rusanov-mpi
$(BIN)/$(v3): $(OBJ)/$(v3)/main.o $(OBJ)/$(v3)/parallelisation.o $(OBJ)/$(v3)/resolution.o $(OBJ)/$(v3)/geometrie.o ../../$(FCC)/$(LIB)/1.a
	$(MPICCP) $(MPICPPFLAGS) $^ -o $@ -lm


$(OBJ)/$(v3)/main.o: $(SOU)/$(v3)/main.cpp
	$(MPICCP) $(MPICPPFLAGS) -c $< -o $@


$(OBJ)/$(v3)/parallelisation.o: $(SOU)/$(v3)/parallelisation.c
	$(MPICCP) $(MPICPPFLAGS) -c $< -o $@


$(OBJ)/$(v3)/resolution.o: $(SOU)/$(v3)/resolution.c
	$(MPICC) $(MPICCFLAGS) -c $< -o $@


$(OBJ)/$(v3)/geometrie.o: ../$(FCC)/$(SOU)/geometrie.c
	$(MPICC) $(MPICCFLAGS) -c $< -o $@





# Variables d'exécution
nombre_thread = 1
nombre_processus = 1
solution_exacte = 2
CFL = 0.1
K = 15000
N = 15000
nom_fichier_entree_type_condition_limite_A = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-type_condition_limite_A.bin
nom_fichier_sortie_type_condition_limite_A = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-type_condition_limite_A.bin
nom_fichier_entree_type_condition_limite_Q = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-type_condition_limite_Q.bin
nom_fichier_sortie_type_condition_limite_Q = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-type_condition_limite_Q.bin
nom_fichier_entree_L_s = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-L_s.bin
nom_fichier_sortie_L_s = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-L_s.bin
nom_fichier_entree_K = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-K.bin
nom_fichier_sortie_K = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-K.bin
nom_fichier_entree_Delta_s = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Delta_s.bin
nom_fichier_sortie_Delta_s = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Delta_s.bin
nom_fichier_entree_s = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-s.bin
nom_fichier_sortie_s = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-s.bin
nom_fichier_entree_L_t = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-L_t.bin
nom_fichier_sortie_L_t = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-L_t.bin
nom_fichier_entree_N = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-N.bin
nom_fichier_sortie_N = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-N.bin
nom_fichier_entree_Delta_t = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Delta_t.bin
nom_fichier_sortie_Delta_t = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Delta_t.bin
nom_fichier_entree_t = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-t.bin
nom_fichier_sortie_t = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-t.bin
nom_fichier_entree_b = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-b.bin
nom_fichier_sortie_b = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-b.bin
nom_fichier_entree_b_prime = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-b_prime.bin
nom_fichier_sortie_b_prime = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-b_prime.bin
nom_fichier_entree_r = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-r.bin
nom_fichier_sortie_r = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-r.bin
nom_fichier_entree_S_0 = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-S_0.bin
nom_fichier_sortie_S_0 = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-S_0.bin
nom_fichier_entree_A_exact = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-A_exact.bin
nom_fichier_sortie_A_exact = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-A_exact.bin
nom_fichier_entree_Q_exact = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Q_exact.bin
nom_fichier_sortie_Q_exact = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Q_exact.bin
nom_fichier_entree_A_initial = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-A_initial.bin
nom_fichier_sortie_A_initial = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-A_initial.bin
nom_fichier_entree_Q_initial = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Q_initial.bin
nom_fichier_sortie_Q_initial = $(ENT)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Q_initial.bin
nom_fichier_sortie_A = $(SOR)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-A.bin
nom_fichier_sortie_Q = $(SOR)/solution_exacte=$(solution_exacte)-K=$(K)-N=$(N)-Q.bin
nom_fichier_sortie_resultat_performance = $(SOR)/resultat_performance.csv





# Règles de compilations et exécutions
.PHONY: nettoyage_total nettoyage_partiel creation_repertoire


$(a1): $(BIN)/$(a1)


$(v1): $(BIN)/$(v1)


$(v2): $(BIN)/$(v2)


$(v3): $(BIN)/$(v3)


exe-a1:
	make nettoyage_total
	make creation_repertoire
	make $(a1)
	./$(BIN)/$(a1) \
		$(K) \
		$(N) \
 		$(nom_fichier_sortie_type_condition_limite_A) \
		$(nom_fichier_sortie_type_condition_limite_Q) \
		$(nom_fichier_sortie_L_s) \
		$(nom_fichier_sortie_K) \
		$(nom_fichier_sortie_Delta_s) \
		$(nom_fichier_sortie_s) \
		$(nom_fichier_sortie_L_t) \
		$(nom_fichier_sortie_N) \
		$(nom_fichier_sortie_Delta_t) \
		$(nom_fichier_sortie_t) \
		$(nom_fichier_sortie_b) \
		$(nom_fichier_sortie_b_prime) \
		$(nom_fichier_sortie_r) \
		$(nom_fichier_sortie_S_0) \
		$(nom_fichier_sortie_A_exact) \
		$(nom_fichier_sortie_Q_exact) \
		$(nom_fichier_sortie_A_initial) \
		$(nom_fichier_sortie_Q_initial)


exe-v1:
	make nettoyage_partiel
	make creation_repertoire
	make $(v1)
	./$(BIN)/$(v1) \
		$(CFL) \
		$(K) \
		$(N) \
		$(nom_fichier_entree_type_condition_limite_A) \
		$(nom_fichier_entree_type_condition_limite_Q) \
		$(nom_fichier_entree_L_s) \
		$(nom_fichier_entree_K) \
		$(nom_fichier_entree_Delta_s) \
		$(nom_fichier_entree_s) \
		$(nom_fichier_entree_L_t) \
		$(nom_fichier_entree_N) \
		$(nom_fichier_entree_Delta_t) \
		$(nom_fichier_entree_t) \
		$(nom_fichier_entree_b) \
		$(nom_fichier_entree_b_prime) \
		$(nom_fichier_entree_r) \
		$(nom_fichier_entree_S_0) \
		$(nom_fichier_entree_A_exact) \
		$(nom_fichier_entree_Q_exact) \
		$(nom_fichier_entree_A_initial) \
		$(nom_fichier_entree_Q_initial) \
		$(nom_fichier_sortie_A) \
		$(nom_fichier_sortie_Q) \
		$(nom_fichier_sortie_resultat_performance)


exe-v2:
	make nettoyage_partiel
	make creation_repertoire
	make $(v2)
	export OMP_NUM_THREADS=$(nombre_thread) && ./$(BIN)/$(v2) \
		$(CFL) \
		$(K) \
		$(N) \
		$(nom_fichier_entree_type_condition_limite_A) \
		$(nom_fichier_entree_type_condition_limite_Q) \
		$(nom_fichier_entree_L_s) \
		$(nom_fichier_entree_K) \
		$(nom_fichier_entree_Delta_s) \
		$(nom_fichier_entree_s) \
		$(nom_fichier_entree_L_t) \
		$(nom_fichier_entree_N) \
		$(nom_fichier_entree_Delta_t) \
		$(nom_fichier_entree_t) \
		$(nom_fichier_entree_b) \
		$(nom_fichier_entree_b_prime) \
		$(nom_fichier_entree_r) \
		$(nom_fichier_entree_S_0) \
		$(nom_fichier_entree_A_exact) \
		$(nom_fichier_entree_Q_exact) \
		$(nom_fichier_entree_A_initial) \
		$(nom_fichier_entree_Q_initial) \
		$(nom_fichier_sortie_A) \
		$(nom_fichier_sortie_Q) \
		$(nom_fichier_sortie_resultat_performance)


exe-v3:
	make nettoyage_partiel
	make creation_repertoire
	make $(v3)
	mpirun -np $(nombre_processus) ./$(BIN)/$(v3) \
		$(CFL) \
		$(K) \
		$(N) \
		$(nom_fichier_entree_type_condition_limite_A) \
		$(nom_fichier_entree_type_condition_limite_Q) \
		$(nom_fichier_entree_L_s) \
		$(nom_fichier_entree_K) \
		$(nom_fichier_entree_Delta_s) \
		$(nom_fichier_entree_s) \
		$(nom_fichier_entree_L_t) \
		$(nom_fichier_entree_N) \
		$(nom_fichier_entree_Delta_t) \
		$(nom_fichier_entree_t) \
		$(nom_fichier_entree_b) \
		$(nom_fichier_entree_b_prime) \
		$(nom_fichier_entree_r) \
		$(nom_fichier_entree_S_0) \
		$(nom_fichier_entree_A_exact) \
		$(nom_fichier_entree_Q_exact) \
		$(nom_fichier_entree_A_initial) \
		$(nom_fichier_entree_Q_initial) \
		$(nom_fichier_sortie_A) \
		$(nom_fichier_sortie_Q) \
		$(nom_fichier_sortie_resultat_performance)


all:
	make creation_repertoire
	make nettoyage_total
	make $(a1) SOLUTION_EXACTE=$(SOLUTION_EXACTE)
	make $(v1)
	make $(v2)
	make $(v3)


creation_repertoire:
	mkdir -p $(OBJ)
	mkdir -p $(OBJ)/$(a1)
	mkdir -p $(OBJ)/$(v1)
	mkdir -p $(OBJ)/$(v2)
	mkdir -p $(OBJ)/$(v3)
	mkdir -p $(BIN)
	mkdir -p $(ENT)
	mkdir -p $(SOR)


nettoyage_total:
	@test -n "$(SOR)" -a -n "$(OBJ)" -a -n "$(BIN)" || exit 1
	rm -rf $(ENT)/* $(SOR)/* $(OBJ)/$(v1)/*.o $(OBJ)/$(v2)/*.o $(OBJ)/$(v3)/*.o $(BIN)/*


nettoyage_partiel:
	@test -n "$(OBJ)" -a -n "$(BIN)" || exit 1
	rm -rf $(OBJ)/$(v1)/*.o $(OBJ)/$(v2)/*.o $(OBJ)/$(v3)/*.o $(BIN)/*