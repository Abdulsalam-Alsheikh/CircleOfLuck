# Random Number Selector with 12 Segments

This project is an electronic circuit that randomly selects a winner from 12 participants by lighting up the corresponding segment on a circular board. The circuit is built using an Arduino Nano, shift registers, MOSFET transistors, and other components. The design includes a PCB layout, simulation in Proteus, and Arduino code for the logic control.

## Components

- **Arduino Nano**: Controls the entire circuit.
- **2 x 74HC595 Shift Registers**: Expands the number of outputs to control the 12 segments.
- **12 x IRLZ44N MOSFET Transistors**: Used to switch the LEDs for each segment.
- **Resistors**: Various values to limit current and ensure proper operation of the circuit.
- **Power Supply Jack**: To feed the circuit with the required voltage.
- **Junction Connectors**: For connecting each segment to its corresponding transistor.

## Project Files

- **Proteus Simulation File**: A simulation of the circuit to test the functionality before actual implementation.
- **Arduino Code**: The code used to control the selection process and light up the segments.
- **PCB Design**: A layout of the PCB ready for manufacturing, including all the components and connections.

## Circuit Design

The circuit is designed to randomly select a number from 1 to 12 using an LED on a circular board. The selection is controlled by an Arduino Nano, which sends signals to the shift registers. The shift registers then control the MOSFET transistors, which switch the LEDs on and off based on the random selection.

### How It Works

1. The Arduino generates a random number between 1 and 12.
2. The shift registers receive the number and activate the corresponding MOSFET.
3. The MOSFET then allows current to pass through and lights up the LED corresponding to the selected number.
4. The number remains lit until the process is repeated.

## Usage

1. Load the provided Arduino code into the Arduino Nano.
2. Connect the circuit components as per the schematic in the Proteus file or PCB design.
3. Power the circuit through the power supply jack.
4. The circuit will randomly select a number and light up the corresponding segment.

Watch the project on [youtube](https://youtu.be/4vKIFw7FxGo) .
![٢٠٢٢١١٢١_٠١٠٨٥٥](https://github.com/user-attachments/assets/20ba46a0-cc94-4d3f-a095-497c375b07b8)
![٢٠٢٢١١١٧_٢٠١٩٢٢](https://github.com/user-attachments/assets/c610e9c0-b2b2-489e-a0d6-13e771b03f9d)


