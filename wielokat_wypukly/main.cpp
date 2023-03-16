#include <iostream>
#include <math.h>
using namespace std;
struct Point {
	int x, y;
};

double calculateField(double a, double b, double c) {
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double calculateSideLength(double x, double y, double x2, double y2) {
	return sqrt(((x2-x) * (x2-x)) + ((y2-y) * (y2-y)));
}

int main() {
	int n;
	double sum=0;
	double a, b, c;
	cin >> n;
	Point* points = (Point*)malloc(n * sizeof(Point));
	for (int i = 0; i < n; i++) {
		cin >> points[i].x;
		cin >> points[i].y;
	}

	for (int i = 0; i < n-2; i++) {
		a = calculateSideLength(points[0].x, points[0].y, points[i + 1].x, points[i + 1].y);
		b = calculateSideLength(points[i+1].x, points[i+1].y, points[i + 2].x, points[i + 2].y);
		c = calculateSideLength(points[0].x, points[0].y, points[i + 2].x, points[i + 2].y);
		sum += calculateField(a, b, c);
	}
	cout << floor(sum);

	return 0;
}