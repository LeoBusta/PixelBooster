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

#include "color_palette_widget.h"

#include <QPainter>
#include <QMouseEvent>

#include "application/pixel_booster.h"
#include "screens/main_window.h"
#include "logic/action_handler.h"

ColorPaletteWidget::ColorPaletteWidget(QWidget *parent) : QWidget(parent) {
palette_ = QImage(":/images/color_palette.png");
}

void ColorPaletteWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  if(palette_.isNull()){
    return;
  }

  painter.drawImage(rect(),palette_);
}

void ColorPaletteWidget::mousePressEvent(QMouseEvent *event) {
  float posx = static_cast<float>(event->pos().x()) / static_cast<float>(this->width());
  float posy = static_cast<float>(event->pos().y()) / static_cast<float>(this->height());
  QColor color = palette_.pixel(palette_.width()*posx, palette_.height()*posy);
  switch(event->button()) {
  case Qt::LeftButton:
    pApp->main_window()->action_handler()->SetMainColor(color);
    break;
  case Qt::RightButton:
    pApp->main_window()->action_handler()->SetAltColor(color);
    break;
  default:
    break;
  }
}
