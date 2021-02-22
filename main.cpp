#include <fstream>
#include <iostream>
#include <string>

using namespace std;
template <int row, int col>
bool Correct_Check(char (&mass)[row][col], int strings_true)
{
    char circle[6] = {'c', 'i', 'r', 'c', 'l', 'e'};
    int i = 0, j = 0;
    for (i = 0; i < strings_true; i++) {
        for (j = 0; j < 6; j++) {
            if (circle[j] != mass[i][j]) {
                cout << "Error at column " << j + 1
                     << " :expected 'circle' at string " << i + 1 << ": "
                     << mass[i] << endl;
                return false;
            }
        }
    }
    for (i = 0; i < strings_true; i++) {
        if (mass[i][6] != '(') {
            cout << "Error at column " << j
                 << " :expected '(x x, x)' at string " << i + 1 << ": "
                 << mass[i] << endl;
            return false;
        }
    }
    for (i = 0; i < strings_true; i++) {
        for (j = 0; j < 30; j++) {
            if (mass[i][j] == '(') {
                j++;
                if (mass[i][j] == '-')
                    continue;
                while (mass[i][j] != ' ') {
                    if (!((mass[i][j] <= '9') && (mass[i][j] >= '1'))) {
                        if (i == 0)
                            i = i - 1;
                        cout << "Error at column:expected 'circle(x x, x)' "
                                "where x - "
                                "number only "
                                "at string "
                             << i + 2 << endl;
                        return false;
                    }
                    j++;
                }
                j++;
                if (mass[i][j] == '-')
                    continue;
                while (mass[i][j] != ',') {
                    if (!((mass[i][j] <= '9') && (mass[i][j] >= '1'))) {
                        if (i == 0)
                            i = i - 1;
                        cout << "Error"
                             << " : expected 'circle(x x, x)' where x - number "
                                "only "
                                "at string "
                             << i + 2 << endl;
                        return false;
                    }
                    j++;
                }
                j++;
                if (mass[i][j] != ' ') {
                    if (i == 0)
                        i = i - 1;
                    cout << "Error"
                         << ": expected 'circle(x x, x)' where x - number only "
                            "at "
                            "string "
                         << i + 2 << endl;
                    return false;
                }
                j++;
                while (mass[i][j] != ')') {
                    if (!((mass[i][j] <= '9') && (mass[i][j] >= '1'))) {
                        if (i == 0)
                            i = i - 1;
                        cout << "Error"
                             << ": expected 'circle(x x, x)' where x - number "
                                "only "
                                "at string: "
                             << i + 2 << endl;
                        return false;
                    }
                    j++;
                }
                j++;
                if (!(mass[i][j] == '\0')) {
                    if (i == 0)
                        i = i - 1;
                    cout << "Error"
                         << ": expected 'circle(x x, x)' where x - number only "
                            "at string: "
                         << i + 2 << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    const int len = 30, strings = 20;
    const char ch = '\n';
    char mass[len][strings];
    int strings_true = 0;
    int j = 0;
    int k = 0;
    string yord, xord, rad;
    string file;
    getline(cin, file);
    file.erase(0, 9);
    ifstream fs(file, ios::in | ios::binary);
    if (!fs) {
        cout << "Could't open file: " << file << endl;
        return 1;
    } //Если ошибка открытия файла, то завершаем программу

    for (int r = 0; r < strings; r++) {
        fs.getline(mass[r], len, ch); //Считываем строки в массив
    }
    for (int r = 0; r < strings; r++) {
        if (!mass[r] || !*mass[r]) {
            strings_true = r;
            break;
        } //Считываем строки в массив
    }
    int coord[strings_true][3];
    if (!(Correct_Check(mass, strings_true)))
        return 1;
    for (k = 0; k < strings_true; k++)
        for (j = 0; j < 60; j++) {
            if (mass[k][j] == '(') {
                j++;
                while (mass[k][j] != ' ') {
                    xord = xord + mass[k][j];
                    j++;
                }
                coord[k][0] = std::stoi(xord);
                j++;
                while (mass[k][j] != ',') {
                    yord = yord + mass[k][j];
                    j++;
                }
                coord[k][1] = std::stoi(yord);
                j++;
                j++;
                while (mass[k][j] != ')') {
                    rad = rad + mass[k][j];
                    j++;
                }
                coord[k][2] = std::stoi(rad);
                xord.clear();
                yord.clear();
                rad.clear();
                break;
            }
        }
    for (int i = 0; i < strings_true; i++) {
        cout << "circle(" << coord[i][0] << ' ' << coord[i][1] << ", "
             << coord[i][2] << ')' << endl;
    }
    fs.close(); //Закрываем файл
    return 0;
}
