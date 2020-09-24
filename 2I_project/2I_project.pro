QT       += core gui multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ammo.cpp \
    boss.cpp \
    coffee.cpp \
    controller.cpp \
    element.cpp \
    enemy.cpp \
    homework.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    menu.cpp \
    model.cpp \
    player.cpp \
    projectile.cpp \
    resource.cpp \
    rules.cpp \
    unit.cpp

HEADERS += \
    ammo.h \
    boss.h \
    coffee.h \
    controller.h \
    element.h \
    enemy.h \
    homework.h \
    mainwindow.h \
    map.h \
    menu.h \
    model.h \
    player.h \
    projectile.h \
    resource.h \
    rules.h \
    unit.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    ../../map/maps/map_test.png \
    fonts/Chicken Quiche.ttf \
    fonts/Chicken Quiche.ttf

FORMS += \
    mainwindow.ui \
    menu.ui \
    rules.ui
