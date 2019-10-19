#pragma once

namespace sanelli
{

class console_colour
{
public:
#if defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__unix__)
   static constexpr const char *reset() noexcept { return "\033[0m"; }
   static constexpr const char *black() noexcept { return "\033[30m"; }
   static constexpr const char *red() noexcept { return "\033[31m"; }
   static constexpr const char *green() noexcept { return "\033[32m"; }
   static constexpr const char *yellow() noexcept { return "\033[33m"; }
   static constexpr const char *blue() noexcept { return "\033[34m"; }
   static constexpr const char *magenta() noexcept { return "\033[35m"; }
   static constexpr const char *cyan() noexcept { return "\033[36m"; }
   static constexpr const char *white() noexcept { return "\033[37m"; }
   static constexpr const char *bold_black() noexcept { return "\033[1m\033[30m"; }
   static constexpr const char *bold_red() noexcept { return "\033[1m\033[31m"; }
   static constexpr const char *bold_green() noexcept { return "\033[1m\033[32m"; }
   static constexpr const char *bold_yellow() noexcept { return "\033[1m\033[33m"; }
   static constexpr const char *bold_blue() noexcept { return "\033[1m\033[34m"; }
   static constexpr const char *bold_magenta() noexcept { return "\033[1m\033[35m"; }
   static constexpr const char *bold_cyan() noexcept { return "\033[1m\033[36m"; }
   static constexpr const char *bold_white() noexcept { return "\033[1m\033[37m"; }
#else
   static constexpr const char *console_colour::reset() noexcept { return ""; }
   static constexpr const char *console_colour::black() noexcept { return ""; }
   static constexpr const char *console_colour::red() noexcept { return ""; }
   static constexpr const char *console_colour::green() noexcept { return ""; }
   static constexpr const char *console_colour::yellow() noexcept { return ""; }
   static constexpr const char *console_colour::blue() noexcept { return ""; }
   static constexpr const char *console_colour::magenta() noexcept { return ""; }
   static constexpr const char *console_colour::cyan() noexcept { return ""; }
   static constexpr const char *console_colour::white() noexcept { return ""; }
   static constexpr const char *console_colour::bold_black() noexcept { return ""; }
   static constexpr const char *console_colour::bold_red() noexcept { return ""; }
   static constexpr const char *console_colour::bold_green() noexcept { return ""; }
   static constexpr const char *console_colour::bold_yellow() noexcept { return ""; }
   static constexpr const char *console_colour::bold_blue() noexcept { return ""; }
   static constexpr const char *console_colour::bold_magenta() noexcept { return ""; }
   static constexpr const char *console_colour::bold_cyan() noexcept { return ""; }
   static constexpr const char *console_colour::bold_white() noexcept { return ""; }
#endif
};

} // namespace sanelli