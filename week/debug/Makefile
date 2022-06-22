#输出文件夹
OUTOBJDIR=debug
#可执行程序文件夹
OUTBINDIR=bin
#连接目标文件夹
OBJFILE=objs
#生成的库的文件夹的名称
OUTLIBSDIR=outlibs

#定义一个宏，用于区别是在哪一级目录进行make
ROOTPATH=ProjectDir

# 最终bin文件的名字
BIN_NAME=myproject.bin
# 生成库的文件的名字
LIB_RECORD_NAME=myrecord
LIB_MYMATH_NAME=mymath
LIB_STRING_NAME=mystring

#判断输出文件夹是否存在，如果不存在自动填充
ifneq ($(OUTOBJDIR), $(wildcard $(OUTOBJDIR)))
$(shell mkdir -p $(OUTOBJDIR) $(OUTOBJDIR)/$(OBJFILE))
$(shell echo 'OBJS=*.o\
	\nODIR=$$(OBJFILE)\n\
	\n$$(ROOT_DIR)/$$(OUTBINDIR)/$$(BIN_NAME):$$(ODIR)/$$(OBJS)\
	\n\t$$(CC) -o $$@ $$^ $$(CFLAGS) $$(LDFLAGS)'\
	> $(OUTOBJDIR)/Makefile)
endif
#输出文件夹下Makefile文件是否存在
ifneq ($(OUTOBJDIR)/Makefile, $(wildcard $(OUTOBJDIR)/Makefile))
$(shell echo 'OBJS=*.o\
	\nODIR=$$(OBJFILE)\n\
	\n$$(ROOT_DIR)/$$(OUTBINDIR)/$$(BIN_NAME):$$(ODIR)/$$(OBJS)\
	\n\t$$(CC) -o $$@ $$^ $$(CFLAGS) $$(LDFLAGS)'\
	> $(OUTOBJDIR)/Makefile)
endif

#判断连接目标文件夹是否存在
ifneq ($(OUTOBJDIR)/$(OBJFILE), $(wildcard $(OUTOBJDIR)/$(OBJFILE)))
$(shell mkdir -p $(OUTOBJDIR)/$(OBJFILE))
endif
#判断输出文件的文件夹是否存在，不存在则创建
ifneq ($(OUTLIBSDIR), $(wildcard $(OUTLIBSDIR)))
$(shell mkdir -p $(OUTLIBSDIR))
endif

#判断输出文件的文件夹是否存在，不存在则创建
ifneq ($(OUTBINDIR), $(wildcard $(OUTBINDIR)))
$(shell mkdir -p $(OUTBINDIR))
endif

#设置编译器
CC=gcc
#生成静态库的指令及其参数
STATIC_LIBS_CMD=ar -cr
#生成动态共享库的指令及其参数
DYNAMIC_LIBS_CMD=$(CC) -shared -FPIC
#删除的指令及其参数
RM=rm -rf
CP=cp --path

#debug文件夹里的makefile文件需要最后执行，所以这里需要执行的子目录要排除debug文件夹，这里使用awk排除了debug文件夹，读取剩下的文件夹
SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
#SUBDIRS删除includes libs文件夹，因为这个文件中是头文件，不需要make
SUBDIRS:=$(patsubst $(OUTLIBSDIR),,$(SUBDIRS))
# 因为在根目录下存在一个 log 文件夹，此文件只为了放置日志文件，并不需要参与编译
SUBDIRS:=$(patsubst log,,$(SUBDIRS))
SUBDIRS:=$(patsubst $(OUTBINDIR),,$(SUBDIRS))
#记住当前工程的根目录路径
ROOT_DIR=$(shell pwd)
#目标文件所在的目录
OBJS_DIR= $(OUTOBJDIR)/$(OBJFILE)
#获取当前目录下的c文件集，放在变量CUR_SOURCE中
CUR_SOURCE=${wildcard *.c}
#将对应的c文件名转为o文件后放在下面的CUR_OBJS变量中
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}
# 获取当前终端的带下，$1表示的是高度，$2表示的是宽度
TERMIALSIZE=$(shell stty size|awk '{print $2}')

# 所需要的底层提供库文件, libm(数学库), libpthread(Linux线程库)
DEPENDLIBS := pthread m

# 所需要的头文件路径
INCLUDE_PATH := $(ROOT_DIR)/includes/
#使用的库目录，静态库和动态库添加在这里
LIBRARY_PATH := $(ROOT_DIR)/$(OUTLIBSDIR)

# 如果需要调试，则在make时候指定DBGEN为true
ifeq (true, ${DEBUG})
	CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1
endif

