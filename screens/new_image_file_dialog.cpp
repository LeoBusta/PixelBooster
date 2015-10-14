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

#include "new_image_file_dialog.h"
#include "ui_new_image_file_dialog.h"

#include <QRegularExpression>

#include "utils/debug.h"
#include "application/pixel_booster.h"

const QSize kPresetOptions[] = {
  QSize(16,16),
  QSize(32,32),
  QSize(256,256),
  QSize(320,240),
  QSize(640,480),
  QSize(800,600)
};

const QPair<QImage::Format,QString> kFormatOptions[] = {
  // TODO(ricardo) fix the program using 8 bit images issue.
  //{QImage::Format_Indexed8,"8 bit indexed"},
  {QImage::Format_ARGB32_Premultiplied, "32 bit"}
};

NewImageFileDialog::NewImageFileDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::NewImageFileDialog),
  selected_size_(kPresetOptions[0]),
  selected_format_(kFormatOptions[0].first){
  ui->setupUi(this);

  for( QSize s : kPresetOptions ) {
    ui->preset_comboBox->addItem(QString("%1 x %2").arg(s.width()).arg(s.height()));
  }

  for( auto f : kFormatOptions ) {
    ui->format_comboBox->addItem(f.second);
  }

  QObject::connect(ui->preset_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(UpdatePresetValues(int)));
  QObject::connect(ui->width_spinBox,SIGNAL(valueChanged(int)),this,SLOT(UpdateWidthValue(int)));
  QObject::connect(ui->height_spinBox,SIGNAL(valueChanged(int)),this,SLOT(UpdateHeightValue(int)));
  QObject::connect(ui->format_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(UpdateFormatValue(int)));

  QSize new_image_size = pApp->options()->new_image_size();
  ui->width_spinBox->setValue(new_image_size.width());
  ui->height_spinBox->setValue(new_image_size.height());

  QObject::connect(this,SIGNAL(accepted()),this,SLOT(UpdateGlobalNewImageSize()));
}

NewImageFileDialog::~NewImageFileDialog() {
  delete ui;
}

QSize NewImageFileDialog::selected_size() const {
  return selected_size_;
}

QImage::Format NewImageFileDialog::selected_format() const {
  return selected_format_;
}

void NewImageFileDialog::UpdatePresetValues(int index) {
  if(index == 0){
    ui->width_spinBox->setEnabled(true);
    ui->height_spinBox->setEnabled(true);
    return;
  }

  ui->width_spinBox->setEnabled(false);
  ui->height_spinBox->setEnabled(false);

  QString label = ui->preset_comboBox->currentText();

  QRegularExpression reg("(\\d+) x (\\d+)");
  QRegularExpressionMatch m = reg.match(label);

  QStringList caps = m.capturedTexts();

  if(caps.size()==3){
    ui->width_spinBox->setValue(caps[1].toInt());
    ui->height_spinBox->setValue(caps[2].toInt());
  }
}

void NewImageFileDialog::UpdateWidthValue(int w) {
  selected_size_.setWidth(w);
}

void NewImageFileDialog::UpdateHeightValue(int h) {
  selected_size_.setHeight(h);
}

void NewImageFileDialog::UpdateFormatValue(int f) {
  selected_format_ = kFormatOptions[f].first;
}

void NewImageFileDialog::UpdateGlobalNewImageSize() {
  pApp->options()->set_new_image_size(selected_size_);
}
