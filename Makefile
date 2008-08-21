include Makefile.include

export NDEBUG

all:
	$(MAKE) -C parser
	$(MAKE) -C common
	$(MAKE) -C apps

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C common clean
	$(MAKE) -C apps clean

.PHONY: all clean
