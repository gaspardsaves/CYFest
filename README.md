1. Avant l’exécution
Concernant la compilation :
- Un exécutable déjà fonctionnel est présent sur le dépôt et s’appelle execdef
	→ Pour l’exécuter tapez la commande ./execdef
- Si vous souhaitez compiler vous-même la commande make clean permet d’effacer les exécutables et vous pouvez alors compiler en utilisant la commande make de même que précédemment l’exécutable généré s’appelle execdef et la commande ./execdef permet de l’exécuter
- Vous pouvez réinitialiser les sauvegardes en supprimant et en recréant les fichiers de sauvegardes en utilisant la commande make cleanfile

2. Pendant l’exécution
Concernant la navigation dans l’interface :
	A l’exécution du code :
- Lors du lancement du programme, l’ensemble des fichiers de sauvegarde sont ré-ouverts s’ils existent, la fonction srand est également initialisée pour son éventuel usage futur lors d’une création de compte utilisateur, et une vérification de l’heure est effectuée afin de savoir si des concerts ne se sont pas terminés depuis la dernière ouverture de l’application.
- La réouverture de ces fichiers permet également de restaurer les comptes utilisateur, l’état des salles et des concerts et de recréer les tableaux  de structures contenant ces différents éléments (tabFest étant le tableau contenant les structures des festivaliers, tabRoom contenant les structures de salles et tabConcert contenant les structures de concert.
- A savoir le code permettant d’entrer dans l’interface manager est 2000

Pour un test complet de l’application, il convient de créer au moins un compte utilisateur, une salle et un concert sur l’interface manager avant de tester la réservation en se connectant sur un compte utilisateur, par la suite, le programme peut être arrêté proprement afin de le ré-exécuter pour tester les sauvegardes.

Avertissement : Si le programme n’est pas correctement arrêté en saisissant 0 sur l’interface initiale, la sauvegarde sur les fichiers ne se fera pas, il est donc important de se déconnecter et d’arrêter le programme proprement sans quoi les modification de salle, de concert, de réservation ou de compte utilisateur ne seront pas correctement enregistrés.
