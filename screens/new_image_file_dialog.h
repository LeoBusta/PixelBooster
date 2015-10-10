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

#ifndef NEW_IMAGE_FILE_DIALOG_H
#define NEW_IMAGE_FILE_DIALOG_H

#include <QDialog>

namespace Ui {
class NewImageFileDialog;
}

/*!
 * \brief The NewImageFileDialog class
 */
class NewImageFileDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewImageFileDialog(QWidget *parent = 0);
  ~NewImageFileDialog();

  QSize selected_size() const;
  QImage::Format selected_format() const;

private:
  Ui::NewImageFileDialog *ui;

  QSize selected_size_;
  QImage::Format selected_format_;
private slots:
  void UpdatePresetValues(int index);
  void UpdateWidthValue(int w);
  void UpdateHeightValue(int h);
  void UpdateFormatValue(int f);
  void UpdateGlobalNewImageSize();
};

#endif // NEW_IMAGE_FILE_DIALOG_H
