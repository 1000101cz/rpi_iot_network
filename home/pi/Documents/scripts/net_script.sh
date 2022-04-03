# FAKE MAC | 27/01/2022 | Stepan Marousek
#   - change ethernet MAC address to fuck with SiliconHill :)

echo "
hacking into SiliconHill network....

"

sudo ifconfig eth0 down
sudo ifconfig wlan0 down
sudo macchanger -p -m FAKE_MAC_ADDRESS eth0
A=$?
sudo ifconfig eth0 up

if [ $A == 0 ]; then
	echo "
hack complete

kudos!
"
else
	echo "
nothing done
"
fi

bash
