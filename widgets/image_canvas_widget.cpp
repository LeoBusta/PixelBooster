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
#include "application/pixel_booster.h"

#include <QPainter>
#include <QMouseEvent>

ImageCanvasWidget::ImageCanvasWidget(QWidget *parent)
  : QWidget(parent),
    anchor_down_(false){
  setMouseTracking(true);
}

ImageCanvasWidget::~ImageCanvasWidget() {

}

void ImageCanvasWidget::SetImage(const QImage &image) {
  if(image.isNull()){
    DEBUG_MSG("image is null");
    return;
  }

  if( image.format() != QImage::Format_Indexed8 ){
    DEBUG_MSG("format not 8bit");
    image_ = image;
  }
  DEBUG_MSG("format not 8bit");
  this->setFixedSize(image_.size());
}

void ImageCanvasWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  DEBUG_MSG("is null?" << image_.isNull());
  if(image_.isNull()) return;
  painter.drawImage(image_.rect(),image_);
}

void ImageCanvasWidget::mousePressEvent(QMouseEvent *event) {
  if(event->button() == Qt::RightButton){
    anchor_down_ = true;
    anchor_ = PosToGrid(event->pos());
    selection_ = anchor_;
    update();
  }
}

void ImageCanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
  anchor_down_ = false;
  if(event->button() == Qt::RightButton){
    //emit SendPick(image_.copy(selection_));
  }else{
    //emit GetPickRequest();
  }
}

void ImageCanvasWidget::mouseMoveEvent(QMouseEvent *event) {
  if(anchor_down_){
    QRect current_cursor = PosToGrid(event->pos());

    selection_ = current_cursor.united(anchor_);
  }else{
    selection_.moveTopLeft( PosToGrid(event->pos()).topLeft() );
  }
  update();
}

QRect ImageCanvasWidget::PosToGrid(const QPoint &pos) const {
  QSize cursor_size = pApp->options()->cursor_size();
  QPoint top_left = QPoint(
                      (pos.x()/cursor_size.width())*cursor_size.width(),
                      (pos.y()/cursor_size.height())*cursor_size.height()
                      );

  return QRect(top_left,cursor_size);
}

