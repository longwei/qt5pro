TEMPLATE = subdirs

CONFIG += ordered

win32 {
    SUBDIRS += \
        breakpad \
        qxmpp \
        qtjson \
        simplecrypt \
        canberra \
        qtsparkle \
        qtsingleapplication
}

unix {
    SUBDIRS += \
              kdelibs
}

SUBDIRS += \
           common \
           qtwidget

win32 {
    SUBDIRS += hipchat \
        explore
}

#SUBDIRS +=  \
#           tests

#SUBDIRS +=  \
#           support

