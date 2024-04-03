#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include "qcustomplot.h"

#include "s21_qmain_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GraphWindow;
}
QT_END_NAMESPACE

namespace s21 {

class GraphWindow : public QWidget {
  Q_OBJECT

 public:
  explicit GraphWindow(const QString& qstring, QWidget* parent = nullptr);
  ~GraphWindow();

 private slots:
  void updateGraphic();

 private:
  void connectButtonsEditEvent();
  void setValidators();
  void drawGraphic();

 private:
  Ui::GraphWindow* ui;
  QMainController main_controller;
  std::string expression;
  QCustomPlot* customPlot;
};

}  // namespace s21

#endif  // GRAPHWINDOW_H
