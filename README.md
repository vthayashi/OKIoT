# OKIoT Open Knowledge Internet of Things

Check out our previous projects on [Wiki](https://github.com/vthayashi/OKIoT/wiki)!

Check out the full [step-by-step guide (pt-BR)](https://github.com/vthayashi/OKIoT/blob/master/Manual%20Kit%20Acelerador%20IoT%20Hedwig.pdf)!

<img src="https://github.com/vthayashi/OKIoT/blob/master/img/smarthomeareas.PNG" alt="Smart Home major interest areas" width="300"/>

In the context of Internet of Things (IoT - Internet of Things), more and more devices are connected to each other and to the Internet, so that their integrated journeys can deliver value to people, making devices and environments more intelligent.

The dematerialization of the mobile application, integration with natural language interfaces and data collection for personalization of services are some examples of what the IoT can offer.
However, for these value proposals to be made tangible, some challenges must be overcome:

* Complexity: how to integrate so many interfaces, services and devices?
* How to tolerate connection failures, to maintain a service level compatible with the current solution?
* How to deal with physical power, bandwidth and processing limitations?
* How to speed up the development of control and monitoring of power modules, for software developers?

To address these challenges, the Hedwig accelerator kit was developed, as a way to accelerate development by encapsulating aspects of communication infrastructure obtained from the Hedwig¹ Project, from USP's Polytechnic School.

As differentials, we focus on dematerialization (integration with voice interface and other external applications) and non-functional requirements (tolerance to communication failures and usability).
integration with power module (up to 3A), with serial protocol for integration with Arduino Nano, integrated with cloud and local APIs to accelerate application development. The module is ideal for transforming Arduino projects into IoT projects, and its use in conjunction with a project-oriented learning method is recommended.

## Getting Started

### Prerequisites

For an standard deploy, you must have an ESP8266 (Expressif IoT), an Arduino Nano, 2 USB cables (for uploading the firmware on each module) and two wires to setup the serial communication between both modules.

Adding libraries on Arduino IDE, firmware upload for Arduino Nano and ESP8266 through Arduino IDE are required.


### Installing

Wire ESP8266 (communication module) and Arduino Nano (application logic module) as described on [step-by-step guide (pt-BR)](https://github.com/vthayashi/OKIoT/blob/master/Manual%20Kit%20Acelerador%20IoT%20Hedwig.pdf).

Upload the [accelerator firmware binary](https://github.com/vthayashi/OKIoT/blob/master/Resp_190811d.ino.d1_mini.bin) into ESP8266 through Arduino IDE to use it as a black box with Access Pòint, webserver, firmware over-the-air and log functionalities built-in.

Upload the [Arduino Nano firmware](https://github.com/vthayashi/OKIoT/tree/master/Nano_190630d) through Arduino IDE. Remember to keep both files within the same folder.

## Running the tests

Explain how to run the automated tests for this system

## Built With

* [Blynk](https://github.com/blynkkk/blynk-library) - The cloud IoT used (free version)

## Contributing

Please contact the [author](https://www.linkedin.com/in/victor-hayashi-885083131/) for contributing with this work at the early stage of the project.

## Authors

* **Victor Hayashi** - *Initial work* - [vthayashi](https://github.com/vthayashi)

* **Fabio Hayashi** - *Initial work* - [fabio hayashi](https://www.linkedin.com/in/fabio-hayashi-bab61914/)


## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Professor Reginaldo Arakaki, Computer Engineering at USP University of São Paulo, Brazil
