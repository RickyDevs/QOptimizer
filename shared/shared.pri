
INCLUDEPATH += $$PWD $$PWD/optimize $$PWD/singletons

include(../3rdparty/qtservice/src/qtservice.pri)

include(../3rdparty/hjson-cpp/src/hjson.pri)

SOURCES += \
    $$PWD/cleanhelper.cpp \
    $$PWD/config.cpp \
    $$PWD/configops.cpp \
    $$PWD/optimize/groupperformancetweaks.cpp \
    $$PWD/optimize/groupnetworkservices.cpp \
    $$PWD/optimize/groupwindowscustom.cpp \
    $$PWD/optimize/optimizebaseitem.cpp \
    $$PWD/optimize/optimizegroupitem.cpp \
    $$PWD/optimize/optimizemanager.cpp \
    $$PWD/optimize/optimizestdcalls.cpp \
    $$PWD/optimize/registrystrategy.cpp \
    $$PWD/optimize/strategyoptimizeitem.cpp \
    $$PWD/utilities.cpp \
    $$PWD/registry.cpp \
    $$PWD/qtglobalmutex.cpp \
    $$PWD/errorlogger.cpp \
    $$PWD/jsonconvert.cpp \
    $$PWD/singletons/singleton.cpp

HEADERS += \
    $$PWD/cleanhelper.h \
    $$PWD/config.h \
    $$PWD/configops.h \
    $$PWD/optimize/groupperformancetweaks.h \
    $$PWD/optimize/groupnetworkservices.h \
    $$PWD/optimize/groupwindowscustom.h \
    $$PWD/optimize/optimizebaseitem.h \
    $$PWD/optimize/optimizegroupitem.h \
    $$PWD/optimize/optimizemanager.h \
    $$PWD/optimize/optimizestdcalls.h \
    $$PWD/optimize/registrystrategy.h \
    $$PWD/optimize/strategyoptimizeitem.h \
    $$PWD/utilities.h \
    $$PWD/enums.h \
    $$PWD/registry.h \
    $$PWD/qtglobalmutex.h \
    $$PWD/errorlogger.h \
    $$PWD/jsonconvert.h \
    $$PWD/tagshelper.h \
    $$PWD/singletons/iactivefromorigin.h \
    $$PWD/singletons/singleton.h

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

contains( qo_shared, registry_fake ) {
    # qo_shared contains fake registry
    message( "Configuring fake registry build..." )

    HEADERS += \
        $$PWD/optimize/registryutil.h

    SOURCES += \
        $$PWD/optimize/registryutil_fake.cpp

} else {
    message( "Configuring real registry build..." )

    HEADERS += \
        $$PWD/optimize/registryutil.h

    SOURCES += \
        $$PWD/optimize/registryutil_impl.cpp

}
