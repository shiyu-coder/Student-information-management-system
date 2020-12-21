QT       += core gui
QT       += sql
QT       += network
QT       +=webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutwidget.cpp \
    adddeptwidget.cpp \
    addmsgwidget.cpp \
    addprowidget.cpp \
    addscholarwidget.cpp \
    addstuwidget.cpp \
    addteacherwidget.cpp \
    adminwindow.cpp \
    applyprowidget.cpp \
    applyscholarwidget.cpp \
    connectdabasewidget.cpp \
    data.cpp \
    dataquery.cpp \
    deptwidget.cpp \
    lesson.cpp \
    loadclassfromwebwidget.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyapplywidget.cpp \
    modifydeptmsgwidget.cpp \
    modifylessonwidget.cpp \
    modifystuwidget.cpp \
    modifyteacherwidget.cpp \
    scholarmsgwidget.cpp \
    student.cpp \
    studentwindow.cpp \
    teacher.cpp \
    teacherwindow.cpp \
    weblogwidget.cpp

HEADERS += \
    aboutwidget.h \
    adddeptwidget.h \
    addmsgwidget.h \
    addprowidget.h \
    addscholarwidget.h \
    addstuwidget.h \
    addteacherwidget.h \
    adminwindow.h \
    applyprowidget.h \
    applyscholarwidget.h \
    connectdabasewidget.h \
    data.h \
    dataquery.h \
    deptwidget.h \
    lesson.h \
    loadclassfromwebwidget.h \
    loginwidget.h \
    mainwindow.h \
    modifyapplywidget.h \
    modifydeptmsgwidget.h \
    modifylessonwidget.h \
    modifystuwidget.h \
    modifyteacherwidget.h \
    scholarmsgwidget.h \
    student.h \
    studentwindow.h \
    teacher.h \
    teacherwindow.h \
    weblogwidget.h

FORMS += \
    aboutwidget.ui \
    adddeptwidget.ui \
    addmsgwidget.ui \
    addprowidget.ui \
    addscholarwidget.ui \
    addstuwidget.ui \
    addteacherwidget.ui \
    adminwindow.ui \
    applyprowidget.ui \
    applyscholarwidget.ui \
    connectdabasewidget.ui \
    deptwidget.ui \
    loadclassfromwebwidget.ui \
    loginwidget.ui \
    mainwindow.ui \
    modifyapplywidget.ui \
    modifydeptmsgwidget.ui \
    modifylessonwidget.ui \
    modifystuwidget.ui \
    modifyteacherwidget.ui \
    scholarmsgwidget.ui \
    studentwindow.ui \
    teacherwindow.ui \
    weblogwidget.ui

TRANSLATIONS += \
    SIM_System_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    SIMS_res.qrc

msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
