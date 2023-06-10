# MQTT-MaraX

It is important to know when the coffee generator is sufficiently heated for extraction. Additionally, one doesn't want to get up, so the whole setup needs to be wireless. 
The temperature is read using an ESP8266 and sent to an MQTT server. The analog device is also an Wifi enabled ESP and retrieves the data from the MQTT server.
![PXL_20230408_190545692](https://github.com/zierroff/MQTT-MaraX/assets/62383514/facb346e-c6da-4266-a8fd-34ff4da62c74)



## Resources for the project
First i want to thank: 
* [marax_monitor](https://github.com/bancbanus/marax_monitor) 
* [marax_timer](https://github.com/alexrus/marax_timer)
* https://www.reddit.com/r/Coffee/comments/hfsvep/data_visualisation_lelit_marax_mod/

## Power supply:
In the old building where the machine is supposed to be placed, power outlets are scarce. Therefore, I am using the one built into the machine.
An ESP requires either 3.3V or 5V as a power supply. Caution: The 5V available at the MaraX control unit should NOT be used!

This is the part inside the machine:

<img src="https://github.com/zierroff/MQTT-MaraX/assets/62383514/46ae73fe-fe88-4b1a-ac53-1d6c4af69dda" width="40%" >

When opened, it looks like this:

![Gicar3](https://github.com/zierroff/MQTT-MaraX/assets/62383514/5e4ed34f-6f2e-483c-9344-36140b5a0fb9)

There are 2 circuit boards: The one on the right with the power supply for 230V to 12V and the relays. The one on the left with the control system and a linear regulator for 12V to 5V. The linear regulator used is an LM7805 in a DPAK package. An ESP can require up to 500mA with Wifi enabled, and the regulator gets too hot and fails.

However, the power supply on the right board is designed for more. It also needs to drive the relays. Therefore, I soldered 2 wires to the capacitor of the 12V power supply. These 2 solder joints can be quickly removed if necessary. The wires are passed through the hole because it fit better into the Gicar's enclosure. They are then converted to 3.3V for the ESP using an OKI-78SR-3.3 power supply.

Here the solder points can be seen: 
![Gicar4](https://github.com/zierroff/MQTT-MaraX/assets/62383514/1d9ff8aa-7775-4612-8bc1-92e7dae573ac)

## Serial output reading:
The serial output of my Gicar is inverted. This needs to be taken into account in the ESP software.
Additionally, I use a level converter for 5V to 3.3V for the ESP. I am aware that many people omit this step. I am using a relatively expensive ADUM1201, but every cheap 1$ TTL logic level converter chip would also do the job.

I always recommend soldering the final product and, in the case of the coffee machine, shrinking it. Breadboards are not a good choice for long-term use.

![Geschrumpft](https://github.com/zierroff/MQTT-MaraX/assets/62383514/a9bb527d-67de-4b38-9809-fa05bf41bf46)
![Gelötet](https://github.com/zierroff/MQTT-MaraX/assets/62383514/60cab6ab-3eca-4c20-b1ef-c46dba14e6d4)

## To Do
* Will add a fritzing
* Clean the code



