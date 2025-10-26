#ifndef ARTISTA_H
#define ARTISTA_H
#include <cstddef>
#include <cstring>
class Album;
class Artista {
private:
    int   codArtista;
    char* nomArtista;
    int   anios;
    char* paisNac;
    int   numFans;
    int   rankingGlobal;
    Album** vecAlbums;
    int lenAlbums;
    int capAlbums;
    static char*  clonar(const char* s);
    static void   reasignar(char*& dst, const char* src);
    static Album** ensureCap(Album** arr, int& cap, int need);
    bool  contieneAlbumPtr(Album* a) const;
public:
    Artista();
    Artista(int id, const char* nombre, int edad, const char* pais, int seguidor, int posicion);
    Artista(const Artista& o);
    Artista& operator=(const Artista& o);
    ~Artista();
    void        setIdArtista(int id);
    int         getIdArtista() const;
    void        setNombre(const char* nombre);
    const char* getNombre() const;
    void        setEdad(int edad);
    int         getEdad() const;
    void        setPaisOrigen(const char* p);
    const char* getPaisOrigen() const;
    void        setSeguidores(int seguidores);
    int         getSeguidores() const;
    void        setPosicionGlobal(int pos);
    int         getPosicionGlobal() const;
    void     setAlbumes(Album** albums, int cantidad, int capacidad);
    Album**  getAlbumes() const;
    int      getLenAlbums() const;
    int      getCapAlbums() const;
    void     agregarAlbum(Album* album);
    void mostrarInformacion();
};
#endif
