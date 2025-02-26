#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
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
        movie.id = stoi(field);

        // Read Title
        getline(ss, movie.title, ',');

        // Read Genre
        getline(ss, movie.genre, ',');

        // Read Year
        getline(ss, field, ',');
        movie.year = stoi(field);

        // Read Revenue
        getline(ss, field, ',');
        movie.revenue = stof(field);

        // Add to vector
        movies.push_back(movie);
    }

    file.close();
}




void displayMovies(const vector<Movie> &movies) {
    cout << "---------------------------------------------------------------\n";
    cout << "| ID  | Title                | Genre       | Year | Revenue ($M) |\n";
    cout << "---------------------------------------------------------------\n";

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