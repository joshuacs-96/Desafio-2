#ifndef CREDITO_H
#define CREDITO_H
#include <cstddef>
#include <cstring>
class Credito {
private:
    char* nombres;
    char* apellidos;
    char* rol;
    char* codSociedad;
    static char* clonar(const char* s);
    static void  reasignar(char*& dst, const char* src);
public:
    Credito();
    Credito(const char* nombre, const char* apellido, const char* tipo, const char* codigo);
    Credito(const Credito& o);
    Credito& operator=(const Credito& o);
    ~Credito();
    void        setNombre(const char* nombre);
    const char* getNombre() const;
    void        setApellido(const char* apellido);
    const char* getApellido() const;
    void        setTipo(const char* tipo);
    const char* getTipo() const;
    void        setCodigoAfiliacion(const char* codigo);
    const char* getCodigoAfiliacion() const;
    void mostrarCredito();
};
#endif
