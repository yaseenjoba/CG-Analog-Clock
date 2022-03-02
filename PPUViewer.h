// Last modified by: Yaseen Joba (181033), on 2.03.2021


#pragma once

#include <QWidget>

class RenderWidget;

class PPUViewer : public QWidget
{
  Q_OBJECT

public:
  PPUViewer();

private:
  RenderWidget *renderWidget;

};

