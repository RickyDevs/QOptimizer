
INCLUDEPATH += $$PWD $$PWD/optimize

include(../3rdparty/qtservice/src/qtservice.pri)

include(../3rdparty/hjson-cpp/src/hjson.pri)

SOURCES += \
    $$PWD/cleanhelper.cpp \
    $$PWD/config.cpp \
    $$PWD/configops.cpp \
    $$PWD/optimize/optimizebaseitem.cpp \
    $$PWD/optimize/optimizegroupitem.cpp \
    $$PWD/optimize/optimizemanager.cpp \
    $$PWD/optimize/optimizestdcalls.cpp \
    $$PWD/optimize/performancetweaks.cpp \
    $$PWD/utilities.cpp \
    $$PWD/registry.cpp \
    $$PWD/qtglobalmutex.cpp \
    $$PWD/errorlogger.cpp \
    $$PWD/jsonconvert.cpp

HEADERS += \
    $$PWD/cleanhelper.h \
    $$PWD/config.h \
    $$PWD/configops.h \
    $$PWD/optimize/optimizebaseitem.h \
    $$PWD/optimize/optimizegroupitem.h \
    $$PWD/optimize/optimizemanager.h \
    $$PWD/optimize/optimizestdcalls.h \
    $$PWD/optimize/performancetweaks.h \
    $$PWD/utilities.h \
    $$PWD/enums.h \
    $$PWD/registry.h \
    $$PWD/qtglobalmutex.h \
    $$PWD/errorlogger.h \
    $$PWD/jsonconvert.h \
    $$PWD/tagshelper.h
    

contains( qo_shared, wbem ) {
    # qo_shared contains 'wbem'
    message( "Configuring WBEM services build..." )

    HEADERS += \
        $$PWD/qt_comutils.h \
        $$PWD/qcominitializer.h \
        $$PWD/qwbemservices.h

    SOURCES += \
        $$PWD/qcominitializer.cpp \
        $$PWD/qwbemservices.cpp

}
