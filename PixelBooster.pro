#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T01:51:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelBooster
TEMPLATE = app
CONFIG += c++11
QMAKE_CXXFLAGS += -Wall

SOURCES += \
    main.cpp\
    widgets/mainwindow.cpp \
    widgets/image_widget.cpp \
    widgets/image_edit_widget.cpp \
    widgets/new_image_file_dialog.cpp \
    application/pixel_booster.cpp \
    logic/action_handler.cpp

HEADERS  += \
    widgets/mainwindow.h \
    widgets/image_widget.h \
    widgets/image_edit_widget.h \
    widgets/new_image_file_dialog.h \
    application/pixel_booster.h \
    logic/action_handler.h \
    utils/debug.h

FORMS    += \
    widgets/mainwindow.ui \
    widgets/new_image_file_dialog.ui

RESOURCES += \
    resources/icons/icons.qrc \
    resources/images/images.qrc
