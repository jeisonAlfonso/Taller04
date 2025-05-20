#include <iostream>
#include "GrafoCitaciones.h"

using namespace std;

int main() {
    GrafoCitaciones g;

    // —————— Grafo de ejemplo ——————
    // Rellena aquí todas las citas del mapa de ejemplo:
    // g.agregarCita("Artículo Origen", "Artículo Destino");
    // Por ejemplo, de lo que sabemos:
    g.agregarCita("A. F. Kramer, et al.", "K. Yaffe, et al.");
    g.agregarCita("A. F. Kramer, et al.", "R. S. Wilson, et al.");
    g.agregarCita("A. F. Kramer, et al.", "E. B. Larson, et al.");
    g.agregarCita("A. F. Kramer, et al.", "J. L. Trejo, et al.");
    // … (el resto de citas directas de A. F. Kramer)
    g.agregarCita("E. B. Larson, et al.", "J. Weuve, et al.");
    g.agregarCita("E. B. Larson, et al.", "L. J. Podewils, et al>");
    // … (continúa con todos los demás artículos y sus citas)
    // ——————————————————————————————

    // Algoritmo 1: artículo más citado
    cout << "Algoritmo 1 – Más citado: "
         << g.articuloMasCitado()
         << "\n";

    // Algoritmo 2: grupos sin A. F. Kramer
    cout << "Algoritmo 2 – Grupos sin \"A. F. Kramer, et al.\": "
         << g.contarGruposSinArticulo("A. F. Kramer, et al.")
         << "\n";

    // Algoritmo 3: índice de referenciación de E. B. Larson
    cout << "Algoritmo 3 – Índice de referenciación de \"E. B. Larson, et al.\": "
         << g.indiceReferenciacion("E. B. Larson, et al.")
         << "\n";

    // Algoritmo 4: citaciones indirectas desde A. F. Kramer
    cout << "Algoritmo 4 – Citaciones indirectas desde \"A. F. Kramer, et al.\": "
         << g.contarCitacionesIndirectas("A. F. Kramer, et al.")
         << "\n";

    return 0;
}
