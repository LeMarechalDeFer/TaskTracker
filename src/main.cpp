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

    fmt::print("📋 Bienvenue dans TaskTrackerCLI — Test des fonctions principales\n");

    // 🔹 1. Test - Adding a task
    fmt::print("\n[TEST] Adding a task...\n");
    TasksManager::addTask("Do my AI homework, no it's more fun to do cpp");

    // 🔹 2. Test - Modifying the description
    fmt::print("\n[TEST] Modifying task description ID 1...\n");
    TasksManager::editTaskDescription(1, "Read AI docs and do Bayesian Networks and do homework blablabla");

    // 🔹 3. Test - Changing status
    fmt::print("\n[TEST] Changing task ID 1 status to 'in-progress'...\n");
    TasksManager::changeTaskStatus(1, "in-progress");

    // 🔹 4. Test - Deleting a task
    fmt::print("\n[TEST] Deleting task ID 1...\n");
    TasksManager::deleteTask(1);

    // 🔹 5. Test - Deleting a non-existent task
    fmt::print("\n[TEST] Deleting non-existent task ID 999...\n");
    TasksManager::deleteTask(999);

    // Print all
    fmt::print("\n[TEST] Printing all Tasks...\n");
    TasksManager::printAllTasks();

    fmt::print("\n[TEST] Printing status Tasks...\n");
    std::string status = "todo";
    TasksManager::printTasksByStatus(status);




    fmt::print("\n✅ All basic tests have been executed.\n");
}
