#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>

#include "style_dialog.hpp"
#include "style_dialog.moc"
#include "msg.hpp"

StyleDialog::StyleDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout;
    QGroupBox *points_box = new QGroupBox("Points", this);


    // points:
    QLabel *label = new QLabel("Size");
    QDoubleSpinBox *spin = new QDoubleSpinBox();
    spin->setSingleStep(0.1);
    spin->setRange(0, 10);

    vlayout->addWidget(label);
    vlayout->addWidget(spin);

    points_box->setLayout(vlayout);


    resize(100, 100);
}



StylePushButton::StylePushButton(QWidget *parent)
        : QPushButton(parent), _parent(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(showDialog()));
}
void StylePushButton::showDialog()
{
    StyleDialog dialog(_parent);
    dialog.exec();
}
