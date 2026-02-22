#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc == 1) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    int n = argc - 1; 
    double sum = 0;

    for (int i = 1; i < argc; i++) {
        sum += stod(argv[i]); 
    }

    double average = sum / n;

    cout << "---------------------------------" << endl;
    cout << "Average of " << n << " numbers = " << average << endl;
    cout << "---------------------------------" << endl;

    return 0;
}
