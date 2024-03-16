#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;
#define SIZE 10000


void readDistribution(double distr[26]) {
    ifstream fin("distribution.txt");
    for (int i = 0; i < 26; ++i) {
        fin >> distr[i];
    }
}

void hist(char* str, double freq[]) {
    int size = strlen(str);
    for (int i = 0; i < 26; ++i) {
        freq[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        if (isalpha(str[i])) {
            char c = tolower(str[i]);
            ++freq[c - 'a'];
        }
    }
    for (int i = 0; i < 26; ++i) {
        freq[i] = freq[i] / size * 100;
    }
}

double distance(double e[], double c[]) {
    double result = 0;
    for (int i = 0; i < 26; ++i) {
        result += ((c[i] - e[i]) * (c[i] - e[i]) / e[i]);
    }
    return result;
}

char shift(char c, int offset) {
    offset = offset % 26;
    if (islower(c)) {
        if (c - offset < 'a') {
            c = c + 26 - offset;
        }
        else {
            c = c - offset;
        }
        return c;
    }
    else if (isupper(c)) {
        if (c - offset < 'A') {
            c = c + 26 - offset;
        }
        else {
            c = c - offset;
        }
        return c;
    }
    else {
        return c;
    }
}

void shiftStr(char str[], int offset, char result[]) {
    int size = strlen(str);
    for (int i = 0; i < size; ++i) {
        result[i] = shift(str[i], offset);
    }
    result[size] = '\0';
}

void decode(char str[], double e[], char result[]) {
    double min = -1;
    int minOffset = 0;
    for (int offset = 0; offset < 26; ++offset) {
        char cand[SIZE];
        shiftStr(str, offset, cand);
        double c[26];
        hist(cand, c);
        double dist = distance(e, c);
        if (min == -1 || dist < min) {
            min = dist;
            minOffset = offset;
        }
    }
    shiftStr(str, minOffset, result);
}

void showMenu() {
    cout << "Select an option:\n"
        "a - encode\n"
        "b - decode\n"
        "m - menu\n"
        "e - to exit\n"
        "option: ";
}

int main() {

    char option = 'm';
    showMenu();
    while (option != 'e') {
        cin >> option;
        if (option == 'a') {
            int cypher;
            char text[SIZE], result[SIZE];
            cout << "Enter the cypher: ";
            cin >> cypher;
            cin.ignore();
            cout << "Enter the text: ";
            cin.getline(text, SIZE);
            shiftStr(text, cypher, result);
            cout << "The deciphered text is: " << result;
            cout << '\n' << '\n';
            showMenu();
        } else if (option == 'b') {
            char text[SIZE];
            cout << "Enter the text: ";
            cin.ignore();
            cin.getline(text, SIZE);
            double distr[26];
            readDistribution(distr);
            char result[SIZE];
            decode(text, distr, result);
            cout << "The deciphered text is: " << result << '\n';
            cout << endl;
            showMenu();

        } else if (option == 'm') {
            cout << '\n';
            showMenu();
        } else if (option == 'e') {
            cout << "Program ended!\n";
        } else {
            cout << "Invalid command!" << '\n' << '\n';
            showMenu();
        }
    }

    /*
    Example for 'b' option:
    
    Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.
    
    */
    return 0;
}
