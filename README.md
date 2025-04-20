# 🎪 CYFEST

**Projet CY-Fest 🕺 — Première année de Pré-Ingénieur CY Tech, Semestre 2 2023-2024**

## 🤝 Collaborateurs
- **[Damien Kae-Nune](https://github.com/Dmkn78)**  
- **[Jean-Luc Maslanka](https://github.com/JEAN-LUC7)**  
- **[Gaspard Savès](https://github.com/gaspardsaves)**

## 📄 Description du projet
[:scroll: Lire le sujet et le cahier des charges du projet](P1-Info2_Project_CY-FEST_v1.0.pdf)

Ce projet a pour but de créer une application permettant d’organiser des festivals de musique fictifs.  
Deux types d’utilisateurs peuvent interagir avec l’application : les **organisateurs** et les **festivaliers**.

- Les **organisateurs** peuvent créer des concerts, configurer des salles, choisir des artistes, fixer des horaires et des prix.  
- Les **festivaliers** peuvent consulter les concerts à venir, sélectionner leurs places et effectuer des réservations.

L’application gère également la **durée des concerts**, en libérant automatiquement les salles une fois l’heure de fin dépassée. Elle assure aussi la **sauvegarde automatique** de l’état des salles entre chaque utilisation.

## ⚙️ Compilation
- Un exécutable prêt à l’emploi est présent sur le dépôt : `execdef`  
   👉 Pour l’exécuter, tapez : `./execdef`

### 🔧 Pour compiler vous-même :
- Lancez la commande `make` → cela génère l’exécutable `execdef`
- Exécutez le programme avec : `./execdef`
- Nettoyez les exécutables avec : `make clean`
- Réinitialisez les fichiers de sauvegarde avec : `make cleanfile`

## 🧪 Utilisation
- Au lancement, l’application :
  - Réouvre les fichiers de sauvegarde (s’ils existent),
  - Initialise `srand` (pour une future génération aléatoire lors de la création de comptes),
  - Vérifie l’heure afin de déterminer si certains concerts sont terminés.

- Les fichiers de sauvegarde permettent de restaurer :
  - Les comptes utilisateurs (`tabFest`),
  - Les salles (`tabRoom`),
  - Les concerts (`tabConcert`).

🔐 **Code d’accès à l’interface Manager : `2000`**

Pour un test complet :
1. Créez un compte utilisateur.
2. Créez au moins une salle et un concert via l’interface manager.
3. Connectez-vous en tant que festivalier pour effectuer une réservation.
4. Arrêtez ensuite proprement le programme afin de tester la persistance des données lors d’une nouvelle exécution.

### ⚠️ Avertissement important
**Le programme doit être arrêté proprement (en saisissant `0` dans l’interface principale) pour garantir la sauvegarde des données.**  
Sinon, les modifications liées aux salles, concerts, réservations ou comptes ne seront **pas enregistrées correctement**.