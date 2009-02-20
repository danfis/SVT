#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "config.hpp"


#include "config.moc"

namespace SVT {

namespace Qt2D {

ConfigWidget::ConfigWidget(QWidget *parent)
    : QGroupBox("Config", parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hlayout;
    QPushButton *button;

    // fit to win button
    button = new QPushButton("Fit to win");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)),
            this, SLOT(_fitToWinSlot(bool)));

    // scale
    hlayout = new QHBoxLayout;

    hlayout->addWidget(new QLabel("Scale:"));

    _scale = new QDoubleSpinBox;
    _scale->setMinimum(0.);
    _scale->setSingleStep(0.05);
    hlayout->addWidget(_scale);
    connect(_scale, SIGNAL(valueChanged(double)),
            this, SLOT(_scaleSlot(double)));

    layout->addLayout(hlayout);

    setLayout(layout);
}


void ConfigWidget::_scaleSlot(double val)
{
    emit scaleChanged(val);
}

void ConfigWidget::_fitToWinSlot(bool ch)
{
    emit fitToWin();
}

}

}
