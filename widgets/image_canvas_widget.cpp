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

#include "image_canvas_widget.h"

#include "utils/debug.h"

#include <QPainter>

ImageCanvasWidget::ImageCanvasWidget(const QImage &image, QWidget *parent)
  : QWidget(parent) {
  setMouseTracking(true);

  DEBUG_MSG(image_.isNull());
  image_ = image;
  DEBUG_MSG("ok?");
  this->setFixedSize(image_.size());
  DEBUG_MSG("wat");
}

ImageCanvasWidget::~ImageCanvasWidget() {

}

void ImageCanvasWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  if(image_.isNull()) return;
  painter.drawImage(image_.rect(),image_);
}

void ImageCanvasWidget::mousePressEvent(QMouseEvent *event) {

}

void ImageCanvasWidget::mouseReleaseEvent(QMouseEvent *event) {

}

void ImageCanvasWidget::mouseMoveEvent(QMouseEvent *event) {

}

