#include "Anuncio.h"
Anuncio::Anuncio():mensaje(0),nivel(0),peso(1),flagUltimo(false){ setTexto(""); setCategoria("C"); }
Anuncio::Anuncio(const char* t,const char* c):mensaje(0),nivel(0),peso(1),flagUltimo(false){ setTexto(t); setCategoria(c); }
Anuncio::Anuncio(const Anuncio& o):mensaje(clonar(o.mensaje)),nivel(clonar(o.nivel)),peso(o.peso),flagUltimo(o.flagUltimo){}
Anuncio& Anuncio::operator=(const Anuncio& o){ if(this!=&o){ reasignar(mensaje,o.mensaje); reasignar(nivel,o.nivel); peso=o.peso; flagUltimo=o.flagUltimo; } return *this; }
Anuncio::~Anuncio(){ delete[] mensaje; delete[] nivel; mensaje=nivel=0; }
void        Anuncio::setTexto(const char* t){ reasignar(mensaje,t);} const char* Anuncio::getTexto()const{ return mensaje?mensaje:""; }
void        Anuncio::setCategoria(const char* c){ reasignar(nivel,c); calcularPrioridad(); } const char* Anuncio::getCategoria()const{ return nivel?nivel:""; }
void        Anuncio::setPrioridad(int p){ peso=(p<0?0:p);} int Anuncio::getPrioridad()const{ return peso; }
void        Anuncio::setUltimoMostrado(bool u){ flagUltimo=u;} bool Anuncio::getUltimoMostrado()const{ return flagUltimo; }
int Anuncio::calcularPrioridad(){ if(nivel){ if(eqCI(nivel,"AAA")) peso=3; else if(eqCI(nivel,"B")) peso=2; else peso=1; } else peso=1; return peso; }
void Anuncio::mostrarAnuncio(){}
