CC              =gcc
#构建SDK库保存目录
CM_BUILD_DIR    =./build/
#SDK的root目录
CM_SDK_DIR      =./SDK/

#把将要编译的sdk添加到CM_SDK_SUB_DIR
CM_SDK_SUB      +=$(CM_SDK_DIR)cm_log/
CM_SDK_SUB      +=$(CM_SDK_DIR)cm_list/

build:check_dir
	@echo "******start build SDK******"
	@list='$(CM_SDK_SUB)'; for SDK in $$list; do\
		echo "******build $$SDK******";\
		(cd $$SDK && $(MAKE) build) || exit 1;\
		echo "******build $$SDK success******";\
	done
	@echo "******build SDK success******"

check_dir:
	@mkdir -p $(CM_BUILD_DIR);

# 提交代码前执行make undo (清除编译生成项，只提交源码)
undo:
	@echo "******undo SDK build******"
	@list='$(CM_SDK_SUB)';for SDK in $$list;\
	do\
		echo "******undo in $$SDK******";\
		(cd $$SDK && $(MAKE) undo) || exit 1;\
		echo "******undo $$SDK success******";\
	done
	@rm -rf $(CM_BUILD_DIR)
	@echo "******undo SDK build success******"

