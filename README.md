# HappySeed - outil de régulation d'une plante d'intérieur

Nous souhaitons optimiser l'environnement d'une plante d'intérieur en jouant sur différents paramètres pour qu'elle puisse s'épanouir au mieux. Nous supposons qu'elle se situe dans une pièce où se trouve une lampe, un système d'arrosage et une fenêtre commandables.

Notre système est donc constitué de 4 capteurs :
- un détecteur d’humidité (placé dans la terre du pot)
- un détecteur de température
- un détecteur de luminosité
- un détecteur du taux de CO2

Il comporte également 6 actionneurs :
- un servo-moteur permettant d'actionner l'ouverture / la fermeture de la fenêtre
- un système de chauffage, modélisé par un servo-moteur également
- un ventilateur, modélisé par un servo-moteur
- une lampe possédant un état haut et un état bas (allumée / éteinte)
- un système d'arrosage à deux états (robinet ouvert / fermé)
- un écran relié par I2C à la carte, qui permet à l'utilisateur d'accéder aux mesures des capteurs.


Nous voulons donc contrôler le taux d'humidité de la terre de la plante : si elle n'a pas assez d'eau, l'arrosage se met en route ; et si elle en a trop, la fenêtre s'ouvre pour accélérer l'évaporation de l'eau.
De même, si la température est trop faible, un chauffage se met en route ; si elle est trop élevée, le ventilateur démarre.
Si la plante est plongée dans l'obscurité, une lampe s'allume pour lui permettre de bénéficier d'un éclairage optimal.


Architecture du projet :
- board.cpp contient la définition des capteurs et des actionneurs et leur emplacement sur la carte Arduino
- core_simulation.cpp et core_simulation.h contiennent les définitions des classes nécessaires à la simulation de la carte. Nous n'y avons pas touché
- environnement.cpp et environnement.h correspond à la définition des classes Plante, Environnement et MyApplication. La classe Plante caractérise les besoins de la plante et son "énergie" (nous l'avons imaginée comme un personnage de jeu vidéo qui perd des points de vie si elle reste trop longtemps dans de mauvaises conditions). La classe Environnement contient avant tout les paramètres d'environnement, déclarés comme static (température, humidité, luminosité, taux de CO2 dans l'air). La classe MyApplication s'occupe d'envoyer les ordres aux actionneurs en fonction de l'état de la plante.
- mydevices.cpp et mydevices.h regroupent les déclarations des différents capteurs / actionneurs. Tous sont des Device, répartis entre les Capteurs et les Actionneurs (qui eux-mêmes sont divisés en Lampe, Moteur et Arrosage).
- sketch_ino.cpp contient les fonctions Board::setup() et Board::loop() dans lesquelles ont lieu la simulation.


Nous supposons que les mesures sont prises à une fréquence très faible : une mesure toutes les 30 min/1h par ex. En effet, la plante n'a pas besoin d'un taux d'humidité optimal en permanence, elle possède une certaine souplesse. 
Pour illustrer sa "résilience", nous lui avons assigné une quantité d'énergie, qui augmente si elle est "à son aise" et qui se détériore si les conditions sont mauvaises trop longtemps. La plante meurt si son énergie est totalement épuisée.

Différentes améliorations seront apportées dans les prochains jours !
