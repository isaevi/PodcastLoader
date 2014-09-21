CONFIG += gui

HEADERS += \
    recordinfo.h \
    parser.h \
    downloader.h \
    rssfetcher.h \
    feeddata.h \
    rssapplication.h \
    entrypoint.h \
    feedmanager.h \
    rssmanager.h \
    helperinterfaces.h \
    downloadmanager.h
SOURCES += main.cpp \
    recordinfo.cpp \
    parser.cpp \
    downloader.cpp \
    rssfetcher.cpp \
    feeddata.cpp \
    rssapplication.cpp \
    entrypoint.cpp \
    feedmanager.cpp \
    rssmanager.cpp \
    downloadmanager.cpp
QT += network xml xmlpatterns quick qml
QMAKE_CXXFLAGS = -std=c++11
#CONFIG += c++11

FORMS +=

OTHER_FILES += \
    main.qml \
    LabeledTextInput.qml \
    FeedDetails.qml \
    FeedItemDelegate.qml \
    img/settings.png \
    RssRecordsDelegate.qml \
    img/download_media.png \
    BusyIndicator.qml \
    img/busy.png \
    ScrollBar.qml

RESOURCES += \
    res.qrc
