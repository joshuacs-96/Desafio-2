#pragma once
#include <cstddef>

class Anuncio {
private:
    char* mensaje;   // texto del anuncio
    char* nivel;     // "AAA", "B", "C"
    int   peso;      // prioridad calculada
    bool  flagUltimo;

    // helpers de manejo de cadenas
    static char* clonar(const char* s);
    static void  reasignar(char*& dst, const char* src);
    static bool  eqCI(const char* a, const char* b); // case-insensitive

public:
    Anuncio();
    Anuncio(const char* texto, const char* categoria);
    Anuncio(const Anuncio& o);
    Anuncio& operator=(const Anuncio& o);
    ~Anuncio();

    void        setTexto(const char* t);
    const char* getTexto() const;

    void        setCategoria(const char* c);
    const char* getCategoria() const;

    void        setPrioridad(int p);
    int         getPrioridad() const;

    void        setUltimoMostrado(bool u);
    bool        getUltimoMostrado() const;

    int         calcularPrioridad(); // actualiza 'peso' según 'nivel'
    void        mostrarAnuncio();
};
