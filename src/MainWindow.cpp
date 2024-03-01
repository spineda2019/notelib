#include "include/MainWindow.h"
#include "include/ui_MainWindow.h"

#include <qwidget.h>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow()) {
  this->ui->setupUi(this);
}

MainWindow::~MainWindow() { delete this->ui; }
