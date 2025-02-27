#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>

//A
using namespace std;

// Define the struct
struct Movie {
    int id;
    string title;
    string genre;
    int year;
    int revenue;
};

//a
void loadCSV(vector<Movie> &movies, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    getline(file, line);  // Skip header row

    while (getline(file, line)) {
        stringstream ss(line);
        Movie movie;
        string field;

        // Read ID
        getline(ss, field, ',');
        if (field.empty()) continue;  // Skip invalid rows
        movie.id = stoi(field);

        // Read Title
        getline(ss, movie.title, ',');

        // Read Genre
        getline(ss, movie.genre, ',');

        // Read Year
        getline(ss, field, ',');
        if (field.empty()) continue;  // Ensure year is valid
        movie.year = stoi(field);

        // Read Revenue
        getline(ss, field, ',');
        if (field.empty()) continue;  // Ensure revenue is valid
        movie.revenue = stoi(field);

        // Add to vector
        movies.push_back(movie);
    }

    file.close();

}




void displayMovies(const vector<Movie> &movies) {
    cout << "-----------------------------------------------------------\n";
    cout << "| ID  | Title                | Genre       | Year | Revenue ($M) |\n";
    cout << "-----------------------------------------------------------\n";

    for (const auto &movie : movies) {
        cout << "| " << movie.id << " | "
             << movie.title << " | "
             << movie.genre << " | "
             << movie.year << " | "
             << fixed << setprecision(2) << movie.revenue << " |\n";
    }
    cout << "---------------------------------------------------------------\n";
}



int searchMovieByTitle(const vector<Movie> &movies, const string &title) {
    for (size_t i = 0; i < movies.size(); i++) {
        if (movies[i].title == title) {
            return i;
        }
    }
    return -1;
}


map<string, int> countMoviesByGenre(const vector<Movie> &movies) {
    map<string, int> genreCount;
    for (const auto &movie : movies) {
        genreCount[movie.genre]++;
    }
    return genreCount;
}


void sortByRevenue(vector<Movie> &movies) {
    sort(movies.begin(), movies.end(), [](const Movie &a, const Movie &b) {
        return a.revenue > b.revenue;
    });
}


void menu(vector<Movie> &movies) {
    int choice;
    string title;

    do {
        cout << "\nMENU:\n";
        cout << "1. Display all movies\n";
        cout << "2. Search for a movie by title\n";
        cout << "3. Count movies by genre\n";
        cout << "4. Sort movies by revenue\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            displayMovies(movies);
        }
        else if (choice == 2) {
            cout << "Enter movie title: ";
            cin.ignore();
            getline(cin, title);
            int index = searchMovieByTitle(movies, title);
            if (index != -1) {
                cout << "Found: " << movies[index].title << " (" << movies[index].year << ")\n";
            } else {
                cout << "Movie not found!\n";
            }
        }
        else if (choice == 3) {
            map<string, int> genreCount = countMoviesByGenre(movies);
            for (const auto &pair : genreCount) {
                cout << pair.first << ": " << pair.second << " movies\n";
            }
        }
        else if (choice == 4) {
            sortByRevenue(movies);
            displayMovies(movies);
        }
        else if (choice == 5) {
            cout << "Exiting\n";
        }
        else {
            cout << "Invalid choice try again\n";
        }
    } while (choice != 5);
}



int main() {
    vector<Movie> movies;

    // Load CSV Data
    loadCSV(movies, "movies.csv");

    // Show Menu
    menu(movies);

    return 0;
}
