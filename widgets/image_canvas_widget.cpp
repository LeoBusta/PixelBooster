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

QVector<ImageCanvasWidget*> ImageCanvasWidget::open_canvas_;

ImageCanvasWidget::ImageCanvasWidget(QWidget *parent)
  : QWidget(parent),
    anchor_down_(false),
    active_(false),
    options_cache_(pApp->options()),
    saved_state_(true){
  setMouseTracking(true);

  open_canvas_.push_back(this);
}

ImageCanvasWidget::~ImageCanvasWidget() {
  open_canvas_.removeOne(this);
}

void ImageCanvasWidget::SetImage(const QImage &image) {
  if(image.isNull()){
    return;
  }

  if( image.format() != QImage::Format_Indexed8 ){
    image_ = image;
  }
  this->setFixedSize(image_.size());
}

void ImageCanvasWidget::set_active(bool active) {
  active_ = active;
}

QVector<ImageCanvasWidget *> *ImageCanvasWidget::open_canvas() {
  return &open_canvas_;
}

bool ImageCanvasWidget::saved_state() const {
  return saved_state_;
}

void ImageCanvasWidget::save_state() {
  saved_state_ = true;
  emit UnsavedChanges(!saved_state_);
}

void ImageCanvasWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  if(image_.isNull()) return;
  painter.drawImage(image_.rect(),image_);

  if(active_){
    QRect selection = options_cache_->selection().adjusted(0,0,-1,-1);

    painter.setPen(Qt::yellow);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(selection);

    QVector<qreal> dashes = {2,2};

    QPen pen;
    pen.setColor(Qt::red);
    pen.setDashPattern(dashes);
    painter.setPen(pen);
    painter.drawRect(selection);
  }
}

void ImageCanvasWidget::mousePressEvent(QMouseEvent *event) {
  if(event->button() == Qt::RightButton){
    options_cache_->CleanCursorShift();
    anchor_down_ = true;
    anchor_ = options_cache_->PosToGrid(event->pos());
    options_cache_->set_selection( anchor_ );
    update();
  }
}

void ImageCanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
  anchor_down_ = false;
  if(event->button() == Qt::RightButton){
    // Get image from the canvas
    emit SendImage(&image_.copy(options_cache_->selection()));
    options_cache_->UpdateCursorShift();
  }else if(event->button() == Qt::LeftButton){
    // Set image back to the canvas
    saved_state_ = false;
    emit UnsavedChanges(!saved_state_);
    emit RequestImage();
  }
}

void ImageCanvasWidget::mouseMoveEvent(QMouseEvent *event) {
  QPoint pos = event->pos();
  if(!rect().contains(event->pos())){
    pos.setX( qMin(rect().right()-1,qMax(rect().left(),pos.x())) );
    pos.setY( qMin(rect().bottom()-1,qMax(rect().top(),pos.y())) );
  }

  QRect current_cursor = options_cache_->PosToGrid(pos);
  if(anchor_down_){
    options_cache_->set_selection( current_cursor.united(anchor_) );
  }else{
    options_cache_->MoveSelection( current_cursor.center() );
  }
  update();
}

void ImageCanvasWidget::ReceiveImage(QImage * image) {
  if(NULL == image || image->isNull()){
    return;
  }
  QPainter painter(&image_);

  if(!options_cache_->transparency_enabled()){
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.eraseRect(options_cache_->selection());
  }
  painter.drawImage(options_cache_->selection(),*image);

  update();
}

