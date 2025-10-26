#ifndef PLATAFORMA_H
#define PLATAFORMA_H
class Usuario;
class Artista;
class Anuncio;
class Cancion;
class SistemaReproduccion;
class MedidorRecursos;
class Plataforma {
private:
    Usuario** usuarios; int numUsuarios, capUsuarios;
    Artista** catalogoArtistas; int numArtistas, capArtistas;
    Anuncio** anuncios; int numAnuncios, capAnuncios;
    SistemaReproduccion* player;
    MedidorRecursos* medidor;
    template <typename T> static T** ensureCap(T** arr,int& cap,int need){
        if(need<=cap) return arr; int nueva=(cap>0)?cap*2:4; if(nueva<need) nueva=need;
        T** v=new T*[nueva]; for(int i=0;i<cap;++i) v[i]=arr?arr[i]:0; for(int i=cap;i<nueva;++i) v[i]=0; delete[] arr; cap=nueva; return v; }
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
};
#endif
