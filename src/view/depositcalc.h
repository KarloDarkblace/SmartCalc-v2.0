#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QMessageBox>
#include <QTableWidget>
#include <QWidget>

#include "s21_qdeposit_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DepositCalc;
}
QT_END_NAMESPACE

namespace s21 {

class DepositCalc : public QWidget {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget* parent = nullptr);
  ~DepositCalc();

 private slots:
  void onReplenishmentsAddClicked();
  void onWithdrawalsAddClicked();
  void onReplenishmentsDeleteClicked();
  void onWithdrawalsDeleteClicked();
  void onCalculateClicked();

 private:
  int getPostingPeriodInDays();
  bool checkWithdrawalField();
  bool checkReplenishmentField();
  bool checkAllFields();
  bool checkEmptyFields();
  bool checkZeroFields();
  void setupSettings();
  void setValidators();
  void setMinimumDateEditsTime();
  void connectAllButtons();
  void setResultToLabel(const s21::DepositResult result);
  void fillDepositParams(s21::DepositParams& depositParams);
  void fillTransactions(std::list<s21::Transaction>& transactions,
                        QTableWidget* tableWidget);
  s21::Transaction createTransactionFromRow(QTableWidgetItem* dateItem,
                                            QTableWidgetItem* amountItem);

 private:
  QDepositController deposit_controller;
  Ui::DepositCalc* ui;
};

}  // namespace s21

#endif  // DEPOSITCALC_H
