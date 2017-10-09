areaName := aquarobot

dependentMods := dmGL dmu dm

archSrc := \
	Vector.cpp \
	EulerAng.cpp \
	Posture.cpp \
	MatrixMy.cpp \
	LegLink.cpp \
	Leg.cpp \
	Body.cpp \
	Robot.cpp \
	GaitAlgorithm.cpp

progSrc := \
	aquarobot.cpp

#MYCFLAGS := -DDM_DOUBLE_PRECISION -DHYDRODYNAMICS

# -------------------------------------------------------------------------

ifeq ($(GLOBAL),true)
include make/arearules.mk
else
include ../make/local.mk
endif
