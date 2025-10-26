#include <iostream>
#include "Plataforma.h"
#include "SistemaReproduccion.h"
#include "MedidorRecursos.h"
#include "Usuario.h"
#include "ListaFavoritos.h"
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "Anuncio.h"

int main(){
    SistemaReproduccion player;
    MedidorRecursos monitor;
    Plataforma app;
    app.setSistemaReproduccion(&player);
    app.setMedidor(&monitor);

    Usuario u("nicolas","Premium","Medellin","CO","2025-10-17");
    ListaFavoritos fav(&u);
    u.setListaFavoritos(&fav);

    Artista a(12345,"UdeABand",5,"CO",1000,1);
    Album   alb(12,"Demo","UdeARecords","2025-10-17","/images/portada_demo.png");
    Cancion c1(123450101,"Tema1",3.0f,"/aud/128/t1.ogg","/aud/320/t1.ogg");
    Cancion c2(123450102,"Tema2",2.5f,"/aud/128/t2.ogg","/aud/320/t2.ogg");
    alb.agregarCancion(&c1); alb.agregarCancion(&c2); alb.calcularDuracion();
    a.agregarAlbum(&alb);

    app.agregarArtista(&a);
    app.agregarUsuario(&u);

    Anuncio ad1("Pruébame gratis 30 días","C");
    Anuncio ad2("Upgrade B","B");
    Anuncio ad3("Oferta AAA Premium","AAA");
    app.agregarAnuncio(&ad1); app.agregarAnuncio(&ad2); app.agregarAnuncio(&ad3);

    fav.agregarCancion(&c1);
    fav.agregarCancion(&c2);

    std::cout << "--------------------------------------\n";
    std::cout << "UdeATunes - Reproduccion Aleatoria\n";
    std::cout << "Artista: " << a.getNombre() << "\n";
    std::cout << "Album: "   << alb.getNombre() << "\n";
    app.reproducirAleatorio();
    Cancion* current = player.getcancionActual();
    if(current){
        std::cout << "Cancion: " << current->getNombre() << "\n";
        std::cout << "Duracion: " << current->getDuracion() << " minutos\n";
        std::cout << "Ruta audio 320kbps: " << current->getRuta320() << "\n";
    }
    std::cout << "--------------------------------------\n";

    std::cout << "Mi Lista de Favoritos\n";
    for(int i=0;i<fav.getLen();++i){
        Cancion** v = fav.getVector();
        if(v[i]) std::cout << "- " << v[i]->getNombre() << " (" << v[i]->getDuracion() << " min)\n";
    }
    std::cout << "Reproduciendo Mi Lista...\n";
    player.setUsuarioActivo(&u);
    fav.reproducirLista(false, &player);
    std::cout << "Total reproducciones: " << player.getConteoReproducciones() << "\n";
    std::cout << "--------------------------------------\n";

    std::cout << "Métricas del sistema\n";
    monitor.setIteraciones(12);
    monitor.agregarMemoria(2048);
    std::cout << "Iteraciones: " << monitor.getIteraciones() << "\n";
    std::cout << "Memoria total: " << (unsigned long long)monitor.getMemoriaTotal() << " bytes\n";
    std::cout << "--------------------------------------\n";
    return 0;
}
