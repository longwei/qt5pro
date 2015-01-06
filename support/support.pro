TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
            app/idletime \
            app/ascii \
            app/paste \
            app/combo

SUBDIRS += \
            module/test_util \
            module/xml_char_filter

SUBDIRS += \
            test/test_xml_char_filter
