
CONFIG += c++11

TEMPLATE = subdirs
defined(QXORM_INCLUDE) {
    SUBDIRS = billing/billing.pro
}
#    gui/gui.pro
