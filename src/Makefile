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

TARGETS = viewer viewer.o app parser

VIEWER_CXXFLAGS = $(CXXFLAGS) $(COIN_CXXFLAGS) $(SOQT_CXXFLAGS) \
	$(QT_CXXFLAGS)
VIEWER_LDFLAGS = $(LDFLAGS) $(COIN_LDFLAGS) $(SOQT_LDFLAGS) $(QT_LDFLAGS)

all: $(TARGETS)

parser: parser.o lexer.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lfl

app: app.cpp viewer.o viewer_push_button.o
	$(CXX) $(VIEWER_CXXFLAGS) -o $@ $^ $(VIEWER_LDFLAGS)

viewer: viewer_app.cpp examiner_viewer.o viewer.o viewer_push_button.o \
        objdata.o
	$(CXX) $(VIEWER_CXXFLAGS) -o $@ $^ $(VIEWER_LDFLAGS)

%.o: %.cpp %.hpp
	$(CXX) $(VIEWER_CXXFLAGS) -c -o $@ $<

lexer.c: lexer.l
	$(FLEX) -o $@ $<
lexer.o: lexer.c
	$(CC) $(CXXFLAGS) -c -o $@ $<

viewer_push_button.cpp: viewer_push_button.moc
%.moc: %.hpp
	$(MOC) -p'.' $< > $@

clean:
	rm -f $(TARGETS)
	rm -f *.o
	rm -f *~
	rm -f *.moc
	rm -f lexer.c

.PHONY: all clean
