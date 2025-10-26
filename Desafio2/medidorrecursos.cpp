#include "MedidorRecursos.h"
#include <cstdio>   // opcional para printf (mostrarMetricas)

MedidorRecursos::MedidorRecursos()
    : nIter(0), bytesTotales(0) {}

MedidorRecursos::MedidorRecursos(const MedidorRecursos& o)
    : nIter(o.nIter), bytesTotales(o.bytesTotales) {}

MedidorRecursos& MedidorRecursos::operator=(const MedidorRecursos& o) {
    if (this != &o) {
        nIter = o.nIter;
        bytesTotales = o.bytesTotales;
    }
    return *this;
}

MedidorRecursos::~MedidorRecursos() { }

void MedidorRecursos::setIteraciones(int iteraciones) { nIter = iteraciones; }
int  MedidorRecursos::getIteraciones() const { return nIter; }

void MedidorRecursos::setMemoriaTotal(size_t memoria) { bytesTotales = memoria; }
size_t MedidorRecursos::getMemoriaTotal() const { return bytesTotales; }

void MedidorRecursos::contarIteracion() { ++nIter; }
void MedidorRecursos::agregarMemoria(size_t bytes) { bytesTotales += bytes; }

void MedidorRecursos::calcularMemoriaObjeto(void* /*objeto*/, size_t tamano) {
    bytesTotales += tamano;
}

void MedidorRecursos::calcularMemoriaArregloDePunteros(void** /*arreglo*/, int cantidad) {
    if (cantidad > 0) bytesTotales += static_cast<size_t>(cantidad) * sizeof(void*);
}

void MedidorRecursos::mostrarMetricas(const char* /*funcionalidad*/) {
    // Opcional: imprime algo para depurar
    // std::printf("Iteraciones=%d, Memoria=%zu bytes\n", nIter, bytesTotales);
}

void MedidorRecursos::reset() {
    nIter = 0;
    bytesTotales = 0;
}
