CONFIG += C++11

HEADERS += \
    tst_xmlcharfilter.h

SOURCES += \
    main.cpp \
    tst_xmlcharfilter.cpp


DEPENDS_STATIC = test_util xml_char_filter

include(../test.pri)

