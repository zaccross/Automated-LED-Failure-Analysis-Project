## Our Project Experience Recap


  Using breadboards, we connected the circuits diagrammed in Figure 1. When testing the Arduino code, we found that not all the LEDs were powered. 
  Furthermore, the LEDs were flickering due insufficient voltage supply. Since the Keithley was being run at maximum output, we had to switch 
  to a GW Instek power supply, which can   provide 30 V and up to 3 amps of current. It is possible that the Keithley had trouble keeping a consistent 
  voltage supply with the duty cycle of the Arduino pins, we hoped that since the GW Instek power supply was a simpler design, it would not try
  to compensate for the frequency and provide a constant voltage.
  
  After assuring sufficient voltage supply with the new equipment, we connected the Raspberry Pi to test the code. 
  Commands sent by the Raspberry Pi were reflected   back from the Arduinos. This could be due to an issue with the serial read 
  on the Arduino, or because the four Arduinos ran in parallel on the same serial pins of the Pi. Due to time constraints, we 
  were unable to resolve the issue. 
  
  ![image](https://user-images.githubusercontent.com/80741351/145652985-313adc01-06a4-4b22-9345-40bd489b2426.png)

  #### Figure 1: 
  Physical realization of the apparturs minus the raspberry pi. LEDs on the leftmost breadbord and Photodiodes on the rightmost breadboard.

