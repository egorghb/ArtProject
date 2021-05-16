#include "Graph.h"

Graph::Graph(int n) {
	track = "";
	lenght = 0;
	for (int i = 0; i < n; i++) {
		vector<int> tmp;
		for (int j = 0; j < n; j++) {
			if (i == j) {
				tmp.push_back(-1);
			}
			else {
				int a;
				cout << "From " << i + 1 << " to " << j + 1 << " : ";
				cin >> a;
				tmp.push_back(a);
			}
		}
		Matrix.push_back(tmp);
	}
	matrix_copy = Matrix;
}

void Graph::print_matrix() {
	if (Matrix.size() == 0)
		cout << "Matrix is empty" << endl;
	else {
		cout << "\nМатрица смежности:\n";
		for (int i = 1; i <= Matrix.size(); i++) {
			cout << "\t" << "(" << i << ")";
		}
		cout << endl;
		for (int i = 0; i < Matrix.size(); i++) {
			cout << "(" << i + 1 << ")" << "\t";
			for (int j = 0; j < Matrix.size(); j++) {
				cout << Matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
}

void Graph::reduct_line() {
	for (int i = 0; i < matrix_copy.size(); i++) {
		int min = INT_MAX;
		for (int j = 0; j < matrix_copy[0].size(); j++) {
			if (min > matrix_copy[i][j] && matrix_copy[i][j] >= 0) {
				min = matrix_copy[i][j];
			}
		}
		if (min != INT_MAX) {
			for (int j = 0; j < matrix_copy[0].size(); j++) {
				if (matrix_copy[i][j] >= 0)
					matrix_copy[i][j] -= min;
			}
		}
	}
}

void Graph::reduct_col() {
	for (int i = 0; i < matrix_copy.size(); i++) {
		int min = INT_MAX;
		for (int j = 0; j < matrix_copy[0].size(); j++) {
			if (min > matrix_copy[j][i] && matrix_copy[j][i] >= 0) {
				min = matrix_copy[j][i];
			}
		}
		if (min != INT_MAX) {
			for (int j = 0; j < matrix_copy[0].size(); j++) {
				if (matrix_copy[j][i] >= 0)
					matrix_copy[j][i] -= min;
			}
		}
	}
}

void Graph::reduct() {
	reduct_line();
	reduct_col();
}

int Graph::findMinCol(int i, int j) {
	int min = INT_MAX;
	for (int l = 0; l < matrix_copy[0].size(); l++) {
		if (l != i && matrix_copy[l][j] != -1 && min > matrix_copy[l][j]) {
			min = matrix_copy[l][j];
		}
	}
	return min;
}

int Graph::findMinLine(int i, int j) {
	int min = INT_MAX;
	for (int c = 0; c < matrix_copy[0].size(); c++) {
		if (c != j  && matrix_copy[i][c] != -1 && min > matrix_copy[i][c]) {
			min = matrix_copy[i][c];
		}
	}
	return min;
}

Edge Graph::FindEdge() {
	int max = -1;
	Edge edge{ 0, 0 };
	for (int i = 0; i < matrix_copy[0].size(); i++) {
		for (int j = 0; j < matrix_copy[0].size(); j++) {
			if (matrix_copy[i][j] == 0) {
				int min_sum = findMinCol(i, j) + findMinLine(i, j);
				if (min_sum > max) {
					max = min_sum;
					edge.from = i;
					edge.to = j;
				}
			}
		}
	}
	matrix_copy[edge.to][edge.from] = -1;
	for (int i = 0; i < matrix_copy[0].size(); i++) {
		matrix_copy[edge.from][i] = -1;
		matrix_copy[i][edge.to] = -1;
	}
	return edge;
}

void Graph::make_track() {
	int n = matrix_copy.size();
	for (int i = 0; i < n - 2; i++) {
		reduct();
		result.push_back(FindEdge());
	}
	bool f = 0;
	int lenght = INT_MAX;
	Edge edge;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix_copy[i][j] != -1 && matrix_copy[i][j] < lenght) {
				lenght = matrix_copy[i][j];
				edge.from = i;
				edge.to = j;
				f = 1;
			}
		}
		if(f) result.push_back(edge);
		lenght = INT_MAX;
		f = 0;
	}
}

string Graph::get_track() {
	Edge current = result[0];
	track += to_string(current.from + 1) + "->" + to_string(current.to + 1);
	int count = 0;
	while (count < result.size()) {
		for (int i = 0; i < result.size(); i++) {
			Edge next = result[i];
			if (current.to == next.from) {
				count++;
				track += "->" + to_string(next.to + 1);
				current = next;
				break;
			}
		}
	}
	track = track.substr(0, track.size() - 3);
	return track;
}

int Graph::get_TrackLenght() {
	Edge current = result[0];
	lenght += Matrix[current.from][current.to];
	int count = 0;
	while (count < result.size()) {
		for (int i = 0; i < result.size(); i++) {
			Edge next = result[i];
			if (current.to == next.from) {
				count++;
				lenght += Matrix[current.from][current.to];
				current = next;
				break;
			}
		}
	}
	lenght -= Matrix[current.from][current.to];
	return lenght;
}

void Graph::change_edge() {
	int i, j, len;
	cout << "Add, delete or change edge:\n";
	cout << "From: "; cin >> i;
	cout << "To: "; cin >> j;
	cout << "Lenght: "; cin >> len;
	Matrix[i - 1][j - 1] = len;
	matrix_copy = Matrix;
}

void Graph::make_files() {
	fstream stream("Matrix.txt", ios::out | ios::trunc);
	if (!stream) return;
	for (int i = 0; i < Matrix.size(); i++) {
		for (int j = 0; j < Matrix.size(); j++) {
			stream << Matrix[i][j] << " ";
		}
		stream << endl;
	}
	stream.close();
	fstream stream2("Track.txt", ios::out | ios::trunc);
	if (!stream2) return;
	stream2 << track << endl << lenght << endl << Matrix[0].size();
	stream2.close();
}