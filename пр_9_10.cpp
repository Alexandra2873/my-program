//вариант 18

#include <iostream>
#include <fstream>
using namespace std;
#include <string>


enum Genre {
    rpg,
    strategy,
    gonki,
    aviasim,
    drugie
};

struct Platforms {
    bool pc;
    bool mobile;
    bool gamepad;
};

struct Game {
    string name;
    string razrab;
    float price;
    int auditoria;
    Platforms platforms;
    Genre genre;
};

int countPlatforms(Platforms p) {
    int count = 0;
    if (p.pc) count++;
    if (p.mobile) count++;
    if (p.gamepad) count++;
    return count;
}

void printGame(const Game& g) {
    cout << "Название: " << g.name << endl;
    cout << "Студия: " << g.razrab << endl;
    cout << "Цена: " << g.price << endl;
    cout << "Аудитория: " << g.auditoria << " млн" << endl;
    cout << "Платформы: ";
    if (g.platforms.pc) cout << "PC ";
    if (g.platforms.mobile) cout << "Mobile ";
    if (g.platforms.gamepad) cout << "Gamepad ";
    cout << endl;
}

void print(Game g[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\nИгра " << i+1 << endl;
        cout << "Название: " << g[i].name << endl;
        cout << "Студия: " << g[i].razrab << endl;
        cout << "Цена: " << g[i].price << endl;
        cout << "Аудитория: " << g[i].auditoria << " млн" << endl;
        cout << "Платформ: " << countPlatforms(g[i].platforms) << endl;
    }
}

void puzirokSort(Game g[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (countPlatforms(g[j].platforms) < countPlatforms(g[j+1].platforms)) {
                Game temp = g[j];
                g[j] = g[j+1];
                g[j+1] = temp;
            }
        }
    }
}

void changeGame(Game& g, string newName, float newPrice) {
    g.name = newName;
    g.price = newPrice;
}



void save(Game games[], int length) {
    ofstream fout("games.txt");
    for (int i = 0; i < length; i++) {
        fout << games[i].name << " | Разработчик: " << games[i].razrab << " | Цена: " << games[i].price << " | Аудитория: " << games[i].auditoria << " млн" << endl;
    }
    fout.close();
    cout << "Структура записана в файл games.txt" << endl;
}


void read() {
    string str;
    ifstream fin("games.txt");
    if (fin.is_open()) {
        cout << "Файл прочитан:" << endl;
        while (!fin.eof()) {
            getline(fin, str);
            cout << str << endl;
        }
    }
    fin.close();
}


void save_bin(Game games[], int length) {
    ofstream fout("games.bin", ios::binary | ios::out);
    if (!fout.is_open()) return;

    for (int i = 0; i < length; i++) {
        
        size_t str_size = games[i].name.size();
        fout.write((char*)&str_size, sizeof(str_size));
        fout.write(games[i].name.c_str(), str_size);

        size_t razrab_size = games[i].razrab.size();
        fout.write((char*)&razrab_size, sizeof(razrab_size));
        fout.write(games[i].razrab.c_str(), razrab_size);

        fout.write((char*)&games[i].price, sizeof(games[i].price));
        fout.write((char*)&games[i].auditoria, sizeof(games[i].auditoria));
        fout.write((char*)&games[i].platforms, sizeof(games[i].platforms));
        fout.write((char*)&games[i].genre, sizeof(games[i].genre));
    }
    fout.close();
    cout << "Бинарный файл записан." << endl;
}


void read_bin(int length) {
    ifstream fin("games.bin", ios::binary | ios::in);
    if (!fin.is_open()) return;

    cout << "Чтение из бинарного файла" << endl;
    for (int i = 0; i < length; i++) {
        Game temp;
        size_t str_size;

        fin.read((char*)&str_size, sizeof(str_size));
        char* buffer = new char[str_size + 1];
        fin.read(buffer, str_size);
        buffer[str_size] = '\0';
        temp.name = buffer;
        delete[] buffer;

        fin.read((char*)&str_size, sizeof(str_size));
        buffer = new char[str_size + 1];
        fin.read(buffer, str_size);
        buffer[str_size] = '\0';
        temp.razrab = buffer;
        delete[] buffer;

        fin.read((char*)&temp.price, sizeof(temp.price));
        fin.read((char*)&temp.auditoria, sizeof(temp.auditoria));
        fin.read((char*)&temp.platforms, sizeof(temp.platforms));
        fin.read((char*)&temp.genre, sizeof(temp.genre));

        printGame(temp);
        cout << endl;
    }
    fin.close();
}


