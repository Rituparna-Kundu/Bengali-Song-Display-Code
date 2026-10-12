# Bengali Song Display Code

An Arduino project that displays Bengali song lyrics/titles on a display screen.

## Features

- Displays Bengali text on a display module
- Supports multiple songs
- Easy to customize with your own songs
- Simple wiring and setup

## Hardware Required

| Component | Quantity |
|-----------|----------|
| Arduino board (Uno / Nano / ESP32) | 1 |
| Display (LCD / OLED / TFT) | 1 |
| Jumper wires | As needed |
| Breadboard | 1 |
| USB cable | 1 |

> Update this table to match the parts you actually used.

## Software Required

- [Arduino IDE](https://www.arduino.cc/en/software)
- Required libraries (install via **Sketch → Include Library → Manage Libraries**):
  - `Adafruit GFX` *(if using OLED/TFT)*
  - `Adafruit SSD1306` *(if using OLED)*
  - `LiquidCrystal` *(if using LCD)*

## Wiring

| Display Pin | Arduino Pin |
|-------------|-------------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

> Change the pins above to match your setup.

## How to Use

1. Clone this repository:
   ```bash
   git clone https://github.com/Rituparna-Kundu/Bengali-Song-Display-Code.git
   ```
2. Open the `.ino` file in the Arduino IDE.
3. Install the required libraries.
4. Select your board and port under **Tools**.
5. Click **Upload**.
6. The Bengali song text will appear on your display.

## Project Structure

```
Bengali-Song-Display-Code/
├── Bengali-Song-Display-Code.ino   # Main Arduino sketch
└── README.md                       # Project documentation
```

## Customization

To add your own songs, edit the song list in the code and upload it again.

## Troubleshooting

- **Blank screen?** Check your wiring and the display's I2C address.
- **Bengali characters not showing?** Make sure you are using a font or bitmap that supports Bengali characters.
- **Upload failed?** Check that the correct board and COM port are selected.

## Contributing

Suggestions and improvements are welcome. Fork the repo and open a pull request.

## Author

**Rituparna Kundu**
GitHub: [@Rituparna-Kundu](https://github.com/Rituparna-Kundu)

## License

This project is open source. Add a license file (for example MIT) if you want others to reuse it.
