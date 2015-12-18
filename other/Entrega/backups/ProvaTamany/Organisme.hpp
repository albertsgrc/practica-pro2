/** @file Organisme.hpp
    @brief Especificació de la classe Organisme de la Pràctica de PRO2
           <em>Reproducció al Laboratori</em>.
*/

#ifndef _Organisme_HPP_
#define _Organisme_HPP_

#include "Celula.hpp"
#include "Arbre.hpp"
#include <vector>

/**
 * @class Organisme
 * @brief Representa un organisme de l'experiment.
 *        Es caracteritza per tenir un identificador que l'identifica
 *        unívocament i un arbre que representa la seva morfologia.
 */
class Organisme {
    public:
        // Constructores

        /**
         * @brief Creadora per defecte. S'executa automàticament al declarar
         *        un Organisme.
         * \pre Cert
         * \post El resultat és un Organisme mort
         */
        Organisme();

        /**
         * @brief Operació de reproducció entre organismes.
         * @param[out] fill Paràmetre de sortida en el que es guardarà el
         *       fill resultant de la reproducció en cas de que els
         *       organismes siguin compatibles.
         * @param[in] escollit Paràmetre d'entrada que conté l'organisme
         *       escollit pel paràmetre implícit per a reproduir-se.
         * @param[out] compatibles Paràmetre de sortida que indica si el
         *        paràmetre implícit i \p escollit són compatibles.
         *       (i.e la reproducció ha donat lloc a un fill).
         * \pre  <ul><li>El paràmetre implícit i \p escollit són Organismes
         *       vius.</li>
         *       <li>\p fill és un Organisme mort.</li></ul>
         * \post <ul><li>El paràmetre implícit i \p escollit no s'han
         *       modificat</li><li>\p fill és l'Organisme resultant
         *       de la reproducció del paràmetre implícit i \p escollit
         *       si \p compatible és cert. Si \p compatible és fals
         *       \p fill és un organisme mort i no existent
         *       (no s'ha modificat)</li></ul>
         */
        void reproduir_parella(Organisme&escollit, Organisme&fill, bool&compatibles);

        // Destructores

        /**
         * @brief Destructora per defecte.
         */
        ~Organisme();

        // Consultores

        /**
         * @brief Consultora del tamany (nombre de cèl·lules no buides)
         *        d'un organisme
         * \pre Cert
         * \post El resultat és el tamany del paràmetre implícit
         */
        int consul_tam() const;

        /**
         * @brief Consultora de l'estat vital d'un organisme.
         * \pre Cert
         * \post El resultat indica si el paràmetre implícit és mort
         */
        bool es_mort() const;

        /**
         * @brief Operació d'escriptura d'un organisme.
         * \pre Cert
         * \post <ul><li>S'ha escrit la morfologia del paràmetre implícit pel
         *       canal estàndard de sortida.</li><li>El paràmetre implícit no
         *       s'ha modificat.</li></ul>
         */
        void escriure_organisme();

        /**
         * @brief Consultora que indica si un organisme ha patit una retallada
         * \pre Cert
         * \post El resultat indica si el paràmetre implícit ha sigut retallat
         *       algun cop desde la seva creació.
         */
        bool esta_retallat() const;

        // Modificadores

        /**
         * @brief Operació de retallada d'un organisme.
         * \pre El paràmetre implícit no està mort
         * \post El paràmetre implícit ha patit una retallada
         */
        void aplicar_retallada();

        /**
         * @brief Operació d'estirament d'un Organisme.
         * \pre El paràmetre implícit no està mort
         * \post El paràmetre implícit ha patit un estirament
         */
        void aplicar_estirament();

        /**
         * @brief Operació de lectura d'un organisme.
         * \pre El paràmetre implícit no està mort
         * \post S'ha llegit el paràmetre implícit pel canal estàndard
         *       d'entrada
         */
        void llegir_organisme();

	private:
        // Declaracions de tipus
        typedef Arbre<Celula> Arbcel;
        // Atributs privats
        /** @brief Representa la morfologia de l'organisme, és a dir, les
         *  cèl·lules que el conformen i les relacions existents entre elles.
         */
        Arbcel morfologia;
        /// @brief Indica si l'organisme ha patit una retallada.
        bool retallat;
        /** @brief Conté en tot moment l'identificador de la cèl·lula amb id
         * de màxim valor de l'organisme. Si l'organisme és mort el seu
         * valor és 0. */
        int idmax;
        /** @brief Conté en tot moment el tamany de l'Organisme
         *  (nº de cèl·lules no buides). S'utilitza per fer una millora
         *  d'eficiència en la funciód e reproducció, en la que descartem
         *  directament el cas en que el tamany d'un dels dos organismes
         *  sigui menor que la suma dels tamanys dividida per 4, ja que
         *  en aquest cas és impossible que siguin compatibles */
        int tam;
        // Mètodes privats
        /**
         * @brief Acció de lectura d'un arbre de cèl·lules.
         * @param[out] a Arbre de cèl·lules a llegir
         * @param[out] idmax Paràmetre de sortida on es guardarà
         *       l'identificador màxim de l'organisme un cop llegit
         * \pre \p a és buit
         * \post <ul><li>\p a és l'arbre de cèl·lules llegit pel canal
         *       estàndard d'entrada en format <b>preordre</b></li><li>
         *       \p idmax conté l'identificador de màxim valor de totes
         *       les cèl·lules d'\p a</li><li>\p tam conté el nombre
         *       de cèl·lules d'\p a</li></ul>
         */
        static void llegir_arbcelula(Arbcel&a, int&idmax, int&tam);

