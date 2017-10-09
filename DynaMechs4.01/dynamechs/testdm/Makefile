areaName := testdm

dependentMods := dmGL dmu dm

archSrc :=

progSrc :=  \
	simple.cpp \
	star.cpp \
	pendulum.cpp \
	tree.cpp \
	carts.cpp \
	wire.cpp \
	ring.cpp \
	crank.cpp

#MYCFLAGS := -DDM_DOUBLE_PRECISION -DHYDRODYNAMICS

# -------------------------------------------------------------------------

ifeq ($(GLOBAL),true)
include make/arearules.mk
else
include ../make/local.mk
endif
