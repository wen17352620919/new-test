485: 485_test.o CRC16.o BitState.o serial_485.o modbus_slave.o TimerBase.o  my_register.o
	arm-none-linux-gnueabihf-g++ -o 485 485_test.o CRC16.o BitState.o serial_485.o modbus_slave.o TimerBase.o  my_register.o -pthread
485_test.o: 485_test.cpp
	arm-none-linux-gnueabihf-g++ -c 485_test.cpp
CRC16.o: CRC16.cpp
	arm-none-linux-gnueabihf-g++ -c CRC16.cpp
BitState.o: BitState.cpp
	arm-none-linux-gnueabihf-g++ -c BitState.cpp
serial_485.o: serial_485.cpp
	arm-none-linux-gnueabihf-g++ -c serial_485.cpp
modbus_slave.o: modbus_slave.cpp
	arm-none-linux-gnueabihf-g++ -c modbus_slave.cpp
# Register.o : Register.cpp
# 	arm-none-linux-gnueabihf-g++ -c Register.cpp
TimerBase.o : TimerBase.cpp
	arm-none-linux-gnueabihf-g++ -c TimerBase.cpp
my_register.o: my_register.cpp
	arm-none-linux-gnueabihf-g++ -c my_register.cpp
clean:
	rm *.o
	rm 485