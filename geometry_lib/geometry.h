#pragma once

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

double calculate_points_distance(Circle circleA, Circle circleB);

Posision_status not_related_check(Circle circleA, Circle circleB);

Posision_status match_check(Circle circleA, Circle circleB);

Posision_status consern_check(Circle circleA, Circle circleB);

Posision_status inside_check(Circle circleA, Circle circleB);

Posision_status intersect_check(Circle circleA, Circle circleB);

Posision_status* code_status(Circle circleA, Circle circleB);

void encode_status(Posision_status* statuses);

