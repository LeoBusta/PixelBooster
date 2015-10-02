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

  QSize selected_size() const;
  QImage::Format selected_format() const;

private:
  Ui::NewImageFileDialog *ui;

  QSize selected_size_;
  QImage::Format selected_format_;
private slots:
  void UpdatePresetValues(int index);
  void UpdateWidthValue(int w);
  void UpdateHeightValue(int h);
  void UpdateFormatValue(int f);
};

#endif // NEW_IMAGE_FILE_DIALOG_H
