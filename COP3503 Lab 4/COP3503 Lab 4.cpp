#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector <string> names;
vector <int> nums;
vector <string> themes;
vector <double> prices;
vector <int> minifigs;
vector <int> pieces;
ifstream file;

void loadData() {
    bool completed = false;
    int count = 0;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream parse(line);
            if (completed) {
                for (int i = 0; i <= 5; i++) {
                    switch (i) {
                    case 0: {
                        getline(parse, line, ',');
                        nums.push_back(stoi(line));
                        break;
                    }
                    case 1: {
                        getline(parse, line, ',');
                        themes.push_back(line);
                        break;
                    }
                    case 2: {
                        getline(parse, line, ',');
                        names.push_back(line);
                        break;
                    }
                    case 3: {
                        getline(parse, line, ',');
                        if (line == "")
                            minifigs.push_back(stoi("0"));
                        else
                            minifigs.push_back(stoi(line));
                        break;
                    }
                    case 4: {
                        getline(parse, line, ',');
                        if (line == "")
                            pieces.push_back(stoi("0"));
                        else
                            pieces.push_back(stoi(line));
                        break;
                    }
                    case 5: {
                        getline(parse, line, '\n');
                        if (line == "\r")
                            prices.push_back(stof("0.0"));
                        else
                            prices.push_back(stof(line));
                        count++;
                        break;
                    }
                    }
                }
            }
            completed = true;
        }
    }
    file.close();
}

void print(int index) {
    cout << "Name: " << names[index] << endl;
    cout << "Number: " << nums[index] << endl;
    cout << "Theme: " << themes[index] << endl;
    cout << "Price: $" << prices[index] << endl;
    cout << "Minifigures: " << minifigs[index] << endl;
    cout << "Piece count: " << pieces[index] << endl << endl;
}

int main() {
    cout << std::fixed << setprecision(2);
    cout << "Which file(s) to open?\n";
    cout << "1. lego1.csv" << endl;
    cout << "2. lego2.csv" << endl;
    cout << "3. lego3.csv" << endl;
    cout << "4. All 3 files" << endl;
    int option;
    cin >> option;
    switch (option) {
    case 1:
        file.open("lego1.csv");
        loadData();
        break;
    case 2:
        file.open("lego2.csv");
        loadData();
        break;
    case 3:
        file.open("lego3.csv");
        loadData();
        break;
    case 4:
        file.open("lego1.csv");
        loadData();
        file.open("lego2.csv");
        loadData();
        file.open("lego3.csv");
        loadData();
        break;
    }
    cout << "1. Most Expensive set" << endl;
    cout << "2. Largest piece count" << endl;
    cout << "3. Search for set name containing..." << endl;
    cout << "4. Search themes..." << endl;
    cout << "5. Part count information" << endl;
    cout << "6. Price information" << endl;
    cout << "7. Minifigure information" << endl;
    cout << "8. If you bought one of everything..." << endl;
    cout << "0. Exit" << endl;
    int choice;
    cin >> choice;
    cin.get();
    switch (choice) {
    case 0:
        break;
    case 1: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        int index = 0;
        float max = prices[0];
        for (unsigned int i = 0; i < prices.size(); i++) {
            if (prices[i] >= max) {
                max = prices[i];
                index = i;
            }
        }
        cout << "The most expensive set is:" << endl;
        print(index);
        break;
    }
    case 2: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        int index = 0;
        float max = pieces[0];
        for (unsigned int i = 0; i < pieces.size(); i++) {
            if (pieces[i] >= max) {
                max = pieces[i];
                index = i;
            }
        }
        cout << "The set with the highest parts count:" << endl;
        print(index);
        break;
    }
    case 3: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        bool completed = false, located = false;
        string searchTerm;
        getline(cin, searchTerm);
        for (unsigned int i = 0; i < names.size(); i++) {
            if (names[i].find(searchTerm) != string::npos) {
                if ((names[i].find(searchTerm) != string::npos) && !completed) {
                    cout << "Sets matching \"" << searchTerm << "\":" << endl;
                    completed = true;
                }
                cout << nums[i] << " " << names[i] << " $" << prices[i] << " " << endl;
                located = true;
            }
            else if ((i == names.size() - 1) && !located) {
                cout << "No sets found matching that search term" << endl;
            }
        }
        break;
    }
    case 4: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        bool completed = false, located = false;
        string searchTheme;
        getline(cin, searchTheme);
        for (unsigned int i = 0; i < themes.size(); i++) {
            if (themes[i].find(searchTheme) != string::npos) {
                if ((themes[i].find(searchTheme) != string::npos) && !completed) {
                    cout << "Sets matching \"" << searchTheme << "\":" << endl;
                    completed = true;
                }
                cout << nums[i] << " " << names[i] << " $" << prices[i] << " " << endl;
                located = true;
            }
            else if ((i == themes.size() - 1) && !located) {
                cout << "No sets found matching that search term" << endl;
            }
        }
        break;
    }
    case 5: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        int avg = 0, total = 0, count = 0;
        for (unsigned int i = 0; i < pieces.size(); i++) {
            total += pieces[i];
            if (pieces[i] > 0)
                count++;
        }
        avg = total / count;
        cout << "Average part count for " << count << " sets: " << avg << endl << endl;
        break;
    }
    case 6: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        int maxIndex = 0, minIndex = 0, count = 0;
        double total = 0.0, avg = 0.0, max = 0.0;
        double min = prices[0];
        for (unsigned int i = 0; i < prices.size(); i++) {
            total += prices[i];
            if (prices[i] > max) {
                max = prices[i];
                maxIndex = i;
            }
            if (prices[i] < min) {
                min = prices[i];
                minIndex = i;
            }
            count++;
        }
        avg = total / count;
        cout << "Average price for " << count << " sets: $" << avg << endl << endl;
        cout << "Least expensive set:" << endl;
        print(minIndex);
        cout << "Most expensive set:" << endl;
        print(maxIndex);
        break;
    }
    case 7: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        int maxIndex = 0, count = 0, total = 0, max = 0, avg = 0;
        for (unsigned int i = 0; i < minifigs.size(); i++) {
            total += minifigs[i];
            if (minifigs[i] > max) {
                max = minifigs[i];
                maxIndex = i;
            }
            count++;
        }
        avg = total / count;
        cout << "Average number of minifigures: " << avg << endl << endl;
        cout << "Set with the most minifigures:" << endl;
        print(maxIndex);
        break;
    }
    case 8: {
        cout << "Total number of sets: " << prices.size() << endl << endl;
        double sumPrice = 0.0;
        int sumPieces = 0, sumMinifigs = 0;
        for (unsigned int i = 0; i < pieces.size(); i++) {
            sumPrice += prices[i];
            sumPieces += pieces[i];
            sumMinifigs += minifigs[i];
        }
        cout << "If you bought one of everything..." << endl;
        cout << "It would cost: $" << sumPrice << endl;
        cout << "You would have " << sumPieces << " pieces in your collection" << endl;
        cout << "You would have an army of " << sumMinifigs << " minifigures!" << endl;
        break;
    }
    }
    return 0;
}