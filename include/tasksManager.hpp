#ifndef __TASKSMANAGER_HPP__
#define __TASKSMANAGER_HPP__

#include "tasks.hpp"
#include <vector>
#include <string>
#include <functional>

// task list --json
// task list
// task list --status done
// task list --status todo


class TaskManager{
    public:
        static std::vector<Task> LoadTasks(const std::string& file);
        static void saveTasks(const std::string& file, const std::vector<Task>& tasks);

        static void printAllTasks(const std::string& file);
        static void printTasksByStatus(const std::string& file, const std::string& status);

        static void addTask(const std::string& file, const std::string& description);
        static void deleteTask(const std::string& file, int id);
        static void editTaskDescription(const std::string& file, int id, const std::string& newDescription);
        static void changeTaskStatus(const std::string& file, int id, const std::string& newStatus);

    private :
        static void printTasks(const std::function<bool(const Task&)>& filter);
        
};


#endif 

