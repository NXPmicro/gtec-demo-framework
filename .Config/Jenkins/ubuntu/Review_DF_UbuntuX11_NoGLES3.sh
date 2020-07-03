#!/bin/bash
set -o errexit

source $WORKSPACE/.Config/Jenkins/ubuntu/PrepareJenkinsEnvironment.sh
export FSL_FEATURES=[EarlyAccess,EGL,GoogleUnitTest,OpenCL1.2,OpenCV,OpenCV4,OpenGLES2,OpenVX,OpenVX1.1,Vulkan]

FslBuild.py -t sdk -vv --BuildTime --UseFeatures $FSL_FEATURES --CMakeInstallPrefix bin
FslBuild.py -t sdk --UseFeatures $FSL_FEATURES --RequireFeature [GoogleUnitTest] --ForAllExe "(EXE) --gtest_output=xml:""$FSL_TEST_REPORTS/(PACKAGE_NAME).xml"""