# S25FL216K C library #

This library support Cypress S25FL216K SPI flash.
To use this library, include `s25fl216k.h` file to your project.

## Working with library ##

To work with this library you need to declare an instance of S25FL216K:

    S25FL216K s25fl216k_0;

Multiple instances can be declared.

Implement an `spi_write` and `spi_read` functions (example for STM32):

    SPI_HandleTypeDef hspi1;

    uint8_t spi_write (uint8_t *buffer, uint8_t count)
    {
      return HAL_SPI_Transmit(&hspi1, buffer, count, 1);
    }
    
    uint8_t spi_read (uint8_t *buffer, uint8_t count)
    {
      return HAL_SPI_Receive(&hspi1, buffer, count, 1);
    }

Set instance pointers to `spi_write` and `spi_read` functions:

    s25fl216k_0.spi_write = &spi_write;
    s25fl216k_0.spi_read = &spi_read;
