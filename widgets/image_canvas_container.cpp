#include "image_canvas_container.h"
#include "ui_image_canvas_container.h"

ImageCanvasContainer::ImageCanvasContainer(QWidget *parent) :
  QScrollArea(parent),
  ui(new Ui::ImageCanvasContainer) {
  ui->setupUi(this);
}

ImageCanvasContainer::~ImageCanvasContainer() {
  delete ui;
}
