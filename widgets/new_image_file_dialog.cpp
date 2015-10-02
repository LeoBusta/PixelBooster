#include "new_image_file_dialog.h"
#include "ui_new_image_file_dialog.h"

#include <QRegularExpression>

#include "utils/debug.h"

const int kPresetOptions[][2] = {
  {16,16},
  {32,32},
  {256,256},
  {320,240},
  {640,480},
  {800,600}
};

const QVector< QPair<QImage::Format,QString> > kFormatOptions = {
  {QImage::Format_Indexed8,"8 bit indexed"},
  {QImage::Format_ARGB32, "32 bit"}
};

NewImageFileDialog::NewImageFileDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::NewImageFileDialog) {
  ui->setupUi(this);

  for( auto x : kPresetOptions ) {
    ui->preset_comboBox->addItem(QString("%1 x %2").arg(x[0]).arg(x[1]));
  }

  for( auto x : kFormatOptions ) {
    ui->format_comboBox->addItem(x.second);
  }

  QObject::connect(ui->preset_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(UpdatePresetValues(int)));
  QObject::connect(ui->width_spinBox,SIGNAL(valueChanged(int)),this,SLOT(UpdateWidthValue(int)));
  QObject::connect(ui->height_spinBox,SIGNAL(valueChanged(int)),this,SLOT(UpdateHeightValue(int)));
  QObject::connect(ui->format_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(UpdateFormatValue(int)));
}

NewImageFileDialog::~NewImageFileDialog() {
  delete ui;
}

QSize NewImageFileDialog::selected_size() const {
  return selected_size_;
}

QImage::Format NewImageFileDialog::selected_format() const {
  return selected_format_;
}

void NewImageFileDialog::UpdatePresetValues(int index) {
  if(index == 0){
    ui->width_spinBox->setEnabled(true);
    ui->height_spinBox->setEnabled(true);
    return;
  }

  ui->width_spinBox->setEnabled(false);
  ui->height_spinBox->setEnabled(false);

  QString label = ui->preset_comboBox->currentText();

  QRegularExpression reg("(\\d+) x (\\d+)");
  QRegularExpressionMatch m = reg.match(label);

  QStringList caps = m.capturedTexts();

  if(caps.size()==3){
    ui->width_spinBox->setValue(caps[1].toInt());
    ui->height_spinBox->setValue(caps[2].toInt());
  }
}

void NewImageFileDialog::UpdateWidthValue(int w) {
  selected_size_.setWidth(w);
}

void NewImageFileDialog::UpdateHeightValue(int h) {
  selected_size_.setHeight(h);
}

void NewImageFileDialog::UpdateFormatValue(int f) {
  selected_format_ = kFormatOptions[f].first;
}
