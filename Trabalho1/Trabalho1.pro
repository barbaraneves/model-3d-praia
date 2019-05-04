TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += objetos

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    objetos/objeto.cpp \
    objetos/palmeira.cpp \
    objetos/bola.cpp \
    objetos/barco.cpp \
    objetos/prancha.cpp \
    objetos/bamboo.cpp \
    objetos/guardasol.cpp \
    objetos/casa.cpp \
    objetos/trave.cpp \
    objetos/porta.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    objetos/objeto.h \
    objetos/palmeira.h \
    objetos/bola.h \
    objetos/barco.h \
    objetos/prancha.h \
    objetos/bamboo.h \
    objetos/guardasol.h \
    objetos/casa.h \
    objetos/trave.h \
    objetos/porta.h
