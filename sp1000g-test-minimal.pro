TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


win32 {
    DEFINES += OS_WIN
    DEFINES += __WINDOWS_TYPES__
    win32-msvc* {
        LIBS += -lsp1000g_api
    }
    equals(QMAKE_CXX, g++) {
        LIBS += sp1000g_api.dll
    }

}

macx: LIBS += -L$$PWD/dependencies/mac/ -lsp1000g_api.1.0.0

HEADERS += \
    ihwapi_common_types.h \
    ihwapi_common_types.h \
    sp1000gapi.h \
    sp1000gapi.h \
    sp1000gapi_types.h \
    sp1000gapi_types.h
