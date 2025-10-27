TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        album.cpp \
        anuncio.cpp \
        artista.cpp \
        cancion.cpp \
        credito.cpp \
        io.cpp \
        listafavoritos.cpp \
        medidorrecursos.cpp \
        mian.cpp \
        plataforma.cpp \
        sistemareproduccion.cpp \
        usuario.cpp

HEADERS += \
    album.h \
    anuncio.h \
    artista.h \
    cancion.h \
    credito.h \
    io.h \
    listafavoritos.h \
    medidorrecursos.h \
    plataforma.h \
    sistemareproduccion.h \
    usuario.h
