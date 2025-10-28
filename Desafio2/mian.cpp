#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include <limits>
#include <filesystem>
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
    player.setMaxHistorial(6);
    app.setMedidor(&monitor);

    auto cargarTodo = [&](const char* base) {
        char path[1024];
        bool ok = true;

        pathJoin(base, "usuarios.csv",  path, sizeof(path)); ok &= cargarUsuarios(path, app);
        pathJoin(base, "artistas.csv",  path, sizeof(path)); ok &= cargarArtistas(path, app);
        pathJoin(base, "albums.csv",    path, sizeof(path)); ok &= cargarAlbums(path, app);
        pathJoin(base, "canciones.csv", path, sizeof(path)); ok &= cargarCanciones(path, app);
        pathJoin(base, "anuncios.csv",  path, sizeof(path)); ok &= cargarAnuncios(path, app);

        return ok;
    };

    const char* bases[] = {"Data","data",".","..","../Data","../data"};
    bool cargado = false;
    for (const char* b : bases) {
        if (cargarTodo(b)) {
            const std::string rutaAbsolutaEspecifica =
                "D:/Udea 3/Info 2/Teorica/PRACTICA 2/Codigo/Desafio2/build/Desktop_Qt_6_9_2_MinGW_64_bit-Debug/debug/debug/data";
            std::cout << "[OK] Datos desde: " << b << "\n"; cargado = true; break; }

    }
    if (!cargado) { std::cout << "[ERROR] No pude cargar CSVs.\n"; return 0; }

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
            std::cout << "Nickname del usuario a seguir: ";
            std::string otro;
            std::getline(std::cin, otro);
            if(otro.empty()) std::getline(std::cin, otro);

            Usuario* u2 = app.login(otro.c_str(), ""); // ignora pass
            if(!u2 || !u2->Premium() || !u2->getListaFavoritos() || u2==activo){
                std::cout << "No es posible seguir esa lista.\n";
            } else {
                ListaFavoritos* lf2 = u2->getListaFavoritos();
                if(lf2 && lf2->getLen()>0){
                    Cancion** vec = lf2->getVector();
                    for(int i=0;i<lf2->getLen();++i) if(vec[i]) fav.agregarCancion(vec[i]);
                    std::cout << "Listas combinadas. (" << fav.getLen() << " canciones)\n";
                } else {
                    std::cout << "La lista destino está vacía.\n";
                }
            }
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }
    return 0;
}
