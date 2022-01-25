# Introduction: 
	
	
  Light emitting diodes (LEDs) have found widespread use due to their low power consumption, low cost, and long lifetime. 
  They offer narrow band emission in a variety of colors and are consistently being improved. Because LEDs are ubiquitous in 
  virtually every industry, the importance of reliability cannot be understated. LEDs failure is often characterized by a gradual 
  decrease in luminous intensity over the lifetime of the bulb, although instantaneous failure occasionally occurs as well. LED 
  failure can be categorized into three types: packaging-related, semiconductor/metal-related, and stress-related. This study 
  focuses on stress-related failure.

  This study explores the operating limits of light emitting diodes (LEDs) through systematic variation of experimental factor 
  levels. Designing an automated failure analysis system using Arduino and Raspberry Pi microprocessors. Each experimental run 
  will power 9 LEDs at 25%, 50%, and 75% of the max duty cycle. To allow the LEDs to fail in a reasonable amount of time, they 
  will be operating above the manufacturers recommended levels. To estimate the current level to be used, an LED was driven to 
  failure by a direct current. The LEDs were more robust than anticipated, requiring ≈160 mA before a visible dimming occurred.
  Increasing the current over the next couple minutes, the diode failed completely at 190 mA. Each experimental run used 180 mA
  of current to drive the LEDs, which required an external power source.
  
  This experiment used VCC 4300H5LC cadmium sulfide LEDs with a peak wavelength of 565 nm. The digital pins on the Arduinos were 
  used to apply a gate voltage of +5V to an NTE2397 n-MOSFET from NTE Electronics. The FET acted as a switch to supply 20 V to the 
  LED circuit. The experiment used two Arduino Nanos to power and pulse the LEDs, one Nano was used to measure the data from the 
  LEDs, and one Nano was dedicated to the operating the CdS photodetectors (PDV-P8001, Advanced Photonics, Inc). A Raspberry Pi was
  used to send commands and query data from each Arduino microcontroller via the serial pinouts on the devices. The photodetectors 
  used 1kΩ pull-down resistors, a lower resistance value was used so that the detectors would be more sensitive to large drops in 
  luminous intensity. 
 
 
  
  ![image](https://user-images.githubusercontent.com/80741351/145651455-48672073-2f07-4116-9152-9df46b7b193c.png)


  #### Figure 1. 
  Example circuit from experimental setup. Each digital output pulsed the LEDs at a different frequency (max 490 Hz). 
  The current was measured by the analogue input of the measurement Arduino. Resistors were used to control the amount of current 
  through each of the LEDs. 
  
  
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

  #### Figure 2: 
  Physical realization of the apparturs minus the raspberry pi. LEDs on the leftmost breadbord and Photodiodes on the rightmost breadboard.
  
  ## Future plans
	
	
  The next stage of this project will be to find out if the communication error between the Arduino and the Raspberry Pi is a hardware error 
  or a bug in the code. Taking a step back to run unit tests on various functions of the code and circuitry will help us to isolate the issue 
  and create an overall more robust design. We found that the analogue write command in the Arduino software does not allow the full +5V to be 
  utilized on the digital out pins connected to the MOSFET gate. We will need to remedy this issue so that we can be sure that the threshold 
  voltage is reached, and the maximum current is flowing through the device. Once we have established a connection between the devices and is
  working as planned, we will need to isolate each LED and photodetector so that we can get an accurate measurement of the intensity of each LED. 
  The data collected from each run will be analyzed using statistical methods in JMP to characterize and optimize the LED operating conditions. 


