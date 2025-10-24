#ifndef USUARIO_H
#define USUARIO_H
#include <cstddef>
#include <cstring>
class ListaFavoritos;
class Usuario {
private:
    char* usuario;
    char* plan;
    char* ciudad;
    char* pais;
    char* fecha;
    ListaFavoritos* lista;
    static bool eq(const char* a,const char* b){ if(!a||!b) return false; return std::strcmp(a,b)==0; }
public:
    Usuario();
    Usuario(const char* u,const char* p,const char* c,const char* pa,const char* f);
    Usuario(const Usuario& o);
    Usuario& operator=(const Usuario& o);
    ~Usuario();
    void setUsuario(const char* u);
    const char* getUsuario() const;
    void setPlan(const char* p);
    const char* getPlan() const;
    void setCiudad(const char* c);
    const char* getCiudad() const;
    void setPais(const char* p);
    const char* getPais() const;
    void setFechaAlta(const char* f);
    const char* getFechaAlta() const;
    void setListaFavoritos(ListaFavoritos* l);
    ListaFavoritos* getListaFavoritos() const;
    bool Premium() const;
};
#endif
