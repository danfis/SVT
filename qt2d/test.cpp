#include <QApplication>

#include "../qt/main_window.hpp"
#include "painter.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SVT::Qt::MainWindow mw;

    mw.setCentralWidget(new SVT::Qt2D::Painter());

    mw.show();

    return app.exec();
}
