/** @file Organisme.cpp
    @brief Implementació de la classe Organisme de la Práctica de PRO2
           <em>Reproducció al Laboratori</em>.
*/

#include "Organisme.hpp"

/****** OPERACIONS PRIVADES ******/

void Organisme::llegir_arbcelula(Arbcel&a, int&idmax, int &tam) {
    Arbcel a1, a2;
    Celula c;
    c.llegir_celula();
    if (not c.es_buida()) {
        // Si no és una cèl·lula buida llegim els dos subarbres,
        // recalculem l'identificador màxim i plantem
        idmax = max(idmax, c.consul_id());
        llegir_arbcelula(a1, idmax, tam);
        llegir_arbcelula(a2, idmax, tam);
        a.plantar(c, a1, a2);
        ++tam;
    }
}

void Organisme::escriure_arbcelula(Arbcel&a) {
    if (not a.es_buit()) {
        Celula c = a.arrel();
        Arbcel a1, a2;
        a.fills(a1, a2);
        escriure_arbcelula(a1);
        cout << ' ';
        c.escriure_celula();
        escriure_arbcelula(a2);
        // Replantem per tal que l'arbre quedi inalterat
        a.plantar(c, a1, a2);
    }
    else cout << ' ' << 0;
}

void Organisme::retallar_arbcelula(Arbcel&a, int&idmax, int &tam) {
    Celula c = a.arrel();
    Arbcel fe, fd;
    a.fills(fe, fd);
    /* Si algun dels dos subarbres és no buit aleshores no cal retallar
     * (la cèl·lula ja s'ha fisionat) */
    if (not fe.es_buit() or not fd.es_buit()) {
        if (not fe.es_buit()) retallar_arbcelula(fe, idmax, tam);
        if (not fd.es_buit()) retallar_arbcelula(fd, idmax, tam);
        a.plantar(c, fe, fd);
        // Recalculem l'identificador màxim
        idmax = max(idmax, c.consul_id());
    }
    else --tam;
    // Altrament es retalla simplement no replantant
}

void Organisme::estirar_arbcelula(Arbcel&a, int&idmax, int&tam) {
    Celula c = a.arrel();
    Arbcel fe, fd;
    a.fills(fe, fd);
    /* Si les dues branques són buides aleshores fissionem
       (estem a una fulla) */
    if (fe.es_buit() and fd.es_buit()) {
        // Creem la cèl·lula del subarbre esquerre
        ++idmax;// Actualitzem l'id màxim
        Celula f1(idmax, c.es_activa());
        Arbcel fbuit;
        fe.plantar(f1, fbuit, fbuit);
        // Creem la cèl·lula del subarbre dret
        ++idmax;
        Celula f2(idmax, c.es_activa());
        fd.plantar(f2, fbuit, fbuit);
        tam += 2;
    }
    else { // Si un dels 2 subarbres és no buit no s'ha de fissionar
        if (not fe.es_buit()) estirar_arbcelula(fe, idmax, tam);
        if (not fd.es_buit()) estirar_arbcelula(fd, idmax, tam);
    }
    a.plantar(c, fe, fd);
}

void Organisme::aux_clons_x1(Arbcel&x1, Arbcel&fill, int&tamf, int&idmaxf) {
    Celula c = x1.arrel();
    Arbcel fe, fd;
    x1.fills(fe, fd);

    Arbcel fef;
    if (not fe.es_buit()) aux_clons_x1(fe, fef, tamf, idmaxf);
    Arbcel fdf;
    if (not fd.es_buit()) aux_clons_x1(fd, fdf, tamf, idmaxf);
    /* Si s'ha plantat alguna cèl·lula en alguna rama inferior o la cèl·lula
       és activa plantem al fill */
    if (c.es_activa() or not fe.es_buit() or not fd.es_buit()) {
        fill.plantar(c, fef, fdf);
        // Actualitzem l'id màxim del fill
        idmaxf = max(idmaxf, c.consul_id());
        ++tamf;
    }
    // Replantem per no destruir l'arbre de l'org que es reprodueix
    x1.plantar(c, fe, fd);
}

