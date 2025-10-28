#include "Plataforma.h"
#include "Usuario.h"
#include "Artista.h"
#include "Anuncio.h"
#include "Album.h"
#include "Cancion.h"
#include "SistemaReproduccion.h"
#include "MedidorRecursos.h"
#include <cstdlib>
#include <cstring>
#include <cctype>   // toupper

Plataforma::Plataforma()
    : usuarios(nullptr), numUsuarios(0), capUsuarios(0),
    catalogoArtistas(nullptr), numArtistas(0), capArtistas(0),
    anuncios(nullptr), numAnuncios(0), capAnuncios(0),
    player(nullptr), medidor(nullptr) {}

Plataforma::~Plataforma() {
    delete[] usuarios;
    delete[] catalogoArtistas;
    delete[] anuncios;

    usuarios = nullptr;
    catalogoArtistas = nullptr;
    anuncios = nullptr;

    numUsuarios = numArtistas = numAnuncios = 0;
    capUsuarios = capArtistas = capAnuncios = 0;
}

void Plataforma::setSistemaReproduccion(SistemaReproduccion* p){ player = p; }
void Plataforma::setMedidor(MedidorRecursos* m){ medidor = m; }

void Plataforma::agregarUsuario(Usuario* u){
    usuarios = ensureCap(usuarios, capUsuarios, numUsuarios + 1);
    usuarios[numUsuarios++] = u;
}

void Plataforma::agregarArtista(Artista* a){
    catalogoArtistas = ensureCap(catalogoArtistas, capArtistas, numArtistas + 1);
    catalogoArtistas[numArtistas++] = a;
}

void Plataforma::agregarAnuncio(Anuncio* a){
    anuncios = ensureCap(anuncios, capAnuncios, numAnuncios + 1);
    anuncios[numAnuncios++] = a;
}

void Plataforma::reproducirAleatorio(){
    if(!player || numArtistas<=0) return;

    const int K = 5;
    Cancion* ultima = nullptr;

    for(int step=0; step<K; ++step){
        // Elegir artista
        int idxA = (numArtistas==1)? 0 : (std::rand()%numArtistas);
        Artista* art = catalogoArtistas[idxA];
        if(!art) continue;

        // Elegir álbum
        Album** albv = art->getAlbumes();
        int nA = art->getLenAlbums();
        if(!albv || nA<=0) continue;
        int idxB = (nA==1)? 0 : (std::rand()%nA);

        Album* alb = albv[idxB];
        if(!alb) continue;

        // Elegir pista
        Cancion** tracks = alb->getCanciones();
        int nT = alb->getLenPistas();
        if(!tracks || nT<=0) continue;

        // Evitar repetir la última pista
        int intentos = 0;
        int idxC = (nT==1)? 0 : (std::rand()%nT);
        while (nT>1 && tracks[idxC]==ultima && intentos<6){
            idxC = std::rand()%nT;
            ++intentos;
        }

        Cancion* c = tracks[idxC];
        if(!c) continue;

        // Reproducir
        player->reproducir(c);
        ultima = c;
    }

    // Al terminar K reproducciones, actualizar métricas si hay medidor.
    if(medidor){
        // sumar 1 iteración de funcionalidad
        medidor->setIteraciones( medidor->getIteraciones() + 1 );

        // calcular memoria aproximada de toda la plataforma
        if constexpr (true) { // solo para que quede claro que es intencional
            // Si ya agregaste memoriaAproximada() (ver sección 2), úsalo:
            size_t m = this->memoriaAproximada();
            medidor->setMemoriaTotal(m);
        }

        medidor->mostrarMetricas("Reproduccion Aleatoria");
        medidor->reset();
    }
}

Cancion* Plataforma::encontrarCancion(int id){
    for(int i=0;i<numArtistas;++i){
        Artista* art = catalogoArtistas[i]; if(!art) continue;
        Album** albv = art->getAlbumes(); int nA = art->getLenAlbums();
        for(int j=0; albv && j<nA; ++j){
            Cancion** tr = albv[j]->getCanciones(); int nT = albv[j]->getLenPistas();
            for(int k=0; tr && k<nT; ++k){
                Cancion* c = tr[k];
                if(c && c->getIdCancion()==id) return c;
            }
        }
    }
    return nullptr;
}

