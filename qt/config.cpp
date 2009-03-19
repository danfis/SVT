/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "config.hpp"


#include "config.moc"

namespace SVT {

namespace Qt {

ConfigWidget::ConfigWidget(QWidget *parent)
    : QGroupBox("Config", parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button;
    QHBoxLayout *bg_layout;
    QGroupBox *bg_group;

    // fit to win button
    button = new QPushButton("Fit to win");
    layout->addWidget(button);

    // Bg Color
    bg_group = new QGroupBox("Bg Color");
    bg_layout = new QHBoxLayout;

    _bg_r = new QDoubleSpinBox();
    _bg_r->setRange(0., 1.);
    _bg_r->setSingleStep(0.05);
    bg_layout->addWidget(_bg_r);

    _bg_g = new QDoubleSpinBox();
    _bg_g->setRange(0., 1.);
    _bg_g->setSingleStep(0.05);
    bg_layout->addWidget(_bg_g);

    _bg_b = new QDoubleSpinBox();
    _bg_b->setRange(0., 1.);
    _bg_b->setSingleStep(0.05);
    bg_layout->addWidget(_bg_b);

    bg_group->setLayout(bg_layout);
    layout->addWidget(bg_group);

    // Connections
    connect(button, SIGNAL(clicked(bool)),
            this, SLOT(_fitToWinSlot(bool)));

    connect(_bg_r, SIGNAL(valueChanged(double)),
            this, SLOT(_bgColorRSlot(double)));
    connect(_bg_g, SIGNAL(valueChanged(double)),
            this, SLOT(_bgColorGSlot(double)));
    connect(_bg_b, SIGNAL(valueChanged(double)),
            this, SLOT(_bgColorBSlot(double)));

    setLayout(layout);
}

void ConfigWidget::setBgColor(double r, double g, double b)
{
    _bg_r->setValue(r);
    _bg_g->setValue(g);
    _bg_b->setValue(b);
}


void ConfigWidget::_fitToWinSlot(bool ch)
{
    emit fitToWin();
}

void ConfigWidget::_bgColorRSlot(double v)
{
    emit bgColorR(v);
}

void ConfigWidget::_bgColorGSlot(double v)
{
    emit bgColorG(v);
}

void ConfigWidget::_bgColorBSlot(double v)
{
    emit bgColorB(v);
}

}

}
