
INCLUDEPATH += $$PWD

include(../3rdparty/qtservice/src/qtservice.pri)

include(../3rdparty/hjson-cpp/src/hjson.pri)

SOURCES += \
    $$PWD/utilities.cpp \
    $$PWD/registry.cpp \
    $$PWD/qtglobalmutex.cpp \
    $$PWD/errorlogger.cpp \
    $$PWD/config.cpp \
    $$PWD/configops.cpp \
    $$PWD/jsonconvert.cpp

HEADERS += \
    $$PWD/utilities.h \
    $$PWD/enums.h \
    $$PWD/registry.h \
    $$PWD/qtglobalmutex.h \
    $$PWD/errorlogger.h \
    $$PWD/config.h \
    $$PWD/configops.h \
    $$PWD/jsonconvert.h
