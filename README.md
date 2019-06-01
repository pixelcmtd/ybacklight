# ybacklight
A complete "rewrite" of xbacklight that actually works.
# Building & Debugging
You can build normally with `make`, test with `make test` and just
compile a debug version with `make debug`.
# Requirements
* A recent version of Linux (2.4.10+, the BSDs aren't tested but
should work)
* A monitor with a software-controllable backlight (every laptop has one)
# Installing
If you've got netsh installed just run `netsh chrissxYT/ybacklight`, else run
`curl -L https://github.com/chrissxYT/ybacklight/raw/master/netsh | sh`.
Our if you have already cloned the repo, run `make install`.
