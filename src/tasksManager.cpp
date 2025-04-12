#include "tasksManager.hpp"
#include <fmt/core.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <cstdlib> 

const std::string TasksManager::filename = [] {
    const char* home = std::getenv("HOME");
    if (!home) throw std::runtime_error("HOME environment variable not set");

    std::filesystem::path configDir = std::filesystem::path(home) / ".tasktrackercli";
    std::filesystem::path filePath = configDir / "tasksFile.json";

    if (!std::filesystem::exists(configDir)) {
        std::filesystem::create_directories(configDir);
        fmt::print("📂 Created config directory: {}\n", configDir.string());
    }

    if (!std::filesystem::exists(filePath)) {
        fmt::print("📄 Will create tasks file at: {}\n", filePath.string());
    }

    return filePath.string();
}();


// const std::string TasksManager::filename = "tasksFile.json";

void TasksManager::createJsonFile(){
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

std::vector<Task> TasksManager::LoadTasks(){
    
    std::ifstream file(filename) ; 
    if (!file.is_open()) {
        fmt::println("File not found, creating new file '{}'", filename);
        TasksManager::createJsonFile();
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

void TasksManager::saveTasks(const std::vector<Task> &tasksList){
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

void TasksManager::addTask(const std::string& description){
    
    

    try {
        std::vector<Task> tasksList = LoadTasks();
        std::time_t now = std::time(nullptr);

        int newId = getNextTaskId(tasksList);
        tasksList.emplace_back(Task{
            .id = newId,
            .description = description,
            .status = "todo", 
            .createdAt = now,
            .updatedAt = now
        });

        fmt::println("Success: Added task {} - '{}'", newId, description);
        saveTasks(tasksList);
    }
    catch(const std::exception& e) {
        fmt::println("Error: Failed to add task - {}", e.what());
    }
}

int TasksManager::getNextTaskId(const std::vector<Task> &tasksList){

    std::vector<Task>::const_iterator it ;
    int maxId = 0;

    for(it = tasksList.begin(); it != tasksList.end(); it++){
        if(it->id > maxId){
            maxId = it->id ;
        }
    }
    return maxId +1 ;
}



void TasksManager::deleteTask(int id){
    try {
        std::vector<Task> tasksList = LoadTasks();
        std::vector<Task>::iterator it = tasksList.begin(); 
        bool found = false;

        while (it != tasksList.end()) {
            if(it->id == id){
                int deletedId = it->id;
                tasksList.erase(it);
                fmt::println("Successful deletion of {} ID", deletedId);
                found = true;
                break;
            }
            it++;
        }

        if (!found) {
            fmt::println("Error: Task with ID {} not found", id);
            return;
        }

        saveTasks(tasksList);
    } catch(const std::exception& e) {
        fmt::println("Error while deleting task: {}", e.what());
    }
}

void TasksManager::editTaskDescription(int id, const std::string& newDescription){
    try
    {
        std::vector<Task> tasksList = LoadTasks();
        std::vector<Task>::iterator it = tasksList.begin(); 
        bool found = false;

        while (it != tasksList.end())
        {
            if(it->id == id){ 
                it->description = newDescription;
                it->updatedAt = std::time(nullptr);
                fmt::println("Successful editing of {} ID", it->id);
                found = true;
                break;
            }
            it++;
        }

        if(!found){
            fmt::println("Task {} not found", id);
            return ;
        }

        saveTasks(tasksList);
    }
    catch(const std::exception& e)
    {
        fmt::println("Error while editing task: {}", e.what());
    }
}

void TasksManager::changeTaskStatus(int id, const std::string& newStatus){
    try
    {
        std::vector<Task> tasksList = LoadTasks();
        std::vector<Task>::iterator it = tasksList.begin(); 
        bool found = false;

        while (it != tasksList.end())
        {
            if(it->id == id){ // Correction: = changé en ==
                it->status = newStatus;
                it->updatedAt = std::time(nullptr);
                fmt::println("Successful status editing of {} ID", it->id);
                found = true;
                break;
            }
            it++;
        }
        
        if(!found){
            fmt::println("Task {} not found", id);
            return;
        }

        saveTasks(tasksList);
    }
    catch(const std::exception& e)
    {
        fmt::println("Error while editing status: {}", e.what());
    }
}

// void TasksManager::printTasks(){

// }

void TasksManager::printAllTasks(){
    std::vector<Task> tasksList = LoadTasks();

    if(tasksList.empty()){
        fmt::println("📭 Any task to display...");
    }

    fmt::println("📋 Your Tasks List");

    for (const auto& task : tasksList) {
        std::string statusEmoji;

        if (task.status == "todo") statusEmoji = "📄";
        else if (task.status == "in-progress") statusEmoji = "🛠️ ";
        else if (task.status == "done") statusEmoji = "✅";
        else statusEmoji = "❓";

        // timestamps format 
        std::tm* created = std::localtime(&task.createdAt);
        std::tm* updated = std::localtime(&task.updatedAt);
        char createdStr[20];
        char updatedStr[20];
        std::strftime(createdStr, sizeof(createdStr), "%Y-%m-%d %H:%M", created);
        std::strftime(updatedStr, sizeof(updatedStr), "%Y-%m-%d %H:%M", updated);

        fmt::print("[{}] {} {:<30} | Status: {:<13} | Created: {} | Updated: {}\n",
                task.id,
                statusEmoji,
                task.description,
                task.status,
                createdStr,
                updatedStr
            );
    }

}

void TasksManager::printTasksByStatus(const std::string &status){
    std::vector<Task> tasksList = LoadTasks();

    if(tasksList.empty()){
        fmt::println("📭 Any task to display...");
    }

    fmt::println("📋 Your '{}' Tasks List", status);

    for(const auto& task : tasksList){
        if(status == task.status){
            std::string statusEmoji;

            if (task.status == "todo") statusEmoji = "📄";
            else if (task.status == "in-progress") statusEmoji = "🛠️ ";
            else if (task.status == "done") statusEmoji = "✅";
            else statusEmoji = "❓";

            // timestamps format 
            std::tm* created = std::localtime(&task.createdAt);
            std::tm* updated = std::localtime(&task.updatedAt);
            char createdStr[20];
            char updatedStr[20];
            std::strftime(createdStr, sizeof(createdStr), "%Y-%m-%d %H:%M", created);
            std::strftime(updatedStr, sizeof(updatedStr), "%Y-%m-%d %H:%M", updated);

            fmt::print("[{}] {} {:<30} | Status: {:<13} | Created: {} | Updated: {}\n",
                task.id,
                statusEmoji,
                task.description,
                task.status,
                createdStr,
                updatedStr
            );
        }
    }


}
