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

#ifndef PIXEL_BOOSTER_H
#define PIXEL_BOOSTER_H

#include <QApplication>

#include "application/global_options.h"

#define pApp dynamic_cast<PixelBooster*>(qApp)

class MainWindow;

/*!
 * \brief The PixelBooster class
 */
class PixelBooster : public QApplication
{
public:
  PixelBooster(int argc, char *argv[]);

  MainWindow *main_window() const;
  GlobalOptions * options() const;

  void SetStatusMessage(const QString &message);

  void Translate(QString language);
private:
  GlobalOptions * options_;
  MainWindow * main_window_;
};

#endif // PIXEL_BOOSTER_H
