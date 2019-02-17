QT += core gui widgets

TEMPLATE = app
CONFIG += app c++1z

QMAKE_CXXFLAGS_DEBUG += -g -Og -dA -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wdiv-by-zero -Wendif-labels -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winline -Winvalid-pch -Wlogical-op -Wmissing-declarations -Wno-missing-format-attribute -Wmissing-include-dirs -Wmultichar -Wpacked -Wpointer-arith -Wreturn-type -Wsequence-point -Wsign-compare -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch -Wswitch-default -Werror=undef -Wno-unused -Wvariadic-macros -Wwrite-strings  -Werror=declaration-after-statement -Werror=implicit-function-declaration -Werror=nested-externs -Werror=strict-prototypes -fno-strict-aliasing -static #-Werror=missing-braces
#-fprofile-arcs -ftest-coverage
#QMAKE_LFLAGS_DEBUG += -lgcov --coverage

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O3


#QMAKE_CXXFLAGS_RELEASE += -Os -s -fPIE -fvisibility-inlines-hidden -flto -fomit-frame-pointer -fstack-protector-all -D_FORTIFY_SOURCE=2 -fcf-protection=full -fstack-clash-protection -fvisibility=hidden -fsanitize=address -fsanitize=kernel-address -fsanitize-address-use-after-scope -fsanitize-coverage=trace-cmp -mmpx -fcheck-pointer-bounds -static -fstack-check -fstack-clash-protection -fsplit-stack -fvtable-verify=preinit -fstack-reuse=none -fno-exceptions -freg-struct-return -fno-jump-tables -mfpmath="387+sse" ## HARDENING
#QMAKE_LFLAGS += -flto -Wl,-z,now -Wl,-z,relro #HARDEN

QMAKE_CXXFLAGS_RELEASE += -Ofast -fopenmp -fomit-frame-pointer -fmodulo-sched -fmodulo-sched-allow-regmoves -fgcse-sm -fgcse-las -fgcse-after-reload -funsafe-loop-optimizations -flive-range-shrinkage -fsched-spec-load-dangerous -fsched2-use-superblocks -floop-nest-optimize -fprefetch-loop-arrays -ffinite-math-only -march=native -mtune=native -mfpmath="387+sse" -std=c++1z -static

INCLUDEPATH += /usr/local/cuda/include
INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/local/include


LIBS += -L/usr/lib \
-lblas \
-llapack

LIBS += -ldl -lrt

#LIBS += -L/opt/intel/mkl/lib/intel64 -lmkl_rt -lmkl_core

LIBS += -L/usr/lib -lGL
LIBS += -L/usr/lib -ltesseract
LIBS += -L/usr/lib/X11 -lXtst -lX11


LIBS += -L/usr/local/lib -ldlib

LIBS += -L/usr/local/cuda/lib64/ -lcudnn -lcudart -lcublas -lcurand -lcusolver

LIBS += -ldl -lrt

LIBS += -L/usr/lib -lomp


LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_imgcodecs \
-lopencv_ml \
-lopencv_video \
-lopencv_videoio \
-lopencv_videostab \
-lopencv_objdetect \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_flann \
-lopencv_optflow \
-lopencv_bgsegm \
-lopencv_cudaimgproc \
-lopencv_cudawarping \
-lopencv_cudafilters \
-lopencv_cudaarithm \
-lopencv_cudaobjdetect \
-lopencv_photo \
-lopencv_xphoto \
-lopencv_highgui

SOURCES += \
    main.cpp \
    cheatcore.cpp \
    overlay.cpp \
    mwindow.cpp

HEADERS += \
    cheatcore.h \
    overlay.h \
    mwindow.h \
    includes.h

FORMS += \
    mwindow.ui
