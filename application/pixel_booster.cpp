#include "pixel_booster.h"

#include "widgets/mainwindow.h"

PixelBooster::PixelBooster(int argc, char * argv[])
  : QApplication(argc,argv),
    main_window_(new MainWindow()) {
  main_window_->show();
}
