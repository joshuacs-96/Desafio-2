#include "io.h"
#include "Plataforma.h"
#include "Usuario.h"
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "Anuncio.h"
#include <cstdio>
#include <cstring>
#include <cstddef>
#include <cstdlib>

// -------- util mínima --------
static bool leerLinea(FILE* f, char* buf, int n){ return std::fgets(buf, n, f)!=nullptr; }
static void trim(char* s){
    if(!s) return;
    int n = (int)std::strlen(s);
    while(n>0 && (s[n-1]=='\r' || s[n-1]=='\n' || s[n-1]==' ' || s[n-1]=='\t')) s[--n]='\0';
    int i=0; while(s[i]==' '||s[i]=='\t') ++i;
    if(i>0) std::memmove(s, s+i, std::strlen(s+i)+1);
}
static char* campo(char* &p){
    if(!p || !*p) { p=nullptr; return nullptr; }
    char* ini = p;
    while(*p && *p!=';') ++p;
    if(*p==';'){ *p='\0'; ++p; }
    trim(ini);
    return ini;
}
static int  toInt(const char* s){ return s? std::atoi(s) : 0; }
static float toFloat(const char* s){ return s? (float)std::atof(s) : 0.f; }

// --------- implementaciones ---------

bool cargarUsuarios(const char* path, Plataforma& app){
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;

    char line[1024];
    while (leerLinea(f, line, sizeof(line))){
        trim(line);
        if(!line[0] || line[0]=='#') continue;

        char* p = line;
        char* nick   = campo(p);
        char* tipo   = campo(p);
        char* ciudad = campo(p);
        char* pais   = campo(p);
        char* fecha  = campo(p);
        (void)campo(p); // pass (opcional)

        if(!nick || !tipo) continue;
        Usuario* u = new Usuario(nick, tipo, ciudad?ciudad:"", pais?pais:"", fecha?fecha:"");
        app.agregarUsuario(u);
    }
    std::fclose(f);
    return true;
}

bool cargarArtistas(const char* path, Plataforma& app){
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char line[1024];
    while (leerLinea(f, line, sizeof(line))){
        trim(line); if(!line[0] || line[0]=='#') continue;
        char* p = line;
        char* sId   = campo(p);          // id
        char* nom   = campo(p);          // nombre
        char* sEdad = campo(p);          // edad
        char* pais  = campo(p);          // pais
        char* sSeg  = campo(p);          // seguidores
        char* sPos  = campo(p);          // posicion

        if(!sId || !nom) continue;
        Artista* a = new Artista();
        a->setIdArtista(toInt(sId));
        a->setNombre(nom);
        a->setEdad(toInt(sEdad));
        a->setPaisOrigen(pais?pais:"");
        a->setSeguidores(toInt(sSeg));
        a->setPosicionGlobal(toInt(sPos));
        app.agregarArtista(a);
    }
    std::fclose(f);
    return true;
}

bool cargarAlbums(const char* path, Plataforma& app){
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char line[2048];
    while (leerLinea(f, line, sizeof(line))){
        trim(line); if(!line[0] || line[0]=='#') continue;
        char* p = line;
        char* sArtId = campo(p); // artista_id
        char* sAlbId = campo(p); // album_id
        char* nom    = campo(p); // nombre
        char* sello  = campo(p); // sello
        char* fecha  = campo(p); // fecha
        char* sPunt  = campo(p); // puntuacion
        char* portada= campo(p); // ruta portada
        char* gens   = campo(p); // generos g1|g2|...

        int artId = toInt(sArtId), albId = toInt(sAlbId);
        Artista* art = app.encontrarArtista(artId);
        if(!art) continue;

        Album* alb = new Album(albId, nom?nom:"", sello?sello:"", fecha?fecha:"", portada?portada:"");
        alb->setPuntuacion(toFloat(sPunt));

        if(gens && *gens){
            // partir por '|'
            char* tmp = gens;
            while(tmp && *tmp){
                char* g = tmp;
                while(*tmp && *tmp!='|') ++tmp;
                if(*tmp=='|'){ *tmp='\0'; ++tmp; }
                trim(g);
                if(*g) alb->agregarGenero(g);
            }
        }
        art->agregarAlbum(alb);
    }
    std::fclose(f);
    return true;
}

bool cargarCanciones(const char* path, Plataforma& app){
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char line[2048];
    while (leerLinea(f, line, sizeof(line))){
        trim(line); if(!line[0] || line[0]=='#') continue;
        char* p = line;
        char* sId9   = campo(p);   // id 9 dígitos
        char* nombre = campo(p);   // nombre pista
        char* sMins  = campo(p);   // duración en minutos (float)
        char* base   = campo(p);   // subruta base (linux, sin el *_128.ogg)
        char* sPlay  = campo(p);   // reproducciones (opcional)

        if(!sId9 || !nombre) continue;
        int id9 = toInt(sId9);

        // descomponer id: AAAAA BB CC
        int artId = id9 / 10000;                 // 5 dígitos
        int albId = (id9 / 100) % 100;           // 2 dígitos
        // int track = id9 % 100;                // 2 dígitos, por si lo necesitas

        Album* alb = app.encontrarAlbum(artId, albId);
        if(!alb) continue;

        // Rutas: si tu CSV YA trae rutas completas a 128/320, comenta este bloque y usa esas columnas.
        char r128[1024], r320[1024];
        std::snprintf(r128, sizeof(r128), "%s/audio/%s_128.ogg", base?base:"", nombre);
        std::snprintf(r320, sizeof(r320), "%s/audio/%s_320.ogg", base?base:"", nombre);

        Cancion* c = new Cancion(id9, nombre, toFloat(sMins), r128, r320);
        c->setReproducciones(toInt(sPlay));
        alb->agregarCancion(c);
        alb->calcularDuracion(); // mantener tiempo total
    }
    std::fclose(f);
    return true;
}

bool cargarAnuncios(const char* path, Plataforma& app){
    FILE* f = std::fopen(path, "rb");
    if(!f) return false;
    char line[1024];
    while (leerLinea(f, line, sizeof(line))){
        trim(line); if(!line[0] || line[0]=='#') continue;
        char* p = line;
        char* cat = campo(p); // AAA | B | C
        char* msg = campo(p); // texto
        if(!msg) continue;
        Anuncio* a = new Anuncio(msg, cat?cat:"C");
        app.agregarAnuncio(a);
    }
    std::fclose(f);
    return true;
}

// util de rutas
void pathJoin(const char* base, const char* file, char* out, std::size_t outsz){
    if(!base || !*base){ std::snprintf(out, outsz, "%s", file?file:""); return; }
    std::snprintf(out, outsz, "%s/%s", base, file?file:"");
}
