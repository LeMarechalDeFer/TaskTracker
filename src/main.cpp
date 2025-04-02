#include <iostream>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <CLI/CLI.hpp>
#include "tasksManager.hpp"


#include "tasks.hpp"
#include <vector>
#include <ctime>

// Requirements
// The application should run from the command line, accept user actions and inputs as arguments, and store the tasks in a JSON file. The user should be able to:

// Add, Update, and Delete tasks
// Mark a task as in progress or done
// List all tasks
// List all tasks that are done
// List all tasks that are not done
// List all tasks that are in progress

// on assume que le chemin sera toujours celui du dossier courant. 

int main(){

    fmt::print("Hello world! Welcome to my TaskTrackerCLI, this project is for reviewing and practicing C++\n");
    // Création d'un objet JSON

    std::vector<Task> temp = {
        {
            .id = 1,
            .description = "Test",
            .status = "Done", 
            .createdAt = std::time(nullptr),
            .updatedAt = std::time(nullptr)
        }
    };
    TaskManager::LoadTasks();
    TaskManager::saveTasks(temp);
  
    return 0;
}

  // // Ajout de différentes valeurs
    // j["nom"] = "Dupont";
    // j["prenom"] = "Jean";
    // j["age"] = 30;
    // j["estActif"] = true;
    // j["competences"] = {"C++", "Python", "JavaScript"};
    
    // // Création d'un sous-objet
    // nlohmann::json adresse;
    // adresse["rue"] = "123 Avenue des Codeurs";
    // adresse["ville"] = "Programmeville";
    // adresse["codePostal"] = "75000";
    
    // // Ajout du sous-objet au JSON principal
    // j["adresse"] = adresse;
    
    // // Affichage du JSON formaté
    // fmt::print("JSON créé:\n{}\n", j.dump(4));
    
    // // Accès aux valeurs
    // fmt::print("\nAccès aux données:\n");
    // fmt::print("Nom: {}\n", j["nom"].get<std::string>());
    // fmt::print("Âge: {}\n", j["age"].get<int>());
    // fmt::print("Première compétence: {}\n", j["competences"][0].get<std::string>());
    // fmt::print("Ville: {}\n", j["adresse"]["ville"].get<std::string>());