// Busca un usuario por nickname (si no usas password, ignóralo)
Usuario* Plataforma::login(const char* nick, const char* /*pass*/){
    for(int i=0;i<numUsuarios;++i){
        if (usuarios[i] && usuarios[i]->getUsuario()
            && std::strcmp(usuarios[i]->getUsuario(), nick)==0){
            return usuarios[i];
        }
    }
    return nullptr;
}

// Ponderación AAA:3, B:2, C/otros:1 usando el primer carácter de la categoría
static int pesoPorCategoria(const char* cat) {
    if (!cat || !*cat) return 1;
    char f = static_cast<char>(std::toupper(static_cast<unsigned char>(cat[0])));
    if (f == 'A') return 3; // "AAA"
    if (f == 'B') return 2;
    return 1;               // "C" u otra
}

Anuncio* Plataforma::elegirAnuncio(){
    if(numAnuncios<=0) return nullptr;

    // calcular pesos (AAA=3, B=2, C=1). Ya tienes peso en Anuncio; si no, calcula aquí.
    int total = 0;
    for(int i=0;i<numAnuncios;++i){
        if(anuncios[i] && !anuncios[i]->getUltimoMostrado()){
            total += anuncios[i]->getPrioridad();
        }
    }
    if(total==0){
        // si todos fueron el último, reinicia la marca y vuelve a sumar
        for(int i=0;i<numAnuncios;++i) if(anuncios[i]) anuncios[i]->setUltimoMostrado(false);
        for(int i=0;i<numAnuncios;++i) if(anuncios[i]) total += anuncios[i]->getPrioridad();
        if(total==0) return nullptr;
    }

    int r = std::rand()%total, acum=0, pick=-1;
    for(int i=0;i<numAnuncios;++i){
        if(!anuncios[i]) continue;
        int w = anuncios[i]->getPrioridad();
        if(!anuncios[i]->getUltimoMostrado()){
            if(r < acum + w){ pick = i; break; }
            acum += w;
        }
    }
    if(pick<0) pick=0;

    // marcar anti-repetición
    for(int i=0;i<numAnuncios;++i) if(anuncios[i]) anuncios[i]->setUltimoMostrado(false);
    anuncios[pick]->setUltimoMostrado(true);
    return anuncios[pick];
}

// Busca artista por id
Artista* Plataforma::encontrarArtista(int id){
    for (int i=0; i<numArtistas; ++i){
        if (catalogoArtistas[i] && catalogoArtistas[i]->getIdArtista() == id)
            return catalogoArtistas[i];
    }
    return nullptr;
}

// Busca album por artista_id y album_id
Album* Plataforma::encontrarAlbum(int artista_id, int album_id){
    Artista* art = encontrarArtista(artista_id);
    if (!art) return nullptr;

    int nA = art->getLenAlbums();
    Album** albs = art->getAlbumes();
    for (int j=0; j<nA; ++j){
        if (albs[j] && albs[j]->getIdAlbum() == album_id) return albs[j];
    }
    return nullptr;
}
size_t Plataforma::memoriaAproximada() const{
    size_t total = 0;

    total += sizeof(*this);
    total += sizeof(Usuario*)  * (size_t)capUsuarios;
    total += sizeof(Artista*)  * (size_t)capArtistas;
    total += sizeof(Anuncio*)  * (size_t)capAnuncios;

    for(int i=0;i<numUsuarios;++i){
        if(usuarios[i]) total += sizeof(*usuarios[i]);
    }

    for(int i=0;i<numArtistas;++i){
        Artista* a = catalogoArtistas[i];
        if(!a) continue;
        total += sizeof(*a);
        total += sizeof(Album*) * (size_t)a->getCapAlbums();

        Album** albs = a->getAlbumes();
        for(int j=0; j<a->getLenAlbums(); ++j){
            Album* alb = albs[j];
            if(!alb) continue;
            total += sizeof(*alb);
            total += sizeof(Cancion*) * (size_t)alb->getCapPistas();

            Cancion** cs = alb->getCanciones();
            for(int k=0; k<alb->getLenPistas(); ++k){
                if(cs[k]) total += sizeof(*cs[k]);
            }
        }
    }

    for(int i=0;i<numAnuncios;++i){
        if(anuncios[i]) total += sizeof(*anuncios[i]);
    }
    return total;
}
