/*Вариант 18.
Определить структурный тип, описывающий компьютерные игры (название игры,
студия разработчик, стоимость подписки, объем аудитории игроков,
поддерживаемые платформы: PC, mobile, gamepad; тип: RPG, стратегия, гонки,
авиасимулятор и др.). Заполнить структурный массив 20-ю записями. Переписать из
исходного массива в другой массив, информацию только об авиасимуляторах с
аудиторией от 1 миллиона пользователей. Затем новый массив отсортировать по
поддерживаемым платформам. Вывести все данные по конкретной игре. Вывести 3
самых дорогих игр. Реализовать функцию изменения игры. В отдельный массив
поместить все стратегии для PC. Реализовать вывод отфильтрованных данных в виде
оберточной функции.*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
    string genre; 
};

void printgame(Game g) {
    cout << "Название: " << g.name << ", Студия: " << g.razrab << endl;
    cout << "Цена: " << g.price << ", Аудитория: " << g.auditoria << " млн" << endl;
    cout << "Жанр: " << g.genre << ", Платформы: ";
    if (g.platforms.pc) cout << "PC ";
    if (g.platforms.mobile) cout << "Mobile ";
    if (g.platforms.gamepad) cout << "Gamepad ";
    cout << endl;
}

void change(Game &g, string newName, float newPrice) {
    g.name = newName;
    g.price = newPrice;
}

int countplatforms(Platforms p) {
    int count = 0;
    if (p.pc) count = count + 1;
    if (p.mobile) count = count + 1;
    if (p.gamepad) count = count + 1;
    return count;
}

void printfiltr(Game filterarr[], int count, string title) {
    cout << endl;
    cout << " " << title << endl << endl;
    
    if (count == 0) {
        cout << "нет данных" << endl;
        return;
    }
    for (int i = 0; i < count; i++) {
        printgame(filterarr[i]);
    }
}

// запись в бинарный файл
void savebin(Game g[], int n) {
    ofstream fout("games.bin", ios::binary);
    for (int i = 0; i < n; i++) {
       
        fout.write((char*)&g[i].price, sizeof(g[i].price));
        fout.write((char*)&g[i].auditoria, sizeof(g[i].auditoria));
        fout.write((char*)&g[i].platforms, sizeof(g[i].platforms));
        
        int nameLen = g[i].name.length();
        fout.write((char*)&nameLen, sizeof(nameLen));
        fout.write(g[i].name.c_str(), nameLen);

        int razrabLen = g[i].razrab.length();
        fout.write((char*)&razrabLen, sizeof(razrabLen));
        fout.write(g[i].razrab.c_str(), razrabLen);

        int genreLen = g[i].genre.length();
        fout.write((char*)&genreLen, sizeof(genreLen));
        fout.write(g[i].genre.c_str(), genreLen);
    }
    fout.close();
}

//  чтение из бинарного файла
void readbin(Game g[], int n) {
    ifstream fin("games.bin", ios::binary);
    if (fin.is_open()) {
        for (int i = 0; i < n; i++) {
            fin.read((char*)&g[i].price, sizeof(g[i].price));
            fin.read((char*)&g[i].auditoria, sizeof(g[i].auditoria));
            fin.read((char*)&g[i].platforms, sizeof(g[i].platforms));
            
            int nameLen;
            fin.read((char*)&nameLen, sizeof(nameLen));
            g[i].name.resize(nameLen);
            fin.read(&g[i].name[0], nameLen);

            int razrabLen;
            fin.read((char*)&razrabLen, sizeof(razrabLen));
            g[i].razrab.resize(razrabLen);
            fin.read(&g[i].razrab[0], razrabLen);

            int genreLen;
            fin.read((char*)&genreLen, sizeof(genreLen));
            g[i].genre.resize(genreLen);
            fin.read(&g[i].genre[0], genreLen);
        }
        fin.close();
    }
}

void savetext(Game g[], int n) {
    ofstream fout("price.txt");
    for (int i = 0; i < n; i++) {
        fout << g[i].price << endl;
    }
    fout.close();
}

void readtext(Game g[], int n) {
    ifstream fin("price.txt");
    float p;
    int i = 0;
    while (fin >> p) {
        if (i < n) {
            g[i].price = p;
            i = i + 1;
        }
    }
    fin.close();
    cout << "Цены обновлены из файла" << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    Game games[20] = {
        {"Microsoft Flight Simulator", "Asobo Studio", 59.9, 2, {1,0,1}, "авиасимулятор"},
        {"IL-2 Sturmovik", "1C Game Studios", 39.9, 1, {1,0,0}, "авиасимулятор"},
        {"DCS World", "Eagle Dynamics", 10.0, 3, {1,0,1}, "авиасимулятор"},
        {"X-Plane 12", "Laminar Research", 49.9, 1, {1,0,1}, "авиасимулятор"},
        {"War Thunder", "Gaijin", 0, 25, {1,1,1}, "авиасимулятор"},
        {"StarCraft II", "Blizzard", 0, 6, {1,0,0}, "стратегия"},
        {"Age of Empires IV", "Relic", 39.9, 5, {1,0,0}, "стратегия"},
        {"Civilization VI", "Firaxis", 29.9, 8, {1,1,1}, "стратегия"},
        {"Total War", "Creative Assembly", 49.9, 3, {1,0,0}, "стратегия"},
        {"Company of Heroes 3", "Relic", 59.9, 2, {1,0,1}, "стратегия"},
        {"Cyberpunk 2077", "CD Projekt", 50.0, 18, {1,0,1}, "RPG"},
        {"The Witcher 3", "CD Projekt", 29.9, 30, {1,1,1}, "RPG"},
        {"Forza Horizon 5", "Playground", 49.9, 12, {1,0,1}, "гонки"},
        {"Genshin Impact", "miHoYo", 0, 60, {1,1,1}, "RPG"},
        {"Minecraft", "Mojang", 26.0, 140, {1,1,1}, "другое"},
        {"Among Us", "Innersloth", 4.9, 50, {1,1,1}, "другое"},
        {"FIFA 23", "EA Sports", 69.9, 20, {1,1,1}, "другое"},
        {"Call of Duty", "Activision", 69.9, 40, {1,1,1}, "другое"},
        {"Apex Legends", "Respawn", 0, 35, {1,1,1}, "другое"},
        {"Fortnite", "Epic Games", 0, 80, {1,1,1}, "другое"}
    };

    Game gamesbin[20];
    
    savebin(games, 20);
    readbin(gamesbin, 20);
    
    savetext(gamesbin, 20);
    readtext(gamesbin, 20);

    cout << "\nвывод конкретной игры" << endl;
    printgame(gamesbin[10]); 

    Game puzirok[20];
    for(int i = 0; i < 20; i++) {
        puzirok[i] = gamesbin[i];
    }
    
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19 - i; j++) {
            if (puzirok[j].price < puzirok[j+1].price) {
                Game temp = puzirok[j];
                puzirok[j] = puzirok[j+1];
                puzirok[j+1] = temp;
            }
        }
    }
    
    cout << "\nтоп-3 дорогих игр" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i+1 << ". " << puzirok[i].name << puzirok[i].price << " $" << endl;
    }

    cout << "\nпосле изменения" << endl;
    change(gamesbin[0], "Flight Simulator 2024", 79.99);
    printgame(gamesbin[0]);

    Game aviaarr[20];
    int aviacount = 0;
    for (int i = 0; i < 20; i++) {
        if (gamesbin[i].genre == "авиасимулятор" && gamesbin[i].auditoria >= 1) {
            aviaarr[aviacount] = gamesbin[i];
            aviacount = aviacount + 1;
        }
    }

    for (int i = 0; i < aviacount - 1; i++) {
        for (int j = 0; j < aviacount - i - 1; j++) {
            if (countplatforms(aviaarr[j].platforms) < countplatforms(aviaarr[j+1].platforms)) {
                Game temp = aviaarr[j];
                aviaarr[j] = aviaarr[j+1];
                aviaarr[j+1] = temp;
            }
        }
    }

    Game strategarr[20];
    int strategyCount = 0;
    for (int i = 0; i < 20; i++) {
        if (gamesbin[i].genre == "стратегия" && gamesbin[i].platforms.pc == true) {
            strategarr[strategyCount] = gamesbin[i];
            strategyCount = strategyCount + 1;
        }
    }

    printfiltr(aviaarr, aviacount, "авиасимуляторы от 1 млн (отсортированы)");
    printfiltr(strategarr, strategyCount, "стратегии для PC");

    return 0;
}
