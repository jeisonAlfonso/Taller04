#ifndef GRAFO_CITACIONES_H
#define GRAFO_CITACIONES_H

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

/**
 * TAD GrafoCitaciones: grafo dirigido donde cada vértice es un artículo
 * y cada arista representa una citación desde origen a destino.
 */
class GrafoCitaciones {
public:
    using Articulo = string;

    // Constructor: crea grafo vacío
    GrafoCitaciones();

    // Añade un artículo al grafo (si no existía)
    void agregarArticulo(const Articulo& articulo);

    // Añade una arista dirigida (cita) de origen a destino
    void agregarCita(const Articulo& origen, const Articulo& destino);

    // Elimina un artículo y todas sus conexiones
    void eliminarArticulo(const Articulo& articulo);

    // Devuelve la lista de todos los artículos (vértices)
    vector<Articulo> obtenerArticulos() const;

    // Devuelve la lista de citas directas (adyacentes) de un artículo
    vector<Articulo> obtenerCitasDirectas(const Articulo& articulo) const;

    // Algoritmos solicitados:
    Articulo articuloMasCitado() const;
    int contarGruposSinArticulo(const Articulo& articulo) const;
    double indiceReferenciacion(const Articulo& articulo) const;
    int contarCitacionesIndirectas(const Articulo& articulo) const;

private:
    // Representación: mapa de adyacencia (salientes) y mapa inverso (entrantes)
    unordered_map<Articulo, vector<Articulo>> adj;
    unordered_map<Articulo, vector<Articulo>> invAdj;

    // DFS auxiliar para contar componentes conectados
    void dfsConexo(const Articulo& v, unordered_set<Articulo>& visitados) const;
};

#endif // GRAFO_CITACIONES_H
