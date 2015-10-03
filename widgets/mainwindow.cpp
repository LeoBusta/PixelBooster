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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSignalMapper>

#include "utils/debug.h"
#include "logic/action_handler.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  action_handler_(new ActionHandler(this)){
  ui->setupUi(this);

  ConnectActions();
}

MainWindow::~MainWindow() {
  delete ui;
}

QMdiArea *MainWindow::mdi_area() const
{
  return ui->image_mdi_area_;
}

void MainWindow::ConnectActions() {
  // File Actions
  QObject::connect(ui->actionNew,SIGNAL(triggered(bool)),action_handler_,SLOT(NewFile()));
  QObject::connect(ui->actionOpen,SIGNAL(triggered(bool)),action_handler_,SLOT(OpenFile()));

  // Translation Actions
  QObject::connect(ui->actionPT_BR,SIGNAL(triggered(bool)),action_handler_,SLOT(TranslatePT_BR()));
  QObject::connect(ui->actionEN_US,SIGNAL(triggered(bool)),action_handler_,SLOT(TranslateEN_US()));
}

void MainWindow::changeEvent(QEvent *event) {
  if(event->type() == QEvent::LanguageChange){
    ui->retranslateUi(this);
  }
}
