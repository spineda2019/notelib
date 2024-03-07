#include "include/MainWindow.h"
#include "include/ui_MainWindow.h"

#include <cstdint>
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
  constexpr std::uint16_t max_cache_size(2048);
  std::string cached_text{};
  cached_text.reserve(max_cache_size);
  char current_character{};

  this->ui->text_display_edit_->clear();
  while (selected_file_stream.get(current_character)) {
    cached_text.push_back(current_character);
    if (cached_text.length() >= max_cache_size) {
      this->ui->text_display_edit_->insertPlainText(
          QString::fromStdString(cached_text));
      cached_text.clear();
    }
  }
  if (!cached_text.empty()) {

    this->ui->text_display_edit_->insertPlainText(
        QString::fromStdString(cached_text));
  }
}
