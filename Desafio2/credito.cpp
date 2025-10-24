#include "Credito.h"
char* Credito::clonar(const char* s){ if(!s) return 0; size_t n=std::strlen(s); char* p=new char[n+1]; std::strcpy(p,s); return p; }
void Credito::reasignar(char*& d,const char* s){ delete[] d; d=clonar(s); }
Credito::Credito():nombres(0),apellidos(0),rol(0),codSociedad(0){ setNombre(""); setApellido(""); setTipo(""); setCodigoAfiliacion(""); }
Credito::Credito(const char* n,const char* a,const char* t,const char* c):nombres(0),apellidos(0),rol(0),codSociedad(0){
    setNombre(n); setApellido(a); setTipo(t); setCodigoAfiliacion(c); }
Credito::Credito(const Credito& o):nombres(clonar(o.nombres)),apellidos(clonar(o.apellidos)),rol(clonar(o.rol)),codSociedad(clonar(o.codSociedad)) {}
Credito& Credito::operator=(const Credito& o){ if(this!=&o){ reasignar(nombres,o.nombres); reasignar(apellidos,o.apellidos); reasignar(rol,o.rol); reasignar(codSociedad,o.codSociedad);} return *this; }
Credito::~Credito(){ delete[] nombres; delete[] apellidos; delete[] rol; delete[] codSociedad; nombres=apellidos=rol=codSociedad=0; }
void        Credito::setNombre(const char* n){ reasignar(nombres,n);} const char* Credito::getNombre()const{ return nombres?nombres:""; }
void        Credito::setApellido(const char* a){ reasignar(apellidos,a);} const char* Credito::getApellido()const{ return apellidos?apellidos:""; }
void        Credito::setTipo(const char* t){ reasignar(rol,t);} const char* Credito::getTipo()const{ return rol?rol:""; }
void        Credito::setCodigoAfiliacion(const char* c){ reasignar(codSociedad,c);} const char* Credito::getCodigoAfiliacion()const{ return codSociedad?codSociedad:""; }
void Credito::mostrarCredito(){ /* stub */ }
