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

#include "global_options.h"

#include <QSettings>

#include "utils/debug.h"

const QString kStateCursorSize = "CursorSize";
const QSize kStateCursorSizeDefault = QSize(32,32);
const QString kStateNewImageSize = "NewImageSize";
const QSize kStateNewImageSizeDefault = QSize(256,256);
const QString kStateTransparency = "TransparencyEnabled";
const bool kStateTransparencyDefault = false;

GlobalOptions::GlobalOptions():
  vertical_shift_(false),
  horizontal_shift_(false),
  zoom_(1){
}

QSize GlobalOptions::cursor_size() const {
  return cursor_size_;
}

void GlobalOptions::set_cursor_size(const QSize &size) {
  cursor_size_ = size;
}

QRect GlobalOptions::selection() const {
  return selection_;
}

void GlobalOptions::set_selection(const QRect &selection) {
  selection_ = selection;
}

void GlobalOptions::UpdateCursorShift() {
  horizontal_shift_ = ((selection_.width()/cursor_size().width())%2==0);
  vertical_shift_ = ((selection_.height()/cursor_size().height())%2==0);
}

void GlobalOptions::CleanCursorShift()
{
  horizontal_shift_ = false;
  vertical_shift_ = false;
}


void GlobalOptions::MoveSelection(const QPoint &center) {
  selection_.moveCenter(center);
}

QRect GlobalOptions::PosToGrid(const QPoint &pos) const {
  int x = (horizontal_shift_?cursor_size_.width()/2:0);
  int y = (vertical_shift_?cursor_size_.height()/2:0);
  QPoint top_left = QPoint(
        ((pos.x()+x)/cursor_size_.width())*cursor_size_.width() -x,
        ((pos.y()+y)/cursor_size_.height())*cursor_size_.height() -y
        );

  return QRect(top_left,cursor_size_);
}

QSize GlobalOptions::new_image_size() const {
  return new_image_size_;
}

void GlobalOptions::set_new_image_size(const QSize &size) {
  new_image_size_ = size;
}

bool GlobalOptions::transparency_enabled() const {
  return transparency_enabled_;
}

void GlobalOptions::set_transparency_enabled(bool transparency) {
  transparency_enabled_ = transparency;
}

int GlobalOptions::zoom() const {
  return zoom_;
}

void GlobalOptions::set_zoom(int zoom) {
  zoom_level_ = zoom;
  zoom_ = pow(2,zoom);
}

void GlobalOptions::SaveState(QSettings * settings) const {
  settings->setValue(kStateCursorSize,cursor_size_);
  settings->setValue(kStateNewImageSize,new_image_size_);
  settings->setValue(kStateTransparency,transparency_enabled_);
}

void GlobalOptions::LoadState(QSettings * settings) {
  cursor_size_ = settings->value(kStateCursorSize,kStateCursorSizeDefault).toSize();
  selection_.setSize(cursor_size_);
  selection_.setTopLeft(QPoint(0,0));
  new_image_size_ = settings->value(kStateNewImageSize,kStateNewImageSizeDefault).toSize();
  transparency_enabled_ = settings->value(kStateTransparency,kStateTransparencyDefault).toBool();
}

