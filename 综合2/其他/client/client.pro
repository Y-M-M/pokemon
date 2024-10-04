QT       += core gui
QT += network # 添加网络模块，允许在项目中使用Qt的网络模块的各种类和功能

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battlecontroller.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    pokemon.cpp

HEADERS += \
    battlecontroller.h \
    login.h \
    mainwindow.h \
    pokemon.h

FORMS += \
    login.ui \
    mainwindow.ui

TRANSLATIONS += \
    qmake_phase2_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    client/image.qrc
