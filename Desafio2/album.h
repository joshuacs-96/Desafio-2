#ifndef ALBUM_H
#define ALBUM_H
#include <cstddef>
#include <cstring>
class Cancion;
class Album {
private:
    int    codAlbum;
    char*  titulo;
    char*  sello;
    char*  fechaPub;
    float  minsTotales;
    char*  rutaPortada;
    enum { MAX_GENEROS = 4 };
    char*  generos[MAX_GENEROS];
    int    lenGeneros;
    float  score;
    Cancion** pistas;
    int    lenPistas;
    int    capPistas;
    static char*   clonar(const char* s);
    static void    reasignar(char*& dst, const char* src);
    static Cancion** ensureCap(Cancion** arr, int& cap, int need);
    bool           contienePistaPtr(Cancion* c) const;
    int            indexGenero(const char* g) const;
    void           limpiarGeneros();
public:
    Album();
    Album(int id, const char* nombre, const char* sello_, const char* fecha, const char* ruta);
    Album(const Album& o);
    Album& operator=(const Album& o);
    ~Album();
    void        setIdAlbum(int id);
    int         getIdAlbum() const;
    void        setNombre(const char* nombre);
    const char* getNombre() const;
    void        setSelloDisquero(const char* s);
    const char* getSelloDisquero() const;
    void        setFechaLanzamiento(const char* f);
    const char* getFechaLanzamiento() const;
    void        setDuracionTotal(float dur);
    float       getDuracionTotal() const;
    void        setPortadaRuta(const char* r);
    const char* getPortadaRuta() const;
    void        setPuntuacion(float puntu);
    float       getPuntuacion() const;
    void        setGenero(const char* genero);
    const char* getGenero() const;
    void        agregarGenero(const char* genero);
    char**      getGeneros();
    const char* getGeneroAt(int i) const;
    int         getLenGeneros() const;
    void        setCanciones(Cancion** canciones, int cantidad, int capacidad);
    Cancion**   getCanciones() const;
    int         getLenPistas() const;
    int         getCapPistas() const;
    void        agregarCancion(Cancion* c);
    void calcularDuracion();
    void mostrarPortada();
};
#endif
