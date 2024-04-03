#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "creditcalc.h"
#include "depositcalc.h"
#include "graphwindow.h"

#include "s21_qmain_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void onResultButtonClicked();
  void onInputButtonClicked();
  void onClearButtonClicked();
  void onBackspaceButtonClicked();
  void onCreditcalcClicked();
  void onDepositcalcClicked();

 private:
  void calculateExpression(QString qstring, long double x = 0);
  void displayGraph(QString qstring);
  void connectAllButtons();
  void setValidator();
  bool isExpressionNormal();

 private:
  Ui::MainWindow* ui;
  QMainController main_controller;
  CreditCalc* credit_calc_window = nullptr;
  DepositCalc* deposit_calc_window = nullptr;
  QList<GraphWindow*> graphWindows;
};

}  // namespace s21
#endif  // MAINWINDOW_H
