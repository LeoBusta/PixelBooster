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

#include "about_dialog.h"
#include "ui_about_dialog.h"

#include "resources/version.h"

AboutDialog::AboutDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AboutDialog)
{
  ui->setupUi(this);

  ui->version_label->setText(kVersionString);
  ui->website_label->setTextFormat(Qt::RichText);
  ui->website_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
  ui->website_label->setOpenExternalLinks(true);
  ui->website_label->setText("<a href=\"http://pixel.busta.com.br\">pixel.busta.com.br</a>");
}

AboutDialog::~AboutDialog()
{
  delete ui;
}
