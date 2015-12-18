/** @file Sistema.cpp
    @brief Implementación de la clase Sistema de la Práctica de PRO2 <em>Reproducción en el Laboratorio</em>.
*/

#include "Sistema.hpp"
#include <vector>

/****** OPERACIONES PÚBLICAS ******/

// Constructoras

Sistema::Sistema(int pobmax) {
    vorg = vector<Organismo>(pobmax); // Asignamos tamaño al vector de organismos
    // Construimos la matriz triangular
    emparejados = Mbool(pobmax - 2); // Es -2 porque sabemos del cierto que los dos últimos organismos del sistema nunca van a poder escoger a nadie.
    // El penúltimo no podrá porqué cuando nazca el último automáticamente acabará el experimento y no tendrá opción
    // de escojerlo, y el último porque no tiene organismos con identificador más grande que el suyo (todo esto es
    // causa de que un organismo sólo puede escoger a uno de identificador mayor)
    for (int i = 0; i < pobmax - 2; ++i) emparejados[i] = Vbool(pobmax - i - 1, false);
    pob = nmuertos = nhijos_ur = 0;
}

// Destructoras

Sistema::~Sistema() {}

int Sistema::consul_pob() const {
    return pob;
}

int Sistema::consul_pob_max() const {
    return vorg.size();
}

bool Sistema::esta_vivo_org(int id) const {
    return id >= 1 and id <= pob and not vorg[id - 1].esta_muerto();
}

bool Sistema::es_estirable_org(int id) const {
    return id >= 1 and id <= pob and not vorg[id - 1].esta_recortado();
}

bool Sistema::esta_lleno() const {
    return pob == vorg.size();
}

bool Sistema::existe_org(int id) const {
    return id >= 1 and id <= pob;
}

int Sistema::consul_nvivos() const {
    return pob - nmuertos;
}

int Sistema::consul_hijos_repr() const {
    return nhijos_ur;
}

void Sistema::escribir_org(int id) {
    cout << id << " :";
    vorg[id - 1].escribir_organismo();
}

// Modificadoras

void Sistema::leer_pob_ini(int pobini) {
    for (int i = 0; i < pobini; ++i) vorg[i].leer_organismo();
    pob = pobini;
}

void Sistema::recortar_org(int id) {
    vorg[id - 1].aplicar_recorte();
    // Comprobamos si ha muerto por el recorte y en caso afirmativo incrementamos el número de muertos
    if (vorg[id - 1].esta_muerto()) ++nmuertos;
}

void Sistema::estirar_org(int id) {
    vorg[id - 1].aplicar_estiron();
}

void Sistema::aplicar_ronda_reproduccion(Ranking&rank) {
    int pobaux = pob;
    // Vector de booleanos auxiliar para guardar los organismos que ya se han emparejado en la ronda
    Vbool agafat(pobaux, false);
    int i = 0;
    nhijos_ur = 0;
    // Es -1 porque sabemos del cierto que el último organismo no podrá escoger a nadie
    while (i < pobaux - 1 and pob < vorg.size()) {
        if (not agafat[i] and not vorg[i].esta_muerto()) { // Lo tratamos sólo si no se ha emparejado aún en la ronda
            int j = i + 1; // Empezamos a buscar desde el siguiente identificador
            while (j < pobaux and (emparejados[i][j - i - 1] or agafat[j] or vorg[j].esta_muerto())) ++j; // Buscamos la pareja
            if (j < pobaux) { // Si se ha encontrado, emparejamos
                agafat[i] = agafat[j] = emparejados[i][j - i - 1] = true;
                bool compatibles;
                vorg[i].reproducir_pareja(vorg[j], vorg[pob], compatibles);
                if (compatibles) { // compatibles nos indica si se ha creado el hijo
                    rank.anadir_pareja(i, j, pob); // pob es el id del hijo
                    ++pob;
                    ++nhijos_ur;
                }
            }
        }
        ++i;
    }
}
