# Variables de répertoires
SOU = Sources
LIB = Librairies
OBJ = Objets





# Variables de compilation
CC = gcc
CCP = g++
CFLAGS = -O3 -Wall
CPPFLAGS = -O3 -Wall -std=c++17





# Création des objets
$(OBJ)/affichage.o: $(SOU)/affichage.cpp
	$(CCP) $(CPPFLAGS) -c $< -o $@


$(OBJ)/calcul-vecteur.o: $(SOU)/calcul-vecteur.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ)/entree-sortie.o: $(SOU)/entree-sortie.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ)/traitement-vecteur.o: $(SOU)/traitement-vecteur.c
	$(CC) $(CFLAGS) -c $< -o $@


$(LIB)/1.a: $(OBJ)/affichage.o $(OBJ)/calcul-vecteur.o $(OBJ)/entree-sortie.o $(OBJ)/traitement-vecteur.o
	ar rcs $@ $^





# Règles de compilations et exécutions
nettoyage:
	rm -rf $(OBJ)/*.o $(LIB)/1.a


all:
	make creation_repertoire
	make nettoyage
	make $(OBJ)/affichage.o
	make $(OBJ)/calcul-vecteur.o
	make $(OBJ)/entree-sortie.o
	make $(OBJ)/traitement-vecteur.o
	make $(LIB)/1.a


creation_repertoire:
	mkdir -p $(OBJ)