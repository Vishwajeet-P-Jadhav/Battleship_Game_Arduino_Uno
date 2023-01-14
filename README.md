DESCRIPTION

This is the code for a Battleship game built on a circuit involving Arduino Uno, an LED Matrix and pushbuttons. 

Circuit components: 
       1. Arduino UNO
       2. 8x8 LED Matrix (with MAX7219 IC)
       3. Breadboard
       4. Pushbuttons
       5. M to M Jumper wires
       5. 22K ohms resistors

Circuit connections:
       1. LED Matrix pins
            - DIN pin connected to Arduino Uno digital pin 12
            - CS pin connected to Arduino Uno digital pin 11
            - CLK pin connected to Arduino Uno digital pin 10
        2. Pushbuttons
            - Pushbuttons need to be connected to pins supporting Interrupts.
            - Left_pushbutton is connected to pin 2 and Right_pushbutton is connected to pin 3

Game Description:
       The game involves a battleship located in the bottom row of the matrix. Bombs start falling vertically in a random column from the top of the led screen with a constant speed. The aim of the game is to avoid contact between bomb and the battleship. The battleship can be moved by using the two pushbuttons - one moves it towards the left while the other moves it towards the right.The score will be printed via Serial communication after every new bomb is sent. Once a bomb hits the battleship, the game ends and the score is saved on the arduino's EEPROM memory, if it is a new high score. On pressing the reset button of the Arduino board, the game starts all over again beginning with printing the previous highscore.

Code/Library specifications:
       I have used the <LedControl.h> library for controlling the led matrix via the MAX7219 IC and the <EEPROM.h> library to access the EEPROM memory of the arduino board. The EEPROM is used to save the value of high score. 