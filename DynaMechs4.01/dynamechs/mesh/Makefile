areaName := mesh

dependentMods := dmGL dmu dm

archSrc :=

progSrc := \
	mesh.cpp

#MYCFLAGS := -DDM_DOUBLE_PRECISION -DHYDRODYNAMICS

# -------------------------------------------------------------------------

ifeq ($(GLOBAL),true)
include make/arearules.mk
else
include ../make/local.mk
endif
