/***************************************************************************\
*  Pixel::Booster, a simple pixel art image editor.                         *
*  Copyright (C) 2015  Ricardo Bustamante de Queiroz (ricardo@busta.com.br) *
*                                                                           *
*  This program is free software: you can redistribute it and/or modify     *
*  it under the terms of the GNU General Public License as published by     *
*  the Free Software Foundation, either version 3 of the License, or        *
*  (at your option) any later version.                                      *
*                                                                           *
*  This program is distributed in the hope that it will be useful,          *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
*  GNU General Public License for more details.                             *
*                                                                           *
*  You should have received a copy of the GNU General Public License        *
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
\***************************************************************************/

#include "application/pixel_booster.h"

#include <QTranslator>
#include <QTimer>

#include "screens/main_window.h"
#include "utils/debug.h"

const QString kApplicationName = "Pixel::Booster";
const QString kOrganizationName = "Busta Software";
const QString kOrganizationDomain = "pixel.busta.com.br";

PixelBooster::PixelBooster(int argc, char * argv[])
  : QApplication(argc,argv),
    main_window_(new MainWindow()),
    options_(new GlobalOptions()){
  QCoreApplication::setApplicationName(kApplicationName);
  QCoreApplication::setOrganizationName(kOrganizationName);
  QCoreApplication::setOrganizationDomain(kOrganizationDomain);
  main_window_->show();
}

QWidget *PixelBooster::main_window() const {
  return main_window_;
}

GlobalOptions *PixelBooster::options() const {
  return options_;
}

void PixelBooster::Translate(QString language) {
  QTranslator * translator = new QTranslator();
  bool res = translator->load(":/translations/pixel_booster_"+language);
  res = this->installTranslator(translator);
}
