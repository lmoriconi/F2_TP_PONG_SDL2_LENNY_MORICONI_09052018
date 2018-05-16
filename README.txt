READ ME :

Je tenais seulement à préciser que je n'ai pas été en mesure de corriger ce bug de "clipping" lors du rafraîchissement de la position des raquettes, de la balle et des scores. Cela a sûrement à voir avec les renderer, mais je ne comprends pas ce qu'il aurait fallu ajouter ou enlever dans le code pour avoir un affichage net.

EDIT : 

Je suis parvenu à corriger ce "bug" qui était seulement dû au fait que j'utilisais 5 renderers simultanément... Cependant j'ai constaté un autre problème : il n'est pas possible pour deux joueurs de bouger leurs raquettes simultanément, mais uniquement lorsque l'autre joueur n'est pas en train d'appuyer sur une touche. Les deux inputs ne sont pas détectés en même temps et donc les deux raquettes ne peuvent pas bouger ensemble.