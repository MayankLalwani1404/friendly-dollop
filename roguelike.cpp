#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

constexpr int WIDTH = 10;
constexpr int HEIGHT = 10;

struct Entity {
    int x, y;
    int hp;
};

vector<string> mapGrid;
Entity player;
vector<Entity> enemies;

void generateMap() {
    mapGrid.assign(HEIGHT, string(WIDTH, '.'));

    // Borders
    for (int i = 0; i < WIDTH; i++) {
        mapGrid[0][i] = '#';
        mapGrid[HEIGHT - 1][i] = '#';
    }
    for (int i = 0; i < HEIGHT; i++) {
        mapGrid[i][0] = '#';
        mapGrid[i][WIDTH - 1] = '#';
    }
}

void spawnEntities() {
    player = {1, 1, 10};

    enemies.clear();
    enemies.push_back({7, 2, 3});
    enemies.push_back({5, 6, 3});
}

void draw() {
    system("cls"); // Use "clear" on Linux/macOS

    auto tempMap = mapGrid;
    tempMap[player.y][player.x] = '@';

    for (auto& e : enemies)
        tempMap[e.y][e.x] = 'E';

    for (auto& row : tempMap)
        cout << row << '\n';

    cout << "\nHP: " << player.hp << "\n";
    cout << "Enemies left: " << enemies.size() << "\n";
    cout << "Move with WASD, q to quit\n";
}

bool isEnemyAt(int x, int y, int& index) {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].x == x && enemies[i].y == y) {
            index = i;
            return true;
        }
    }
    return false;
}

void movePlayer(int dx, int dy) {
    int nx = player.x + dx;
    int ny = player.y + dy;

    if (mapGrid[ny][nx] == '#')
        return;

    int enemyIndex;
    if (isEnemyAt(nx, ny, enemyIndex)) {
        enemies[enemyIndex].hp--;
        if (enemies[enemyIndex].hp <= 0)
            enemies.erase(enemies.begin() + enemyIndex);
        return;
    }

    player.x = nx;
    player.y = ny;
}

int main() {
    srand(time(nullptr));
    generateMap();
    spawnEntities();

    char input;
    while (true) {
        draw();

        if (enemies.empty()) {
            cout << "\nYou win!\n";
            break;
        }

        cin >> input;
        if (input == 'q') break;

        if (input == 'w') movePlayer(0, -1);
        if (input == 's') movePlayer(0, 1);
        if (input == 'a') movePlayer(-1, 0);
        if (input == 'd') movePlayer(1, 0);
    }
    return 0;
}
