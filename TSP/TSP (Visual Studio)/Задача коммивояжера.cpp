#include "Graph.h"
using namespace std;


int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите количество узлов: "; cin >> n;
    Graph graph(n);
    graph.print_matrix();
    graph.make_track();
    cout << "\nTrack: " << graph.get_track();
    cout << "\nTrack lenght: " << graph.get_TrackLenght() << endl;
    graph.make_files();
    system("pause");
    return 0;
}
