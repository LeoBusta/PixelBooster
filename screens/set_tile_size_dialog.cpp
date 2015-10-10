#include "set_tile_size_dialog.h"
#include "ui_set_tile_size_dialog.h"

#include "application/pixel_booster.h"
#include "utils/debug.h"

SetTileSizeDialog::SetTileSizeDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SetTileSizeDialog) {
  ui->setupUi(this);

  QSize cursor_size = pApp->options()->cursor_size();
  DEBUG_MSG("Cursor size" << cursor_size);
  ui->tile_width_spinBox->setValue(cursor_size.width());
  ui->tile_height_spinBox->setValue(cursor_size.height());

  QObject::connect(this,SIGNAL(accepted()),this,SLOT(UpdateGlobalValues()));
}

SetTileSizeDialog::~SetTileSizeDialog() {
  delete ui;
}

void SetTileSizeDialog::UpdateGlobalValues() {
  pApp->options()->set_cursor_size(QSize(ui->tile_width_spinBox->value(),ui->tile_height_spinBox->value()));
}
