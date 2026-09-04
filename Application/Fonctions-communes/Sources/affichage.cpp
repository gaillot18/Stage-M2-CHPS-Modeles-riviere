# include <iostream>
# include <iomanip>
# include <stdlib.h>





// Afficher une matrice (ou une partie d'une matrice)
void afficher_matrice(
    double *matrice,
    int x_minimum,
    int x_maximum,
    int y_minimum,
    int y_maximum,
    int nombre_colonne
){


    for (int x = x_minimum ; x < x_maximum ; x ++){
        for (int y = y_minimum ; y < y_maximum ; y ++){
            std::cout << std::fixed << std::setprecision(5) << matrice[x * nombre_colonne + y] << " ";
        }
        std::cout << std::endl;
    }


    return;


}





// Afficher un vecteur (ou une partie d'un vecteur)
void afficher_vecteur(
    double *vecteur,
    int x_minimum,
    int x_maximum
){


    for (int x = x_minimum ; x < x_maximum ; x ++){
        std::cout << std::fixed << std::setprecision(3) << vecteur[x] << " ";
    }
    std::cout << std::endl;


    return;


}