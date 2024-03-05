#ifndef NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP
#define NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP

#include <QMainWindow>
#include <qtconfigmacros.h>

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

private:
  Ui::MainWindow *ui;
};

#endif // NOTELIB_SRC_INCLUDE_MAINWINDOW_HPP
