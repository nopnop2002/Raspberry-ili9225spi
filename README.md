# ili9225spi_rpi
ILI9225 SPI TFT Library for RaspberryPi/OrangePi.  

This library can show a chart to ILI9225 SPI TFT.   

----

Wirering   

|TFT||Rpi/Opi|
|:-:|:-:|:-:|
|CS|--|Pin#24(SPI CE0)|
|RST|--|Pin#5(*)|
|RS|--|Pin#3(*)|
|SDA|--|Pin#19(SPI MOSI)|
|CLK|--|Pin#23(SPI SCLK)|
|GND|--|GND|
|5V|--|5V|

(*) 
This is default.   
If you want to use other pin, You have to change this.   
#define D_C  2  // GPIO2=D/C   
#define RES  3  // GPIO3=RESET   

----

build with bcm2835 library (very fast)   

wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.42.tar.gz   
tar zxvf bcm2835-1.42.tar.gz   
cd bcm2835-1.42   
./configure   
make   
sudo make check   
sudo make install   
cd $HOME   

_\* This tool require 1.56 or later._   
_\* Because this tool uses bcm2835_spi_write._   


git clone https://github.com/nopnop2002/ili9225spi_rpi   
cd ili9225spi_rpi   
cc -o demo demo.c fontx.c ili9225.c -lbcm2835 -lm -lpthread   
sudo ./demo   

----

build with wiringPi library (very slow)   

git clone https://github.com/nopnop2002/ili9225spi_rpi   
cd ili9225spi_rpi   
cc -o demo demo.c fontx.c ili9225.c -lwiringPi -lm -lpthread -DWPI   
sudo ./demo   

---

![ili9225-3](https://cloud.githubusercontent.com/assets/6020549/25643234/827c5e60-2fd9-11e7-8f3d-969950c99615.JPG)

