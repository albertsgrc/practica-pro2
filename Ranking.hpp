/** @file Ranking.hpp
    @brief Especificació de la classe Ranking de la Pràctica de PRO2 <em>Reproducció al Laboratori</em>.
*/

#ifndef _RANKING_HPP_
#define _RANKING_HPP_

#include <list>
#include <vector>
#include "utils.PRO2"

/**
 * @class Ranking
 * @brief
 *        <b>Descripció:</b><br>
 *        Representa un rànking de reproduccions entre organismes.
 *        Es caracteritza per tenir una llista d'enters que representa
 *        l'ordre del rànking i un vector amb les llistes d'emparellaments
 *        de cada organisme.
 *
 *        <b>Comentaris:</b>
 *        <ul>
 *        <li>
 *        Aclarar que en aquesta classe en concret quan fem servir la paraula
 *        organisme per fer referència a un objecte de la classe organisme no
 *        ens referim a l'objecte en sí sinó al seu identificador.
 *        </li>
 *        <li>
 *        Sempre que es faci referència a un identificador d'un organisme
 *        perquè aquest apareix com a paràmetre d'una funció ens referirem
 *        a l'identificador incrementat en una unitat respecte
 *        el que s'especifica, donat que per no deixar la posició 0 dels
 *        vectors buida els identificadors es decrementen en una unitat en
 *        el seu tractament.
 *        </li>
 *        </ul>
 */
class Ranking {
    public:
        // Constructores

       /**
        * @brief Creadora de Ranking.
        * @param pobmax Nombre màxim d'organismes que pot contenir el rànking
        * \pre \p pobmax > 0
        * \post El resultat és un Ranking buit amb població màxima \p pobmax
        */
        Ranking(int pobmax);

        // Destructores

        /**
         * @brief Destructora per defecte.
         */
        ~Ranking();

        // Consultores

        /** @brief Operació d'escriptura del rànking.
         * @param pob Població històrica del sistema associat al rànking
         * \pre \p pob és com a molt la població màxima del paràmetre implícit,
         *       i és com a mínim el nombre d'organismes que s'han reproduit en
         *       el sistema associat al Ranking
         * \post S'han escrit els \p pob primers organismes del paràmetre
         *       implícit en ordre decreixent per nombre de fills creats i,
         *       en cas d'empat, per ordre creixent d'identificador de
         *       l'organisme
         */
        void escriure_ranking(int pob) const;

        // Modificadores

        /** @brief Acció que afegeix una parella i un fill al rànking
         *  @param id1 Identificador del primer organisme de la parella
         *  @param id2 Identificador del segon organisme de la parella
         *  @param fill Identificador del fill
         * \pre <ul><li>\p id1 i \p id2 són menors que la població màxima
         *      del paràmetre implícit (aquest cop es refereix als valors
         *      decrementats dels identificadors, que van de 0 en endavant)</li>
         *      <li>\p fill és major que tots els identificadors de fills
         *      existents al paràmetre implícit</li></ul>
         * \post S'ha afegit la parella < \p id1, \p id2 > i el fill
         *       \p fill al paràmetre implícit, actualitzant l'ordre
         *       del rànking
         */
        void afegir_parella(int id1, int id2, int fill);


    private:
        // Definicions de tipus
        /** @brief Estructura de dades que conté la informació d'una
            reproducció */
        struct Reproduccio {
            int parella; /// @brief Identificador d'una parella
            int fill; /// @brief Identificador del fill corresponent
        };

        typedef list<Reproduccio> Lrep;
        /** @brief Estructura de dades que conté l'informació de les parelles
            i els fills d'un organisme, a més d'un iterador apuntant
            a la seva posició en rànking en cas de que s'hagi reproduït */
        struct Dades {
            /** @brief Llista de reproduccions, conté la informació
             *  de les parelles i els fills resultants de les reproduccions
             *  d'un organisme. Està ordenada creixentment per l'id dels
             *  dels fills */
            Lrep empar;
            /** @brief Iterador a la posició que ocupa un organisme
             *  al rànking (si s'ha reproduït) per tal de fer insercions
             *  eficients */
            list<int>::iterator itr;
        };

