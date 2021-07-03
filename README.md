PGL22G platform, running arm and rtos system
  
管教分配列表:  
复位reset   V12  外接按键  

Keil5 for ARM链接：https://pan.baidu.com/s/1oz_VRyehyxrR6OD4hxh65g 提取码：n0od  
破解器keygen链接：https://pan.baidu.com/s/1ogptW88TrH9fo9pcAyRz2g 提取码：565y 

本项目基于2021集创赛紫光同创杯，由于初赛被刷，现将相关文件系统软硬件代码公开，仅供学习交流使用，目前实现了如下的功能：  
1、实现了基于SPI协议的SD卡外设，挂载在AHB总线上。  
2、通过软硬件的配合实现了文件系统的移植，文件系统可以与windows文件系统兼容(可以互相识别访问文件)。  
3、移植了摄像头的硬件驱动，可以通过UDP加速模块直接发送JPEG图像文件数据。  

存在的问题：  
1、虽然UDP加速模块发送速率快一点，但是UDP加速模块出来的checksum是错的，在上位机获取图像数据较为困难，需要从底层网络编程获取数据。  
2、DDR的图像数据写入部分还没有实现，这导致不能在ARM端访问到图像数据，倘若这一步完成，则可以实现SD卡图像文件的写入，以及基于lwip协议栈的UDP数据报文发送。