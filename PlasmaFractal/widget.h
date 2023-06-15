#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <cstdlib>
#include <ctime>
#include <vector>


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
  void Plasma(size_t x1, size_t y1, size_t x2, size_t y2);

 private:
  Ui::Widget *ui;
  //QPixmap *plane;
  //QImage image;
  std::vector<std::vector<QRgb>> map;
  std::vector<std::vector<double>> dmap;
  bool is_drawn;
};


#endif // WIDGET_H
