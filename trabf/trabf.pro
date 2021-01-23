TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CFLAGS += -Wno-unknown-pragmas -fopenmp -std=c99
LIBS += -O3 -g -fopenmp -std=c99
SOURCES += \
        main.c

DISTFILES += \
    save.txt \
    teste \
    teste2
