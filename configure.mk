# 在配置文件中定义的变量，以_开头
# SDK 源目录
export _CMROOT = $(PWD)
export _CMSDK = $(_CMROOT)/SDK

# cm 库目录 (构建后目录，需要先创建)
export _CMBUILD = $(_CMROOT)/build
export _CMLIBS = $(_CMBUILD)/libs
export _CMINCLUDES = $(_CMBUILD)/includes
export _CMBINS = $(_CMBUILD)/bins

# 编译工具
export _CC = gcc