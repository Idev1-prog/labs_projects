#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void sorting(std::vector<T>& data) {
	std::sort(data.begin(), data.end(), [](T a, T b) { return a > b; });
}
//C++98