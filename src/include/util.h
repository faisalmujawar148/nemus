
#include <string_view>
#include <type_traits>
namespace nemus {

constexpr unsigned long long operator"" _kb(unsigned long long kb) {
  return kb * 1024;
}

constexpr unsigned long long operator"" _mb(unsigned long long mb) {
  return mb * 1024_kb;
}

/** Templated class which represents a range. */
template <typename Type, typename = std::enable_if_t<std::is_integral_v<Type>>>
struct range {
  constexpr range(Type start, std::size_t size, std::string_view desc)
      : m_start(start), m_end(start + size), m_size(size), m_desc(desc){};
  constexpr range(Type start, std::size_t size)
      : m_start(start), m_end(start + size), m_size(size), m_desc(""){};

  /** Start of the range. */
  const Type m_start;
  /** End of the range. */
  const Type m_end;
  /** Size of the range. */
  const std::size_t m_size;
  /** Description of the range. */
  const std::string_view m_desc;
  /**
   * Function which checks whether an input is contained
   * in the range or not.
   */
  bool contains(Type arg) { return arg >= m_start && arg < m_end; }
};

}; // namespace nemus
