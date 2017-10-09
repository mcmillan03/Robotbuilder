areaName := dmu

dependentMods := dm

archSrc := \
	dmLock.cpp \
	dmLoader.cpp \
	dmLoader_dm.cpp \
	dmLoader_dm203.cpp \
	dmLoader_dm21.cpp \
	dmLoader_dm30.cpp \
	dmLoader_dm40.cpp \
	dmLoader_env.cpp \
	dmUtils.cpp \
	glLoadModels.cpp

progSrc :=

#MYCFLAGS := -DDM_DOUBLE_PRECISION -DHYDRODYNAMICS

# -------------------------------------------------------------------------

ifeq ($(GLOBAL),true)
include make/arearules.mk
else
include ../make/local.mk
endif
