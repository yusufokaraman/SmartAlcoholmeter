# SmartAlcoholmeter

The goal of this research is to show data
(card-identification information, fingerprint information, alcohol value, heart
pulse value) obtained from external environments on the C # interface screen
and control various devices with the interface based on the inputs. The
hardware's embedded software is developed in C, with the IAR compiler, while
the interface is designed in C # with Visual Studio. Hardware includes a
fingerprint reader, heart rate sensor, alcohol measuring sensor, and RFID card
reader sensor.

# Block Diagram
## ElectricaL Block Diagram

![electrical Blok diagram](https://user-images.githubusercontent.com/34060382/146657651-148acdbb-8eb5-4959-8d3c-e03b1465295f.png)

## Communication Block Diagram

![Communication Diagram](https://user-images.githubusercontent.com/34060382/146657657-a29e68f5-8182-46aa-9bdd-5da82f993d96.png)

## STM32F407VG Software Block Diagram

![STM Software Block Diagram](https://user-images.githubusercontent.com/34060382/146657676-432192da-c804-41d7-8948-3c717fc55b24.png)
### Embedded C Codes Explanation
First of all, it started from GPIO settings. In our project,
3 communication units, 2 USART and 1 SPI, are used. In addition, 1 pin for the
user button, 5 output pins for general purpose use, and 2 pins for the ADC have
been set.



General settings for the 2 USART units are made in the
USART_Config function. The baudrate of the fingerprint sensor is set to 57600.
This setting is adjusted to determine the amount of fingerprints to be stored.
USB TTL is used to provide the old communication between the C # interface and
the device. TTL baudrate was chosen as 9600.



SPI communication has been selected for RFID. The commands
specified in the RFID's datasheet are sent to the device and the card reading
functions of the device have been adjusted.



The ADCs to be used have been selected as 12bit, and their
measurements with the DMA unit are set to be sent to the C # interface via the
serial port. For interrupt setup, the function named NVIC_Config has been used
to configure two different interrupts according to their priority settings.



Thanks to a boolean value defined in the interrupt, the
transition to the necessary functions was made by checking whether data is
received from the C # interface.



1 struct has been defined for the fingerprint sensor. Thanks
to Struct, it is provided to add address, password and reading functions to be
used in fingerprint. Afterwards, the start commands were sent in accordance
with the datasheet with the USART interface and reading functions were created.
While the fingerprint is being read, the sensor is set to send finger data to
the microprocessor. The reading function has been created by transmitting the
necessary commands with the RFID card reader sensor SPI interface. Alcohol and
heart rate values are set to be sent to the C # interface by DMA and ADC
sensors.

## C# Software Block Diagram

![C# Software Block Diagram](https://user-images.githubusercontent.com/34060382/146657690-3fdc17fd-8bcf-4012-9982-83473651c456.png)

### Interactives
The "new entry" button was clicked on Form1 and
Form2 was loaded. The card information of the persons is taken from an external
hardware with the RFID module. To receive this data, 1 is sent from the serial
port and the STM32 sends the data read from the RFID to the interface via the
serial port. The user is asked whether this data is accepted or not. If the
user thinks that the read data is not correct and does not accept it, the data
is read again, this process occurs again. If the user thinks that the data is
correct, the user is asked whether the data will be recorded in the database or
not. If the user accepts the data to be saved in the database, the screen
writes green OKAY, the buzzer sounds 1 time and updates the database with
reference to its name, if the user does not want the data to be saved in the
database, the data will not be saved and in both conditions, it will increase
the index by 1 and switch to the other data reading operation.

### Initialize Form
![Form](https://user-images.githubusercontent.com/34060382/146657714-86aae744-01c0-4742-9495-165826285316.png)

The alcohol button is clicked on the interface, the value 2
goes to STM32 from the interface. Alcohol values of the persons are measured
with alcohol meter. The measured value is sent from STM32 to the interface via
the serial port. This received value is shown on the screen. If the person
using the interface thinks that the alcohol level is high and presses the high
button, the red LED lights up, the buzzer sounds a long time and the interface
says "high Alcohol value". If the person using the interface thinks
that the alcohol level is low and presses the low button, the green LED will
turn on, the buzzer will sound once and the interface will write "alcohol
free".
### Smart Alcoholmeter Interface
![2](https://user-images.githubusercontent.com/34060382/146657736-cad1f6cc-c42c-4fce-9377-dac93eb0e1fd.png)

The heart rate measurement button is clicked on the
interface, the 3 value is sent to STM32 via serial port. Taking 3 values, STM32
performs the pulse measurement and transfers the measured value to the
interface with the serial port. The measured value is displayed on the
interface. If the person using the interface thinks that the pulse level is low
and presses the low button, the green LED turns on, the buzzer sounds once and
the interface shows "no risk". If the user thinks that the pulse
level is high, he / she clicks the high button and a warning message appears.
If the person is thought to be both intoxicated and has a high pulse rate, click
the "danger" button and a "risk" warning appears on the
interface, the buzzer beeps intermittently for a long time.



The "Enroll fingerprint" button is clicked from the
interface and the value 1 is sent to STM32 from the interface, STM32 takes the
fingerprint and transfers the data back from the serial port to the interface.
If the user thinks that the information is correct, he clicks the OK button and
the screen says green OKAY, the buzzer chirps once. If the user thinks that the
information is wrong, he clicks the button again and re-reading processes
occur. After the information is received, the user is asked whether to register
in the database or not. If yes, the data database is updated, and the green LED
is lit. If it is said no, the data are not saved.

