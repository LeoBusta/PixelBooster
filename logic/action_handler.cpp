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
#include "screens/mainwindow.h"
#include "screens/new_image_file_dialog.h"
#include "screens/about_dialog.h"


#include <QFileDialog>
#include <QMdiArea>
#include <QLabel>

ActionHandler::ActionHandler(QObject *parent)
  : QObject(parent) {

}

ActionHandler::~ActionHandler() {

}

void ActionHandler::NewFile() const {
  NewImageFileDialog * image_file_dialog = new NewImageFileDialog(pApp->main_window());
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
  CreateImageCanvas(image);

  delete image_file_dialog;
  return;
}

void ActionHandler::OpenFile() const {
  QStringList file_names = QFileDialog::getOpenFileNames(pApp->main_window(),"Open Files",".","Images (*.png *.xpm *.jpg)");

  for( QString file_name : file_names ){
    if(!file_name.isEmpty()){
      QImage image(file_name);
      if(!image.isNull()){
        CreateImageCanvas(image);
      }
    }
  }
}

void ActionHandler::About() const {
  AboutDialog * about_dialog = new AboutDialog(pApp->main_window());
  about_dialog->exec();
  delete about_dialog;
}

void ActionHandler::TranslatePT_BR() const {
  pApp->Translate("pt_br");
}

void ActionHandler::TranslateEN_US() const {
  pApp->Translate("en_us");
}

void ActionHandler::CreateImageCanvas(const QImage &image) const {
  ImageCanvasContainer * canvas_container = new ImageCanvasContainer(image);
  QMdiArea * mdi = dynamic_cast<MainWindow*>(pApp->main_window())->mdi_area();
  mdi->addSubWindow(canvas_container);
  canvas_container->show();
}
