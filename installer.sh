#!/bin/sh
git clone https://github.com/chrissxYT/ybacklight.git .yb-setup-foo
cd .yb-setup-foo
./build
./install
cd ..
rm -rf .yb-setup-foo
