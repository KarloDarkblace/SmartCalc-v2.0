#include "creditcalc.h"
#include "ui_creditcalc.h"

namespace s21 {

CreditCalc::CreditCalc(QWidget* parent)
    : QWidget(parent), ui(new Ui::CreditCalc) {
  this->setFixedSize(355, 417);

  ui->setupUi(this);

  setValidators();
  connect(ui->calculateQPushButton, &QPushButton::clicked, this,
          &CreditCalc::onCalculateClicked);
}

CreditCalc::~CreditCalc() {
  delete ui;
}

void CreditCalc::setValidators() {
  ui->amountQLineEdit->setValidator(
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 0, this));
  ui->termQLineEdit->setValidator(new QIntValidator(0, 600, this));
  QDoubleValidator* validator = new QDoubleValidator(0, 99999, 4, this);
  validator->setLocale(QLocale::English);
  ui->rateQLineEdit->setValidator(validator);
}

bool CreditCalc::checkEmptyPlains() {
  bool return_value = false;
  if (ui->amountQLineEdit->text().size() < 1) {
    QMessageBox::warning(this, "Error", "The amount field is empty.");
    ui->amountQLineEdit->clear();
    return_value = true;
  }
  if (ui->termQLineEdit->text().size() < 1) {
    QMessageBox::warning(this, "Error", "The term field is empty.");
    ui->termQLineEdit->clear();
    return_value = true;
  }
  if (ui->rateQLineEdit->text().size() < 1) {
    QMessageBox::warning(this, "Error", "The rate field is empty.");
    ui->rateQLineEdit->clear();
    return_value = true;
  }
  return return_value;
}

bool CreditCalc::checkMinValues() {
  bool return_value = false;
  if (ui->amountQLineEdit->text().toDouble() < 1) {
    QMessageBox::warning(this, "Error",
                         "The amount value must be greater than 0.");
    ui->amountQLineEdit->clear();
    return_value = true;
  }
  if (ui->termQLineEdit->text().toDouble() < 1) {
    QMessageBox::warning(this, "Error",
                         "The term value must be greater than 0.");
    ui->termQLineEdit->clear();
    return_value = true;
  }
  if (ui->rateQLineEdit->text().toDouble() < 1) {
    QMessageBox::warning(this, "Error",
                         "The rate value must be greater than 0.");
    ui->rateQLineEdit->clear();
    return_value = true;
  }
  return return_value;
}

void CreditCalc::setResultValues(const AnnuityCreditResult credit_result) {
  ui->monthlyPaymentOutputQLabel->setText(
      QString::number(credit_result.monthly_payment, 'f', 2));
  ui->overpaymentOutputQLabel->setText(
      QString::number(credit_result.overpayment, 'f', 2));
  ui->totalPaymentOutputQLabel->setText(
      QString::number(credit_result.total_payment, 'f', 2));
}

void CreditCalc::setResultValues(const DifferentialCreditResult credit_result) {
  QString monthlyPaymentText =
      QString::number(credit_result.first_monthly_payment, 'f', 2) + "..." +
      QString::number(credit_result.last_monthly_payment, 'f', 2);
  ui->monthlyPaymentOutputQLabel->setText(monthlyPaymentText);
  ui->overpaymentOutputQLabel->setText(
      QString::number(credit_result.overpayment, 'f', 2));
  ui->totalPaymentOutputQLabel->setText(
      QString::number(credit_result.total_payment, 'f', 2));
}

void CreditCalc::getValuesFromLabels(CreditParams& credit_params) {
  credit_params.amount = ui->amountQLineEdit->text().toDouble();
  credit_params.term = ui->termQLineEdit->text().toDouble();
  credit_params.rate = ui->rateQLineEdit->text().toDouble();

  if (ui->dateQComboBox->currentText() == "YEARS") {
    credit_params.term *= 12;
  }
}

void CreditCalc::onCalculateClicked() {
  if (checkEmptyPlains() || checkMinValues()) {
    return;
  }

  CreditParams credit_params;
  getValuesFromLabels(credit_params);

  if (ui->annuityQRadioButton->isChecked()) {
    AnnuityCreditResult annuity_result =
        credit_controller.CalculateAnnuityMonthPayments(credit_params);
    setResultValues(annuity_result);
  } else {
    DifferentialCreditResult differential_result =
        credit_controller.CalculateDifferentialMonthPayments(credit_params);
    setResultValues(differential_result);
  }
}

}  // namespace s21
