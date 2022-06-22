#当前路径
MYPATH =$(shell pwd)
#编译器
CC= gcc
#生成的可执行文件名
EXE = myexe
#子文件生成的.o文件存放位置
OUTPUT_DIR = $(MYPATH)/bin

# #判断存放.o文件的文件夹是否存在，不存在则创建
# ifneq ($(OUTPUT_DIR), $(wildcard $(OUTPUT_DIR)))
# $(shell mkdir  $(OUTPUT_DIR))
# endif

# #输出文件夹下Makefile文件是否存在
# ifneq ($(OUTOBJDIR)/Makefile, $(wildcard $(OUTOBJDIR)/Makefile))
# $(shell echo 'CUR_OUT=${wildcard *.o}\
# 	\n$(EXE):$(CUR_OUT)\
# 	\n\t$(CC)  -o $(MYPATH)/$(EXE) $^'\
# 	> $(OUTOBJDIR)/Makefile)
# endif

#可执行文件名， 这个根据具体程序会有变动。
#遍历条件筛选
SUBDIRS =$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
#去掉不需要编译的文件夹
SUBDIRS:=$(patsubst bin,,$(SUBDIRS))
SUBDIRS:=$(patsubst Head,,$(SUBDIRS))
SUBDIRS:=$(patsubst src,,$(SUBDIRS))

#获取当前目录下的c文件集，放在变量CUR_SOURCE中
#CUR_SOURCE+=${wildcard *.c}

# 将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CC OUTPUT_DIR CUR_SOURCE MYPATH EXE

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
	$(CC)  -c main.c -o $(OUTPUT_DIR)/main.o
	make -C $(OUTPUT_DIR)


clean: 
	rm $(OUTPUT_DIR)/*.o


#打印
#	$(info $(MYPATH))
#shell命令为 :=,不能为=
#@取消中间打印，直接出结果
#$@ 代表目标
#$< 代表第一个引用
#$^ 代表全部引用
