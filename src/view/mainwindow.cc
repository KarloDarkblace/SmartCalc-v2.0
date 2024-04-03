#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->setFixedSize(this->width(), this->height());

  setValidator();
  connectAllButtons();
}

void MainWindow::setValidator() {
  QDoubleValidator* validator =
      new QDoubleValidator(std::numeric_limits<double>::min(),
                           std::numeric_limits<double>::max(), 7, this);
  validator->setLocale(QLocale::English);
  ui->inputXQLineEdit->setValidator(validator);
}

void MainWindow::connectAllButtons() {
  connect(ui->zeroQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->oneQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->twoQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->threeQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->fourQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->fiveQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->sixQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->sevenQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->eightQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->nineQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);

  connect(ui->expQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->powQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->pointQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->sumQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->subQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->mulQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->divQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->modQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);

  connect(ui->cosQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->sinQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->tanQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->acosQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->asinQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->atanQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->lnQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->logQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->sqrtQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);

  connect(ui->xQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->leftbracketQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);
  connect(ui->rightbracketQPushButton, &QPushButton::clicked, this,
          &MainWindow::onInputButtonClicked);

  connect(ui->clearQPushButton, &QPushButton::clicked, this,
          &MainWindow::onClearButtonClicked);

  connect(ui->backspaceQPushButton, &QPushButton::clicked, this,
          &MainWindow::onBackspaceButtonClicked);

  connect(ui->creditcalcQPushButton, &QPushButton::clicked, this,
          &MainWindow::onCreditcalcClicked);
  connect(ui->depositcalcQPushButton, &QPushButton::clicked, this,
          &MainWindow::onDepositcalcClicked);
  connect(ui->resultQPushButton, &QPushButton::clicked, this,
          &MainWindow::onResultButtonClicked);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
  for (auto* window : qAsConst(graphWindows)) {
    window->close();
  }
  if (credit_calc_window != nullptr) {
    credit_calc_window->close();
  }
  if (deposit_calc_window != nullptr) {
    deposit_calc_window->close();
  }
  QMainWindow::closeEvent(event);
}

void MainWindow::displayGraph(QString qstring) {
  GraphWindow* graphWindow = new GraphWindow(qstring);
  graphWindows.append(graphWindow);
  graphWindow->show();
}

void MainWindow::calculateExpression(QString qstring, long double x) {
  long double number = 0.0f;
  std::string expression = qstring.toStdString();
  main_controller.CalculateExpression(expression, number, x);

  ui->inputFieldQTextBrowser->setPlainText(QString::number(number, 'g', 10));
  QTextCursor cursor = ui->inputFieldQTextBrowser->textCursor();
  cursor.movePosition(QTextCursor::End);
  ui->inputFieldQTextBrowser->setTextCursor(cursor);
}

void MainWindow::onInputButtonClicked() {
  if (ui->inputFieldQTextBrowser->toPlainText().size() <= 255) {
    if (ui->inputFieldQTextBrowser->toPlainText() == "ERROR IN EXPRESSION") {
      ui->inputFieldQTextBrowser->clear();
    }
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
      ui->inputFieldQTextBrowser->insertPlainText(button->text());
      if (button->text().size() > 1 && button->text() != "mod") {
        ui->inputFieldQTextBrowser->insertPlainText("(");
      }
    }
  }
}

void MainWindow::onBackspaceButtonClicked() {
  QTextCursor cursor = ui->inputFieldQTextBrowser->textCursor();

  if (!cursor.atStart()) {
    cursor.movePosition(QTextCursor::Left);
    cursor.deleteChar();
  }
}

void MainWindow::onClearButtonClicked() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if (button) {
    ui->inputFieldQTextBrowser->clear();
  }
}

void MainWindow::onResultButtonClicked() {
  if (isExpressionNormal() == false) {
    ui->inputFieldQTextBrowser->setPlainText("ERROR IN EXPRESSION");
    return;
  }

  QString qstring = ui->inputFieldQTextBrowser->toPlainText();

  if (qstring.contains('x')) {
    if (ui->inputXQLineEdit->text().size() > 0) {
      double x_number = ui->inputXQLineEdit->text().toDouble();
      calculateExpression(qstring, x_number);
    } else {
      displayGraph(qstring);
    }
  } else {
    calculateExpression(qstring);
  }
}

bool MainWindow::isExpressionNormal() {
  bool return_value = true;

  QString qstring = ui->inputFieldQTextBrowser->toPlainText();
  if (qstring.contains('x') && ui->inputXQLineEdit->text().size() > 0) {
    double x_number = ui->inputXQLineEdit->text().toDouble();
    return_value =
        main_controller.IsExpressionNormal(qstring.toStdString(), x_number);
  } else {
    return_value = main_controller.IsExpressionNormal(qstring.toStdString());
  }

  return return_value;
}

void MainWindow::onCreditcalcClicked() {
  if (credit_calc_window == nullptr) {
    credit_calc_window = new CreditCalc();
  }
  credit_calc_window->show();
}

void MainWindow::onDepositcalcClicked() {
  if (deposit_calc_window == nullptr) {
    deposit_calc_window = new DepositCalc();
  }
  deposit_calc_window->show();
}

}  // namespace s21
