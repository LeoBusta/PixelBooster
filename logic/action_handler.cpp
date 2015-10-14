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

#include "action_handler.h"

#include "application/pixel_booster.h"
#include "utils/debug.h"
#include "widgets/image_canvas_container.h"
#include "widgets/image_canvas_widget.h"
#include "screens/main_window.h"
#include "screens/new_image_file_dialog.h"
#include "screens/about_dialog.h"
#include "screens/set_tile_size_dialog.h"


#include <QFileDialog>
#include <QMdiArea>
#include <QLabel>
#include <QMdiSubWindow>
#include <QColorDialog>

const QString kTxtSelectMainColor = "Select Main Color";
const QString kTxtSelectAltColor = "Select Secondary Color";

ActionHandler::ActionHandler(QObject *parent)
  : QObject(parent),
    options_cache_(pApp->options()),
    window_cache_(dynamic_cast<MainWindow*>(parent)){
}

ActionHandler::~ActionHandler() {
}

void ActionHandler::NewFile() const {
  NewImageFileDialog * image_file_dialog = new NewImageFileDialog(window_cache_);
  int result = image_file_dialog->exec();

  // Check if the user canceled the new image creation.
  if(result != QFileDialog::Accepted){
    delete image_file_dialog;
    return;
  }

  // Gather information from the dialog to create the image.
  QSize size = image_file_dialog->selected_size();
  QImage::Format format = image_file_dialog->selected_format();

  QImage image(size,format);
  image.fill(Qt::white);
  CreateImageCanvas(image, "");

  delete image_file_dialog;
  return;
}

void ActionHandler::OpenFile() const {
  QStringList file_names = QFileDialog::getOpenFileNames(window_cache_,"Open Files",".","Images (*.png *.xpm *.jpg)");

  for( QString file_name : file_names ){
    if(!file_name.isEmpty()){
      QImage image(file_name);
      if(!image.isNull()){
        CreateImageCanvas(image,file_name);
      }
    }
  }
}

void ActionHandler::SaveFile() const {
  DEBUG_MSG("Should attempt to save all unsaved files");
}

void ActionHandler::About() const {
  AboutDialog * about_dialog = new AboutDialog(window_cache_);
  about_dialog->exec();
  delete about_dialog;
}

void ActionHandler::TileSize() const {
  SetTileSizeDialog * tile_dialog = new SetTileSizeDialog(window_cache_);
  tile_dialog->exec();
  delete tile_dialog;
}

void ActionHandler::ToggleTransparency(bool transparency) const {
  options_cache_->set_transparency_enabled(transparency);
}

void ActionHandler::Zoom(int zoom) const {
  options_cache_->set_zoom_level( zoom );
  emit UpdateEditArea();
}

void ActionHandler::OpenMainColorPick() const {
  QColor color = QColorDialog::getColor(options_cache_->main_color(),window_cache_,kTxtSelectMainColor,QColorDialog::ShowAlphaChannel);
  options_cache_->set_main_color(color);
  QWidget * color_widget = dynamic_cast<QWidget*>(sender());
  if(nullptr != color_widget){
    color_widget->setStyleSheet(QString("background-color: %1;").arg(color.name()));
  }
}

void ActionHandler::OpenAltColorPick() const {
  QColor color = QColorDialog::getColor(options_cache_->alt_color(),window_cache_,kTxtSelectAltColor,QColorDialog::ShowAlphaChannel);
  options_cache_->set_alt_color(color);
  QWidget * color_widget = dynamic_cast<QWidget*>(sender());
  if(nullptr != color_widget){
    color_widget->setStyleSheet(QString("background-color: %1;").arg(color.name()));
  }
}

void ActionHandler::TranslatePT_BR() const {
  pApp->Translate("pt_br");
}

void ActionHandler::TranslateEN_US() const {
  pApp->Translate("en_us");
}

void ActionHandler::CreateImageCanvas(const QImage &image, const QString &file_name) const {
  ImageCanvasContainer * canvas_container = new ImageCanvasContainer(image,file_name);
  QMdiArea * mdi = dynamic_cast<MainWindow*>(window_cache_)->mdi_area();
  QMdiSubWindow * w = mdi->addSubWindow(canvas_container);
  QSize size = image.size() + QSize(50,50);
  w->resize(size);
  w->show();
}
