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

```
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.56.tar.gz   
tar zxvf bcm2835-1.56.tar.gz   
cd bcm2835-1.56   
./configure   
make   
sudo make check   
sudo make install   
cd $HOME   
```

_\* This tool require 1.56 or later._   
_\* Because this tool uses bcm2835_spi_write._   


```
git clone https://github.com/nopnop2002/ili9225spi_rpi
cd ili9225spi_rpi
cc -o demo demo.c fontx.c ili9225.c -lbcm2835 -lm -lpthread
sudo ./demo

ColorBarTest elapsed time[ms]=61
ArrowTest elapsed time[ms]=77
LineTest elapsed time[ms]=163
CircleTest elapsed time[ms]=152
RoundRectTest elapsed time[ms]=150
DirectionTest elapsed time[ms]=73
HorizontalTest elapsed time[ms]=112
VerticalTest elapsed time[ms]=111
FillRectTest elapsed time[ms]=143
ColorTest elapsed time[ms]=125
```

----

build with wiringPi library (very slow)   

```
git clone https://github.com/nopnop2002/ili9225spi_rpi
cd ili9225spi_rpi
cc -o demo demo.c fontx.c ili9225.c -lwiringPi -lm -lpthread -DWPI
sudo ./demo

ColorBarTest elapsed time[ms]=170
ArrowTest elapsed time[ms]=754
LineTest elapsed time[ms]=4716
CircleTest elapsed time[ms]=4147
RoundRectTest elapsed time[ms]=4113
DirectionTest elapsed time[ms]=689
HorizontalTest elapsed time[ms]=2021
VerticalTest elapsed time[ms]=1912
FillRectTest elapsed time[ms]=1081
ColorTest elapsed time[ms]=338
```

---

![ili9225-11](https://user-images.githubusercontent.com/6020549/58362412-bfa46f00-7ed1-11e9-9c74-dd56ea798c2c.JPG)
![ili9225-12](https://user-images.githubusercontent.com/6020549/58362413-bfa46f00-7ed1-11e9-93c5-7a6c78b6b2a5.JPG)
![ili9225-13](https://user-images.githubusercontent.com/6020549/58362414-bfa46f00-7ed1-11e9-80a4-e3c8e6f0f901.JPG)
![ili9225-14](https://user-images.githubusercontent.com/6020549/58362415-c03d0580-7ed1-11e9-8506-bc6b8e9b9afd.JPG)
![ili9225-15](https://user-images.githubusercontent.com/6020549/58362416-c03d0580-7ed1-11e9-9f2a-b40fd4ee5776.JPG)
![ili9225-16](https://user-images.githubusercontent.com/6020549/58362417-c03d0580-7ed1-11e9-899d-a61d415d4947.JPG)
![ili9225-17](https://user-images.githubusercontent.com/6020549/58362418-c03d0580-7ed1-11e9-8a0d-fc3342925b06.JPG)
![ili9225-18](https://user-images.githubusercontent.com/6020549/58362419-c0d59c00-7ed1-11e9-8fec-2d5b673a877a.JPG)
![ili9225-19](https://user-images.githubusercontent.com/6020549/58362420-c0d59c00-7ed1-11e9-9b8b-cf3657149c2f.JPG)
![ili9225-20](https://user-images.githubusercontent.com/6020549/58362421-c16e3280-7ed1-11e9-8033-eea28354c9a5.JPG)
![ili9225-21](https://user-images.githubusercontent.com/6020549/58362674-a3ee9800-7ed4-11e9-9a87-2774e6b6dcc8.JPG)

