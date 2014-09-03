# CONFIG += console

HEADERS += \
    recordinfo.h \
    parser.h \
    downloader.h \
    rssfetcher.h \
    feeddata.h \
    rssapplication.h \
    recordsmanager.h \
    rsslist.h \
    configuration.h \
    entrypoint.h
SOURCES += main.cpp \
    recordinfo.cpp \
    parser.cpp \
    downloader.cpp \
    rssfetcher.cpp \
    feeddata.cpp \
    rssapplication.cpp \
    recordsmanager.cpp \
    rsslist.cpp \
    configuration.cpp \
    entrypoint.cpp
QT += network xml widgets xmlpatterns quick qml
QMAKE_CXXFLAGS = -std=c++11
#CONFIG += c++11

# install
target.path = $$[QT_INSTALL_EXAMPLES]/xml/rsslisting
INSTALLS += target

FORMS +=

OTHER_FILES += \
    main.qml \
    LabeledTextInput.qml \
    FeedDetails.qml \
    FeedItemDelegate.qml \
    img/settings.png

RESOURCES += \
    res.qrc
