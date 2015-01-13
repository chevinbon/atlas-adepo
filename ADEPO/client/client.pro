QT       += core gui widgets testlib network

TARGET = client
CONFIG   -= app_bundle

TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/../eigen-eigen-ffa86ffb5570

SOURCES += \
    atlas_bcam.cpp \
    main.cpp \
    read_write_ref.cpp

HEADERS += \
    atlas_bcam.h \
    float_table_widget_item.h \
    read_write_ref.h \
    result.h

FORMS += \
    ATLAS_BCAM.ui


unix: LIBS += -L$$OUT_PWD/../common/ -lcommon

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

unix: PRE_TARGETDEPS += $$OUT_PWD/../common/libcommon.a


unix: LIBS += -L$$OUT_PWD/../server/ -lserver

INCLUDEPATH += $$PWD/../server
DEPENDPATH += $$PWD/../server

unix: PRE_TARGETDEPS += $$OUT_PWD/../server/libserver.a