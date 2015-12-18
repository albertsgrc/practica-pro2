#include "Ranking.hpp"
/** @file Ranking.cpp
    @brief Implementación de la clase Ranking de la Práctica de PRO2 <em>Reproducción en el Laboratorio</em>.
*/

/****** OPERACIONES PRIVADAS ******/

void Ranking::escribir_lista_org(const list<Parejahijo>&l) {
     // Escribimos la lista de parejas/hijos de un organismo dado
    for (list<Parejahijo>::const_iterator it = l.begin(); it != l.end(); ++it) {
        cout << ' ' << (*it).pareja + 1 << ' ' << (*it).hijo + 1;
    }
    cout << endl;
}

// Función de comparación para el orden de la lista exterior del ranking
bool Ranking::comp(int id1, int id2) {
    /************COST LINEAL************/
    int s1 = (*(organismos[id1].itp)).size();
    int s2 = (*(organismos[id2].itp)).size();
    if (s1 == s2) { // Si han creado el mismo número de hijos entonces ordenamos por id
        return id1 > id2;
    }
    return s1 < s2;
}

void Ranking::insertar_lranking(int id) {
    list<int>::iterator it = lranking.begin();
    while (it != lranking.end() and comp(id, *it)) ++it;
    organismos[id].itr = lranking.insert(it, id);
}

void Ranking::actualizar_lranking(int id) {
    lranking.erase(organismos[id].itr);
    insertar_lranking(id);
}

void Ranking::actualizar_org(int id1, int id2, int hijo) {
    if (not organismos[id1].hi_es) { // Si el organismo no existe en el ranking lo añadimos
        Parejahijo ph; // Creamos el struct de pareja/hijo
        ph.pareja = id2;
        ph.hijo = hijo;
        organismos[id1].hi_es = true; // Marcamos que está en el ranking en su correspondiente struct
        list<Parejahijo> l; // Creamos la lista de parejas/hijos del organismo con el nuevo emparejamiento
        l.insert(l.begin(), ph); // Insertamos el emparejamiento
        list< list<Parejahijo> >::iterator it = emparejamientos.end();
        organismos[id1].itp = emparejamientos.insert(it, l); // Insertamos la lista de emparejamientos a la lista de listas
        insertar_lranking(id1); // Insertamos el organismo en el ranking
    }
    else {
        Parejahijo ph; // Creamos el struct pareja/hijo
        ph.pareja = id2;
        ph.hijo = hijo;
        (*(organismos[id1].itp)).insert((*(organismos[id1].itp)).end(), ph); // Lo insertamos a la correspondiente lista de parejas/hijos del organismo
        actualizar_lranking(id1); // Actualizamos el orden del ranking
    }
}

/****** OPERACIONES PÚBLICAS ******/

// Constructoras

Ranking::Ranking(int pobmax) {
    organismos = vector<Referencia>(pobmax);
}

// Destructoras

Ranking::~Ranking() {}

// Consultoras

void Ranking::escribir_ranking(int pob) const {
     // Escribimos por orden los organismos que se han reproducido
    for (list<int>::const_iterator it = lranking.begin(); it != lranking.end(); ++it) {
        cout << *it + 1 << " :";
        escribir_lista_org(*(organismos[*it].itp)); // Escribimos la correspondiente lista de parejas/hijos
    }
    for (int j = 0; j < pob; ++j) { // Escribimos por orden creciente de id los organismos que no se han reproducido
        if (not organismos[j].hi_es) cout << j + 1 << " :" << endl; // Sólo lo escribimos si no se ha reproducido
    }
    cout << endl;
}

// Modificadoras

void Ranking::anadir_pareja(int id1, int id2, int hijo) {
    actualizar_org(id1, id2, hijo);
    actualizar_org(id2, id1, hijo);
}
