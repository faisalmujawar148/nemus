
#include "typedefs.h"
#include <string_view>
#include <type_traits>
namespace nemus {
/** Templated class which represents a range. */
template <typename Type, typename = std::enable_if_t<std::is_integral_v<Type>>>
struct range {
  range(Type start, Type end, std::string_view desc)
      : m_start(start), m_end(end), m_desc(desc){};
  range(Type start, Type end) : m_start(start), m_end(end), m_desc(""){};

  /** Start of the range. */
  const Type m_start;
  /** End of the range. */
  const Type m_end;
  /** Description of the range. */
  const std::string_view m_desc;
  /**
   * Function which checks whether an input is contained
   * in the range or not.
   */
  bool contains(Type arg) { return arg >= m_start && arg < m_end; }
};

}; // namespace nemus
