#include <iostream>
#include <cmath>
#include <clocale>

using namespace std;

struct Point {
	int x;
	int y;
};

struct Circle {
	Point centre;
	int r;
};

enum Posision_status {
	INTERSECT,
	MATCH,
	CONSERN,
	NOT_RELATED,
	INSIDE,
	NO_INFO = 400
};

double calculate_points_distance(Circle circleA, Circle circleB) {
	return sqrt(pow(circleB.centre.x - circleA.centre.x, 2) +
		pow(circleB.centre.y - circleA.centre.y, 2));
}

Posision_status not_related_check(Circle circleA, Circle circleB) {
	double d = calculate_points_distance(circleA, circleB);
	if (d > (circleA.r + circleB.r)) {
		return NOT_RELATED;
	}
	return NO_INFO;
}

Posision_status match_check(Circle circleA, Circle circleB) {
	if (circleA.r == circleB.r &&
		circleA.centre.y == circleB.centre.y &&
		circleA.centre.x == circleB.centre.x)
		return MATCH;
	return NO_INFO;
}

Posision_status consern_check(Circle circleA, Circle circleB) {
	double d = calculate_points_distance(circleA, circleB);
	if (d == (circleA.r + circleB.r) || d == abs(circleA.r - circleB.r)) {
		return CONSERN;
	}
	return NO_INFO;
}

Posision_status inside_check(Circle circleA, Circle circleB) {
	double d = calculate_points_distance(circleA, circleB);
	if (d + circleA.r <= circleB.r) {
		return INSIDE;
	}
	else if (d + circleB.r <= circleA.r) {
		return INSIDE;
	}
	return NO_INFO;
}

Posision_status intersect_check(Circle circleA, Circle circleB) {
	double d = calculate_points_distance(circleA, circleB);
	if (abs(circleA.r - circleB.r) < d && d < circleA.r + circleB.r) {
		return INTERSECT;
	}
	return NO_INFO;
}

Posision_status* code_status(Circle circleA, Circle circleB) {
	static Posision_status results[5];
	results[0] = not_related_check(circleA, circleB);
	results[1] = match_check(circleA, circleB);
	results[2] = consern_check(circleA, circleB);
	results[3] = inside_check(circleA, circleB);
	results[4] = intersect_check(circleA, circleB);
	return results;
}


void encode_status(Posision_status* statuses) {
	cout << "Circle statuses:" << endl;

	for (int i = 0; i < 5; i++) {
		if (statuses[i] != NO_INFO) {
			switch (statuses[i]) {
			case INTERSECT:
				cout << "  - INTERSECT" << endl;
				break;
			case MATCH:
				cout << "  - MATCH" << endl;
				break;
			case CONSERN:
				cout << "  - CONSERN" << endl;
				break;
			case NOT_RELATED:
				cout << "  - NOT_RELATED" << endl;
				break;
			case INSIDE:
				cout << "  - INSIDE" << endl;
				break;
			default:
				break;
			}
		}
	}
}

/*
int main()
{
	Circle c1, c2;
	setlocale(LC_ALL, "Rus");
	cout << "¬ведите денные по 1-у кругу (в формате x, y, rad): ";
	cin >> c1.centre.x >> c1.centre.y >> c1.r;
	cout << "¬ведите денные по 2-у кругу (в формате x, y, rad): ";
	cin >> c2.centre.x >> c2.centre.y >> c2.r;
	Posision_status* results4 = code_status(c1, c2);
	encode_status(results4);
}
*/