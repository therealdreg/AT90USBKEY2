ATMEL Corp January 2006


USB bootloader implementation for AT90USBXXX devices.


This USB bootloader can be used to program the flash of AT90USBXXX device through the USB bus.

The bootloader enumerates with the USB DFU class and requires Flip3 software to be installed to operate.

The windows drivers for AT90USBXXX are provided within the Flip3 installation package.

When connecting the AT90USBXXX bootloader and prompt for a windows drivers, make the drivers install procedure points to the FLip3/usb installation directory path.
Usually : "C:\Program Files\Atmel\Flip3\usb\usb_dfu.inf"

Parts come with the USB device bootloader preprogrammed in the bootloader section of the on-chip flash memory.
The bootloader can be activated upon reset thanks to the HWB pin.



