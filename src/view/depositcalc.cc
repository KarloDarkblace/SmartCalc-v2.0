#include "depositcalc.h"
#include "ui_depositcalc.h"

namespace s21 {

DepositCalc::DepositCalc(QWidget* parent)
    : QWidget(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);
  setupSettings();
}

DepositCalc::~DepositCalc() {
  delete ui;
}

void DepositCalc::setupSettings() {
  this->setFixedSize(this->width(), this->height());
  setMinimumDateEditsTime();
  setValidators();
  connectAllButtons();
}

void DepositCalc::setMinimumDateEditsTime() {
  ui->replenishmentsQDateEdit->setMinimumDate(QDate::currentDate());
  ui->withdrawalsQDateEdit->setMinimumDate(QDate::currentDate());
}

void DepositCalc::setValidators() {
  ui->depositAmountQLineEdit->setValidator(
      new QDoubleValidator(1, std::numeric_limits<double>::max(), 0, this));
  ui->postingPeriodQLineEdit->setValidator(new QIntValidator(1, INT_MAX, this));
  ui->taxRateQLineEdit->setValidator(new QIntValidator(1, INT_MAX, this));
  ui->interestRateQLineEdit->setValidator(new QIntValidator(1, INT_MAX, this));
  ui->replenishmentsQLineEdit->setValidator(
      new QIntValidator(1, INT_MAX, this));
  ui->withdrawalsQLineEdit->setValidator(new QIntValidator(1, INT_MAX, this));
}

void DepositCalc::connectAllButtons() {
  connect(ui->replenishmentsAddQPushButton, &QPushButton::clicked, this,
          &DepositCalc::onReplenishmentsAddClicked);
  connect(ui->withdrawalsAddQPushButton, &QPushButton::clicked, this,
          &DepositCalc::onWithdrawalsAddClicked);
  connect(ui->replenishmentsDeleteQPushButton, &QPushButton::clicked, this,
          &DepositCalc::onReplenishmentsDeleteClicked);
  connect(ui->withdrawalsDeleteQPushButton, &QPushButton::clicked, this,
          &DepositCalc::onWithdrawalsDeleteClicked);
  connect(ui->calculateQPushButton, &QPushButton::clicked, this,
          &DepositCalc::onCalculateClicked);
}

bool DepositCalc::checkWithdrawalField() {
  bool return_value = false;
  if (ui->withdrawalsQLineEdit->text().size() == 0) {
    QMessageBox::warning(this, "Error", "The withdrawal field is empty.");
    return_value = true;
  } else if (ui->withdrawalsQLineEdit->text().toDouble() == 0) {
    QMessageBox::warning(this, "Error",
                         "The withdrawal value must be greater than 0.");
    return_value = true;
  }
  return return_value;
}

bool DepositCalc::checkReplenishmentField() {
  bool return_value = false;
  if (ui->replenishmentsQLineEdit->text().size() == 0) {
    QMessageBox::warning(this, "Error", "The eplenishment field is empty.");
    return_value = true;
  } else if (ui->replenishmentsQLineEdit->text().toDouble() == 0) {
    QMessageBox::warning(this, "Error",
                         "The eplenishment value must be greater than 0.");
    return_value = true;
  }
  return return_value;
}

bool DepositCalc::checkEmptyFields() {
  bool return_value = false;
  if (ui->depositAmountQLineEdit->text().size() == 0) {
    QMessageBox::warning(this, "Error", "The deposit amount field is empty.");
    return_value = true;
  }
  if (ui->postingPeriodQLineEdit->text().size() == 0) {
    QMessageBox::warning(this, "Error", "The posting period field is empty.");
    return_value = true;
  }
  if (ui->taxRateQLineEdit->text().size() == 0) {
    QMessageBox::warning(this, "Error", "The tax rate field is empty.");
    return_value = true;
  }
  if (ui->interestRateQLineEdit->text().size() == 0) {
    QMessageBox::warning(this, "Error", "The interest rate field is empty.");
    return_value = true;
  }
  return return_value;
}

bool DepositCalc::checkZeroFields() {
  bool return_value = false;
  if (ui->depositAmountQLineEdit->text().toDouble() == 0) {
    QMessageBox::warning(this, "Error",
                         "The deposit amount must be greater than 0.");
    return_value = true;
  }
  if (ui->postingPeriodQLineEdit->text().toDouble() == 0) {
    QMessageBox::warning(this, "Error",
                         "The posting period value must be greater than 0.");
    return_value = true;
  }
  if (ui->taxRateQLineEdit->text().toDouble() == 0) {
    QMessageBox::warning(this, "Error",
                         "The tax rate value must be greater than 0.");
    return_value = true;
  }
  if (ui->interestRateQLineEdit->text().toDouble() == 0) {
    QMessageBox::warning(this, "Error",
                         "The interest rate value must be greater than 0.");
    return_value = true;
  }
  return return_value;
}

