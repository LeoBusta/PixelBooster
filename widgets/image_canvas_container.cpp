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

#include "image_canvas_container.h"
#include "ui_image_canvas_container.h"

#include "widgets/image_edit_widget.h"
#include "utils/debug.h"

ImageCanvasContainer::ImageCanvasContainer(const QImage &image, QWidget *parent) :
  QScrollArea(parent),
  ui(new Ui::ImageCanvasContainer){
  ui->setupUi(this);
  ui->image_canvas_widget_->SetImage(image);
}

ImageCanvasContainer::~ImageCanvasContainer() {
  delete ui;
}

void ImageCanvasContainer::SetAsActive(ImageEditWidget * edit_widget) {
  QObject::connect(ui->image_canvas_widget_,SIGNAL(SendImage(QImage*)),edit_widget,SLOT(GetImage(QImage*)));
  QObject::connect(ui->image_canvas_widget_,SIGNAL(RequestImage()),edit_widget,SLOT(HandleRequest()));
  QObject::connect(edit_widget,SIGNAL(SendImage(QImage*)),ui->image_canvas_widget_,SLOT(ReceiveImage(QImage*)));
  ui->image_canvas_widget_->set_active(true);
}

void ImageCanvasContainer::RemoveAsActive(ImageEditWidget * edit_widget) {
  QObject::disconnect(ui->image_canvas_widget_,0,edit_widget,0);
  QObject::disconnect(edit_widget,0,ui->image_canvas_widget_,0);
  ui->image_canvas_widget_->set_active(false);
}
