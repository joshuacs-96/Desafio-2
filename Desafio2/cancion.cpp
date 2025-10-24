#include "Cancion.h"
#include "Credito.h"
char* Cancion::clonar(const char* s){ if(!s) return 0; size_t n=std::strlen(s); char* p=new char[n+1]; std::strcpy(p,s); return p; }
void  Cancion::reasignar(char*& d,const char* s){ delete[] d; d=clonar(s); }
Credito** Cancion::ensureCap(Credito** arr,int& cap,int need){
    if(need<=cap) return arr; int nueva=(cap>0)?cap*2:4; if(nueva<need) nueva=need;
    Credito** v=new Credito*[nueva]; for(int i=0;i<cap;++i) v[i]=arr?arr[i]:0; for(int i=cap;i<nueva;++i) v[i]=0;
    delete[] arr; cap=nueva; return v; }
bool Cancion::contieneCreditoPtr(Credito* c) const{ for(int i=0;i<lenCreditos;++i) if(autorias[i]==c) return true; return false; }
int  Cancion::contarDigitos(int x){ if(x==0) return 1; if(x<0) x=-x; int cnt=0; while(x>0){x/=10; ++cnt;} return cnt; }
Cancion::Cancion():codCancion(0),titulo(0),minutos(0.0f),path128(0),path320(0),plays(0),autorias(0),lenCreditos(0),capCreditos(0){
    setNombre(""); setRuta128(""); setRuta320(""); }
Cancion::Cancion(int id,const char* n,float d,const char* r128,const char* r320):Cancion(){
    setIdCancion(id); setNombre(n); setDuracion(d); setRuta128(r128); setRuta320(r320); }
Cancion::Cancion(const Cancion& o):codCancion(o.codCancion),titulo(clonar(o.titulo)),minutos(o.minutos),
    path128(clonar(o.path128)),path320(clonar(o.path320)),plays(o.plays),autorias(0),lenCreditos(o.lenCreditos),capCreditos(o.capCreditos){
    autorias=(capCreditos>0)? new Credito*[capCreditos]:0; for(int i=0;i<capCreditos;++i) autorias[i]=(i<o.lenCreditos? o.autorias[i]:0); }
Cancion& Cancion::operator=(const Cancion& o){
    if(this!=&o){ reasignar(titulo,o.titulo); reasignar(path128,o.path128); reasignar(path320,o.path320);
        codCancion=o.codCancion; minutos=o.minutos; plays=o.plays; delete[] autorias; autorias=0;
        lenCreditos=o.lenCreditos; capCreditos=o.capCreditos; autorias=(capCreditos>0)? new Credito*[capCreditos]:0;
        for(int i=0;i<capCreditos;++i) autorias[i]=(i<o.lenCreditos? o.autorias[i]:0); }
    return *this; }
Cancion::~Cancion(){ delete[] titulo; delete[] path128; delete[] path320; delete[] autorias; titulo=path128=path320=0; autorias=0; lenCreditos=capCreditos=0; }
void        Cancion::setIdCancion(int id){ codCancion=id; } int Cancion::getIdCancion()const{ return codCancion; }
void        Cancion::setNombre(const char* n){ reasignar(titulo,n);} const char* Cancion::getNombre()const{ return titulo?titulo:""; }
void        Cancion::setDuracion(float d){ minutos=(d<0.0f?0.0f:d);} float Cancion::getDuracion()const{ return minutos; }
void        Cancion::setRuta128(const char* r){ reasignar(path128,r);} const char* Cancion::getRuta128()const{ return path128?path128:""; }
void        Cancion::setRuta320(const char* r){ reasignar(path320,r);} const char* Cancion::getRuta320()const{ return path320?path320:""; }
void        Cancion::setReproducciones(int r){ plays=(r<0?0:r);} int Cancion::getReproducciones()const{ return plays; }
void Cancion::setCreditos(Credito** c,int cant,int cap){
    delete[] autorias; autorias=0; lenCreditos=0; capCreditos=0; if(cap<cant) cap=cant; if(cap<0) cap=0;
    if(cap>0){ autorias=new Credito*[cap]; for(int i=0;i<cap;++i) autorias[i]=0; for(int i=0;i<cant;++i) autorias[i]=c[i]; }
    lenCreditos=cant; capCreditos=cap; }
Credito** Cancion::getCreditos()const{ return autorias; } int Cancion::getLenCreditos()const{ return lenCreditos; } int Cancion::getCapCreditos()const{ return capCreditos; }
bool Cancion::validarID()const{ return contarDigitos(codCancion)==9; }
void Cancion::reproducir(const char* /*calidad*/){ ++plays; } void Cancion::mostrarRutas(){} void Cancion::incrementarReproduccion(){ ++plays; }
void Cancion::agregarCredito(Credito* c){ if(!c) return; if(contieneCreditoPtr(c)) return; autorias=ensureCap(autorias,capCreditos,lenCreditos+1); autorias[lenCreditos++]=c; }
