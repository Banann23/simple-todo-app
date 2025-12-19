#include <iostream> // input/output
#include <fstream>  // file operations
#include <map>      // map structure (category -> list of tasks)
#include <vector>   // list of tasks

using namespace std;

// Function to display all tasks
void showTasks(const map<string, vector<string>> &todo)
{
    if (todo.empty()) // no tasks
    {
        cout << "No tasks\n";
        return;
    }

    for (const auto &pair : todo) // iterate over categories
    {
        const string &category = pair.first;
        const vector<string> &tasks = pair.second;

        cout << "\n"
             << category << ":\n";
        for (int i = 0; i < tasks.size(); i++) // display tasks
        {
            cout << "  " << i + 1 << ". " << tasks[i] << "\n";
        }
    }
}

// Function to load tasks from file
void loadFromFile(map<string, vector<string>> &todo, const string &filename)
{
    ifstream file(filename);

    if (!file) // cannot open file
    {
        cout << "Cannot open file for reading\n";
        return;
    }

    todo.clear(); // clear current tasks
    string line, currentCategory;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (line.front() == '[' && line.back() == ']') // new category
        {
            currentCategory = line.substr(1, line.size() - 2);
            todo[currentCategory] = {};
        }
        else
        {
            todo[currentCategory].push_back(line); // add task to category
        }
    }

    file.close();
    cout << "Loaded from file\n";
}

// Function to save tasks to file
void saveToFile(const map<string, vector<string>> &todo, const string &filename)
{
    ofstream file(filename);

    if (!file) // cannot open file
    {
        cout << "Cannot open file for writing\n";
        return;
    }

    for (const auto &pair : todo)
    {
        file << "[" << pair.first << "]\n";  // save category
        for (const auto &task : pair.second) // save tasks
        {
            file << task << "\n";
        }
    }

    file.close();
    cout << "Saved to file\n";
}

int main()
{
    map<string, vector<string>> todo; // tasks storage
    int choice;                       // menu choice

    do
    {
        // display menu
        cout << "\n--- TO-DO APP ---\n";
        cout << "1. Add task\n";
        cout << "2. Show tasks\n";
        cout << "3. Remove task\n";
        cout << "4. Save tasks to file\n";
        cout << "5. Load tasks from file\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice)
        {
        case 1: // add task
        {
            string category, task;
            cout << "Category: ";
            getline(cin, category);
            cout << "Task: ";
            getline(cin, task);

            todo[category].push_back(task);
            cout << "Task added\n";
            break;
        }

        case 2: // show tasks
            showTasks(todo);
            break;

        case 3: // remove task
        {
            string category;
            int index;

            cout << "Category: ";
            getline(cin, category);

            if (todo.count(category) == 0 || todo[category].empty())
            {
                cout << "No such category or empty\n";
                break;
            }

            for (int i = 0; i < todo[category].size(); i++)
            {
                cout << i + 1 << ". " << todo[category][i] << "\n";
            }

            cout << "Task number to remove: ";
            cin >> index;

            if (index < 1 || index > todo[category].size())
            {
                cout << "Invalid task number\n";
            }
            else
            {
                todo[category].erase(todo[category].begin() + index - 1);
                cout << "Task removed\n";
            }
            cin.ignore(); // clear buffer
            break;
        }

        case 4: // save to file
            saveToFile(todo, "todo.txt");
            break;

        case 5: // load from file
            loadFromFile(todo, "todo.txt");
            break;

        case 0: // exit
            cout << "Exiting program.\n";
            break;

        default: // invalid choice
            cout << "Invalid choice\n";
            break;
        }

    } while (choice != 0);

    return 0;
}
