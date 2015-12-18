/** @file Sistema.hpp
    @brief Especificació de la classe Sistema de la Pràctica de PRO2 <em>Reproducció al Laboratori</em>.
*/

#ifndef _SISTEMA_HPP_
#define _SISTEMA_HPP_

#include "Organisme.hpp"
#include "Ranking.hpp"

/**
 * @class Sistema
 * @brief <b>Descripció</b>
 *
 *        Representa un sistema format per organismes celulars on es poden
 *        produïr reproduccions entre organismes i creixement, decreixement
 *        i mort dels mateixos.
 *
 *        Es caracteritza per tenir un vector que conté els organismes i una
 *        població màxima permesa.
 *
 *        <b>Comentaris i observacions:</b>
 *
 *        <b>Com.:</b> Definim que un organisme <em>existeix</em> en el
 *        sistema sii el seu identificador està entre 1 i la població
 *        històrica del sistema (organismes vius i morts que han passat
 *        pel sistema), ambdós inclosos. Formalment, <em>1 <= id <= pob</em>.
 *
 *        <b>Obs.:</b> Pel que fa a les rondes de reproducció del sistema,
 *        es pot demostrar que <b>un organisme mai es pot emparellar amb un
 *        organisme d'identificador menor o igual</b>.<br>
 *        <b>Dem.:</b> Sigui \p id l'identificador de l'organisme que intenta
 *        escollir a un cert organisme amb identificador \p id'
 *        Per casos:
 *        <ul>
 *        <li>
 *        Si \p id = \p id' per les condicions de l'enunciat un organisme
 *        no es pot emparellar amb ell mateix.
 *        </li>
 *        <li>
 *        Si \p id' < \p id, per la forma en la que es desenvolupen les
 *        rondes, l'organisme \p id' haurà provat d'escollir a un organisme
 *        abans que \p id.
 *        <ul>
 *        <li>En el cas que n'hagi pogut escollir algun:
 *        <ul> <li> Si el que ha escollit és l'organisme \p id, efectivament
 *        \p id ja estarà ocupat per la ronda i no podrà escollir. </li>
 *        <li>Si el que ha escollit no és \p id aleshores tampoc podrà \p id
 *        escollir a \p id' ja que \p id' ja estarà ocupat en aquella ronda.
 *        </li>
 *        </ul>
 *        </li>
 *        <li>
 *        En el cas que \p id' no hagi pogut escollir a cap organisme, voldrà
 *        dir que, o bé \p id' és mort, o bé \p id és mort, o ja s'han
 *        emparellat o \p id ja està ocupat en la ronda.
 *        Si \p id' és mort òbviament \p id no podrà escollir-lo. Si
 *        \p id és mort òbviament tampoc podrà escollir a cap organisme.
 *        Si ja s'ha emparellat amb \p id òbviament \p id no podrà escollir
 *        un organisme amb el qual ja s'ha emparellat. Si està ocupat
 *        en la ronda òbviament \p id no podrà escollir \p id' donat que
 *        \p id ja estàra ocupat.
 *        </li>
 *        </ul>
 *        </ul>
 *
 *        Aquest resultat ens porta directament a un corol·lari:
 *        <ol>
 *        <li> L'organisme amb identificador màxim del sistema
 *        en una ronda donada mai podrà escollir a cap altre per
 *        emparellar-se (això no vol dir que no pugui ser escollit). <br>
 *        <b>Dem</b>: Sigui \p omax l'organisme amb identificador màxim en
 *        una ronda donada. En aquest cas el nº d'organismes amb
 *        identificador major que \p omax és nul, ja que hem definit
 *        que \p omax és el d'id màxim. En efecte, pel resultat
 *        anterior, mai podrà escollir a cap altre organisme per
 *        reproduir-se.</li>
 *        </ol>
 *        Aquest corol·lari ens permet no haver de guardar la informació dels
 *        organismes que pugui escollir o hagi escollit l'organisme amb
 *        identificador més gran del sistema en un moment donat, ja que
 *        aquest no podrà escollir-ne a cap de moment. */

class Sistema {
    public:
        // Constructores

        /**
         * @brief Creadora de Sistema.
         * @param pobmax Indica la població màxima que pot contenir el
         *        sistema.
         * \pre \p pobmax > 0
         * \post El resultat és un Sistema amb població nul·la,
         *       i amb població màxima permesa \p pobmax
         */
        Sistema(int pobmax);

        // Destructores

        /**
         * @brief Destructora per defecte.
         */
        ~Sistema();

