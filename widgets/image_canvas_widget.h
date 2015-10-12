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

#ifndef IMAGE_CANVAS_WIDGET_H
#define IMAGE_CANVAS_WIDGET_H

#include <QWidget>

class GlobalOptions;

/*!
 * \brief The ImageCanvasWidget class
 */
class ImageCanvasWidget : public QWidget {
  Q_OBJECT
public:
  explicit ImageCanvasWidget(QWidget *parent = 0);
  virtual ~ImageCanvasWidget();

  void SetImage(const QImage &image);

  void set_active(bool active);
protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);

private:
  GlobalOptions * options_cache_;

  bool active_;
  bool anchor_down_;

  QImage image_;
  QRect anchor_;
  //QRect cursor_;
signals:
  void SendImage(QImage*);
  void RequestImage();

private slots:
  void ReceiveImage(QImage*image);
};

#endif // IMAGE_CANVAS_WIDGET_H