        /**
         * @brief Acció d'escriptura d'un arbre de cèl·lules.
         * @param[in] a Arbre de cèl·lules a escriure
         * \pre Cert
         * \post <ul><li>\p a no s'ha modificat</li><li> S'ha escrit
         *       \p a pel canal estàndard de sortida en format <b>inordre</b>,
         *       amb els identificadors de les cèl·lules acompanyats d'un
         *       <em>1</em> si són actives i un <em>-1</em> si són passives
         *       </li></ul>
         */
        static void escriure_arbcelula(Arbcel&a);

        /**
         * @brief Acció de retallada d'un arbre de cèl·lules.
         * @param[in,out] a Arbre de cèl·lules a retallar.
         * @param[out] idmax Paràmetre de sortida on es guardarà
         *       l'identificador màxim de l'arbre després de la retallada
         * \pre \p <ul><li>\p a és no buit</li><li>\p idmax = 0</li>
         *       <li>\p a=A</li></ul>
         * \post <ul><li>\p a és l'arbre resultant d'eliminar totes les fulles
         *       d'A</li><li>\p Si \p a és no buit idmax és l'identificador
         *       màxim d'entre totes les cèl·lules d'\p a, altrament \p idmax
         *       val 0</li><li>\p tam s'ha decrementat en tantes unitats
         *       com nombre de cèl·lules fulla s'hagin eliminat</li></ul>
         */
        static void retallar_arbcelula(Arbcel&a, int&idmax, int&tam);

        /**
         * @brief Acció d'estirament d'un arbre de cèl·lules.
         * @param[in,out] a Arbre de cèl·lules a estirar
         * @param[in,out] idmax Paràmetre d'entrada/sortida que val en tot
         *       moment l'identificador màxim de totes les cèl·lules d'\p a
         * \pre <ul><li>\p a=A</li><li>\p idmax conté l'identificador màxim
         *      de totes les cèl·lules d'\p a</li><li>\p a és no buit</li></ul>
         * \post <ul><li>\p a és el resultat d'afegir dues cèl·lules filles a
         *       totes les fulles d'\p A, amb valors d'identificadors
         *       a partir del següent al màxim identificador d'A
         *       assignats correlativament d'esquerra a dreta en l'arbre,
         *       i amb activitat o passivitat heredada de la corresponent
         *       fulla mare en A</li> <li>\p idmax conté l'identificador màxim
         *       de totes les cèl·lules d'\p a</li><li>\p tam s'ha incrementat
         *       en tantes unitats com el doble del nº de fulles d'A</li></ul>
         */
        static void estirar_arbcelula(Arbcel&a, int&idmax, int&tam);

        /**
         * @brief Acció de creació de l'Arbre del fill i obtenció
         *        d'informació de la compatibilitat d'una parella
         *        d'arbres associats a Organismes.
         * @param[in] x1 Arbre de l'Organisme que escull a \p x2 per a
         *       reproduir-se
         * @param[in] x2 Arbre de l'Organisme escollit per \p x1 per a
         *       reproduir-se
         * @param[out] fill Arbre de l'Organisme resultant de la reproducció
         *       d'\p x1 amb \p x2
         * @param[in,out] idclonsx2 Identificador que s'utilitzarà per
         *       assignar als clons de cèl·lules de l'arbre \p x2, inicialment
         *       coinicident amb l'identificador màxim de l'arbre \p x1
         * @param[out] idmaxf Paràmetre de sortida on es guardarà el valor
         *       de l'identificador màxim del fill
         * @param[out] tamint Paràmetre de sortida on es guardarà el valor del
         *       tamany de la intersecció dels arbres \p x1 i \p x2
         * @param[out] tamx1 Paràmetre de sortida on es guardarà el valor del
         *       tamany de l'arbre \p x1
         * @param[out] tamx2 Paràmetre de sortida on es guardarà el valor del
         *       tamany de l'arbre \p x2
         * \pre <ul><li>\p x1 i \p x2 són no buits</li><li>\p fill és buit</li>
         *      <li>\p idmaxf = \p tamint = \p tamf = 0</li>
         *      <li>\p idclonsx2 coincideix amb l'identificador màxim de totes
         *      les cèl·lules d'\p x1</li></ul>
         * \post <ul><li>\p x1 i \p x2 no s'han modificat</li>
         *       <li>\p fill és l'arbre de l'Organisme resultant de la
         *       reproducció dels organismes els arbres dels quals són
         *       \p x1 i \p x2</li><li>\p idclonsx2 conté l'identificador
         *       màxim d'\p x1 si no s'ha plantat cap clon d'\p x2, altrament
         *       conté l'identificador de l'últim clon plantat d'\p x2</li>
         *       <li>\p idmaxf conté l'identificador màxim de \p fill</li>
         *       <li>\p tamint conté el tamany de l'intersecció de \p x1 i
         *       \p x2</li><li>\p tamx1 i \p tamx2 contenen el tamany dels
         *       arbres \p x1 i \p x2 respectivament (nombre de nodes)</li>
         *       <li>\p tamf conté el nombre de cèl·lules de \p fill</li></ul>
         */
        static void crear_fill(Arbcel&x1, Arbcel&x2, Arbcel&fill, int&idclonsx2, int&idmaxf, int&tamint, int&tamf);

