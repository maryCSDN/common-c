# 编译工具
CC                      =gcc
# 构建SDK库保存目录
CM_BUILD_ROOT_PATH      =./build
# SDK的root目录
CM_SDK_ROOT_PATH        =./SDK
# 即将编译的项目列表 (查找SDK目录下的一级子目录,目录前缀必须是cm_)
COMPILE_PROS            = $(shell find $(CM_SDK_ROOT_PATH) \
                          -maxdepth 1 -type d -name "cm_*")

# 构建sdk （集中构建SDK下项目集合）
build:create_dir compile


# 1. 创建用于存放SDK编译后文件的文件夹
create_dir:
	@echo "Create build directory"
	@mkdir -p $(CM_BUILD_DIR)


# 2. 在build目录下创建SDK子项目对应路径,将对应项目的目标文件拷贝到build
cmbuild:$(COMPILE_PROS)
	@echo "Start build SDK"
	@list = '$(COMPILE_PROS)';\
	for PRO in $$list;\
	do\
		echo "Build $$PRO";\
		mkdir -p $(CM_BUILD_ROOT_PATH)/$$PRO;\
		(cd $$PRO && $(MAKE) compile) || (echo "Compile $$PRO failed"; exit 1;)\
		cp -rf $$PRO/src/include $(CM_BUILD_ROOT_PATH)/$$PRO;
		cp -f  $$PRO/src/*.a     $(CM_BUILD_ROOT_PATH)/$$PRO/lib;
		echo "Build $$PRO successful";\
	done
	@echo "Build SDK successful"


# 3. 清除构建过程生成项 （提交代码前必须执行此命令）
clean:$(COMPILE_PROS)
	@echo "Clean build"
	@list = '$(COMPILE_PROS)';\
	for PRO in $$list;\
	do\
		echo "Clean in $$PRO";\
		(cd $$SDK && $(MAKE) clean) || exit 1;\
		echo "Clean $$PRO successful";\
	done
	@rm -rf $(CM_BUILD_DIR)
	@echo "Clean build successful"

# 4. 查看即将构建的子项目列表
cmlist:$(COMPILE_PROS)
	@echo $^
