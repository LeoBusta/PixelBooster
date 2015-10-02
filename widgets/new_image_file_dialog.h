#ifndef NEW_IMAGE_FILE_DIALOG_H
#define NEW_IMAGE_FILE_DIALOG_H

#include <QDialog>

namespace Ui {
class New_Image_File_Dialog;
}

class NewImageFileDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewImageFileDialog(QWidget *parent = 0);
  ~NewImageFileDialog();

private:
  Ui::New_Image_File_Dialog *ui;
};

#endif // NEW_IMAGE_FILE_DIALOG_H
