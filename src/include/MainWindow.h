#ifndef NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP
#define NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP

#include <QMainWindow>
#include <cstdint>
#include <mutex>
#include <qtconfigmacros.h>
#include <qtmetamacros.h>

namespace {
enum class DocumentState : std::uint8_t {
  DoesNotExist,
  Exists,
};
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
};
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QMainWindow *parent = nullptr);
  ~MainWindow();

private slots:
  void OpenNewPage();
  void SaveCurrentPage();
  void IndicateFileHasBeenChanged();

private:
  Ui::MainWindow *ui;
  std::mutex open_file_lock_;
  std::string current_file_name;
  std::size_t number_of_lines_;
  enum class DocumentState current_state_;
};

#endif // NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP
