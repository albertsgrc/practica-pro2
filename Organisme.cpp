/** @file Organisme.cpp
    @brief Implementació de la classe Organisme de la Práctica de PRO2
           <em>Reproducció al Laboratori</em>.
*/

#include "Organisme.hpp"

/****** OPERACIONS PRIVADES ******/

void Organisme::llegir_acel(Acel&a, int&idmax) {
    Acel a1, a2;
    Celula c;
    c.llegir_celula();
    if (not c.es_buida()) {
        // Si no es una celula buida llegim els dos subarbres,
        // recalculem l'identificador maxim i plantem
        idmax = max(idmax, c.consul_id());
        llegir_acel(a1, idmax);
        llegir_acel(a2, idmax);
        a.plantar(c, a1, a2);
    }
}

void Organisme::escriure_acel(Acel&a) {
    if (not a.es_buit()) {
        Celula c = a.arrel();
        Acel a1, a2;
        a.fills(a1, a2);
        escriure_acel(a1);
        c.escriure_celula();
        escriure_acel(a2);
        // Replantem per tal que l'arbre quedi inalterat
        a.plantar(c, a1, a2);
    }
    else cout << 0 << ' ';
}

void Organisme::retallar_acel(Acel&a, int&idmax) {
    Celula c = a.arrel();
    Acel fe, fd;
    a.fills(fe, fd);
    /* Si algun dels dos subarbres es no buit aleshores no cal retallar
     * (la cel·lula ja s'ha fisionat) */
    if (not fe.es_buit() or not fd.es_buit()) {
        if (not fe.es_buit()) retallar_acel(fe, idmax);
        if (not fd.es_buit()) retallar_acel(fd, idmax);
        a.plantar(c, fe, fd);
        // Recalculem l'identificador maxim
        idmax = max(idmax, c.consul_id());
    }
    // Altrament es retalla simplement no replantant
}

void Organisme::estirar_acel(Acel&a, int&idmax) {
    Celula c = a.arrel();
    Acel fe, fd;
    a.fills(fe, fd);
    if (fe.es_buit() and fd.es_buit()) {
        ++idmax;
        Celula f1(idmax, c.es_activa());
        Acel fbuit1;
        fe.plantar(f1, fbuit1, fbuit1);
        ++idmax;
        Acel fbuit2;
        Celula f2(idmax, c.es_activa());
        fd.plantar(f2, fbuit2, fbuit2);
    }
    else {
        if (not fe.es_buit()) estirar_acel(fe, idmax);
        if (not fd.es_buit()) estirar_acel(fd, idmax);
    }
    a.plantar(c, fe, fd);
}

void Organisme::aux_clons_x1(Acel&x1, Acel&fill, int&tam, int&idmaxf) {
    ++tam;
    Celula c = x1.arrel();
    Acel fe, fd;
    x1.fills(fe, fd);

    Acel fef;
    if (not fe.es_buit()) aux_clons_x1(fe, fef, tam, idmaxf);
    Acel fdf;
    if (not fd.es_buit()) aux_clons_x1(fd, fdf, tam, idmaxf);
    /* Si s'ha plantat alguna celula en alguna branca inferior o la celula
       es activa plantem al fill */
    if (c.es_activa() or not fef.es_buit() or not fdf.es_buit()) {
        fill.plantar(c, fef, fdf);
        // Actualitzem l'id màxim del fill
        idmaxf = max(idmaxf, c.consul_id());
    }
    // Replantem per no destruir l'arbre de l'org que es reprodueix
    x1.plantar(c, fe, fd);
}

