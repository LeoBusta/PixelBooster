#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  action_handler_(new ActionHandler(this)){
  ui->setupUi(this);

  ConnectActions();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::ConnectActions() {
  QObject::connect(ui->actionNew,SIGNAL(triggered(bool)),action_handler_,SLOT(NewFile()));
  QObject::connect(ui->actionOpen,SIGNAL(triggered(bool)),action_handler_,SLOT(OpenFile()));
}
