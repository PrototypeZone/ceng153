# Steps taken to create Raspberry Pi OS SD card image suitable for this course

## 2025-08-07
(editor's note to self see Documents\ceng317\DevelopmentTimeNeeded.txt)   
We are looking to create a ready to go version of   
https://downloads.raspberrypi.com/raspios_full_armhf/images/raspios_full_armhf-2025-05-13/2025-05-13-raspios-bookworm-armhf-full.img.xz   
which will include:   
[/home/pi/C153Doxygen2023-05-30](https://github.com/PrototypeZone/ceng153/tree/main/C153Doxygen2023-05-30)   
[/home/pi/C153SenseHat2025-06-12](https://github.com/PrototypeZone/ceng153/tree/main/C153SenseHat2025-06-12)   
[/home/pi/lg-master](https://github.com/joan2937/lg)

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
7. Name: 2024-03-15-rpioshf
8. ISO Image: debian-12.5.0-amd64-DVD-1.iso
9. Username: vboxuser   
Password: changeme   
Hostname: 2024-03-15-rpioshf   
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
