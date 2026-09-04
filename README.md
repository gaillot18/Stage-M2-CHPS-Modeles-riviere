**Veille, étude et implémentation de modèles de rivière basés sur les équations de Saint-Venant**

*par Jean-Baptiste Gaillot*

# Informations

L'objectif de ce projet est d'étudier des modèles de rivière, d'un point de vue mathématique (équations aux dérivées partielles) et informatique (calcul haute performance).

# Application en ligne de commande

- Les modèles de rivière fonctionnent par l'utilisation d'une application en ligne de commande, écrite en langages ```C``` et ```C++```, et qui fonctionne avec ```docker```.
- Les étapes pour utiliser l'application sont les suivantes :
  - Se placer dans un répertoire dédié à stocker l'application.
  - Cloner le dépôt :
  ```sh
  git clone https://github.com/gaillot18/Stage-M2-CHPS-Modeles-riviere
  ```
  - Se placer dans le répertoire de l'application :
  ```sh
  cd Application
  ```
  - Construire l'image ```docker``` associée à l'application :
  ```sh
  docker build -f Dockerfile -t modeles-riviere .
  ```
  - Créer et lancer un conteneur associé à l'image précédente :
  ```sh
  docker run -it --rm -v .:/Repertoire_racine modeles-riviere \
  /bin/bash -c "./Script.sh"
  ```
- Dans l'image ```docker```, les paquets sont les suivants :
  - ```gcc``` (paquet ```apt```).
  - ```g++``` (paquet ```apt```).
  - ```make``` (paquet ```apt``` ou ```homebrew```).
  - ```libgomp1``` (paquet ```apt``` ou ```homebrew```).
  - ```mpich``` (paquet ```apt``` ou ```homebrew```).
  - ```libmpich``` (paquet ```apt``` ou ```homebrew```).