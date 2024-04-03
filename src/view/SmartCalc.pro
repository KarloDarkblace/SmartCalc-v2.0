QT       += core gui widgets printsupport

CONFIG += c++17

SOURCES += \
    ../controller/credit/s21_qcredit_controller.cc \
    ../controller/deposit/s21_qdeposit_controller.cc \
    ../controller/main/s21_qmain_controller.cc \
    ../model/calculators/credit/s21_credit_calc.cc \
    ../model/calculators/deposit/s21_deposit_calc.cc \
    ../model/polish/functions/s21_calc_polish.cc \
    ../model/polish/functions/s21_main_polish.cc \
    ../model/polish/functions/s21_scan_polish.cc \
    creditcalc.cc \
    depositcalc.cc \
    graphwindow.cc \
    main.cc \
    mainwindow.cc \
    qcustomplot.cc

HEADERS += \
    ../controller/credit/s21_qcredit_controller.h \
    ../controller/deposit/s21_qdeposit_controller.h \
    ../controller/main/s21_qmain_controller.h \
    ../model/calculators/credit/s21_credit_calc.h \
    ../model/calculators/deposit/s21_deposit_calc.h \
    ../model/polish/s21_calculator_model.h \
    creditcalc.h \
    depositcalc.h \
    graphwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditcalc.ui \
    depositcalc.ui \
    graphwindow.ui \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../model/polish
INCLUDEPATH += $$PWD/../model/calculators/credit
INCLUDEPATH += $$PWD/../model/calculators/deposit
INCLUDEPATH += $$PWD/../controller/credit/
INCLUDEPATH += $$PWD/../controller/deposit/
INCLUDEPATH += $$PWD/../controller/main/
