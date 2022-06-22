#当前路径
MYPATH =$(shell pwd)
#编译器
CC= gcc
#生成的可执行文件名
EXE = mycomtrade
#子文件生成的.o文件存放位置
OUTPUT_DIR = $(MYPATH)/bin

#主函数和对应.o文件名
MainSrc = main.c
MainOut = main.o
#编译依赖的库
LDFLAGS = -pthread
#可执行文件名， 这个根据具体程序会有变动。
#遍历条件筛选
SUBDIRS =$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
#去掉不需要编译的文件夹
SUBDIRS:=$(patsubst bin,,$(SUBDIRS))
SUBDIRS:=$(patsubst Head,,$(SUBDIRS))
SUBDIRS:=$(patsubst modbus,,$(SUBDIRS))

# 将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CC OUTPUT_DIR CUR_SOURCE MYPATH EXE LDFLAGS

#循环执行,先clean再遍历编译
all:$(clean)  $(SUBDIRS) END 
	@echo
	@echo  All Compile completed!!!
	@echo

$(SUBDIRS):ECHO
	make -C $@

ECHO:
# $(info $(SUBDIRS))


END:
	$(CC)  -c $(MainSrc) -o $(OUTPUT_DIR)/$(MainOut)
	make -C $(OUTPUT_DIR)


clean: 
	rm $(OUTPUT_DIR)/*.o