HEADERS += \
    $$PWD/loggermanagement.h \
    $$PWD/loggerwidget.h \
    $$PWD/logreplay.h \
    $$PWD/systemlogger.h \
    $$PWD/xlsxlogger.h

SOURCES += \
    $$PWD/loggermanagement.cpp \
    $$PWD/loggerwidget.cpp \
    $$PWD/logreplay.cpp \
    $$PWD/systemlogger.cpp \
    $$PWD/xlsxlogger.cpp

include($$PWD/xlsx/qtxlsx.pri)
INCLUDEPATH += $$PWD/xlsx
