#include "ListaFavoritos.h"
#include "Usuario.h"
#include "Cancion.h"
#include "SistemaReproduccion.h"

static Cancion** ensureCapImpl(Cancion** arr, int& cap, int need) {
    if (need <= cap) return arr;
    int nueva = (cap > 0) ? cap * 2 : 4;
    if (nueva < need) nueva = need;
    Cancion** v = new Cancion*[nueva];
    for (int i = 0; i < cap; ++i) v[i] = arr ? arr[i] : nullptr;
    for (int i = cap; i < nueva; ++i) v[i] = nullptr;
    delete[] arr;
    cap = nueva;
    return v;
}

Cancion** ListaFavoritos::ensureCap(Cancion** arr, int& cap, int need) {
    return ensureCapImpl(arr, cap, need);
}

bool ListaFavoritos::contiene(Cancion* c) const {
    for (int i = 0; i < len; ++i)
        if (items[i] == c) return true;
    return false;
}

ListaFavoritos::ListaFavoritos(Usuario* u)
    : propietario(u), items(nullptr), len(0), cap(0) {}

ListaFavoritos::~ListaFavoritos() {
    delete[] items;
    items = nullptr;
    len = cap = 0;
}

void ListaFavoritos::setPropietario(Usuario* u) { propietario = u; }
Usuario* ListaFavoritos::getPropietario() const { return propietario; }

void ListaFavoritos::agregarCancion(Cancion* c) {
    if (!c) return;
    if (contiene(c)) return;
    items = ensureCap(items, cap, len + 1);
    items[len++] = c;
}

int ListaFavoritos::getLen() const { return len; }
Cancion** ListaFavoritos::getVector() const { return items; }

void ListaFavoritos::reproducirLista(bool /*aleatorio*/, SistemaReproduccion* player) {
    if (!player || len <= 0) return;
    for (int i = 0; i < len; ++i)
        if (items[i])
            player->reproducir(items[i]);
}