        // Consultores

        /**
         * @brief Consultora de la <b>població històrica</b> del Sistema.
         * \pre Cert
         * \post El resultat és la població històrica (nombre d'organismes
         *       vius i morts) del paràmetre implícit
         */
        int consul_pob() const;

        /**
         * @brief Consultora que indica la <b>quantitat</b> d'organismes vius
         *        del Sistema.
         * \pre Cert
         * \post El resultat es el nombre d'organismes vius del paràmetre
         *       implícit
         */
        int consul_nvius() const;

        /**
         * @brief Consultora de l'<b>existència</b> d'un organisme.
         * @param id Identificador de l'organisme a consultar
         * \pre \p id >= 1
         * \post El resultat indica si l'organisme amb identificador \p id
         *       existeix al paràmetre implícit
         */
        bool existeix_org(int id) const;

        /**
         * @brief Consultora de <b>l'estat vital</b> d'un organisme.
         * @param id Identificador de l'organisme a consultar
         * \pre \p id >= 1
         * \post El resultat indica si l'organisme amb identificador \p id
         *       existeix al paràmetre implícit i està viu
         */
        bool es_viu_org(int id) const;
        
        /**
         * @brief Consultora de l'<b>estirabilitat</b> d'un organisme.
         * @param id Identificador de l'organisme a consultar
         * \pre \p id >= 1
         * \post El resultat indica si l'organisme amb identificador \p id
         *       existeix al paràmetre implícit i és estirable
         */
        bool es_estirable_org(int id) const;

        /**
         * @brief Consultora que indica si el sistema està plè (la
         *        seva població coincideix amb la màxima permesa).
         * \pre La població del paràmetre implícit és com a molt la màxima
         *      permesa
         * \post El resultat indica si el paràmetre implícit està plè
         */
        bool esta_ple() const;

        /**
         * @brief Consultora del nombre de fills nascuts en l'última ronda
         *        de reproducció del sistema
         * \pre Cert
         * \post El resultat és el nombre de <b>fills nascuts en l'última
         *       ronda de reproducció</b> del sistema, si n'hi ha hagut.
         *       Si no n'hi ha hagut, el resultat és zero
         */
        int consul_fills_repr() const;

        /**
         * @brief Operació d'<b>escriptura</b> d'organisme per identificador
         * @param id Identificador de l'organisme a escriure
         * \pre \p id És un identificador d'un Organisme existent al
         *      paràmetre implícit
         * \post S'ha escrit l'Organisme amb identificador \p id pel
         *       canal estàndard de sortida
         */
        void escriure_org(int id);

        // Modificadores

        /**
         * @brief Operació de <b>lectura</b> de la població inicial del
         *        sistema.
         * @param pobini Conté el nombre d'organismes de la població inicial
         *        del sistema
         * \pre \p pobini > 0
         * \post El paràmetre implícit conté la població inicial del sistema
         */
        void llegir_pob_ini(int pobini);

        /**
         * @brief Operació de <b>retallada</b> d'un organisme per
         *        identificador.
         * @param id Identificador de l'organisme a retallar
         * \pre \p id És un indentificador d'un organisme existent i viu al
         *      paràmetre implícit
         * \post L'Organisme amb identificador \p id del paràmetre implícit
         *       ha patit una retallada. Si l'organisme ha mort, el nombre
         *       de morts del paràmetre implícit s'ha incrementat en 1
         */
        void retallar_org(int id);

        /**
         * @brief Operació d'<b>estirament</b> d'un organisme per
         *        identificador.
         * @param id Identificador de l'organisme del paràmetre
         *        implícit a estirar
         * \pre \p id És un identificador d'un organisme existent i viu al
         *      paràmetre implícit
         * \post L'organisme amb identificador \p id del paràmetre
         *       implícit ha patit un estirament
         */
        void estirar_org(int id);

        /**
         * @brief Operació que aplica una <b>ronda de reproducció</b> al
         *        sistema.
         * @param[in,out] rank Ranking d'organismes associat al sistema
         * \pre <ul><li>Població actual del sistema = POB</li>
         * <li>POB > 0</li>
         * <li>Sigui i tal que 1 <= i <= POB l’element i  de la llista
         * d’informació d’emparellaments del paràmetre implícit conté la
         * informació dels emparellaments en rondes anteriors de l’organisme
         * amb id = i</li></ul>
         * \post <ul><li>Si s’ha arribat a la població màxima del sistema
         *  durant la ronda, els organismes amb identificadors 1..i han
         *  intentat escollir a un altre organisme per reproduir-se
         * (o han estat escollits o són morts). Altrament, els organismes
         * amb identificadors 1...POB-1 han intentat escollir a un altre
         * organisme per reproduir-se (o han estat escollits o són morts)</li>
         * <li>S'ha actualitzat el nombre de fills nascuts en la ronda</li>
         * <li>El rànking s'ha actualitzat amb la informació de les
         * reproduccions que hagin tingut fills en la ronda</li></ul>

         */
        void aplicar_ronda_reproduccio(Ranking&rank);

