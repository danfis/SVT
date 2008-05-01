#ifndef _INIT_HPP_
#define _INIT_HPP_

#include <Inventor/Qt/SoQt.h>
#include <QWidget>
#include <QMainWindow>
#include <QStatusBar>
#include "viewer.hpp"


class Coin3dTools {
  private:
    static QMainWindow *_mainwin;
    static QWidget *_win;
    static QStatusBar *_status_bar;
    static Viewer *_viewer;

  public:
    /**
     * Initialize Coin3dTools lib
     */
    static void init(const char *title="");

    /**
     * Starts Coin3dTools previously initialized
     */
    static void mainLoop();

    /**
     * Finish everything (free memory etc...)
     */
    static void finish();

    /**
     * Creates and return Viewer instance. If Viewer is already created it
     * only returns pointer to it.
     */
    static Viewer *viewer();
};

#endif
