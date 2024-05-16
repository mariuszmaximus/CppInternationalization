#include <iostream>
#include <cstdlib>
#include <libintl.h>

#if WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#define _(STRING) gettext(STRING)

static void setup_i18n(const std::string_view locale) {
#if WIN32
  // LocaleNameToLCID requires a LPCWSTR so we need to convert from char to wchar_t
  const auto wStringSize = MultiByteToWideChar(CP_UTF8, 0, locale.data(), static_cast<int>(locale.length()), nullptr, 0);
  std::wstring localeName;
  localeName.reserve(wStringSize);
  MultiByteToWideChar(CP_UTF8, 0, locale.data(), static_cast<int>(locale.length()), localeName.data(), wStringSize);

  _configthreadlocale(_DISABLE_PER_THREAD_LOCALE);
  const auto localeId = LocaleNameToLCID(localeName.c_str(), LOCALE_ALLOW_NEUTRAL_NAMES);
  SetThreadLocale(localeId);
#else
  setlocale(LC_MESSAGES, locale.data());
#endif

  bindtextdomain(GETTEXT_DOMAIN, GETTEXT_OUTPUT_DIR);
  bind_textdomain_codeset(GETTEXT_DOMAIN, "UTF-8");
  textdomain(GETTEXT_DOMAIN);
}

int main() {
  setup_i18n("de");

  std::cout << _("Hello World!") << std::endl;

  return EXIT_SUCCESS;
}
