#ifndef WIDGET_H
#define WIDGET_H

#include "complex.h"

#include <QWidget>
#include <QPainter>
#include <cmath>
#include <QMouseEvent>
#include <tuple>
#include <stack>
#include <deque>


QT_BEGIN_NAMESPACE

namespace Ui {
  class Widget;
}

QT_END_NAMESPACE


class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget() override;

  void paintEvent(QPaintEvent *event) override;

 private:
  Ui::Widget *ui;
  std::stack<QPixmap *> planes;

  double x0;
  double y0;
  double x_scale;
  double y_scale;

  size_t size;
  double inf_sqr;

  std::deque<Complex> constants;
  std::deque<std::tuple<size_t, size_t, size_t>> rgb_colors;
  std::deque<std::pair<double, double>> hsv_colors;


  int mouse_x0;
  int mouse_y0;

  int mouse_x;
  int mouse_y;

  bool need_repaint;
  bool is_pressed;
  bool is_hsv;


  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
};


#endif // WIDGET_H
