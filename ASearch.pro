TARGET = ASearch
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -O2 -Wall -Wextra



SOURCES += \
        tinyxml2.cpp \
        xmllogger.cpp\
        isearch.cpp\
        mission.cpp\
        map.cpp \
        dijkstra.cpp \
        config.cpp \
        astar.cpp \
        main.cpp \
        environmentoptions.cpp \
        FakeMap.cpp \
        IOpenContainer.cpp \
        OList.cpp \
        OPriorityQueue.cpp \
        OSet.cpp \
        OVctList.cpp \
        OVctSet.cpp \
        OVctProirityQueue.cpp

HEADERS += \
        tinyxml2.h \
        node.h \
        gl_const.h \
        xmllogger.h \
        isearch.h \
        mission.h \
        map.h \
        ilogger.h \
        dijkstra.h \
        config.h \
        astar.h \
        searchresult.h \
        environmentoptions.h \
        FakeMap.h \
        IOpenContainer.h \
        OList.h \
        OPriorityQueue.h \
        Compare.h \
        OSet.h \
        OVctList.h \
        OVctSet.h \
        OVctProirityQueue.h
