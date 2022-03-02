// Last modified by: Yaseen Joba (181033), on 2.03.2021

#include "PPUViewer.h"

#include <QApplication>
#include<iostream>
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  PPUViewer tPPUViewer;
  tPPUViewer.show();

  return app.exec();
}