#ifndef NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP
#define NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP

#include <QMainWindow>
#include <mutex>
#include <qtconfigmacros.h>
#include <qtmetamacros.h>

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
};

#endif // NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP
