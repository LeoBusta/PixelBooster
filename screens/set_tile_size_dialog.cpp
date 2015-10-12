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

#include "set_tile_size_dialog.h"
#include "ui_set_tile_size_dialog.h"

#include "application/pixel_booster.h"
#include "utils/debug.h"

SetTileSizeDialog::SetTileSizeDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SetTileSizeDialog) {
  ui->setupUi(this);

  QSize cursor_size = pApp->options()->cursor_size();
  DEBUG_MSG("Cursor size" << cursor_size);
  ui->tile_width_spinBox->setValue(cursor_size.width());
  ui->tile_height_spinBox->setValue(cursor_size.height());

  QObject::connect(this,SIGNAL(accepted()),this,SLOT(UpdateGlobalValues()));
}

SetTileSizeDialog::~SetTileSizeDialog() {
  delete ui;
}

void SetTileSizeDialog::UpdateGlobalValues() {
  pApp->options()->set_cursor_size(QSize(ui->tile_width_spinBox->value(),ui->tile_height_spinBox->value()));
}
