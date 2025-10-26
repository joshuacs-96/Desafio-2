#ifndef ANUNCIO_H
#define ANUNCIO_H
#include <cstddef>
#include <cstring>
#include <cctype>
class Anuncio {
private:
    char* mensaje;
    char* nivel;
    int   peso;
    bool  flagUltimo;
    static int toLower(int ch){ return (ch>='A'&&ch<='Z')? ch-'A'+'a' : ch; }
    static bool eqCI(const char* a,const char* b){
        if(!a||!b) return false; while(*a && *b){ if(toLower(*a)!=toLower(*b)) return false; ++a; ++b; } return (*a==0 && *b==0);
    }
    static char* clonar(const char* s){ if(!s) return 0; size_t n=std::strlen(s); char* p=new char[n+1]; std::strcpy(p,s); return p; }
    static void  reasignar(char*& d,const char* s){ delete[] d; d=clonar(s); }
public:
    Anuncio();
    Anuncio(const char* texto, const char* categoria);
    Anuncio(const Anuncio& o);
    Anuncio& operator=(const Anuncio& o);
    ~Anuncio();
    void        setTexto(const char* texto);
    const char* getTexto() const;
    void        setCategoria(const char* categoria);
    const char* getCategoria() const;
    void        setPrioridad(int prioridad);
    int         getPrioridad() const;
    void        setUltimoMostrado(bool ultimo);
    bool        getUltimoMostrado() const;
    int calcularPrioridad();
    void mostrarAnuncio();
};
#endif
