#include "tasksManager.hpp"
#include <fmt/core.h>
#include <iostream>
#include <fstream>

const std::string TaskManager::filename = "tasksFile.json";

void TaskManager::createJsonFile(){
    std::ifstream checkFile(filename);

    if(!checkFile.is_open()){
        fmt::println("Let's create a Taskfile");
        std::ofstream newFile(filename);
        if(newFile.is_open()){
            newFile << "[]"; // Initialize with empty JSON array
            newFile.close();
            fmt::println("TaskFile created successfully");
        } else {
            fmt::println("Error: Could not create TaskFile");
        }
    }else{
        fmt::println("There is already a TaskFile");
        checkFile.close();
    }
}

std::vector<Task> TaskManager::LoadTasks(){
    
    std::ifstream file(filename) ; 
    if (!file.is_open()) {
        fmt::println("File not found, creating new file '{}'", filename);
        TaskManager::createJsonFile();
        return {};
    }
    json j ; 
    std::vector<Task> tasksList;

    try{
        file >> j ; 
    }
    catch(const std::exception& e){
        fmt::println("Error: failled to extract JSON - {}", e.what());
        return {};
    }

    try{
        tasksList = j.get<std::vector<Task>>() ;
    }catch(const std::exception& e){
        fmt::println("Error: failled to parse (déserialisation) JSON - {}", e.what());
        return {};
    }

    fmt::println("Loading Succes !");
    return tasksList ; 
    
}

void TaskManager::saveTasks(const std::vector<Task> &tasksList){
    std::ofstream file(filename);
    if(!file.is_open()){
        fmt::println("Error: file not found");
    }
    json j ;
    try{
        j = tasksList ; 
        file << j.dump(4);
    }catch(const std::exception &e){
        fmt::println("Error: failled to serialise JSON - {}", e.what());
    }
}





// void TaskManager::printAllTasks() {
//     printTasks([](const Task&) {
//         return true; // tout afficher
//     });
// }

// void TaskManager::printTasksByStatus(const std::string& status) {
//     printTasks([&](const Task& t) {
//         return t.status == status;
//     });
// }

// void TaskManager::printTasks(const std::function<bool(const Task&)>& filter) {
//     auto tasks = LoadTasks();
//     for (const auto& task : tasks) {
//         if (filter(task)) {
//             std::cout << "- " << task.description << " [" << task.status << "]\n";
//         }
//     }
// }
