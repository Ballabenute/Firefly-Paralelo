TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ..\\ic-daniel\\fontes\\HSVimg.cpp \
    ..\\ic-daniel\\fontes\\Image.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += C:\\Alunos\\OpenCV\\OpenCV-2.4.9\\include
LIBS += -LC:\\Alunos\\OpenCV\\OpenCV-2.4.9\\build-qt\\lib\
    -lopencv_calib3d249d \
    -lopencv_contrib249d \
    -lopencv_core249d \
    -lopencv_features2d249d \
    -lopencv_flann249d \
    -lopencv_gpu249d \
    -lopencv_highgui249d \
    -lopencv_imgproc249d \
    -lopencv_legacy249d \
    -lopencv_ml249d \
    -lopencv_nonfree249d \
    -lopencv_objdetect249d \
    -lopencv_ocl249d \
    -lopencv_photo249d \
    -lopencv_stitching249d \
    -lopencv_superres249d \
    -lopencv_ts249d \
    -lopencv_video249d \
    -lopencv_videostab249d

HEADERS += \
    ..\\ic-daniel\\headers\\entropy.h \
    ..\\ic-daniel\\headers\\firefly.h \
    ..\\ic-daniel\\headers\\histogram.h \
    ..\\ic-daniel\\headers\\HSVimg.h \
    ..\\ic-daniel\\headers\\Image.h \
    ..\\ic-daniel\\headers\\Lde.hpp \
    ..\\ic-daniel\\headers\\node.hpp \
    ..\\ic-daniel\\headers\\hsv-a.h \
    ..\\tsallis\\tsallis.h \
    ..\\ic-daniel\\headers\\incl.h \
    ..\\ic-daniel\\headers\\multilimiarizacao.h \
    ..\\ic-daniel\\headers\\bests.h \
    ..\\ic-daniel\\headers\\grayseg.h \
    calchistgray.h

