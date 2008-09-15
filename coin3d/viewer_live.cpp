#include "viewer_live.hpp"

#include "viewer_live.moc"

namespace SVT {

namespace Coin3d {

ViewerLive::ViewerLive(QWidget *win)
    : Viewer(win)
{
    _dyn = new SoSwitch;
    _dyn->whichChild = SO_SWITCH_ALL;
    _dyn->ref();

    _root->addChild(_dyn);

    connect(this, SIGNAL(_setDynSceneGraphSignal(SoNode *)),
            this, SLOT(_setDynSceneGraph(SoNode *)));
    connect(this, SIGNAL(_clearDynSceneGraphSignal()),
            this, SLOT(_clearDynSceneGraph()));
}

ViewerLive::~ViewerLive()
{
    _dyn->unref();
}

void ViewerLive::_setDynSceneGraph(SoNode *root)
{
    _dyn->removeAllChildren();
    _dyn->addChild(root);
    //setSceneGraph(_root);
}

void ViewerLive::_clearDynSceneGraph()
{
    _dyn->removeAllChildren();
}

void ViewerLive::setDynSceneGraph(SoNode *root)
{
    emit _setDynSceneGraph(root);
}

void ViewerLive::clearDynSceneGraph()
{
    emit _clearDynSceneGraphSignal();
}

} /* namespace Coin3d */

} /* namespace SVT */
