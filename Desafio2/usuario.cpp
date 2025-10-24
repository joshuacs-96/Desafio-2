#include "Usuario.h"
#include "ListaFavoritos.h"
Usuario::Usuario():usuario(0),plan(0),ciudad(0),pais(0),fecha(0),lista(0){ setUsuario(""); setPlan("Free"); setCiudad(""); setPais(""); setFechaAlta(""); }
Usuario::Usuario(const char* u,const char* p,const char* c,const char* pa,const char* f):Usuario(){ setUsuario(u); setPlan(p); setCiudad(c); setPais(pa); setFechaAlta(f); }
Usuario::Usuario(const Usuario& o):usuario(0),plan(0),ciudad(0),pais(0),fecha(0),lista(o.lista){
    setUsuario(o.usuario); setPlan(o.plan); setCiudad(o.ciudad); setPais(o.pais); setFechaAlta(o.fecha); }
Usuario& Usuario::operator=(const Usuario& o){ if(this!=&o){ setUsuario(o.usuario); setPlan(o.plan); setCiudad(o.ciudad); setPais(o.pais); setFechaAlta(o.fecha); lista=o.lista; } return *this; }
Usuario::~Usuario(){ delete[] usuario; delete[] plan; delete[] ciudad; delete[] pais; delete[] fecha; usuario=plan=ciudad=pais=fecha=0; lista=0; }
void Usuario::setUsuario(const char* u){ delete[] usuario; if(!u) u=""; size_t n=std::strlen(u); usuario=new char[n+1]; std::strcpy(usuario,u); }
const char* Usuario::getUsuario()const{ return usuario?usuario:""; }
void Usuario::setPlan(const char* p){ delete[] plan; if(!p) p=""; size_t n=std::strlen(p); plan=new char[n+1]; std::strcpy(plan,p); }
const char* Usuario::getPlan()const{ return plan?plan:""; }
void Usuario::setCiudad(const char* c){ delete[] ciudad; if(!c) c=""; size_t n=std::strlen(c); ciudad=new char[n+1]; std::strcpy(ciudad,c); }
const char* Usuario::getCiudad()const{ return ciudad?ciudad:""; }
void Usuario::setPais(const char* p){ delete[] pais; if(!p) p=""; size_t n=std::strlen(p); pais=new char[n+1]; std::strcpy(pais,p); }
const char* Usuario::getPais()const{ return pais?pais:""; }
void Usuario::setFechaAlta(const char* f){ delete[] fecha; if(!f) f=""; size_t n=std::strlen(f); fecha=new char[n+1]; std::strcpy(fecha,f); }
const char* Usuario::getFechaAlta()const{ return fecha?fecha:""; }
void Usuario::setListaFavoritos(ListaFavoritos* l){ lista=l; } ListaFavoritos* Usuario::getListaFavoritos()const{ return lista; }
bool Usuario::Premium()const{ return eq(plan,"Premium"); }
