#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  //ui->plane->showFullScreen()
  ui->plane->setGeometry(0, 0, 1366, 1024);
  this->setGeometry(ui->plane->geometry());
  std::srand(static_cast<unsigned int>(time(nullptr)));
  map.resize(static_cast<size_t>(this->geometry().height()),
             std::vector<QRgb>(static_cast<size_t>(this->geometry().width()), 0));
  dmap.resize(static_cast<size_t>(this->geometry().height()),
              std::vector<double>(static_cast<size_t>(this->geometry().width()), 0));
  is_drawn = 0;
  repaint();
  return;
}

Widget::~Widget() {
  delete ui;
  return;
}

void Widget::paintEvent(QPaintEvent *) {
  if (!is_drawn) {


    //map[0][0] = ((static_cast<unsigned int>(rand()) % 0xFF) << 16) +
    //            ((static_cast<unsigned int>(rand()) % 0xFF) << 8) +
    //            static_cast<unsigned int>(rand()) % 0xFF;
    //
    //map[0][static_cast<size_t>(ui->plane->geometry().width() - 1)] =
    //    ((static_cast<unsigned int>(rand()) % 0xFF) << 16) +
    //    ((static_cast<unsigned int>(rand()) % 0xFF) << 8) +
    //    static_cast<unsigned int>(rand()) % 0xFF;
    //
    //map[static_cast<size_t>(ui->plane->geometry().height() - 1)][0] =
    //    ((static_cast<unsigned int>(rand()) % 0xFF) << 16) +
    //    ((static_cast<unsigned int>(rand()) % 0xFF) << 8) +
    //    static_cast<unsigned int>(rand()) % 0xFF;
    //
    //map[static_cast<size_t>(ui->plane->geometry().height() - 1)]
    //   [static_cast<size_t>(ui->plane->geometry().width() - 1) ] =
    //    ((static_cast<unsigned int>(rand()) % 0xFF) << 16) +
    //    ((static_cast<unsigned int>(rand()) % 0xFF) << 8) +
    //    static_cast<unsigned int>(rand()) % 0xFF;


    dmap[0][0] = rand() % 360;

    dmap[0][static_cast<size_t>(ui->plane->geometry().width() - 1)] = rand() % 360;

    dmap[static_cast<size_t>(ui->plane->geometry().height() - 1)][0] = rand() % 360;

    dmap[static_cast<size_t>(ui->plane->geometry().height() - 1)]
        [static_cast<size_t>(ui->plane->geometry().width() - 1) ] = rand() % 360;

    Plasma(0,
           0,
           static_cast<size_t>(ui->plane->geometry().width() - 1),
           static_cast<size_t>(ui->plane->geometry().height() - 1));

  }

  QPainter painter(this);

  for (size_t i = 0; i < map.size(); ++i) {
    for (size_t j = 0; j < map[i].size(); ++j) {
      //painter.setPen(QColor((0xFFU << 24) + map[i][j]));
      painter.setPen(QColor::fromHsv((static_cast<int>(dmap[i][j]) % 360 + 360) % 360, 255, 212));
      painter.drawPoint(static_cast<int>(j), static_cast<int>(i));
    }
  }

  is_drawn = 1;
  return;
}

void Widget::Plasma(size_t x1, size_t y1, size_t x2, size_t y2) {
  if (x1 + 1 >= x2 && y1 + 1 >= y2) return;

  //map[y1][(x1 + x2) >> 1] = (map[y1][x1] >> 1) + (map[y1][x2] >> 1);
  //
  //map[y2][(x1 + x2) >> 1] = (map[y2][x1] >> 1) + (map[y2][x2] >> 1);
  //
  //map[(y1 + y2) >> 1][x1] = (map[y1][x1] >> 1) + (map[y2][x1] >> 1);
  //
  //map[(y1 + y2) >> 1][x2] = (map[y1][x2] >> 1) + (map[y2][x2] >> 1);
  //
  //map[(y1 + y2) >> 1][(x1 + x2) >> 1] = (map[y1][x1] >> 2) +
  //                                      (map[y2][x1] >> 2) +
  //                                      (map[y1][x2] >> 2) +
  //                                      (map[y2][x2] >> 2) + rand() % 50;


  dmap[y1][(x1 + x2) >> 1] = (dmap[y1][x1] / 2) + (dmap[y1][x2] / 2);

  dmap[y2][(x1 + x2) >> 1] = (dmap[y2][x1] / 2) + (dmap[y2][x2] / 2);

  dmap[(y1 + y2) >> 1][x1] = (dmap[y1][x1] / 2) + (dmap[y2][x1] / 2);

  dmap[(y1 + y2) >> 1][x2] = (dmap[y1][x2] / 2) + (dmap[y2][x2] / 2);

  dmap[(y1 + y2) >> 1][(x1 + x2) >> 1] = (dmap[y1][x1] / 4) +
                                         (dmap[y2][x1] / 4) +
                                         (dmap[y1][x2] / 4) +
                                         (dmap[y2][x2] / 4) +
                                         (2.0 * rand() / RAND_MAX - 1) * ((x2 - x1 + y2 - y1) * 2) *
                                         //(1.0 * rand() / RAND_MAX - 0.5) *
                                         (4.0 * rand() / RAND_MAX - 2);

  Plasma(x1, y1, (x1 + x2) >> 1, (y1 + y2) >> 1);
  Plasma((x1 + x2) >> 1, y1, x2, (y1 + y2) >> 1);
  Plasma(x1, (y1 + y2) >> 1, (x1 + x2) >> 1, y2);
  Plasma((x1 + x2) >> 1, (y1 + y2) >> 1, x2, y2);

  return;
}
