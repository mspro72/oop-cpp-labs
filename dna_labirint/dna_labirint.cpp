#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <locale.h>

#include <algorithm>
#include <queue>

using namespace std;

// Отключаем выравнивание, чтобы структуры точно совпадали с бинарным форматом BMP
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{0x4D42};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};
};

struct BMPInfoHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{0};
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};

struct RGB {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};
#pragma pack(pop)

struct Point {
    int y;
    int x;
};

void saveBMP(const string& filename, vector<vector<RGB>>& image) {
    int height = image.size();
    int width = image[0].size();
    int padding = (4 - (width * 3) % 4) % 4;

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    infoHeader.size = sizeof(BMPInfoHeader);
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.planes = 1;
    infoHeader.bit_count = 24;
    infoHeader.size_image = (width * 3 + padding) * height;

    fileHeader.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    fileHeader.file_size = fileHeader.offset_data + infoHeader.size_image;

    ofstream file(filename, ios::binary);
    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    uint8_t pad[3] = { 0, 0, 0 };
    for (int y = height - 1; y >= 0; --y) {
        file.write(reinterpret_cast<char*>(image[y].data()), width * sizeof(RGB));
        file.write(reinterpret_cast<char*>(pad), padding);
    }
}

//Функция для чтения BMP файла в двумерный вектор структур
vector<vector<RGB>> readBMP(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return {};
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.file_type != 0x4D42 || infoHeader.bit_count != 24) {
        cerr << "Поддерживаются только 24-битные BMP файлы!" << endl;
        return {};
    }

    int width = infoHeader.width;
    int height = abs(infoHeader.height);

    //Создаем двумерный массив (вектор векторов) размера [height][width]
    vector<vector<RGB>> pixels(height, vector<RGB>(width));
    file.seekg(fileHeader.offset_data, ios::beg);

    int padding = (4 - (width * 3) % 4) % 4;
    bool isTopDown = infoHeader.height < 0;

    for (int y = 0; y < height; ++y) {
        int targetY = isTopDown ? y : (height - 1 - y);
        for (int x = 0; x < width; ++x) {
            file.read(reinterpret_cast<char*>(&pixels[targetY][x]), sizeof(RGB));
        }
        file.seekg(padding, ios::cur);
    }

    return pixels;
}

// Волновой алгоритм поиска пути
vector<Point> findWavePath(const vector<vector<RGB>>& image, Point start, Point finish) {
    int height = image.size();
    int width = image[0].size();

    //Карта расстояний (-1 не посещено)
    vector<vector<int>> dist(height, vector<int>(width, -1));
    queue<Point> q;

    dist[start.y][start.x] = 0;
    q.push(start);

    int dy[] = { -1, 1, 0, 0 };
    int dx[] = { 0, 0, -1, 1 };
    bool found = false;

    //Волна
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.y == finish.y && curr.x == finish.x) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int ny = curr.y + dy[i];
            int nx = curr.x + dx[i];

            if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                //Условие проходимости: пиксель должен быть белым (или близким к белому)
                //Черный цвет (стены) имеет значения R=0, G=0, B=0. Белый — R=255, G=255, B=255
				//Проверяем, что пиксель белый или он имеет цвет старта или финиша (красный или зеленый)
                auto& px = image[ny][nx];
                bool isWhite = px.red > 200 && px.green > 200 && px.blue > 200;
                bool isRed = px.red > 150 && px.green < 100 && px.blue < 100;
                bool isGreen = px.green > 150 && px.red < 100 && px.blue < 100;
                if ((isWhite || isRed || isGreen) && dist[ny][nx] == -1) {
                    dist[ny][nx] = dist[curr.y][curr.x] + 1;
                    q.push({ ny, nx });
                }
            }
        }
    }

    if (!found) return {}; // Пути нет

    //Восстановление пути
    vector<Point> path;
    Point curr = finish;
    path.push_back(curr);

    while (curr.y != start.y || curr.x != start.x) {
        for (int i = 0; i < 4; ++i) {
            int ny = curr.y + dy[i];
            int nx = curr.x + dx[i];

            if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                if (dist[ny][nx] == dist[curr.y][curr.x] - 1) {
                    curr = { ny, nx };
                    path.push_back(curr);
                    break;
                }
            }
        }
    }

    reverse(path.begin(), path.end());
    return path;
}

int main() {
	setlocale(LC_ALL, "rus");
    vector<vector<RGB>> mazeImage = readBMP("ДНК_Лабиринт.bmp");

    if (mazeImage.empty()) {
        return 1;
    }

    cout << "Успешно загружено!" << endl;
    cout << "Ширина: " << mazeImage[0].size() << endl;
    cout << "Высота: " << mazeImage.size() << endl;
    //Задаем точки старта и финиша (в пикселях)
    //Красный начало. Зелёный конец
    Point start = { 685, 135 };  // красный
    Point finish = { 522, 1253 };  // зелёный

    //Запускаем поиск пути прямо по массиву пикселей
    vector<Point> path = findWavePath(mazeImage, start, finish);

    if (path.empty()) {
        cout << "Путь через лабиринт на картинке не найден!" << endl;
    }
    else {
        cout << "Путь успешно найден! Количество шагов (пикселей): " << path.size() << endl;
        cout << "Старт: (" << start.y << "," << start.x << ") -> Финиш: (" << finish.y << "," << finish.x << ")" << endl;
    }

    for (auto& p : path)
        mazeImage[p.y][p.x] = { 255, 255, 0 }; 

    saveBMP("ДНК_Лабиринт_solved.bmp", mazeImage);
    cout << "Изображение сохранено!" << endl;

    return 0;
}