##############################################################################
# Global Variable Setup Section
##############################################################################

default: all

GLOBAL := true


libdir := lib/platform.$(DM_PLATFORM)
objdir := obj/platform.$(DM_PLATFORM)
exedir := bin/platform.$(DM_PLATFORM)

include make/make.platform.$(DM_PLATFORM)

# List all the modules (that should normally be compiled) in the src tree.
# Order does not matter.
modules := \
	dm \
	dmu

ifneq ($(NOGLUT),TRUE)
modules += \
	dmGL \
	testdm \
	aquarobot \
	mesh

ifeq ($(DM_DEMOS),TRUE)
modules += \
	apsim \
	artQuad3D \
	hopper \
	motPlat \
	prisBnd3d \
	spherMesh \
	waav
endif
endif

cleanGoal := $(strip $(filter %Clean %clean,$(MAKECMDGOALS)))

ifeq ("$(cleanGoal)","")
mkcmd1 = if [ ! -d $(libdir) ]; then mkdir -p $(libdir); fi;
mkcmd1 += if [ ! -d $(objdir) ]; then mkdir -p $(objdir); fi;
mkcmd1 += if [ ! -d $(exedir) ]; then mkdir -p $(exedir); fi;
junk2 := $(shell $(mkcmd1))
endif

GLUTLIB := 0
include $(addsuffix /Makefile,$(modules))

moduleNames := $(notdir $(modules))

incs := $(addprefix -I,$(modules))

##############################################################################
# Implicit Rule Section
##############################################################################

vpath %.d $(objdir)
vpath %.cpp $(modules)
vpath %.o $(objdir)
vpath %.exe $(exedir)
vpath %.$(LIBSFX) $(libdir)

$(objdir)/%.o : %.cpp
	@echo _____________________________________________________________
	@echo Compiling $@
	$(CXX) $(incs) $(CXXFLAGS) -D$(<D)_DLL_FILE $< $(OBJNAMEARG)$@

$(exedir)/%.exe : %.cpp %.o
	@echo _____________________________________________________________
	@echo Linking $@
	$(LINKER) $(objdir)/$*.o $(EXENAMEARG)$@ $(LINKDIRARG)$(libdir) $($(<D)ExeLibs) $(LDGLUT) $(LDFLAGS)

%.d:
	@echo _____________________________________________________________
	@echo Computing dependencies for $*
	make/depend.pl $@ $? -- $(incs) $(DEPENDFLAGS)


##############################################################################
# Global Target Section
##############################################################################

.PHONY: default rmdirs all clean distclean force true

rmdirs:
	if [ -d lib ]; then rm -rf lib; fi;
	if [ -d obj ]; then rm -rf obj; fi;
	if [ -d bin ]; then rm -rf bin; fi;

all: $(addsuffix Tree,$(moduleNames))

clean: $(addsuffix Clean,$(moduleNames))

distclean: rmdirs

force:
	$(MAKE) all FORCE=true

true:
