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

GlobalOptions::GlobalOptions() {
  cursor_size_ = QSize(32,32);
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

void GlobalOptions::MoveSelection(const QPoint &center) {
  selection_.moveCenter(center);
}

