#ifndef PIXEL_BOOSTER_H
#define PIXEL_BOOSTER_H

#include <QApplication>

class MainWindow;

class PixelBooster : public QApplication
{
public:
  PixelBooster(int argc, char *argv[]);

private:
  MainWindow * main_window_;
};

#endif // PIXEL_BOOSTER_H
