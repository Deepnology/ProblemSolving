#pragma once

// -------------------------------
//   MSVC x86 only (/Gh, /GH)
// -------------------------------
#if !defined(_M_IX86)
#  error "/Gh and /GH (and naked _penter/_pexit) are only supported for 32-bit (x86) MSVC."
#endif

#include <windows.h>

extern "C" {

// Injected by the compiler at function entry when you build TUs with /Gh
__declspec(naked) void __cdecl _penter();

// Injected by the compiler at function exit when you build TUs with /GH
__declspec(naked) void __cdecl _pexit();

// -------- Region-gating API (call from your code) --------
// Start logging in the current thread. Children of the current frame are
// logged with relative depth 0; grandchildren depth 1; etc.
// You can nest calls; each Begin must be matched with an End in LIFO order.
void __cdecl HH_BeginTrace(int maxRelativeDepth /* = INT_MAX */);

// Stop logging in the current thread (pop one gate).
void __cdecl HH_EndTrace();
}
