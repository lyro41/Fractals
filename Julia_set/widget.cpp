#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  this->setGeometry(0, 0, 1366, 768);
  planes.push(new QPixmap(this->geometry().width(), this->geometry().height()));
  ui->plane->setGeometry(this->geometry());
  this->setMouseTracking(true);

  x_scale = 0.31e-2;
  y_scale = 0.31e-2;
  x0 = -this->geometry().width() / 2.0 * x_scale;
  y0 = -this->geometry().height() / 2.0 * y_scale;

  inf_sqr = 4;
  size = 256;

  constants = std::deque<Complex>({ { -0.8, 0.156 },
                                    { 0.285, 0.01 },
                                    { -0.0085, 0.71 },
                                    { -0.74543, 0.11301 },
                                    { -0.752, 0.07 },
                                    { -0.3, 0.6 },
                                    { 0.3, 0.5 },
                                    { 0.3, 0.46 },
                                    { -0.800043099666580, 0.164138006668392 },
                                    { -1, 1 },
                                    { 6.175615574477433e-16, -1 },
                                    { -0.17999999999999938, -1.1 },
                                    { 0.36, -0.09 },
                                    { 0.36, -0.11 },
                                    { 0.360001, -0.1144569 },
                                    { -0.80004309966658, 0.254738006668392 },
                                    //{ -1.24904309966658, 0.184738006668392 },
                                    //{ -1.24904309966658, 0.174738006668392 },
                                    //{ -1.259005, 0.174738006668392 },
                                    //{ -1.2590050010003, 0.174738006668392 },
                                    { -1.259005001000298, 0.17473800666839192 }
                                  });

  rgb_colors = std::deque<std::tuple<size_t, size_t, size_t>>({ { 255, 255, 255 },
                                                                { 193, 112, 255 },
                                                                { 112, 193, 255 },
                                                                { 193, 255, 112 },
                                                                { 112, 255, 193 },
                                                                { 255, 193, 112 },
                                                                { 255, 112, 193 }
                                                              });

  hsv_colors = std::deque<std::pair<double, double>>({ { 360, 000 },
                                                       { 60, 240 }
                                                     });

  need_repaint = 1;
  is_pressed = 0;
  is_hsv = 0;

  this->repaint();

  return;
}

Widget::~Widget() {
  delete ui;
  return;
}

void Widget::paintEvent(QPaintEvent *) {

  if (need_repaint) {

    planes.push(new QPixmap(this->geometry().width(), this->geometry().height()));
    QPainter painter(planes.top());

    for (int i = 0; i < this->geometry().width(); ++i) {
      for (int j = 0; j < this->geometry().height(); ++j) {
        Complex z(x0 + i * x_scale, y0 + j * y_scale);

        size_t k;
        for (k = 0; k < size; ++k) {
          if (z.SqrAbs() >= inf_sqr) break;
          z = z * z + constants.front();
        }

        if (z.SqrAbs() < inf_sqr) {
          painter.setPen(Qt::black);
          painter.drawPoint(i, j);
          continue;
        }

        QColor newcolor;

        if (is_hsv) {
          newcolor.setHsv(static_cast<int>(hsv_colors.front().first * k / size +
                                           hsv_colors.front().second),
                          255,
                          static_cast<int>(255.0 * k / size));
        }
        else {
          newcolor.setRgb(static_cast<int>(1.0 * k / size * std::get<0>(rgb_colors.front())),
                          static_cast<int>(1.0 * k / size * std::get<1>(rgb_colors.front())),
                          static_cast<int>(1.0 * k / size * std::get<2>(rgb_colors.front())));
        }

        painter.setPen(newcolor);
        painter.drawPoint(i, j);
      }
    }

    need_repaint = 0;

  }

  if (is_pressed) {
    QPixmap rect = *planes.top();
    QPainter painter(&rect);
    painter.setPen(Qt::white);
    painter.setBrush(QBrush(QColor(255, 255, 255, 64)));
    painter.drawRect(mouse_x0, mouse_y0, mouse_x - mouse_x0, mouse_y - mouse_y0);
    ui->plane->setPixmap(rect);
    return;
  }

  ui->plane->setPixmap(*planes.top());
  return;
}

void Widget::mousePressEvent(QMouseEvent *event) {
  is_pressed = 1;
  mouse_x0 = event->x();
  mouse_y0 = event->y();
  mouse_x = mouse_x0;
  mouse_y = mouse_y0;
  return;
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
  //if (!is_pressed) return;
  mouse_x = event->x();
  mouse_y = event->y();
  return;
}

void Widget::mouseReleaseEvent(QMouseEvent *) {
  is_pressed = 0;
  if (x_scale * std::abs(mouse_x - mouse_x0) / this->geometry().width() < 3e-9 ||
      y_scale * std::abs(mouse_y - mouse_y0) / this->geometry().height() < 3e-9) return;
  if (mouse_x < mouse_x0) std::swap(mouse_x, mouse_x0);
  if (mouse_y < mouse_y0) std::swap(mouse_y, mouse_y0);
  x0 = x0 + mouse_x0 * x_scale;
  y0 = y0 + mouse_y0 * y_scale;
  x_scale = x_scale * (mouse_x - mouse_x0) / this->geometry().width();
  y_scale = y_scale * (mouse_y - mouse_y0) / this->geometry().height();

  need_repaint = 1;
  repaint();
  return;
}

void Widget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    //case Qt::Key_Escape:
      //if (planes.size() > 1) planes.pop();
      //x_scale = x_scale * this->geometry().width() / (mouse_x - mouse_x0);
      //y_scale = y_scale * this->geometry().height() / (mouse_y - mouse_y0);
      //x0 = x0 - x_scale * mouse_x0 / this->geometry().width();
      //y0 = y0 - y_scale * mouse_y0 / this->geometry().width();
      //break;

    case Qt::Key_Right:
      constants.push_back(constants.front());
      constants.pop_front();
      need_repaint = 1;
      repaint();
      break;

    case Qt::Key_Left:
      constants.push_front(constants.back());
      constants.pop_back();
      need_repaint = 1;
      repaint();
      break;

    case Qt::Key_Up:
      rgb_colors.push_back(rgb_colors.front());
      rgb_colors.pop_front();
      hsv_colors.push_back(hsv_colors.front());
      hsv_colors.pop_front();
      need_repaint = 1;
      repaint();
      break;

    case Qt::Key_Down:
      rgb_colors.push_front(rgb_colors.back());
      rgb_colors.pop_back();
      hsv_colors.push_front(hsv_colors.back());
      hsv_colors.pop_back();
      need_repaint = 1;
      repaint();
      break;

    case Qt::Key_CapsLock:
      is_hsv = !is_hsv;
      need_repaint = 1;
      repaint();
      break;
  }
  return;
}
