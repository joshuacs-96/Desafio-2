#ifndef IO_H
#define IO_H

#include <cstddef> // std::size_t
class Plataforma;  // forward-declare, no hace falta incluir todo aquí

bool cargarUsuarios (const char* path, Plataforma& app);
bool cargarArtistas (const char* path, Plataforma& app);
bool cargarAlbums   (const char* path, Plataforma& app);
bool cargarCanciones(const char* path, Plataforma& app);
bool cargarAnuncios (const char* path, Plataforma& app);

// util de rutas
void pathJoin(const char* base, const char* file, char* out, std::size_t outsz);

#endif // IO_H
