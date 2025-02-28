#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;  
        string name = line.substr(0, colonPos); 
        int score1, score2, score3;
        if (sscanf(line.c_str() + colonPos + 1, "%d %d %d", &score1, &score2, &score3) == 3) {
            int total = score1 + score2 + score3;
            names.push_back(name);
            scores.push_back(total);
            grades.push_back(score2grade(total));
        }
    }
}
void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    string input;
    getline(cin, input);

    size_t pos = input.find(' ');
    if (pos != string::npos) {
        command = input.substr(0, pos);
        key = input.substr(pos + 1);
    } else {
        command = input;
        key = "";
    }
}



void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string name){
    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == name) {
            cout << "\n---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "\n---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string grade){
    bool found = false;
    cout << "\n---------------------------------\n";
    for (size_t i = 0; i < grades.size(); i++) {
        if (grades[i] == grade[0]) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if (!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "\n---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
