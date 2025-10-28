#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <cstddef>
class Usuario;
class Artista;
class Anuncio;
class Cancion;
class SistemaReproduccion;
class Album;
class MedidorRecursos;
class Plataforma {
private:
    Usuario** usuarios; int numUsuarios, capUsuarios;
    Artista** catalogoArtistas; int numArtistas, capArtistas;
    Anuncio** anuncios; int numAnuncios, capAnuncios;
    SistemaReproduccion* player;
    MedidorRecursos* medidor;
    template <typename T>
    static T** ensureCap(T** arr, int& cap, int need) {
        if (need <= cap) {
            return arr;
        }
        int nueva = (cap > 0) ? cap * 2 : 4;
        if (nueva < need) {
            nueva = need;
        }
        T** v = new T*[nueva];
        for (int i = 0; i < nueva; ++i) {
            v[i] = (i < cap && arr) ? arr[i] : nullptr;
        }
        delete[] arr;
        cap = nueva;
        return v;
    }
public:
    Plataforma();
    ~Plataforma();
    void setSistemaReproduccion(SistemaReproduccion* p);
    void setMedidor(MedidorRecursos* m);
    void agregarUsuario(Usuario* u);
    void agregarArtista(Artista* a);
    void agregarAnuncio(Anuncio* a);
    void reproducirAleatorio();
    Cancion* encontrarCancion(int id);
    Usuario* login(const char* nick, const char* pass);
    Anuncio* elegirAnuncio();
    Artista* encontrarArtista(int id);
    Album* encontrarAlbum(int artista_id, int album_id);
    size_t memoriaAproximada() const;
    int getNumUsuarios() const { return numUsuarios; }
    int getNumArtistas() const { return numArtistas; }
    int getNumAnuncios() const { return numAnuncios; }
};
#endif
