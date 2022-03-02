// Last modified by: Yaseen Joba (181033), on 2.03.2021


#include "RenderWidget.h"
#include <QPainter>
#include <iostream>
struct POINT {
    float x, y;
};
bool minutes = false;;
POINT rotate_point(float cx, float cy, float angle, POINT p)
{
    angle = angle * 3.14 / 180;
    float s = sin(angle);
    float c = cos(angle);

    // translate point back to origin:
    p.x -= cx;
    p.y -= cy;

    // rotate point
    float xnew = p.x * c - p.y * s;
    float ynew = p.x * s + p.y * c;

    // translate point back:
    p.x = xnew + cx;
    p.y = ynew + cy;
    return p;
}

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
  // to be implemeted later
}

QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
  return QSize(800, 1100);
}

void RenderWidget::paintEvent(QPaintEvent *)
{
  
  QPainter painter(this);

  //painter.setRenderHint(QPainter::Antialiasing, false);
  QColor color(0, 0, 0);
  painter.setPen(color);
  int c = 1;
  if (c == 1) {
      painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
      drawArc((width() - 1)/2, (height() - 1)/2, 30, 150, 300);
      drawTheClock();
      int h, m;
      time_t now = time(0);
      tm* ltm = localtime(&now);;
      h = ltm->tm_hour;
      h %= 12;
      m = ltm->tm_min;
      std::cout << h << " " << m << "\n";
      drawTime(h, m);
      drawLine(659, 498, 690, 670 , false);
      drawLine(140, 499, 110, 670, false);
      drawLine(690, 670, 110, 670 , false);
  }
  else {
      painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
      drawTheClock();
      int h =10, m = 30;
      std :: cin >> h >> m;
      h %= 12;
      drawTime(h, m);
  }

  
}
void RenderWidget::drawTheClock() {
    QPainter painter(this);
    QColor color(0, 0, 0);
    painter.setPen(color);
    painter.setPen(QPen(Qt::black, 3));
    float x = (width() - 1) / 2;
    float y = (height() - 1) / 2;
    POINT s;
    s.x = x, s.y = y + 230;
    POINT e;
    e.x = x, e.y = y + 280;
    POINT TS = s, TE = e;
    POINT D;
    D.x = x;
    D.y = y + 260;
    POINT d = D;
    for (int i = 0; i < 60; i++) {
        painter.drawPoint(round(d.x), round(d.y));
        d = rotate_point(round(x), round(y), (i + 1) * 6, D);
    }

    for (int i = 0; i < 12; i++) {
        drawLine(round(s.x), round(s.y), round(e.x), round(e.y) , false);
        s = rotate_point(round(x), round(y), (i + 1) * 30, TS);
        e = rotate_point(round(x), round(y), (i + 1) * 30, TE);
    }
    //drawing the middle circle.
    drawCircle(x, y, 280);
    int r = 4;
    while (r > 1) {
        drawCircle(x, y, r);
        r--;
    }
}
void RenderWidget::drawTime(int h, int m) {
    float x = (width() - 1) / 2;
    float y = (height() - 1) / 2;
    POINT s;
    s.x = x, s.y = y - 200 ;
    POINT e;
    e.x = x, e.y = y;
    POINT TS = s, TE = e;
    s = rotate_point(round(x), round(y), h%12 * 30, TS);
    drawLine(round(s.x), round(s.y), round(e.x), round(e.y),false);
    s = rotate_point(round(x), round(y), m * 6, TS);
    drawLine(round(s.x), round(s.y), round(e.x), round(e.y),true);
}

void RenderWidget::drawLine(float x1, float y1, float x2, float y2 ,bool is)
{
  QPainter painter(this);

  QColor color(0, 0, 0);
  painter.setPen(color);
  if (!is) {
      painter.setPen(QPen(Qt::black, 3));
  }
  else painter.setPen(QPen(Qt::gray, 3));
  // m = dy / dx;
  float dx = x2 - x1;
  float dy = y2 - y1;
  float k;
  if (abs(dx) >= abs(dy))
      //m < 1
      k = abs(dx);
  else
      //m > 1;
      k = abs(dy);

  float incToX = dx / k;
  float incToY = dy / k;


  float x = x1;
  float y = y1;
  painter.drawPoint(ceil(x), ceil(y));

  for (int i = 1; i < k; i++)
  {
      x = x + incToX;
      y = y + incToY;
      painter.drawPoint(ceil(x), ceil(y));
  }
}
void RenderWidget::drawArc(float xc , float yc , float t1 , float t2 , float r) {
    QPainter painter(this);

    QColor color(0, 0, 0);
    painter.setPen(QPen(Qt::black, 3));
    float theta = 0;
    const float pi = 3.14;
    float i = t1;
    while (i <= t2) {
        theta = i * pi / 180;
        float x = xc + r * cos(theta);
        float y = yc + r * sin(theta);
        painter.drawPoint(round(x), round(y));
        i += 0.05;
    }
}
void RenderWidget::drawCircle(float xc, float yc, float r){
    QPainter painter(this);

    QColor color(0, 0, 0);
    painter.setPen(QPen(Qt::black , 3));
    float theta = 0;
    const float pi = 3.14;
    float i = 0;
    while (i <= 360) {
        theta = i * pi / 180;
        float x = xc + r * cos(theta);
        float y = yc + r * sin(theta);
        painter.drawPoint(round(x), round(y));
        i+=0.05;
    }
}
