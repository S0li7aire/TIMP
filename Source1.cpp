#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

int check(int row, int col, char** lab, int** visited, queue<int>& plan) {
	int empty = 0;
	if (!visited[row][col]) {
		if (lab[row + 1][col] == '.') {
			empty++;
			if (!visited[row + 1][col]) {
				plan.push(row + 1);
				plan.push(col);
			}
		}
		if (lab[row - 1][col] == '.') {
			empty++;
			if (!visited[row - 1][col]) {
				plan.push(row - 1);
				plan.push(col);
			}
		}
		if (lab[row][col + 1] == '.') {
			empty++;
			if (!visited[row][col + 1]) {
				plan.push(row);
				plan.push(col + 1);
			}
		}
		if (lab[row][col - 1] == '.') {
			empty++;
			if (!visited[row][col - 1]) {
				plan.push(row);
				plan.push(col - 1);
			}
		}
		visited[row][col] = 1;
		return 4 - empty;
	}
	return 0;
}

int main() {
	int N;
	try
	{
		std::fstream file("input.txt", std::ios_base::in);
		if (!file.is_open())
		{
			throw (-1);
		}
		else
		{
			
			int size{};
			file >> size;
			if ((size < 3) || (size > 50))
			{
				throw (-2);
			}
			
			char** data{ new char* [size] };
			for (int i{}; i < size; ++i)
			{
				data[i] = new char[size];
				for (int j{}; j < size; ++j)
				{
					if (file.eof())
					{
						throw (-3);
					}
					else
					{
						file >> data[i][j];
					}
				}
			}
			if ((data[0][0] == '#') || (data[size - 1][size - 1] == '#'))
			{
				throw (-4);
			}
			else
			{
				file.close();
			}
		}
	}
	catch (int errorid)
	{
		switch (errorid)
		{
		case -1:
			std::cerr << "Error: file 'input.txt' not found" << std::endl;
			break;
		case -2:
			std::cerr << "Error: 'N < 3' or 'N > 50'" << std::endl;
			break;
		case -3:
			std::cerr << "Error: labyrinth not full" << std::endl;
			break;
		case -4:
			std::cerr << "Error: left upper or right lower corner not empty" << std::endl;
			break;
		default:
			std::cerr << "Error: unknown" << std::endl;
		}
		return errorid;
	}

	std::fstream file("input.txt", std::ios_base::in);
	file >> N;
	char** lab = new char* [N + 2];
	int** visited = new int* [N + 2];
	for (int i = 0; i < N + 2; i++) {
		lab[i] = new char[N + 2];
		visited[i] = new int[N + 2];
		for (int j = 0; j < N + 2; j++) {
			visited[i][j] = 0;
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1) {
				lab[i][j] = '*';
			}
			else {
				file >> lab[i][j];
			}
		}
	}
	queue <int> plan;
	plan.push(1);
	plan.push(1);
	int walls = 0;
	file.close();
	while (!plan.empty()) {
		int row = plan.front();
		plan.pop();
		int col = plan.front();
		plan.pop();
		walls += check(row, col, lab, visited, plan);
	}
	if (!visited[N][N]) {
		plan.push(N);
		plan.push(N);
		while (!plan.empty()) {
			int row = plan.front();
			plan.pop();
			int col = plan.front();
			plan.pop();
			walls += check(row, col, lab, visited, plan);
		}
	}
	walls -= 4;
	int meters = walls * 9;
	file.open("output.txt", std::ios_base::out | std::ios_base::trunc);
	file << meters << std::endl;
	return 0;
}