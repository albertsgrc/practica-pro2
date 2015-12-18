#include <iostream>
using namespace std;

int main() {
    cout << "Entra l'organisme inicial: " << endl;
    int x;
    cin >> x;
    cout << "Entra el nombre d'organismes a matar" << endl;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 10; ++j) cout << x << ' ';
        ++x;
        cout << endl;
    }
}
