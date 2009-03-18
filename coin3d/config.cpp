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

namespace Coin3d {

ConfigWidget::ConfigWidget(QWidget *parent)
    : QGroupBox("Config", parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button;

    // fit to win button
    button = new QPushButton("Fit to win");
    layout->addWidget(button);
    connect(button, SIGNAL(clicked(bool)),
            this, SLOT(_fitToWinSlot(bool)));

    setLayout(layout);
}


void ConfigWidget::_fitToWinSlot(bool ch)
{
    emit fitToWin();
}

}

}
