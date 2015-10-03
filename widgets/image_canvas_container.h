#ifndef IMAGE_CANVAS_CONTAINER_H
#define IMAGE_CANVAS_CONTAINER_H

#include <QScrollArea>

namespace Ui {
class ImageCanvasContainer;
}

class ImageCanvasContainer : public QScrollArea
{
  Q_OBJECT

public:
  explicit ImageCanvasContainer(QWidget *parent = 0);
  ~ImageCanvasContainer();

private:
  Ui::ImageCanvasContainer *ui;
};

#endif // IMAGE_CANVAS_CONTAINER_H
