# stempi
This is a project send the CPU temperatue from RPi to MCU via Serial Port.
## How to use it 
1. Login to your Raspberry Pi and then turn on your Serial port via:
```bash
sudo raspi-config 
```
Navigate to "Interfacing Options" ---> "Serial" ---> "enable"
2. Open a terminal on Raspberry Pi and typing following command:
```bash
cd ~
git clone https://github.com/yoyojacky/stempi.git
cd stempi/
chmod +x stempi
./stempi 
```
It will send your CPU temperatue via Serial port /dev/ttyAMA0, you can connect
GPIO 14 and GPIO 15 to your MCU.
## More information Please contact us.
E-Mail: jacky.li@52pi.com


