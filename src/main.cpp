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

    CLI::App app{
        "📋 Hello world! Welcome to my TaskTrackerCLI, this project is for reviewing and practicing C++\n\n"
        "Subcommands:\n"
        "  ➤ add       Add a task (requires --description or -d)\n"
        "  ➤ delete    Delete a task by ID (--id or -i)\n"
        "  ➤ edit      Edit a task (requires --id and --description)\n"
        "  ➤ status    Change status (requires --id and --status)\n"
        "  ➤ print     Print tasks (optionally filtered by status)"
    };
    app.footer(R"(
        Examples:
        task add --description 'Buy milk'
        task delete --id 1
        task edit --id 1 --description 'Finish project'
        task status --id 1 --status done
        task print -s all
        task print --status todo

        Short options :
        id: -i, status: -s, description: -d
        Statuses allowed: all, todo, in-progress, done
    )");

    //need to add callbacks later for description printing
    auto addTaskCmd = app.add_subcommand("add", "Add a new task to your list (format: add --description 'text' or -d 'text')");
    auto deleteTaskCmd = app.add_subcommand("delete", "Delete an existing task (format: delete --id <num> or -i <num>)");
    auto editTaskCmd = app.add_subcommand("edit", "Edit a task description (format: edit --id <num> --description 'text' or -i <num> -d 'text')");
    auto changeStatusCmd = app.add_subcommand("status", "Change a task status (format: status --id <num> --status <status> or -i <num> -s <status>)");
    auto printCmd = app.add_subcommand("print", "Display tasks (format: print --status <status> or -s <status>, options: all, todo, in-progress, done)");

    std::optional<std::string> description ;
    addTaskCmd->add_option("--description, -d", description, "Description of your task, don't forget ' ' ");

    std::optional<int> deleteID ; 
    deleteTaskCmd->add_option("--id, -i", deleteID, "Id to delete");

    std::optional<int> updateID ;
    std::optional<std::string> updateDescription ;
    editTaskCmd->add_option("--id, -i", updateID, "Id to update");
    editTaskCmd->add_option("--description, -d", updateDescription, "Description to update");
    
    std::optional<int> statusID ;
    std::optional<std::string> newStatus ;
    changeStatusCmd->add_option("--id, -i", statusID, "Id to change status");
    changeStatusCmd->add_option("--status, -s", newStatus, "Status to update (todo, in-progress, done)")
    ->check(CLI::IsMember({"all", "todo", "in-progress", "done"}));

    std::optional<std::string> printingByStatus ;
    printCmd->add_option("--status, -s", printingByStatus, "Printing by status (all, todo, in-progress, done)")
    ->check(CLI::IsMember({"all", "todo", "in-progress", "done"}));

    CLI11_PARSE(app, argc, argv);

    if (argc == 1) {
    fmt::print("{}", app.help());
    return 0;
    }


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

    
};






   

    


