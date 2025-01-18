#include "typedefs.h"
#include "util.h"

namespace nemus::sysmmap {
constexpr range<Addr16> zero_page_range = range<Addr16>(
    0x0, 0x100, "Zero Page Address Range in the System Memory Map");

} // namespace nemus::sysmmap
