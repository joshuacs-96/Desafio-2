#include "io.h"
#include "Plataforma.h"
#include "Usuario.h"
// Si vas a crear objetos reales, incluye también: Artista.h, Album.h, Cancion.h, Anuncio.h
#include <cstdio>
#include <cstring>
#include <cstddef>
#include <cstdio>

// -------- helpers locales --------
static bool leerLinea(FILE* f, char* buf, int n) {
    return std::fgets(buf, n, f) != nullptr;
}
static void cortarNL(char* s){
    if(!s) return;
    std::size_t n = std::strlen(s);
    if(n && (s[n-1]=='\n' || s[n-1]=='\r')) s[n-1] = 0;
}
static char* campo(char* s){                // separa por ';'
    char* p = std::strchr(s, ';');
    if (p) { *p = 0; return p + 1; }
    return nullptr;
}
// ---------------------------------

void pathJoin(const char* base, const char* file, char* out, std::size_t outsz) {
    if (!base) base = "";
    if (!file) file = "";
    bool needsSlash = (std::strlen(base) > 0 && base[std::strlen(base) - 1] != '/');
    std::snprintf(out, outsz, "%s%s%s", base, (needsSlash ? "/" : ""), file);
}

bool cargarUsuarios(const char* path, Plataforma& app){
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;

    char line[1024];
    while (leerLinea(f, line, 1024)){
        cortarNL(line);
        if(!line[0] || line[0]=='#') continue;

        char* p = line;
        char* nick   = p;              p = campo(p);
        char* tipo   = p ? p : (char*)""; p = p ? campo(p) : nullptr;
        char* ciudad = p ? p : (char*)""; p = p ? campo(p) : nullptr;
        char* pais   = p ? p : (char*)""; p = p ? campo(p) : nullptr;
        char* fecha  = p ? p : (char*)""; p = p ? campo(p) : nullptr;
        char* pass   = p ? p : (char*)""; // opcional
        (void)pass; // para evitar warning si no lo usas

        // Crea el usuario según tu ctor real:
        // Usuario(const char* nick, const char* tipo, const char* ciudad, const char* pais, const char* fecha)
        Usuario* u = new Usuario(nick, tipo, ciudad, pais, fecha);
        app.agregarUsuario(u);
    }
    std::fclose(f);
    return true;
}

// Las siguientes pueden ser "stubs" (leen el archivo para validar existencia y devuelven true)
// Si conoces los constructores de Artista/Album/Cancion/Anuncio, aquí mismo crea los objetos y llama a app.agregarXxx.
// De momento, solo validan que se pueda abrir y leer.
bool cargarArtistas(const char* path, Plataforma& app){
    (void)app;
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char buf[256];
    while (leerLinea(f, buf, sizeof(buf))) { /* opcional: parsear */ }
    std::fclose(f);
    return true;
}

bool cargarAlbums(const char* path, Plataforma& app){
    (void)app;
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char buf[256];
    while (leerLinea(f, buf, sizeof(buf))) { /* opcional: parsear */ }
    std::fclose(f);
    return true;
}

bool cargarCanciones(const char* path, Plataforma& app){
    (void)app;
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char buf[256];
    while (leerLinea(f, buf, sizeof(buf))) { /* opcional: parsear */ }
    std::fclose(f);
    return true;
}

bool cargarAnuncios(const char* path, Plataforma& app){
    (void)app;
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char buf[256];
    while (leerLinea(f, buf, sizeof(buf))) { /* opcional: parsear */ }
    std::fclose(f);
    return true;
}
