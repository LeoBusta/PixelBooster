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

#ifndef IMAGE_CANVAS_CONTAINER_H
#define IMAGE_CANVAS_CONTAINER_H

#include <QScrollArea>

namespace Ui {
class ImageCanvasContainer;
}

class ImageCanvasWidget;
class ImageEditWidget;

/*!
 * \brief The ImageCanvasContainer class
 */
class ImageCanvasContainer : public QScrollArea {
  Q_OBJECT
public:
  explicit ImageCanvasContainer(const QImage &image, const QString &file_name, QWidget *parent = 0);
  ~ImageCanvasContainer();

  void SetAsActive(ImageEditWidget * edit_widget);
  void RemoveAsActive(ImageEditWidget *edit_widget);
private:
  Ui::ImageCanvasContainer *ui;

  QString file_name_;
};

#endif // IMAGE_CANVAS_CONTAINER_H
