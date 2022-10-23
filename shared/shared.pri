
INCLUDEPATH += $$PWD

include(../3rdparty/qtservice/src/qtservice.pri)

include(../3rdparty/hjson-cpp/src/hjson.pri)

SOURCES += \
    $$PWD/cleanhelper.cpp \
    $$PWD/config.cpp \
    $$PWD/configops.cpp \
    $$PWD/utilities.cpp \
    $$PWD/registry.cpp \
    $$PWD/qtglobalmutex.cpp \
    $$PWD/errorlogger.cpp \
    $$PWD/jsonconvert.cpp \
    $$PWD/qwbemservices.cpp \
    $$PWD/qcominitializer.cpp

HEADERS += \
    $$PWD/cleanhelper.h \
$$PWD/config.h \
    $$PWD/configops.h \
    $$PWD/utilities.h \
    $$PWD/enums.h \
    $$PWD/registry.h \
    $$PWD/qtglobalmutex.h \
    $$PWD/errorlogger.h \
    $$PWD/jsonconvert.h \
    $$PWD/qt_comutils.h \
    $$PWD/qwbemservices.h \
    $$PWD/qcominitializer.h
