/** Cypress S25FL216K SPI flash control.
  */
#ifndef _S25FL216K_H_
#define _S25FL216K_H_

#include <stdint.h>

/** Total memory bytes.
  */
#define S25FL216K_SIZE (2097152)

/** Number of blocks.
  */
#define S25FL216K_BLOCKS (32)

/** Block size.
  */
#define S25FL216K_BLOCK_SIZE ((S25FL216K_SIZE) / (S25FL216K_BLOCKS))

/** Number of sectors.
  */
#define S25FL216K_SECTORS (512)

/** Sector size.
  */
#define S25FL216K_SECTOR_SIZE ((S25FL216K_SIZE) / (S25FL216K_SECTORS))

/** Number of pages.
  */
#define S25FL216K_PAGES (8192)

/** Page size.
  */
#define S25FL216K_PAGE_SIZE ((S25FL216K_SIZE) / (S25FL216K_PAGES))

/** Device ID.
  */
#define S25FL216K_DEVICE_ID (0x14)

/** JEDEC ID.
  */
#define S25FL216K_JEDEC_ID (0x4015)

/// S25FL216K block protection.
typedef enum
{
  S25FL216K_BLOCK_PROTECT_NONE  = 0,  ///< No blocks protected.
  S25FL216K_BLOCK_PROTECT_31    = 1,  ///< 1 block 31 protected.
  S25FL216K_BLOCK_PROTECT_30_31 = 2,  ///< 2 blocks 30 - 31 protected.
  S25FL216K_BLOCK_PROTECT_28_31 = 3,  ///< 4 blocks 28 - 31 protected.
  S25FL216K_BLOCK_PROTECT_24_31 = 4,  ///< 8 blocks 24 - 31 protected.
  S25FL216K_BLOCK_PROTECT_16_31 = 5,  ///< 16 blocks 16 - 31 protected.
  S25FL216K_BLOCK_PROTECT_0_15  = 10, ///< 16 blocks 0 - 15 protected.
  S25FL216K_BLOCK_PROTECT_0_23  = 11, ///< 24 blocks 0 - 23 protected.
  S25FL216K_BLOCK_PROTECT_0_27  = 12, ///< 28 blocks 0 - 27 protected.
  S25FL216K_BLOCK_PROTECT_0_29  = 13, ///< 30 blocks 0 - 29 protected.
  S25FL216K_BLOCK_PROTECT_0_30  = 14, ///< 31 blocks 0 - 30 protected.
  S25FL216K_BLOCK_PROTECT_ALL   = 15, ///< 32 (all) blocks protected.
} S25FL216K_BLOCK_PROTECT;

/// S25FL216K commands.
typedef enum
{
  S25FL216K_COMMAND_WRITE_ENABLE  = 0x06, ///< Write enable.
  S25FL216K_COMMAND_WRITE_DISABLE = 0x04, ///< Write disable.
  S25FL216K_COMMAND_READ_STATUS   = 0x05, ///< Read status register.
  S25FL216K_COMMAND_WRITE_STATUS  = 0x01, ///< Write status register.
  S25FL216K_COMMAND_READ_DATA     = 0x03, ///< Read data.
  S25FL216K_COMMAND_FAST_READ     = 0x0B, ///< Fast read data.
  S25FL216K_COMMAND_PAGE_PROGRAM  = 0x02, ///< Program page.
  S25FL216K_COMMAND_BLOCK_ERASE   = 0xD8, ///< Erase block (64 k).
  S25FL216K_COMMAND_SECTOR_ERASE  = 0x20, ///< Erase sector (4 k).
  S25FL216K_COMMAND_CHIP_ERASE    = 0xC7, ///< Erase full chip.
  S25FL216K_COMMAND_POWER_DOWN    = 0xB9, ///< Power down.
  S25FL216K_COMMAND_RELEASE_PD    = 0xAB, ///< Release power down.
  S25FL216K_COMMAND_DEVICE_ID     = 0x90, ///< Read device ID.
  S25FL216K_COMMAND_JEDEC_ID      = 0x9F, ///< Read device JEDEC ID.
} S25FL216K_COMMAND;

/** Status register structure.
  */
typedef union
{
  /// Access to individual bits.
  struct
  {
    uint8_t WIP:1; ///< Write in progress.
    uint8_t WEL:1; ///< Write enable latch.
    uint8_t BP :4; ///< Block protect.
    uint8_t    :1; ///< Reserved.
    uint8_t SRP:1; ///< Status register protect.
  } bit;
  /// Access to whole register.
  uint8_t all;
} S25FL216K_STATUS;

/// S25FL216K SPI CS signal states.
typedef enum
{
  S25FL216K_CS_LOW  = 0, ///< Drive SPI CS signal low.
  S25FL216K_CS_HIGH = 1, ///< Drive SPI CS signal high.
} S25FL216K_CS_STATE;

/** S25FL216K structure.
  */
typedef struct
{
  /// Pointer to SPI write function.
  uint8_t (*spi_write) (uint8_t *buffer, uint8_t count);
  /// Pointer to SPI read function.
  uint8_t (*spi_read) (uint8_t *buffer, uint8_t count);
  /// Pointer to SPI CS control function.
  void (*spi_cs) (S25FL216K_CS_STATE state);
} S25FL216K;

