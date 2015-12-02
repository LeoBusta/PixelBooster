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

#ifndef IMAGE_EDIT_WIDGET_H
#define IMAGE_EDIT_WIDGET_H

#include <QWidget>
#include <QImage>

class GlobalOptions;

/*!
 * \brief The ImageEditWidget class
 */
class ImageEditWidget : public QWidget
{
  Q_OBJECT
public:
  explicit ImageEditWidget(QWidget *parent = 0);

  QImage image_;

  void Clear(const QSize &size);
protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void leaveEvent(QEvent *event);
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
private:
  QRect cursor_;
  bool left_button_down_;
  bool right_button_down_;

  GlobalOptions * options_cache_;

  void ToolAction(const QPoint &pos);
signals:
  void SendImage(QImage*);
public slots:
  void GetImage(QImage*image);
  void HandleRequest();
  void UpdateWidget();
};

#endif // IMAGE_EDIT_WIDGET_H
