PGL22G platform, running arm and rtos system
pnr/generate_bitstream/ 目录下的.bin文件是串口程序，运行后会通过串口一直传输数据。  
目前RTOS的运行还有一点问题，就是IIC对于EEPROM的访问存在错误。  
将RTOS中关于IIC的代码注释掉后可正常运行。IIC部分估计是硬件写的有问题，导致读写数据的位置不一致，从而导致读写的数据不一致。因此不宜使用IIC的这部分的地址。  
  
管教分配列表:  
复位reset   V12  外接按键  

Keil5 for ARM链接：https://pan.baidu.com/s/1oz_VRyehyxrR6OD4hxh65g 提取码：n0od  
破解器keygen链接：https://pan.baidu.com/s/1ogptW88TrH9fo9pcAyRz2g 提取码：565y 
