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
#include <QMouseEvent>

#include "utils/debug.h"
#include "application/pixel_booster.h"

ImageEditWidget::ImageEditWidget(QWidget *parent)
  : QWidget(parent),
    left_button_down_(false),
    right_button_down_(false) {
  setMouseTracking(true);
  image_ = QImage(0,0,QImage::Format_ARGB32_Premultiplied);
  this->setFixedSize(0,0);
}

void ImageEditWidget::Clear(const QSize &size) {
  image_ = QImage(size,QImage::Format_ARGB32_Premultiplied);
  image_.fill(Qt::white);
  this->setFixedSize(image_.size());
  update();
}

void ImageEditWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  if(image_.isNull()){
    return;
  }

  int zoom = pApp->options()->zoom();

  QRect image_rect = image_.rect();
  image_rect.setSize( QSize(image_.width()*zoom,image_.height()*zoom) );

  painter.drawImage(image_rect,image_);

  painter.drawRect(cursor_);

  if(cursor_.isValid()) {
  painter.drawPoint(cursor_.topLeft());
  }
}

void ImageEditWidget::mouseMoveEvent(QMouseEvent *event) {
  int zoom = pApp->options()->zoom();
  QPoint pos = event->pos();

  if(rect().contains(pos)){
    QPoint p = QPoint((pos.x()/zoom)*zoom,(pos.y()/zoom)*zoom);
    cursor_ = QRect(p,QSize(zoom-1,zoom-1));
  }else{
    cursor_ = QRect(0,0,0,0);
  }

  ToolAction(pos);
  update();
}

void ImageEditWidget::leaveEvent(QEvent *event) {
  cursor_ = QRect(0,0,0,0);
  update();
}

void ImageEditWidget::mousePressEvent(QMouseEvent *event) {
  switch(event->button()) {
  case Qt::LeftButton:
    left_button_down_ = true;
    break;
  case Qt::RightButton:
    break;
  default:
    break;
  }
  ToolAction(event->pos());
  update();
}

void ImageEditWidget::mouseReleaseEvent(QMouseEvent *event) {
  switch(event->button()) {
  case Qt::LeftButton:
    left_button_down_ = false;
    break;
  case Qt::RightButton:
    break;
  default:
    break;
  }
}

void ImageEditWidget::ToolAction(const QPoint &pos) {
  if(left_button_down_ && cursor_.isValid()){
    int zoom = pApp->options()->zoom();
    QPoint img_pos = QPoint(pos.x()/zoom,pos.y()/zoom);
    image_.setPixel(img_pos,pApp->options()->main_color().rgba());
  }
}

void ImageEditWidget::GetImage(QImage *image) {
  if(NULL == image || image->isNull()){
    return;
  }

  image_ = *image;

  UpdateWidget();
}

void ImageEditWidget::HandleRequest() {
  emit SendImage(&image_);
}

void ImageEditWidget::UpdateWidget() {
  int zoom = pApp->options()->zoom();

  QSize image_size = image_.size().scaled(image_.width()*zoom,image_.height()*zoom,Qt::KeepAspectRatio);

  this->setFixedSize(image_size);
  update();
}