        /**
         * @brief Acció auxiliar que col·loca els clons d'un subarbre de
         *        l'arbre de l'organisme que escull a un altre per reproduir-se
         * @param[in] x1 Subarbre de l'organisme les cèl·lules del qual es
         *        clonifiquen
         * @param[in] fill Subarbre del fill on es col·loquen les cèl·lules
         *        clonificades
         * @param[in,out] tamx1 Nombre de nodes tractats de l'arbre de
         *       l'organisme que escull a un altre per reproduir-se
         * @param[in,out] idmaxf Identificador màxim de totes les cèl·lules
         *       de la part creada del fill (no es refereix al paràmetre
         *       d'aquesta funció, que de fet és un subarbre de la part de
         *       l'arbre del fill creada sinó a la part del fill creada,
         *       en la seva totalitat)
         * \pre <ul><li>\p x1 és no buit</li><li>\p fill és buit</li></ul>
         * \post <ul><li>\p x1 no s'ha modificat</li><li>\p tamx1 s'ha
         *       incrementat en el nombre de clons que s'hagin plantat</li>
         *       <li>S'han afegit a \p fill els clons de les cèl·lules actives
         *       d'\p x1 a més del mínim nombre de cèl·lules passives per tal
         *       que les actives no quedéssin desconectades, amb identificadors
         *       coincidents amb les corresponents cèl·lules d'\p x1</li>
         *       <li>\p idmaxf s'ha actualitzat amb el màxim entre el seu valor
         *       inicial i el màxim d'entre tots els identificadors de les
         *       cèl·lules plantades al \p fill</li><li>\p tamf s'ha
         *       incrementat en tantes unitats com nombre de clons s'hagin
         *       plantat</li></ul>
         */
        static void aux_clons_x1(Arbcel&x1, Arbcel&fill, int&tamf, int&idmaxf);

        /**
         * @brief Acció auxiliar que col·loca els clons d'un subarbre de
         *        l'arbre de l'organisme que és escollit per un altre per
         *        reproduir-se
         * @param[in] x2 Subarbre de l'organisme les cèl·lules del qual es
         *        clonifiquen
         * @param[in] fill Subarbre del fill on es col·loquen les cèl·lules
         *        clonificades
         * @param[in,out] tamx2 Nombre de nodes tractats de l'arbre de
         *       l'organisme escollit per un altre per reproduir-se
         * @param[in,out] idmaxf Identificador màxim de totes les cèl·lules
         *       de la part creada del fill (no es refereix al paràmetre
         *       d'aquesta funció, que de fet és un subarbre de la part de
         *       l'arbre del fill creada sinó a la part del fill creada,
         *       en la seva totalitat)
         * @param[in,out] idclonsx2 Conté l'indentificador de l'últim
         *       clon plantat, si no se n'ha plantat cap conté
         *       l'identificador màxim de l'arbre de l'Organisme que ha
         *       escollit a l'Organisme un subarbre del qual és \p a
         *       per reproduir-se
         * \pre <ul><li>\p x2 és no buit</li><li>\p fill és buit</li>
         *      </ul>
         * \post <ul><li>\p x2 no s'ha modificat</li><li>\p tamx2 s'ha
         *       incrementat en el nombre de clons que s'hagin plantat</li>
         *       <li>S'han afegit a \p fill els clons de les cèl·lules actives
         *       d'\p x2 a més del mínim nombre de cèl·lules passives per tal
         *       que les actives no quedéssin desconectades, amb identificadors
         *       assignats correlativament en preordre a partir del valor
         *       següent a \p idclonsx2</li><li>\p idclonsx2 conté
         *       l'indentificador de l'últim clon plantat, si no se n'ha
         *       plantat cap el seu valor no s'ha modificat</li><li>\p tamf s'ha
         *       incrementat en tantes unitats com nombre de clons s'hagin
         *       plantat</li></ul>
         */
        static void aux_clons_x2(Arbcel&x2, Arbcel&fill, int&tamf, int&idmaxf, int&idclonsx2);
};

#endif
