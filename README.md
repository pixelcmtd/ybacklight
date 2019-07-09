# ybacklight
A complete "rewrite" of xbacklight that actually works.
# Building & Debugging
You can build normally with `make`, test with `make test` or just
compile a debug version with `make debug`. (and there's also
`make lol`, which you should avoid)
# Requirements
* A recent version of Linux (2.4.10+, the BSDs aren't tested but
should work)
* A monitor with a software-controllable backlight
(virtually every laptop has one)
# Installing
To install this just run
`netsh -C "sudo make install" -c chrissxYT/ybacklight`.
