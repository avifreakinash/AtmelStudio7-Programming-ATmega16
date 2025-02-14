###  Atmel Studio7 - Programming the ATmega16  Microcontroller
🚀 A collection of AVR  Source code for **ATmega16**, developed using **Atmel Studio 7**.  

---

#### 📌 Project Overview  
This repository contains **embedded C programs** for the **ATmega16 microcontroller**, demonstrating fundamental (as of now) and advanced concepts, including:  

	- LED Blinking  
	- Adding Button to Microcontroller  
	- Button Debouncing through Software
	- The Button Game
	- ... 
#### 📂 Folder Structure  
	AtmelStudio7-Programming-ATmega16/ 
	│── src/           # Source code (.c and .h files) 
	│── .gitignore     # Ignore unnecessary files (build files, binaries, etc.) 
	│── README.md      # Project documentation 
	│── LICENSE        # License information

#### ⚡ Getting Started
	1️⃣ Requirements
```
📌 Hardware:
					ATmega16 Microcontroller
					AVR Programmer (USBasp, AVRISP mkII, etc.)
					LEDs, Buttons, and Sensors 
📌 Software:
					Atmel Studio 7 (Download: Microchip)
					AVRDUDE (for flashing HEX files)
					Git (for version control)
```

	2️⃣ How to Build & Flash
```
🔹 Build the Project
				Open Atmel Studio 7
				Load the main.c file
				Click Build → Build Solution (F7)

🔹 Flash the HEX File

	📌 Using AVRDUDE:
				avrdude -c usbasp -p m16 -U flash:w:hex/main.hex:i

	📌 Using configurable Tools in AtmelStudio7 for External Programmer (USBasp):

				How to Configure -

				Navigate to Tools → Extended Tools :
				Title		:	USBasp Release
				Path		:	C:\avrdude-6.3-mingw32\avrdude.exe ( path to the dir where avrdude is installed)
				Arguments	:	-c USBasp -p m16 -U flash:w:$(ProjectDir)\Release\$(TargetName).hex:i

```
> To flash the program, go to Tools and click **USBasp Release**. The flashing should start. This will upload the program to ATmega16 using the USBasp programmer.
