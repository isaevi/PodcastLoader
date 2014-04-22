HEADERS += \
    recordinfo.h \
    parser.h \
    downloader.h \
    rssfetcher.h \
    feeddata.h \
    rssapplication.h \
    recordsmanager.h \
    rsslist.h
SOURCES += main.cpp \
    recordinfo.cpp \
    parser.cpp \
    downloader.cpp \
    rssfetcher.cpp \
    feeddata.cpp \
    rssapplication.cpp \
    recordsmanager.cpp \
    rsslist.cpp
QT += network xml widgets xmlpatterns
QMAKE_CXXFLAGS = -std=c++11

# install
target.path = $$[QT_INSTALL_EXAMPLES]/xml/rsslisting
INSTALLS += target
