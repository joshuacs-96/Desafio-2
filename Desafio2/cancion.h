#ifndef CANCION_H
#define CANCION_H
#include <cstddef>
#include <cstring>
class Credito;
class Cancion {
private:
    int    codCancion;
    char*  titulo;
    float  minutos;
    char*  path128;
    char*  path320;
    int    plays;
    Credito** autorias;
    int       lenCreditos;
    int       capCreditos;
    static char* clonar(const char* s);
    static void  reasignar(char*& dst, const char* src);
    static Credito** ensureCap(Credito** arr, int& cap, int need);
    bool contieneCreditoPtr(Credito* c) const;
    static int contarDigitos(int x);
public:
    Cancion();
    Cancion(int id, const char* nombre, float duracion, const char* r128, const char* r320);
    Cancion(const Cancion& o);
    Cancion& operator=(const Cancion& o);
    ~Cancion();
    void        setIdCancion(int id);
    int         getIdCancion() const;
    void        setNombre(const char* nombre);
    const char* getNombre() const;
    void        setDuracion(float dur);
    float       getDuracion() const;
    void        setRuta128(const char* r);
    const char* getRuta128() const;
    void        setRuta320(const char* r);
    const char* getRuta320() const;
    void        setReproducciones(int r);
    int         getReproducciones() const;
    void setCreditos(Credito** creditos, int cantidad, int capacidad);
    Credito**   getCreditos() const;
    int         getLenCreditos() const;
    int         getCapCreditos() const;
    bool validarID() const;
    void reproducir(const char* calidad);
    void mostrarRutas();
    void incrementarReproduccion();
    void agregarCredito(Credito* c);
};
#endif
