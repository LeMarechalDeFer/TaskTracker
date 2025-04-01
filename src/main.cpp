#include <iostream>
#include <fmt/core.h>
#include <nlohmann/json.hpp>


// using json = nlohmann::json;

int main(){
    // std::cout << "Hello world !" << std::endl;
    fmt::print("Hello world\n");
    // Création d'un objet JSON
    nlohmann::json j;
    
    // Ajout de différentes valeurs
    j["nom"] = "Dupont";
    j["prenom"] = "Jean";
    j["age"] = 30;
    j["estActif"] = true;
    j["competences"] = {"C++", "Python", "JavaScript"};
    
    // Création d'un sous-objet
    nlohmann::json adresse;
    adresse["rue"] = "123 Avenue des Codeurs";
    adresse["ville"] = "Programmeville";
    adresse["codePostal"] = "75000";
    
    // Ajout du sous-objet au JSON principal
    j["adresse"] = adresse;
    
    // Affichage du JSON formaté
    fmt::print("JSON créé:\n{}\n", j.dump(4));
    
    // Accès aux valeurs
    fmt::print("\nAccès aux données:\n");
    fmt::print("Nom: {}\n", j["nom"].get<std::string>());
    fmt::print("Âge: {}\n", j["age"].get<int>());
    fmt::print("Première compétence: {}\n", j["competences"][0].get<std::string>());
    fmt::print("Ville: {}\n", j["adresse"]["ville"].get<std::string>());
    return 0;
}