#---------------------------------------------------------------------------#
#  Pixel::Booster, a simple pixel art image editor.                         #
#  Copyright (C) 2015  Ricardo Bustamante de Queiroz (ricardo@busta.com.br) #
#                                                                           #
#  This program is free software: you can redistribute it and/or modify     #
#  it under the terms of the GNU General Public License as published by     #
#  the Free Software Foundation, either version 3 of the License, or        #
#  (at your option) any later version.                                      #
#                                                                           #
#  This program is distributed in the hope that it will be useful,          #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of           #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
#  GNU General Public License for more details.                             #
#                                                                           #
#  You should have received a copy of the GNU General Public License        #
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.    #
#---------------------------------------------------------------------------#

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelBooster
TEMPLATE = app
CONFIG += c++11
QMAKE_CXXFLAGS += -Wall

SOURCES += \
    main.cpp \
    widgets/image_edit_widget.cpp \
    screens/new_image_file_dialog.cpp \
    application/pixel_booster.cpp \
    logic/action_handler.cpp \
    widgets/image_canvas_container.cpp \
    widgets/image_canvas_widget.cpp \
    application/global_options.cpp \
    screens/about_dialog.cpp \
    screens/set_tile_size_dialog.cpp \
    screens/main_window.cpp \
    widgets/color_picker_widget.cpp

HEADERS  += \
    widgets/image_edit_widget.h \
    screens/new_image_file_dialog.h \
    application/pixel_booster.h \
    logic/action_handler.h \
    utils/debug.h \
    resources/translations/international_text.h \
    widgets/image_canvas_container.h \
    widgets/image_canvas_widget.h \
    application/global_options.h \
    screens/about_dialog.h \
    screens/set_tile_size_dialog.h \
    screens/main_window.h \
    widgets/color_picker_widget.h

FORMS    += \
    screens/new_image_file_dialog.ui \
    widgets/image_canvas_container.ui \
    screens/about_dialog.ui \
    screens/set_tile_size_dialog.ui \
    screens/main_window.ui \
    widgets/color_picker_widget.ui

RESOURCES += \
    resources/icons/icons.qrc \
    resources/images/images.qrc \
    resources/translations/translations.qrc

# To update .ts files with the most recent translations run lupdate
# To generate the .qm files that will be needed by the application run lrelease
TRANSLATIONS += \
    resources/translations/pixel_booster_pt_br.ts \
    resources/translations/pixel_booster_en_us.ts \
