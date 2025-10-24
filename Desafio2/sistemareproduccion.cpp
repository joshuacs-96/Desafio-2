#include "SistemaReproduccion.h"
#include "Cancion.h"
#include "Usuario.h"
#include "Anuncio.h"
#include <cstring>
static Cancion** ensureCapH(Cancion** arr,int& cap,int need){
    if(need<=cap) return arr; int nueva=(cap>0)?cap*2:8; if(nueva<need) nueva=need;
    Cancion** v=new Cancion*[nueva]; for(int i=0;i<cap;++i) v[i]=arr?arr[i]:0; for(int i=cap;i<nueva;++i) v[i]=0;
    delete[] arr; cap=nueva; return v; }
Cancion** SistemaReproduccion::ensureCapHist(Cancion** arr,int& cap,int need){ return ensureCapH(arr,cap,need); }
void SistemaReproduccion::pushHistorial(Cancion* c){
    if(!c) return;
    if(maxHistorial>0 && lenHistorial>=maxHistorial){ for(int i=1;i<lenHistorial;++i) historialTracks[i-1]=historialTracks[i]; --lenHistorial; }
    historialTracks = ensureCapHist(historialTracks,capHistorial,lenHistorial+1);
    historialTracks[lenHistorial++]=c;
}
int SistemaReproduccion::findIndex(Cancion** canciones,int total) const{
    if(!canciones||total<=0||!trackActual) return -1; for(int i=0;i<total;++i) if(canciones[i]==trackActual) return i; return -1; }
const char* SistemaReproduccion::calidadPorPlan() const{ return (sesionUsuario && sesionUsuario->Premium())? "320":"128"; }
SistemaReproduccion::SistemaReproduccion():trackActual(0),historialTracks(0),sesionUsuario(0),modoRepetir(false),conteo(0),
    lenHistorial(0),capHistorial(0),maxHistorial(1000),estadoPausado(false),estadoDetenido(true),cachedLista(0),cachedTotal(0),cachedIndex(-1){}
SistemaReproduccion::~SistemaReproduccion(){ delete[] historialTracks; historialTracks=0; }
void SistemaReproduccion::setMaxHistorial(int m){ maxHistorial=(m<=0?1000:m); }
void SistemaReproduccion::setcancionActual(Cancion* c){ trackActual=c; cachedIndex=-1; }
Cancion* SistemaReproduccion::getcancionActual()const{ return trackActual; }
void SistemaReproduccion::setUsuarioActivo(Usuario* u){ sesionUsuario=u; } Usuario* SistemaReproduccion::getUsuarioActivo()const{ return sesionUsuario; }
void SistemaReproduccion::setEstaRepitiendo(bool r){ modoRepetir=r; } bool SistemaReproduccion::getEstaRepitiendo()const{ return modoRepetir; }
int SistemaReproduccion::getConteoReproducciones()const{ return conteo; }
int SistemaReproduccion::getLenHistorial()const{ return lenHistorial; } Cancion** SistemaReproduccion::getHistorial()const{ return historialTracks; }
void SistemaReproduccion::reproducir(Cancion* c){ if(!c) return; trackActual=c; estadoDetenido=false; estadoPausado=false; c->reproducir(calidadPorPlan()); pushHistorial(c); ++conteo; }
void SistemaReproduccion::pausar(){ if(!estadoDetenido && trackActual) estadoPausado=true; }
void SistemaReproduccion::detener(){ estadoDetenido=true; estadoPausado=false; }
Cancion* SistemaReproduccion::siguiente(Cancion** canciones,int total){
    if(!canciones||total<=0) return 0; if(modoRepetir && trackActual){ pushHistorial(trackActual); ++conteo; trackActual->reproducir(calidadPorPlan()); return trackActual; }
    if(cachedLista!=canciones || cachedTotal!=total){ cachedLista=canciones; cachedTotal=total; cachedIndex=findIndex(canciones,total); }
    if(cachedIndex<0) cachedIndex=0; else cachedIndex=(cachedIndex+1)%total; Cancion* c=canciones[cachedIndex]; if(c) reproducir(c); return c; }
Cancion* SistemaReproduccion::anterior(){ if(lenHistorial<2) return 0; Cancion* prev=historialTracks[lenHistorial-2]; historialTracks[--lenHistorial]=0; trackActual=prev; estadoDetenido=false; estadoPausado=false; if(cachedLista && cachedTotal>0) cachedIndex=findIndex(cachedLista,cachedTotal); return trackActual; }
bool SistemaReproduccion::puedeRetroceder()const{ return lenHistorial>=2; }
void SistemaReproduccion::agregarAlHistoriar(Cancion* c){ pushHistorial(c); }
Anuncio* SistemaReproduccion::mostrarPublicidad(Anuncio** anuncios,int total){ if(!anuncios||total<=0) return 0; if(sesionUsuario && sesionUsuario->Premium()) return 0; for(int i=0;i<total;++i) if(anuncios[i]) return anuncios[i]; return 0; }
void SistemaReproduccion::mostrarInterfaz(){}
