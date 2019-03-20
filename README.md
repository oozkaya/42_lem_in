# Lem_in @ 42

Ce projet a pour but de vous faire coder un gestionaire de fourmillière dans lequel nous devons trouver le(s) chemin(s) le(s) plus optimisé(s) pour le transport des fourmis.

## Algorithm


L'algorithme consiste à prendre tout les chemins valides possibles dans un premier temps.

Ensuite ces chemins sont comparés pour selectionner les meilleurs d'entre-eux (les plus courts, ceux qui ne se croisent pas, etc...).

## Compréhension des maps
```
10          // Numéro de la fourmi
1 250 150   // Nom de la salle (1) et ses coordonnées X-Y (qui serviront pour la visualisation des graphes)
2 550 150
3 550 450
##start     // La prochaine salle sera la salle de début
4 250 450
##end       // La prochaine salle seral la salle de fin
5 850 450
6 850 150
1-2         // Relations entre les salles. La salle 1 sera reliée à la salle 2
1-3
1-4
2-4
2-6
2-5
3-4
3-5
3-6
5-6
```

## Compréhension de l'output

L[fourmi]-[salle]
```
L1-2 L2-3                // Tour 1 : la fourmi n°1 va à la salle "2". La fourmi n°2 va à la salle "3"
L1-5 L3-2 L2-5 L4-3
L3-5 L5-2 L4-5 L6-3
L5-5 L7-2 L6-5 L8-3
L7-5 L9-2 L8-5 L10-3
L9-5 L10-5
```

## Installation

`make`

## Run

Mode standard : 

`./lem-in < [map]`

Afficher des informations concernant la map:

`./lem-in -i < [map]` // affiche la totalité des infos
`./lem-in -l < [map]` // affiche le nombre de tour necessaire pour terminer la map
`./lem-in -r < [map]` // affiche les infos liées aux salles (start et end etant en rouge)

Exemple :

![alt text](https://bitbucket.org/oozkaya75/lem_in/raw/cdbbbc64d17a6f251c39b8deca667ef2ef824232/flag_i.png)

### Graphe visuel en .png

`./lem-in -g < [map]`

Ceci va générer une image png d'un graphe de la fourmiliere, ses salles et ses liens.
Assez utile pour avoir une vue d'ensemble des maps et se faire une idée des chemins proposés par l'algorithme.

Exemple :

![alt text](https://bitbucket.org/oozkaya75/lem_in/raw/cdbbbc64d17a6f251c39b8deca667ef2ef824232/graph.png)


# Note finale

`125/100 (Full bonus)`
