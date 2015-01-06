LIBS += -L../../bin
LIBS += -L../../lib

MODULE_LIBS =

for( module, DEPENDS_STATIC ) {
    INCLUDEPATH += ../../module/$$module
    DEPENDPATH  += ../../module/$$module

    !contains(CONFIG, staticlib) {
#        LIBS += -l$$module
        MODULE_LIBS += -l$$module

        unix {
            PRE_TARGETDEPS += ../../lib/lib$${module}.a
        }
        win32 {
            contains(QMAKE_CXX, g++){
                PRE_TARGETDEPS += ../../lib/lib$${module}.a
            } else {
                PRE_TARGETDEPS += ../../lib/$${module}.lib
            }
        }
    }
}

for( module, DEPENDS_SHARED ) {
    INCLUDEPATH += ../../module/$$module
    DEPENDPATH  += ../../module/$$module

    !contains(CONFIG, staticlib) {
#        LIBS += -l$$module
        MODULE_LIBS += -l$$module
    }
}

#the trick of listing all the libs twice does not work
#  (at least without tweaking qmake's behavior -- if that's possible)
#  hence, static libs are always added first
#  (and their order, as the order of the shared ones, should always
#   be correct -- when there are dependencies inside either set)
LIBS += $$MODULE_LIBS #$$MODULE_LIBS

#!include(3dparty.pri) {
#    error("please set up the 3dparty.pri file, see 3dparty.pri.sample for an example")
#}
