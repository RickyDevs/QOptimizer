
QT += qml quick axcontainer
QT -= widgets svg d3d

CONFIG += c++11 qmltypes

LIBS += -lwbemuuid

QML_IMPORT_NAME = io.qoptimizer.backend
QML_IMPORT_MAJOR_VERSION = 1

qo_shared += wbem

include(../shared/shared.pri)

INCLUDEPATH += $$PWD/optimize

HEADERS += \
    program.h \
    mainmodel.h \
    optimize/qoptimizeproxyitem.h \
    optimize/qoptimizeproxymanager.h

SOURCES += main.cpp \
    program.cpp \
    mainmodel.cpp \
    optimize/qoptimizeproxyitem.cpp \
    optimize/qoptimizeproxymanager.cpp

RESOURCES += qml.qrc

OTHER_FILES += \
    qml/main.qml \
    qml/Page1.qml \
    qml/controls/OptimizeItem.qml \
    qml/controls/ToggleButton.qml \
    qml/page1/MainPanelView.qml \
    qml/page1/MainTreeView.qml \
    qml/pageX/ProfileActivatePage.qml \
    qml/js/page1.js


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QO_GUI

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


