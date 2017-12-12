# Mini projet
Raven all the way

De nouvelles règles ont été ajoutées au Rocket Launcher pour optimiser son utilisation en prenant mieux en compte l'environnement.
Le "bruit" modifiant la précision des tirs a été modifié pour utiliser la logique floue et rendre la visée plus réaliste. Il est obtenu en fonction de la distance à la cible, de sa vélocité et du temps où elle a été visible.

Pour la partie équipe plusieurs choses ont été implémentées:
Le mode équipe peut-être activé/désactivé via la touche T.
Une stratégie d'équipe consistant à aider un coéquipier dont la vie est basse a également été implémentée.
Si un allié meurt, il laisse ses items près du spawn de son équipe.
Le nombre d'équipes de départ dépend du nombre de spwans sur la map. L'ajout/suppression de spwans se fait via le fichier DM1.map.
Les équipes possèdent également des comportements qui biaisent leurs choix. Une équipe aggressive attaquera sans tenir compte de ses points de vie. Une équipe looter privilégiera le ramassage d'objets.
Le Flocking peut également être activé/désactivé via la touche F.

Concernant  le réseau de neurones, on peut activer le mode apprentissage en cochant le mode entraînement. Pendant que le mode entraînement est actif, le fichier d'apprentissage est édité toutes les deux secondes et à chaque fois que le joueur tire. Les données suivantes sont récupérées et analysées: Distance entre le joueur et l'ennemi, Visibilité de l'ennemi, Type d'arme du joueur, Munitions associées à l'arme, Vie de l'ennemi. Après avoir arrêté le mode apprentissage et redémarré le jeu, un nouveau fichier correspondant au réseau de neurones entraîné est créé. On peut alors ajouter le bot apprenant en appuyant sur la touche Flèche droite du clavier.
