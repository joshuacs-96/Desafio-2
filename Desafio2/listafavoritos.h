
#pragma once
// ----------- no incluyas Usuario.h ni Cancion.h aquí -----------
class Usuario;            // forward declarations
class Cancion;
class SistemaReproduccion;
// ---------------------------------------------------------------

class ListaFavoritos {
private:
    Usuario* propietario;
    Cancion** items;
    int len;
    int cap;

    static Cancion** ensureCap(Cancion** arr, int& cap, int need);
    bool contiene(Cancion* c) const;

public:
    explicit ListaFavoritos(Usuario* u = nullptr);
    ~ListaFavoritos();

    void setPropietario(Usuario* u);
    Usuario* getPropietario() const;

    void agregarCancion(Cancion* c);
    int  getLen() const;
    Cancion** getVector() const;

    void reproducirLista(bool aleatorio, SistemaReproduccion* player);
};
