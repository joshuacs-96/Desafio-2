#ifndef SISTEMA_REPRODUCCION_H
#define SISTEMA_REPRODUCCION_H
class Cancion;
class Usuario;
class Anuncio;
class SistemaReproduccion {
private:
    Cancion*  trackActual;
    Cancion** historialTracks;
    Usuario*  sesionUsuario;
    bool  modoRepetir;
    int   conteo;
    int   lenHistorial;
    int   capHistorial;
    int   maxHistorial;
    bool  estadoPausado;
    bool  estadoDetenido;
    Cancion** cachedLista;
    int       cachedTotal;
    int       cachedIndex;
    static Cancion** ensureCapHist(Cancion** arr,int& cap,int need);
    void pushHistorial(Cancion* c);
    int findIndex(Cancion** canciones,int total) const;
    const char* calidadPorPlan() const;
public:
    SistemaReproduccion();
    ~SistemaReproduccion();
    void setMaxHistorial(int m);
    void setcancionActual(Cancion* c);
    Cancion* getcancionActual() const;
    void setUsuarioActivo(Usuario* u);
    Usuario* getUsuarioActivo() const;
    void setEstaRepitiendo(bool r);
    bool getEstaRepitiendo() const;
    int getConteoReproducciones() const;
    int getLenHistorial() const;
    Cancion** getHistorial() const;
    void reproducir(Cancion* c);
    void pausar();
    void detener();
    Cancion* siguiente(Cancion** canciones,int total);
    Cancion* anterior();
    bool puedeRetroceder() const;
    void agregarAlHistoriar(Cancion* c);
    Anuncio* mostrarPublicidad(Anuncio** anuncios,int total);
    void mostrarInterfaz();
};
#endif
