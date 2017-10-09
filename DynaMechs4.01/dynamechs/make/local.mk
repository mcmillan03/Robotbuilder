SHELL=/bin/sh

all:
	cd ..; $(MAKE) $(areaName)

force:
	cd ..; $(MAKE) $(areaName)Force

clean:
	cd ..; $(MAKE) $(areaName)Clean

realclean: realClean
realClean:
	cd ..; $(MAKE) $(areaName)RealClean

distclean: distClean
distClean:
	cd ..; $(MAKE) $(areaName)DistClean

