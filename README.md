# WT_ARM_MediaPlayer_Project

**Media Player Project (ARM CortexM4 (STM32F401xC))**

**Description**

The project is a media player (mp3 files). Using a python code, a playlist is converted and images are extracted to work on the following modules:

- R2R 8bit DAC (Audio Display)
- 128 x 160 TFT (Image Display)

Files are converted and transmitted to  stm32f401 through usb to ttl serial communication (UART). The user can control the media using 5 buttons:

- Play
- Pause
- Stop
- Next
- Previous

Data received in the micro-controller through UART are forwarded directly to a buffer using the DMA peripheral ensuring fast and responsive communication

**Drivers**

1) HAL
   1) DAC
   1) TFT

1) MCAL
   1) RCC
   1) GPIO
   1) SYSTICK
   1) NVIC
   1) EXTI
   1) DMA
   1) UART
   1) SPI


**Pins** 

|Pin No.|Direction|Mode||
| :-: | :-: | :-: | :-: |
|A0|---|---|---|
|A1|---|---|---|
|A2|Output|DAC Bit2|---|
|A3|Output|DAC Bit3|---|
|A4|Alt Function|SPI1 SS|---|
|A5|Alt Function|SPI1 SCK|---|
|A6|Alt Function|SPI1 MOSI|---|
|A7|Alt Function|SPI1 MISO|---|
|A8|---|---|---|
|A9|Alt Function|UART1 TX|---|
|A10|Alt Function|UART1 RX|---|
|A11|---|---|---|
|A12|---|---|---|
|B0|Output|DAC Bit0|---|
|B1|Output|DAC Bit1|---|
|B5|Output|DAC Bit5|---|
|B6|Output|DAC Bit6|---|
|B7|Output|DAC Bit7|---|
|B8|Output|DAC Bit8|---|
|B9|---|---|---|
|B10|Input|Button 10 (EXTI10)|---|
|B11|---|---|---|
|B12|Input|Button 12 (EXTI12)|---|
|B13|Input|Button 13 (EXTI13)|---|
|B14|Input|Button 14 (EXTI14)|---|
|B15|Input|Button 15 (EXTI15)|---|
|C13|---|---|---|
|C14|---|---|---|
|C15|---|---|---|

