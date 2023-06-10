# MQTT-MaraX

It is important to know when the coffee generator is sufficiently heated for extraction. Additionally, one doesn't want to get up, so the whole setup needs to be wireless. 
The temperature is read using an ESP8266 and sent to an MQTT server. The analog device is also an ESP and retrieves the data from the MQTT server.
![PXL_20230408_190545692](https://github.com/zierroff/MQTT-MaraX/assets/62383514/facb346e-c6da-4266-a8fd-34ff4da62c74)



## Resources for the project
First i want to thank: 
* [marax_monitor](https://github.com/bancbanus/marax_monitor) 
* [marax_timer](https://github.com/alexrus/marax_timer)
* https://www.reddit.com/r/Coffee/comments/hfsvep/data_visualisation_lelit_marax_mod/

## 

## Power supply:
In the old building where the machine is supposed to be placed, power outlets are scarce. Therefore, I am using the one built into the machine.

An ESP requires either 3.3V or 5V as a power supply. Caution: The 5V available at the MaraX control unit should NOT be used!

This is the part inside the machine:

When opened, it looks like this:

There are 2 circuit boards: The one on the right with the switch-mode power supply for 230V to 12V and the relays. The one on the left with the control and a linear regulator for 12V to 5V. The linear regulator used is an LM7805 in a DPAK package. An ESP can require up to 500mA with WLAN enabled, and the regulator gets too hot and fails.

However, the switch-mode power supply on the right board is designed more robustly. It also needs to drive the relays. Therefore, I soldered 2 wires to the smoothing capacitor of the 12V power supply. These 2 solder joints can be quickly removed if necessary. The wires are passed through the hole because it fit better into the Gicar's enclosure. They are then converted to 3.3V for the ESP using an OKI-78SR-3.3 power supply.

Serial output reading:
The serial output of my Gicar is inverted. This needs to be taken into account in the ESP software. Additionally, I use a level converter for 5V to 3.3V for the ESP. I am aware that many people omit this step. I am using a relatively expensive ADUM1201, but a cheaper one would also do the job.

I always recommend soldering the final product and, in the case of the coffee machine, shrinking it. Breadboards are not a good choice for long-term use.
