CXX = g++
CC = gcc
MOC = moc
FLEX = flex

CXXFLAGS = -g -pedantic -Wall
QT_CXXFLAGS = $(shell pkg-config QtGui --cflags)
QT_LDFLAGS = $(shell pkg-config QtGui --libs)
COIN_CXXFLAGS = $(shell coin-config --cppflags)
COIN_LDFLAGS = $(shell coin-config --ldflags --libs)
SOQT_CXXFLAGS = $(shell soqt-config --cppflags)
SOQT_LDFLAGS = $(shell soqt-config --ldflags --libs)

export CXX
export CC
export MOC
export FLEX
export CXXFLAGS
export QT_CXXFLAGS
export QT_LDFLAGS
export COIN_CXXFLAGS
export COIN_LDFLAGS
export SOQT_CXXFLAGS
export SOQT_LDFLAGS

all:
	$(MAKE) -C parser
	$(MAKE) -C common
	$(MAKE) -C apps

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C common clean
	$(MAKE) -C apps clean

.PHONY: all clean
