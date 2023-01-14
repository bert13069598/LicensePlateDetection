# LicensePlateDetection

## prerequisite
### environment
```
sudo apt install git bc bison flex libssl-dev make libc6-dev libncurses5-dev crossbuild-essential-armhf gcc-arm-linux-gnueabihf
```
### kernel download
```
git clone --depth=1 --branch rpi-6.0.y
```
### target board config
```
cd kernel
KERNEL=kernel7l
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2711_defconfig
```
### kernel build
```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs –j`nproc`
```
### SDcard porting
edit ext4 &rarr; ~/rootfs <br>
edit fat32 &rarr; ~/boot
```
cd kernel
sudo env PATH=$PATH make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-INSTALL_MOD_PATH=/media/ext4 modules_install
cd arch/arm/boot/
sudo cp zImage /media/fat32/kernel7l.img
sudo cp dts/*.dtb /media/fat32/
sudo cp dts/overlays/*.dtb* /media/fat32/overlays/
sudo cp dts/overlays/README /media/fat32/overlays/
```
## cross compile

Check the [KDIR](https://github.com/bert13069598/LicensePlateDetection/blob/3890d830f38b6a01205d5544345a8ccce080d80f/Makefile#L3) is right path to your kernel path.

```
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
```
