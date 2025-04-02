#ifndef __TASKS_HPP__
#define __TASKS_HPP__

#include <string>
#include <nlohmann/json.hpp>
#include <ctime>
// Task Properties
// Each task should have the following properties:

// id: A unique identifier for the task
// description: A short description of the task
// status: The status of the task (todo, in-progress, done)
// createdAt: The date and time when the task was created
// updatedAt: The date and time when the task was last updated
// Make sure to add these properties to the JSON file when adding a new task and update them when updating a task.


struct Task{
    int id ;
    std::string description;
    std::string status;
    std::time_t createdAt;
    std::time_t updatedAt;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Task, id, description, status, createdAt, updatedAt);
};

#endif 
