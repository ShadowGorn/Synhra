QT += core
QT -= gui

CONFIG += c++11

TARGET = Synhra
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

DISTFILES += \
    documentation/html/search/all_0.js \
    documentation/html/search/all_1.js \
    documentation/html/search/all_2.js \
    documentation/html/search/all_3.js \
    documentation/html/search/all_4.js \
    documentation/html/search/all_5.js \
    documentation/html/search/all_6.js \
    documentation/html/search/all_7.js \
    documentation/html/search/all_8.js \
    documentation/html/search/all_9.js \
    documentation/html/search/all_a.js \
    documentation/html/search/classes_0.js \
    documentation/html/search/enums_0.js \
    documentation/html/search/enumvalues_0.js \
    documentation/html/search/enumvalues_1.js \
    documentation/html/search/enumvalues_2.js \
    documentation/html/search/files_0.js \
    documentation/html/search/functions_0.js \
    documentation/html/search/functions_1.js \
    documentation/html/search/functions_2.js \
    documentation/html/search/functions_3.js \
    documentation/html/search/functions_4.js \
    documentation/html/search/functions_5.js \
    documentation/html/search/search.js \
    documentation/html/search/searchdata.js \
    documentation/html/search/variables_0.js \
    documentation/html/search/variables_1.js \
    documentation/html/annotated_dup.js \
    documentation/html/dynsections.js \
    documentation/html/files.js \
    documentation/html/jquery.js \
    documentation/html/main_8cpp.js \
    documentation/html/menu.js \
    documentation/html/menudata.js \
    documentation/html/navtree.js \
    documentation/html/navtreedata.js \
    documentation/html/navtreeindex0.js \
    documentation/html/resize.js \
    documentation/html/structerror.js \
    documentation/html/search/close.png \
    documentation/html/search/mag_sel.png \
    documentation/html/search/search_l.png \
    documentation/html/search/search_m.png \
    documentation/html/search/search_r.png \
    documentation/html/bc_s.png \
    documentation/html/bdwn.png \
    documentation/html/closed.png \
    documentation/html/doc.png \
    documentation/html/doxygen.png \
    documentation/html/folderclosed.png \
    documentation/html/folderopen.png \
    documentation/html/nav_f.png \
    documentation/html/nav_g.png \
    documentation/html/nav_h.png \
    documentation/html/open.png \
    documentation/html/splitbar.png \
    documentation/html/sync_off.png \
    documentation/html/sync_on.png \
    documentation/html/tab_a.png \
    documentation/html/tab_b.png \
    documentation/html/tab_h.png \
    documentation/html/tab_s.png \
    documentation/html/search/search.css \
    documentation/html/doxygen.css \
    documentation/html/navtree.css \
    documentation/html/tabs.css \
    documentation/html/search/all_0.html \
    documentation/html/search/all_1.html \
    documentation/html/search/all_2.html \
    documentation/html/search/all_3.html \
    documentation/html/search/all_4.html \
    documentation/html/search/all_5.html \
    documentation/html/search/all_6.html \
    documentation/html/search/all_7.html \
    documentation/html/search/all_8.html \
    documentation/html/search/all_9.html \
    documentation/html/search/all_a.html \
    documentation/html/search/classes_0.html \
    documentation/html/search/enums_0.html \
    documentation/html/search/enumvalues_0.html \
    documentation/html/search/enumvalues_1.html \
    documentation/html/search/enumvalues_2.html \
    documentation/html/search/files_0.html \
    documentation/html/search/functions_0.html \
    documentation/html/search/functions_1.html \
    documentation/html/search/functions_2.html \
    documentation/html/search/functions_3.html \
    documentation/html/search/functions_4.html \
    documentation/html/search/functions_5.html \
    documentation/html/search/nomatches.html \
    documentation/html/search/variables_0.html \
    documentation/html/search/variables_1.html \
    documentation/html/annotated.html \
    documentation/html/classes.html \
    documentation/html/files.html \
    documentation/html/functions.html \
    documentation/html/functions_vars.html \
    documentation/html/globals.html \
    documentation/html/globals_enum.html \
    documentation/html/globals_eval.html \
    documentation/html/globals_func.html \
    documentation/html/index.html \
    documentation/html/main_8cpp.html \
    documentation/html/main_8cpp_source.html \
    documentation/html/structerror-members.html \
    documentation/html/structerror.html \
    documentation/latex/make.bat \
    chain.txt \
    match.txt \
    result.txt \
    documentation/latex/annotated.tex \
    documentation/latex/doxygen.sty \
    documentation/latex/files.tex \
    documentation/latex/main_8cpp.tex \
    documentation/latex/refman.tex \
    documentation/latex/structerror.tex
