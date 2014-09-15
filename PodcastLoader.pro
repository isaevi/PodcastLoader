# CONFIG += console

HEADERS += \
    recordinfo.h \
    parser.h \
    downloader.h \
    rssfetcher.h \
    feeddata.h \
    rssapplication.h \
    recordsmanager.h \
    entrypoint.h \
    feedmanager.h \
    rssmanager.h \
    helperinterfaces.h
SOURCES += main.cpp \
    recordinfo.cpp \
    parser.cpp \
    downloader.cpp \
    rssfetcher.cpp \
    feeddata.cpp \
    rssapplication.cpp \
    recordsmanager.cpp \
    entrypoint.cpp \
    feedmanager.cpp \
    rssmanager.cpp
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
    img/settings.png \
    RssRecordsDelegate.qml \
    img/download_media.png \
    BusyIndicator.qml \
    img/busy.png

RESOURCES += \
    res.qrc
