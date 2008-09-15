include Makefile.include

export NDEBUG

all:
	$(MAKE) -C parser
	$(MAKE) -C common
	$(MAKE) -C qt
	$(MAKE) -C coin3d
	$(MAKE) -C apps

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C common clean
	$(MAKE) -C qt clean
	$(MAKE) -C coin3d clean
	$(MAKE) -C apps clean

.PHONY: all clean
