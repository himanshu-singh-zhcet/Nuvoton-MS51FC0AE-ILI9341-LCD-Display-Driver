# Nuvoton-MS51FC0AE-ILI9341-LCD-Display-Driver

This repository contains code to interface the ILI9341 SPI-based 2.4" TFT LCD display with the Nuvoton MS51FC0AE microcontroller. The project demonstrates basic SPI communication, display initialization, and functions to render graphics and text on the screen.

## 📌 Features

- SPI communication with ILI9341 display
- TFT LCD initialization
- Drawing basic shapes (lines, rectangles, circles)
- Displaying text and numbers
- Static memory allocation (no `malloc`)
- Compatible with 8-bit 8051 architecture

## 🛠️ Hardware Used

- **Microcontroller**: Nuvoton MS51FC0AE
- **Display**: ILI9341 TFT LCD (SPI interface)
- **Crystal Frequency**: 24 MHz (external)
- **Power Supply**: 3.3V

## 🧰 Pin Configuration

| ILI9341 Pin | Description       | MS51FC0AE Pin |
|-------------|-------------------|----------------|
| VCC         | 3.3V Power        | 3.3V           |
| GND         | Ground            | GND            |
| CS          | Chip Select       | P1.0           |
| RESET       | Reset             | P1.1           |
| DC/RS       | Data/Command      | P1.2           |
| SDI/MOSI    | SPI MOSI          | P1.5           |
| SCK         | SPI Clock         | P1.7           |
| LED         | Backlight Power   | 3.3V (or GPIO) |

> **Note**: Adjust pins in the code as per your connection.

## 🔧 How It Works

1. Initializes the SPI module for 8-bit data transfer.
2. Sends ILI9341 initialization commands.
3. Provides functions to:
   - Fill screen with color
   - Draw pixels, lines, rectangles
   - Print characters and strings

## 📂 File Structure
├── src/ │ ├── main.c # Main application code │ ├── ili9341.c # Display driver source │ └── ili9341.h # Display driver header ├── README.md

