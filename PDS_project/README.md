# 该PDS项目文件无需改动，可直接使用，自带BOOTLOADER程序，只需将keil 生成的.bin文件和数据拼接成sfc文件后烧录进flash中即可启动应用程序，具体可参考doc文件夹下的教程。  

# pgr_ARM_Cortex_M1设计实例目录结构图：  

├─bench                           //仿真test bench   
├─docs                            //设计文档-PDS工程使用手册  
├─ip                              //设计调用相关IP   
├─pnr                             //工程目录                   
│  ├─generate_bitstream           //.sbit  
│  ├─ipcore                       //IP中用到的IP  
│  ├─source                       //fdc文件  
│  ├─ARM_M1_SoC_Top.pds           //工程文件  
│  ├─itcm0                        //机器码文件0  
│  ├─itcm1                        //机器码文件1  
│  ├─itcm2                        //机器码文件2  
│  ├─itcm3                        //机器码文件3  
├─simulation                      //仿真工程目录  
├─src                             //设计实例包含的RTL文件  
│  ├─ahb                          //AHB代码  
│  │  ├─ahb_decoder               //AHB_LITE从设备选择  
│  │  ├─ahb_def_slave             //AHB_LITE默认从设备  
│  │  ├─ahb_mux                   //AHB_LITE从设备相关接口配置  
│  ├─logic                        //外设  
│  │  ├─cmsdk_ahb_dcache          //DCACHE  
│  │  ├─cmsdk_ahb_ethernet_dmac   //Ethernet_DMAC  
│  │  ├─cmsdk_ahb_gpio            //GPIO  
│  │  ├─cmsdk_ahb_icache          //ICACHE  
│  │  ├─cmsdk_ahb_to_apb          //AHB转APB桥  
│  │  ├─cmsdk_apb_i2c             //I2C  
│  │  ├─cmsdk_apb_mem             //MEM  
│  │  ├─cmsdk_apb_slave_mux       //APB从设备接口配置  
│  │  ├─cmsdk_apb_spi             //SPI  
│  │  ├─cmsdk_apb_subsystem       //APB外设顶层  
│  │  ├─cmsdk_apb_timer           //TIMER  
│  │  ├─cmsdk_apb_uart            //UART  
│  │  ├─cmsdk_apb_watchdog        //看门狗  
│  │  ├─cmsdk_iop_gpio            //GPIO子模块  
│  ├─m1_core                      //Cortex M1相关文件  
│  ├─tsmac_phy                    //PANGO TSMAC IP  
│  ├─M1_soc_top                   //Demo顶层  
│  ├─rst_gen                      //系统复位 

