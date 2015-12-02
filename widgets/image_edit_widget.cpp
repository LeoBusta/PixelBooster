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
#include "logic/action_handler.h"
#include "screens/main_window.h"

ImageEditWidget::ImageEditWidget(QWidget *parent)
  : QWidget(parent),
    left_button_down_(false),
    right_button_down_(false) {
  setMouseTracking(true);
  image_ = QImage(0,0,QImage::Format_ARGB32_Premultiplied);
  options_cache_ = pApp->options();
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

  //setStatusTip(QString("Cursor x: %1 y: %2").arg(pos.x()).arg(pos.y()));

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
    right_button_down_ = true;
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
    right_button_down_ = false;
    break;
  default:
    break;
  }
}

void ImageEditWidget::ToolAction(const QPoint &pos) {
  int zoom = options_cache_->zoom();
  QPoint img_pos = QPoint(pos.x()/zoom,pos.y()/zoom);

  switch (options_cache_->tool()) {
  case TOOL_PENCIL:
    if(left_button_down_ && cursor_.isValid()){
      image_.setPixel(img_pos,options_cache_->main_color().rgba());
    }else if(right_button_down_ && cursor_.isValid()){
      pApp->main_window()->action_handler()->SetMainColor(image_.pixel(img_pos));
    }
    break;
  case TOOL_FILL:
    if(left_button_down_ && cursor_.isValid()){
      Fill(img_pos, options_cache_->main_color());
    }else if(right_button_down_ && cursor_.isValid()){
      pApp->main_window()->action_handler()->SetMainColor(image_.pixel(img_pos));
    }
    break;
  default:
    break;
  }
}

void ImageEditWidget::Fill(const QPoint &seed_pos, const QColor &color) {
  QRgb new_color = color.rgba();
  QRgb old_color = image_.pixel(seed_pos);
  QList<QPoint> to_do_list = {seed_pos};

  QVector<QPoint> expansion = {
    QPoint(1,0),
    QPoint(0,1),
    QPoint(-1,0),
    QPoint(0,-1)
  };

  image_.setPixel(seed_pos,new_color);

  while(!to_do_list.isEmpty()){
    //DEBUG_MSG(to_do_list.length());
    QPoint target = to_do_list.takeFirst();

    for(QPoint e : expansion){
      QPoint new_target = target+e;
      //DEBUG_MSG(new_target);
      if(image_.rect().contains(new_target) && image_.pixel(new_target) == old_color){
        to_do_list.push_back(new_target);
        image_.setPixel(new_target,new_color);
      }
    }
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

