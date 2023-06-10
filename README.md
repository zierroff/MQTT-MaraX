# MQTT-MaraX

It is important to know when the coffee generator is sufficiently heated for extraction. Additionally, one doesn't want to get up, so the whole setup needs to be wireless. 
The temperature is read using an ESP8266 and sent to an MQTT server. In my case a Raspi with a docker mosquitto. The analog device is also an Wifi enabled ESP and retrieves the data from the MQTT server.
![PXL_20230408_190545692](https://github.com/zierroff/MQTT-MaraX/blob/main/pictures/complete.jpg)

## Resources for the project
First i want to thank: 
* [marax_monitor](https://github.com/bancbanus/marax_monitor) 
* [marax_timer](https://github.com/alexrus/marax_timer)
* https://www.reddit.com/r/Coffee/comments/hfsvep/data_visualisation_lelit_marax_mod/
* [pimp-my-marax](https://github.com/michelhe/pimp-my-marax)

## Power supply:
In the old building where the machine is supposed to be placed, power outlets are scarce. Therefore, I am using the one built into the machine.
An ESP requires either 3.3V or 5V as a power supply. Caution: The 5V available at the MaraX control unit should NOT be used!

This is the part inside the machine:

<img src="https://github.com/zierroff/MQTT-MaraX/blob/main/pictures/Gicar1.jpg" width="40%" >

When opened, it looks like this:

![Gicar3](https://github.com/zierroff/MQTT-MaraX/blob/main/pictures/Gicar3.jpg)

There are 2 circuit boards: The one on the right with the power supply for 230V to 12V and the relays. The one on the left with the control system and a linear regulator for 12V to 5V. The linear regulator used is an LM7805 in a DPAK package. An ESP can require up to 500mA with Wifi enabled, and the regulator gets too hot and fails.

However, the power supply on the right board is designed for more. It also needs to drive the relays. Therefore, I soldered 2 wires to the capacitor of the 12V power supply. These 2 solder joints can be quickly removed if necessary. The wires are passed through the hole because it fit better into the Gicar's enclosure. They are then converted to 3.3V for the ESP using an OKI-78SR-3.3 power supply.

Here the solder points can be seen: 
![Gicar4](https://github.com/zierroff/MQTT-MaraX/blob/main/pictures/Gicar4.jpg)

## Serial output reading:
The serial output of my Gicar is inverted. This needs to be taken into account in the ESP software.
Additionally, I use a level converter for 5V to 3.3V for the ESP. I am using a relatively expensive ADUM1201, but every cheap 1$ TTL logic level converter chip would also do the job. 

## Software 
Please read through the code if you want to use this project for yourselves. The code is made with vscode and the platformio addon. There are a few things you have to change: Wifi Password, Wifi SSID, MQTT IP. 

The data is streamed in when the ESP is powered on. I am splitting the data with the ESP and sending it to the Mqtt Server. 
If you want to check the pump with a reed sensor i have added the option in Software on pin14. The data is read every 100ms and send. So there is a error of 200ms if that concerns. In the end i have not added the reed sensor since the flag option also sendes when the pump SSR is powerd. 
Please read trough the 

## Schematic
The OKI-78SR family comes pin compatible to a 7805 but without the need of capacitors and much more efficent. So i choose a 3.3V variant for the project.
The LLC should be connected to Pin 3 and 4 on the Gicar. (Starting with pin1).

![Untitled Sketch_Steckplatine](https://github.com/zierroff/MQTT-MaraX/blob/main/pictures/fritzing.jpg)

I always recommend soldering the final product and, in the case of the coffee machine, shrinking it. Breadboards are not a good choice for long-term use.

![solder](https://github.com/zierroff/MQTT-MaraX/blob/main/pictures/shrink.jpg)
![shrink](https://github.com/zierroff/MQTT-MaraX/blob/main/pictures/solder.jpg)



