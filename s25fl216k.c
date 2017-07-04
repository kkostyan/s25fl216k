#include "s25fl216k.h"

void
S25FL216K_WriteEnable (S25FL216K *device)
{
  // Data buffer.
  uint8_t buffer;
  
  // Fill data buffer.
  buffer = S25FL216K_COMMAND_WRITE_ENABLE;
  // Write data buffer to device.
  device->spi_write (&buffer, 1);
}

void
S25FL216K_WriteDisable (S25FL216K *device)
{
  // Data buffer.
  uint8_t buffer;
  
  // Fill data buffer.
  buffer = S25FL216K_COMMAND_WRITE_DISABLE;
  // Write data buffer to device.
  device->spi_write (&buffer, 1);
}

uint8_t
S25FL216K_ReadStatus (S25FL216K *device)
{
  // Data buffer.
  uint8_t buffer;
  
  // Fill data buffer.
  buffer = S25FL216K_COMMAND_READ_STATUS;
  // Write data buffer to device.
  device->spi_write (&buffer, 1);
  // Read status register content.
  device->spi_read (&buffer, 1);
  // Return status register content.
  return buffer;
}

void
S25FL216K_WriteStatus (S25FL216K *device, uint8_t status)
{
  // Data buffer.
  uint8_t buffer[2];
  
  // Fill data buffer.
  buffer[0] = S25FL216K_COMMAND_WRITE_STATUS;
  buffer[1] = status;
  // Write data buffer to device.
  device->spi_write (buffer, 2);
}
