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
