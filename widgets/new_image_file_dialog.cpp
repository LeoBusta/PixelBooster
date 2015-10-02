#include "new_image_file_dialog.h"
#include "ui_new_image_file_dialog.h"

NewImageFileDialog::NewImageFileDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::New_Image_File_Dialog)
{
  ui->setupUi(this);
}

NewImageFileDialog::~NewImageFileDialog()
{
  delete ui;
}
