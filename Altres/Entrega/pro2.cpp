/** @mainpage Pràctica de Programació 2: Reproducció al Laboratori

    En aquesta pràctica s'ha implementat un programa modular que ofereix
    un menú d'opcions per simular un experiment de laboratori amb
    <b>organismes cel·lulars</b> que poden créixer, decréixer, morir i
    reproduir-se, a més de disposar de l'opció d'obtenir en tot moment un
    rànking amb informació de les reproduccions dels organismes.

    Per implementar-lo s'ha dividit en <b>5 mòduls</b>:
    <ul>
        <li>El programa principal, el codi del qual està contingut en
        l'arxiu <em>pro2.cpp</em>.</li>
        <li>La classe Celula (<em>Celula.cpp</em>), per representar
        les cèl·lules dels organismes.</li>
        <li>La classe Organisme (<em>Organisme.cpp</em>), per
        representar els organismes i les seves operacions.</li>
        <li>La classe Ranking (<em>Ranking.cpp</em>), que representa
        el <b>rànking de reproduccions</b> i les seves operacions.</li>
        <li>La classe Sistema (<em>Sistema.cpp</em>), que conté el
        <b>conjunt d'organismes</b> i certa informació relativa a
        l'experiment.</li>
    </ul>

    <b>Comentaris:</b>
    <ul>
    <li>
    Sobre el diagrama modular, es pot notar que el programa principal no
    accedeix mai directament sobre la classe Organisme. Això és degut a que
    podríem tenir una pèrdua notable d'eficiència si ho féssim, donat que
    els objectes de la classe Organisme poden tenir un tamany (en memòria)
    important i en la majoria dels casos hauríem d'obtenir els organismes
    mitjançant la classe Sistema (aquesta hauria de tenir funcions que
    retornéssin organismes), i això suposaria haver de fer una còpia cada
    cop que en volguéssim consultar.
    </li>
    <li>
    També es pot notar que hi ha operacions que en principi no haurien
    de modificar el Sistema o els organismes, però aquests paràmetres
    es passen per <b>referència no constant</b>. Això és degut a que si
    els passéssim per referència constant hauríem de fer còpies per consultar
    els arbres dels organismes, i això ens suposaria novament una pèrdua
    notable d'eficiència. En el seu defecte es passen per referència i
    per tal que no quedin modificats es replanten les arrels amb els
    subarbres en totes les funcions de consulta.
    </li>
    </ul>

*/

/** @file pro2.cpp
 *
    @brief Programa principal de la Pràctica de PRO2
    <em>Reproducció al Laboratori</em>.

    En aquesta pràctica suposem que les dades llegides sempre
    són correctes, en conseqüència no es fan comprovacions sobre l'entrada.
    Les opcions a aplicar a l'experiment es representen amb
    nombres negatius, del -1 al -6.
*/

#include "Ranking.hpp"
#include "Sistema.hpp"

/* Declaració de constants per cada opció de l'experiment per tal
   d'augmentar la llegibilitat del codi */
const int ESTIRAMENT = -1;
const int RETALLADA = -2;
const int RONDAREP = -3;
const int OBTRANKING = -4;
const int CONSULEST = -5;
const int FINAL = -6;

/** @brief Acció que duu a terme l'opció d'aplicar estiraments a un
    subconjunt d'organismes de l'experiment. <br> Aquells organismes llegits
    pel canal estàndar existents a l'experiment i que no hagin sigut
    retallats amb anterioritat han patiràn un estirament.
    */
void aplicarEstiramentsSubcjt(Sistema&sis) {
    int L = readint();

    for (int i = 0; i < L; ++i) {
        int id = readint();
        // Només ens cal comprovar que l'organisme és estirable
        // (existeix i no s'ha retallat amb anterioritat) i retallar-lo
        // en cas afirmatiu
        if (sis.es_estirable_org(id)) sis.estirar_org(id);
    }
}

/** @brief Acció que duu a terme l'opció d'aplicar retallades a un
    subconjunt d'organismes de l'experiment. <br> Aquells organismes vius
    i existents a l'experiment llegits pel canal estàndar d'entrada patiràn
    una retallada.
    */
void aplicarRetalladesSubcjt(Sistema&sis) {
    int L = readint();

    for (int i = 0; i < L; ++i) {
        int id = readint();
        // Només ens cal comprovar que existeix i és viu, i retallar-lo en
        // conseqüència
        if (sis.es_viu_org(id)) sis.retallar_org(id);
    }
}

/** @brief Acció que duu a terme l'opció de consultar un subconjunt
    d'organismes de l'experiment. <br> Aquells organismes llegits pel canal
    estàndar que existeixin al sistema seràn escrits pel canal estàndar
    de sortida
    */
void consultarSubcjt(Sistema&sis) {
    int L = readint();

    cout << "ORGANISMOS" << endl;
    for (int i = 0; i < L; ++i) {
        int id = readint();
        // Comprovem que existeix, i en cas afirmatiu l'escrivim
        if (sis.existeix_org(id)) sis.escriure_org(id);
    }
    cout << endl;
}

/** @brief Acció que notifica sobre la causa del final de l'experiment. <br>
    S'escriu el nombre d'organismes totals que ha contingut l'experiment
    i el nombre d'organismes vius en el moment de la fi de l'experiment
    */
void notiFinal(Sistema&sis, const Ranking&rank) {
    cout << "FIN" << endl << endl
         << "Organismos en total : " << sis.consul_pob() << endl
         << "Organismos vivos : " << sis.consul_nvius() << endl << endl;

    if (sis.esta_ple()) {
        cout << "ORGANISMOS" << endl;
        /* Escrivim els organismes nascuts en l'última ronda
           en ordre creixent per identificador. Per la condició
           de l'if sabem que si N és la població actual (de fet coincideix
           amb la població màxima permesa) i el nombre
           d'organismes nascuts a l'última reproducció és R aleshores
           tenen per identificadors [N-R+1...N], ja que els identificadors
           s'assignen correlativament de menor a major a mesura que neixen
           nous organismes */
        int pob = sis.consul_pob();
        int nfillsur = sis.consul_fills_repr();
        for (int i = pob - nfillsur + 1; i <= pob; ++i) {
            sis.escriure_org(i);
        }
        cout << endl << "RANKING" << endl;
        rank.escriure_ranking(sis.consul_pob());
    }
}

/** @brief Programa principal de la Pràctica de PRO2
    <em>Reproducció al Laboratori</em>.
*/
int main() {
    int N = readint(); // Població inicial de l'experiment
    int M = readint(); // Població màxima permesa de l'experiment
    Sistema sis(M);
    sis.llegir_pob_ini(N);
    Ranking rank(M);

    int op; // Codi d'operació
    while (sis.consul_nvius() > 0 and not sis.esta_ple()
                                  and cin >> op and op != FINAL) {
        switch (op) {
            case ESTIRAMENT: aplicarEstiramentsSubcjt(sis);
            break;
            case RETALLADA: aplicarRetalladesSubcjt(sis);
            break;
            case RONDAREP:
                cout << "RONDA DE EMPAREJAMIENTOS" << endl;
                sis.aplicar_ronda_reproduccio(rank);
                cout << "Nuevos organismos : " << sis.consul_fills_repr()
                     << endl << endl;
            break;
            case OBTRANKING:
                cout << "RANKING" << endl;
                rank.escriure_ranking(sis.consul_pob());
            break;
            case CONSULEST: consultarSubcjt(sis);
            break;
        }
    }

    notiFinal(sis, rank);
}
