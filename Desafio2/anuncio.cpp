#include "Anuncio.h"
#include <cstring>
#include <cctype>
#include <new>      // std::nothrow

// ------- helpers privados -------
char* Anuncio::clonar(const char* s) {
    if (!s) return nullptr;
    std::size_t n = std::strlen(s) + 1;
    char* p = new(std::nothrow) char[n];
    if (!p) return nullptr;
    std::memcpy(p, s, n);
    return p;
}

void Anuncio::reasignar(char*& dst, const char* src) {
    if (dst == src) return;
    delete[] dst;
    dst = clonar(src);
}

static inline char toLowerChar(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

bool Anuncio::eqCI(const char* a, const char* b) {
    if (!a || !b) return false;
    while (*a && *b) {
        if (toLowerChar(*a) != toLowerChar(*b)) return false;
        ++a; ++b;
    }
    return *a == *b;
}
// --------------------------------

Anuncio::Anuncio()
    : mensaje(nullptr), nivel(nullptr), peso(1), flagUltimo(false) {
    setTexto("");
    setCategoria("C");
}

Anuncio::Anuncio(const char* t, const char* c)
    : mensaje(nullptr), nivel(nullptr), peso(1), flagUltimo(false) {
    setTexto(t);
    setCategoria(c);
}

Anuncio::Anuncio(const Anuncio& o)
    : mensaje(clonar(o.mensaje)),
    nivel(clonar(o.nivel)),
    peso(o.peso),
    flagUltimo(o.flagUltimo) {}

Anuncio& Anuncio::operator=(const Anuncio& o) {
    if (this != &o) {
        reasignar(mensaje, o.mensaje);
        reasignar(nivel,   o.nivel);
        peso = o.peso;
        flagUltimo = o.flagUltimo;
    }
    return *this;
}

Anuncio::~Anuncio() {
    delete[] mensaje;
    delete[] nivel;
    mensaje = nivel = nullptr;
}

void Anuncio::setTexto(const char* t)          { reasignar(mensaje, t); }
const char* Anuncio::getTexto() const          { return mensaje ? mensaje : ""; }

void Anuncio::setCategoria(const char* c)      { reasignar(nivel, c); calcularPrioridad(); }
const char* Anuncio::getCategoria() const      { return nivel ? nivel : ""; }

void Anuncio::setPrioridad(int p)              { peso = (p < 0 ? 0 : p); }
int  Anuncio::getPrioridad() const             { return peso; }

void Anuncio::setUltimoMostrado(bool u)        { flagUltimo = u; }
bool Anuncio::getUltimoMostrado() const        { return flagUltimo; }

int Anuncio::calcularPrioridad() {
    if (nivel) {
        if (eqCI(nivel, "AAA"))      peso = 3;
        else if (eqCI(nivel, "B"))   peso = 2;
        else                         peso = 1; // C u otro
    } else {
        peso = 1;
    }
    return peso;
}

void Anuncio::mostrarAnuncio() {
    // imprime o dispara evento; de momento vacío
}
