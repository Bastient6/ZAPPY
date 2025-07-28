🧠 Zappy — Year-End Project (B4 - EPITECH)

Zappy est un projet de fin d’année développé par des étudiants de 4ème année à EPITECH. Il s’agit d’un simulateur multijoueur mettant en œuvre une intelligence artificielle capable de coopérer pour survivre et évoluer dans un environnement concurrentiel.
📦 Composants du projet

Le projet est divisé en trois grands modules :
🖥️ Serveur (C)

    Communication bi-directionnelle avec les clients (IA & GUI).

    Gestion de la carte, des ressources, des joueurs et des règles du jeu.

    Interface de connexion réseau multi-client.

🤖 Intelligence Artificielle (Python)

    Stratégie d’évolution : collecte et gestion des ressources nécessaires à l’évolution des IA.

    Communication entre IA pour organiser les rassemblements et sacrifices nécessaires à l'évolution.

    Capacité de survie, exploration de la carte, et coopération.

🎮 Interface Graphique (C++)

    Affichage de l’état de la carte et des joueurs.

    Écran d’inventaire et d’évolution.

    Affichage de la victoire.

🎯 Objectifs
🎓 Mission du Master

    Collecter les ressources nécessaires à l’évolution de toutes les IA jusqu’au niveau 8.

    Gérer la répartition des tâches et coordonner les subordonnés.

👥 Mission des Subordonnés

    Survivre dans le temps nécessaire à la réussite de la mission du Master.

    Fournir l’assistance dans les rassemblements d’IA pour les rituels d’évolution.

📈 Résultats

    Niveau atteint : de 1 à 8

    Temps moyen de complétion : 2 à 3 minutes

    Taux de réussite : 95%

⚖️ Points forts / faibles
Situation Favorable	Situation Défavorable
Carte réduite avec beaucoup de ressources	Grande carte pauvre en ressources
🛠️ Prérequis
Pour compiler le serveur :

    GCC / Clang

    make

Pour l’IA :

    Python 3.x

Pour la GUI :

    C++17

    SFML

🚀 Lancer le projet

    Démarrer le serveur

cd server/
make
./zappy_server [options]

Lancer l’IA

cd ai/
python3 main.py [options]

Lancer la GUI

    cd gui/
    make
    ./zappy_gui [options]

👥 Équipe

    Thomas Janiaut

    Corentin Albertus

    Louis Cornu

    Amir Madaoui

    Bastien Tiffy

Merci à l’équipe pédagogique d’EPITECH pour leur accompagnement tout au long de ce projet.
