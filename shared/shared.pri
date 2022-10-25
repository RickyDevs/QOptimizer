
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
    $$PWD/jsonconvert.cpp

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
