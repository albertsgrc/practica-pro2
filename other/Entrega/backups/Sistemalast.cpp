/** @file Sistema.cpp
    @brief Implementació de la classe Sistema de la Pràctica de PRO2
           <em>Reproducció al Laboratori</em>.
*/

#include "Sistema.hpp"
#include <vector>

/****** OPERACIONS PRIVADES******/

void Sistema::emparellar_organismes(Vbool&agafat, Ranking&rank, int i, int j) {
    /* Marquem que els organismes s'han emparellat en el vector de booleans
       de la ronda i la matriu d'emparellaments */
    agafat[i] = agafat[j] = emparellats[i][j - i - 1] = true;
    bool compatibles;
    vorg[i].reproduir_parella(vorg[j], vorg[pob], compatibles);
    if (compatibles) { // Compatibles ens indica si s'ha creat el fill
        rank.afegir_parella(i, j, pob); // 'pob+1' és l'identificador del fill
        ++pob;
        ++nfills_ur;
    }
}

/****** OPERACIONS PÚBLIQUES ******/

// Constructores

Sistema::Sistema(int pobmax) {
    vorg = vector<Organisme>(pobmax);
    emparellats = Mbool(pobmax - 2); /* És -2 pel segon corol·lari argumentat
                                        en la descripció de la classe */
    /* Construïm la matriu triangular superior, que pot tenir aquesta
       estructura donat el que s'ha demostrat en la descripció de la classe
       (no ens cal emmagatzemar l'informació sobre si un organisme s'ha
       emparellat amb un d'id menor o igual al seu ja que sabem del cert que
       mai s'hi podrà emparellar */
    for (int i = 0; i < pobmax - 2; ++i) {
        emparellats[i] = Vbool(pobmax - i - 1, false);
    }
    ini_emp = vector<int>(pobmax - 2); // Novament, és -2 per la mateixa raó
    for (int i = 0; i < pobmax - 2; ++i) ini_emp[i] = i + 1;
    pob = nmorts = nfills_ur = 0;
}

// Destructores

Sistema::~Sistema() {}

// Consultores

int Sistema::consul_pob() const {
    return pob;
}

bool Sistema::es_viu_org(int id) const {
    /* Per la post de la creadora d'Organisme sabem que qualsevol organisme
       no existent al paràmetre implícit és mort, per tant només ens cal
       comprovar si no està mort, ja que si això és cert podem estar segurs
       que existeix */
    return not vorg[id - 1].es_mort();
}

bool Sistema::es_estirable_org(int id) const {
    return id >= 1 and id <= pob and not vorg[id - 1].esta_retallat();
}

bool Sistema::esta_ple() const {
    return pob == vorg.size();
}

bool Sistema::existeix_org(int id) const {
    return id >= 1 and id <= pob;
}

int Sistema::consul_nvius() const {
    return pob - nmorts;
}

int Sistema::consul_fills_repr() const {
    return nfills_ur;
}

void Sistema::escriure_org(int id) {
    cout << id << " :";
    vorg[id - 1].escriure_organisme();
}

// Modificadores

void Sistema::llegir_pob_ini(int pobini) {
    for (int i = 0; i < pobini; ++i) vorg[i].llegir_organisme();
    pob = pobini;
}

void Sistema::retallar_org(int id) {
    vorg[id - 1].aplicar_retallada();
    /* Comprovem si ha mort per la retallada i en cas afirmatiu incrementem
       el nº de morts */
    if (vorg[id - 1].es_mort()) ++nmorts;
}

void Sistema::estirar_org(int id) {
    vorg[id - 1].aplicar_estirament();
}

void Sistema::aplicar_ronda_reproduccio(Ranking&rank) {
    int pobaux = pob;
    /* Utilitzem un vector de booleans auxiliar per la ronda que ens dirà
       si dos organismes ja s'han emparellat en la ronda */
    Vbool agafat(pobaux, false);
    int i = 0;
    nfills_ur = 0;
    /* La condició és i < pobaux -1 pel corol·lari 1 argumentat en
     * la descripció de la classe.
     * També hem de comprovar que no s'hagi arribat a la població màxima
     * en cada iteració */
    while (i < pobaux - 1 and pob < vorg.size()) {
        /* El tractem únicament si no s'ha emparellat encara en la ronda
           i no està mort */
        if (not agafat[i] and not vorg[i].es_mort()) {
            /* Avancem l'organisme inicial d'emparellament mentre aquest
             * sigui mort o ja s'hi hagi emparellat */
            while (ini_emp[i] < pobaux and
                   (vorg[ini_emp[i]].es_mort()
                    or emparellats[i][ini_emp[i] - i - 1])) ++ini_emp[i];
            /* Per la condició de sortida del while sabem que o bé
             * no té cap organisme disponible per emparellar-se o bé
             * es pot emparellar amb ini_emp[i] si està disponible
             * per aquella ronda */
            if (ini_emp[i] < pobaux) {
                // Si està disponible emparellem
                if (not agafat[ini_emp[i]]) {
                    emparellar_organismes(agafat, rank, i, ini_emp[i]);
                }
                else { // Sinó seguim buscant
                    int j = ini_emp[i] + 1;
                    while (j < pobaux and
                           (emparellats[i][j - i - 1]
                            or agafat[j] or vorg[j].es_mort())) ++j;
                    /* Per la condició de sortida del while si j < pobaux
                     * vol dir que s'hi pot emparellar */
                    if (j < pobaux) emparellar_organismes(agafat, rank, i, j);
                }
            }
        }
        ++i;
    }
}
