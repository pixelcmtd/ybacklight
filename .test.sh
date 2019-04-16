sudo make debug
sudo chmod +s ybacklight
PREV=$(./ybacklight cur)
MAX=$(./ybacklight max)
echo "500/$MAX (set 500)"
sudo ./ybacklight set 500
sleep 2
echo "700/$MAX (inc 200)"
sudo ./ybacklight inc 200
sleep 2
echo "200/$MAX (dec 500)"
sudo ./ybacklight dec 500
sleep 2
echo "$PREV/$MAX (set $PREV)"
sudo ./ybacklight set $PREV