/** Write Enable.
    The Write Enable command sets the Write Enable Latch (WEL) bit in the
    Status Register to a 1, which enables the device to accept a Write Status,
    Page Program, Sector Erase, Block Erase or Chip Erase, commands.
    The WEL bit must be set prior to every Page Program, Sector Erase,
    Block Erase, Chip Erase, and Write Status commands.
  */
void S25FL216K_WriteEnable (S25FL216K *device);

/** Write Disable.
    The Write Disable command resets the Write Enable Latch (WEL) bit to a 0,
    which disables the device from accepting a Write Status, Page Program,
    Sector Erase, Block Erase or Chip Erase, commands.
    The WEL bit is automatically reset after Power-up and upon completion
    of the Write Status, Page Program, Sector Erase, Block Erase and
    Chip Erase commands.
  */
void S25FL216K_WriteDisable (S25FL216K *device);

/** Read Status.
    The Read Status command outputs the state of the Status Register bits.
    This command may be written at any time, even while a Page Program,
    Sector Erase, Block Erase or Chip Erase operation is in progress.
    The host system should check the Write In Progress (WIP) bit before
    sending a new command to the device if an operation is already in progress.
  */
S25FL216K_STATUS S25FL216K_ReadStatus (S25FL216K *device);

/** Write Status.
    The Write Status command allows the Status Register to be written.
    A Write Enable command must previously have been executed for the device
    to accept the Write Status command.
    Only non-volatile Status Register bits SRP and BP[3:0] can be written to.
    All other Status Register bit locations are read-only and will not
    be affected by the Write Status command.
  */
void S25FL216K_WriteStatus (S25FL216K *device, S25FL216K_STATUS status);

/** Read Data.
    The Read Data command allows up to 256 data bytes to be sequentially
    read from the memory. If a Read Data command is issued while a Page Program,
    Sector Erase, Block Erase or Chip Erase cycle is in process (WIP=1)
    the command is ignored.
  */
void S25FL216K_ReadData (S25FL216K *device, uint32_t addr, uint8_t *data, uint8_t count);

/** Fast Read.
    The Fast Read command is similar to the Read Data command except that
    it can operate at higher frequency than the traditional Read Data command.
  */
void S25FL216K_FastRead (S25FL216K *device, uint32_t addr, uint8_t *data, uint8_t count);

/** Page Program.
    The Page Program command allows up to 256 bytes of data to be programmed
    at previously erased to 0xFF memory locations. A Write Enable command
    must be executed before the device will accept the Page Program command.
    The Page Program command will not be executed if the addressed page is
    protected by the Block Protect BP[3:0] bits.
    If an entire 256 byte page is to be programmed, the last address byte
    should be set to 0. If the last address byte is not zero, and the number
    of bytes exceed the remaining page length, the addressing will wrap
    to the beginning of the page.
  */
void S25FL216K_PageProgram (S25FL216K *device, uint32_t addr, uint8_t *data, uint8_t count);

/** Sector Erase.
    The Sector Erase command sets all bytes in the addressed 4K sector to 0xFF.
    Before the Sector Erase command can be accepted by the device, 
    a Write Enable command must be issued.
    The Sector Erase command will not be executed if the addressed page
    is protected by the Block Protect BP[3:0] bits.
  */
void S25FL216K_SectorErase (S25FL216K *device, uint32_t addr);

/** Block Erase.
    The Block Erase command sets all bytes in the addressed 64K block to 0xFF.
    Before the Block Erase command can be accepted by the device,
    a Write Enable command must be issued.
    The Block Erase command will not be executed if the addressed page
    is protected by the Block Protect BP[3:0] bits.
  */
void S25FL216K_BlockErase (S25FL216K *device, uint32_t addr);

/** Chip Erase.
    The Chip Erase command sets all bytes to 0xFF inside the entire memory array.
    Before the Chip Erase command can be accepted by the device, a Write Enable
    command must be issued.
    The Chip Erase command will not be executed if any page is protected by the
    Block Protect BP[3:0] bits.
  */
void S25FL216K_ChipErase (S25FL216K *device);

/** Power Down.
    The Power Down command provides the lowest power consumption mode
    of the device. While in the power-down state only the Release Power Down
    command will be recognized. All other commands are ignored.
    The device rejects any Power Down command issued while it is executing
    a Page Program, Sector Erase, Block Erase or Chip Erase operation.
  */
void S25FL216K_PowerDown (S25FL216K *device);

/** Release Power Down.
    The Release Power Down command is used to release the device from the
    power-down state. If the Release Power Down command is issued while a
    Page Program, Sector Erase, Block Erase or Chip Erase operation is
    in process the command is ignored.
  */
void S25FL216K_ReleasePD (S25FL216K *device);

/** Read Device ID.
    The Read Device ID command is used to get device ID. The device ID returned
    by this function must be equal to S25FL216K_DEVICE_ID.
  */
uint8_t S25FL216K_DeviceID (S25FL216K *device);

/** Read JEDEC ID.
    The Read JEDEC ID command is used to get JEDEC ID from device.
    The JEDEC ID returned by this function must be equal to S25FL216K_JEDEC_ID.
  */
uint16_t S25FL216K_JEDECID (S25FL216K *device);

#endif /* _S25FL216K_H_ */
