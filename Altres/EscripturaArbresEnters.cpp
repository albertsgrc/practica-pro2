#include <cmath>
#include <vector>
#include "utils.PRO2"
#include "Arbre.hpp"

const int MARCA = 0;

void altura_arb(Arbre<int>&a, int&h) {
    if (a.es_buit()) h = 0;
    else if (not a.es_buit()) {
        int h2, h3;
        Arbre<int> a1, a2;
        int c = a.arrel();
        a.fills(a1, a2);
        altura_arb(a1, h2);
        altura_arb(a2, h3);
        h = max(h2, h3) + 1;
        a.plantar(c, a1, a2);
    }
}

void conv_a_matriu(Arbre<int>&a, vector< vector<int> >&m, int h, vector<int>&ultimpos, int hmax) {
    if (not a.es_buit()) {
        int c = a.arrel();
        m[h][ultimpos[h]] = c;
        ++ultimpos[h];
        Arbre<int> a1, a2;
        a.fills(a1, a2);
        conv_a_matriu(a1, m, h+1, ultimpos, hmax);
        conv_a_matriu(a2, m, h+1, ultimpos, hmax);
        a.plantar(c, a1, a2);
    }
    else {
        ++ultimpos[h];
        ++h;
        int espais = 2;
        while (h < hmax) {
            ultimpos[h] += espais;
            espais *= 2;
            ++h;
        }
    }
}

void espais(int n) {
    for (int i = 0; i < n; ++i) cout << ' ';
}

void escriu_elem(int elem) {
    if (elem != MARCA) cout << elem;
    else cout << ' ';
}

int ndigits(int n) {
    if (n < 10) return 1;
    else return 1 + ndigits(n/10);
}

void escriure_arbre(const vector< vector<int> >&m) {
    int n = m.size() - 1;
    int espaientreelements = 3*pow(2, n - 1);
    int espaiinicial = espaientreelements/2;
    int espaientrebarres = espaiinicial/2;
    int espaientrebranques =  3*espaientrebarres;
    int strideespaiinicial = espaientrebarres/2;
    for (int i = 0; i < n; ++i) {
        if (n - i == 3) espaiinicial = 6;
        else if (n - i == 2) espaiinicial = 3;
        else if (n - i == 1) espaiinicial = 1;
        espais(espaiinicial - 1);
        espaiinicial -= strideespaiinicial;
        for (int j = 0; j < m[i].size(); ++j) {
            escriu_elem(m[i][j]);
            int sumadigits = 0;
            if (j%2 == 0) sumadigits += ndigits(m[i][j]) - 1;
            if (j+1 < m[i].size()) {
                sumadigits += ndigits(m[i][j+1]) - 1;
            }
            if (n - i == 1) {
                if (j%2 == 0) espaientreelements = 4;
                else espaientreelements = 2;
            }
            espais(espaientreelements - 1 - sumadigits);
        }
        cout << endl;
        if (n - i == 3) espaiinicial = 4;
        else if (n - i == 2) espaiinicial = 2;
        espais(espaiinicial - 1);
        espaiinicial -= strideespaiinicial;
        int j = 0;
        for (int k = 0; k < m[i].size(); ++k) {
            if (m[i + 1][j] != MARCA) cout << '/';
            else cout << ' ';
            ++j;
            if (n - i == 2) espaientrebarres = 2;
            else if (n - i == 3) espaientrebarres = 4;
            espais(espaientrebarres - 1);
            if (m[i + 1][j] != MARCA) cout << '\\';
            else cout << ' ';
            ++j;
            if (n - i == 3) espaientrebranques = 8;
            else if (n - i == 2) espaientrebranques = 4;
            espais(espaientrebranques - 1);
        }
        cout << endl;
        strideespaiinicial /= 2;
        espaientrebarres /= 2;
        espaientrebranques /= 2;
        espaientreelements /= 2;
    }
}

void llegir_arbre_int(Arbre<int>& a, int marca) {
  Arbre<int> a1, a2;
  int x;
  cin >> x;
  if (x!= marca) {
    llegir_arbre_int(a1, marca);
    llegir_arbre_int(a2, marca);
    a.plantar(x,a1,a2);
  }
}

int main() {
    Arbre<int> a;
    cout << "Entra l'arbre d'enters:" << endl;
    llegir_arbre_int(a, MARCA);
    cout << endl << "----Arbre d'enters----" << endl << endl;
    int h;
    altura_arb(a, h);
    vector< vector<int> > m(h + 1, vector<int>());
    int pot = 1;
    for (int i = 0; i <= h; ++i) {
        m[i] = vector<int>(pot, MARCA);
        pot *= 2;
    }
    vector<int> ultimpos(h + 1, 0);
    int haux = 0;
    conv_a_matriu(a, m, haux, ultimpos, h);
    escriure_arbre(m);
    cout << "------------------------" << endl;
}

