//===--------------------------- filesystem -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE-libc++.txt for details.
//
//===----------------------------------------------------------------------===//

#if __has_include(<filesystem>)
#include <filesystem>
#elif HAVE(STD_EXPERIMENTAL_FILESYSTEM)
#include <experimental/filesystem>
namespace std {
namespace filesystem = std::experimental::filesystem;
}
#else

/* Imports a copy of <filesystem> from r343838 of the libc++ project. This
   is only needed until macOS 10.14 is no longer supported at which point all
   ports will support <filesystem> directly.
*/


#ifndef _LIBCPP_FILESYSTEM
#define _LIBCPP_FILESYSTEM
/*
    filesystem synopsis

    namespace std { namespace filesystem {

    class path;

    void swap(path& lhs, path& rhs) noexcept;
    size_t hash_value(const path& p) noexcept;

    bool operator==(const path& lhs, const path& rhs) noexcept;
    bool operator!=(const path& lhs, const path& rhs) noexcept;
    bool operator< (const path& lhs, const path& rhs) noexcept;
    bool operator<=(const path& lhs, const path& rhs) noexcept;
    bool operator> (const path& lhs, const path& rhs) noexcept;
    bool operator>=(const path& lhs, const path& rhs) noexcept;

    path operator/ (const path& lhs, const path& rhs);

    // fs.path.io operators are friends of path.
    template <class charT, class traits>
    friend basic_ostream<charT, traits>&
    operator<<(basic_ostream<charT, traits>& os, const path& p);

    template <class charT, class traits>
    friend basic_istream<charT, traits>&
    operator>>(basic_istream<charT, traits>& is, path& p);

    template <class Source>
      path u8path(const Source& source);
    template <class InputIterator>
      path u8path(InputIterator first, InputIterator last);

    class filesystem_error;
    class directory_entry;

    class directory_iterator;

    // enable directory_iterator range-based for statements
    directory_iterator begin(directory_iterator iter) noexcept;
    directory_iterator end(const directory_iterator&) noexcept;

    class recursive_directory_iterator;

    // enable recursive_directory_iterator range-based for statements
    recursive_directory_iterator begin(recursive_directory_iterator iter) noexcept;
    recursive_directory_iterator end(const recursive_directory_iterator&) noexcept;

    class file_status;

    struct space_info
    {
      uintmax_t capacity;
      uintmax_t free;
      uintmax_t available;
    };

    enum class file_type;
    enum class perms;
    enum class perm_options;
    enum class copy_options;
    enum class directory_options;

    typedef chrono::time_point<trivial-clock>  file_time_type;

    // operational functions

    path absolute(const path& p);
    path absolute(const path& p, error_code &ec);

    path canonical(const path& p);
    path canonical(const path& p, error_code& ec);

    void copy(const path& from, const path& to);
    void copy(const path& from, const path& to, error_code& ec);
    void copy(const path& from, const path& to, copy_options options);
    void copy(const path& from, const path& to, copy_options options,
                   error_code& ec);

    bool copy_file(const path& from, const path& to);
    bool copy_file(const path& from, const path& to, error_code& ec);
    bool copy_file(const path& from, const path& to, copy_options option);
    bool copy_file(const path& from, const path& to, copy_options option,
                           error_code& ec);

    void copy_symlink(const path& existing_symlink, const path& new_symlink);
    void copy_symlink(const path& existing_symlink, const path& new_symlink,
                              error_code& ec) noexcept;

    bool create_directories(const path& p);
    bool create_directories(const path& p, error_code& ec);

    bool create_directory(const path& p);
    bool create_directory(const path& p, error_code& ec) noexcept;

    bool create_directory(const path& p, const path& attributes);
    bool create_directory(const path& p, const path& attributes,
                                  error_code& ec) noexcept;

    void create_directory_symlink(const path& to, const path& new_symlink);
    void create_directory_symlink(const path& to, const path& new_symlink,
                                          error_code& ec) noexcept;

    void create_hard_link(const path& to, const path& new_hard_link);
    void create_hard_link(const path& to, const path& new_hard_link,
                                  error_code& ec) noexcept;

    void create_symlink(const path& to, const path& new_symlink);
    void create_symlink(const path& to, const path& new_symlink,
                                error_code& ec) noexcept;

    path current_path();
    path current_path(error_code& ec);
    void current_path(const path& p);
    void current_path(const path& p, error_code& ec) noexcept;

    bool exists(file_status s) noexcept;
    bool exists(const path& p);
    bool exists(const path& p, error_code& ec) noexcept;

    bool equivalent(const path& p1, const path& p2);
    bool equivalent(const path& p1, const path& p2, error_code& ec) noexcept;

    uintmax_t    file_size(const path& p);
    uintmax_t    file_size(const path& p, error_code& ec) noexcept;

    uintmax_t    hard_link_count(const path& p);
    uintmax_t    hard_link_count(const path& p, error_code& ec) noexcept;

    bool is_block_file(file_status s) noexcept;
    bool is_block_file(const path& p);
    bool is_block_file(const path& p, error_code& ec) noexcept;

    bool is_character_file(file_status s) noexcept;
    bool is_character_file(const path& p);
    bool is_character_file(const path& p, error_code& ec) noexcept;

    bool is_directory(file_status s) noexcept;
    bool is_directory(const path& p);
    bool is_directory(const path& p, error_code& ec) noexcept;

    bool is_empty(const path& p);
    bool is_empty(const path& p, error_code& ec) noexcept;

    bool is_fifo(file_status s) noexcept;
    bool is_fifo(const path& p);
    bool is_fifo(const path& p, error_code& ec) noexcept;

    bool is_other(file_status s) noexcept;
    bool is_other(const path& p);
    bool is_other(const path& p, error_code& ec) noexcept;

    bool is_regular_file(file_status s) noexcept;
    bool is_regular_file(const path& p);
    bool is_regular_file(const path& p, error_code& ec) noexcept;

    bool is_socket(file_status s) noexcept;
    bool is_socket(const path& p);
    bool is_socket(const path& p, error_code& ec) noexcept;

    bool is_symlink(file_status s) noexcept;
    bool is_symlink(const path& p);
    bool is_symlink(const path& p, error_code& ec) noexcept;

    file_time_type  last_write_time(const path& p);
    file_time_type  last_write_time(const path& p, error_code& ec) noexcept;
    void last_write_time(const path& p, file_time_type new_time);
    void last_write_time(const path& p, file_time_type new_time,
                                 error_code& ec) noexcept;

    void permissions(const path& p, perms prms,
                     perm_options opts=perm_options::replace);
    void permissions(const path& p, perms prms, error_code& ec) noexcept;
    void permissions(const path& p, perms prms, perm_options opts,
                     error_code& ec);

    path proximate(const path& p, error_code& ec);
    path proximate(const path& p, const path& base = current_path());
    path proximate(const path& p, const path& base, error_code &ec);

    path read_symlink(const path& p);
    path read_symlink(const path& p, error_code& ec);

    path relative(const path& p, error_code& ec);
    path relative(const path& p, const path& base=current_path());
    path relative(const path& p, const path& base, error_code& ec);

    bool remove(const path& p);
    bool remove(const path& p, error_code& ec) noexcept;

    uintmax_t    remove_all(const path& p);
    uintmax_t    remove_all(const path& p, error_code& ec);

    void rename(const path& from, const path& to);
    void rename(const path& from, const path& to, error_code& ec) noexcept;

    void resize_file(const path& p, uintmax_t size);
    void resize_file(const path& p, uintmax_t size, error_code& ec) noexcept;

    space_info   space(const path& p);
    space_info   space(const path& p, error_code& ec) noexcept;

    file_status  status(const path& p);
    file_status  status(const path& p, error_code& ec) noexcept;

    bool status_known(file_status s) noexcept;

    file_status  symlink_status(const path& p);
    file_status  symlink_status(const path& p, error_code& ec) noexcept;

    path temp_directory_path();
    path temp_directory_path(error_code& ec);

    path weakly_canonical(path const& p);
    path weakly_canonical(path const& p, error_code& ec);


} }  // namespaces std::filesystem

*/

#include <__config>
#include <cstddef>
#include <cstdlib>
#include <chrono>
#include <iterator>
#include <iosfwd>
#include <locale>
#include <memory>
#include <stack>
#include <string>
#include <system_error>
#include <utility>
#include <iomanip> // for quoted
#include <string_view>
/* #include <version> */

#include <__debug>