# 如果运行目标平台是真实的物理板卡，则在make是指定类型
ifeq (board, $(TYPE))
	CFLAGS += -DPHYSICALBOARD
endif

# 如果想要使用系统时间为接收时间，则在make是指定
ifeq (sys, $(TIME))
	CFLAGS += -DSYSTEMTIME_MODE
endif

# 获取所有的头文件路径
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))
# 获取所有的依赖库的文件的路径
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))
# 获取所有的依赖库的文件
LDFLAGS += -Xlinker "-(" -l$(LIB_MYMATH_NAME) -l$(LIB_RECORD_NAME) -l$(LIB_STRING_NAME) -Xlinker "-)"
LDFLAGS += $(foreach lib, $(DEPENDLIBS), -l$(lib))
#添加编译的C标准版本，输入宏定义参数_POSIX_C_SOURCE
CFLAGS += --std=c11 -D_POSIX_C_SOURCE -D_GNU_SOURCE
# 将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CC RM OBJS_DIR OUTBINDIR BIN_NAME ROOT_DIR LDFLAGS CP \
		CFLAGS LIB_MYMATH_NAME LIB_RECORD_NAME LIB_STRING_NAME OUTLIBSDIR DYNAMIC_LIBS_CMD STATIC_LIBS_CMD OBJFILE ROOTPATH CCU
#注意这里的顺序，需要先执行SUBDIRS最后才能是DEBUG
all:$(clean) $(SUBDIRS) $(CUR_OBJS) DEBUG
	@echo
	@echo  All Compile completed!!!
	@echo
#递归执行子目录下的makefile文件，这是递归执行的关键
$(SUBDIRS):ECHO
	make -C $@
DEBUG:ECHO
#直接去debug目录下执行makefile文件
	make -C $(OUTOBJDIR)
ECHO:
	@echo $(SUBDIRS)

#将c文件编译为o文件，并放在指定放置目标文件的目录中即OBJS_DIR
$(CUR_OBJS):%.o:%.c
	$(CC) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@ $(CFLAGS)

ODDRUNTIMEDIR += runtime1
EVENRUNTIMEDIR += runtime2
CONFIGFILEDIR += cfg
CONFIGFILENAME += Cfg.ini
ODDRUNTIME += $(shell if [ -d $(ODDRUNTIMEDIR) ]; then echo "true"; else echo "false"; fi)
EVENRUNTIME += $(shell if [ -d $(EVENRUNTIMEDIR) ]; then echo "true"; else echo "false"; fi)
ODDCONFIGFILE += [VOBC-Cfg]\nTRAIN_NUMBER=1\nHEAD_SIDE=0\nCCU_CYCLE=100
EVENCONFIGFILE += [VOBC-Cfg]\nTRAIN_NUMBER=1\nHEAD_SIDE=1\nCCU_CYCLE=100

.PHYON:install
install:
ifeq ("$(ODDRUNTIME)", "false")
	$(shell mkdir $(ODDRUNTIMEDIR))
endif
ifeq ("$(EVENRUNTIME)", "false")
	$(shell mkdir $(EVENRUNTIMEDIR))
endif
	@$(CP) $(OUTLIBSDIR)/$(BIN_NAME) $(ODDRUNTIMEDIR)/
	@$(CP) $(OUTLIBSDIR)/$(BIN_NAME) $(EVENRUNTIMEDIR)/
	@$(CP) $(CONFIGFILEDIR)/* $(EVENRUNTIMEDIR)/
	@$(CP) $(CONFIGFILEDIR)/* $(ODDRUNTIMEDIR)/
	@echo '$(ODDCONFIGFILE)' > $(ODDRUNTIMEDIR)/$(CONFIGFILEDIR)/$(CONFIGFILENAME)
	@echo '$(EVENCONFIGFILE)' > $(EVENRUNTIMEDIR)/$(CONFIGFILEDIR)/$(CONFIGFILENAME)

.PHYON:runodd
runodd:install
	@cd $(ODDRUNTIMEDIR)/$(OUTLIBSDIR) ; ./$(BIN_NAME)

.PHYON:runeven
runeven:install
	@cd $(EVENRUNTIMEDIR)/$(OUTLIBSDIR) ; ./$(BIN_NAME)

.PHYON:run
run:
	@cd $(OUTBINDIR)/ ; ./$(BIN_NAME)

.PHYON:clean
clean:
	@$(RM) $(OBJS_DIR)/*.o
	@$(RM) $(OUTOBJDIR)
	@$(RM) $(OUTLIBSDIR) $(ODDRUNTIMEDIR) $(EVENRUNTIMEDIR)
