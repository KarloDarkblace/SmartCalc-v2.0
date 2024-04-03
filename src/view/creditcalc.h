#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QMessageBox>
#include <QWidget>
#include <climits>
#include <sstream>

#include "s21_qcredit_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CreditCalc;
}
QT_END_NAMESPACE

namespace s21 {

class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget* parent = nullptr);
  ~CreditCalc();

 private slots:
  void onCalculateClicked();

 private:
  void setValidators();
  void setResultValues(const s21::AnnuityCreditResult credit_result);
  void setResultValues(const s21::DifferentialCreditResult credit_result);
  void getValuesFromLabels(s21::CreditParams& credit_params);
  bool checkEmptyPlains();
  bool checkMinValues();
  void calculateCredit();

 private:
  QCreditController credit_controller;
  Ui::CreditCalc* ui;
};

}  // namespace s21

#endif  // CREDITCALC_H
