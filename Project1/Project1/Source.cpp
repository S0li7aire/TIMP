#include <iostream>
#include <queue>
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
	cin >> N;
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
				cin >> lab[i][j];
			}
		}
	}
	queue <int> plan;
	plan.push(1);
	plan.push(1);
	int walls = 0;
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
	cout << meters << endl;
	return 0;
}