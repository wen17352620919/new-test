#将所有的.o文件放入变量中
CUR_OUT=${wildcard *.o}

$(EXE):$(CUR_OUT)
	$(CC)  -o $(MYPATH)/$(EXE) $^ $(LDFLAGS)