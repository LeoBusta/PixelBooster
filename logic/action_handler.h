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

#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include <QObject>

class GlobalOptions;
class MainWindow;

/*!
 * \brief The ActionHandler class
 */
class ActionHandler: public QObject {
  Q_OBJECT
public:
  explicit ActionHandler(QObject * parent);
  virtual ~ActionHandler();

public slots:
  // File Actions
  void NewFile() const;
  void OpenFile() const;
  void SaveFile() const;

  // Interface Actions
  void About() const;
  void TileSize() const;
  void ToggleTransparency(bool transparency) const;
  void Zoom(int zoom);

  // Language Actions
  void TranslatePT_BR() const;
  void TranslateEN_US() const;

signals:
  void UpdateEditArea();

private:
  GlobalOptions * options_cache_;
  MainWindow * window_cache_;

  void CreateImageCanvas(const QImage &image, const QString &file_name) const;
};

#endif // ACTION_HANDLER_H
