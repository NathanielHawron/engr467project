# ENGR 467 Course Project &ndash; "Nuclear ChibiOS"

This course project provides the scheduling and IPC capabilities of ChibiOS
on the NUCLEO-H563ZI STM32 development board.

## Software Requirements

This project requires the following software:

- Git
- GNU Make
- ARM GNU Toolchain (arm-none-eabi)
- STM32CubeProgrammer
- GNU Debugger (GDB) (debugging only)
- OpenOCD (debugging only)

### Arch Linux

Most software components can be installed through the `pacman` package manager:

```bash
sudo pacman -Syu
sudo pacman -S --needed base-devel gdb git arm-none-eabi-gcc openocd
```

Install STM32CubeProgrammer through STMicroelectronics' offical site:
[STM32CubeProg](https://www.st.com/en/development-tools/stm32cubeprog.html)

### Debian-based Linux

Most software components can be installed through the APT package manager:

```bash
sudo apt update
sudo apt upgrade -y
sudo apt install make git gdb gcc-arm-none-eabi openocd
```

Install STM32CubeProgrammer through STMicroelectronics' offical site:
[STM32CubeProg](https://www.st.com/en/development-tools/stm32cubeprog.html)

### Other Linux Distros

Check your linux distro's official repositories for the software mentioned
above. You may need to install some software through their official websites.
See the Windows setup section for those websites.

### Windows

You will need to install all software either through their official websites
or through your preferred package manager if possible (e.g. `winget`, `scoop`,
or Chocolatey). The official download sites for all software is provided below
for convenience:

- Git: [Git-Install for Windows](https://git-scm.com/install/windows)
- GNU Make,GDB, and OpenOCD: [MSYS2](https://www.msys2.org/)
- ARM GNU Toolchain: [ARM GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- STM32CubeProgrammer: [STM32CubeProg](https://www.st.com/en/development-tools/stm32cubeprog.html)

