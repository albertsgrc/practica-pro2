/** @file Sistema.cpp
    @brief Implementació de la classe Sistema de la Pràctica de PRO2
           <em>Reproducció al Laboratori</em>.
*/

#include "Sistema.hpp"

/****** OPERACIONS PRIVADES******/

void Sistema::emparellar_organismes(Vbool&ocupat, Ranking&rank, int i, int j,
                                    Lemp::iterator it) {
    /* Marquem que els organismes s'han emparellat en el vector de booleans
       de la ronda i la matriu d'emparellaments */
    ocupat[i] = ocupat[j] = (*it).e[j - i - 1] = true;
    bool compatibles;
    vorg[i].reproduir_parella(vorg[j], vorg[pob], compatibles);
    if (compatibles) { // Compatibles ens indica si s'ha creat el fill
        // Creem l'informacio d'emparellaments de l'ultim organisme
        // que s'havia creat (que encara no en tenia perque no la necessitava,
        // pero ara que n'ha nascut un amb identificador mes gran que ell si
        // que la necessita
        InfoEmparellaments ie;
        // ie.e sempre tindra tamany major que 0 ja que
        // pob < vorg.size() (sinó hauria acabat l'experiment)
        ie.e = Vbool(vorg.size() - pob, false);
        ie.ini = pob;
        empar.insert(empar.end(), ie);
        rank.afegir_parella(i, j, pob); // 'pob+1' és l'identificador del fill
        ++pob;
        ++nfills_ur;
    }
}

/****** OPERACIONS PUBLIQUES ******/

// Constructores

Sistema::Sistema(int pobmax) {
    vorg = vector<Organisme>(pobmax);
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
       no existent al parametre implícit es mort, per tant nomes ens cal
       comprovar si no esta mort, ja que si aixo és cert podem estar segurs
       que existeix */
    return not vorg[id - 1].es_mort();
}

bool Sistema::es_estirable_org(int id) const {
    return id <= pob and not vorg[id - 1].esta_retallat();
}

bool Sistema::esta_ple() const {
    return pob == vorg.size();
}

bool Sistema::existeix_org(int id) const {
    return id <= pob;
}

int Sistema::consul_nvius() const {
    return pob - nmorts;
}

int Sistema::consul_fills_repr() const {
    return nfills_ur;
}

void Sistema::escriure_org(int id) {
    cout << id << " : ";
    vorg[id - 1].escriure_organisme();
}

// Modificadores

void Sistema::llegir_pob_ini(int pobini) {
    for (int i = 0; i < pobini - 1; ++i) {
        vorg[i].llegir_organisme();
        InfoEmparellaments ie;
        ie.e = Vbool(vorg.size() - i - 1, false);
        ie.ini = i + 1;
        empar.insert(empar.end(), ie);
    }
    /* L'ultim organisme no necessita informacio sobre emparellaments
       donat que de moment no en podra escollir a cap. L'acces es valid
       perque pobini >= 1 per la pre */
    vorg[pobini - 1].llegir_organisme();
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
  int i = 0;
  Lemp::iterator it = empar.begin();
  Vbool ocupat(pobaux, false);
  nfills_ur = 0;
  while (i < pobaux - 1 and pob < vorg.size()) {
    if (not ocupat[i] and not vorg[i].es_mort()) {
      bool incomp = true;
      /* Avancem l'organisme inicial d'emparellament mentre aquest
       * sigui mort o ja s'hi hagi emparellat. Aixo ens permet tenir
       * una notable millora en l'eficiencia de l'operacio donat que
       * la proxima vegada que l'organisme es reprodueixi no començarem
       * a buscar candidats des del principi, sino des del primer id
       * a partir del qual sabem que tots els anteriors son candidats no
       * no valids */
      while (incomp and (*it).ini < pobaux) {
        int cand = (*it).ini;
        incomp = vorg[cand].es_mort() or (*it).e[cand-i-1];
        if (not incomp) {
          if (not ocupat[cand]) emparellar_organismes(ocupat, rank, i, cand, it);
          else {
            ++cand;
            bool emparellables = false;
            while (not emparellables and cand < pobaux) {
              if (not ocupat[cand] and not vorg[cand].es_mort()
                                   and not (*it).e[cand-i-1]) {
                emparellables = true;
                emparellar_organismes(ocupat, rank, i, cand, it);
              }
              ++cand;
            }
          }
        }
        else ++(*it).ini;
      }
    }
    ++i;
    ++it;
  }
}