bool DepositCalc::checkAllFields() {
  return checkEmptyFields() ? true : checkZeroFields();
}

void DepositCalc::onReplenishmentsAddClicked() {
  if (checkReplenishmentField()) {
    return;
  }

  int rowCount = ui->replenishmentsQTableWidget->rowCount();
  ui->replenishmentsQTableWidget->insertRow(rowCount);

  ui->replenishmentsQTableWidget->setItem(
      rowCount, 0, new QTableWidgetItem(ui->replenishmentsQDateEdit->text()));
  ui->replenishmentsQTableWidget->setItem(
      rowCount, 1, new QTableWidgetItem(ui->replenishmentsQLineEdit->text()));
  ui->replenishmentsQLineEdit->clear();
}

void DepositCalc::onWithdrawalsAddClicked() {
  if (checkWithdrawalField()) {
    return;
  }

  int rowCount = ui->withdrawalsQTableWidget->rowCount();

  ui->withdrawalsQTableWidget->insertRow(rowCount);

  ui->withdrawalsQTableWidget->setItem(
      rowCount, 0, new QTableWidgetItem(ui->withdrawalsQDateEdit->text()));
  ui->withdrawalsQTableWidget->setItem(
      rowCount, 1, new QTableWidgetItem(ui->withdrawalsQLineEdit->text()));
  ui->withdrawalsQLineEdit->clear();
}

void DepositCalc::onReplenishmentsDeleteClicked() {
  int currentRow = ui->replenishmentsQTableWidget->currentRow();
  if (currentRow != -1) {
    ui->replenishmentsQTableWidget->removeRow(currentRow);
  }
}

void DepositCalc::onWithdrawalsDeleteClicked() {
  int currentRow = ui->withdrawalsQTableWidget->currentRow();
  if (currentRow != -1) {
    ui->withdrawalsQTableWidget->removeRow(currentRow);
  }
}

int DepositCalc::getPostingPeriodInDays() {
  int return_value = ui->postingPeriodQLineEdit->text().toInt();
  if (ui->postingPeriodQComboBox->currentIndex() == 2) {
    return_value *= 365;
  } else if (ui->postingPeriodQComboBox->currentIndex() == 1) {
    return_value *= 30;
  }
  return return_value;
}

void DepositCalc::setResultToLabel(const DepositResult result) {
  ui->accruedInterestOutputQLabel->setText(
      QString::number(result.accrued_interest, 'f', 4));
  ui->taxAmountOutputQLabel->setText(
      QString::number(result.tax_amount, 'f', 4));
  ui->finalBanaceOutputQLabel->setText(
      QString::number(result.total_amount, 'f', 4));
}

void DepositCalc::fillDepositParams(DepositParams& depositParams) {
  depositParams.deposit_amount = ui->depositAmountQLineEdit->text().toDouble();
  depositParams.posting_period = getPostingPeriodInDays();
  depositParams.tax_rate = ui->taxRateQLineEdit->text().toDouble();
  depositParams.interest_rate = ui->interestRateQLineEdit->text().toDouble();
  depositParams.capitalization = ui->capitalizationQCheckBox->isChecked();
  depositParams.frequency_of_payments = static_cast<InterestAccrualFrequency>(
      ui->frequencyOfPaymentsQComboBox->currentIndex());

  fillTransactions(depositParams.transactions.replenishments,
                   ui->replenishmentsQTableWidget);
  fillTransactions(depositParams.transactions.withdrawals,
                   ui->withdrawalsQTableWidget);
}

void DepositCalc::fillTransactions(std::list<Transaction>& transactions,
                                   QTableWidget* tableWidget) {
  for (int i = 0; i < tableWidget->rowCount(); ++i) {
    QTableWidgetItem* dateItem = tableWidget->item(i, 0);
    QTableWidgetItem* amountItem = tableWidget->item(i, 1);
    transactions.push_back(createTransactionFromRow(dateItem, amountItem));
  }
}

Transaction DepositCalc::createTransactionFromRow(
    QTableWidgetItem* dateItem, QTableWidgetItem* amountItem) {
  Transaction transaction;
  transaction.date = QDate::fromString(dateItem->text(), "dd.MM.yyyy");
  transaction.amount = amountItem->text().toDouble();
  return transaction;
}

void DepositCalc::onCalculateClicked() {
  if (checkAllFields()) {
    return;
  }

  DepositParams depositParams;
  fillDepositParams(depositParams);

  DepositResult result = deposit_controller.CalculateDeposit(depositParams);
  setResultToLabel(result);
}

}  // namespace s21
