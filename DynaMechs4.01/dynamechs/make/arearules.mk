
$(areaName)CleanFiles :=

archive :=
progs :=

##############################################################################
# Area Archive Section
##############################################################################

ifdef archSrc
archive := $(libdir)/$(LIBPFX)$(areaName).$(LIBSFX)
libarchive := $(libdir)/$(areaName).lib
exparchive := $(libdir)/$(areaName).exp

archObjs := $(addprefix $(objdir)/,$(addsuffix .o,$(basename $(notdir $(archSrc)))))

.SECONDARY: $(archObjs)


$(notdir $(archive))Objs := $(archObjs)
ifdef archiveDoesntNeedLibs
$(notdir $(archive))Libs := 
else
$(notdir $(archive))Libs := $(patsubst %,$(LINKLIBARG)%$(LINKLIBSFX),$(dependentMods))
endif

$(areaName)CleanFiles += $(archObjs) $(archive) $(libarchive) $(exparchive)

$(archObjs): $(FORCE)

ifeq ($(GLUTLIB),1) 
$(archive): $(archObjs) $(FORCE)
	@echo _____________________________________________________________
	@echo Updating Dynamic Library $(@F)
	$(SHLINKER) $(SHLKFLAG) $($(@F)Objs) $(LINKDIRARG)$(libdir) $($(@F)Libs) $(LIBLDGLUT) $(LDFLAGS) $(SHLNAMEARG)$(libdir)/$(@F)
else
$(archive): $(archObjs) $(FORCE)
	@echo _____________________________________________________________
	@echo Updating Dynamic Library $(@F)
	$(SHLINKER) $(SHLKFLAG) $($(@F)Objs) $(LINKDIRARG)$(libdir) $($(@F)Libs) $(LDFLAGS) $(SHLNAMEARG)$(libdir)/$(@F)
endif

endif  # ifdef archSrc


##############################################################################
# Area Program Section
##############################################################################

ifdef progSrc
progs := $(addprefix $(exedir)/,$(addsuffix .exe,$(basename $(notdir $(progSrc)))))

.SECONDARY: $(addprefix $(objdir)/,$(addsuffix .o,$(basename $(notdir $(progSrc)))))

$(areaName)CleanFiles += $(progs) $(addprefix $(objdir)/,$(addsuffix .o,$(basename $(notdir $(progSrc)))))

$(progs:.exe=.o): $(FORCE)
$(progs): $(FORCE)

endif # ifdef progSrc



dep := $(objdir)/$(areaName).d
$(dep): $(archSrc) $(progSrc)

ifeq ("$(cleanGoal)","")
include $(dep)
endif


##############################################################################
# Area Permanent Variables Section
##############################################################################


ifdef archSrc
$(areaName)ExeLibs := $(patsubst %,$(LINKLIBARG)%$(LINKLIBSFX),$(areaName) $(dependentMods))
else
$(areaName)ExeLibs := $(patsubst %,$(LINKLIBARG)%$(LINKLIBSFX),$(dependentMods))
endif


##############################################################################
# Area Target Section
##############################################################################

.PHONY: $(areaName) $(areaName)Force $(areaName)Clean $(areaName)Tree

$(areaName): $(archive) $(progs)

$(areaName)Force:
	$(MAKE) $(patsubst %Force,%,$@) FORCE=true

$(areaName)Clean:
	-rm -f $($(patsubst %Clean,%,$@)CleanFiles)

$(areaName)Tree: $(addsuffix Tree,$(dependentMods)) $(areaName)

GLUTLIB := 0
