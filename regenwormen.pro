QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

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
    action.cpp \
    action_type.cpp \
    dice.cpp \
    dice_selection.cpp \
    dice_selections.cpp \
    die.cpp \
    game.cpp \
    game_state.cpp \
    main.cpp \
    game_dialog.cpp \
    strategy.cpp \
    tile.cpp \
    tiles.cpp \
    turn.cpp \
    turns.cpp

HEADERS += \
    action.h \
    action_type.h \
    dice.h \
    dice_selection.h \
    dice_selections.h \
    die.h \
    game.h \
    game_dialog.h \
    game_state.h \
    strategy.h \
    tile.h \
    tiles.h \
    turn.h \
    turns.h

FORMS += \
    game_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
