#include "Ranking.hpp"
/** @file Ranking.cpp
    @brief Implementació de la classe Ranking de la Pràctica de PRO2
           <em>Reproducció al Laboratori</em>.
*/

/****** OPERACIONS PRIVADES ******/

void Ranking::escriure_llista_org(const Lrep&l) {
    /* Escrivim la llista de parelles/fills d'un organisme donat, que
      sabem que s'escriura per l'ordre que demana l'enunciat ja que
       els fills es van afegint a les llistes a mesura que es van creant,
       i prenen identificadors de petit a gran */
    for (Lrep::const_iterator it = l.begin(); it != l.end(); ++it) {
        cout << ' ' << (*it).parella + 1 << ' ' << (*it).fill + 1;
    }
    cout << endl;
}

bool Ranking::comp(int id1, int id2) {
    // Mirem el nombre de fills que han creat els organismes
    int s1 = org[id1].empar.size();
    int s2 = org[id2].empar.size();
    if (s1 == s2) return id1 > id2;
    else return s1 < s2;
}

void Ranking::insertar_org(int id, Lint::iterator it) {
    // Movem l'iterador fins la posicio d'insercio
    while (it != ordre.end() and comp(*it, id)) ++it;
    // Insertem i guardem l'iterador de la posicio on hem insertat
    org[id].itr = ordre.insert(it, id);
}

void Ranking::actualitzar_org(int id1, int id2, int fill) {
    Reproduccio r;
    r.parella = id2;
    r.fill = fill;
    // L'insertem a la corresponent llista de parelles/fills de l'organisme
    org[id1].empar.insert(org[id1].empar.end(), r);
    /* Si el tamany de la seva llista de emparellaments es 1
       (es la seva primera reproduccio) comencem a insertar-lo
       des del begin de la llista (sabem que sera una insercio rapida ja que
       la llista esta ordenada de menys a mes fills creats) */
    if (org[id1].empar.size() == 1) insertar_org(id1, ordre.begin());
    /* Sino vol dir que ja existeix, per tant el borrem d'on estigui
       i comencem a insertar desde la posicio on l'hem borrat per tal
       que la insercio sigui mes eficient */
    else insertar_org(id1, ordre.erase(org[id1].itr));
}

/****** OPERACIONS PUBLIQUES ******/

// Constructores

Ranking::Ranking(int pobmax) {
    org = vector<Dades>(pobmax);
}

// Destructores

Ranking::~Ranking() {}

// Consultores

void Ranking::escriure_ranking(int pob) const {
    /* Es tracta d'escriure primer els organismes que s'han reproduit
       en l'ordre indicat a l'enunciat (en aquest cas començant per l'end()
       i acabant al begin() ja que la llista esta ordenada del reves
       i despres els organismes que no s'han reproduit encara, de menor a major
       identificador */
    Lint::const_iterator it = ordre.end();
    while (it != ordre.begin()) {
        --it;
        cout << *it + 1 << " :";
        escriure_llista_org(org[*it].empar);
    }
    for (int j = 0; j < pob; ++j) {
        /* El tamany de la seva llista d'emparellaments ens indica si
           s'ha reproduit */
        if (org[j].empar.size() == 0) cout << j + 1 << " :" << endl;
    }
    cout << endl;
}

// Modificadores

void Ranking::afegir_parella(int id1, int id2, int fill) {
    /* Es tracta d'actualitzar el ranking i les llistes d'emparellaments
       dels dos organismes implicats en la reproduccio */
    actualitzar_org(id1, id2, fill);
    actualitzar_org(id2, id1, fill);
}
