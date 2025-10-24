#ifndef MEDIDOR_RECURSOS_H
#define MEDIDOR_RECURSOS_H
#include <cstddef>
#include <cstdint>
class MedidorRecursos {
private:
    int    nIter;
    size_t bytesTotales;
public:
    MedidorRecursos();
    MedidorRecursos(const MedidorRecursos& o);
    MedidorRecursos& operator=(const MedidorRecursos& o);
    ~MedidorRecursos();
    void   setIteraciones(int iteraciones);
    int    getIteraciones() const;
    void   setMemoriaTotal(size_t memoria);
    size_t getMemoriaTotal() const;
    void contarIteracion();
    void agregarMemoria(size_t bytes);
    void calcularMemoriaObjeto(void* /*objeto*/, size_t tamano);
    void calcularMemoriaArregloDePunteros(void** arreglo, int cantidad);
    template <typename T> void calcularMemoriaBloque(const T* /*ptr*/, int cantidad){
        if (cantidad > 0) bytesTotales += (size_t)cantidad * sizeof(T);
    }
    void mostrarMetricas(const char* /*funcionalidad*/);
    void reset();
};
#endif
