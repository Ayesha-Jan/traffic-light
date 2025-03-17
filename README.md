# 🚦 ESP8266 Traffic Light Web Controller

This project creates a **web-based traffic light simulation** with a moving car animation, hosted directly on an **ESP8266 D1 Mini** using PlatformIO. The light controls are interactive and synced with actual **GPIO LEDs** (no resistors or breadboard needed).

## Features

- Interactive front-end with animated day/night background
- Moving car animation that reacts to the light changes
- Clickable red/yellow/green lights
- LED control via GPIO (using `/led/on` and `/led/off` routes)
- Entire app (HTML/CSS/JS/image) served from onboard LittleFS
- PlatformIO-based setup for modern, modular development

---

## Getting Started:

### Hardware Setup

- **Board:** Wemos D1 Mini (ESP8266)
- **LEDs:** Red, Yellow, Green (connected directly to pins)
- **Resistors:** None used in this setup

**GPIO Mapping:**

| Color  | GPIO | D1 Mini Label |
|--------|------|---------------|
| Red    | 13   | D7            |
| Yellow | 12   | D6            |
| Green  | 14   | D5            |

*Direct connection to GPIO pins without resistors is functional, but not electrically safe for all scenarios. Proceed with care.*

### Prerequisites

Before getting started, make sure you have the following installed:

- **PlatformIO** (for managing the project and dependencies)
- **LittleFS** (for serving files from the ESP8266)
- **ESP8266 Board Package** (from PlatformIO)

### Installation

1. **Clone the Repository**:

   First, clone this repository to your local machine:

   ```bash
   git clone https://github.com/your-username/Traffic-Light.git
   cd Traffic-Light

2. **Install Dependencies**:

   Install the necessary libraries by adding them to your platformio.ini file. The dependencies required for the project are:

   - ESP8266WiFi
   - ESP8266WebServer
   - LittleFS

3. **Upload Web Files to LittleFS**:

   Place your web files (index.html, style.css, script.js, car.png) in a folder named data in your project directory. To upload these files to the ESP8266's flash filesystem (LittleFS), run:
   
   ```bash
   pio run --target uploadfs

### Running the Project:

1. **Upload the Firmware**:

   Upload the firmware to the ESP8266 board with PlatformIO:

   ```bash
   pio run --target upload

2. **Monitor Serial Output**:

   After uploading, monitor the serial output to get the IP address of your ESP8266. Once the ESP8266 is connected to WiFi, you will see the IP address displayed in the serial monitor.

   ```bash
   pio device monitor

3. **Access the Web Interface**:

   Open a web browser and enter the IP address of the ESP8266. This will open the web interface where you can interact with the traffic light and car simulation.

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contact

For questions or feedback, please contact: [Ayesha.Jan@stud.srh-campus-berlin.de]

