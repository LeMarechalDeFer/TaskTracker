#include <iostream>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <CLI/CLI.hpp>
#include "tasksManager.hpp"
#include <string>
#include <optional>

// Requirements
// The application should run from the command line, accept user actions and inputs as arguments, and store the tasks in a JSON file. The user should be able to:

// Add, Update, and Delete tasks
// Mark a task as in progress or done
// List all tasks
// List all tasks that are done
// List all tasks that are not done
// List all tasks that are in progress

// on assume que le chemin sera toujours celui du dossier courant. 

int main(int argc, char** argv){

    CLI::App app{"Hello world! Welcome to my TaskTrackerCLI, this project is for reviewing and practicing C++\n"};
    
    auto addTaskCmd = app.add_subcommand("add");
    auto deleteTaskCmd = app.add_subcommand("delete");
    auto editTaskCmd = app.add_subcommand("edit");
    auto changeStatusCmd = app.add_subcommand("status");
    auto printCmd = app.add_subcommand("print");

    std::optional<std::string> description ;
    addTaskCmd->add_option("--description", description, "Description of your task, don't forget ' ' ");

    std::optional<int> deleteID ; 
    deleteTaskCmd->add_option("--id", deleteID, "Id to delete");

    std::optional<int> updateID ;
    std::optional<std::string> updateDescription ;
    editTaskCmd->add_option("--id", updateID, "Id to update");
    editTaskCmd->add_option("--description", updateDescription, "Description to update");
    
    std::optional<int> statusID ;
    std::optional<std::string> newStatus ;
    changeStatusCmd->add_option("--id", statusID, "Id to change status");
    changeStatusCmd->add_option("--status", newStatus, "Status to update (todo, in-progress, done)")
    ->check(CLI::IsMember({"all", "todo", "in-progress", "done"}));

    std::optional<std::string> printingByStatus ;
    printCmd->add_option("--status", printingByStatus, "Printing by status (all, todo, in-progress, done)")
    ->check(CLI::IsMember({"all", "todo", "in-progress", "done"}));

    CLI11_PARSE(app, argc, argv);

    if(description.has_value()){
        TasksManager::addTask(description.value());
    }

    if(deleteID.has_value()){
        TasksManager::deleteTask(deleteID.value());
    }

    if(updateID.has_value() && updateDescription.has_value()){
        TasksManager::editTaskDescription(updateID.value(), updateDescription.value());
    }else if(updateID.has_value() && !updateDescription.has_value()){
        fmt::print("❌ Missing new description.\n💡 Format: edit --id <yourID> --description 'your new description'\n");
    }else if(!updateID.has_value() && updateDescription.has_value()){
        fmt::print("❌ Missing ID of the task to edit.\n💡 Format: edit --id <yourID> --description 'your new description'\n");
    }

    if (statusID.has_value() && newStatus.has_value()) {
    TasksManager::changeTaskStatus(statusID.value(), newStatus.value());
    } else if (statusID.has_value() && !newStatus.has_value()) {
        fmt::print("❌ Missing new status value.\n💡 Format: status --id <yourID> --status 'your new status' (all, todo, in-progress, done)\n");
    } else if (!statusID.has_value() && newStatus.has_value()) {
        fmt::print("❌ Missing new status Id.\n💡 Format: status --id <yourID> --status 'your new status' (all, todo, in-progress, done)\n\n");
    }

    if(printingByStatus.has_value()){
        if(printingByStatus.value() == "all"){
            TasksManager::printAllTasks();
        }else{
            TasksManager::printTasksByStatus(printingByStatus.value());
        }
    }

}



   

    


