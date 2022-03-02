// Last modified by: Yaseen Joba (181033), on 2.03.2021



#pragma once

#include <QWidget>

class RenderWidget : public QWidget
{
    Q_OBJECT

  public:
    RenderWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
	  void drawLine(float x1, float y1, float x2, float y2 , bool is);
      void drawCircle(float xc, float yc, float r);
      void drawTheClock();
      void drawTime(int h, int m);
      void drawArc(float x, float y, float t1, float t2, float r);

  protected:
    void paintEvent(QPaintEvent *event) override;

};
