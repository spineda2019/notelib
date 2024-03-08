#include "include/MainWindow.h"
#include "include/ui_MainWindow.h"

#include <QTextBlock>
#include <cstdint>
#include <fstream>
#include <mutex>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qpointer.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qtextcursor.h>
#include <qwidget.h>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow()), open_file_lock_{},
      number_of_lines_(1), current_file_name{},
      current_state_(DocumentState::DoesNotExist) {
  this->ui->setupUi(this);

  connect(this->ui->open_existing_page_button_, &QPushButton::clicked, this,
          &MainWindow::OpenNewPage);
  connect(this->ui->text_display_edit_, &QPlainTextEdit::textChanged, this,
          &MainWindow::IndicateFileHasBeenChanged);
  connect(this->ui->save_page_button_, &QPushButton::clicked, this,
          &MainWindow::SaveCurrentPage);
}

MainWindow::~MainWindow() { delete this->ui; }

void MainWindow::SaveCurrentPage() {
  if (this->current_state_ == DocumentState::DoesNotExist) {
    // request file destination
    QString selected_file(QFileDialog::getSaveFileName(this, tr("Save File")));

    if (selected_file.isEmpty()) {
      return;
    }

    QFileInfo file_info(selected_file);
    this->ui->current_page_label_->setText("Current Page: " +
                                           file_info.fileName());
    this->ui->current_notebook_label_->setText("Current Notebook: " +
                                               file_info.absolutePath());
    this->current_file_name = file_info.fileName().toStdString();
    this->current_state_ = DocumentState::Exists;
  }

  this->ui->save_page_button_->setStyleSheet("background-color: #ff7f7f;");
  QPointer<QTextDocument> current_document(
      this->ui->text_display_edit_->document());
  QTextCursor document_cursor(current_document);
  document_cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  this->ui->text_display_edit_->setTextCursor(document_cursor);
  std::ofstream output_file(this->current_file_name);
  while (!document_cursor.atEnd()) {
    document_cursor.movePosition(QTextCursor::EndOfLine,
                                 QTextCursor::MoveAnchor);
    output_file << document_cursor.block().text().toStdString();
    document_cursor.movePosition(QTextCursor::NextBlock,
                                 QTextCursor::MoveAnchor);
    if (!document_cursor.atEnd()) {
      output_file << "\n";
    }
  }

  this->ui->save_page_button_->setStyleSheet("background-color: #90ee90;");
}

void MainWindow::IndicateFileHasBeenChanged() {
  this->ui->save_page_button_->setStyleSheet("background-color: #f1eb9c;");
}

void MainWindow::OpenNewPage() {
  std::scoped_lock file_lock(this->open_file_lock_);
  this->ui->open_existing_page_button_->setStyleSheet(
      "background-color: #ff7f7f;");
  QString selected_file(QFileDialog::getOpenFileName(this, tr("Select File")));

  if (selected_file.isEmpty()) {
    this->ui->open_existing_page_button_->setStyleSheet(
        "background-color: #90ee90;");
    return;
  }

  this->current_state_ = DocumentState::Exists;
  QFileInfo file_info(selected_file);
  this->ui->current_page_label_->setText("Current Page: " +
                                         file_info.fileName());
  this->ui->current_notebook_label_->setText("Current Notebook: " +
                                             file_info.absolutePath());

  this->current_file_name =
      std::move(file_info.canonicalFilePath().toStdString());

  std::ifstream selected_file_stream(selected_file.toStdString());
  constexpr std::uint16_t max_cache_size(2048);
  std::string cached_text{};
  cached_text.reserve(max_cache_size);
  char current_character{};

  this->ui->text_display_edit_->clear();
  while (selected_file_stream.get(current_character)) {
    cached_text.push_back(current_character);
    if (current_character == '\n') {
      this->number_of_lines_++;
    }
    if (cached_text.length() >= max_cache_size) {
      this->ui->text_display_edit_->appendPlainText(
          QString::fromStdString(cached_text));
      cached_text.clear();
    }
  }
  if (!cached_text.empty()) {

    this->ui->text_display_edit_->appendPlainText(
        QString::fromStdString(cached_text));
  }

  this->ui->save_page_button_->setStyleSheet("background-color: #90ee90;");
  this->ui->open_existing_page_button_->setStyleSheet(
      "background-color: #90ee90;");

  QPointer<QTextDocument> current_document(
      this->ui->text_display_edit_->document());
  QTextCursor document_cursor(current_document);
  document_cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  this->ui->text_display_edit_->setTextCursor(document_cursor);
}
