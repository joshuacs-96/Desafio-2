#ifndef LISTA_FAVORITOS_H
#define LISTA_FAVORITOS_H
#include <cstddef>
class Usuario;
class Cancion;
class SistemaReproduccion;
class ListaFavoritos {
private:
    Usuario* propietario;
    Cancion** items;
    int len;
    int cap;
    static Cancion** ensureCap(Cancion** arr,int& cap,int need);
    bool contiene(Cancion* c) const;
public:
    ListaFavoritos(Usuario* u=0);
    ~ListaFavoritos();
    void setPropietario(Usuario* u);
    Usuario* getPropietario() const;
    void agregarCancion(Cancion* c);
    int getLen() const;
    Cancion** getVector() const;
    void reproducirLista(bool aleatorio, SistemaReproduccion* player);
};
#endif

