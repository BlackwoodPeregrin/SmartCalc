QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PlotLibrary/qcustomplot.cpp \
    main.cpp \
    model/modelCalc.cpp \
    viewer/viewerCalc.cpp \
    viewer/viewerCalcCredit.cpp \
    viewer/viewerCalcDeposit.cpp \
    viewer/viewerCalcX.cpp \
    viewer/viewerPlot.cpp

HEADERS += \
    PlotLibrary/qcustomplot.h \
    conteiners_SQ/s21_queue.h \
    conteiners_SQ/s21_stack.h \
    controller/checkInputError.h \
    controller/controllerCalc.h \
    controller/controllerCreditCalc.h \
    controller/controllerDepositCalc.h \
    model/modelCalc.h \
    model/modelCreditCalc.h \
    model/modelDepositCalc.h \
    viewer/ui_main_Calc.h \
    viewer/viewerCalc.h \
    viewer/viewerCalcCredit.h \
    viewer/viewerCalcDeposit.h \
    viewer/viewerCalcX.h \
    viewer/viewerPlot.h

FORMS += \
    viewer/ui/credit_Calc.ui \
    viewer/ui/credit_CalcResult.ui \
    viewer/ui/deposit_Calc.ui \
    viewer/ui/deposit_CalcResult.ui \
    viewer/ui/plot.ui \
    viewer/ui/x_Calc.ui

TRANSLATIONS += \
    calc_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    calc_en_US.ts \
    style.css \
    viewer/button_style.css
