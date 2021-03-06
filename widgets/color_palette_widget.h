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

#ifndef COLOR_PALETTE_WIDGET_H
#define COLOR_PALETTE_WIDGET_H

#include <QWidget>

class ColorPaletteWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ColorPaletteWidget(QWidget *parent = 0);

  virtual void paintEvent(QPaintEvent *event);

  virtual void mousePressEvent(QMouseEvent *event);
private:
  QImage palette_;
signals:

public slots:
};

#endif // COLOR_PALETTE_WIDGET_H
