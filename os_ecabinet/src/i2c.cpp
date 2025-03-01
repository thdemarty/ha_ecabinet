#include "i2c.h"

bool i2c_check(uint8_t addr)
{
  m5gfx::i2c::beginTransaction(I2C_PORT, addr, 100000); 
  if (m5gfx::i2c::endTransaction(I2C_PORT).error() == 0)
  {
    return true;
  }
  else {
    return false;
  }
}