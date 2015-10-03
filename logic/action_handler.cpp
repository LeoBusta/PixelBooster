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

#include "widgets/new_image_file_dialog.h"
#include "application/pixel_booster.h"
#include "utils/debug.h"
#include "widgets/image_canvas_container.h"
#include "widgets/mainwindow.h"
#include "widgets/image_canvas_widget.h"

#include <QFileDialog>
#include <QMdiArea>
#include <QLabel>

ActionHandler::ActionHandler(QObject *parent)
  : QObject(parent) {

}

ActionHandler::~ActionHandler() {

}

void ActionHandler::TranslatePT_BR() const {
  pApp->Translate("pt_br");
}

void ActionHandler::TranslateEN_US() const {
  pApp->Translate("en_us");
}

void ActionHandler::NewFile() const {
  NewImageFileDialog * image_file_dialog = new NewImageFileDialog(pApp->main_window());
  image_file_dialog->exec();
  delete image_file_dialog;

  CreateImageCanvas();
}

void ActionHandler::OpenFile() const {
  QStringList file_names = QFileDialog::getOpenFileNames(pApp->main_window(),"Open Files",".");

  for( QString file_name : file_names ){
    DEBUG_MSG(file_name);
  }

  CreateImageCanvas();
}

void ActionHandler::CreateImageCanvas() const {
  ImageCanvasWidget * image_canvas = new ImageCanvasWidget;
  ImageCanvasContainer * canvas_container = new ImageCanvasContainer(image_canvas);
  QMdiArea * mdi = dynamic_cast<MainWindow*>(pApp->main_window())->mdi_area();
  mdi->addSubWindow(canvas_container);
  canvas_container->show();
}
