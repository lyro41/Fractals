#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <queue>
#include <string>
#include <cmath>


QT_BEGIN_NAMESPACE
namespace Ui {
  class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  void paintEvent(QPaintEvent *event);

private slots:
  void on_decrease_button_clicked();
  void on_increase_button_clicked();

private:
  Ui::Widget *ui;
  size_t power_;
  const size_t kPowerMax;
};


#endif // WIDGET_H
