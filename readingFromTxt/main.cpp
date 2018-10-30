#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

struct Point{
    float x;
    float y;
};

QFile file("points.txt");
QTextStream in(&file);
QStringList points;
QString line;
Point quadOne[5];

void readFile();
void getPoints();
float distance(Point A, Point B);
float perimeter();
float area();

int main() {
    if (!file.exists()){
        cout << "Can't find file \"points.txt\"";
        return -1;
    }
    if(!file.open(QIODevice::ReadOnly)) {
        cout << "Can't read file \"points.txt\"";
        return -1;
    }
    readFile();
    cout << "\nPolygon's area - " << area() << "\nPolygon's perimeter - " << perimeter();
}

void readFile() {
    int i=0;

    while(!in.atEnd()) {
        line = in.readLine();
        points = line.split(";");

        quadOne[i].x = points.at(0).toFloat();
        quadOne[i].y = points.at(1).toFloat();
        cout << " X: " << quadOne[i].x;
        if (quadOne[i].x > 0) cout << " ";
        cout << "  Y: " << quadOne[i].y << endl;
        i++;
    }
}

float distance(Point A, Point B) {
    float distance = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
    return distance;
}

float perimeter() {
    float AE = distance(quadOne[0], quadOne[4]);
    float BE = distance(quadOne[1], quadOne[4]);
    float BC = distance(quadOne[1], quadOne[2]);
    float CD = distance(quadOne[2], quadOne[3]);
    float DA = distance(quadOne[0], quadOne[3]);
    float perimeter = AE + BE + BC + CD + DA;
    return perimeter;
}

float area() {
    float AE = distance(quadOne[0], quadOne[4]);
    float AB = distance(quadOne[0], quadOne[1]);
    float BE = distance(quadOne[1], quadOne[4]);
    float BC = distance(quadOne[1], quadOne[2]);
    float CA = distance(quadOne[2], quadOne[0]);
    float CD = distance(quadOne[2], quadOne[3]);
    float DA = distance(quadOne[0], quadOne[3]);

    float p1 = (AB + BC + CA) / 2;
    float p2 = (CD + DA + CA) / 2;
    float p3 = (AE + BE + AB) / 2;
    float area1 = sqrt(p1*(p1 - AB)*(p1 - BC)*(p1 - CA));
    float area2 = sqrt(p2*(p2 - CD)*(p2 - DA)*(p2 - CA));
    float area3 = sqrt(p3*(p3 - BE)*(p3 - AE)*(p3 - AB));
    float area = area1 + area2 + area3;
    return area;
}