        typedef list<int> Lint;

        // Atributs privats
        /** @brief Llista d'enters que conté els identificadors dels
         *         organismes que s'han reproduït, ordenada
         *         <b>creixentment</b> pel nombre de fills creats,
         *         i, en cas d'empat, decreixentment per identificador
         *         (ordre oposat al que demana l'enunciat), per tal de
         *         poder fer insercions eficients des del principi de la
         *         llista. (A l'hora d'escriure'l es fa en ordre invers).
                   */
        Lint ordre;

        /** @brief Vector de tamany la població màxima del rànking en el que
         *         la posició <em>i</em> conté la llista d'emparellaments i
         *         l'iterador apuntant a la posició que ocupa l'organisme
         *         amb id = <em>i+1</em> a la llista del rànking. */
        vector<Dades> org;
        // Mètodes privats
        /**
         * @brief Acció que escriu la llista d'emparellaments d'un organisme
         *        (parelles i fills).
         * @param l Llista d'emparellaments
         * \pre Cert
         * \post S'ha escrit pel canal estàndard de sortida la llista de
         *       fills i parelles ordenada creixentment per l'identificador
         *       del fill
         */
        static void escriure_llista_org(const Lrep &l);
        /**
         * @brief Acció que actualitza l'ordre del rànking i afegeix
         *        una reproducció (parella i fill) a un organisme
         * @param id1 Identificador de l'organisme a qui s'afegeix la
         *        reproducció i s'actualitza la posició en el rànking
         * @param id2 Identificador de la parella de l'organisme \p id1
         * @param fill Identificador del fill resultant de la reproducció
         *        dels organismes \p id1 i \p id2
         * \pre <ul><li>0 <= id1 < població màxima</li><li>0 <= id2 <
         *      població màxima</li></ul>
         * \post La parella \p id2 i el fill \p fill s'han afegit a la
         *       llista d'emparellaments \p d'id1 i s'ha actualitzat l'ordre
         *       del paràmetre implícit
         */
        void actualitzar_org(int id1, int id2, int fill);
        /**
         * @brief Acció que inserta un organisme a la posició que li toca
         *        en l'ordre del rànking
         * @param id Identificador de l'organisme a insertar
         * @param it Iterador que apunta a la posició a partir de la qual
         *        es comença a buscar la posició d'inserció
         * \pre <ul><li>Tots els organismes anteriors al referenciat per \p it en
         *      el paràmetre implícit han creat menys fills (o, en cas d'empat
         *      tenen major identificador) que l'organisme amb identificador
         *      \p id (recordem que el rànking està ordenat
         *      al revés).</li><li>0 <= \p id < població màxima</li><li>
         *      ordre.begin() <= \p it <= ordre.end()</li></ul>
         * \post L'organisme amb identificador \p id s'ha insertat
         *       en la posició que li toca en l'ordre del paràmetre implícit
         */
        void insertar_org(int id, Lint::iterator it);
        /**
         * @brief Funció de comparació per l'ordre del rànking
         * @param id1 Identificador del primer organisme
         * @param id2 Identificador del segon organisme
         * \pre <ul><li>0 <= \p id1 < població màxima</li><li>0 <= \p id2 <
         *      població màxima</li></ul>
         * \post Si el nombre de fills de l'organisme \p id1 coincideix
         *       amb el nombre de fills \p d'id2 el resultat indica si \p id1
         *       és més gran que \p id2. Altrament el resultat indica si el
         *       nombre de fills \p d'id1 és més petit que el nombre de fills
         *       \p d'id2
         */
        bool comp(int id1, int id2);
};

#endif
