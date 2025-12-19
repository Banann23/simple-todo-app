#include <iostream> // wejscie/wyjscie
#include <fstream>  // operacje na plikach
#include <map>      // struktura map (kategoria -> lista zadan)
#include <vector>   // lista zadan

using namespace std;

// Funkcja wyswietlajaca wszystkie zadania
void showTasks(const map<string, vector<string>> &todo)
{
    if (todo.empty()) // jesli nie ma zadnych zadan
    {
        cout << "Brak zadan \n";
        return;
    }

    for (const auto &pair : todo) // iteracja po kategoriach
    {
        const string &category = pair.first;       // nazwa kategorii
        const vector<string> &tasks = pair.second; // lista zadan

        cout << "\n"
             << category << ":\n";
        for (int i = 0; i < tasks.size(); i++) // wyswietlanie zadan
        {
            cout << "  " << i + 1 << ". " << tasks[i] << "\n";
        }
    }
}

// Funkcja wczytujaca liste zadan z pliku
void loadFromFile(map<string, vector<string>> &todo, const string &filename)
{
    ifstream file(filename);

    if (!file) // jesli nie mozna otworzyc pliku
    {
        cout << "Nie mozna otworzyc pliku do odczytu\n";
        return;
    }

    todo.clear(); // czyszczenie listy zadan
    string line, currentCategory;

    while (getline(file, line))
    {
        if (line.empty()) // pominiecie pustych linii
            continue;

        if (line.front() == '[' && line.back() == ']') // nowa kategoria
        {
            currentCategory = line.substr(1, line.size() - 2);
            todo[currentCategory] = {}; // inicjalizacja pustej listy zadan
        }
        else
        {
            todo[currentCategory].push_back(line); // dodanie zadania do aktualnej kategorii
        }
    }

    file.close();
    cout << "Wczytano z pliku\n";
}

// Funkcja zapisujaca liste zadan do pliku
void saveToFile(const map<string, vector<string>> &todo, const string &filename)
{
    ofstream file(filename);

    if (!file) // jesli nie mozna otworzyc pliku
    {
        cout << "Nie mozna otworzyc pliku do zapisu\n";
        return;
    }

    for (const auto &pair : todo) // iteracja po kategoriach
    {
        file << "[" << pair.first << "]\n";  // zapis kategorii
        for (const auto &task : pair.second) // zapis zadan
        {
            file << task << "\n";
        }
    }

    file.close();
    cout << "Zapisano do pliku\n";
}

int main()
{
    map<string, vector<string>> todo; // struktura przechowujaca zadania
    int choice;                       // wybor z menu

    do
    {
        // wyswietlanie menu
        cout << "\n--- TO-DO APP ---\n";
        cout << "1. Dodaj zadanie\n";
        cout << "2. Pokaz zadania\n";
        cout << "3. Usun zadanie\n";
        cout << "4. Zapisz zadania do pliku\n";
        cout << "5. Wczytaj zadania z pliku\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> choice;
        cin.ignore(); // czyszczenie bufora wejscia

        switch (choice)
        {
        case 1: // dodawanie zadania
        {
            string category, task; // wczytanie kategorii i zadania
            cout << "Kategoria: ";
            getline(cin, category);
            cout << "Zadanie: ";
            getline(cin, task);

            todo[category].push_back(task); // dodanie zadania do kategorii
            cout << "Dodano zadanie\n";
            break;
        }

        case 2: // wyswietlanie zadan
            showTasks(todo);
            break;

        case 3: // usuwanie zadania
        {
            string category;
            int index;

            cout << "Kategoria: ";
            getline(cin, category);

            if (todo.count(category) == 0 || todo[category].empty()) // sprawdzenie czy kategoria istnieje
            {
                cout << "Brak takiej kategorii lub pusta\n";
                break;
            }

            // wyswietlanie zadan w kategorii
            for (int i = 0; i < todo[category].size(); i++)
            {
                cout << i + 1 << ". " << todo[category][i] << "\n";
            }

            cout << "Numer zadania do usuniecia: ";
            cin >> index;

            if (index < 1 || index > todo[category].size()) // sprawdzenie poprawnosci numeru
            {
                cout << "Zly numer zadania\n";
            }
            else
            {
                todo[category].erase(todo[category].begin() + index - 1);
                cout << "Usunieto zadanie\n";
            }
            cin.ignore(); // czyszczenie bufora wejscia
            break;
        }

        case 4: // zapisywanie do pliku
            saveToFile(todo, "todo.txt");
            break;

        case 5: // wczytywanie z pliku
            loadFromFile(todo, "todo.txt");
            break;

        case 0: // wyjscie
            cout << "Koniec programu.\n";
            break;

        default: // niepoprawny wybor
            cout << "Nieprawidlowy wybor\n";
            break;
        }

    } while (choice != 0); // koniec programu

    return 0;
}