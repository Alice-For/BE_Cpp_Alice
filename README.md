# HappySeed - outil de régulation d'une plante d'intérieur

Nous souhaitons optimiser l'environnement d'une plante d'intérieur en jouant sur différents paramètres pour qu'elle puisse s'épanouir au mieux. Nous supposons qu'elle se situe dans une pièce où se trouve une lampe, un système d'arrosage et une fenêtre commandables.
Notre système est donc constitué de 4 capteurs :
- un détecteur d’humidité (placé dans la terre du pot)
- un détecteur de température
- un détecteur de luminosité
- un détecteur du taux de CO2

Il comporte également 5 actionneurs :
- un servo-moteur permettant d'actionner l'ouverture / la fermeture de la fenêtre
- un système de chauffage, modélisé par un servo-moteur également
- un ventilateur, modélisé par un servo-moteur
- une lampe possédant un état haut et un état bas (allumée / éteinte)
- un système d'arrosage à deux états (robinet ouvert / fermé)

Nous supposons que les mesures sont prises à une fréquence très faible : une mesure toutes les 30 min/1h par ex. En effet, la plante n'a pas besoin d'un taux d'humidité optimal en permanence, elle possède une certaine souplesse.
