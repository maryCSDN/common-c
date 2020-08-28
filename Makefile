# 引入配置文件
include configure.mk

# SDK目录下的项目列表，仅当项目之间无依赖关系时可以使用下面方法
#SDK_PROS            = $(shell find $(CM_SDK_ROOT_PATH) \
#                          -maxdepth 1 -type d -name "cm_*")

# 将要编译的项目追加到 SDK_PROS (被依赖的具有高优先级，放在前面编译)
SDK_PROS += $(_CMSDK)/cm_log
SDK_PROS += $(_CMSDK)/cm_container
SDK_PROS += $(_CMSDK)/cm_timer
# SDK_PROS += $(_CMSDK)/cm_network

# 构建sdk （集中构建SDK下项目集合）
build:createbuild buildpro

# 1. 创建用于存放SDK编译后文件的目录
createbuild:
	@echo "Create build directory"
	@mkdir -p $(_CMBUILD)
	@mkdir -p $(_CMLIBS)
	@mkdir -p $(_CMINCLUDES)
	@mkdir -p $(_CMBINS)


# 2. 在build目录下创建SDK子项目对应路径,将对应项目的目标文件拷贝到build
#cp -rfp $$PRO/src/include/* $(CM_BUILD_ROOT_PATH)/$$PRO/include || exit 1; 
#cp -fp $$PRO/src/*.a $(CM_BUILD_ROOT_PATH)/$$PRO/lib || exit 1;
buildpro:$(SDK_PROS)
	@echo "Start build SDK"
	@list='$(SDK_PROS)';\
	for PRO in $$list;\
	do\
		(cd $$PRO && $(MAKE) build) || exit 1;\
	done
	@echo "Build SDK successful"


# 3. 清除构建过程生成项 （提交代码前必须执行此命令）
clean:$(SDK_PROS)
	@echo "Clean build"
	@list='$(SDK_PROS)';\
	for PRO in $$list;\
	do\
		echo "Clean in $$PRO";\
		(cd $$PRO && $(MAKE) clean) || exit 1;\
		echo "Clean $$PRO successful";\
	done
	@rm -rf $(_CMBUILD)
	@echo "Clean build successful"

# 4. 查看即将构建的子项目的路径（src path）
sp:$(SDK_PROS)
	@echo $^
