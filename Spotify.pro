QT += widgets multimedia core
QT += core gui widgets

INCLUDEPATH += $$PWD/libs/taglib/include
LIBS += -L$$PWD/libs/taglib/lib -ltag

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MusicLibrary.cpp \
    Player.cpp \
    Playlist.cpp \
    Queue.cpp \
    Track.cpp \
    TrackStorage.cpp \
    favouriteswidget.cpp \
    framelesswindow.cpp \
    homewidget.cpp \
    librarywidget.cpp \
    main.cpp \
    mainwindow.cpp
HEADERS += \
    MusicLibrary.h \
    Player.h \
    Playlist.h \
    Queue.h \
    Track.h \
    TrackStorage.h \
    favouriteswidget.h \
    framelesswindow.h \
    homewidget.h \
    librarywidget.h \
    mainwindow.h

FORMS += \
    favouriteswidget.ui \
    homewidget.ui \
    librarywidget.ui \
    mainwindow.ui \

win32 {
    DESTDIR = $$OUT_PWD

    dlls.path = $$DESTDIR
    dlls.files += $$PWD/libs/taglib/bin/libtag-2.dll
    dlls.files += $$PWD/libs/taglib/bin/zlib1.dll

    INSTALLS += dlls
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_POST_LINK += copy /Y $$shell_path($$PWD/libs/taglib/bin/libtag-2.dll) $$shell_path($$OUT_PWD/) && copy /Y $$shell_path($$PWD/libs/taglib/bin/zlib1.dll) $$shell_path($$OUT_PWD/)

RESOURCES += \
    resources.qrc
