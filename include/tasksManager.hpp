#ifndef __TASKSMANAGER_HPP__
#define __TASKSMANAGER_HPP__

#include "tasks.hpp"
#include <vector>
#include <string>
#include <functional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// task list --json
// task list
// task list --status done
// task list --status todo
// task add "Lire la doc"
// task list
// task list --status done
// task delete 3
// task edit 2 "Faire du café"
// task status 2 in-progress

class TaskManager{
    public:
        static std::vector<Task> LoadTasks(); //ok
        static void saveTasks(const std::vector<Task>& tasksList); //ok

        static void printAllTasks();
        static void printTasksByStatus(const std::string& status);

        static void addTask(const std::string& description); 
        static void deleteTask(int id);
        static void editTaskDescription(int id, const std::string& newDescription);
        static void changeTaskStatus(int id, const std::string& newStatus);
        

    private :
        static const std::string filename;  //ok
        static void printTasks(const std::function<bool(const Task&)>& filter); 
        static void createJsonFile(); //ok
        
};


#endif 

