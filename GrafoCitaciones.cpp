#include "GrafoCitaciones.h"
using namespace std;

// Constructor
GrafoCitaciones::GrafoCitaciones() {}

/**
 * Garantiza que un artículo exista en ambas estructuras.
 */
void GrafoCitaciones::agregarArticulo(const Articulo& articulo) {
    if (adj.find(articulo) == adj.end()) {
        adj[articulo] = {};
        invAdj[articulo] = {};
    }
}

void GrafoCitaciones::agregarCita(const Articulo& origen, const Articulo& destino) {
    agregarArticulo(origen);
    agregarArticulo(destino);
    adj[origen].push_back(destino);
    invAdj[destino].push_back(origen);
}

void GrafoCitaciones::eliminarArticulo(const Articulo& articulo) {
    if (adj.find(articulo) == adj.end()) return;
    // Quitar salientes
    for (auto& destino : adj[articulo]) {
        auto& inv = invAdj[destino];
        inv.erase(remove(inv.begin(), inv.end(), articulo), inv.end());
    }
    adj.erase(articulo);
    // Quitar entrantes
    for (auto& p : adj) {
        auto& lista = p.second;
        lista.erase(remove(lista.begin(), lista.end(), articulo), lista.end());
    }
    invAdj.erase(articulo);
}

vector<GrafoCitaciones::Articulo> GrafoCitaciones::obtenerArticulos() const {
    vector<Articulo> res;
    res.reserve(adj.size());
    for (const auto& p : adj) 
        res.push_back(p.first);
    return res;
}

vector<GrafoCitaciones::Articulo>
GrafoCitaciones::obtenerCitasDirectas(const Articulo& articulo) const {
    auto it = adj.find(articulo);
    return (it != adj.end()) ? it->second : vector<Articulo>{};
}

void GrafoCitaciones::dfsConexo(const Articulo& v,
    unordered_set<Articulo>& visitados) const {
    visitados.insert(v);
    // vecinos salientes
    for (const auto& w : adj.at(v))
        if (!visitados.count(w))
            dfsConexo(w, visitados);
    // vecinos entrantes (para grafo no dirigido)
    for (const auto& w : invAdj.at(v))
        if (!visitados.count(w))
            dfsConexo(w, visitados);
}

GrafoCitaciones::Articulo GrafoCitaciones::articuloMasCitado() const {
    size_t maxCount = 0;
    Articulo mejor = "";
    for (const auto& p : invAdj) {
        if (p.second.size() > maxCount) {
            maxCount = p.second.size();
            mejor = p.first;
        }
    }
    return mejor;
}

int GrafoCitaciones::contarGruposSinArticulo(const Articulo& articulo) const {
    GrafoCitaciones copia = *this;
    copia.eliminarArticulo(articulo);
    unordered_set<Articulo> visitados;
    int grupos = 0;
    for (const auto& art : copia.obtenerArticulos()) {
        if (!visitados.count(art)) {
            copia.dfsConexo(art, visitados);
            ++grupos;
        }
    }
    return grupos;
}

double GrafoCitaciones::indiceReferenciacion(const Articulo& articulo) const {
    double salientes = adj.at(articulo).size();
    double entrantes = invAdj.at(articulo).size();
    if (salientes == 0) return 0.0;
    return entrantes / (0.5 * salientes);
}

int GrafoCitaciones::contarCitacionesIndirectas(const Articulo& articulo) const {
    const auto& directas = adj.at(articulo);
    unordered_set<Articulo> setDirectas(directas.begin(), directas.end());
    unordered_set<Articulo> indirectas;
    for (const auto& cita : directas) {
        for (const auto& sec : adj.at(cita)) {
            if (sec != articulo && !setDirectas.count(sec))
                indirectas.insert(sec);
        }
    }
    return indirectas.size();
}
