#ifndef SET_TILE_SIZE_DIALOG_H
#define SET_TILE_SIZE_DIALOG_H

#include <QDialog>

namespace Ui {
class Set_Tile_Size_Dialog;
}

class Set_Tile_Size_Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Set_Tile_Size_Dialog(QWidget *parent = 0);
  ~Set_Tile_Size_Dialog();

private:
  Ui::Set_Tile_Size_Dialog *ui;
};

#endif // SET_TILE_SIZE_DIALOG_H
