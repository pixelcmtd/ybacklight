# ybacklight

A simpler alternative to `xbacklight`.

# Building & Debugging

* Configure in `config.h`
* Build: `make`
* Test: `make test`
* Install: `make install`
* Build with debugging support: `CFLAGS="-Og -g" make`

# Requirements

* Linux 2.4.10+ (or another `sysfs` compatible OS)
* A monitor with a software-controllable backlight (practically a laptop)

# Installing

`netsh -C "sudo make install" -c pixelcmtd/ybacklight`
