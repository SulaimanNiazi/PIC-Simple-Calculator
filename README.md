# PIC Simple Calculator

This project is a firmware application designed for the PIC16F877A microcontroller to function as a calculator. It displays the results on an LM016L LCD display. The firmware is developed using the MPLAB X IDE and the XC8 compiler.

<video title="PIC Simple Calculator Simulation video" width="100%" controls autoplay>
    <source src="./Simulation/PIC Simple Calculator Simulation video.mp4" type="video/mp4">
    Your browser does not support the video tag.
</video>

## Table of Contents

- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Apparatus](#apparatus)
- [Uploading to the Microcontroller](#uploading-to-the-microcontroller)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)

## Prerequisites

- MPLAB X IDE
- XC8 Compiler
- PIC16F877A Microcontroller

## Building the Project

1. Open the project in MPLAB X IDE.
2. Ensure the XC8 compiler is selected.
3. Build the project to generate the `.hex` or `.cof` file.
4. Alternatively, you can build the project using Visual Studio Code with the MPLAB extension. Set the project output file path, name, and extension using `Ctrl+Shift+P` and selecting "Edit Project Properties".

## Apparatus

Necessary components that can't be changed:

1. PIC16F877A microcontroller: To run the program.
1. LM016L LCD display: To display output.
1. Quartz Crystal and 2 1nF non-polarized capacitors.

Optional components depending on your circuit:

1. 16 Buttons 
1. 9 Resistors

## Uploading to the Microcontroller

After building the project, upload the generated `.hex` or `.cof` file to the PIC16F877A microcontroller using a suitable programmer. The file can be found in either of the following paths:

1. In case of using MPLAB X IDE: [dist\default\debug\PIC_Calculator.X.debug.cof](./dist/default/debug/PIC_Calculator.X.debug.cof)
2. In case of using Visual Studio Code (if the file name was set as default): [out\PIC_Simple_Calculator\default.hex](./out/PIC_Simple_Calculator/PIC_Calculator.hex)

## Usage

1. Connect the microcontroller and the necessary components as per the circuit diagram.
2. Power on the system.
3. The LCD will display the current input and results.
4. Use the buttons to input numbers and operations.

## Troubleshooting

- Ensure all connections are secure and correct.
- Verify the microcontroller is programmed with the correct `.hex` or `.cof` file.
- Check the power supply to the microcontroller and other components.
- If the LCD does not display correctly, check the connections and contrast settings.