/** @file Celula.cpp
    @brief Implementació de la classe Celula de la Pràctica de PRO2
    <em>Reproducció al Laboratori</em>.
*/

#include "Celula.hpp"

/****** OPERACIONS PUBLIQUES******/

// Constructores

Celula::Celula() {
    id = ID_BUIDA;
    activa = false; // Definim que les celules buides son passives
}

Celula::Celula(int identificador, bool activitat) {
    id = identificador;
    activa = activitat;
}

Celula::Celula(const Celula&c) {
    id = c.id;
    activa = c.activa;
}

// Destructores

Celula::~Celula() {}

// Consultores

bool Celula::es_buida() const {
    return id == ID_BUIDA;
}

bool Celula::es_activa() const {
    return activa;
}

int Celula::consul_id() const {
    return id;
}

void Celula::escriure_celula() const {
    /* Escrivim l'identificador de la cel·lula i la informacio
       sobre la seva activitat/passivitat */
    cout << id << ' ';
    if (activa) cout << ACTIVA << ' ';
    else cout << PASSIVA << ' ';
}

// Modificadores

void Celula::llegir_celula() {
    /* Es tracta de llegir la informacio necessaria per definir la celula,
       en aquest cas l'identificador i la passivitat/activitat, tenint en
       compte que si la celula es buida no ens cal tenir informacio sobre
       la seva activitat, pero com que hem definit que les celules buides
       siguin passives, hem d'assignar la seva passivitat */
    id = readint();
    if (id != ID_BUIDA) activa = readbool();
    else activa = false;
}
