#include "application/pixel_booster.h"

#include "utils/debug.h"

int main(int argc, char ** argv) {
  PixelBooster a(argc,argv);
  return a.exec();
}
