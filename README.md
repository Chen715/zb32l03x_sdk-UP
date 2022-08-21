# ZB32L03x_SDK

ZB32L03x_SDK

## Keil-C Configuration

+ Set 4 Spaces to replace Tab and UTF8 encoding
    > [Edit] -> [Configuration..]

    ![Keil-C_configuration](./Docs/image/keil_c_configuration.jpg)

+ Select `Target device`
    > + `CONFIG_USE_ZB32L030`


    - [Options for Target] -> [C/C++] -> [Define]
        > Add `CONFIG_USE_ZB32L030` or the other target device

        ![keil-c_CC++](./Docs/image/keil-c_CC++.jpg)

    - [Options for Target] -> [Asm] -> [Define]
        > Add `CONFIG_USE_ZB32L030` or the other target device

        ![keil-c_Asm](./Docs/image/keil-c_Asm.jpg)

+ Configure SRAM size
    > + ZB32L030  => `SRAM size = 0x2000`

    - [Options for Target] -> [Target] -> [IRAM1]

        ![keil-c_target](./Docs/image/keil_c_target.jpg)
