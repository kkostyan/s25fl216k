# S25FL216K C library #

This library support Cypress S25FL216K SPI flash.
To use this library, include `s25fl216k.h` file to your project.

## Working with library ##

To work with this library you need to declare an instance of S25FL216K:

    S25FL216K s25fl216k_0;

Multiple instances can be declared.

Implement an `spi_write`, `spi_read` and `spi_cs` functions (example for STM32):

    SPI_HandleTypeDef hspi1;

    uint8_t spi_write (uint8_t *buffer, uint8_t count)
    {
      return HAL_SPI_Transmit(&hspi1, buffer, count, 1);
    }
    
    uint8_t spi_read (uint8_t *buffer, uint8_t count)
    {
      return HAL_SPI_Receive(&hspi1, buffer, count, 1);
    }
    
    void spi_cs (S25FL216K_CS_STATE state)
    {
      switch (state)
      {
        case S25FL216K_CS_LOW:
          HAL_GPIO_WritePin (S25FL216K_CS_GPIO_Port, S25FL216K_CS_Pin, GPIO_PIN_RESET);
          break;
        case S25FL216K_CS_HIGH:
          HAL_GPIO_WritePin (S25FL216K_CS_GPIO_Port, S25FL216K_CS_Pin, GPIO_PIN_SET);
          break;
      }
    }

Set instance pointers to `spi_write`, `spi_read` and `spi_cs` functions:

    s25fl216k_0.spi_write = &spi_write;
    s25fl216k_0.spi_read = &spi_read;
    s25fl216k_0.spi_cs = &spi_cs;
