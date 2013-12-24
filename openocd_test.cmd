rem set oocd_bin=.\OpenOCD\bin\openocd-0.6.0-dev-120229143915.exe
set oocd_bin=.\OpenOCD\bin\openocd.exe
start %oocd_bin% -d 3 -f interface/stlink-v2.cfg -f target/stm32f4x_stlink.cfg -c init
rem start telnet localhost 4444
start %ProgramFiles%\putty\putty.exe telnet://localhost:4444
rem pause