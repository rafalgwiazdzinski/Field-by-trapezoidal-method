#include <iostream>
#include <fstream>
#include <list>
#include <ctime>
#define N 5 // number of points
#define RANGE 100 // range for positive numbers

// Project assumptions: points x and y are positive integers

using namespace std;

typedef pair <int, int>           point_t;
typedef list <point_t>            list_of_points_t;

list_of_points_t list_of_points;
list_of_points_t list_of_points_from_file;

void print_list(list<point_t> l);
double field_calculation_by_trapezoidal_method(list<point_t> l);

int main() {
    srand( time( NULL ) );
    rand();
    for(int i = 0; i<N; i++) {
        int x = RANGE * rand() / RAND_MAX;
        int y = RANGE * rand() / RAND_MAX;
        point_t point = make_pair(x, y);
        list_of_points.push_back(point);
    }
    list_of_points.sort();
    ///////////// save to file ///////////////////
    ofstream output;
    output.open("output.txt");
    for(auto itr=list_of_points.begin();itr != list_of_points.end();++itr)
    {
        output<<itr->first << " " << itr->second << endl;
    }
    output.close();
    cout << "Zapisano posortowane punkty do pliku" << endl;
    ////////////////////////////////////////////////
    //////////// read from file ////////////////////
    ifstream myfile ("output.txt");
    if (myfile.is_open()) {
        point_t point;
        while ( myfile >> point.first >> point.second )
        {
            list_of_points_from_file.push_back(point);
        }
        myfile.close();
        cout << "Odczytano punkty z pliku" << endl;
        print_list(list_of_points_from_file);
    } else cout << "Nie mozna otworzyc pliku";
    ////////////////////////////////////////////////
    double field = field_calculation_by_trapezoidal_method(list_of_points_from_file);
    cout << "Pole pod wykresem: " << field << std::endl;
    return 0;
}

void print_list(list<point_t> l) {
    for(auto iter = l.begin(); iter != l.end(); iter++) {
        cout << (*iter).first << "  " << (*iter).second << endl;
    }
}

double field_calculation_by_trapezoidal_method(list<point_t> l) {
    double sum_fields = 0;
    int x1, x2, y1, y2;
    for(auto itr = l.begin(); itr != l.end(); itr++) {
        x1 = itr->first;
        y1 = itr->second;
        //cout << "x1, y1: " << x1 << ", " << y1 << endl;
        auto itr2 = next(itr);
        if(itr2 == l.end()) {
            return sum_fields;
        }
        x2 = itr2->first;
        y2 = itr2->second;
        //cout << "x2, y2: " << x2 << ", " << y2 << endl;
        int h = x2 - x1;
        double field = (y1 + y2) * h / 2.0;
        //cout << "Wysokosc: " << field << endl;
        sum_fields = sum_fields + field;
    }
    return sum_fields;
}

