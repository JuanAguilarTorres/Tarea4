QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    ui_es_CR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/tienda_local/release/ -ltienda_local
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/tienda_local/debug/ -ltienda_local
else:unix: LIBS += -L$$OUT_PWD/../../lib/tienda_local/ -ltienda_local

INCLUDEPATH += $$PWD/../../lib/tienda_local
DEPENDPATH += $$PWD/../../lib/tienda_local

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/tienda_local/release/libtienda_local.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/tienda_local/debug/libtienda_local.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/tienda_local/release/tienda_local.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/tienda_local/debug/tienda_local.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/tienda_local/libtienda_local.a
