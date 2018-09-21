// Ce readme.txt contient les informations necessaires pour comprendre les parametres du fichier Config.txt //

https://www.dcode.fr/jeu-de-la-vie

largeur >=5
hauteur >=5
motif [1,6] 1=Ligne 2=U 3=Planeur 4=Aleatoire 5=AleatoireVertical 6=AleatoireHorizontal
naissance Nombre de voisines vivantes que doit avoir une cellule pour prendre Vie [Fonctionnement par OU]
survie Conditions sur les voisines vivantes pour que la cellule reste vivante [Fonctionnement par OU]
image caractere qui compose le motif
vitesse >0 En secondes. Float possibles
continue [0,1] 1 permet d'afficher en continue, 0 nécéssite l'appuis d'une touche
/!\ Une fois les parametres naissance et survie choisi, completez pour remplir les 8 cases avec des nombres déjà entrés
/!\ Respectez l'espace apres chaque mots et ne sautez pas de lignes comme dans l'exemple suivant : 

largeur 30   
hauteur 30         
motif 1
naissance 1 3 5 5 5 5 5 5
survie 2 3 4 4 4 4 4 4  
image o
vitesse 1
continue 1

Pour une Grille carrée, pensez à doubler la largeur par rapport à la hauteur