void Organisme::aux_clons_x2(Acel&x2, Acel&fill, int&tam,
                             int&idmaxf, int&idclonsx2) {
    ++tam;
    Celula c = x2.arrel();
    Acel fe, fd;
    x2.fills(fe, fd);
    int idcel = idclonsx2 + 1;
    /* Les celules dels subarbres tindran identificadors
     * a partir de l'identificador que es planta en aquesta crida */
    int idclonsx2prima = idcel;

    Acel fef;
    if (not fe.es_buit()) aux_clons_x2(fe, fef, tam, idmaxf, idclonsx2prima);
    Acel fdf;
    if (not fd.es_buit()) aux_clons_x2(fd, fdf, tam, idmaxf, idclonsx2prima);
    if (c.es_activa() or not fef.es_buit() or not fdf.es_buit()) {
        fill.plantar(Celula(idcel, c.es_activa()), fef, fdf);
        idmaxf = max(idmaxf, idcel);
        idclonsx2 = idclonsx2prima;
    }

    x2.plantar(c, fe, fd);
}

void Organisme::crear_fill(Acel&x1, Acel&x2, Acel&fill, int&idclonsx2,
                           int&idmaxf, int&tamint, int&stams) {
    Acel fe1, fd1, fe2, fd2;
    Celula c1(x1.arrel());
    Celula c2(x2.arrel());
    x1.fills(fe1, fd1);
    x2.fills(fe2, fd2);
    ++tamint;
    stams += 2;

    /* Si els dos subarbres son no buits aleshores seguim en la interseccio,
     * sino haurem de mirar per separat els subarbres que no siguin buits
     * en una funcio auxiliar que es dedica a col·locar els clons */

    // Subarbres esquerres
    Acel fef;
    if (not fe1.es_buit() and not fe2.es_buit()) {
        crear_fill(fe1, fe2, fef, idclonsx2, idmaxf, tamint, stams);
    }
    else if (not fe1.es_buit()) aux_clons_x1(fe1, fef, stams, idmaxf);
    else if (not fe2.es_buit()) aux_clons_x2(fe2, fef, stams, idmaxf, idclonsx2);
    // Subarbres drets
    Acel fdf;
    if (not fd1.es_buit() and not fd2.es_buit()) {
        crear_fill(fd1, fd2, fdf, idclonsx2, idmaxf, tamint, stams);
    }
    else if (not fd1.es_buit()) aux_clons_x1(fd1, fdf, stams, idmaxf);
    else if (not fd2.es_buit()) aux_clons_x2(fd2, fdf, stams, idmaxf, idclonsx2);

    fill.plantar(Celula(c1.consul_id(), c1.es_activa() or c2.es_activa()), fef, fdf);
    idmaxf = max(idmaxf, c1.consul_id());
    x1.plantar(c1, fe1, fd1);
    x2.plantar(c2, fe2, fd2);
}

/****** OPERACIONS PUBLIQUES ******/

// Constructores

Organisme::Organisme() {
    retallat = false;
    idmax = 0;
}

void Organisme::reproduir_parella(Organisme&escollit, Organisme&fill,
                                                      bool&compatibles) {
    int auxidmax = idmax;
    int stams = 0;
    int tamint = 0;
    crear_fill(morfologia, escollit.morfologia, fill.morfologia,
               auxidmax, fill.idmax, tamint, stams);
    compatibles = tamint >= (stams)/4;
    if (not compatibles) {
        // Si no son compatibles destruim el fill
        fill.morfologia.a_buit();
        fill.idmax = 0;
    }
}

// Destructores

Organisme::~Organisme() {}

// Consultores

bool Organisme::es_mort() const {
    return morfologia.es_buit();
}

void Organisme::escriure_organisme() {
    escriure_acel(morfologia);
    cout << endl;
}

bool Organisme::esta_retallat() const {
    return retallat;
}

// Modificadores

void Organisme::aplicar_retallada() {
    retallat = true;
    // Variable auxiliar en la que obtindrem el nou id max. despres de retallar
    int auxidmax = 0;
    retallar_acel(morfologia, auxidmax);
    idmax = auxidmax; // Actualitzem idmax
}

void Organisme::aplicar_estirament() {
    estirar_acel(morfologia, idmax);
}

void Organisme::llegir_organisme() {
    llegir_acel(morfologia, idmax);
}
