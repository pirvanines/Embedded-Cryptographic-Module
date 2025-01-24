# Hardware cybersecurity project

## Description

The purpose of this project is to sign a block of data, to encrypt and decrypt it, and to verify its signature using RSA *(before and after modifying the data)* using the following hardware and software components:

* [OPTIGA Trust M Click](https://www.mikroe.com/trust-m-click) security chip which communicates with [STM32F407ZGT6](https://www.st.com/en/microcontrollers-microprocessors/stm32f407-417.html) microcontroller on [Micro Fusion](https://www.mikroe.com/fusion-for-arm) for ARM board, through [I2C](https://github.com/Infineon/optiga-trust-m/blob/develop/documents/Infineon_I2C_Protocol_v2.03.pdf) protocol
* [J-Link](https://www.segger.com/products/debug-probes/j-link/) debugger
* [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html), an integrated development environment for STM32