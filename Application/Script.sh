#!/bin/bash

echo "Exécutions de l'application démarrées"


mkdir -p Resultats/


cd Fonctions-communes


# Compilation de la bibliothèque Fonction-communes
make nettoyage
make all
cd ..


cd Problemes


# Exécutions pour le problème Saint-Venant-1D-dynamique
cd Saint-Venant-1D-dynamique
./Script.sh
cp Sorties/resultat_performance.csv ../../Resultats/resultat_performance_Saint-Venant-1D-dynamique.csv
cd ..


# Exécutions pour le problème Saint-Venant-1D-diffusif
cd Saint-Venant-1D-diffusif
./Script.sh
cp Sorties/resultat_performance.csv ../../Resultats/resultat_performance_Saint-Venant-1D-diffusif.csv
cd ..


# Exécutions pour le problème Saint-Venant-1D-cinematique
cd Saint-Venant-1D-cinematique
./Script.sh
cp Sorties/resultat_performance.csv ../../Resultats/resultat_performance_Saint-Venant-1D-cinematique.csv
cd ..


cd ..


echo "Exécutions de l'application terminées"