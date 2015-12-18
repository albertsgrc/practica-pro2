/** @file Celula.hpp
    @brief Especificació de la classe Celula de la Pràctica de PRO2
    <em>Reproducció al Laboratori</em>.
*/

#ifndef _CELULA_HPP_
#define _CELULA_HPP_

#include "utils.PRO2"

/**
 * @class Celula
 * @brief Representa una cèlula d'un organisme
 *
 *        Es caracteritza per un natural que l'identifica i pot ser activa
 *        o passiva. Es pot llegir, escriure i es poden consultar els seus
 *        paràmetres. Les cèlules buides tenen un identificador especial,
 *        el 0, i són passives.
 *
 *        <b>Comentaris:</b>
 *
 *        Aquesta classe té poques operacions i totes són creadores,
 *        consultores, o de lectura o escriptura. La seva utilització
 *        no era estrictament necessària però vaig considerar que seria
 *        millor tenir les seves operacions agrupades en un mòdul per tal
 *        d'organitzar millor el programa modular, ja que tampoc suposa una
 *        pèrdua notable d'eficiència, i vaig considerar l'organització un
 *        criteri prioritari.
 */
class Celula {
	public:
        // Constructores

        /**
         * @brief Creadora per defecte. S'executa automàticament al
         *        declarar una Celula.
         * \pre Cert
         * \post El resultat és una Celula <b>buida</b>
         */
        Celula();

        /**
         * @brief Creadora amb paràmetres.
         * @param identificador Identificador de la cèl·lula a crear
         * @param activitat Indicador de la activitat/passivitat de la cèl·lula
         *        a crear
         * \pre Cert
         * \post El resultat és una cèlula amb identificador \p id.
         *       Si \p activa és cert, aleshores la cèl·lula resultant
         *       és <b>activa</b>, altrament és <b>passiva</b>
         */
        Celula(int identificador, bool activitat);

        /**
         * @brief Constructora de còpia. Crea una cèl·lula còpia d'una altra.
         * @param c Celula de la qual es vol crear una còpia
         * \pre Cert
         * \post El resultat és una Celula copia de \p c
         */
        Celula(const Celula&c);

        // Destructores

        /**
         * @brief Destructora per defecte.
         */
        ~Celula();

        // Consultores

        /**
         * @brief Consultora que indica si una cèl·lula és buida.
         * \pre Cert
         * \post El resultat indica si el paràmetre implícit és una
         *       Celula <b>buida</b>
         */
        bool es_buida() const;

        /**
         * @brief Consultora de la activitat/passivitat d'una cèl·lula.
         * \pre Cert
         * \post El resultat indica si el paràmetre implícit és una Celula
         *       <b>activa</b>
         */
        bool es_activa() const;

        /**
         * @brief Consultora de l'identificador d'una cèl·lula.
         * \pre Cert
         * \post El resultat és <b>l'identificador</b> del paràmetre implícit
         */
        int consul_id() const;

        /**
         * @brief Operació d'escriptura d'una cèl·lula.
         * \pre Cert
         * \post S'ha escrit pel canal estàndard de sortida l'identificador
         *       del paràmetre implícit i un <em>'-1'</em> si la Celula és
         *       <b>passiva</b> o un <em>'1'</em> si és <b>activa</b>
         */
        void escriure_celula() const;

        // Modificadores

        /**
         * @brief Operació de lectura d'una cèl·lula
         * \pre Estàn preparats al canal estàndard d'entrada un enter
         *      que representa l'identificador de la cèl·lula a llegir
         *      i, si la cèl·lula no és buida, un booleà que
         *      indica si la cèl·lula a llegir és activa o
         *      passiva
         * \post S'han llegit els paràmetres <em>id</em> i <em>activa</em>
         *       del parámetre implícit si la cèl·lula no és buida.
         *       En cas de ser buida només s'ha llegit el seu identificador
         *       (un 0) i la Celula resultant és passiva.
         */
        void llegir_celula();


	private:
        /// @brief Conté l'identificador de la cèl·lula
        int id;
        /// @brief Indica si la cèl·lula és activa o passiva.
        bool activa;
        /// @brief Identificador especial per <b>cèl·lules buides.</b>
        static const int ID_BUIDA = 0;
        /// @brief Representació de les cèl·lules passives
        static const int PASSIVA = -1;
        /// @brief Representació de les cèl·lules actives
        static const int ACTIVA = 1;
};

#endif
