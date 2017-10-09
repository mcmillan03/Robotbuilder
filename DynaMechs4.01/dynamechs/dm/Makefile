areaName := dm

dependentMods :=

archSrc := \
	dmObject.cpp \
	dmSystem.cpp \
	dmArticulation.cpp \
	dmClosedArticulation.cpp \
	dmLink.cpp \
	dmStaticRootLink.cpp \
	dmZScrewTxLink.cpp \
	dmRigidBody.cpp \
	dmMobileBaseLink.cpp \
	dmSphericalLink.cpp \
	dmQuaternionLink.cpp \
	dmMDHLink.cpp \
	dmPrismaticLink.cpp \
	dmRevoluteLink.cpp \
	dmActuator.cpp \
	dmRevDCMotor.cpp \
	dmEnvironment.cpp \
	dmTreadmill.cpp \
	dmForce.cpp \
	dmContactModel.cpp \
	dmSecondaryForce.cpp \
	dmSecondaryJoint.cpp \
	dmSecondarySphericalJoint.cpp \
	dmSecondaryPrismaticJoint.cpp \
	dmSecondaryRevoluteJoint.cpp \
	dmIntegrator.cpp \
	dmIntegEuler.cpp \
	dmIntegRK4.cpp \
	dmIntegRK45.cpp \
	svd_linpack.cpp \
	gldraw.cpp

progSrc :=

#MYCFLAGS := -DDM_DOUBLE_PRECISION -DHYDRODYNAMICS

# -------------------------------------------------------------------------

ifeq ($(GLOBAL),true)
include make/arearules.mk
else
include ../make/local.mk
endif
