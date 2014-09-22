wikihouse-controls
==================

Welcome to the WikiHouse 4.0 Controls project.

Design principles
-----------------

This is the first WikiHouse that we have hacked with open source electronics.

We are very excited to share this system with you because the building services are (we think) rather special:

1. *DC Power and Data Network*. Most of the house is operating on a low voltage direct current (DC) system, so the electrical and electronic systems are safe and best suited for energy storage and renewable energy production, rather than the alternating current (AC) system we currently use in our homes. The converged DC power and data infrastructure is specifically designed for low power DC devices (mobile phones, tablets, LED lighting, etc.) and creates a sensing, actuation and home automation network using open source software and open design. 

2. *Plug and Play*. The electronics are modular and adaptable so you can easily reposition and reprogram any of the electrical components. The sensing, lighting, heating/ventilation and other services devices can be moved and reconfigured without the need of major works involving professionally qualified technicians. The kitchen and the house electrical panel are the only two places with AC sockets. Open standards, open protocols and open hardware and software have been used extensively: for instance the power sockets include 48V Power over Ethernet (PoE), 12V car and 5V USB adapters. Think plug and play electronics, instead of making expensive and sometimes complicated decisions just to make simple changes in your own home.

3. *You own your data*. The system showcases not only the opportunity to return control of the house to its owner, but also the possibility of household data ownership, as opposed to sharing data with cloud services where data collected by sensors or 'smart' appliances is typically owned by a private company or corporation. Welcome the *Intranet of Things*!.

4. *Professional LED lighting*. We have also introduced full white spectrum, high colour rendering, professional LED lighting to a domestic application. Domestic LED lighting has been provided by most of the manufacturers by retrofitting LEDs to the AC infrastructure, compromising on quality of the emitted spectrum and on dimming capabilities. Wikihouse 4.0 has a 24V DC power system with constant current dimming from a centralised panel and full spectrum, high colour rendering LEDs that dim down to zero using the open DMX protocol.

5. *Open Hardware*. Wikihouse 4.0 included an open design heat recovery fan (openMVHR) and other open hardware devices such as the Olimex Olinuxino A20 single board computer, Arduino ethernet microcontroller boards and shields, the Adafruit motor shield V2.0, Seeeduino Grove sensors and the Open DMX USB controller.

6. *Open Building Automation*. [openHAB](http://www.openhab.org) is at the heart of Wikihouse controls, enabling all the devices to talk one another using the MQTT protocol. The open automation system exposes all the building devices using a RESTful API that offers immediate access and control using the language of the Internet.

The house electrical and control system schematic is shown below.

(https://raw.githubusercontent.com/00/wikihouse-controls/master/pictures/wikihouse_controls_schematic_2014-09-22.png "Wikihouse 4.0 Controls Schematic")

# DC Power and Data Network
## Power over Ethernet

# Wiring
## Cat 5E / Cat 6 wiring
## Termination boxes
## Connectors and sockets

# Lighting
## High colour rendering LEDs
## Pluggable lighting track connectors
## DMX
### Open Lighting Architecture

# Sensors
## Arduino Ethernet Boards and Shields
## Seeduino Grove Base Shield and Sensors
## DFRobot CO2 Sensor

# Ventilation
## OpenMVHR
## Adafruit Motor Shield V2.0

# Building automation
## Olimex Olinuxono A20 Micro
## Debian Linux
## openHAB
## nginx web server





