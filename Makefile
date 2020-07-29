CC              =gcc
#编译文件保存目录
CM_COMPILES_DIR =./compiles/
#SDK的root目录
CM_SDK_DIR      =./SDK/

#把将要编译的sdk添加到CM_SDK_SUB_DIR
CM_SDK_SUB      +=$(CM_SDK_DIR)cm_log/
#CM_SDK_SUB      +=$(CM_SDK_DIR)cm_list/

build:check_dir
	@echo "##build SDK"
	@list='$(CM_SDK_SUB)'; for SDK in $$list; do\
		echo "##compile $$SDK";\
		(cd $$SDK && $(MAKE) build) || exit 1;\
	done
	@echo "##build success"

check_dir:
	mkdir -p $(CM_COMPILES_DIR);

# 提交代码前执行make undo (清除编译生成项，只提交源码)
undo:
	@echo "##clean all compiles"
	@list='$(CM_SDK_SUB)';for SDK in $$list;\
	do\
		echo "##clean in $$SDK";\
		(cd $$SDK && $(MAKE) undo) || exit 1;\
	done
	@rm -rf $(CM_COMPILES_DIR)
	@echo "##clean end"

