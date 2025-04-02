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
