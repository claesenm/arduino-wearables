# arduino-wearables
Prototype exhibitions for the Health House based on Arduino, Raspberry Pi &amp; the health sensor kit.

Information about all sensors is available at [cooking hacks](https://www.cooking-hacks.com/documentation/tutorials/ehealth-biometric-sensor-platform-arduino-raspberry-pi-medical/). Make sure to read carefully before attaching a new sensor.

## Basic steps

1. Unplug the RPi, which will kill power to the Arduino too.
1. Attach your favorite sensors to the Arduino's health sensor shield.
2. Plug the RPi back in, it will automatically boot and set up the `Raspberry_WiPi` access point.
3. Connect to `Raspberry_WiPi` (password: 'wearables').
4. SSH into the RPi (ip 192.168.42.1, password 'raspberry' if you are connected to `Raspberry_WiPi`) and run `sudo read_serial` until it starts spamming sensor readouts (sudo password is 'raspberry'). This may take a few tries. If it refuses to work, unplug RPi and try again. Do not kill the terminal or the RPi will stop doing sensor readouts (also keep the connection open ... I will install screen on the RPi soon to get rid of this mess).
5. You should now be able to access the MongoDB that is hosted by the RPi from your own laptop at `
'mongodb://192.168.42.1:27017/'` (no username/password required).

For plotting libraries, some good places to start are:
- matplotlib (Python's default plotting library): http://matplotlib.org/
- D3.js (cool javascript plots, very popular): https://d3js.org/
- mpld3 (matplotlib interface to D3.js): http://mpld3.github.io/
