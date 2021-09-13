#!/bin/sh

./ybacklight Sc/Sm
PREV=$(./ybacklight c)
MAX=$(./ybacklight m)

t() {
        echo "$2/$MAX ($1)"
        ./ybacklight "$1"
        [ -z $3 ] && sleep 1
}

t Ss5 500
t i200 700
t d500 200
t s$PREV $PREV no
