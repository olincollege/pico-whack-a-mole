# Whack-a-Mole Game with raspi RGB Matrix

Ellen Sun, Swasti Jain, Meagan Lipsman

Have you ever wanted to play a fun handheld version of one of your favorite childhood games? Well you're in luck, because this project implementd a Whack-a-mole style game on a raspi pico RGB keypad display.

## How It Works

The game functions by randomly lighting up buttons one at a time for varying lengths of time. The user must press the button while it is lit to earn a point. If the user hits a button that is not lit then they loose and the game will end.

## Material

The following materials are needed to run the game:

- [Rasperry pi pico](https://shop.pimoroni.com/products/raspberry-pi-pico-2-w?variant=54852252991867)
- [Pico RGB Keypad Base](https://shop.pimoroni.com/products/pico-rgb-keypad-base?variant=32369517166675)
- USB to Micro USB-b cord
- Computer configured to run the C program
- Two 20x1 pin style (Male) Header Pins
- [LED Display Screen](https://www.amazon.com/dp/B0B76YGDV4?ref=cm_sw_r_cso_sms_apin_dp_PSMCENFZE8E7QDNYRK0P&ref_=cm_sw_r_cso_sms_apin_dp_PSMCENFZE8E7QDNYRK0P&social_share=cm_sw_r_cso_sms_apin_dp_PSMCENFZE8E7QDNYRK0P&titleSource=avft-a&previewDoh=1&th=1)
- Four Socket to socket (female to female) jumper cables

## Hardware Set Up

1. Acquire all of your hardware pieces.
2. Solder the header pins to the raspi pico with the shorter ends on the side with the bootsell button.
3. Insert the pico pins into the header pin holder already present on the RGB keypad board. Install the board with the bootsell button facing upwards so the button is easily accessible.
4. Use the socket to socket jumpers to attach the RBG keypad to the LED display. Connect the 1 pin on the LED display to the VBUS pin on the pico, connect the 2 pin on the LED display to a ground pin on the pico, connect the 3 pin on the LED display to the GP6 pin on the pico, and finally connect the 4 pin on the LED display to the GP 7 pin on the pico.
   ![alt text](image.png)

## Software Set up

1. Make sure that you have CMake set up so that you can build and run code.
2. Create a folder for the project named pico
3. In this folder clone _this_ repository using the

```
$ git clone
```

and copy and pasting the link given when clicking the green code button and selecting the SSH option ![alt text](image-1.png) ![alt text](image-2.png)

4. In the same folder clone the pico-sdk repository using the below command. This will allow us to build.

```
$ git clone -b master https://github.com/raspberrypi/pico-sdk.git
```

5. Set the PICO_SDK_PATH environment variable to where you just cloned the repo by making a .txt file called pico_sdk_path.txt containing the path to your pico-sdk folder.

6. Go into the pico-sdk folder using:

```
$ cd pico-sdk
```

7. run the command:

```
$ git submodule update --init
```

8. You will also need the rgb_keybad library which has been included as a part of this repository for your convenience

## Building/Uploading Code

To build code go into your build folder using:

```
$ cd build/
```

Next run CMake to compile and build the executable using the following commands:

```
$ cmake ..
$ make
```

To upload code, start by pressing the bootsell button and holding it down while you plug the USB into your computer. You should see a pico pop up, click on it to open the pico file. Next, find the .uf2 file located in **\*\***\_\_**\*\***. This file is created when you build your code. Drag and drop this file into the pico file. You will need to do this everytime to rebuild/flash new code.
