######################################################################
# Automatically generated by qmake (3.1) Tue Dec 24 13:04:31 2019
######################################################################

#qt5.13.2默认启动支持c++14,因此不需要CONFIG +=c++14

TEMPLATE = app
QT +=widgets
TARGET = abc
INCLUDEPATH += . core component

#可执行文件放在此目录,即当前工程目录
# DESTDIR =$$PWD

#msvc编译器识别正常utf-8
msvc {
	QMAKE_CFLAGS += /utf-8
	QMAKE_CXXFLAGS += /utf-8
}

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += \
           component/demosim.h \
           component/hanoisim.h \
           component/mazesim.h \
           component/quicksortsim.h \
           component/rbtreesimulation.h \
           core/common.h \
           core/myscreen.h \
           core/setting.h \
           core/simulator.h \
           core/widget.h
FORMS += core/form.ui core/widget.ui
SOURCES += \
           component/demosim.cpp \
           component/hanoisim.cpp \
           component/mazesim.cpp \
           component/quicksortsim.cpp \
           component/rbtreesimulation.cpp \
           core/main.cpp \
           core/myscreen.cpp \
           core/setting.cpp \
           core/simulator.cpp \
           core/widget.cpp
TRANSLATIONS +=abc_en_US.ts \
            abc_zh_CN.ts \

#message($$CONFIG)
#message($$QMAKESPEC)
