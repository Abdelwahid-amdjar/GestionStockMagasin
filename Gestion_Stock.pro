QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfourniseur.cpp \
    addproduit.cpp \
    deleteproduit.cpp \
    gerelentre.cpp \
    gerestock.cpp \
    main.cpp \
    mainwindow.cpp \
    updateproduit.cpp \
    verifierstock.cpp

HEADERS += \
    Mydb.h \
    addfourniseur.h \
    addproduit.h \
    deleteproduit.h \
    gerelentre.h \
    gerestock.h \
    mainwindow.h \
    updateproduit.h \
    verifierstock.h

FORMS += \
    addfourniseur.ui \
    addproduit.ui \
    deleteproduit.ui \
    gerelentre.ui \
    gerestock.ui \
    mainwindow.ui \
    updateproduit.ui \
    verifierstock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
