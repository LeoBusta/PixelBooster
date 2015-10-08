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

#include <QMdiSubWindow>

#include "utils/debug.h"
#include "logic/action_handler.h"
#include "widgets/image_canvas_container.h"
#include "application/pixel_booster.h"

#include <QSettings>

const QString kConfigFileName = "config.ini";
const QString kConfigGroupState = "State";
const QString kConfigGroupWindow = "Window";
const QString kConfigWindowState = "WindowState";
const QString kConfigWindowGeometry = "WindowGeometry";
const QRect kConfigDefaultWindowGeometry = QRect(0,10,800,600);

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  action_handler_(new ActionHandler(this)),
  current_canvas_container_(NULL){
  ui->setupUi(this);

  ConnectActions();
  ConnectWidgets();

  LoadSettings();
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

  // Interface Actions
  QObject::connect(ui->actionAbout,SIGNAL(triggered(bool)),action_handler_,SLOT(About()));

  // Translation Actions
  QObject::connect(ui->actionPT_BR,SIGNAL(triggered(bool)),action_handler_,SLOT(TranslatePT_BR()));
  QObject::connect(ui->actionEN_US,SIGNAL(triggered(bool)),action_handler_,SLOT(TranslateEN_US()));
}

void MainWindow::ConnectWidgets() {
  QObject::connect(ui->image_mdi_area_,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(CurrentWindowChanged(QMdiSubWindow*)));
}

void MainWindow::SaveSettings() {
  QSettings settings(kConfigFileName,QSettings::IniFormat);

  settings.beginGroup(kConfigGroupState);
  pApp->options()->SaveState();
  settings.endGroup();

  settings.beginGroup(kConfigGroupWindow);
  settings.setValue(kConfigWindowGeometry,this->geometry());
  settings.setValue(kConfigWindowState,this->saveState());
  settings.endGroup();
}

void MainWindow::LoadSettings() {
  QSettings settings(kConfigFileName,QSettings::IniFormat);

  settings.beginGroup(kConfigGroupState);
  pApp->options()->LoadState();
  settings.endGroup();

  settings.beginGroup(kConfigGroupWindow);
  setGeometry(settings.value(kConfigWindowGeometry,kConfigDefaultWindowGeometry).toRect());
  restoreState(settings.value(kConfigWindowState).toByteArray());
  settings.endGroup();
}

void MainWindow::changeEvent(QEvent *event) {
  if(event->type() == QEvent::LanguageChange){
    ui->retranslateUi(this);
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  SaveSettings();
}

void MainWindow::CurrentWindowChanged(QMdiSubWindow *w) {
  if(NULL != current_canvas_container_) {
    current_canvas_container_->RemoveAsActive(ui->edit_widget);
    current_canvas_container_ = NULL;
  }

  if(NULL != w) {
    current_canvas_container_ = dynamic_cast<ImageCanvasContainer*>(w->widget());
    if(NULL != current_canvas_container_){
      current_canvas_container_->SetAsActive(ui->edit_widget);
    }
  }
}