int main() {
    Game games[20] = {
        {"Microsoft Flight Simulator", "Asobo Studio", 9.99, 2, {1,0,1}, aviasim},
        {"IL-2 Sturmovik", "1C Game Studios", 0, 1, {1,0,1}, aviasim},
        {"DCS World", "Eagle Dynamics", 0, 3, {1,0,1}, aviasim},
        {"X-Plane 12", "Laminar Research", 0, 1, {1,0,1}, aviasim},
        {"War Thunder", "Gaijin Entertainment", 0, 25, {1,1,1}, aviasim},
        {"StarCraft II", "Blizzard Entertainment", 0, 6, {1,0,0}, strategy},
        {"Age of Empires IV", "Relic Entertainment", 0, 5, {1,0,0}, strategy},
        {"Civilization VI", "Firaxis Games", 29.99, 8, {1,1,1}, strategy},
        {"Total War: Three Kingdoms", "Creative Assembly", 0, 3, {1,0,0}, strategy},
        {"Company of Heroes 3", "Relic Entertainment", 0, 2, {1,0,1}, strategy},
        {"Cyberpunk 2077", "CD Projekt Red", 0, 18, {1,0,1}, rpg},
        {"The Witcher 3", "CD Projekt Red", 0, 30, {1,1,1}, rpg},
        {"Forza Horizon 5", "Playground Games", 0, 12, {1,0,1}, gonki},
        {"Genshin Impact", "miHoYo", 4.99, 60, {1,1,1}, rpg},
        {"Minecraft", "Mojang Studios", 0, 140, {1,1,1}, drugie},
        {"Among Us", "Innersloth", 0, 50, {1,1,1}, drugie},
        {"FIFA 23", "EA Sports", 4.99, 20, {1,1,1}, drugie},
        {"Call of Duty", "Activision", 0, 40, {1,1,1}, drugie},
        {"Apex Legends", "Respawn Entertainment", 0, 35, {1,1,1}, drugie},
        {"Fortnite", "Epic Games", 0, 80, {1,1,1}, drugie}
    };


    save(games, 20);
    cout << endl << endl;
    read();
    cout << endl << endl;
    save_bin(games, 20);
    cout << endl << endl;
    read_bin(20);
    cout << endl << endl;


    Game avia[20];                //авиасимуляторы с аудиторией >= 1 млн
    int aviaсount = 0;
    
    for (int i = 0; i < 20; i++) {
        if (games[i].genre == aviasim && games[i].auditoria >= 1) {
            avia[aviaсount] = games[i];
            aviaсount++;
        }
    }

    puzirokSort(avia, aviaсount);          //сорт по платформам


    cout << endl << "Вывод данных по конкретной игре (первой):" << endl;
    printGame(games[0]);



    Game copy[20];
    for (int i = 0; i < 20; i++) copy[i] = games[i];
    
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19 - i; j++) {
            if (copy[j].price < copy[j+1].price) {
                Game temp = copy[j];
                copy[j] = copy[j+1];
                copy[j+1] = temp;
            }
        }
    }
    
    cout << endl << "3 самых дорогих игр:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << copy[i].name << " - " << copy[i].price << endl;
    }

    cout << endl << "Вывод структуры после изменения игры:" << endl;
    changeGame(games[0], "Flight Simulator 2024", 12.99);
    printGame(games[0]);



    Game strategii[20];
    int strategсount = 0;
    
    for (int i = 0; i < 20; i++) {
        if (games[i].genre == strategy && games[i].platforms.pc == true) {
            strategii[strategсount] = games[i];
            strategсount++;
        }
    }

    cout << endl << "Вывод структуры после сортировки по платформам:" << endl;
    print(avia, aviaсount);

    cout << endl << "Вывод всех стратегий для PC:" << endl;
    print(strategii, strategсount);
    
    return 0;
}
