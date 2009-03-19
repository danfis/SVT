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

#ifndef COIN3D_CONFIG_HPP_
#define COIN3D_CONFIG_HPP_

#include <QGroupBox>
#include <QDoubleSpinBox>

namespace SVT {

namespace Qt {


class ConfigWidget : public QGroupBox {
    Q_OBJECT

  private:
    QDoubleSpinBox *_bg_r, *_bg_g, *_bg_b;

  public:
    ConfigWidget(QWidget *parent = 0);

    void setBgColor(double r, double g, double b);

  private slots:
    void _fitToWinSlot(bool ch);
    void _bgColorRSlot(double v);
    void _bgColorGSlot(double v);
    void _bgColorBSlot(double v);

  signals:
    void fitToWin();
    void bgColorR(double v);
    void bgColorG(double v);
    void bgColorB(double v);
};

}

}

#endif