#if _LIBCPP_STD_VER >= 17
#define _LIBCPP_BEGIN_NAMESPACE_FILESYSTEM \
  _LIBCPP_BEGIN_NAMESPACE_STD inline namespace __fs { namespace filesystem {
#else
#define _LIBCPP_BEGIN_NAMESPACE_FILESYSTEM \
  _LIBCPP_BEGIN_NAMESPACE_STD namespace __fs { namespace filesystem {
#endif

#define _LIBCPP_END_NAMESPACE_FILESYSTEM \
  _LIBCPP_END_NAMESPACE_STD } }

#define _VSTD_FS _VSTD::__fs::filesystem

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include <__undef_macros>

#ifndef _LIBCPP_CXX03_LANG

_LIBCPP_BEGIN_NAMESPACE_FILESYSTEM

struct _FilesystemClock {
#if !defined(_LIBCPP_HAS_NO_INT128)
  typedef __int128_t rep;
  typedef nano period;
#else
  typedef long long rep;
  typedef nano period;
#endif

  typedef chrono::duration<rep, period> duration;
  typedef chrono::time_point<_FilesystemClock> time_point;

  static _LIBCPP_CONSTEXPR_AFTER_CXX11 const bool is_steady = false;

  _LIBCPP_FUNC_VIS static time_point now() noexcept;

  _LIBCPP_INLINE_VISIBILITY
  static time_t to_time_t(const time_point& __t) noexcept {
    typedef chrono::duration<rep> __secs;
    return time_t(
        chrono::duration_cast<__secs>(__t.time_since_epoch()).count());
  }

  _LIBCPP_INLINE_VISIBILITY
  static time_point from_time_t(time_t __t) noexcept {
    typedef chrono::duration<rep> __secs;
    return time_point(__secs(__t));
  }
};

typedef chrono::time_point<_FilesystemClock> file_time_type;

struct _LIBCPP_TYPE_VIS space_info {
  uintmax_t capacity;
  uintmax_t free;
  uintmax_t available;
};

enum class _LIBCPP_ENUM_VIS file_type : signed char {
  none = 0,
  not_found = -1,
  regular = 1,
  directory = 2,
  symlink = 3,
  block = 4,
  character = 5,
  fifo = 6,
  socket = 7,
  unknown = 8
};

enum class _LIBCPP_ENUM_VIS perms : unsigned {
  none = 0,

  owner_read = 0400,
  owner_write = 0200,
  owner_exec = 0100,
  owner_all = 0700,

  group_read = 040,
  group_write = 020,
  group_exec = 010,
  group_all = 070,

  others_read = 04,
  others_write = 02,
  others_exec = 01,
  others_all = 07,

  all = 0777,

  set_uid = 04000,
  set_gid = 02000,
  sticky_bit = 01000,
  mask = 07777,
  unknown = 0xFFFF,
};

_LIBCPP_INLINE_VISIBILITY
inline constexpr perms operator&(perms _LHS, perms _RHS) {
  return static_cast<perms>(static_cast<unsigned>(_LHS) &
                            static_cast<unsigned>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr perms operator|(perms _LHS, perms _RHS) {
  return static_cast<perms>(static_cast<unsigned>(_LHS) |
                            static_cast<unsigned>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr perms operator^(perms _LHS, perms _RHS) {
  return static_cast<perms>(static_cast<unsigned>(_LHS) ^
                            static_cast<unsigned>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr perms operator~(perms _LHS) {
  return static_cast<perms>(~static_cast<unsigned>(_LHS));
}

_LIBCPP_INLINE_VISIBILITY
inline perms& operator&=(perms& _LHS, perms _RHS) { return _LHS = _LHS & _RHS; }

_LIBCPP_INLINE_VISIBILITY
inline perms& operator|=(perms& _LHS, perms _RHS) { return _LHS = _LHS | _RHS; }

_LIBCPP_INLINE_VISIBILITY
inline perms& operator^=(perms& _LHS, perms _RHS) { return _LHS = _LHS ^ _RHS; }

enum class _LIBCPP_ENUM_VIS perm_options : unsigned char {
  replace = 1,
  add = 2,
  remove = 4,
  nofollow = 8
};

_LIBCPP_INLINE_VISIBILITY
inline constexpr perm_options operator&(perm_options _LHS, perm_options _RHS) {
  return static_cast<perm_options>(static_cast<unsigned>(_LHS) &
                                   static_cast<unsigned>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr perm_options operator|(perm_options _LHS, perm_options _RHS) {
  return static_cast<perm_options>(static_cast<unsigned>(_LHS) |
                                   static_cast<unsigned>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr perm_options operator^(perm_options _LHS, perm_options _RHS) {
  return static_cast<perm_options>(static_cast<unsigned>(_LHS) ^
                                   static_cast<unsigned>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr perm_options operator~(perm_options _LHS) {
  return static_cast<perm_options>(~static_cast<unsigned>(_LHS));
}

_LIBCPP_INLINE_VISIBILITY
inline perm_options& operator&=(perm_options& _LHS, perm_options _RHS) {
  return _LHS = _LHS & _RHS;
}

_LIBCPP_INLINE_VISIBILITY
inline perm_options& operator|=(perm_options& _LHS, perm_options _RHS) {
  return _LHS = _LHS | _RHS;
}

_LIBCPP_INLINE_VISIBILITY
inline perm_options& operator^=(perm_options& _LHS, perm_options _RHS) {
  return _LHS = _LHS ^ _RHS;
}

enum class _LIBCPP_ENUM_VIS copy_options : unsigned short {
  none = 0,
  skip_existing = 1,
  overwrite_existing = 2,
  update_existing = 4,
  recursive = 8,
  copy_symlinks = 16,
  skip_symlinks = 32,
  directories_only = 64,
  create_symlinks = 128,
  create_hard_links = 256,
  __in_recursive_copy = 512,
};

_LIBCPP_INLINE_VISIBILITY
inline constexpr copy_options operator&(copy_options _LHS, copy_options _RHS) {
  return static_cast<copy_options>(static_cast<unsigned short>(_LHS) &
                                   static_cast<unsigned short>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr copy_options operator|(copy_options _LHS, copy_options _RHS) {
  return static_cast<copy_options>(static_cast<unsigned short>(_LHS) |
                                   static_cast<unsigned short>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr copy_options operator^(copy_options _LHS, copy_options _RHS) {
  return static_cast<copy_options>(static_cast<unsigned short>(_LHS) ^
                                   static_cast<unsigned short>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr copy_options operator~(copy_options _LHS) {
  return static_cast<copy_options>(~static_cast<unsigned short>(_LHS));
}

_LIBCPP_INLINE_VISIBILITY
inline copy_options& operator&=(copy_options& _LHS, copy_options _RHS) {
  return _LHS = _LHS & _RHS;
}

_LIBCPP_INLINE_VISIBILITY
inline copy_options& operator|=(copy_options& _LHS, copy_options _RHS) {
  return _LHS = _LHS | _RHS;
}

_LIBCPP_INLINE_VISIBILITY
inline copy_options& operator^=(copy_options& _LHS, copy_options _RHS) {
  return _LHS = _LHS ^ _RHS;
}

enum class _LIBCPP_ENUM_VIS directory_options : unsigned char {
  none = 0,
  follow_directory_symlink = 1,
  skip_permission_denied = 2
};

_LIBCPP_INLINE_VISIBILITY
inline constexpr directory_options operator&(directory_options _LHS,
                                             directory_options _RHS) {
  return static_cast<directory_options>(static_cast<unsigned char>(_LHS) &
                                        static_cast<unsigned char>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr directory_options operator|(directory_options _LHS,
                                             directory_options _RHS) {
  return static_cast<directory_options>(static_cast<unsigned char>(_LHS) |
                                        static_cast<unsigned char>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr directory_options operator^(directory_options _LHS,
                                             directory_options _RHS) {
  return static_cast<directory_options>(static_cast<unsigned char>(_LHS) ^
                                        static_cast<unsigned char>(_RHS));
}

_LIBCPP_INLINE_VISIBILITY
inline constexpr directory_options operator~(directory_options _LHS) {
  return static_cast<directory_options>(~static_cast<unsigned char>(_LHS));
}

_LIBCPP_INLINE_VISIBILITY
inline directory_options& operator&=(directory_options& _LHS,
                                     directory_options _RHS) {
  return _LHS = _LHS & _RHS;
}

_LIBCPP_INLINE_VISIBILITY
inline directory_options& operator|=(directory_options& _LHS,
                                     directory_options _RHS) {
  return _LHS = _LHS | _RHS;
}

_LIBCPP_INLINE_VISIBILITY
inline directory_options& operator^=(directory_options& _LHS,
                                     directory_options _RHS) {
  return _LHS = _LHS ^ _RHS;
}

class _LIBCPP_TYPE_VIS file_status {
public:
  // constructors
  _LIBCPP_INLINE_VISIBILITY
  file_status() noexcept : file_status(file_type::none) {}
  _LIBCPP_INLINE_VISIBILITY
  explicit file_status(file_type __ft, perms __prms = perms::unknown) noexcept
      : __ft_(__ft),
        __prms_(__prms) {}

  file_status(const file_status&) noexcept = default;
  file_status(file_status&&) noexcept = default;

  _LIBCPP_INLINE_VISIBILITY
  ~file_status() {}

  file_status& operator=(const file_status&) noexcept = default;
  file_status& operator=(file_status&&) noexcept = default;

  // observers
  _LIBCPP_INLINE_VISIBILITY
  file_type type() const noexcept { return __ft_; }

  _LIBCPP_INLINE_VISIBILITY
  perms permissions() const noexcept { return __prms_; }

  // modifiers
  _LIBCPP_INLINE_VISIBILITY
  void type(file_type __ft) noexcept { __ft_ = __ft; }

  _LIBCPP_INLINE_VISIBILITY
  void permissions(perms __p) noexcept { __prms_ = __p; }

private:
  file_type __ft_;
  perms __prms_;
};

class _LIBCPP_TYPE_VIS directory_entry;

template <class _Tp>
struct __can_convert_char {
  static const bool value = false;
};
template <class _Tp>
struct __can_convert_char<const _Tp> : public __can_convert_char<_Tp> {};
template <>
struct __can_convert_char<char> {
  static const bool value = true;
  using __char_type = char;
};
template <>
struct __can_convert_char<wchar_t> {
  static const bool value = true;
  using __char_type = wchar_t;
};
template <>
struct __can_convert_char<char16_t> {
  static const bool value = true;
  using __char_type = char16_t;
};
template <>
struct __can_convert_char<char32_t> {
  static const bool value = true;
  using __char_type = char32_t;
};

template <class _ECharT>
typename enable_if<__can_convert_char<_ECharT>::value, bool>::type
__is_separator(_ECharT __e) {
  return __e == _ECharT('/');
}

struct _NullSentinal {};

template <class _Tp>
using _Void = void;

template <class _Tp, class = void>
struct __is_pathable_string : public false_type {};

template <class _ECharT, class _Traits, class _Alloc>
struct __is_pathable_string<
    basic_string<_ECharT, _Traits, _Alloc>,
    _Void<typename __can_convert_char<_ECharT>::__char_type> >
    : public __can_convert_char<_ECharT> {
  using _Str = basic_string<_ECharT, _Traits, _Alloc>;
  using _Base = __can_convert_char<_ECharT>;
  static _ECharT const* __range_begin(_Str const& __s) { return __s.data(); }
  static _ECharT const* __range_end(_Str const& __s) {
    return __s.data() + __s.length();
  }
  static _ECharT __first_or_null(_Str const& __s) {
    return __s.empty() ? _ECharT{} : __s[0];
  }
};

template <class _ECharT, class _Traits>
struct __is_pathable_string<
    basic_string_view<_ECharT, _Traits>,
    _Void<typename __can_convert_char<_ECharT>::__char_type> >
    : public __can_convert_char<_ECharT> {
  using _Str = basic_string_view<_ECharT, _Traits>;
  using _Base = __can_convert_char<_ECharT>;
  static _ECharT const* __range_begin(_Str const& __s) { return __s.data(); }
  static _ECharT const* __range_end(_Str const& __s) {
    return __s.data() + __s.length();
  }
  static _ECharT __first_or_null(_Str const& __s) {
    return __s.empty() ? _ECharT{} : __s[0];
  }
};

template <class _Source, class _DS = typename decay<_Source>::type,
          class _UnqualPtrType =
              typename remove_const<typename remove_pointer<_DS>::type>::type,
          bool _IsCharPtr = is_pointer<_DS>::value&&
              __can_convert_char<_UnqualPtrType>::value>
struct __is_pathable_char_array : false_type {};

template <class _Source, class _ECharT, class _UPtr>
struct __is_pathable_char_array<_Source, _ECharT*, _UPtr, true>
    : __can_convert_char<typename remove_const<_ECharT>::type> {
  using _Base = __can_convert_char<typename remove_const<_ECharT>::type>;

  static _ECharT const* __range_begin(const _ECharT* __b) { return __b; }
  static _ECharT const* __range_end(const _ECharT* __b) {
    using _Iter = const _ECharT*;
    const _ECharT __sentinal = _ECharT{};
    _Iter __e = __b;
    for (; *__e != __sentinal; ++__e)
      ;
    return __e;
  }

  static _ECharT __first_or_null(const _ECharT* __b) { return *__b; }
};

template <class _Iter, bool _IsIt = __is_input_iterator<_Iter>::value,
          class = void>
struct __is_pathable_iter : false_type {};

template <class _Iter>
struct __is_pathable_iter<
    _Iter, true,
    _Void<typename __can_convert_char<
        typename iterator_traits<_Iter>::value_type>::__char_type> >
    : __can_convert_char<typename iterator_traits<_Iter>::value_type> {
  using _ECharT = typename iterator_traits<_Iter>::value_type;
  using _Base = __can_convert_char<_ECharT>;

  static _Iter __range_begin(_Iter __b) { return __b; }
  static _NullSentinal __range_end(_Iter) { return _NullSentinal{}; }

  static _ECharT __first_or_null(_Iter __b) { return *__b; }
};

template <class _Tp, bool _IsStringT = __is_pathable_string<_Tp>::value,
          bool _IsCharIterT = __is_pathable_char_array<_Tp>::value,
          bool _IsIterT = !_IsCharIterT && __is_pathable_iter<_Tp>::value>
struct __is_pathable : false_type {
  static_assert(!_IsStringT && !_IsCharIterT && !_IsIterT, "Must all be false");
};

template <class _Tp>
struct __is_pathable<_Tp, true, false, false> : __is_pathable_string<_Tp> {};

template <class _Tp>
struct __is_pathable<_Tp, false, true, false> : __is_pathable_char_array<_Tp> {
};

template <class _Tp>
struct __is_pathable<_Tp, false, false, true> : __is_pathable_iter<_Tp> {};

template <class _ECharT>
struct _PathCVT {
  static_assert(__can_convert_char<_ECharT>::value,
                "Char type not convertible");

  typedef __narrow_to_utf8<sizeof(_ECharT) * __CHAR_BIT__> _Narrower;

  static void __append_range(string& __dest, _ECharT const* __b,
                             _ECharT const* __e) {
    _Narrower()(back_inserter(__dest), __b, __e);
  }

  template <class _Iter>
  static void __append_range(string& __dest, _Iter __b, _Iter __e) {
    static_assert(!is_same<_Iter, _ECharT*>::value, "Call const overload");
    if (__b == __e)
      return;
    basic_string<_ECharT> __tmp(__b, __e);
    _Narrower()(back_inserter(__dest), __tmp.data(),
                __tmp.data() + __tmp.length());
  }

  template <class _Iter>
  static void __append_range(string& __dest, _Iter __b, _NullSentinal) {
    static_assert(!is_same<_Iter, _ECharT*>::value, "Call const overload");
    const _ECharT __sentinal = _ECharT{};
    if (*__b == __sentinal)
      return;
    basic_string<_ECharT> __tmp;
    for (; *__b != __sentinal; ++__b)
      __tmp.push_back(*__b);
    _Narrower()(back_inserter(__dest), __tmp.data(),
                __tmp.data() + __tmp.length());
  }

  template <class _Source>
  static void __append_source(string& __dest, _Source const& __s) {
    using _Traits = __is_pathable<_Source>;
    __append_range(__dest, _Traits::__range_begin(__s),
                   _Traits::__range_end(__s));
  }
};

template <>
struct _PathCVT<char> {

  template <class _Iter>
  static typename enable_if<__is_exactly_input_iterator<_Iter>::value>::type
  __append_range(string& __dest, _Iter __b, _Iter __e) {
    for (; __b != __e; ++__b)
      __dest.push_back(*__b);
  }

  template <class _Iter>
  static typename enable_if<__is_forward_iterator<_Iter>::value>::type
  __append_range(string& __dest, _Iter __b, _Iter __e) {
    __dest.__append_forward_unsafe(__b, __e);
  }

  template <class _Iter>
  static void __append_range(string& __dest, _Iter __b, _NullSentinal) {
    const char __sentinal = char{};
    for (; *__b != __sentinal; ++__b)
      __dest.push_back(*__b);
  }

  template <class _Source>
  static void __append_source(string& __dest, _Source const& __s) {
    using _Traits = __is_pathable<_Source>;
    __append_range(__dest, _Traits::__range_begin(__s),
                   _Traits::__range_end(__s));
  }
};

class _LIBCPP_TYPE_VIS path {
  template <class _SourceOrIter, class _Tp = path&>
  using _EnableIfPathable =
      typename enable_if<__is_pathable<_SourceOrIter>::value, _Tp>::type;

  template <class _Tp>
  using _SourceChar = typename __is_pathable<_Tp>::__char_type;

  template <class _Tp>
  using _SourceCVT = _PathCVT<_SourceChar<_Tp> >;

public:
  typedef char value_type;
  typedef basic_string<value_type> string_type;
  typedef _VSTD::string_view __string_view;
  static constexpr value_type preferred_separator = '/';

  enum class _LIBCPP_ENUM_VIS format : unsigned char {
    auto_format,
    native_format,
    generic_format
  };

  // constructors and destructor
  _LIBCPP_INLINE_VISIBILITY path() noexcept {}
  _LIBCPP_INLINE_VISIBILITY path(const path& __p) : __pn_(__p.__pn_) {}
  _LIBCPP_INLINE_VISIBILITY path(path&& __p) noexcept
      : __pn_(_VSTD::move(__p.__pn_)) {}

  _LIBCPP_INLINE_VISIBILITY
  path(string_type&& __s, format = format::auto_format) noexcept
      : __pn_(_VSTD::move(__s)) {}

  template <class _Source, class = _EnableIfPathable<_Source, void> >
  path(const _Source& __src, format = format::auto_format) {
    _SourceCVT<_Source>::__append_source(__pn_, __src);
  }

  template <class _InputIt>
  path(_InputIt __first, _InputIt __last, format = format::auto_format) {
    typedef typename iterator_traits<_InputIt>::value_type _ItVal;
    _PathCVT<_ItVal>::__append_range(__pn_, __first, __last);
  }

  // TODO Implement locale conversions.
  template <class _Source, class = _EnableIfPathable<_Source, void> >
  path(const _Source& __src, const locale& __loc, format = format::auto_format);
  template <class _InputIt>
  path(_InputIt __first, _InputIt _last, const locale& __loc,
       format = format::auto_format);

  _LIBCPP_INLINE_VISIBILITY
  ~path() = default;

  // assignments
  _LIBCPP_INLINE_VISIBILITY
  path& operator=(const path& __p) {
    __pn_ = __p.__pn_;
    return *this;
  }

  _LIBCPP_INLINE_VISIBILITY
  path& operator=(path&& __p) noexcept {
    __pn_ = _VSTD::move(__p.__pn_);
    return *this;
  }

  template <class = void>
  _LIBCPP_INLINE_VISIBILITY path& operator=(string_type&& __s) noexcept {
    __pn_ = _VSTD::move(__s);
    return *this;
  }

  _LIBCPP_INLINE_VISIBILITY
  path& assign(string_type&& __s) noexcept {
    __pn_ = _VSTD::move(__s);
    return *this;
  }

  template <class _Source>
  _LIBCPP_INLINE_VISIBILITY _EnableIfPathable<_Source>
  operator=(const _Source& __src) {
    return this->assign(__src);
  }

  template <class _Source>
  _EnableIfPathable<_Source> assign(const _Source& __src) {
    __pn_.clear();
    _SourceCVT<_Source>::__append_source(__pn_, __src);
    return *this;
  }

  template <class _InputIt>
  path& assign(_InputIt __first, _InputIt __last) {
    typedef typename iterator_traits<_InputIt>::value_type _ItVal;
    __pn_.clear();
    _PathCVT<_ItVal>::__append_range(__pn_, __first, __last);
    return *this;
  }

private:
  template <class _ECharT>
  static bool __source_is_absolute(_ECharT __first_or_null) {
    return __is_separator(__first_or_null);
  }

public:
  // appends
  path& operator/=(const path& __p) {
    if (__p.is_absolute()) {
      __pn_ = __p.__pn_;
      return *this;
    }
    if (has_filename())
      __pn_ += preferred_separator;
    __pn_ += __p.native();
    return *this;
  }

  // FIXME: Use _LIBCPP_DIAGNOSE_WARNING to produce a diagnostic when __src
  // is known at compile time to be "/' since the user almost certainly intended
  // to append a separator instead of overwriting the path with "/"
  template <class _Source>
  _LIBCPP_INLINE_VISIBILITY _EnableIfPathable<_Source>
  operator/=(const _Source& __src) {
    return this->append(__src);
  }

  template <class _Source>
  _EnableIfPathable<_Source> append(const _Source& __src) {
    using _Traits = __is_pathable<_Source>;
    using _CVT = _PathCVT<_SourceChar<_Source> >;
    if (__source_is_absolute(_Traits::__first_or_null(__src)))
      __pn_.clear();
    else if (has_filename())
      __pn_ += preferred_separator;
    _CVT::__append_source(__pn_, __src);
    return *this;
  }

  template <class _InputIt>
  path& append(_InputIt __first, _InputIt __last) {
    typedef typename iterator_traits<_InputIt>::value_type _ItVal;
    static_assert(__can_convert_char<_ItVal>::value, "Must convertible");
    using _CVT = _PathCVT<_ItVal>;
    if (__first != __last && __source_is_absolute(*__first))
      __pn_.clear();
    else if (has_filename())
      __pn_ += preferred_separator;
    _CVT::__append_range(__pn_, __first, __last);
    return *this;
  }

  // concatenation
  _LIBCPP_INLINE_VISIBILITY
  path& operator+=(const path& __x) {
    __pn_ += __x.__pn_;
    return *this;
  }

  _LIBCPP_INLINE_VISIBILITY
  path& operator+=(const string_type& __x) {
    __pn_ += __x;
    return *this;
  }

  _LIBCPP_INLINE_VISIBILITY
  path& operator+=(__string_view __x) {
    __pn_ += __x;
    return *this;
  }

  _LIBCPP_INLINE_VISIBILITY
  path& operator+=(const value_type* __x) {
    __pn_ += __x;
    return *this;
  }

  _LIBCPP_INLINE_VISIBILITY
  path& operator+=(value_type __x) {
    __pn_ += __x;
    return *this;
  }

  template <class _ECharT>
  typename enable_if<__can_convert_char<_ECharT>::value, path&>::type
  operator+=(_ECharT __x) {
    basic_string<_ECharT> __tmp;
    __tmp += __x;
    _PathCVT<_ECharT>::__append_source(__pn_, __tmp);
    return *this;
  }

  template <class _Source>
  _EnableIfPathable<_Source> operator+=(const _Source& __x) {
    return this->concat(__x);
  }

  template <class _Source>
  _EnableIfPathable<_Source> concat(const _Source& __x) {
    _SourceCVT<_Source>::__append_source(__pn_, __x);
    return *this;
  }

  template <class _InputIt>
  path& concat(_InputIt __first, _InputIt __last) {
    typedef typename iterator_traits<_InputIt>::value_type _ItVal;
    _PathCVT<_ItVal>::__append_range(__pn_, __first, __last);
    return *this;
  }

  // modifiers
  _LIBCPP_INLINE_VISIBILITY
  void clear() noexcept { __pn_.clear(); }

  path& make_preferred() { return *this; }

  _LIBCPP_INLINE_VISIBILITY
  path& remove_filename() {
    auto __fname = __filename();
    if (!__fname.empty())
      __pn_.erase(__fname.data() - __pn_.data());
    return *this;
  }

  path& replace_filename(const path& __replacement) {
    remove_filename();
    return (*this /= __replacement);
  }

  path& replace_extension(const path& __replacement = path());

  _LIBCPP_INLINE_VISIBILITY
  void swap(path& __rhs) noexcept { __pn_.swap(__rhs.__pn_); }

  // private helper to allow reserving memory in the path
  _LIBCPP_INLINE_VISIBILITY
  void __reserve(size_t __s) { __pn_.reserve(__s); }

  // native format observers
  _LIBCPP_INLINE_VISIBILITY
  const string_type& native() const noexcept { return __pn_; }

  _LIBCPP_INLINE_VISIBILITY
  const value_type* c_str() const noexcept { return __pn_.c_str(); }

  _LIBCPP_INLINE_VISIBILITY operator string_type() const { return __pn_; }

  template <class _ECharT, class _Traits = char_traits<_ECharT>,
            class _Allocator = allocator<_ECharT> >
  basic_string<_ECharT, _Traits, _Allocator>
  string(const _Allocator& __a = _Allocator()) const {
    using _CVT = __widen_from_utf8<sizeof(_ECharT) * __CHAR_BIT__>;
    using _Str = basic_string<_ECharT, _Traits, _Allocator>;
    _Str __s(__a);
    __s.reserve(__pn_.size());
    _CVT()(back_inserter(__s), __pn_.data(), __pn_.data() + __pn_.size());
    return __s;
  }

  _LIBCPP_INLINE_VISIBILITY std::string string() const { return __pn_; }
  _LIBCPP_INLINE_VISIBILITY std::wstring wstring() const {
    return string<wchar_t>();
  }
  _LIBCPP_INLINE_VISIBILITY std::string u8string() const { return __pn_; }
  _LIBCPP_INLINE_VISIBILITY std::u16string u16string() const {
    return string<char16_t>();
  }
  _LIBCPP_INLINE_VISIBILITY std::u32string u32string() const {
    return string<char32_t>();
  }

  // generic format observers
  template <class _ECharT, class _Traits = char_traits<_ECharT>,
            class _Allocator = allocator<_ECharT> >
  basic_string<_ECharT, _Traits, _Allocator>
  generic_string(const _Allocator& __a = _Allocator()) const {
    return string<_ECharT, _Traits, _Allocator>(__a);
  }

  std::string generic_string() const { return __pn_; }
  std::wstring generic_wstring() const { return string<wchar_t>(); }
  std::string generic_u8string() const { return __pn_; }
  std::u16string generic_u16string() const { return string<char16_t>(); }
  std::u32string generic_u32string() const { return string<char32_t>(); }

private:
  int __compare(__string_view) const;
  __string_view __root_name() const;
  __string_view __root_directory() const;
  __string_view __root_path_raw() const;
  __string_view __relative_path() const;
  __string_view __parent_path() const;
  __string_view __filename() const;
  __string_view __stem() const;
  __string_view __extension() const;

public:
  // compare
  _LIBCPP_INLINE_VISIBILITY int compare(const path& __p) const noexcept {
    return __compare(__p.__pn_);
  }
  _LIBCPP_INLINE_VISIBILITY int compare(const string_type& __s) const {
    return __compare(__s);
  }
  _LIBCPP_INLINE_VISIBILITY int compare(__string_view __s) const {
    return __compare(__s);
  }
  _LIBCPP_INLINE_VISIBILITY int compare(const value_type* __s) const {
    return __compare(__s);
  }

  // decomposition
  _LIBCPP_INLINE_VISIBILITY path root_name() const {
    return string_type(__root_name());
  }
  _LIBCPP_INLINE_VISIBILITY path root_directory() const {
    return string_type(__root_directory());
  }
  _LIBCPP_INLINE_VISIBILITY path root_path() const {
    return root_name().append(string_type(__root_directory()));
  }
  _LIBCPP_INLINE_VISIBILITY path relative_path() const {
    return string_type(__relative_path());
  }
  _LIBCPP_INLINE_VISIBILITY path parent_path() const {
    return string_type(__parent_path());
  }
  _LIBCPP_INLINE_VISIBILITY path filename() const {
    return string_type(__filename());
  }
  _LIBCPP_INLINE_VISIBILITY path stem() const { return string_type(__stem()); }
  _LIBCPP_INLINE_VISIBILITY path extension() const {
    return string_type(__extension());
  }

  // query
  _LIBCPP_NODISCARD_AFTER_CXX17 _LIBCPP_INLINE_VISIBILITY bool
  empty() const noexcept {
    return __pn_.empty();
  }

  _LIBCPP_INLINE_VISIBILITY bool has_root_name() const {
    return !__root_name().empty();
  }
  _LIBCPP_INLINE_VISIBILITY bool has_root_directory() const {
    return !__root_directory().empty();
  }
  _LIBCPP_INLINE_VISIBILITY bool has_root_path() const {
    return !__root_path_raw().empty();
  }
  _LIBCPP_INLINE_VISIBILITY bool has_relative_path() const {
    return !__relative_path().empty();
  }
  _LIBCPP_INLINE_VISIBILITY bool has_parent_path() const {
    return !__parent_path().empty();
  }
  _LIBCPP_INLINE_VISIBILITY bool has_filename() const {
    return !__filename().empty();
  }
  _LIBCPP_INLINE_VISIBILITY bool has_stem() const { return !__stem().empty(); }
  _LIBCPP_INLINE_VISIBILITY bool has_extension() const {
    return !__extension().empty();
  }

  _LIBCPP_INLINE_VISIBILITY bool is_absolute() const {
    return has_root_directory();
  }
  _LIBCPP_INLINE_VISIBILITY bool is_relative() const { return !is_absolute(); }

  // relative paths
  path lexically_normal() const;
  path lexically_relative(const path& __base) const;

  _LIBCPP_INLINE_VISIBILITY path lexically_proximate(const path& __base) const {
    path __result = this->lexically_relative(__base);
    if (__result.native().empty())
      return *this;
    return __result;
  }

  // iterators
  class _LIBCPP_TYPE_VIS iterator;
  typedef iterator const_iterator;

  iterator begin() const;
  iterator end() const;

  template <class _CharT, class _Traits>
  _LIBCPP_INLINE_VISIBILITY friend
      typename enable_if<is_same<_CharT, char>::value &&
                             is_same<_Traits, char_traits<char> >::value,
                         basic_ostream<_CharT, _Traits>&>::type
      operator<<(basic_ostream<_CharT, _Traits>& __os, const path& __p) {
    __os << std::__quoted(__p.native());
    return __os;
  }

  template <class _CharT, class _Traits>
  _LIBCPP_INLINE_VISIBILITY friend
      typename enable_if<!is_same<_CharT, char>::value ||
                             !is_same<_Traits, char_traits<char> >::value,
                         basic_ostream<_CharT, _Traits>&>::type
      operator<<(basic_ostream<_CharT, _Traits>& __os, const path& __p) {
    __os << std::__quoted(__p.string<_CharT, _Traits>());
    return __os;
  }

  template <class _CharT, class _Traits>
  _LIBCPP_INLINE_VISIBILITY friend basic_istream<_CharT, _Traits>&
  operator>>(basic_istream<_CharT, _Traits>& __is, path& __p) {
    basic_string<_CharT, _Traits> __tmp;
    __is >> __quoted(__tmp);
    __p = __tmp;
    return __is;
  }

private:
  inline _LIBCPP_INLINE_VISIBILITY path&
  __assign_view(__string_view const& __s) noexcept {
    __pn_ = string_type(__s);
    return *this;
  }
  string_type __pn_;
};

inline _LIBCPP_INLINE_VISIBILITY void swap(path& __lhs, path& __rhs) noexcept {
  __lhs.swap(__rhs);
}

_LIBCPP_FUNC_VIS
size_t hash_value(const path& __p) noexcept;

inline _LIBCPP_INLINE_VISIBILITY bool operator==(const path& __lhs,
                                                 const path& __rhs) noexcept {
  return __lhs.compare(__rhs) == 0;
}

inline _LIBCPP_INLINE_VISIBILITY bool operator!=(const path& __lhs,
                                                 const path& __rhs) noexcept {
  return __lhs.compare(__rhs) != 0;
}

inline _LIBCPP_INLINE_VISIBILITY bool operator<(const path& __lhs,
                                                const path& __rhs) noexcept {
  return __lhs.compare(__rhs) < 0;
}

inline _LIBCPP_INLINE_VISIBILITY bool operator<=(const path& __lhs,
                                                 const path& __rhs) noexcept {
  return __lhs.compare(__rhs) <= 0;
}

inline _LIBCPP_INLINE_VISIBILITY bool operator>(const path& __lhs,
                                                const path& __rhs) noexcept {
  return __lhs.compare(__rhs) > 0;
}

inline _LIBCPP_INLINE_VISIBILITY bool operator>=(const path& __lhs,
                                                 const path& __rhs) noexcept {
  return __lhs.compare(__rhs) >= 0;
}

inline _LIBCPP_INLINE_VISIBILITY path operator/(const path& __lhs,
                                                const path& __rhs) {
  path __result(__lhs);
  __result /= __rhs;
  return __result;
}

template <class _Source>
_LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_pathable<_Source>::value, path>::type
    u8path(const _Source& __s) {
  static_assert(
      is_same<typename __is_pathable<_Source>::__char_type, char>::value,
      "u8path(Source const&) requires Source have a character type of type "
      "'char'");
  return path(__s);
}

template <class _InputIt>
_LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_pathable<_InputIt>::value, path>::type
    u8path(_InputIt __f, _InputIt __l) {
  static_assert(
      is_same<typename __is_pathable<_InputIt>::__char_type, char>::value,
      "u8path(Iter, Iter) requires Iter have a value_type of type 'char'");
  return path(__f, __l);
}

class _LIBCPP_TYPE_VIS path::iterator {
public:
  enum _ParserState : unsigned char {
    _Singular,
    _BeforeBegin,
    _InRootName,
    _InRootDir,
    _InFilenames,
    _InTrailingSep,
    _AtEnd
  };

public:
  typedef bidirectional_iterator_tag iterator_category;

  typedef path value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const path* pointer;
  typedef const path& reference;

  typedef void
      __stashing_iterator_tag; // See reverse_iterator and __is_stashing_iterator

public:
  _LIBCPP_INLINE_VISIBILITY
  iterator()
      : __stashed_elem_(), __path_ptr_(nullptr), __entry_(),
        __state_(_Singular) {}

  iterator(const iterator&) = default;
  ~iterator() = default;

  iterator& operator=(const iterator&) = default;

  _LIBCPP_INLINE_VISIBILITY
  reference operator*() const { return __stashed_elem_; }

  _LIBCPP_INLINE_VISIBILITY
  pointer operator->() const { return &__stashed_elem_; }

  _LIBCPP_INLINE_VISIBILITY
  iterator& operator++() {
    _LIBCPP_ASSERT(__state_ != _Singular,
                   "attempting to increment a singular iterator");
    _LIBCPP_ASSERT(__state_ != _AtEnd,
                   "attempting to increment the end iterator");
    return __increment();
  }

  _LIBCPP_INLINE_VISIBILITY
  iterator operator++(int) {
    iterator __it(*this);
    this->operator++();
    return __it;
  }

  _LIBCPP_INLINE_VISIBILITY
  iterator& operator--() {
    _LIBCPP_ASSERT(__state_ != _Singular,
                   "attempting to decrement a singular iterator");
    _LIBCPP_ASSERT(__entry_.data() != __path_ptr_->native().data(),
                   "attempting to decrement the begin iterator");
    return __decrement();
  }

  _LIBCPP_INLINE_VISIBILITY
  iterator operator--(int) {
    iterator __it(*this);
    this->operator--();
    return __it;
  }

private:
  friend class path;

  inline _LIBCPP_INLINE_VISIBILITY friend bool operator==(const iterator&,
                                                          const iterator&);

  iterator& __increment();
  iterator& __decrement();

  path __stashed_elem_;
  const path* __path_ptr_;
  path::__string_view __entry_;
  _ParserState __state_;
};

inline _LIBCPP_INLINE_VISIBILITY bool operator==(const path::iterator& __lhs,
                                                 const path::iterator& __rhs) {
  return __lhs.__path_ptr_ == __rhs.__path_ptr_ &&
         __lhs.__entry_.data() == __rhs.__entry_.data();
}

inline _LIBCPP_INLINE_VISIBILITY bool operator!=(const path::iterator& __lhs,
                                                 const path::iterator& __rhs) {
  return !(__lhs == __rhs);
}

class _LIBCPP_EXCEPTION_ABI filesystem_error : public system_error {
public:
  _LIBCPP_INLINE_VISIBILITY
  filesystem_error(const string& __what, error_code __ec)
      : system_error(__ec, __what),
        __storage_(make_shared<_Storage>(path(), path())) {
    __create_what(0);
  }

  _LIBCPP_INLINE_VISIBILITY
  filesystem_error(const string& __what, const path& __p1, error_code __ec)
      : system_error(__ec, __what),
        __storage_(make_shared<_Storage>(__p1, path())) {
    __create_what(1);
  }

  _LIBCPP_INLINE_VISIBILITY
  filesystem_error(const string& __what, const path& __p1, const path& __p2,
                   error_code __ec)
      : system_error(__ec, __what),
        __storage_(make_shared<_Storage>(__p1, __p2)) {
    __create_what(2);
  }

  _LIBCPP_INLINE_VISIBILITY
  const path& path1() const noexcept { return __storage_->__p1_; }

  _LIBCPP_INLINE_VISIBILITY
  const path& path2() const noexcept { return __storage_->__p2_; }

  ~filesystem_error() override; // key function

  _LIBCPP_INLINE_VISIBILITY
  const char* what() const noexcept override {
    return __storage_->__what_.c_str();
  }

  _LIBCPP_FUNC_VIS
  void __create_what(int __num_paths);

private:
  struct _Storage {
    _LIBCPP_INLINE_VISIBILITY
    _Storage(const path& __p1, const path& __p2) : __p1_(__p1), __p2_(__p2) {}

    path __p1_;
    path __p2_;
    string __what_;
  };
  shared_ptr<_Storage> __storage_;
};

template <class... _Args>
_LIBCPP_NORETURN inline _LIBCPP_INLINE_VISIBILITY
#ifndef _LIBCPP_NO_EXCEPTIONS
    void
    __throw_filesystem_error(_Args&&... __args) {
  throw filesystem_error(std::forward<_Args>(__args)...);
}
#else
    void
    __throw_filesystem_error(_Args&&...) {
  _VSTD::abort();
}
#endif

// operational functions

_LIBCPP_FUNC_VIS
path __absolute(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
path __canonical(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
void __copy(const path& __from, const path& __to, copy_options __opt,
            error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
bool __copy_file(const path& __from, const path& __to, copy_options __opt,
                 error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
void __copy_symlink(const path& __existing_symlink, const path& __new_symlink,
                    error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
bool __create_directories(const path& p, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
bool __create_directory(const path& p, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
bool __create_directory(const path& p, const path& attributes,
                        error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
void __create_directory_symlink(const path& __to, const path& __new_symlink,
                                error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
void __create_hard_link(const path& __to, const path& __new_hard_link,
                        error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
void __create_symlink(const path& __to, const path& __new_symlink,
                      error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
path __current_path(error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
void __current_path(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
bool __equivalent(const path&, const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
uintmax_t __file_size(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
uintmax_t __hard_link_count(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
bool __fs_is_empty(const path& p, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
file_time_type __last_write_time(const path& p, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
void __last_write_time(const path& p, file_time_type new_time,
                       error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
void __permissions(const path&, perms, perm_options, error_code* = nullptr);
_LIBCPP_FUNC_VIS
path __read_symlink(const path& p, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
bool __remove(const path& p, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
uintmax_t __remove_all(const path& p, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
void __rename(const path& from, const path& to, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
void __resize_file(const path& p, uintmax_t size, error_code* ec = nullptr);
_LIBCPP_FUNC_VIS
space_info __space(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
file_status __status(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
file_status __symlink_status(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
path __system_complete(const path&, error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
path __temp_directory_path(error_code* __ec = nullptr);
_LIBCPP_FUNC_VIS
path __weakly_canonical(path const& __p, error_code* __ec = nullptr);

inline _LIBCPP_INLINE_VISIBILITY path current_path() {
  return __current_path();
}

inline _LIBCPP_INLINE_VISIBILITY path current_path(error_code& __ec) {
  return __current_path(&__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void current_path(const path& __p) {
  __current_path(__p);
}

inline _LIBCPP_INLINE_VISIBILITY void current_path(const path& __p,
                                                   error_code& __ec) noexcept {
  __current_path(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY path absolute(const path& __p) {
  return __absolute(__p);
}

inline _LIBCPP_INLINE_VISIBILITY path absolute(const path& __p,
                                               error_code& __ec) {
  return __absolute(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY path canonical(const path& __p) {
  return __canonical(__p);
}

inline _LIBCPP_INLINE_VISIBILITY path canonical(const path& __p,
                                                error_code& __ec) {
  return __canonical(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void copy(const path& __from,
                                           const path& __to) {
  __copy(__from, __to, copy_options::none);
}

inline _LIBCPP_INLINE_VISIBILITY void copy(const path& __from, const path& __to,
                                           error_code& __ec) {
  __copy(__from, __to, copy_options::none, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void copy(const path& __from, const path& __to,
                                           copy_options __opt) {
  __copy(__from, __to, __opt);
}

inline _LIBCPP_INLINE_VISIBILITY void copy(const path& __from, const path& __to,
                                           copy_options __opt,
                                           error_code& __ec) {
  __copy(__from, __to, __opt, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool copy_file(const path& __from,
                                                const path& __to) {
  return __copy_file(__from, __to, copy_options::none);
}

inline _LIBCPP_INLINE_VISIBILITY bool
copy_file(const path& __from, const path& __to, error_code& __ec) {
  return __copy_file(__from, __to, copy_options::none, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool
copy_file(const path& __from, const path& __to, copy_options __opt) {
  return __copy_file(__from, __to, __opt);
}

inline _LIBCPP_INLINE_VISIBILITY bool copy_file(const path& __from,
                                                const path& __to,
                                                copy_options __opt,
                                                error_code& __ec) {
  return __copy_file(__from, __to, __opt, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void copy_symlink(const path& __existing,
                                                   const path& __new) {
  __copy_symlink(__existing, __new);
}

inline _LIBCPP_INLINE_VISIBILITY void
copy_symlink(const path& __ext, const path& __new, error_code& __ec) noexcept {
  __copy_symlink(__ext, __new, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool create_directories(const path& __p) {
  return __create_directories(__p);
}

inline _LIBCPP_INLINE_VISIBILITY bool create_directories(const path& __p,
                                                         error_code& __ec) {
  return __create_directories(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool create_directory(const path& __p) {
  return __create_directory(__p);
}

inline _LIBCPP_INLINE_VISIBILITY bool
create_directory(const path& __p, error_code& __ec) noexcept {
  return __create_directory(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool create_directory(const path& __p,
                                                       const path& __attrs) {
  return __create_directory(__p, __attrs);
}

inline _LIBCPP_INLINE_VISIBILITY bool
create_directory(const path& __p, const path& __attrs,
                 error_code& __ec) noexcept {
  return __create_directory(__p, __attrs, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void
create_directory_symlink(const path& __to, const path& __new) {
  __create_directory_symlink(__to, __new);
}

inline _LIBCPP_INLINE_VISIBILITY void
create_directory_symlink(const path& __to, const path& __new,
                         error_code& __ec) noexcept {
  __create_directory_symlink(__to, __new, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void create_hard_link(const path& __to,
                                                       const path& __new) {
  __create_hard_link(__to, __new);
}

inline _LIBCPP_INLINE_VISIBILITY void
create_hard_link(const path& __to, const path& __new,
                 error_code& __ec) noexcept {
  __create_hard_link(__to, __new, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void create_symlink(const path& __to,
                                                     const path& __new) {
  __create_symlink(__to, __new);
}

inline _LIBCPP_INLINE_VISIBILITY void
create_symlink(const path& __to, const path& __new, error_code& __ec) noexcept {
  return __create_symlink(__to, __new, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool status_known(file_status __s) noexcept {
  return __s.type() != file_type::none;
}

inline _LIBCPP_INLINE_VISIBILITY bool exists(file_status __s) noexcept {
  return status_known(__s) && __s.type() != file_type::not_found;
}

inline _LIBCPP_INLINE_VISIBILITY bool exists(const path& __p) {
  return exists(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool exists(const path& __p,
                                             error_code& __ec) noexcept {
  auto __s = __status(__p, &__ec);
  if (status_known(__s))
    __ec.clear();
  return exists(__s);
}

inline _LIBCPP_INLINE_VISIBILITY bool equivalent(const path& __p1,
                                                 const path& __p2) {
  return __equivalent(__p1, __p2);
}

inline _LIBCPP_INLINE_VISIBILITY bool
equivalent(const path& __p1, const path& __p2, error_code& __ec) noexcept {
  return __equivalent(__p1, __p2, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY uintmax_t file_size(const path& __p) {
  return __file_size(__p);
}

inline _LIBCPP_INLINE_VISIBILITY uintmax_t
file_size(const path& __p, error_code& __ec) noexcept {
  return __file_size(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY uintmax_t hard_link_count(const path& __p) {
  return __hard_link_count(__p);
}

inline _LIBCPP_INLINE_VISIBILITY uintmax_t
hard_link_count(const path& __p, error_code& __ec) noexcept {
  return __hard_link_count(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool is_block_file(file_status __s) noexcept {
  return __s.type() == file_type::block;
}

inline _LIBCPP_INLINE_VISIBILITY bool is_block_file(const path& __p) {
  return is_block_file(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_block_file(const path& __p,
                                                    error_code& __ec) noexcept {
  return is_block_file(__status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY bool
is_character_file(file_status __s) noexcept {
  return __s.type() == file_type::character;
}

inline _LIBCPP_INLINE_VISIBILITY bool is_character_file(const path& __p) {
  return is_character_file(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool
is_character_file(const path& __p, error_code& __ec) noexcept {
  return is_character_file(__status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_directory(file_status __s) noexcept {
  return __s.type() == file_type::directory;
}

inline _LIBCPP_INLINE_VISIBILITY bool is_directory(const path& __p) {
  return is_directory(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_directory(const path& __p,
                                                   error_code& __ec) noexcept {
  return is_directory(__status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_empty(const path& __p) {
  return __fs_is_empty(__p);
}

inline _LIBCPP_INLINE_VISIBILITY bool is_empty(const path& __p,
                                               error_code& __ec) {
  return __fs_is_empty(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY bool is_fifo(file_status __s) noexcept {
  return __s.type() == file_type::fifo;
}
inline _LIBCPP_INLINE_VISIBILITY bool is_fifo(const path& __p) {
  return is_fifo(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_fifo(const path& __p,
                                              error_code& __ec) noexcept {
  return is_fifo(__status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY bool
is_regular_file(file_status __s) noexcept {
  return __s.type() == file_type::regular;
}

inline _LIBCPP_INLINE_VISIBILITY bool is_regular_file(const path& __p) {
  return is_regular_file(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool
is_regular_file(const path& __p, error_code& __ec) noexcept {
  return is_regular_file(__status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_socket(file_status __s) noexcept {
  return __s.type() == file_type::socket;
}

inline _LIBCPP_INLINE_VISIBILITY bool is_socket(const path& __p) {
  return is_socket(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_socket(const path& __p,
                                                error_code& __ec) noexcept {
  return is_socket(__status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_symlink(file_status __s) noexcept {
  return __s.type() == file_type::symlink;
}

inline _LIBCPP_INLINE_VISIBILITY bool is_symlink(const path& __p) {
  return is_symlink(__symlink_status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_symlink(const path& __p,
                                                 error_code& __ec) noexcept {
  return is_symlink(__symlink_status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_other(file_status __s) noexcept {
  return exists(__s) && !is_regular_file(__s) && !is_directory(__s) &&
         !is_symlink(__s);
}

inline _LIBCPP_INLINE_VISIBILITY bool is_other(const path& __p) {
  return is_other(__status(__p));
}

inline _LIBCPP_INLINE_VISIBILITY bool is_other(const path& __p,
                                               error_code& __ec) noexcept {
  return is_other(__status(__p, &__ec));
}

inline _LIBCPP_INLINE_VISIBILITY file_time_type
last_write_time(const path& __p) {
  return __last_write_time(__p);
}

inline _LIBCPP_INLINE_VISIBILITY file_time_type
last_write_time(const path& __p, error_code& __ec) noexcept {
  return __last_write_time(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void last_write_time(const path& __p,
                                                      file_time_type __t) {
  __last_write_time(__p, __t);
}

inline _LIBCPP_INLINE_VISIBILITY void
last_write_time(const path& __p, file_time_type __t,
                error_code& __ec) noexcept {
  __last_write_time(__p, __t, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void
permissions(const path& __p, perms __prms,
            perm_options __opts = perm_options::replace) {
  __permissions(__p, __prms, __opts);
}

inline _LIBCPP_INLINE_VISIBILITY void permissions(const path& __p, perms __prms,
                                                  error_code& __ec) noexcept {
  __permissions(__p, __prms, perm_options::replace, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void permissions(const path& __p, perms __prms,
                                                  perm_options __opts,
                                                  error_code& __ec) {
  __permissions(__p, __prms, __opts, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY path proximate(const path& __p,
                                                const path& __base,
                                                error_code& __ec) {
  path __tmp = __weakly_canonical(__p, &__ec);
  if (__ec)
    return {};
  path __tmp_base = __weakly_canonical(__base, &__ec);
  if (__ec)
    return {};
  return __tmp.lexically_proximate(__tmp_base);
}

inline _LIBCPP_INLINE_VISIBILITY path proximate(const path& __p,
                                                error_code& __ec) {
  return proximate(__p, current_path(), __ec);
}

inline _LIBCPP_INLINE_VISIBILITY path
proximate(const path& __p, const path& __base = current_path()) {
  return __weakly_canonical(__p).lexically_proximate(
      __weakly_canonical(__base));
}

inline _LIBCPP_INLINE_VISIBILITY path read_symlink(const path& __p) {
  return __read_symlink(__p);
}

inline _LIBCPP_INLINE_VISIBILITY path read_symlink(const path& __p,
                                                   error_code& __ec) {
  return __read_symlink(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY path relative(const path& __p,
                                               const path& __base,
                                               error_code& __ec) {
  path __tmp = __weakly_canonical(__p, &__ec);
  if (__ec)
    return path();
  path __tmpbase = __weakly_canonical(__base, &__ec);
  if (__ec)
    return path();
  return __tmp.lexically_relative(__tmpbase);
}

inline _LIBCPP_INLINE_VISIBILITY path relative(const path& __p,
                                               error_code& __ec) {
  return relative(__p, current_path(), __ec);
}

inline _LIBCPP_INLINE_VISIBILITY path
relative(const path& __p, const path& __base = current_path()) {
  return __weakly_canonical(__p).lexically_relative(__weakly_canonical(__base));
}

inline _LIBCPP_INLINE_VISIBILITY bool remove(const path& __p) {
  return __remove(__p);
}

inline _LIBCPP_INLINE_VISIBILITY bool remove(const path& __p,
                                             error_code& __ec) noexcept {
  return __remove(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY uintmax_t remove_all(const path& __p) {
  return __remove_all(__p);
}

inline _LIBCPP_INLINE_VISIBILITY uintmax_t remove_all(const path& __p,
                                                      error_code& __ec) {
  return __remove_all(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void rename(const path& __from,
                                             const path& __to) {
  return __rename(__from, __to);
}

inline _LIBCPP_INLINE_VISIBILITY void
rename(const path& __from, const path& __to, error_code& __ec) noexcept {
  return __rename(__from, __to, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY void resize_file(const path& __p,
                                                  uintmax_t __ns) {
  return __resize_file(__p, __ns);
}

inline _LIBCPP_INLINE_VISIBILITY void
resize_file(const path& __p, uintmax_t __ns, error_code& __ec) noexcept {
  return __resize_file(__p, __ns, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY space_info space(const path& __p) {
  return __space(__p);
}

inline _LIBCPP_INLINE_VISIBILITY space_info space(const path& __p,
                                                  error_code& __ec) noexcept {
  return __space(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY file_status status(const path& __p) {
  return __status(__p);
}

inline _LIBCPP_INLINE_VISIBILITY file_status status(const path& __p,
                                                    error_code& __ec) noexcept {
  return __status(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY file_status symlink_status(const path& __p) {
  return __symlink_status(__p);
}

inline _LIBCPP_INLINE_VISIBILITY file_status
symlink_status(const path& __p, error_code& __ec) noexcept {
  return __symlink_status(__p, &__ec);
}

inline _LIBCPP_INLINE_VISIBILITY path temp_directory_path() {
  return __temp_directory_path();
}

inline _LIBCPP_INLINE_VISIBILITY path temp_directory_path(error_code& __ec) {
  return __temp_directory_path(&__ec);
}

inline _LIBCPP_INLINE_VISIBILITY path weakly_canonical(path const& __p) {
  return __weakly_canonical(__p);
}

inline _LIBCPP_INLINE_VISIBILITY path weakly_canonical(path const& __p,
                                                       error_code& __ec) {
  return __weakly_canonical(__p, &__ec);
}

class directory_iterator;
class recursive_directory_iterator;
class __dir_stream;

class directory_entry {
  typedef _VSTD_FS::path _Path;

public:
  // constructors and destructors
  directory_entry() noexcept = default;
  directory_entry(directory_entry const&) = default;
  directory_entry(directory_entry&&) noexcept = default;

  _LIBCPP_INLINE_VISIBILITY
  explicit directory_entry(_Path const& __p) : __p_(__p) {
    error_code __ec;
    __refresh(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  directory_entry(_Path const& __p, error_code& __ec) : __p_(__p) {
    __refresh(&__ec);
  }

  ~directory_entry() {}

  directory_entry& operator=(directory_entry const&) = default;
  directory_entry& operator=(directory_entry&&) noexcept = default;

  _LIBCPP_INLINE_VISIBILITY
  void assign(_Path const& __p) {
    __p_ = __p;
    error_code __ec;
    __refresh(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  void assign(_Path const& __p, error_code& __ec) {
    __p_ = __p;
    __refresh(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  void replace_filename(_Path const& __p) {
    __p_.replace_filename(__p);
    error_code __ec;
    __refresh(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  void replace_filename(_Path const& __p, error_code& __ec) {
    __p_ = __p_.parent_path() / __p;
    __refresh(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  void refresh() { __refresh(); }

  _LIBCPP_INLINE_VISIBILITY
  void refresh(error_code& __ec) noexcept { __refresh(&__ec); }

  _LIBCPP_INLINE_VISIBILITY
  _Path const& path() const noexcept { return __p_; }

  _LIBCPP_INLINE_VISIBILITY
  operator const _Path&() const noexcept { return __p_; }

  _LIBCPP_INLINE_VISIBILITY
  bool exists() const { return _VSTD_FS::exists(file_status{__get_ft()}); }

  _LIBCPP_INLINE_VISIBILITY
  bool exists(error_code& __ec) const noexcept {
    return _VSTD_FS::exists(file_status{__get_ft(&__ec)});
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_block_file() const { return __get_ft() == file_type::block; }

  _LIBCPP_INLINE_VISIBILITY
  bool is_block_file(error_code& __ec) const noexcept {
    return __get_ft(&__ec) == file_type::block;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_character_file() const { return __get_ft() == file_type::character; }

  _LIBCPP_INLINE_VISIBILITY
  bool is_character_file(error_code& __ec) const noexcept {
    return __get_ft(&__ec) == file_type::character;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_directory() const { return __get_ft() == file_type::directory; }

  _LIBCPP_INLINE_VISIBILITY
  bool is_directory(error_code& __ec) const noexcept {
    return __get_ft(&__ec) == file_type::directory;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_fifo() const { return __get_ft() == file_type::fifo; }

  _LIBCPP_INLINE_VISIBILITY
  bool is_fifo(error_code& __ec) const noexcept {
    return __get_ft(&__ec) == file_type::fifo;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_other() const { return _VSTD_FS::is_other(file_status{__get_ft()}); }

  _LIBCPP_INLINE_VISIBILITY
  bool is_other(error_code& __ec) const noexcept {
    return _VSTD_FS::is_other(file_status{__get_ft(&__ec)});
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_regular_file() const { return __get_ft() == file_type::regular; }

  _LIBCPP_INLINE_VISIBILITY
  bool is_regular_file(error_code& __ec) const noexcept {
    return __get_ft(&__ec) == file_type::regular;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_socket() const { return __get_ft() == file_type::socket; }

  _LIBCPP_INLINE_VISIBILITY
  bool is_socket(error_code& __ec) const noexcept {
    return __get_ft(&__ec) == file_type::socket;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool is_symlink() const { return __get_sym_ft() == file_type::symlink; }

  _LIBCPP_INLINE_VISIBILITY
  bool is_symlink(error_code& __ec) const noexcept {
    return __get_sym_ft(&__ec) == file_type::symlink;
  }
  _LIBCPP_INLINE_VISIBILITY
  uintmax_t file_size() const { return __get_size(); }

  _LIBCPP_INLINE_VISIBILITY
  uintmax_t file_size(error_code& __ec) const noexcept {
    return __get_size(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  uintmax_t hard_link_count() const { return __get_nlink(); }

  _LIBCPP_INLINE_VISIBILITY
  uintmax_t hard_link_count(error_code& __ec) const noexcept {
    return __get_nlink(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  file_time_type last_write_time() const { return __get_write_time(); }

  _LIBCPP_INLINE_VISIBILITY
  file_time_type last_write_time(error_code& __ec) const noexcept {
    return __get_write_time(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  file_status status() const { return __get_status(); }

  _LIBCPP_INLINE_VISIBILITY
  file_status status(error_code& __ec) const noexcept {
    return __get_status(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  file_status symlink_status() const { return __get_symlink_status(); }

  _LIBCPP_INLINE_VISIBILITY
  file_status symlink_status(error_code& __ec) const noexcept {
    return __get_symlink_status(&__ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  bool operator<(directory_entry const& __rhs) const noexcept {
    return __p_ < __rhs.__p_;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool operator==(directory_entry const& __rhs) const noexcept {
    return __p_ == __rhs.__p_;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool operator!=(directory_entry const& __rhs) const noexcept {
    return __p_ != __rhs.__p_;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool operator<=(directory_entry const& __rhs) const noexcept {
    return __p_ <= __rhs.__p_;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool operator>(directory_entry const& __rhs) const noexcept {
    return __p_ > __rhs.__p_;
  }

  _LIBCPP_INLINE_VISIBILITY
  bool operator>=(directory_entry const& __rhs) const noexcept {
    return __p_ >= __rhs.__p_;
  }

private:
  friend class directory_iterator;
  friend class recursive_directory_iterator;
  friend class __dir_stream;

  enum _CacheType : unsigned char {
    _Empty,
    _IterSymlink,
    _IterNonSymlink,
    _RefreshSymlink,
    _RefreshSymlinkUnresolved,
    _RefreshNonSymlink
  };

  struct __cached_data {
    uintmax_t __size_;
    uintmax_t __nlink_;
    file_time_type __write_time_;
    perms __sym_perms_;
    perms __non_sym_perms_;
    file_type __type_;
    _CacheType __cache_type_;

    _LIBCPP_INLINE_VISIBILITY
    __cached_data() noexcept { __reset(); }

    _LIBCPP_INLINE_VISIBILITY
    void __reset() {
      __cache_type_ = _Empty;
      __type_ = file_type::none;
      __sym_perms_ = __non_sym_perms_ = perms::unknown;
      __size_ = __nlink_ = uintmax_t(-1);
      __write_time_ = file_time_type::min();
    }
  };

  _LIBCPP_INLINE_VISIBILITY
  static __cached_data __create_iter_result(file_type __ft) {
    __cached_data __data;
    __data.__type_ = __ft;
    __data.__cache_type_ = [&]() {
      switch (__ft) {
      case file_type::none:
        return _Empty;
      case file_type::symlink:
        return _IterSymlink;
      default:
        return _IterNonSymlink;
      }
    }();
    return __data;
  }

  _LIBCPP_INLINE_VISIBILITY
  void __assign_iter_entry(_Path&& __p, __cached_data __dt) {
    __p_ = std::move(__p);
    __data_ = __dt;
  }

  _LIBCPP_FUNC_VIS
  error_code __do_refresh() noexcept;

  _LIBCPP_INLINE_VISIBILITY
  static bool __is_dne_error(error_code const& __ec) {
    if (!__ec)
      return true;
    switch (static_cast<errc>(__ec.value())) {
    case errc::no_such_file_or_directory:
    case errc::not_a_directory:
      return true;
    default:
      return false;
    }
  }

  _LIBCPP_INLINE_VISIBILITY
  void __handle_error(const char* __msg, error_code* __dest_ec,
                      error_code const& __ec, bool __allow_dne = false) const {
    if (__dest_ec) {
      *__dest_ec = __ec;
      return;
    }
    if (__ec && (!__allow_dne || !__is_dne_error(__ec)))
      __throw_filesystem_error(__msg, __p_, __ec);
  }

  _LIBCPP_INLINE_VISIBILITY
  void __refresh(error_code* __ec = nullptr) {
    __handle_error("in directory_entry::refresh", __ec, __do_refresh(),
                   /*allow_dne*/ true);
  }

  _LIBCPP_INLINE_VISIBILITY
  file_type __get_sym_ft(error_code* __ec = nullptr) const {
    switch (__data_.__cache_type_) {
    case _Empty:
      return __symlink_status(__p_, __ec).type();
    case _IterSymlink:
    case _RefreshSymlink:
    case _RefreshSymlinkUnresolved:
      if (__ec)
        __ec->clear();
      return file_type::symlink;
    case _IterNonSymlink:
    case _RefreshNonSymlink:
      file_status __st(__data_.__type_);
      if (__ec && !_VSTD_FS::exists(__st))
        *__ec = make_error_code(errc::no_such_file_or_directory);
      else if (__ec)
        __ec->clear();
      return __data_.__type_;
    }
    _LIBCPP_UNREACHABLE();
  }

  _LIBCPP_INLINE_VISIBILITY
  file_type __get_ft(error_code* __ec = nullptr) const {
    switch (__data_.__cache_type_) {
    case _Empty:
    case _IterSymlink:
    case _RefreshSymlinkUnresolved:
      return __status(__p_, __ec).type();
    case _IterNonSymlink:
    case _RefreshNonSymlink:
    case _RefreshSymlink: {
      file_status __st(__data_.__type_);
      if (__ec && !_VSTD_FS::exists(__st))
        *__ec = make_error_code(errc::no_such_file_or_directory);
      else if (__ec)
        __ec->clear();
      return __data_.__type_;
    }
    }
    _LIBCPP_UNREACHABLE();
  }

  _LIBCPP_INLINE_VISIBILITY
  file_status __get_status(error_code* __ec = nullptr) const {
    switch (__data_.__cache_type_) {
    case _Empty:
    case _IterNonSymlink:
    case _IterSymlink:
    case _RefreshSymlinkUnresolved:
      return __status(__p_, __ec);
    case _RefreshNonSymlink:
    case _RefreshSymlink:
      return file_status(__get_ft(__ec), __data_.__non_sym_perms_);
    }
    _LIBCPP_UNREACHABLE();
  }

  _LIBCPP_INLINE_VISIBILITY
  file_status __get_symlink_status(error_code* __ec = nullptr) const {
    switch (__data_.__cache_type_) {
    case _Empty:
    case _IterNonSymlink:
    case _IterSymlink:
      return __symlink_status(__p_, __ec);
    case _RefreshNonSymlink:
      return file_status(__get_sym_ft(__ec), __data_.__non_sym_perms_);
    case _RefreshSymlink:
    case _RefreshSymlinkUnresolved:
      return file_status(__get_sym_ft(__ec), __data_.__sym_perms_);
    }
    _LIBCPP_UNREACHABLE();
  }

  _LIBCPP_INLINE_VISIBILITY
  uintmax_t __get_size(error_code* __ec = nullptr) const {
    switch (__data_.__cache_type_) {
    case _Empty:
    case _IterNonSymlink:
    case _IterSymlink:
    case _RefreshSymlinkUnresolved:
      return _VSTD_FS::__file_size(__p_, __ec);
    case _RefreshSymlink:
    case _RefreshNonSymlink: {
      error_code __m_ec;
      file_status __st(__get_ft(&__m_ec));
      __handle_error("in directory_entry::file_size", __ec, __m_ec);
      if (_VSTD_FS::exists(__st) && !_VSTD_FS::is_regular_file(__st)) {
        errc __err_kind = _VSTD_FS::is_directory(__st) ? errc::is_a_directory
                                                       : errc::not_supported;
        __handle_error("in directory_entry::file_size", __ec,
                       make_error_code(__err_kind));
      }
      return __data_.__size_;
    }
    }
    _LIBCPP_UNREACHABLE();
  }

  _LIBCPP_INLINE_VISIBILITY
  uintmax_t __get_nlink(error_code* __ec = nullptr) const {
    switch (__data_.__cache_type_) {
    case _Empty:
    case _IterNonSymlink:
    case _IterSymlink:
    case _RefreshSymlinkUnresolved:
      return _VSTD_FS::__hard_link_count(__p_, __ec);
    case _RefreshSymlink:
    case _RefreshNonSymlink: {
      error_code __m_ec;
      (void)__get_ft(&__m_ec);
      __handle_error("in directory_entry::hard_link_count", __ec, __m_ec);
      return __data_.__nlink_;
    }
    }
    _LIBCPP_UNREACHABLE();
  }

  _LIBCPP_INLINE_VISIBILITY
  file_time_type __get_write_time(error_code* __ec = nullptr) const {
    switch (__data_.__cache_type_) {
    case _Empty:
    case _IterNonSymlink:
    case _IterSymlink:
    case _RefreshSymlinkUnresolved:
      return _VSTD_FS::__last_write_time(__p_, __ec);
    case _RefreshSymlink:
    case _RefreshNonSymlink: {
      error_code __m_ec;
      file_status __st(__get_ft(&__m_ec));
      __handle_error("in directory_entry::last_write_time", __ec, __m_ec);
      if (_VSTD_FS::exists(__st) &&
          __data_.__write_time_ == file_time_type::min())
        __handle_error("in directory_entry::last_write_time", __ec,
                       make_error_code(errc::value_too_large));
      return __data_.__write_time_;
    }
    }
    _LIBCPP_UNREACHABLE();
  }

private:
  _Path __p_;
  __cached_data __data_;
};

class __dir_element_proxy {
public:
  inline _LIBCPP_INLINE_VISIBILITY directory_entry operator*() {
    return _VSTD::move(__elem_);
  }

private:
  friend class directory_iterator;
  friend class recursive_directory_iterator;
  explicit __dir_element_proxy(directory_entry const& __e) : __elem_(__e) {}
  __dir_element_proxy(__dir_element_proxy&& __o)
      : __elem_(_VSTD::move(__o.__elem_)) {}
  directory_entry __elem_;
};

class directory_iterator {
public:
  typedef directory_entry value_type;
  typedef ptrdiff_t difference_type;
  typedef value_type const* pointer;
  typedef value_type const& reference;
  typedef input_iterator_tag iterator_category;

public:
  //ctor & dtor
  directory_iterator() noexcept {}

  explicit directory_iterator(const path& __p)
      : directory_iterator(__p, nullptr) {}

  directory_iterator(const path& __p, directory_options __opts)
      : directory_iterator(__p, nullptr, __opts) {}

  directory_iterator(const path& __p, error_code& __ec)
      : directory_iterator(__p, &__ec) {}

  directory_iterator(const path& __p, directory_options __opts,
                     error_code& __ec)
      : directory_iterator(__p, &__ec, __opts) {}

  directory_iterator(const directory_iterator&) = default;
  directory_iterator(directory_iterator&&) = default;
  directory_iterator& operator=(const directory_iterator&) = default;

  directory_iterator& operator=(directory_iterator&& __o) noexcept {
    // non-default implementation provided to support self-move assign.
    if (this != &__o) {
      __imp_ = _VSTD::move(__o.__imp_);
    }
    return *this;
  }

  ~directory_iterator() = default;

  const directory_entry& operator*() const {
    _LIBCPP_ASSERT(__imp_, "The end iterator cannot be dereferenced");
    return __dereference();
  }

  const directory_entry* operator->() const { return &**this; }

  directory_iterator& operator++() { return __increment(); }

  __dir_element_proxy operator++(int) {
    __dir_element_proxy __p(**this);
    __increment();
    return __p;
  }

  directory_iterator& increment(error_code& __ec) { return __increment(&__ec); }

private:
  inline _LIBCPP_INLINE_VISIBILITY friend bool
  operator==(const directory_iterator& __lhs,
             const directory_iterator& __rhs) noexcept;

  // construct the dir_stream
  _LIBCPP_FUNC_VIS
  directory_iterator(const path&, error_code*,
                     directory_options = directory_options::none);

  _LIBCPP_FUNC_VIS
  directory_iterator& __increment(error_code* __ec = nullptr);

  _LIBCPP_FUNC_VIS
  const directory_entry& __dereference() const;

private:
  shared_ptr<__dir_stream> __imp_;
};

inline _LIBCPP_INLINE_VISIBILITY bool
operator==(const directory_iterator& __lhs,
           const directory_iterator& __rhs) noexcept {
  return __lhs.__imp_ == __rhs.__imp_;
}

inline _LIBCPP_INLINE_VISIBILITY bool
operator!=(const directory_iterator& __lhs,
           const directory_iterator& __rhs) noexcept {
  return !(__lhs == __rhs);
}

// enable directory_iterator range-based for statements
inline _LIBCPP_INLINE_VISIBILITY directory_iterator
begin(directory_iterator __iter) noexcept {
  return __iter;
}

inline _LIBCPP_INLINE_VISIBILITY directory_iterator
end(const directory_iterator&) noexcept {
  return directory_iterator();
}

class recursive_directory_iterator {
public:
  using value_type = directory_entry;
  using difference_type = std::ptrdiff_t;
  using pointer = directory_entry const*;
  using reference = directory_entry const&;
  using iterator_category = std::input_iterator_tag;

public:
  // constructors and destructor
  _LIBCPP_INLINE_VISIBILITY
  recursive_directory_iterator() noexcept : __rec_(false) {}

  _LIBCPP_INLINE_VISIBILITY
  explicit recursive_directory_iterator(
      const path& __p, directory_options __xoptions = directory_options::none)
      : recursive_directory_iterator(__p, __xoptions, nullptr) {}

  _LIBCPP_INLINE_VISIBILITY
  recursive_directory_iterator(const path& __p, directory_options __xoptions,
                               error_code& __ec)
      : recursive_directory_iterator(__p, __xoptions, &__ec) {}

  _LIBCPP_INLINE_VISIBILITY
  recursive_directory_iterator(const path& __p, error_code& __ec)
      : recursive_directory_iterator(__p, directory_options::none, &__ec) {}

  recursive_directory_iterator(const recursive_directory_iterator&) = default;
  recursive_directory_iterator(recursive_directory_iterator&&) = default;

  recursive_directory_iterator&
  operator=(const recursive_directory_iterator&) = default;

  _LIBCPP_INLINE_VISIBILITY
  recursive_directory_iterator&
  operator=(recursive_directory_iterator&& __o) noexcept {
    // non-default implementation provided to support self-move assign.
    if (this != &__o) {
      __imp_ = _VSTD::move(__o.__imp_);
      __rec_ = __o.__rec_;
    }
    return *this;
  }

  ~recursive_directory_iterator() = default;

  _LIBCPP_INLINE_VISIBILITY
  const directory_entry& operator*() const { return __dereference(); }

  _LIBCPP_INLINE_VISIBILITY
  const directory_entry* operator->() const { return &__dereference(); }

  recursive_directory_iterator& operator++() { return __increment(); }

  _LIBCPP_INLINE_VISIBILITY
  __dir_element_proxy operator++(int) {
    __dir_element_proxy __p(**this);
    __increment();
    return __p;
  }

  _LIBCPP_INLINE_VISIBILITY
  recursive_directory_iterator& increment(error_code& __ec) {
    return __increment(&__ec);
  }

  _LIBCPP_FUNC_VIS directory_options options() const;
  _LIBCPP_FUNC_VIS int depth() const;

  _LIBCPP_INLINE_VISIBILITY
  void pop() { __pop(); }

  _LIBCPP_INLINE_VISIBILITY
  void pop(error_code& __ec) { __pop(&__ec); }

  _LIBCPP_INLINE_VISIBILITY
  bool recursion_pending() const { return __rec_; }

  _LIBCPP_INLINE_VISIBILITY
  void disable_recursion_pending() { __rec_ = false; }

private:
  recursive_directory_iterator(const path& __p, directory_options __opt,
                               error_code* __ec);

  _LIBCPP_FUNC_VIS
  const directory_entry& __dereference() const;

  _LIBCPP_FUNC_VIS
  bool __try_recursion(error_code* __ec);

  _LIBCPP_FUNC_VIS
  void __advance(error_code* __ec = nullptr);

  _LIBCPP_FUNC_VIS
  recursive_directory_iterator& __increment(error_code* __ec = nullptr);

  _LIBCPP_FUNC_VIS
  void __pop(error_code* __ec = nullptr);

  inline _LIBCPP_INLINE_VISIBILITY friend bool
  operator==(const recursive_directory_iterator&,
             const recursive_directory_iterator&) noexcept;

  struct __shared_imp;
  shared_ptr<__shared_imp> __imp_;
  bool __rec_;
}; // class recursive_directory_iterator

inline _LIBCPP_INLINE_VISIBILITY bool
operator==(const recursive_directory_iterator& __lhs,
           const recursive_directory_iterator& __rhs) noexcept {
  return __lhs.__imp_ == __rhs.__imp_;
}

_LIBCPP_INLINE_VISIBILITY
inline bool operator!=(const recursive_directory_iterator& __lhs,
                       const recursive_directory_iterator& __rhs) noexcept {
  return !(__lhs == __rhs);
}
// enable recursive_directory_iterator range-based for statements
inline _LIBCPP_INLINE_VISIBILITY recursive_directory_iterator
begin(recursive_directory_iterator __iter) noexcept {
  return __iter;
}

inline _LIBCPP_INLINE_VISIBILITY recursive_directory_iterator
end(const recursive_directory_iterator&) noexcept {
  return recursive_directory_iterator();
}

_LIBCPP_END_NAMESPACE_FILESYSTEM

#endif // !_LIBCPP_CXX03_LANG

_LIBCPP_POP_MACROS

#endif // _LIBCPP_FILESYSTEM
#endif
