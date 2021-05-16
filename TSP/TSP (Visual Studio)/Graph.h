#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Edge {
	int from;
	int to;
};

class Graph
{
	vector<vector<int>> Matrix;
	vector<Edge> result;
	vector<vector<int>> matrix_copy;
	string track;
	int lenght;
	void reduct_line();
	void reduct_col();
	int findMinCol(int, int);
	int findMinLine(int, int);
	Edge FindEdge();
	void reduct();
public:
	Graph(int);
	~Graph(){};
	void print_matrix();
	void make_track();
	string get_track();
	int get_TrackLenght();
	void change_edge();
	void make_files();
};

