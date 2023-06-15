#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), power_(0), kPowerMax(8) {
  ui->setupUi(this);
  ui->decrease_button->setEnabled(false);
}

Widget::~Widget() {
  delete ui;
}

void Widget::on_decrease_button_clicked() {
  --power_;
  ui->increase_button->setEnabled(true);
  if (power_ == 0) ui->decrease_button->setEnabled(false);
  repaint();
}

void Widget::on_increase_button_clicked() {
  ++power_;
  ui->decrease_button->setEnabled(true);
  if (power_ == kPowerMax) ui->increase_button->setEnabled(false);
  repaint();
}

void Widget::paintEvent(QPaintEvent *event) {
  std::queue<char> actual;
  std::string start_state = "S--S--S";
  std::string conversion = "S+S--S+S";
  for (size_t i = 0; i < start_state.size(); ++i) {
    actual.push(start_state[i]);
  }

  for (size_t i = 0; i < power_; ++i) {
    std::queue<char> buff;
    while (!actual.empty()) {
      switch (actual.front()) {
        case '-':
        case '+':
          buff.push(actual.front());
          break;

        case 'S':
          for (size_t k = 0; k < conversion.size(); ++k) {
            buff.push(conversion[k]);
          }
          break;
      }
      actual.pop();
    }
    actual = buff;
  }

  double x = 233;
  double y = 240;
  double angle = 0;
  double length = 729;
  double r = 1.0 / 3;
  const double pi = 3.141592653589793238;

  QPainter painter(this);

  painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
  painter.setRenderHint(QPainter::Antialiasing, true);

  while (!actual.empty()) {
    switch (actual.front()) {
      case '+':
        angle -= 60;
        break;

      case '-':
        angle += 60;
        break;

      case 'S':
        double x_next = x + length * std::pow(r, power_) * cos(angle / 180 * pi);
        double y_next = y + length * std::pow(r, power_) * sin(angle / 180 * pi);
        painter.drawLine(x, y, x_next, y_next);
        x = x_next;
        y = y_next;
        break;
    }
    actual.pop();
  }

}
