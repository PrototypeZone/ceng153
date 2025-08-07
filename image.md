# Steps taken to create Raspberry Pi OS SD card image suitable for this course

## 2025-08-07
(editor's note to self see Documents\ceng317\DevelopmentTimeNeeded.txt)   
We are looking to create a ready to go version of   
https://downloads.raspberrypi.com/raspios_full_armhf/images/raspios_full_armhf-2025-05-13/2025-05-13-raspios-bookworm-armhf-full.img.xz   
which will include:   
[/home/pi/C153Doxygen2023-05-30](https://github.com/PrototypeZone/ceng153/tree/main/C153Doxygen2023-05-30)   
[/home/pi/C153SenseHat2025-06-12](https://github.com/PrototypeZone/ceng153/tree/main/C153SenseHat2025-06-12)   
[/home/pi/lg-master](https://github.com/joan2937/lg)

Should be done with [pi-gen](#pi-gen), going to try [legacy-process](#legacy-process) first.

## pi-gen
1. The image creation using pi-gen should be done upon minor releases every few months. Websites to visit to identify minor releases:   
https://en.wikipedia.org/wiki/Raspberry_Pi_OS#Releases   
https://downloads.raspberrypi.com/raspios_full_armhf/images/   

2. "pi-gen runs on Debian-based operating systems released after 2017, and we always advise you use the latest OS for security reasons."

3. Designate a hard drive on which to download the most recent VirtualBox, Debian OS, and Raspbery Pi OS:   
https://download.virtualbox.org/virtualbox/7.1.12/VirtualBox-7.1.12-169651-Win.exe
https://cdimage.debian.org/debian-cd/current/amd64/iso-dvd/debian-12.11.0-amd64-DVD-1.iso   

4. Install Oracle VM VirtualBox
5. Start Oracle VM VirtualBox
6. Machine->New…
7. Name: 2025-05-12-rpioshf
8. ISO Image: debian-12.11.0-amd64-DVD-1.iso
9. Username: vboxuser   
Password: changeme   
Hostname: 2025-05-12-rpioshf   
Domain Name: myguest.virtualbox.org   
Check Guest Additions   
Next   
10. Hardware Base Memory: 4000 MB, Processors: 4, Next
11. Virtual Hard disk file 64.00 GB, Next (which will leave less than 8GB to spare, need to have enough to have the host os {6GB}, build the target os with the image {12GB} in the work directory {40+GB} and zip the images into the deploy directory {6+GB}) note that virtual machine should be built on an external drive if using a computer that reimages upon reboot such that it persists until the next work session as well as over a lunch break.
12. Finish
13. Click on user upon virtual machine reboot.
14. Type in password to log in.
15. Click on the [!] bubble to hide notifications.
16. Welcome->Next
17. Typing->Next
18. Privacy, slide to left, Next
19. Connect Your Online Accounts, Skip
20. Start Using Debian GNU/Linux
21. Activities->Type to search terminal, Click on Terminal
22. Change to root 
```
su – 
``` 
23. Type in password
24. Add user to sudo group 
```
usermod -a -G sudo vboxuser 
```
25. Ctrl-d to go back to user
26. Click on the icon at the top right of the screen slightly above [!] bubble to reach what is behind it, click on the power icon, select Restart… Restart
27. Click on user and type in password to log in.
28. Activities->Type to search terminal, Click on Terminal
29. sudo nano /etc/apt/sources.list
30. Type in password
31. Comment out the existing line with a #
32. Add:
```
deb http://deb.debian.org/debian bookworm main non-free-firmware 
deb-src http://deb.debian.org/debian bookworm main non-free-firmware 
 
deb http://deb.debian.org/debian-security/ bookworm-security main non-free-firmware 
deb-src http://deb.debian.org/debian-security/ bookworm-security main non-free-firmware 
 
deb http://deb.debian.org/debian bookworm-updates main non-free-firmware 
deb-src http://deb.debian.org/debian bookworm-updates main non-free-firmware 
Ctrl+x, y, enter 
sudo apt update 
``` 
33. To install the required dependencies for pi-gen run: 
```
sudo apt install quilt qemu-user-static debootstrap zerofree \ 
zip libarchive-tools rsync git curl pigz xxd -y 
``` 
34. Type: 
```
git clone https://github.com/RPI-Distro/pi-gen.git 
```
35. cd pi-gen 
36. ```nano myconfig``` and add:
```
export IMG_NAME=pi5testing 
export IMG_DATE=2024-05-01 
export FIRST_USER_PASS=pi 
export DISABLE_FIRST_BOOT_USER_RENAME=1 
export ENABLE_SSH=1 
export LOCALE_DEFAULT=en_US.UTF-8 
export KEYBOARD_KEYMAP=us 
export KEYBOARD_LAYOUT="English (US)" 
export TIMEZONE_DEFAULT=America/New_York 
```
37. ``` Ctrl+x, y, enter ```
38. ```nano stage2/01-sys-tweaks/00-patches/07-resize-init.diff``` and remove: 
```
quiet init=/usr/lib/raspberrypi-sys-mods/firstboot 
```
39. ``` Ctrl+x, y, enter ```
40. ```nano stage5/00-install-extras/00-packages and add: ```
```
vim 
libi2c-dev 
codeblocks 
libfuse2 
libncurses-dev 
```
41. ```Ctrl+x, y, enter ```
42. ```nano stage5/00-install-extras/01-run.sh``` and create: 
```
#!/bin/bash -e 

on_chroot << EOF 
wget https://github.com/joan2937/lg/archive/master.zip 
unzip master.zip 
cd lg-master 
make 
#sudo make install 
#is this the place to run the nmcli commands as well? 
EOF 
``` 
43. ```Ctrl+x, y, enter ```
44. ```chmod a+x stage5/00-install-extras/01-run.sh ```
45. ```sudo ./build.sh -c myconfig ```

Configuration still needs tweaking to attempt to match the previously hacked image, a run seems to take over 40 () minutes. 

## image-testing 
Image should boot on the following platforms as of 4/29/2024, the 4Bs since current students have them and the 5B since the next order should ideally be of 5Bs.   
    Q2 2019 4B V1.1 b03111   
    Q1 2022 4B V1.5 b03115   
    Q1 2022 4B V1.5 c03115   
    __ ____ 5B V1.0 c04170   
It is helpful for the image to be backwards compatible with existing 2B and 3Bs on campus and for CENG 317 and CENG 355 Wi-Fi is required. For CENG 260, Open CV+ is required, specifications unknown currently.   

## legacy-process
Format an at least class 10 minimum of 16GB SD card with: https://www.sdcard.org/downloads/formatter_4/index.html   
Use win32diskimager (used instead of rufus, balena etcher, Raspberry Pi Imager since it can also read images) to write [2025-05-13-raspios-bookworm-armhf-full.img](https://downloads.raspberrypi.com/raspios_full_armhf/images/raspios_full_armhf-2025-05-13/2025-05-13-raspios-bookworm-armhf-full.img.xz) to a 16GB or bigger card   
Boot on a pi connected to hardwired monitor, keyboard and mouse, then make the following tweaks   
canada canadian english toronto us keyboard english language   
pi/pi login/password   
firefox over chromium   
skip, reboot   
firefox calls home, has weird initial settings, change them before connecting to the internet   
remove quiet in /boot/commandline.txt such that can see waiting for network   
hdmi_group=1   
hdmi_mode=4   
Recall that hooking up a monitor helps with image debugging but not so much if the video feed blanks after a timeout , consider https://www.raspberrypi.com/documentation/computers/configuration.html#list-of-options30   
sudo raspi-config nonint do_blanking 1   
sudo raspi-config nonint do_audio 1   
sudo raspi-config nonint do_ssh 0   
sudo raspi-config nonint do_vnc 0   
sudo raspi-config nonint do_i2c 0   
sudo nmcli con mod “Wired connection 1” ipv4.addresses 169.254.0.2/16 ipv4.gateway 169.254.0.1 ipv4.dns 0.0.0.0 ipv4.method manual   
sudo systemctl restart NetworkManager   
cd Desktop   
wget https://github.com/joan2937/lg/archive/master.zip   
unzip master.zip   
cd lg-master   
make   
sudo make install  
cd ~   
add   
[/home/pi/C153Doxygen2023-05-30](https://github.com/PrototypeZone/ceng153/tree/main/C153Doxygen2023-05-30)   
[/home/pi/C153SenseHat2025-06-12](https://github.com/PrototypeZone/ceng153/tree/main/C153SenseHat2025-06-12)   
Then compile at a terminal in the sensehat directory by typing:   
make? (vs gcc shmenu.c hts221.c lps25h.c led2472g.c lsm9ds1.c tcs3400.c -li2c)   
(Note that only the latest Sense HAT Version 2 has the TCS3400 RGB colour and brightness sensor)   
run by typing:   
./a.out   
gcc shtest.c hts221.c lps25h.c led2472g.c lsm9ds1.c tcs3400.c -li2c -o /home/pi/shtest   
edit /etc/rc.local and add sudo /home/pi/shtest & on a line before the exit command   
Start (Raspberry Symbol)->Programming->Visual Studio Code 

Install the C/C++ Extension by Microsoft 
Here's the resulting start to a bookworm image, 2025-08-07pi5fall2025:   
```TODO insert sharepoint link to zip```   
​
The current start to a bookworm image might not have this yet so connect via VNC viewer and use the GUI to connect to the eduguest WiFi and open a browser to 1.1.1.1,  http://wifi-portal.humber.ca/wifisplash.php with appended MAC address to accept terms to be able to:   

sudo apt install vim -y   
sudo apt install libi2c-dev -y   
sudo apt install codeblocks -y   
codeblock dependencies noted here in case networking is down (note that we now use vscode... so update here todo... sudo apt install code -y):   

sudo apt install codeblocks-common   
sudo apt install libastyle3   
sudo apt install libcodeblocks0   
sudo apt install libtinyxml2.6.2v5   
sudo apt install libutempter0   
sudo apt install xbitmaps   
sudo apt install xterm   

sudo apt install libfuse2 -y   
sudo apt install libncurses -y   
sudo apt install libncurses-dev -y

Note for older pi image https://archive.raspbian.org/raspbian/pool/main/i/i2c-tools/libi2c-dev_4.1-1_armhf.deb can be used despite errors.   

So far we've noticed that vi is loaded instead of vim, and that for later in CENG 153 we also sudo apt install codeblocks, in case of no internet download and install separately: 

sudo dpkg -i vim-runtime_9.0.1378-2_all.deb   
sudo dpkg -i vim_9.0.1378-2_armhf.deb   
sudo dpkg -i libi2c-dev_4.3-2+b2_armhf.deb   
sudo dpkg -i libwxbase3.0-0v5_3.0.5.1+dfsg-5+b1_armhf.deb   
sudo dpkg -i libwxgtk3.0-gtk3-0v5_3.0.5.1+dfsg-5+b1_armhf.deb   
sudo dpkg -i libtinyxml2.6.2v5_2.6.2-6_armhf.deb   
sudo dpkg -i libastyle3_3.1-3_armhf.deb   
sudo dpkg -i libcodeblocks0_20.03-3_armhf.deb   
sudo dpkg -i codeblocks-common_20.03-3_all.deb   
sudo dpkg -i codeblocks_20.03-3_armhf.deb   
sudo dpkg -i xbitmaps_1.1.1-2.1_all.deb   
sudo dpkg -i libutempter0_1.2.1-3_armhf.deb   
sudo dpkg -i xterm_389-1_armhf.deb   
sudo dpkg -i libfuse2_2.9.9-8_armhf.deb   
sudo dpkg -i libncurses-dev_6.4-4_armhf.deb   

I have a couple of scripts one is 6 years old that attempted to duplicate Paul's image creation steps (which additionally set up mysql-server, phpmyadmin, glgtoolkit among other steps) and a simple one that adds the above packages once downloaded thus winscp transfer getstartedwithpi5testing if available:   

chmod u+x additionalpackages.sh   
./additionalpackages.sh   

which adds vim, codeblocks, and xterm, otherwise add them manually.   

change menu entry for codeblocks to use sudo since otherwise the icons are unwieldy.   

use vnc viewer click on up/down arrow Click here to set Wi-Fi Country CA Canada OK, eduguest   

Once Wi-Fi is reliable again this is a moot point due to Network Time Protocol (NTP) but for now:   

Set the date sudo date –s “01 MAY 2020 13:00:00”   
             sudo date -s "15 FEB 2024 12:22:00"   

https://forums.raspberrypi.com/viewtopic.php?t=370152   
