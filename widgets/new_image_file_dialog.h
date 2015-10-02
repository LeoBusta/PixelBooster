#ifndef NEW_IMAGE_FILE_DIALOG_H
#define NEW_IMAGE_FILE_DIALOG_H

#include <QDialog>

namespace Ui {
class NewImageFileDialog;
}

class NewImageFileDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewImageFileDialog(QWidget *parent = 0);
  ~NewImageFileDialog();

private:
  Ui::NewImageFileDialog *ui;

  QSize selected_size_;
  int selected_format_;
private slots:
  void UpdatePresetValues(int index);
  void UpdateWidthValue(int w);
  void UpdateHeightValue(int h);
};

#endif // NEW_IMAGE_FILE_DIALOG_H
