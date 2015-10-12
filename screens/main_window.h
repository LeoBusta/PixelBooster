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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QMdiArea;
class QMdiSubWindow;
class ActionHandler;
class ImageCanvasContainer;

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  QMdiArea * mdi_area() const;
  ImageCanvasContainer * current_canvas_container();
private:
  Ui::MainWindow *ui;
  ActionHandler * action_handler_;
  ImageCanvasContainer * current_canvas_container_;

  void ConnectActions();
  void ConnectWidgets();

  void SaveSettings();
  void LoadSettings();

  void changeEvent(QEvent *event);
  void closeEvent(QCloseEvent *event);

private slots:
  void CurrentWindowChanged(QMdiSubWindow *w);
};

#endif // MAINWINDOW_H
