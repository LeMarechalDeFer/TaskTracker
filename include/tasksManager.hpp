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

class TasksManager{
    public:     
        static void printAllTasks();
        static void printTasksByStatus(const std::string& status);

        static void addTask(const std::string& description); //ok
        static void deleteTask(int id); //ok
        static void editTaskDescription(int id, const std::string& newDescription);//ok
        static void changeTaskStatus(int id, const std::string& newStatus); //ok
        

    private :
        static void saveTasks(const std::vector<Task>& tasksList); //ok
        static const std::string filename;  //ok
        static std::vector<Task> LoadTasks(); //ok
        static void printTasks(const std::function<bool(const Task&)>& filter); 
        static void createJsonFile(); //ok
        static int getNextTaskId(const std::vector<Task> &tasksList); //ok
        
};


#endif 

