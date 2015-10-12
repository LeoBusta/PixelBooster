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

#include "image_edit_widget.h"

#include <QPainter>

#include "utils/debug.h"
#include "application/pixel_booster.h"

ImageEditWidget::ImageEditWidget(QWidget *parent) : QWidget(parent) {
  image_ = QImage(0,0,QImage::Format_ARGB32);
  this->setFixedSize(0,0);
}

void ImageEditWidget::Clear(const QSize &size) {
  image_ = QImage(size,QImage::Format_ARGB32);
  image_.fill(Qt::white);
  this->setFixedSize(image_.size());
  update();
}

void ImageEditWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  if(image_.isNull()){
    return;
  }
  painter.drawImage(image_.rect(),image_);
}

void ImageEditWidget::GetImage(QImage *image) {
  if(NULL == image || image->isNull()){
    return;
  }

  image_ = *image;

  this->setFixedSize(image_.size());
  update();
}

void ImageEditWidget::HandleRequest() {
  emit SendImage(&image_);
}

