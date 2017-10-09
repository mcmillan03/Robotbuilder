SHELL=/bin/sh
.SILENT:

# wildcard doesn't seem to work
#platforms := $(subst make/make.platform.,,$(wildcard make/make.platform.*))

platforms := $(shell make/platformlist.pl)


ifneq ($(filter $(MAKECMDGOALS),$(platforms)),)
export DM_PLATFORM := $(MAKECMDGOALS)
cmd := $(MAKE) -f make/masterrules.mk
else
ifeq ($(origin DM_PLATFORM),undefined)
cmd := echo "Please choose a platform: $(platforms)"
else
ifeq ($(filter $(DM_PLATFORM),$(platforms)),)
cmd := echo "Please choose a platform: $(platforms)"
else
cmd := $(MAKE) -f make/masterrules.mk $(MAKECMDGOALS)
endif
endif
endif

default:
#	echo $(cmd)
	$(cmd)

$(MAKECMDGOALS): default
