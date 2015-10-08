#include "set_tile_size_dialog.h"
#include "ui_set_tile_size_dialog.h"

Set_Tile_Size_Dialog::Set_Tile_Size_Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Set_Tile_Size_Dialog)
{
  ui->setupUi(this);
}

Set_Tile_Size_Dialog::~Set_Tile_Size_Dialog()
{
  delete ui;
}
