# ybacklight

A program (and library) for managing the screen brightness.

A simpler alternative to `xbacklight`.

## Building & Debugging

- Configure in `config.h`
- Build: `make`
- Test: `make test`
- Install: `make install`
- Build with debugging support: `CFLAGS="-Og -g" make`

## Requirements

- Linux 2.4.10+ (or another `sysfs` compatible OS)
- A monitor with a software-controllable backlight (practically a laptop)

## Installing

`netsh -C "sudo make install" -c pixelcmtd/ybacklight`

## Usage

`ybacklight [instruction-stream]`

The `instruction-stream` contains a series of instructions.

`ybacklight` can be understood like a simple VM with four registers that we will
call `A`, `S`, `C` and `M` here. `A`, `C` and `M` are `long long` (64 bit
integer on sane compilers), `S` is a `boolean` value.

On startup, `C` is read as the current `brightness value` of the display and `M`
from the maximal `brightness value` of the display, `S` is `false` and `A` `-1`.

Before exit, `C` is, if changed, written to the display's current
`brightness value` and if any characters were written to `stdout`, a newline is
written.

### Instructions

- All numbers (`[0-9]+`) set the `A` register to their value, read in decimal
- `S`: sets the `S` register to `true`
- `c`: prints the `C` register to `stdout`
- `m`: prints the `M` register to `stdout`
- `s`: sets the `C` register to the value of the `A` register
- `i`: increments the `C` register by the value of the `A` register
- `d`: decrements the `C` register by the value of the `A` register
- All other instructions are just echoed

`s`, `i` and `d` can also be queued: If a number follows them directly, that is
interpreted first.

You just need to understand one more constant: `SHORT_FACTOR` is defined in
`config.h`, usually `100`. All reads/writes from/to the `C` and `M` registers
are divided/multiplied by `SHORT_FACTOR`, if the `S` register is set to `true`.

### Examples

Examples have been merged into tldr (`tldr ybacklight`), so they are maintained
[there](https://github.com/tldr-pages/tldr/blob/main/pages/common/ybacklight.md).

### Using `ybacklight` as a library

If you want to, you can also use `ybacklight.c` as a library for reading and
writing brightness values.

Give `read_brightness` the path of the brightness file to read from (e.g.
`/sys/class/backlight/intel_backlight/brightness`) and it will yield the value.

Give `write_brightness` the path of the brightness file to write to and the
value to write and it will write it.
