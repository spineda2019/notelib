#include <qapplication.h>

#include "include/MainWindow.h"

int main(int argc, char **argv) {
  QApplication notelib(argc, argv);
  notelib.setApplicationName("NoteLib");
  MainWindow main_window{};
  main_window.setWindowTitle("Notelib");
  main_window.show();

  return notelib.exec();
}
