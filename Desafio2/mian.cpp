#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include <limits>

#include "Plataforma.h"
#include "Usuario.h"
#include "ListaFavoritos.h"
#include "Album.h"
#include "Cancion.h"
#include "Anuncio.h"
#include "SistemaReproduccion.h"
#include "MedidorRecursos.h"
#include "io.h"

static void pausa3s() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

static void imprimirBanner() {
    std::cout << "--------------------------------------\n";
    std::cout << "        UdeATunes - Plataforma        \n";
    std::cout << "--------------------------------------\n";
}

static void imprimirMenu(bool premium) {
    std::cout << "\nMenu principal\n";
    std::cout << "1) Reproduccion aleatoria\n";
    if (premium) {
        std::cout << "2) Mi Lista de Favoritos: reproducir\n";
        std::cout << "3) Mi Lista de Favoritos: agregar cancion por ID\n";
        std::cout << "4) Seguir otra lista (demo)\n";
    }
    std::cout << "0) Salir\n";
    std::cout << "Seleccione: ";
}

static void reproducirAleatoriaConAnuncios(Plataforma& app, Usuario* u, int K) {
    std::cout << "--------------------------------------\n";
    std::cout << "Reproduccion Aleatoria (K=" << K << ")\n";

    for (int i = 0; i < K; ++i) {
        app.reproducirAleatorio();

        if (u && !u->Premium() && ((i + 1) % 2 == 0)) {
            Anuncio* ad = app.elegirAnuncio();
            if (ad) std::cout << "[PUBLICIDAD] " << ad->getTexto() << "\n";
        }
        pausa3s();
    }
}

int main() {
    imprimirBanner();

    // --- Inicializar sistema ---
    SistemaReproduccion player;
    MedidorRecursos monitor;
    Plataforma app;

    app.setSistemaReproduccion(&player);
    app.setMedidor(&monitor);

    // --- Cargar CSVs ---
    const char* dataDir = "data";  // carpeta con los archivos CSV
    char path[1024];

    pathJoin(dataDir, "usuarios.csv",  path, sizeof(path));  cargarUsuarios(path, app);
    pathJoin(dataDir, "artistas.csv",  path, sizeof(path));  cargarArtistas(path, app);
    pathJoin(dataDir, "albums.csv",    path, sizeof(path));  cargarAlbums(path, app);
    pathJoin(dataDir, "canciones.csv", path, sizeof(path));  cargarCanciones(path, app);
    pathJoin(dataDir, "anuncios.csv",  path, sizeof(path));  cargarAnuncios(path, app);

    // --- Login ---
    std::string nick, pass;
    std::cout << "Usuario: ";
    std::getline(std::cin, nick);
    if (nick.empty()) std::getline(std::cin, nick);  // limpia salto residual
    std::cout << "Clave  : ";
    std::getline(std::cin, pass);

    Usuario* activo = app.login(nick.c_str(), pass.c_str());
    if (!activo) {
        std::cout << "Usuario o clave invalida.\n";
        return 0;
    }

    std::cout << "Bienvenido, " << activo->getUsuario()
              << (activo->Premium() ? " (Premium)\n" : " (Estandar)\n");

    // --- Lista de favoritos ---
    ListaFavoritos fav(activo);
    activo->setListaFavoritos(&fav);

    bool premium = activo->Premium();
    int op = -1;

    while (true) {
        imprimirMenu(premium);

        if (!(std::cin >> op)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (op == 0) {
            std::cout << "Saliendo...\n";
            break;

        } else if (op == 1) {
            monitor.reset();
            monitor.contarIteracion();
            reproducirAleatoriaConAnuncios(app, activo, 5);

            std::cout << "--------------------------------------\n";
            std::cout << "Metricas del sistema\n";
            std::cout << "Iteraciones: " << monitor.getIteraciones() << "\n";
            std::cout << "Memoria total: "
                      << static_cast<unsigned long long>(monitor.getMemoriaTotal())
                      << " bytes\n";
            std::cout << "--------------------------------------\n";

        } else if (op == 2 && premium) {
            int L = fav.getLen();
            std::cout << "Mi Lista de Favoritos (" << L << ")\n";
            for (int i = 0; i < L; ++i) {
                Cancion* c = fav.getVector()[i];
                if (c) { player.reproducir(c); pausa3s(); }
            }

        } else if (op == 3 && premium) {
            std::cout << "ID de la cancion a agregar: ";
            int id;
            if (!(std::cin >> id)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ID invalido.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Cancion* c = app.encontrarCancion(id);
            if (c) { fav.agregarCancion(c); std::cout << "Agregada.\n"; }
            else   { std::cout << "No encontrada.\n"; }

        } else if (op == 4 && premium) {
            std::cout << "(Demo) Seguir otra lista: por implementar.\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }
    return 0;
}
