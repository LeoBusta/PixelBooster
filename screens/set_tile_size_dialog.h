#ifndef SET_TILE_SIZE_DIALOG_H
#define SET_TILE_SIZE_DIALOG_H

#include <QDialog>

namespace Ui {
class SetTileSizeDialog;
}

class SetTileSizeDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SetTileSizeDialog(QWidget *parent = 0);
  ~SetTileSizeDialog();

private:
  Ui::SetTileSizeDialog *ui;

private slots:
  void UpdateGlobalValues();
};

#endif // SET_TILE_SIZE_DIALOG_H
