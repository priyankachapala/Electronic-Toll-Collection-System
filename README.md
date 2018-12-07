# Electronic Toll Collection System

An Automated Toll collection system using ATMEL 8051 Microcontroller and RFID. Each user will be given an RFID tag . Whenever the car passes through the RFID reader toll will be deduced immediately without any manual operation and the gates will be opened.

Components Recquired<br />
1.AT89S52 microcontroller<br />
2.Crystal oscillator<br />
3.16X2 char LCD<br />
4.Servo motor<br />
5.RFID reader & tags<br />
6.Capacitors – 22pF<br />
7.Resistors<br />

WORKING:<br />
 
  The RFID tag issued to the user contains digital code. Microcontroller reads the RFID card number from the RFID reader and then sends this data to LCD which aids the person to read the balance of the card. Micontroller then decides to open the gate based on the balance in the RFID tag. Tags with insuffient balance are considered invalid and informed to pay the balance manually.
  
  Complete theory about various components used can be found in the Theory file

