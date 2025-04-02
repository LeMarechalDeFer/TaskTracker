# TaskTracker
Cpp - Roadmap.sh

## Starting the project

Firt of all, you need to install vcpkg. You can install it by following this docummentation :
https://learn.microsoft.com/fr-fr/vcpkg/get_started/get-started?pivots=shell-bash
Don't forget to add vcpkg to your path and modify the CMakeUserPresets.json file to match your vcpkg path.

You need vcpkg to install nlohmann/json, cli11 & ftm library. You can install it by running the following commands:

```bash
vcpkg add port nlohmann-json
vcpkg add port ftm
vcpkg add port cli11
vcpkg install
```


To run the program, you can use the following commands:

```bash
cmake --preset=default
cmake --build build
./build/TaskTracker
```

## Description

Task tracker is a project used to track and manage your tasks. In this task, you will build a simple command line interface (CLI) to track what you need to do, what you have done, and what you are currently working on. This project will help you practice your programming skills, including working with the filesystem, handling user inputs, and building a simple CLI application.

Requirements
The application should run from the command line, accept user actions and inputs as arguments, and store the tasks in a JSON file. The user should be able to:

Add, Update, and Delete tasks
Mark a task as in progress or done
List all tasks
List all tasks that are done
List all tasks that are not done
List all tasks that are in progress


Here are some constraints to guide the implementation:

You can use any programming language to build this project.
Use positional arguments in command line to accept user inputs.
Use a JSON file to store the tasks in the current directory.
The JSON file should be created if it does not exist.
<!-- Use the native file system module of your programming language to interact with the JSON file.
Do not use any external libraries or frameworks to build this project. -->
Ensure to handle errors and edge cases gracefully.

Task Properties
Each task should have the following properties:

id: A unique identifier for the task
description: A short description of the task
status: The status of the task (todo, in-progress, done)
createdAt: The date and time when the task was created
updatedAt: The date and time when the task was last updated
Make sure to add these properties to the JSON file when adding a new task and update them when updating a task.

## Architecture Reflection

Question between keeping data in RAM with data structures or increasing the number of I/O operations by being stateless.
Conclusion: choice to base on Linux philosophy: Start Fast, execute, exit.
 Do one thing and do it well.