void Organisme::aux_clons_x2(Arbcel&x2, Arbcel&fill, int&tamf,
                             int&idmaxf, int&idclonsx2) {
    Celula c = x2.arrel();
    Arbcel fe, fd;
    x2.fills(fe, fd);
    int idcel = idclonsx2 + 1;
    /* Els subarbres plantaràn a partir de l'identificador que es planta
       en aquesta crida */
    int idclonsx2prima = idcel;

    Arbcel fef;
    if (not fe.es_buit()) aux_clons_x2(fe, fef, tamf, idmaxf, idclonsx2prima);
    Arbcel fdf;
    if (not fd.es_buit()) aux_clons_x2(fd, fdf, tamf, idmaxf, idclonsx2prima);
    if (c.es_activa() or not fe.es_buit() or not fd.es_buit()) {
        fill.plantar(Celula(idcel, c.es_activa()), fef, fdf);
        idmaxf = max(idmaxf, idcel);
        idclonsx2 = idclonsx2prima;
        ++tamf;
    }

    x2.plantar(c, fe, fd);
}

void Organisme::crear_fill(Arbcel&x1, Arbcel&x2, Arbcel&fill, int&idclonsx2,
                           int&idmaxf, int&tamint, int&tamf) {
    Arbcel fe1, fd1, fe2, fd2;
    Celula c1(x1.arrel());
    Celula c2(x2.arrel());
    x1.fills(fe1, fd1);
    x2.fills(fe2, fd2);
    ++tamint;
    ++tamf;

    /* Si els dos subarbres són no buits aleshores seguim en la intersecció,
     * sinó haurem de mirar per separat els subarbres que no siguin buits
     * en una funció auxiliar que es dedica a col·locar els clons */

    // Subarbres esquerres
    Arbcel fef;
    if (not fe1.es_buit() and not fe2.es_buit()) {
        crear_fill(fe1, fe2, fef, idclonsx2, idmaxf, tamint, tamf);
    }
    else if (not fe1.es_buit()) aux_clons_x1(fe1, fef, tamf, idmaxf);
    else if (not fe2.es_buit()) {
        aux_clons_x2(fe2, fef, tamf, idmaxf, idclonsx2);
    }
    // Subarbres drets
    Arbcel fdf;
    if (not fd1.es_buit() and not fd2.es_buit()) {
        crear_fill(fd1, fd2, fdf, idclonsx2, idmaxf, tamint, tamf);
    }
    else if (not fd1.es_buit()) aux_clons_x1(fd1, fdf, tamf, idmaxf);
    else if (not fd2.es_buit()) {
        aux_clons_x2(fd2, fdf, tamf, idmaxf, idclonsx2);
    }

    fill.plantar(Celula(c1.consul_id(), c1.es_activa() or c2.es_activa()),
                 fef, fdf);
    idmaxf = max(idmaxf, c1.consul_id());
    x1.plantar(c1, fe1, fd1);
    x2.plantar(c2, fe2, fd2);
}

/****** OPERACIONS PÚBLIQUES ******/

// Constructores

Organisme::Organisme() {
    retallat = false;
    idmax = tam = 0;
}

void Organisme::reproduir_parella(Organisme&escollit,  Organisme&fill,
                                  bool&compatibles) {
    int auxidmax = idmax;
    int tamint = 0;
    crear_fill(morfologia, escollit.morfologia, fill.morfologia,
               auxidmax, fill.idmax, tamint, fill.tam);
    compatibles = tamint >= (tam + escollit.tam)/4;
    if (not compatibles) {
        // Si no són compatibles destruim el fill
        fill.morfologia.a_buit();
        fill.idmax = fill.tam = 0;
    }
}

// Destructores

Organisme::~Organisme() {}

// Consultores

int Organisme::consul_tam() const {
    return tam;
}

bool Organisme::es_mort() const {
    return morfologia.es_buit();
}

void Organisme::escriure_organisme() {
    escriure_arbcelula(morfologia);
    cout << endl;
}

bool Organisme::esta_retallat() const {
    return retallat;
}

// Modificadores

void Organisme::aplicar_retallada() {
    retallat = true;
    // Variable auxiliar en la que obtindrem el nou id màx. després de retallar
    int auxidmax = 0;
    retallar_arbcelula(morfologia, auxidmax, tam);
    idmax = auxidmax; // Actualitzem idmax
}

void Organisme::aplicar_estirament() {
    estirar_arbcelula(morfologia, idmax, tam);
}

void Organisme::llegir_organisme() {
    llegir_arbcelula(morfologia, idmax, tam);
}
