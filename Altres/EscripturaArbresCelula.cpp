#include <cmath>
#include <vector>

/***********INDICACIONS*************
*Canviar "***Organisme***" pel nom de la vostra classe organisme
*Canviar "***Celula***" pel nom de la vostra classe o estructura de dades que representa una cèlula (ej.: pair<int, bool> o simplement Celula)
*Canviar la resta de elements entre estrelles pel que s'indica en cada cas
************************************/

/***********DECLARACIONS HPP***************/
static void altura_arb(Arbre<***Celula***>&a, int&h);
static void conv_a_matriu(Arbre<***Celula***>&a, vector< vector<***Celula***> >&m, int h, vector<int> &ultimpos, int hmax);
static void escriu_elem(const ***Celula*** &elem);
static void escriure_arbre(const vector< vector<***Celula***> >&m);
static void escriure_arbre_gran(const vector< vector<***Celula***> >&m);
static void escriure_arbcelula_visual(const Arbre<***Celula***>&a);
static bool es_buida(const ***Celula***&c);
static bool es_activa(const ***Celula***&c);
static int id(const ***Celula***&c);
static ***Celula*** celvacia();
/******************************************/

void ***Organisme***::altura_arb(Arbre<***Celula***>&a, int&h) {
    if (a.es_buit()) h = 0;
    else if (not a.es_buit()) {
        int h2, h3;
        Arbre<***Celula***> a1, a2;
        ***Celula*** c = a.arrel();
        a.fills(a1, a2);
        altura_arb(a1, h2);
        altura_arb(a2, h3);
        h = max(h2, h3) + 1;
        a.plantar(c, a1, a2);
    }
}

void ***Organisme***::conv_a_matriu(Arbre<***Celula***>&a, vector< vector<***Celula***> >&m, int h, vector<int>&ultimpos, int hmax) {
    if (not a.es_buit()) {
        ***Celula*** c = a.arrel();
        m[h][ultimpos[h]] = c;
        ++ultimpos[h];
        Arbre<***Celula***> a1, a2;
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

bool ***Organisme***::es_buida(const ***Celula***&c) {
    return ***c.es_buida()***; // Canviar per la vostra funció o paràmetre (indica si l'id de la cèlula és 0)
}

bool ***Organisme***::es_activa(const ***Celula***&c) {
    return ***c.es_activa()***; // Canviar per la vostra funció o paràmetre (indica si la cèlula és activa)
}

int ***Organisme***::id(const ***Celula***&c) {
    return ***c.consul_id()***; // Canviar per la vostra funció o paràmetre (retorna l'identificador de la cèlula)
}

***Celula*** ***Organisme***::celvacia() { // Funció que retorna una cèlula buida (amb id = 0)
    return Celula(); // Canviar per la vostra funció o conjunt d'instruccions que retornin una cèlula amb identificador 0
    // Exemple amb struct:
    // Celula c;
    // c.id = 0;
    // c.activa = false;
    // return c;
}

void ***Organisme***::escriu_elem(const ***Celula***&elem) {
    if (not es_buida(elem)) {
        if (not es_activa(elem)) cout << '!';
        cout << id(elem);
    }
    else cout << ' ';
}

int ndigits(bool es_activa, int n) {
    if (n < 10 and es_activa) return 1;
    else if (n < 10) return 2;
    else return 1 + ndigits(es_activa, n/10);
}

void ***Organisme***::escriure_arbre(const vector< vector<***Celula***> >&m) {
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
            if (j%2 == 0 and not es_buida(m[i][j])) {
                sumadigits += ndigits(es_activa(m[i][j]), id(m[i][j])) - 1;
                if (j+1 < m[i].size()) {
                    sumadigits += ndigits(es_activa(m[i][j+1]), id(m[i][j+1])) - 1;
                }
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
            if (not es_buida(m[i + 1][j])) cout << '/';
            else cout << ' ';
            ++j;
            if (n - i == 2) espaientrebarres = 2;
            else if (n - i == 3) espaientrebarres = 4;
            espais(espaientrebarres - 1);
            if (not es_buida(m[i + 1][j])) cout << '\\';
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

void ***Organisme***::escriure_arbcelula_visual(const Arbre<***Celula***>&arb) { // Es passa const i es fa una còpia per tal que la gent que tingui la funció de la classe declarada com a const no tingui errors al compilar
    cout << endl << "----Arbre de celules----" << endl << endl;
    int h;
    Arbre<***Celula***> a = arb;
    altura_arb(a, h);
    vector< vector<***Celula***> > m(h + 1, vector<***Celula***>());
    int pot = 1;
    for (int i = 0; i <= h; ++i) {
        m[i] = vector<***Celula***>(pot, celvacia());
        pot *= 2;
    }
    vector<int> ultimpos(h + 1, 0);
    int haux = 0;
    conv_a_matriu(a, m, haux, ultimpos, h);
    escriure_arbre(m);
    cout << "------------------------" << endl;
}

