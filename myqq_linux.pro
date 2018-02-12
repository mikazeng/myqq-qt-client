#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T22:05:48
#
#-------------------------------------------------

QT       += core gui network
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myqq
TEMPLATE = app


SOURCES += main.cpp\
    toolbox.cpp \
    chat.cpp \
    json/json_internalarray.inl \
    json/json_internalmap.inl \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_valueiterator.inl \
    json/json_writer.cpp \
    login.cpp

HEADERS  += \
    toolbox.h \
    chat.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/json_batchallocator.h \
    json/reader.h \
    json/value.h \
    json/writer.h \
    login.h \
    encrypt.h

FORMS    += \
    chat.ui \
    login.ui

RESOURCES += \
    image.qrc
CONFIG +=C++11

OTHER_FILES += \
    json/jsoncpp-src-0.5.0.tar (1).gz \
    json/sconscript

LIBS += -LC:/OpenSSL-Win32/lib/MinGw -leay32
INCLUDEPATH += C:/OpenSSL-Win32/include
