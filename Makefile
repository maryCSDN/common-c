# 编译工具
CC                      =gcc
# 构建SDK库保存目录
CM_BUILD_ROOT_PATH      =build
# SDK的root目录
CM_SDK_ROOT_PATH        =SDK
# 即将编译的项目列表 (查找SDK目录下的一级子目录,目录前缀必须是cm_)
BUILD_PROS            = $(shell find $(CM_SDK_ROOT_PATH) \
                          -maxdepth 1 -type d -name "cm_*")

# 构建sdk （集中构建SDK下项目集合）
build:create_dir cmbuild


# 1. 创建用于存放SDK编译后文件的文件夹
create_dir:
	@echo "Create build directory"
	@mkdir -p $(CM_BUILD_ROOT_PATH)


# 2. 在build目录下创建SDK子项目对应路径,将对应项目的目标文件拷贝到build
#cp -rfp $$PRO/src/include/* $(CM_BUILD_ROOT_PATH)/$$PRO/include || exit 1; 
#cp -fp $$PRO/src/*.a $(CM_BUILD_ROOT_PATH)/$$PRO/lib || exit 1;
cmbuild:$(BUILD_PROS)
	@echo "Start build SDK"
	@list='$(BUILD_PROS)';\
	for PRO in $$list;\
	do\
		echo "Build $$PRO";\
		mkdir -p $(CM_BUILD_ROOT_PATH)/$$PRO;\
		(cd $$PRO && $(MAKE) compile) || exit 1;\
		cp -rfp $$PRO/src/include/* $(CM_BUILD_ROOT_PATH)/$$PRO/include;\
		cp -fp $$PRO/src/*.a $(CM_BUILD_ROOT_PATH)/$$PRO/lib;\
		cp -fp $$PRO/service/bin/* $(CM_BUILD_ROOT_PATH)/$$PRO/bin\
		echo "Build $$PRO successful";\
	done
	@echo "Build SDK successful"


# 3. 清除构建过程生成项 （提交代码前必须执行此命令）
cmclean:$(BUILD_PROS)
	@echo "Clean build"
	@list = '$(BUILD_PROS)';\
	for PRO in $$list;\
	do\
		echo "Clean in $$PRO";\
		(cd $$SDK && $(MAKE) clean) || exit 1;\
		echo "Clean $$PRO successful";\
	done
	@rm -rf $(CM_BUILD_ROOT_PATH)
	@echo "Clean build successful"

# 4. 查看即将构建的子项目列表
cmlist:$(BUILD_PROS)
	@echo $^
