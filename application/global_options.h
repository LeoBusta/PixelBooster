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

#ifndef GLOBAL_OPTIONS_H
#define GLOBAL_OPTIONS_H

#include <QSize>
#include <QRect>

/*!
 * \brief The GlobalOptions class
 */
class GlobalOptions {
public:
  GlobalOptions();

  QSize cursor_size() const;
  void set_cursor_size(const QSize &size);

  QRect selection() const;
  void set_selection(const QRect &selection);
  void MoveSelection(const QPoint &top_left);

private:
  QSize cursor_size_;
  QRect selection_;
};

#endif // GLOBAL_OPTIONS_H