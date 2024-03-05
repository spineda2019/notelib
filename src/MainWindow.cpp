#include "include/MainWindow.h"
#include "include/ui_MainWindow.h"

#include <fstream>
#include <qfiledialog.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qwidget.h>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow()) {
  this->ui->setupUi(this);

  connect(this->ui->open_new_page_button_, &QPushButton::pressed, this,
          &MainWindow::OpenNewPage);
}

MainWindow::~MainWindow() { delete this->ui; }

void MainWindow::OpenNewPage() {
  QString selected_file(QFileDialog::getOpenFileName(this, tr("Select File")));

  if (selected_file.isEmpty()) {
    return;
  }

  std::ifstream selected_file_stream(selected_file.toStdString());
  char current_character{};

  this->ui->text_display_edit_->clear();
  while (selected_file_stream.get(current_character)) {
    this->ui->text_display_edit_->insertPlainText(QString(current_character));
  }
}
