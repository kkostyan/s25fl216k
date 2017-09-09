#include "s25fl216k.h"

void
S25FL216K_WriteEnable (S25FL216K *device)
{
  // Data output buffer.
  uint8_t buffer_out;
  
  // Fill data output buffer.
  buffer_out = S25FL216K_COMMAND_WRITE_ENABLE;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (&buffer_out, sizeof(buffer_out));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

void
S25FL216K_WriteDisable (S25FL216K *device)
{
  // Data output buffer.
  uint8_t buffer_out;
  
  // Fill data output buffer.
  buffer_out = S25FL216K_COMMAND_WRITE_DISABLE;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (&buffer_out, sizeof(buffer_out));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

S25FL216K_STATUS
S25FL216K_ReadStatus (S25FL216K *device)
{
  // Data output buffer.
  uint8_t buffer_out;
  // Device status register.
  S25FL216K_STATUS status;
  
  // Fill data output buffer.
  buffer_out = S25FL216K_COMMAND_READ_STATUS;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (&buffer_out, sizeof(buffer_out));
  // Read status register content.
  device->spi_read (&status.all, sizeof(status));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
  // Return status register content.
  return status;
}

void
S25FL216K_WriteStatus (S25FL216K *device, S25FL216K_STATUS status)
{
  // Data output buffer.
  uint8_t buffer_out[2];
  
  // Fill data output buffer.
  buffer_out[0] = S25FL216K_COMMAND_WRITE_STATUS;
  buffer_out[1] = status.all;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (buffer_out, sizeof(buffer_out));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

void
S25FL216K_ReadData (S25FL216K *device, uint32_t addr, uint8_t *data, uint8_t count)
{
  // Data output buffer.
  uint8_t buffer_out[4];
  
  // Fill data output buffer.
  buffer_out[0] = S25FL216K_COMMAND_READ_DATA;
  buffer_out[1] = (uint8_t)(addr >> 16);
  buffer_out[2] = (uint8_t)(addr >> 8);
  buffer_out[3] = (uint8_t)(addr);
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (buffer_out, sizeof(buffer_out));
  // Read data from device.
  device->spi_read (data, count);
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

void
S25FL216K_FastRead (S25FL216K *device, uint32_t addr, uint8_t *data, uint8_t count)
{
  // Data output buffer.
  uint8_t buffer_out[5];
  
  // Fill data output buffer.
  buffer_out[0] = S25FL216K_COMMAND_READ_DATA;
  buffer_out[1] = (uint8_t)(addr >> 16);
  buffer_out[2] = (uint8_t)(addr >> 8);
  buffer_out[3] = (uint8_t)(addr);
  buffer_out[4] = 0;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (buffer_out, sizeof(buffer_out));
  // Read data from device.
  device->spi_read (data, count);
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

void
S25FL216K_PageProgram (S25FL216K *device, uint32_t addr, uint8_t *data, uint8_t count)
{
  // Data output buffer.
  uint8_t buffer_out[4];
  
  // Fill data output buffer.
  buffer_out[0] = S25FL216K_COMMAND_PAGE_PROGRAM;
  buffer_out[1] = (uint8_t)(addr >> 16);
  buffer_out[2] = (uint8_t)(addr >> 8);
  buffer_out[3] = (uint8_t)(addr);
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (buffer_out, sizeof(buffer_out));
  // Write data to device.
  device->spi_write (data, count);
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

void
S25FL216K_SectorErase (S25FL216K *device, uint32_t addr)
{
  // Data output buffer.
  uint8_t buffer_out[4];
  
  // Fill data output buffer.
  buffer_out[0] = S25FL216K_COMMAND_SECTOR_ERASE;
  buffer_out[1] = (uint8_t)(addr >> 16);
  buffer_out[2] = (uint8_t)(addr >> 8);
  buffer_out[3] = (uint8_t)(addr);
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (buffer_out, sizeof(buffer_out));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

void
S25FL216K_BlockErase (S25FL216K *device, uint32_t addr)
{
  // Data output buffer.
  uint8_t buffer_out[4];
  
  // Fill data output buffer.
  buffer_out[0] = S25FL216K_COMMAND_BLOCK_ERASE;
  buffer_out[1] = (uint8_t)(addr >> 16);
  buffer_out[2] = (uint8_t)(addr >> 8);
  buffer_out[3] = (uint8_t)(addr);
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (buffer_out, sizeof(buffer_out));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

void
S25FL216K_ChipErase (S25FL216K *device)
{
  // Data output buffer.
  uint8_t buffer_out;
  
  // Fill data output buffer.
  buffer_out = S25FL216K_COMMAND_CHIP_ERASE;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (&buffer_out, sizeof(buffer_out));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
}

uint8_t
S25FL216K_DeviceID (S25FL216K *device)
{
  // Data output buffer.
  uint8_t buffer_out[4];
  // Data input buffer.
  uint8_t buffer_in[2];
  
  // Fill data buffer.
  buffer_out[0] = S25FL216K_COMMAND_DEVICE_ID;
  buffer_out[1] = 0;
  buffer_out[2] = 0;
  buffer_out[3] = 0;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (buffer_out, sizeof(buffer_out));
  // Read Manufacturer ID and Device ID.
  device->spi_read (buffer_in, sizeof(buffer_in));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
  // Return Device ID.
  return buffer_in[1];
}

uint16_t
S25FL216K_JEDECID (S25FL216K *device)
{
  // Data output buffer.
  uint8_t buffer_out;
  // Data input buffer.
  uint8_t buffer_in[3];
  
  // Fill data buffer.
  buffer_out = S25FL216K_COMMAND_JEDEC_ID;
  // Drive device CS low.
  device->spi_cs (S25FL216K_CS_LOW);
  // Write data output buffer to device.
  device->spi_write (&buffer_out, sizeof(buffer_out));
  // Read Manufacturer ID, Memory type and Capacity.
  device->spi_read (buffer_in, sizeof(buffer_in));
  // Drive device CS high.
  device->spi_cs (S25FL216K_CS_HIGH);
  // Return Memory type and capacity.
  return ((uint16_t)buffer_in[1] << 8) | buffer_in[2];
}
