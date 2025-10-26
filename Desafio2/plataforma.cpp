#include "Plataforma.h"
#include "Usuario.h"
#include "Artista.h"
#include "Anuncio.h"
#include "Album.h"
#include "Cancion.h"
#include "SistemaReproduccion.h"
#include "MedidorRecursos.h"
#include <cstdlib>
Plataforma::Plataforma():usuarios(0),numUsuarios(0),capUsuarios(0),catalogoArtistas(0),numArtistas(0),capArtistas(0),
    anuncios(0),numAnuncios(0),capAnuncios(0),player(0),medidor(0){}
Plataforma::~Plataforma() {
    delete[] usuarios;
    delete[] catalogoArtistas;
    delete[] anuncios;

    usuarios = nullptr;          // <- en líneas separadas
    catalogoArtistas = nullptr;  //    para no mezclar tipos
    anuncios = nullptr;

    numUsuarios = numArtistas = numAnuncios = 0;
    capUsuarios = capArtistas = capAnuncios = 0;
}
void Plataforma::setSistemaReproduccion(SistemaReproduccion* p){ player=p; } void Plataforma::setMedidor(MedidorRecursos* m){ medidor=m; }
void Plataforma::agregarUsuario(Usuario* u){ usuarios=ensureCap(usuarios,capUsuarios,numUsuarios+1); usuarios[numUsuarios++]=u; }
void Plataforma::agregarArtista(Artista* a){ catalogoArtistas=ensureCap(catalogoArtistas,capArtistas,numArtistas+1); catalogoArtistas[numArtistas++]=a; }
void Plataforma::agregarAnuncio(Anuncio* a){ anuncios=ensureCap(anuncios,capAnuncios,numAnuncios+1); anuncios[numAnuncios++]=a; }
void Plataforma::reproducirAleatorio(){
    if(!player || numArtistas<=0) return;
    int idxA = (numArtistas==1)?0: (std::rand()%numArtistas);
    Artista* art = catalogoArtistas[idxA]; if(!art) return;
    Album** albv = art->getAlbumes(); int nA = art->getLenAlbums(); if(!albv||nA<=0) return;
    int idxB = (nA==1)?0: (std::rand()%nA);
    Album* alb = albv[idxB]; if(!alb) return;
    Cancion** tracks = alb->getCanciones(); int nT = alb->getLenPistas(); if(!tracks||nT<=0) return;
    int idxC = (nT==1)?0: (std::rand()%nT);
    player->reproducir(tracks[idxC]);
}
Cancion* Plataforma::encontrarCancion(int id){
    for(int i=0;i<numArtistas;++i){
        Artista* art=catalogoArtistas[i]; if(!art) continue;
        Album** albv = art->getAlbumes(); int nA=art->getLenAlbums();
        for(int j=0; albv && j<nA; ++j){
            Cancion** tr = albv[j]->getCanciones(); int nT = albv[j]->getLenPistas();
            for(int k=0; tr && k<nT; ++k){ Cancion* c=tr[k]; if(c && c->getIdCancion()==id) return c; }
        }
    }
    return 0;
}
