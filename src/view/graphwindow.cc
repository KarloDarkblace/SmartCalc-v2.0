#include "graphwindow.h"
#include "ui_graphwindow.h"

namespace s21 {

GraphWindow::GraphWindow(const QString& qstring, QWidget* parent)
    : QWidget(parent), ui(new Ui::GraphWindow) {
  ui->setupUi(this);

  this->setFixedSize(this->width(), this->height());

  customPlot = new QCustomPlot(this);
  ui->verticalQLayout->addWidget(customPlot);
  expression = qstring.toStdString();

  connectButtonsEditEvent();
  setValidators();
  drawGraphic();
}

GraphWindow::~GraphWindow() {
  delete ui;
}

void GraphWindow::connectButtonsEditEvent() {
  connect(ui->xRangeMinQLineEdit, &QLineEdit::textChanged, this,
          &GraphWindow::updateGraphic);
  connect(ui->xRangeMaxQLineEdit, &QLineEdit::textChanged, this,
          &GraphWindow::updateGraphic);
  connect(ui->yRangeMinQLineEdit, &QLineEdit::textChanged, this,
          &GraphWindow::updateGraphic);
  connect(ui->yRangeMaxQLineEdit, &QLineEdit::textChanged, this,
          &GraphWindow::updateGraphic);
}

void GraphWindow::setValidators() {
  ui->xRangeMinQLineEdit->setValidator(new QIntValidator(-1000000, 0, this));
  ui->xRangeMaxQLineEdit->setValidator(new QIntValidator(0, 1000000, this));
  ui->yRangeMinQLineEdit->setValidator(new QIntValidator(-1000000, 0, this));
  ui->yRangeMaxQLineEdit->setValidator(new QIntValidator(0, 1000000, this));
}

void GraphWindow::drawGraphic() {
  customPlot->clearGraphs();

  QVector<double> x(101), y(101);
  double minX = ui->xRangeMinQLineEdit->text().toDouble(),
         maxX = ui->xRangeMaxQLineEdit->text().toDouble();
  double minY = ui->yRangeMinQLineEdit->text().toDouble(),
         maxY = ui->yRangeMaxQLineEdit->text().toDouble();

  long double number = 0.0f;

  for (int i = 0; i < 101; ++i) {
    x[i] = minX + (maxX - minX) * i / 100.0;
    main_controller.CalculateExpression(expression, number, x[i]);
    y[i] = number;
  }

  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);
  customPlot->xAxis->setLabel("X");
  customPlot->yAxis->setLabel("Y");
  customPlot->xAxis->setRange(minX, maxX);
  customPlot->yAxis->setRange(minY, maxY);
  customPlot->replot();
}

void GraphWindow::updateGraphic() {
  drawGraphic();
}

}  // namespace s21
