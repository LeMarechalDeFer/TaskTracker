#!/bin/bash

# Script de test pour TaskTrackerCLI
# Ce script exécute une série de commandes pour tester les fonctionnalités de l'application

echo "🔹 Test d'ajout de tâches"
./build/TaskTrackerCLI add --description 'Faire les courses'
./build/TaskTrackerCLI add --description 'Préparer le devoir de maths'
./build/TaskTrackerCLI add --description 'Réserver le train pour samedi'

echo -e "\n🔹 Test d'affichage des tâches"
./build/TaskTrackerCLI print                         # Par défaut : all
./build/TaskTrackerCLI print --status all
./build/TaskTrackerCLI print --status todo
./build/TaskTrackerCLI print --status in-progress
./build/TaskTrackerCLI print --status done

echo -e "\n🔹 Test de modification des tâches"
./build/TaskTrackerCLI edit --id 1 --description 'Faire les courses et aller à la pharmacie'
./build/TaskTrackerCLI edit --id 2 --description 'Refaire les exercices de maths'

echo -e "\n🔹 Test des cas d'erreur pour la modification"
# ❌ Cas d'erreur (description manquante)
./build/TaskTrackerCLI edit --id 3

# ❌ Cas d'erreur (id manquant)
./build/TaskTrackerCLI edit --description 'Tâche sans ID'

echo -e "\n🔹 Test de changement de statut"
./build/TaskTrackerCLI status --id 1 --status done
./build/TaskTrackerCLI status --id 2 --status in-progress

echo -e "\n🔹 Test des cas d'erreur pour le changement de statut"
# ❌ Cas d'erreur (id manquant)
./build/TaskTrackerCLI status --status todo

# ❌ Cas d'erreur (status manquant)
./build/TaskTrackerCLI status --id 3

echo -e "\n🔹 Test de suppression de tâches"
./build/TaskTrackerCLI delete --id 1
./build/TaskTrackerCLI delete --id 2

echo -e "\n🔹 Test des cas d'erreur pour la suppression"
# ❌ Cas d'erreur (id manquant)
./build/TaskTrackerCLI delete

# (facultatif) ID inexistant
./build/TaskTrackerCLI delete --id 99

echo -e "\n🔹 Test des commandes générales"
# ❌ Aucune sous-commande → devrait afficher l'aide ou ne rien faire
./build/TaskTrackerCLI

# ✅ Affiche l'aide générale
./build/TaskTrackerCLI --help

echo -e "\n🔹 Test avec un statut invalide"
# ❌ Statut invalide (tu peux gérer ce cas dans ton code !)
./build/TaskTrackerCLI print --status urgent

echo -e "\n✅ Tous les tests ont été exécutés"