    private:
        // Definicions de tipus
        typedef vector<bool> Vbool;
        struct InfoEmparellaments {
            Vbool e;
            int ini;
        };
        typedef list<InfoEmparellaments> Lemp;
        // Atributs privats
        /** @brief Vector que conté en tot moment els organismes
         *  (vius i morts) del sistema. El seu tamany coincideix
         *  amb la població màxima permesa del sistema i la posició
         *  <em>i-èssima</em> del vector conté l'Organisme amb identificador
         *  <em>id = i + 1</em> */
        vector<Organisme> vorg;
        /** @brief Conté el nombre d'organismes (vius i morts que hagin estat
            vius algun cop) del Sistema. */
        int pob;
        /// @brief Conté el nombre d'organismes morts existents al Sistema.
        int nmorts;
        /** @brief Conté el nombre de fills nascuts en l'última ronda de
            reproducció del sistema, si la ha hagut. Sinó el seu valor
            és 0. */
        int nfills_ur;
        /** @brief Llista que conté la informació dels emparellaments
         *  dels organismes existents al Sistema, excepte l'últim, que
         *  pel que s'ha demostrat en la descripció de la classe no
         *  en necessitem la informació dels emparellaments perquè
         *  no es podrà emparellar de moment. Té tamany <em>pob - 1</em>.<br>
         *  La posició i de la llista conté un enter <em>ini</em>
         *  que representa l'id decrementat en una unitat
         *  de l'organisme amb id més petit a partir
         *  del qual l'organisme amb id=<em>i+1</em> pot emparellar-se en
         *  un moment donat. <br>Donat un organisme d'identificador menor a
         *  <em>ini</em>, o bé no s'hi pot emparellar (perquè té id igual
         *  o menor), o bé és mort, o bé ja s'hi ha emparellat. Si l'organisme
         *  <em>i+1</em> no té cap organisme per emparellar-se aleshores el
         *  valor de la posició <em>i</em> coincideix amb la població actual.
         *  <br>La posició <em>i</em> de la llista també conté
         *  un vector de booleans <em>e</em> de tamany
         *  <em>[població màxima - i - 1]</em> (pel que es demostra en la
         *  descripció de la classe) i la posició <em>j</em> indica si
         *  l'organisme amb <em>id = i + 1</em> s'ha emparellat amb
         *  l'organisme amb <em>id = i + j + 2</em>. */
        Lemp empar;
        // Operacions privades
        /**
         * @brief Operació que emparella dos organismes del sistema i
         *        ordena (en el sentit imperatiu) l'actualització del ranking
         * @param[in,out] ocupat Vector de booleans associat a la ronda que
         *        indica si els organismes ja s'han emparellat(en la ronda).
         * @param[in,out] rank Ranking associat al sistema
         * @param i <em>i + 1</em> És l'identificador de l'organisme que
         *        ha escollit a l'organisme <em>j + 1</em> per reproduir-se
         * @param j <em>j + 1</em> és l'organisme escollit per
         *        l'organisme <em>i + 1</em> per reproduir-se
         * \pre <ul><li><em>0 <\p j <= agafat.size()</em></li>
         *      <li>\p i < \p j</li>
         *      <li><em>agafat.size() < població màxima permesa</em></li>
         *      <li>\p rank és un rànking associat al paràmetre implícit
         *      (comparteixen població màxima)</li></ul>
         *
         * \post L'organisme <em>\p i+1</em> s'ha emparellat amb l'organisme
         *       \p j+1, els dos organismes s'han marcat com a agafats
         *       en la ronda i, en cas de que fóssin compatibles s'ha
         *       incrementat la població i el nombre de fills nascuts en
         *       la ronda en una unitat, a més d'haver actualitzat \p rank
         *       conseqüentment
         */
        void emparellar_organismes(Vbool&ocupat, Ranking&rank, int i, int j,
                                   Lemp::iterator it);
};

#endif
