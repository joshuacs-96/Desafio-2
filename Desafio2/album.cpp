#include "Album.h"
#include "Cancion.h"
char* Album::clonar(const char* s){ if(!s) return 0; size_t n=std::strlen(s); char* p=new char[n+1]; std::strcpy(p,s); return p; }
void  Album::reasignar(char*& d,const char* s){ delete[] d; d=clonar(s); }
Cancion** Album::ensureCap(Cancion** arr,int& cap,int need){
    if(need<=cap) return arr; int nueva=(cap>0)?cap*2:4; if(nueva<need) nueva=need;
    Cancion** v=new Cancion*[nueva]; for(int i=0;i<cap;++i) v[i]=arr?arr[i]:0; for(int i=cap;i<nueva;++i) v[i]=0;
    delete[] arr; cap=nueva; return v; }
bool Album::contienePistaPtr(Cancion* c)const{ for(int i=0;i<lenPistas;++i) if(pistas[i]==c) return true; return false; }
int  Album::indexGenero(const char* g)const{ if(!g) return -1; for(int i=0;i<lenGeneros;++i){ if(generos[i] && std::strcmp(generos[i],g)==0) return i; } return -1; }
void Album::limpiarGeneros(){ for(int i=0;i<lenGeneros;++i){ delete[] generos[i]; generos[i]=0; } lenGeneros=0; }
Album::Album():codAlbum(0),titulo(0),sello(0),fechaPub(0),minsTotales(0.0f),rutaPortada(0),lenGeneros(0),score(0.0f),
    pistas(0),lenPistas(0),capPistas(0){ for(int i=0;i<MAX_GENEROS;++i) generos[i]=0; setNombre(""); setSelloDisquero(""); setFechaLanzamiento(""); setPortadaRuta(""); }
Album::Album(int id,const char* n,const char* s,const char* f,const char* r):Album(){ setIdAlbum(id); setNombre(n); setSelloDisquero(s); setFechaLanzamiento(f); setPortadaRuta(r); }
Album::Album(const Album& o):codAlbum(o.codAlbum),titulo(clonar(o.titulo)),sello(clonar(o.sello)),fechaPub(clonar(o.fechaPub)),
    minsTotales(o.minsTotales),rutaPortada(clonar(o.rutaPortada)),lenGeneros(o.lenGeneros),score(o.score),
    pistas(0),lenPistas(o.lenPistas),capPistas(o.capPistas){
    for(int i=0;i<MAX_GENEROS;++i) generos[i]=0; for(int i=0;i<lenGeneros && i<MAX_GENEROS;++i) generos[i]=clonar(o.generos[i]);
    pistas=(capPistas>0)? new Cancion*[capPistas]:0; for(int i=0;i<capPistas;++i) pistas[i]=(i<o.lenPistas? o.pistas[i]:0); }
Album& Album::operator=(const Album& o){
    if(this!=&o){ reasignar(titulo,o.titulo); reasignar(sello,o.sello); reasignar(fechaPub,o.fechaPub); reasignar(rutaPortada,o.rutaPortada);
        codAlbum=o.codAlbum; minsTotales=o.minsTotales; score=o.score; limpiarGeneros(); lenGeneros=o.lenGeneros;
        for(int i=0;i<lenGeneros && i<MAX_GENEROS;++i) generos[i]=clonar(o.generos[i]);
        delete[] pistas; pistas=0; lenPistas=o.lenPistas; capPistas=o.capPistas; pistas=(capPistas>0)? new Cancion*[capPistas]:0;
        for(int i=0;i<capPistas;++i) pistas[i]=(i<o.lenPistas? o.pistas[i]:0); }
    return *this; }
Album::~Album(){ delete[] titulo; delete[] sello; delete[] fechaPub; delete[] rutaPortada; limpiarGeneros(); delete[] pistas; pistas=0; lenPistas=capPistas=0; }
void        Album::setIdAlbum(int id){ codAlbum=id; } int Album::getIdAlbum()const{ return codAlbum; }
void        Album::setNombre(const char* n){ reasignar(titulo,n);} const char* Album::getNombre()const{ return titulo?titulo:""; }
void        Album::setSelloDisquero(const char* s){ reasignar(sello,s);} const char* Album::getSelloDisquero()const{ return sello?sello:""; }
void        Album::setFechaLanzamiento(const char* f){ reasignar(fechaPub,f);} const char* Album::getFechaLanzamiento()const{ return fechaPub?fechaPub:""; }
void        Album::setDuracionTotal(float d){ minsTotales=(d<0.0f?0.0f:d);} float Album::getDuracionTotal()const{ return minsTotales; }
void        Album::setPortadaRuta(const char* r){ reasignar(rutaPortada,r);} const char* Album::getPortadaRuta()const{ return rutaPortada?rutaPortada:""; }
void        Album::setPuntuacion(float puntu){ score=puntu;} float Album::getPuntuacion()const{ return score; }
void Album::setGenero(const char* g){ limpiarGeneros(); if(g && *g){ generos[0]=clonar(g); lenGeneros=1; } }
const char* Album::getGenero()const{ return (lenGeneros>0 && generos[0])?generos[0]:""; }
void Album::agregarGenero(const char* g){ if(!g||!*g) return; if(lenGeneros>=MAX_GENEROS) return; if(indexGenero(g)>=0) return; generos[lenGeneros++]=clonar(g); }
char** Album::getGeneros(){ return generos; } const char* Album::getGeneroAt(int i)const{ return (i>=0 && i<lenGeneros && generos[i])?generos[i]:""; }
int Album::getLenGeneros()const{ return lenGeneros; }
void Album::setCanciones(Cancion** c,int cant,int cap){ delete[] pistas; pistas=0; lenPistas=0; capPistas=0; if(cap<cant) cap=cant; if(cap<0) cap=0;
    if(cap>0){ pistas=new Cancion*[cap]; for(int i=0;i<cap;++i) pistas[i]=0; for(int i=0;i<cant;++i) pistas[i]=c[i]; } lenPistas=cant; capPistas=cap; }
Cancion** Album::getCanciones()const{ return pistas; } int Album::getLenPistas()const{ return lenPistas; } int Album::getCapPistas()const{ return capPistas; }
void Album::agregarCancion(Cancion* c){ if(!c) return; if(contienePistaPtr(c)) return; pistas=ensureCap(pistas,capPistas,lenPistas+1); pistas[lenPistas++]=c; }
void Album::calcularDuracion(){ float t=0.0f; for(int i=0;i<lenPistas;++i) if(pistas[i]) t+=pistas[i]->getDuracion(); minsTotales=(t<0.0f?0.0f:t); }
void Album::mostrarPortada(){}
