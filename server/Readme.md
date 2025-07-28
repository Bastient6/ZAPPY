# Server

Le serveur prend plusieurs arguments :

- **Port** :
  - Flag : `-p`
  - Description : Le port sur lequel il accepte les connexions.
  - Type : `int` compris entre 1024 et 49151.

- **Width de la map** :
  - Flag : `-x`
  - Description : La largeur de la carte.
  - Type : `int`.

- **Height de la map** :
  - Flag : `-y`
  - Description : La hauteur de la carte.
  - Type : `int`.

- **Noms des équipes** :
  - Flag : `-n`
  - Description : Les noms des équipes, séparés par des espaces.
  - Type : `char*`.

- **Nombre de clients par équipe** :
  - Flag : `-c`
  - Description : Le nombre de clients par équipe.
  - Type : `int`.

- **Fréquence d'exécution des actions** :
  - Flag : `-f`
  - Description : La fréquence d'exécution des actions en secondes.
  - Type : `int`.

Une fois lancé, le serveur acceptera `n * c` connexions. S'il faut en ajouter, il faut augmenter `team->maxClients`.

## Structure des Données

### Structure `team`

Les différentes équipes sont stockées dans la structure `team` qui contient :

- `name` : Le nom de l'équipe.
- `currentClients` : Le nombre de clients actuellement dans l'équipe.
- `maxClients` : Le nombre maximal de clients dans l'équipe.
- `id` : L'identifiant de l'équipe.

### Structure `client`

Une fois un client connecté au serveur, il recoit "WELCOM\n" du server il doit ensuite envoyer le nom de son équipe afin de se loguer sur le serveur. il recevra les information du jeu, et sera ajouté dans la structure `client` avec :

- `fd` : Le descripteur de fichier du client.
- `id_team` : L'identifiant de l'équipe à laquelle le client appartient.
- `return_value` : Une valeur de retour si nécessaire.

Dans le cas ou le client est un GUI, le server doit recevoir GRAPHIC est se client sera ajouté avec comme id_team 0 (celui réservé pour la team graphic)
# Structure `server`

La structure `server` est utilisée pour stocker les informations nécessaires au fonctionnement du serveur.

## Membres de la Structure

- `fd` : Le descripteur de fichier du serveur.
- `port` : Le port sur lequel le serveur accepte les connexions.
- `sockaddr_in` : Une structure contenant les informations d'adresse du serveur.
- `sockaddr_in_size` : La taille de la structure `sockaddr_in`.
- `width` : La largeur de la carte.
- `height` : La hauteur de la carte.
- `clientsNb` : Le nombre de clients par équipe.
- `freq` : La fréquence d'exécution des actions en secondes.
- `nbteams` : Le nombre d'équipes.
- `teams` : Un pointeur vers un tableau des équipes.
- `clients` : Un pointeur vers un tableau des clients.

## Description des Membres

- `fd` : Le descripteur de fichier est utilisé pour identifier le socket du serveur.
- `port` : Le port sur lequel le serveur accepte les connexions des clients.
- `sockaddr_in` : Cette structure contient des informations sur l'adresse du serveur, comme l'adresse IP et le port.
- `sockaddr_in_size` : La taille de la structure `sockaddr_in`.
- `width` : La largeur de la carte du jeu.
- `height` : La hauteur de la carte du jeu.
- `clientsNb` : Le nombre de clients autorisés par équipe.
- `freq` : La fréquence d'exécution des actions du jeu, en secondes.
- `nbteams` : Le nombre total d'équipes dans le jeu.
- `teams` : Un pointeur vers un tableau des équipes participantes.
- `clients` : Un pointeur vers un tableau des clients connectés au serveur.


# handle commande 

## ia
  les commandes des ia sont géré dans handle_command_ia.c avec la fonction handle_command_ia


## gui
  les commandes du graphique sotn géré dans handle_command_graphique.c avec la fonction handle_command_graphique

  toutes les commandes qui doivent être execute par le server sans instruction du client doivent être appelé avec le nom de la commande ainsi que l'id du client