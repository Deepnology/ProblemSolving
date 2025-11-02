#pragma once
// ---------------------------------------------------------
// UnifiedHookHooks.h
// Cross-platform function-entry tracing glue.
//   Linux (GCC/Clang)           : -finstrument-functions
//   Windows x64 (clang-cl)      : /clang:-finstrument-functions
//   Windows x86 (MSVC cl)       : /Gh /GH  (naked _penter/_pexit)
// ---------------------------------------------------------

#include <limits.h> // INT_MAX

// ---- Platform probes ----
#if defined(_WIN32)
  #define HH_OS_WINDOWS 1
#else
  #define HH_OS_WINDOWS 0
#endif

#if defined(__linux__)
  #define HH_OS_LINUX 1
#else
  #define HH_OS_LINUX 0
#endif

// ---- no-instrument function attribute (where supported) ----
#if defined(__clang__) || defined(__GNUC__)
  #define HH_ATTR_NOINSTR __attribute__((no_instrument_function))
#else
  #define HH_ATTR_NOINSTR
#endif

// ---- C-linkage helpers (hooks must be unmangled) ----
#ifdef __cplusplus
  #define HH_EXTERN_C_BEGIN extern "C" {
  #define HH_EXTERN_C_END   }
  #define HH_NOEXCEPT       noexcept
  // In C++ we can put attribute before return type
  #define HH_DECL(ret)      HH_ATTR_NOINSTR ret
#else
  #define HH_EXTERN_C_BEGIN
  #define HH_EXTERN_C_END
  #define HH_NOEXCEPT       /*nothing*/
  // In C, attribute must follow return type
  #define HH_DECL(ret)      ret HH_ATTR_NOINSTR
#endif

// ---- Public gating API (same on all platforms) ----
HH_EXTERN_C_BEGIN

// Start logging in *this thread*.
// The first callee after HH_BeginTrace() is relative depth 0.
// Only frames with 0 <= relDepth <= maxRelativeDepth are emitted.
// Nestable (LIFO). Pass INT_MAX for "no limit".
HH_DECL(void) HH_BeginTrace(int maxRelativeDepth /*pass INT_MAX for 'no limit'*/) HH_NOEXCEPT;

// Stop logging in this thread (pop one gate).
HH_DECL(void) HH_EndTrace(void) HH_NOEXCEPT;

HH_EXTERN_C_END

// ---- Instrumentation entry points (platform-dependent) ----
//
// Linux / Windows (clang-cl): -finstrument-functions
#if (HH_OS_LINUX) || (HH_OS_WINDOWS && defined(__clang__))
  HH_EXTERN_C_BEGIN
  HH_DECL(void) __cyg_profile_func_enter(void* this_fn, void* call_site) HH_NOEXCEPT;
  HH_DECL(void) __cyg_profile_func_exit (void* this_fn, void* call_site) HH_NOEXCEPT;
  HH_EXTERN_C_END
#endif

// Windows x86 MSVC: /Gh /GH
#if (HH_OS_WINDOWS) && defined(_MSC_VER) && !defined(__clang__) && defined(_M_IX86)
  HH_EXTERN_C_BEGIN
  // MSVC inserts calls to these when /Gh /GH is enabled for *your* TUs.
  __declspec(naked) void __cdecl _penter();
  __declspec(naked) void __cdecl _pexit();
  HH_EXTERN_C_END
#endif
