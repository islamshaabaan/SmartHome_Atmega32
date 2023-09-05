
# Smart Home

[Remotely Controlled Home (AVR-ATmega32 Proteus Simulation)](https://drive.google.com/file/d/1RflksQqBNHOmFjZTG-YJuDq2tQf6iYvx/view?usp=drive_link)

## Description:

#### The system allows controlling the home by mobile phone application through Bluetooth [UART Terminal with TTL]. 

#### There Are subsystems are implemented; 
	1- First You should entering user name and password	
	
	2- Choose Options:
	  - a Safety door [Servo Motor] that could be opened
	  - a light On/Off that could also be controlled
	  - a Fan [DC Motor] On/Off
	  -  ..
	  -  ..

#### The system supports 5 users with different names and passwords, and uses an external EEPROM to read and save users' data.

#### In case of entering the username and password 3 times wrong, the system should give an alarm.

## Project Design:
### The project is based on Layered Architecture and operates inside a Super Loop.

### Files:
- #### Application Layer:
	1. main.c
 - #### Hardware Abstraction Layer[HAL]:
	 1. Bluetooth_Module: Driver for HC-05 Bluetooth module and is used for interfacing with mobile phone
	 2. EEPROM: Driver for ST24C08 EEPROM and is used to read and write data from and to the EEPROM
	 3. SERVO: Driver used to control the Servo Motor
    	 4. DC Motor: Driver used to control the DC Motor
	 5. SIREN: Driver used to make a siren sound from the buzzer
   	 6. LED : Driver used to Control the LED
 - #### Microcontroller Abstraction Layer[MCAL]:
	 1. DIO: Driver used to control the GPIO pins
	 2. TIMERS: Driver used for controlling timers for Servor and Buzzer
	 3. TWI: Driver used for interfacing with the I2C peripheral for EEPROM communications
	 4. UART: Driver used for interfacing with the UART peripheral for bluetooth communications
- #### Library Layer[LIB]:
	1. BIT_MACROS: Contains bit-wise operations
	2. STD_TYPES: Contains all the data types used
## Project design:

![Smart_Home](https://github.com/islamshaabaan/SmartHome_Atmega32/assets/36308342/c785e5a1-08aa-4ad9-b4cc-6b4efc5657e7)

  
