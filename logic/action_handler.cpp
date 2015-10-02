#include "action_handler.h"

#include "widgets/new_image_file_dialog.h"

ActionHandler::ActionHandler(QObject *parent)
  : QObject(parent) {

}

ActionHandler::~ActionHandler()
{

}

void ActionHandler::NewFile() {
  NewImageFileDialog * image_file_dialog = new NewImageFileDialog();
  image_file_dialog->exec();
  delete image_file_dialog;
}

void ActionHandler::OpenFile() {
}

