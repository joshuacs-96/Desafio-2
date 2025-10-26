#include "Artista.h"
#include "Album.h"
char* Artista::clonar(const char* s){ if(!s) return 0; size_t n=std::strlen(s); char* p=new char[n+1]; std::strcpy(p,s); return p; }
void  Artista::reasignar(char*& d,const char* s){ delete[] d; d=clonar(s); }
Album** Artista::ensureCap(Album** arr,int& cap,int need){
    if(need<=cap) return arr; int nueva=(cap>0)?cap*2:4; if(nueva<need) nueva=need;
    Album** v=new Album*[nueva]; for(int i=0;i<cap;++i) v[i]=arr?arr[i]:0; for(int i=cap;i<nueva;++i) v[i]=0;
    delete[] arr; cap=nueva; return v; }
bool Artista::contieneAlbumPtr(Album* a)const{ for(int i=0;i<lenAlbums;++i) if(vecAlbums[i]==a) return true; return false; }
Artista::Artista():codArtista(0),nomArtista(0),anios(0),paisNac(0),numFans(0),rankingGlobal(0),vecAlbums(0),lenAlbums(0),capAlbums(0){
    setNombre(""); setPaisOrigen(""); }
Artista::Artista(int id,const char* n,int e,const char* p,int s,int pos):Artista(){
    setIdArtista(id); setNombre(n); setEdad(e); setPaisOrigen(p); setSeguidores(s); setPosicionGlobal(pos); }
Artista::Artista(const Artista& o):codArtista(o.codArtista),nomArtista(clonar(o.nomArtista)),anios(o.anios),
    paisNac(clonar(o.paisNac)),numFans(o.numFans),rankingGlobal(o.rankingGlobal),vecAlbums(0),lenAlbums(o.lenAlbums),capAlbums(o.capAlbums){
    vecAlbums=(capAlbums>0)? new Album*[capAlbums]:0; for(int i=0;i<capAlbums;++i) vecAlbums[i]=(i<o.lenAlbums? o.vecAlbums[i]:0); }
Artista& Artista::operator=(const Artista& o){
    if(this!=&o){ reasignar(nomArtista,o.nomArtista); reasignar(paisNac,o.paisNac);
        codArtista=o.codArtista; anios=o.anios; numFans=o.numFans; rankingGlobal=o.rankingGlobal;
        delete[] vecAlbums; vecAlbums=0; lenAlbums=o.lenAlbums; capAlbums=o.capAlbums;
        vecAlbums=(capAlbums>0)? new Album*[capAlbums]:0; for(int i=0;i<capAlbums;++i) vecAlbums[i]=(i<o.lenAlbums? o.vecAlbums[i]:0); }
    return *this; }
Artista::~Artista(){ delete[] nomArtista; delete[] paisNac; delete[] vecAlbums; nomArtista=paisNac=0; vecAlbums=0; lenAlbums=capAlbums=0; }
void        Artista::setIdArtista(int id){ codArtista=id; } int Artista::getIdArtista()const{ return codArtista; }
void        Artista::setNombre(const char* n){ reasignar(nomArtista,n);} const char* Artista::getNombre()const{ return nomArtista?nomArtista:""; }
void        Artista::setEdad(int e){ anios=(e<0?0:e);} int Artista::getEdad()const{ return anios; }
void        Artista::setPaisOrigen(const char* p){ reasignar(paisNac,p);} const char* Artista::getPaisOrigen()const{ return paisNac?paisNac:""; }
void        Artista::setSeguidores(int s){ numFans=(s<0?0:s);} int Artista::getSeguidores()const{ return numFans; }
void        Artista::setPosicionGlobal(int r){ rankingGlobal=(r<0?0:r);} int Artista::getPosicionGlobal()const{ return rankingGlobal; }
void Artista::setAlbumes(Album** a,int cant,int cap){ delete[] vecAlbums; vecAlbums=0; lenAlbums=0; capAlbums=0; if(cap<cant) cap=cant; if(cap<0) cap=0;
    if(cap>0){ vecAlbums=new Album*[cap]; for(int i=0;i<cap;++i) vecAlbums[i]=0; for(int i=0;i<cant;++i) vecAlbums[i]=a[i]; } lenAlbums=cant; capAlbums=cap; }
Album** Artista::getAlbumes()const{ return vecAlbums; } int Artista::getLenAlbums()const{ return lenAlbums; } int Artista::getCapAlbums()const{ return capAlbums; }
void Artista::agregarAlbum(Album* a){ if(!a) return; if(contieneAlbumPtr(a)) return; vecAlbums=ensureCap(vecAlbums,capAlbums,lenAlbums+1); vecAlbums[lenAlbums++]=a; }
void Artista::mostrarInformacion(){}
