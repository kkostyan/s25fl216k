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
  S25FL216K_COMMAND_WRITE_ENABLE  = 0x06,
  S25FL216K_COMMAND_WRITE_DISABLE = 0x04,
  S25FL216K_COMMAND_READ_STATUS   = 0x05,
  S25FL216K_COMMAND_WRITE_STATUS  = 0x01,
  S25FL216K_COMMAND_READ_DATA     = 0x03,
  S25FL216K_COMMAND_FAST_READ     = 0x0B,
  S25FL216K_COMMAND_PAGE_PROGRAM  = 0x02,
  S25FL216K_COMMAND_BLOCK_ERASE   = 0xD8,
  S25FL216K_COMMAND_SECTOR_ERASE  = 0x20,
  S25FL216K_COMMAND_CHIP_ERASE    = 0xC7,
  S25FL216K_COMMAND_POWER_DOWN    = 0xB9,
  S25FL216K_COMMAND_RELEASE_PD    = 0xAB,
  S25FL216K_COMMAND_DEVICE_ID     = 0x90,
  S25FL216K_COMMAND_JEDEC_ID      = 0x9F,
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
} S25FL216K_STATUS_REGISTER;

/** S25FL216K structure.
  */
typedef struct
{
  /// Pointer to SPI write function.
  uint8_t (*spi_write) (uint8_t *buffer, uint8_t count);
  /// Pointer to SPI read function.
  uint8_t (*spi_read) (uint8_t *buffer, uint8_t count);
} S25FL216K;

/// Write enable.
void S25FL216K_WriteEnable (S25FL216K *device);
/// Write disable.
void S25FL216K_WriteDisable (S25FL216K *device);

#endif /* _S25FL216K_H_ */
