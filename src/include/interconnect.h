#include "typedefs.h"
#include <cstdint>

namespace nemus::interconnect {

class InterConnect;

struct ICMessage {
  unsigned char m_data;
  uint8_t m_size;
  Addr16 m_addr;
  bool m_read;
};

class ICNode {
  InterConnect *m_interconnect;

public:
  bool send(ICMessage &msg) { return false; };
  virtual bool recieve(ICMessage &msg) = 0;
};

class InterConnect {};

}; // namespace nemus::interconnect
