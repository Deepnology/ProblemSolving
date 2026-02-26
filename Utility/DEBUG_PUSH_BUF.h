#ifndef DEBUG_PUSH_BUF_INDEXED_H_
#define DEBUG_PUSH_BUF_INDEXED_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef _MSC_VER
#  include <sal.h>
#endif

/* ========================= common small helpers ========================= */

#define DEBUG__PB_MKNAME2(a,b) a##b
#define DEBUG__PB_MKNAME(a,b)  DEBUG__PB_MKNAME2(a,b)

#ifdef _MSC_VER
#  define DEBUG__PB_ANALYZE_ASSUME(x) _Analysis_assume_(x)
#else
#  define DEBUG__PB_ANALYZE_ASSUME(x) ((void)0)
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define DEBUG__PB_ERR(msg) \
    fprintf(stderr, "%s:%d.%s: %s\n", __FILE__, __LINE__, __func__, (msg))
#else
#define DEBUG__PB_ERR(msg) \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, (msg))
#endif

#define DEBUG__PB_BUFDECL(name, bufLenExpr) \
    char name[((size_t)(bufLenExpr) > 0) ? (size_t)(bufLenExpr) : 1] = {0}

#define DEBUG__PB_SLOT_OK(si_expr) ((size_t)(si_expr) < (size_t)(DEBUG_PUSH_BUF_SLOTS_))

#define DEBUG__PB_HAS_ELEM_ROOM_SI(si_expr) \
    (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] < (size_t)(DEBUG_PUSH_BUF_LENS_CAP_))

#define DEBUG__PB_HAS_ROOM_SI(si_expr, add_len_expr) \
    ( (DEBUG_PUSH_BUF_CAP_ > 0) && \
      ((DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] + (size_t)(add_len_expr)) < (size_t)DEBUG_PUSH_BUF_CAP_) )

#define DEBUG__PB_TERM_SI(si_expr) \
    do { \
        if (DEBUG_PUSH_BUF_CAP_ > 0) { \
            if (DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] >= (size_t)DEBUG_PUSH_BUF_CAP_) \
                DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] = (size_t)DEBUG_PUSH_BUF_CAP_ - 1; \
            DEBUG_PUSH_BUF_[(size_t)(si_expr)][DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]] = '\0'; \
        } \
    } while (0)

/* ========================= initialization ========================= */
/*
slotCount : number of independent buffers ("instances")
bufCap    : bytes per buffer
maxElems  : max elements per buffer
*/
#define DEBUG_PUSH_BUF_INIT_I(slotCount, bufCap, maxElems) \
    char   DEBUG_PUSH_BUF_[(slotCount)][(bufCap)] = {{0}}; \
    size_t DEBUG_PUSH_BUF_POS_[(slotCount)] = {0}; \
    const size_t DEBUG_PUSH_BUF_CAP_ = (size_t)(bufCap); \
    const size_t DEBUG_PUSH_BUF_SLOTS_ = (size_t)(slotCount); \
    size_t DEBUG_PUSH_BUF_LENS_[(slotCount)][(maxElems)] = {{0}}; \
    const size_t DEBUG_PUSH_BUF_LENS_CAP_ = (size_t)(maxElems); \
    size_t DEBUG_PUSH_BUF_N_[(slotCount)] = {0}

/* ===================== internal offset helpers (SI / SI+IDX) ===================== */

#define DEBUG__PB_OFFSET_ELEM_SI(si_expr, idx_expr, off_out, ok_out) \
    do { \
        size_t __dbgpb_k = 0; \
        size_t __dbgpb_off = 0; \
        (ok_out) = 0; \
        (off_out) = 0; \
        if (DEBUG__PB_SLOT_OK((si_expr)) && (size_t)(idx_expr) < DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]) { \
            for (__dbgpb_k = 0; __dbgpb_k < (size_t)(idx_expr); ++__dbgpb_k) \
                __dbgpb_off += DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][__dbgpb_k]; \
            (off_out) = __dbgpb_off; \
            (ok_out) = 1; \
        } \
    } while (0)

#define DEBUG__PB_OFFSET_INS_SI(si_expr, idx_expr, off_out, ok_out) \
    do { \
        size_t __dbgpb_k = 0; \
        size_t __dbgpb_off = 0; \
        (ok_out) = 0; \
        (off_out) = 0; \
        if (DEBUG__PB_SLOT_OK((si_expr)) && (size_t)(idx_expr) <= DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]) { \
            for (__dbgpb_k = 0; __dbgpb_k < (size_t)(idx_expr); ++__dbgpb_k) \
                __dbgpb_off += DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][__dbgpb_k]; \
            (off_out) = __dbgpb_off; \
            (ok_out) = 1; \
        } \
    } while (0)

/* ===================== internal lens/byte shift helpers ===================== */

#define DEBUG__PB_LENS_SHIFT_RIGHT_SI(si_expr, idx_expr) \
    do { \
        size_t __dbgpb_n = DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]; \
        size_t __dbgpb_idx = (size_t)(idx_expr); \
        if (__dbgpb_n > __dbgpb_idx) { \
            memmove(DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + __dbgpb_idx + 1, \
                    DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + __dbgpb_idx, \
                    (__dbgpb_n - __dbgpb_idx) * sizeof(DEBUG_PUSH_BUF_LENS_[0][0])); \
        } \
    } while (0)

#define DEBUG__PB_LENS_SHIFT_LEFT_SI(si_expr, idx_expr) \
    do { \
        size_t __dbgpb_n = DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]; \
        size_t __dbgpb_idx = (size_t)(idx_expr); \
        if (__dbgpb_n > __dbgpb_idx + 1) { \
            memmove(DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + __dbgpb_idx, \
                    DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + __dbgpb_idx + 1, \
                    (__dbgpb_n - __dbgpb_idx - 1) * sizeof(DEBUG_PUSH_BUF_LENS_[0][0])); \
        } \
    } while (0)

#define DEBUG__PB_BYTES_SHIFT_RIGHT_SI(si_expr, off_expr, delta_expr) \
    do { \
        size_t __dbgpb_off = (size_t)(off_expr); \
        size_t __dbgpb_delta = (size_t)(delta_expr); \
        size_t __dbgpb_pos = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        if (__dbgpb_delta > 0 && __dbgpb_pos > __dbgpb_off) { \
            memmove(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off + __dbgpb_delta, \
                    DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off, \
                    __dbgpb_pos - __dbgpb_off); \
        } \
    } while (0)

#define DEBUG__PB_BYTES_SHIFT_LEFT_SI(si_expr, off_expr, delta_expr) \
    do { \
        size_t __dbgpb_off = (size_t)(off_expr); \
        size_t __dbgpb_delta = (size_t)(delta_expr); \
        size_t __dbgpb_pos = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        size_t __dbgpb_tail_off = __dbgpb_off + __dbgpb_delta; \
        if (__dbgpb_tail_off < __dbgpb_pos) { \
            memmove(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off, \
                    DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_tail_off, \
                    __dbgpb_pos - __dbgpb_tail_off); \
        } \
    } while (0)

/* ===================== internal core ops (SI / SI+IDX) ===================== */

/* ---- clear ---- */
#define DEBUG__PB_CLR_SI(si_expr) \
    do { \
        if (DEBUG_PUSH_BUF_CAP_ > 0) memset(DEBUG_PUSH_BUF_[(size_t)(si_expr)], 0, DEBUG_PUSH_BUF_CAP_); \
        memset(DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)], 0, DEBUG_PUSH_BUF_LENS_CAP_ * sizeof(DEBUG_PUSH_BUF_LENS_[0][0])); \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] = 0; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] = 0; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

/* ---- at/span ---- */
#define DEBUG__PB_AT_SI_IDX(si_expr, idx_expr, out_ptr, out_len) \
    do { \
        size_t __dbgpb_off = 0; int __dbgpb_ok = 0; \
        DEBUG__PB_OFFSET_ELEM_SI((si_expr), (idx_expr), __dbgpb_off, __dbgpb_ok); \
        if (!__dbgpb_ok) { (out_ptr) = NULL; (out_len) = 0; } \
        else { \
            (out_ptr) = DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off; \
            (out_len) = DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)]; \
        } \
    } while (0)

/* ---- pop front/back (no public macro call) ---- */
#define DEBUG__PB_POP_FRONT_SI(si_expr) \
    do { \
        if (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] == 0) break; \
        size_t __dbgpb_len = DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][0]; \
        if (DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] > __dbgpb_len) { \
            memmove(DEBUG_PUSH_BUF_[(size_t)(si_expr)], \
                    DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_len, \
                    DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] - __dbgpb_len); \
        } \
        if (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] > 1) { \
            memmove(DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)], \
                    DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + 1, \
                    (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] - 1) * sizeof(DEBUG_PUSH_BUF_LENS_[0][0])); \
        } \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]--; \
        if (__dbgpb_len > DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]) __dbgpb_len = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] -= __dbgpb_len; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

#define DEBUG__PB_POP_BACK_SI(si_expr) \
    do { \
        if (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] == 0) break; \
        size_t __dbgpb_len = DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] - 1]; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]--; \
        if (__dbgpb_len > DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]) __dbgpb_len = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] -= __dbgpb_len; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

/* ---- push back/front STR (no public macro call) ---- */
#define DEBUG__PB_PUSH_BACK_STR_SI(si_expr, cstr_expr) \
    do { \
        const char* __dbgpb_s = (cstr_expr); if (!__dbgpb_s) __dbgpb_s = ""; \
        size_t __dbgpb_len = strlen(__dbgpb_s); \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI((si_expr))) { DEBUG__PB_ERR("push_back_str: elem cap"); break; } \
        if (!DEBUG__PB_HAS_ROOM_SI((si_expr), __dbgpb_len)) { DEBUG__PB_ERR("push_back_str: buf cap"); break; } \
        if (__dbgpb_len > 0) memcpy(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)], __dbgpb_s, __dbgpb_len); \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++] = __dbgpb_len; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_len; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

#define DEBUG__PB_PUSH_FRONT_STR_SI(si_expr, cstr_expr) \
    do { \
        const char* __dbgpb_s = (cstr_expr); if (!__dbgpb_s) __dbgpb_s = ""; \
        size_t __dbgpb_len = strlen(__dbgpb_s); \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI((si_expr))) { DEBUG__PB_ERR("push_front_str: elem cap"); break; } \
        if (!DEBUG__PB_HAS_ROOM_SI((si_expr), __dbgpb_len)) { DEBUG__PB_ERR("push_front_str: buf cap"); break; } \
        size_t __dbgpb_pos = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        if (__dbgpb_pos > 0 && __dbgpb_len > 0) { \
            memmove(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_len, DEBUG_PUSH_BUF_[(size_t)(si_expr)], __dbgpb_pos); \
        } \
        if (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] > 0) { \
            memmove(DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + 1, DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)], \
                    DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] * sizeof(DEBUG_PUSH_BUF_LENS_[0][0])); \
        } \
        if (__dbgpb_len > 0) memcpy(DEBUG_PUSH_BUF_[(size_t)(si_expr)], __dbgpb_s, __dbgpb_len); \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][0] = __dbgpb_len; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_len; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

/* ---- direct-to-destination PUSH BACK FMT ---- */
#define DEBUG__PB_PUSH_BACK_FMT_SI(si_expr, fmt, ...) \
    do { \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI((si_expr))) { DEBUG__PB_ERR("push_back_fmt: elem cap"); break; } \
        if (DEBUG_PUSH_BUF_CAP_ == 0 || DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] >= DEBUG_PUSH_BUF_CAP_ - 1) { \
            DEBUG__PB_ERR("push_back_fmt: buf cap"); break; \
        } \
        size_t __dbgpb_pos0 = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        size_t __dbgpb_avail = (DEBUG_PUSH_BUF_CAP_ - 1) - __dbgpb_pos0; \
        int __dbgpb_n = snprintf(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_pos0, __dbgpb_avail + 1, (fmt), ##__VA_ARGS__); \
        if (__dbgpb_n < 0) { fprintf(stderr, "%s:%d: push_back_fmt: snprintf failed\n", __FILE__, __LINE__); break; } \
        size_t __dbgpb_written = ((size_t)__dbgpb_n <= __dbgpb_avail) ? (size_t)__dbgpb_n : __dbgpb_avail; \
        if ((size_t)__dbgpb_n > __dbgpb_avail) { \
            fprintf(stderr, "%s:%d: push_back_fmt: truncated (need=%d avail=%zu)\n", __FILE__, __LINE__, __dbgpb_n, __dbgpb_avail); \
        } \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_written; \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++] = __dbgpb_written; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

/* ---- direct-to-destination PUSH FRONT FMT (two-pass) ---- */
#define DEBUG__PB_PUSH_FRONT_FMT_SI(si_expr, fmt, ...) \
    do { \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI((si_expr))) { DEBUG__PB_ERR("push_front_fmt: elem cap"); break; } \
        if (DEBUG_PUSH_BUF_CAP_ == 0) { DEBUG__PB_ERR("push_front_fmt: buf cap"); break; } \
        size_t __dbgpb_pos0 = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        size_t __dbgpb_avail = (__dbgpb_pos0 < DEBUG_PUSH_BUF_CAP_) ? ((DEBUG_PUSH_BUF_CAP_ - 1) - __dbgpb_pos0) : 0; \
        if (__dbgpb_avail == 0) { DEBUG__PB_ERR("push_front_fmt: buf cap"); break; } \
        int __dbgpb_need_i = snprintf(NULL, 0, (fmt), ##__VA_ARGS__); \
        if (__dbgpb_need_i < 0) { fprintf(stderr, "%s:%d: push_front_fmt: probe failed\n", __FILE__, __LINE__); break; } \
        size_t __dbgpb_wlen = ((size_t)__dbgpb_need_i <= __dbgpb_avail) ? (size_t)__dbgpb_need_i : __dbgpb_avail; \
        if ((size_t)__dbgpb_need_i > __dbgpb_avail) { \
            fprintf(stderr, "%s:%d: push_front_fmt: truncated (need=%d avail=%zu)\n", __FILE__, __LINE__, __dbgpb_need_i, __dbgpb_avail); \
        } \
        if (__dbgpb_pos0 > 0 && __dbgpb_wlen > 0) { \
            memmove(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_wlen, DEBUG_PUSH_BUF_[(size_t)(si_expr)], __dbgpb_pos0); \
        } \
        if (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] > 0) { \
            memmove(DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + 1, DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)], \
                    DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] * sizeof(DEBUG_PUSH_BUF_LENS_[0][0])); \
        } \
        if (__dbgpb_wlen > 0) { \
            int __dbgpb_n2 = snprintf(DEBUG_PUSH_BUF_[(size_t)(si_expr)], __dbgpb_wlen + 1, (fmt), ##__VA_ARGS__); \
            if (__dbgpb_n2 < 0) fprintf(stderr, "%s:%d: push_front_fmt: snprintf failed (2nd)\n", __FILE__, __LINE__); \
        } \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][0] = __dbgpb_wlen; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_wlen; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

/* ---- SET/INSERT/ERASE internal helpers (already safe) ---- */
#define DEBUG__PB_SET_STR_SI_IDX(si_expr, idx_expr, cstr_expr) \
    do { \
        const char* __dbgpb_s = (cstr_expr); if (!__dbgpb_s) __dbgpb_s = ""; \
        size_t __dbgpb_newlen = strlen(__dbgpb_s); \
        size_t __dbgpb_off = 0; int __dbgpb_ok = 0; \
        DEBUG__PB_OFFSET_ELEM_SI((si_expr), (idx_expr), __dbgpb_off, __dbgpb_ok); \
        if (!__dbgpb_ok) { DEBUG__PB_ERR("set_str: bad idx"); break; } \
        size_t __dbgpb_oldlen = DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)]; \
        if (__dbgpb_newlen > __dbgpb_oldlen) { \
            size_t __dbgpb_grow = __dbgpb_newlen - __dbgpb_oldlen; \
            if (!DEBUG__PB_HAS_ROOM_SI((si_expr), __dbgpb_grow)) { DEBUG__PB_ERR("set_str: no room"); break; } \
        } \
        if (__dbgpb_newlen > __dbgpb_oldlen) \
            DEBUG__PB_BYTES_SHIFT_RIGHT_SI((si_expr), __dbgpb_off + __dbgpb_oldlen, __dbgpb_newlen - __dbgpb_oldlen); \
        else if (__dbgpb_oldlen > __dbgpb_newlen) \
            DEBUG__PB_BYTES_SHIFT_LEFT_SI((si_expr), __dbgpb_off + __dbgpb_newlen, __dbgpb_oldlen - __dbgpb_newlen); \
        if (__dbgpb_newlen > 0) memcpy(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off, __dbgpb_s, __dbgpb_newlen); \
        if (__dbgpb_newlen >= __dbgpb_oldlen) DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += (__dbgpb_newlen - __dbgpb_oldlen); \
        else DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] -= (__dbgpb_oldlen - __dbgpb_newlen); \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)] = __dbgpb_newlen; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

#define DEBUG__PB_SET_FMT_SI_IDX(si_expr, idx_expr, fmt, ...) \
    do { \
        int __dbgpb_need_i = snprintf(NULL, 0, (fmt), ##__VA_ARGS__); \
        if (__dbgpb_need_i < 0) { fprintf(stderr, "%s:%d: set_fmt: probe failed\n", __FILE__, __LINE__); break; } \
        size_t __dbgpb_newlen = (size_t)__dbgpb_need_i; \
        size_t __dbgpb_off = 0; int __dbgpb_ok = 0; \
        DEBUG__PB_OFFSET_ELEM_SI((si_expr), (idx_expr), __dbgpb_off, __dbgpb_ok); \
        if (!__dbgpb_ok) { DEBUG__PB_ERR("set_fmt: bad idx"); break; } \
        size_t __dbgpb_oldlen = DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)]; \
        if (__dbgpb_newlen > __dbgpb_oldlen) { \
            size_t __dbgpb_grow = __dbgpb_newlen - __dbgpb_oldlen; \
            if (!DEBUG__PB_HAS_ROOM_SI((si_expr), __dbgpb_grow)) { DEBUG__PB_ERR("set_fmt: no room"); break; } \
        } \
        if (__dbgpb_newlen > __dbgpb_oldlen) \
            DEBUG__PB_BYTES_SHIFT_RIGHT_SI((si_expr), __dbgpb_off + __dbgpb_oldlen, __dbgpb_newlen - __dbgpb_oldlen); \
        else if (__dbgpb_oldlen > __dbgpb_newlen) \
            DEBUG__PB_BYTES_SHIFT_LEFT_SI((si_expr), __dbgpb_off + __dbgpb_newlen, __dbgpb_oldlen - __dbgpb_newlen); \
        if (__dbgpb_newlen > 0) { \
            int __dbgpb_n2 = snprintf(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off, __dbgpb_newlen + 1, (fmt), ##__VA_ARGS__); \
            if (__dbgpb_n2 < 0 || (size_t)__dbgpb_n2 != __dbgpb_newlen) \
                fprintf(stderr, "%s:%d: set_fmt: snprintf failed (2nd)\n", __FILE__, __LINE__); \
        } \
        if (__dbgpb_newlen >= __dbgpb_oldlen) DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += (__dbgpb_newlen - __dbgpb_oldlen); \
        else DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] -= (__dbgpb_oldlen - __dbgpb_newlen); \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)] = __dbgpb_newlen; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

#define DEBUG__PB_INSERT_STR_SI_IDX(si_expr, idx_expr, cstr_expr) \
    do { \
        const char* __dbgpb_s = (cstr_expr); if (!__dbgpb_s) __dbgpb_s = ""; \
        size_t __dbgpb_len = strlen(__dbgpb_s); \
        if (!DEBUG__PB_HAS_ROOM_SI((si_expr), __dbgpb_len)) { DEBUG__PB_ERR("insert_str: no room"); break; } \
        size_t __dbgpb_off = 0; int __dbgpb_ok = 0; \
        DEBUG__PB_OFFSET_INS_SI((si_expr), (idx_expr), __dbgpb_off, __dbgpb_ok); \
        if (!__dbgpb_ok) { DEBUG__PB_ERR("insert_str: bad idx"); break; } \
        DEBUG__PB_BYTES_SHIFT_RIGHT_SI((si_expr), __dbgpb_off, __dbgpb_len); \
        DEBUG__PB_LENS_SHIFT_RIGHT_SI((si_expr), (idx_expr)); \
        if (__dbgpb_len > 0) memcpy(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off, __dbgpb_s, __dbgpb_len); \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)] = __dbgpb_len; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_len; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

#define DEBUG__PB_INSERT_FMT_SI_IDX(si_expr, idx_expr, fmt, ...) \
    do { \
        int __dbgpb_need_i = snprintf(NULL, 0, (fmt), ##__VA_ARGS__); \
        if (__dbgpb_need_i < 0) { fprintf(stderr, "%s:%d: insert_fmt: probe failed\n", __FILE__, __LINE__); break; } \
        size_t __dbgpb_len = (size_t)__dbgpb_need_i; \
        if (!DEBUG__PB_HAS_ROOM_SI((si_expr), __dbgpb_len)) { DEBUG__PB_ERR("insert_fmt: no room"); break; } \
        size_t __dbgpb_off = 0; int __dbgpb_ok = 0; \
        DEBUG__PB_OFFSET_INS_SI((si_expr), (idx_expr), __dbgpb_off, __dbgpb_ok); \
        if (!__dbgpb_ok) { DEBUG__PB_ERR("insert_fmt: bad idx"); break; } \
        DEBUG__PB_BYTES_SHIFT_RIGHT_SI((si_expr), __dbgpb_off, __dbgpb_len); \
        DEBUG__PB_LENS_SHIFT_RIGHT_SI((si_expr), (idx_expr)); \
        if (__dbgpb_len > 0) { \
            int __dbgpb_n2 = snprintf(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_off, __dbgpb_len + 1, (fmt), ##__VA_ARGS__); \
            if (__dbgpb_n2 < 0 || (size_t)__dbgpb_n2 != __dbgpb_len) \
                fprintf(stderr, "%s:%d: insert_fmt: snprintf failed (2nd)\n", __FILE__, __LINE__); \
        } \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)] = __dbgpb_len; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_len; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

#define DEBUG__PB_ERASE_SI_IDX(si_expr, idx_expr) \
    do { \
        size_t __dbgpb_off = 0; int __dbgpb_ok = 0; \
        DEBUG__PB_OFFSET_ELEM_SI((si_expr), (idx_expr), __dbgpb_off, __dbgpb_ok); \
        if (!__dbgpb_ok) { DEBUG__PB_ERR("erase: bad idx"); break; } \
        size_t __dbgpb_len = DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][(size_t)(idx_expr)]; \
        DEBUG__PB_BYTES_SHIFT_LEFT_SI((si_expr), __dbgpb_off, __dbgpb_len); \
        DEBUG__PB_LENS_SHIFT_LEFT_SI((si_expr), (idx_expr)); \
        if (__dbgpb_len > DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]) __dbgpb_len = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] -= __dbgpb_len; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]--; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

/* ---- argv as ONE element ---- */
#define DEBUG__PB_PUSH_BACK_ARGV_SI(si_expr, argc, argv) \
    do { \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI((si_expr))) { DEBUG__PB_ERR("push_back_argv: elem cap"); break; } \
        size_t __dbgpb_before = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        for (int __dbgpb_i = 0; __dbgpb_i < (argc); ++__dbgpb_i) { \
            const char* __dbgpb_arg = (argv)[__dbgpb_i]; if (!__dbgpb_arg) __dbgpb_arg = ""; \
            size_t __dbgpb_len = strlen(__dbgpb_arg); \
            if (DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] >= DEBUG_PUSH_BUF_CAP_ - 1) break; \
            size_t __dbgpb_avail = (DEBUG_PUSH_BUF_CAP_ - 1) - DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
            if (__dbgpb_len > __dbgpb_avail) __dbgpb_len = __dbgpb_avail; \
            if (__dbgpb_len > 0) memcpy(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)], __dbgpb_arg, __dbgpb_len); \
            DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_len; \
            if (__dbgpb_i < (argc) - 1 && DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] < DEBUG_PUSH_BUF_CAP_ - 1) \
                DEBUG_PUSH_BUF_[(size_t)(si_expr)][DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]++] = ' '; \
        } \
        DEBUG__PB_TERM_SI((si_expr)); \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++] = \
            (DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] - __dbgpb_before); \
    } while (0)

#define DEBUG__PB_PUSH_FRONT_ARGV_SI(si_expr, argc, argv) \
    do { \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI((si_expr))) { DEBUG__PB_ERR("push_front_argv: elem cap"); break; } \
        size_t __dbgpb_need = 0; \
        for (int __dbgpb_i = 0; __dbgpb_i < (argc); ++__dbgpb_i) { \
            const char* __dbgpb_arg = (argv)[__dbgpb_i]; if (!__dbgpb_arg) __dbgpb_arg = ""; \
            __dbgpb_need += strlen(__dbgpb_arg); \
            if (__dbgpb_i < (argc) - 1) __dbgpb_need += 1; \
        } \
        size_t __dbgpb_pos0 = DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)]; \
        size_t __dbgpb_avail = (__dbgpb_pos0 < DEBUG_PUSH_BUF_CAP_) ? ((DEBUG_PUSH_BUF_CAP_ - 1) - __dbgpb_pos0) : 0; \
        if (__dbgpb_avail == 0) { DEBUG__PB_ERR("push_front_argv: buf cap"); break; } \
        size_t __dbgpb_wlen = (__dbgpb_need <= __dbgpb_avail) ? __dbgpb_need : __dbgpb_avail; \
        if (__dbgpb_pos0 > 0 && __dbgpb_wlen > 0) \
            memmove(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_wlen, DEBUG_PUSH_BUF_[(size_t)(si_expr)], __dbgpb_pos0); \
        if (DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] > 0) \
            memmove(DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)] + 1, DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)], \
                    DEBUG_PUSH_BUF_N_[(size_t)(si_expr)] * sizeof(DEBUG_PUSH_BUF_LENS_[0][0])); \
        size_t __dbgpb_pos = 0; \
        for (int __dbgpb_i2 = 0; __dbgpb_i2 < (argc) && __dbgpb_pos < __dbgpb_wlen; ++__dbgpb_i2) { \
            const char* __dbgpb_arg2 = (argv)[__dbgpb_i2]; if (!__dbgpb_arg2) __dbgpb_arg2 = ""; \
            size_t __dbgpb_len2 = strlen(__dbgpb_arg2); \
            size_t __dbgpb_rem = __dbgpb_wlen - __dbgpb_pos; \
            if (__dbgpb_len2 > __dbgpb_rem) __dbgpb_len2 = __dbgpb_rem; \
            if (__dbgpb_len2 > 0) { \
                memcpy(DEBUG_PUSH_BUF_[(size_t)(si_expr)] + __dbgpb_pos, __dbgpb_arg2, __dbgpb_len2); \
                __dbgpb_pos += __dbgpb_len2; \
            } \
            if (__dbgpb_i2 < (argc) - 1 && __dbgpb_pos < __dbgpb_wlen) \
                DEBUG_PUSH_BUF_[(size_t)(si_expr)][__dbgpb_pos++] = ' '; \
        } \
        DEBUG_PUSH_BUF_LENS_[(size_t)(si_expr)][0] = __dbgpb_wlen; \
        DEBUG_PUSH_BUF_N_[(size_t)(si_expr)]++; \
        DEBUG_PUSH_BUF_POS_[(size_t)(si_expr)] += __dbgpb_wlen; \
        DEBUG__PB_TERM_SI((si_expr)); \
    } while (0)

/* ---- time as one element (uses *_STR internal, no nesting issues) ---- */
#ifdef _MSC_VER
#define DEBUG__PB_PUSH_BACK_TIME_SI(si_expr) \
    do { \
        time_t __dbgpb_now; time(&__dbgpb_now); \
        char __dbgpb_tbuf[26]; \
        if (ctime_s(__dbgpb_tbuf, sizeof(__dbgpb_tbuf), &__dbgpb_now) != 0) { \
            fprintf(stderr, "%s:%d: push_back_time: ctime_s failed\n", __FILE__, __LINE__); break; \
        } \
        size_t __dbgpb_len = strlen(__dbgpb_tbuf); \
        if (__dbgpb_len > 0 && __dbgpb_tbuf[__dbgpb_len - 1] == '\n') __dbgpb_tbuf[__dbgpb_len - 1] = '\0'; \
        DEBUG__PB_PUSH_BACK_STR_SI((si_expr), __dbgpb_tbuf); \
    } while (0)

#define DEBUG__PB_PUSH_FRONT_TIME_SI(si_expr) \
    do { \
        time_t __dbgpb_now; time(&__dbgpb_now); \
        char __dbgpb_tbuf[26]; \
        if (ctime_s(__dbgpb_tbuf, sizeof(__dbgpb_tbuf), &__dbgpb_now) != 0) { \
            fprintf(stderr, "%s:%d: push_front_time: ctime_s failed\n", __FILE__, __LINE__); break; \
        } \
        size_t __dbgpb_len = strlen(__dbgpb_tbuf); \
        if (__dbgpb_len > 0 && __dbgpb_tbuf[__dbgpb_len - 1] == '\n') __dbgpb_tbuf[__dbgpb_len - 1] = '\0'; \
        DEBUG__PB_PUSH_FRONT_STR_SI((si_expr), __dbgpb_tbuf); \
    } while (0)
#else
#define DEBUG__PB_PUSH_BACK_TIME_SI(si_expr) \
    do { \
        time_t __dbgpb_now; time(&__dbgpb_now); \
        char* __dbgpb_t = ctime(&__dbgpb_now); \
        if (!__dbgpb_t) { fprintf(stderr, "%s:%d: push_back_time: ctime failed\n", __FILE__, __LINE__); break; } \
        char __dbgpb_tmp[64]; \
        size_t __dbgpb_len = strlen(__dbgpb_t); \
        if (__dbgpb_len >= sizeof(__dbgpb_tmp)) __dbgpb_len = sizeof(__dbgpb_tmp) - 1; \
        memcpy(__dbgpb_tmp, __dbgpb_t, __dbgpb_len); __dbgpb_tmp[__dbgpb_len] = '\0'; \
        if (__dbgpb_len > 0 && __dbgpb_tmp[__dbgpb_len - 1] == '\n') __dbgpb_tmp[__dbgpb_len - 1] = '\0'; \
        DEBUG__PB_PUSH_BACK_STR_SI((si_expr), __dbgpb_tmp); \
    } while (0)

#define DEBUG__PB_PUSH_FRONT_TIME_SI(si_expr) \
    do { \
        time_t __dbgpb_now; time(&__dbgpb_now); \
        char* __dbgpb_t = ctime(&__dbgpb_now); \
        if (!__dbgpb_t) { fprintf(stderr, "%s:%d: push_front_time: ctime failed\n", __FILE__, __LINE__); break; } \
        char __dbgpb_tmp[64]; \
        size_t __dbgpb_len = strlen(__dbgpb_t); \
        if (__dbgpb_len >= sizeof(__dbgpb_tmp)) __dbgpb_len = sizeof(__dbgpb_tmp) - 1; \
        memcpy(__dbgpb_tmp, __dbgpb_t, __dbgpb_len); __dbgpb_tmp[__dbgpb_len] = '\0'; \
        if (__dbgpb_len > 0 && __dbgpb_tmp[__dbgpb_len - 1] == '\n') __dbgpb_tmp[__dbgpb_len - 1] = '\0'; \
        DEBUG__PB_PUSH_FRONT_STR_SI((si_expr), __dbgpb_tmp); \
    } while (0)
#endif

#define DEBUG__PB_PUSH_BACK_PTR_SI(si_expr, ptr_expr)                               \
    do {                                                                            \
        const void* __dbgpb_p = (const void*)(ptr_expr);                            \
        if (__dbgpb_p == NULL) {                                                    \
            DEBUG__PB_PUSH_BACK_STR_SI((si_expr), "0x0");                           \
        } else {                                                                    \
            /* direct-to-destination, records as one element */                     \
            DEBUG__PB_PUSH_BACK_FMT_SI((si_expr), "0x%" PRIxPTR, (uintptr_t)__dbgpb_p); \
        }                                                                           \
    } while (0)

#define DEBUG__PB_PUSH_FRONT_PTR_SI(si_expr, ptr_expr)                              \
    do {                                                                            \
        const void* __dbgpb_p = (const void*)(ptr_expr);                            \
        if (__dbgpb_p == NULL) {                                                    \
            DEBUG__PB_PUSH_FRONT_STR_SI((si_expr), "0x0");                          \
        } else {                                                                    \
            DEBUG__PB_PUSH_FRONT_FMT_SI((si_expr), "0x%" PRIxPTR, (uintptr_t)__dbgpb_p); \
        }                                                                           \
    } while (0)

#define DEBUG__PB_SET_PTR_SI_IDX(si_expr, idx_expr, ptr_expr)                       \
    do {                                                                            \
        const void* __dbgpb_p = (const void*)(ptr_expr);                            \
        if (__dbgpb_p == NULL) {                                                    \
            DEBUG__PB_SET_STR_SI_IDX((si_expr), (idx_expr), "0x0");                 \
        } else {                                                                    \
            DEBUG__PB_SET_FMT_SI_IDX((si_expr), (idx_expr), "0x%" PRIxPTR,          \
                                    (uintptr_t)__dbgpb_p);                          \
        }                                                                           \
    } while (0)

#define DEBUG__PB_INSERT_PTR_SI_IDX(si_expr, idx_expr, ptr_expr)                    \
    do {                                                                            \
        const void* __dbgpb_p = (const void*)(ptr_expr);                            \
        if (__dbgpb_p == NULL) {                                                    \
            DEBUG__PB_INSERT_STR_SI_IDX((si_expr), (idx_expr), "0x0");              \
        } else {                                                                    \
            DEBUG__PB_INSERT_FMT_SI_IDX((si_expr), (idx_expr), "0x%" PRIxPTR,       \
                                       (uintptr_t)__dbgpb_p);                       \
        }                                                                           \
    } while (0)

/* Declares a user-visible buffer name outside; this helper only fills it. */
#define DEBUG__PB_AT_DUMP_SI_IDX(si_expr, idx_expr, dst_buf, dst_cap, out_len_var)  \
    do {                                                                            \
        const char* __dbgpb_p = NULL;                                               \
        size_t      __dbgpb_n = 0;                                                  \
        DEBUG__PB_AT_SI_IDX((si_expr), (idx_expr), __dbgpb_p, __dbgpb_n);           \
        (out_len_var) = 0;                                                          \
        if ((dst_cap) == 0) {                                                       \
            /* nothing */                                                           \
        } else if (!__dbgpb_p) {                                                    \
            (dst_buf)[0] = '\0';                                                    \
        } else {                                                                    \
            size_t __dbgpb_cpy = (__dbgpb_n < ((dst_cap) - 1)) ? __dbgpb_n : ((dst_cap) - 1); \
            if (__dbgpb_cpy > 0) memcpy((dst_buf), __dbgpb_p, __dbgpb_cpy);         \
            (dst_buf)[__dbgpb_cpy] = '\0';                                          \
            (out_len_var) = __dbgpb_cpy;                                            \
        }                                                                           \
    } while (0)


/* ===================== PUBLIC *_I APIs (thin wrappers; no nesting hazards) ===================== */

#define DEBUG_PUSH_BUF_CLR_I(slotIndex) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("CLR_I: slot out of range"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) = DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_ANALYZE_ASSUME(DEBUG__PB_MKNAME(__pb_si_,__LINE__) < DEBUG_PUSH_BUF_SLOTS_); \
        DEBUG__PB_CLR_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__)); \
    } while (0)

/*
     read/span use:
     size_t len; const char* p;
     DEBUG_PUSH_BUF_AT_I(0, i, p, len);
     printf("%.*s", (int)len, p);
*/
#define DEBUG_PUSH_BUF_AT_I(slotIndex, elemIndex, out_ptr, out_len) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { (out_ptr)=NULL; (out_len)=0; break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) = DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__) = (size_t)(elemIndex); \
        DEBUG__PB_AT_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__), DEBUG__PB_MKNAME(__pb_idx_,__LINE__), (out_ptr), (out_len)); \
    } while (0)

#define DEBUG_POP_BUF_FRONT_I(slotIndex) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("POP_FRONT_I: slot out of range"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) = DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_POP_FRONT_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__)); \
    } while (0)

#define DEBUG_POP_BUF_BACK_I(slotIndex) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("POP_BACK_I: slot out of range"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) = DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_POP_BACK_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__)); \
    } while (0)

#define DEBUG_PUSH_BUF_BACK_STR_I(slotIndex, str) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("BACK_STR_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_BACK_STR_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (str)); \
    } while (0)

#define DEBUG_PUSH_BUF_FRONT_STR_I(slotIndex, str) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("FRONT_STR_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_FRONT_STR_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (str)); \
    } while (0)

#define DEBUG_PUSH_BUF_BACK_FMT_I(slotIndex, fmt, ...) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("BACK_FMT_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_BACK_FMT_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (fmt), ##__VA_ARGS__); \
    } while (0)

#define DEBUG_PUSH_BUF_FRONT_FMT_I(slotIndex, fmt, ...) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("FRONT_FMT_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_FRONT_FMT_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (fmt), ##__VA_ARGS__); \
    } while (0)

#define DEBUG_SET_BUF_STR_I(slotIndex, elemIndex, str) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__)=(size_t)(elemIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("SET_STR_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) >= DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) { DEBUG__PB_ERR("SET_STR_I: idx out"); break; } \
        DEBUG__PB_SET_STR_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__), DEBUG__PB_MKNAME(__pb_idx_,__LINE__), (str)); \
    } while (0)

#define DEBUG_SET_BUF_FMT_I(slotIndex, elemIndex, fmt, ...) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__)=(size_t)(elemIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("SET_FMT_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) >= DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) { DEBUG__PB_ERR("SET_FMT_I: idx out"); break; } \
        DEBUG__PB_SET_FMT_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__), DEBUG__PB_MKNAME(__pb_idx_,__LINE__), (fmt), ##__VA_ARGS__); \
    } while (0)

#define DEBUG_INSERT_BUF_STR_I(slotIndex, elemIndex, str) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__)=(size_t)(elemIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("INS_STR_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__))) { DEBUG__PB_ERR("INS_STR_I: elem cap"); break; } \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) > DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) { DEBUG__PB_ERR("INS_STR_I: idx out"); break; } \
        DEBUG__PB_INSERT_STR_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__), DEBUG__PB_MKNAME(__pb_idx_,__LINE__), (str)); \
    } while (0)

#define DEBUG_INSERT_BUF_FMT_I(slotIndex, elemIndex, fmt, ...) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__)=(size_t)(elemIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("INS_FMT_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__))) { DEBUG__PB_ERR("INS_FMT_I: elem cap"); break; } \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) > DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) { DEBUG__PB_ERR("INS_FMT_I: idx out"); break; } \
        DEBUG__PB_INSERT_FMT_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__), DEBUG__PB_MKNAME(__pb_idx_,__LINE__), (fmt), ##__VA_ARGS__); \
    } while (0)

#define DEBUG_ERASE_BUF_I(slotIndex, elemIndex) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__)=(size_t)(elemIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("ERASE_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        if (DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)] == 0) { DEBUG__PB_ERR("ERASE_I: empty"); break; } \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) >= DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) { DEBUG__PB_ERR("ERASE_I: idx out"); break; } \
        DEBUG__PB_ERASE_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__), DEBUG__PB_MKNAME(__pb_idx_,__LINE__)); \
    } while (0)

#define DEBUG_PUSH_BUF_BACK_ARGV_I(slotIndex, argc, argv) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("BACK_ARGV_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_BACK_ARGV_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (argc), (argv)); \
    } while (0)

#define DEBUG_PUSH_BUF_FRONT_ARGV_I(slotIndex, argc, argv) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("FRONT_ARGV_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_FRONT_ARGV_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (argc), (argv)); \
    } while (0)

#define DEBUG_PUSH_BUF_BACK_TIME_I(slotIndex) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("BACK_TIME_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_BACK_TIME_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__)); \
    } while (0)

#define DEBUG_PUSH_BUF_FRONT_TIME_I(slotIndex) \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("FRONT_TIME_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        DEBUG__PB_PUSH_FRONT_TIME_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__)); \
    } while (0)

#define DEBUG_PUSH_BUF_BACK_PTR_I(slotIndex, ptr)                                   \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex);       \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) {          \
            DEBUG__PB_ERR("BACK_PTR_I: slot out");                                  \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) =                                \
            DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__);                                \
        DEBUG__PB_PUSH_BACK_PTR_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (ptr));     \
    } while (0)

#define DEBUG_PUSH_BUF_FRONT_PTR_I(slotIndex, ptr)                                  \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex);       \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) {          \
            DEBUG__PB_ERR("FRONT_PTR_I: slot out");                                 \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) =                                \
            DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__);                                \
        DEBUG__PB_PUSH_FRONT_PTR_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__), (ptr));    \
    } while (0)

#define DEBUG_SET_BUF_PTR_I(slotIndex, elemIndex, ptr)                              \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex);       \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__) = (size_t)(elemIndex);          \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) {          \
            DEBUG__PB_ERR("SET_PTR_I: slot out");                                   \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) =                                \
            DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__);                                \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) >=                                 \
            DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) {       \
            DEBUG__PB_ERR("SET_PTR_I: idx out");                                    \
            break;                                                                  \
        }                                                                           \
        DEBUG__PB_SET_PTR_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__),               \
                                 DEBUG__PB_MKNAME(__pb_idx_,__LINE__), (ptr));      \
    } while (0)

#define DEBUG_INSERT_BUF_PTR_I(slotIndex, elemIndex, ptr)                           \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex);       \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__) = (size_t)(elemIndex);          \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) {          \
            DEBUG__PB_ERR("INS_PTR_I: slot out");                                   \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) =                                \
            DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__);                                \
        if (!DEBUG__PB_HAS_ELEM_ROOM_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__))) {     \
            DEBUG__PB_ERR("INS_PTR_I: elem cap");                                   \
            break;                                                                  \
        }                                                                           \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) >                                  \
            DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) {       \
            DEBUG__PB_ERR("INS_PTR_I: idx out");                                    \
            break;                                                                  \
        }                                                                           \
        DEBUG__PB_INSERT_PTR_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__),            \
                                    DEBUG__PB_MKNAME(__pb_idx_,__LINE__), (ptr));   \
    } while (0)

/* ===================== dump helpers (indexed) using internal pop (safe nesting) ===================== */

#define DEBUG_POP_BUF_FRONT_DUMP_I(slotIndex, bufLen) \
    DEBUG__PB_BUFDECL(DEBUG_POP_BUF_FRONT_, (bufLen)); \
    size_t DEBUG_POP_BUF_FRONT_LEN_ = 0; \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("POP_FRONT_DUMP_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        if (DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)] == 0) { \
            /* empty */ \
        } else { \
            size_t __dbgpb_n = DEBUG_PUSH_BUF_LENS_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)][0]; \
            size_t __dbgpb_cap = ((size_t)(bufLen) > 0) ? (size_t)(bufLen) : 1; \
            size_t __dbgpb_cpy = (__dbgpb_n < (__dbgpb_cap - 1)) ? __dbgpb_n : (__dbgpb_cap - 1); \
            if (__dbgpb_cpy > 0) memcpy(DEBUG_POP_BUF_FRONT_, DEBUG_PUSH_BUF_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)], __dbgpb_cpy); \
            DEBUG_POP_BUF_FRONT_[__dbgpb_cpy] = '\0'; \
            DEBUG_POP_BUF_FRONT_LEN_ = __dbgpb_cpy; \
            DEBUG__PB_POP_FRONT_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__)); \
        } \
    } while (0)

#define DEBUG_POP_BUF_BACK_DUMP_I(slotIndex, bufLen) \
    DEBUG__PB_BUFDECL(DEBUG_POP_BUF_BACK_, (bufLen)); \
    size_t DEBUG_POP_BUF_BACK_LEN_ = 0; \
    do { \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__)=(size_t)(slotIndex); \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) { DEBUG__PB_ERR("POP_BACK_DUMP_I: slot out"); break; } \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__)=DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__); \
        size_t __dbgpb_n_elems = DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]; \
        if (__dbgpb_n_elems == 0) { \
            /* empty */ \
        } else { \
            size_t __dbgpb_idx = __dbgpb_n_elems - 1; \
            size_t __dbgpb_off = 0; \
            for (size_t __dbgpb_k = 0; __dbgpb_k < __dbgpb_idx; ++__dbgpb_k) \
                __dbgpb_off += DEBUG_PUSH_BUF_LENS_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)][__dbgpb_k]; \
            size_t __dbgpb_n = DEBUG_PUSH_BUF_LENS_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)][__dbgpb_idx]; \
            size_t __dbgpb_cap = ((size_t)(bufLen) > 0) ? (size_t)(bufLen) : 1; \
            size_t __dbgpb_cpy = (__dbgpb_n < (__dbgpb_cap - 1)) ? __dbgpb_n : (__dbgpb_cap - 1); \
            if (__dbgpb_cpy > 0) memcpy(DEBUG_POP_BUF_BACK_, DEBUG_PUSH_BUF_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)] + __dbgpb_off, __dbgpb_cpy); \
            DEBUG_POP_BUF_BACK_[__dbgpb_cpy] = '\0'; \
            DEBUG_POP_BUF_BACK_LEN_ = __dbgpb_cpy; \
            DEBUG__PB_POP_BACK_SI(DEBUG__PB_MKNAME(__pb_si_,__LINE__)); \
        } \
    } while (0)

#define DEBUG_PUSH_BUF_AT_DUMP_I(slotIndex, elemIndex, bufLen)                      \
    DEBUG__PB_BUFDECL(DEBUG_PUSH_BUF_AT_, (bufLen));                                \
    size_t DEBUG_PUSH_BUF_AT_LEN_ = 0;                                              \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__) = (size_t)(slotIndex);       \
        size_t DEBUG__PB_MKNAME(__pb_idx_,__LINE__) = (size_t)(elemIndex);          \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__))) {          \
            DEBUG__PB_ERR("AT_DUMP_I: slot out");                                   \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__pb_si_,__LINE__) =                                \
            DEBUG__PB_MKNAME(__pb_si_raw_,__LINE__);                                \
        /* if idx out of range -> leave empty */                                    \
        if (DEBUG__PB_MKNAME(__pb_idx_,__LINE__) >=                                 \
            DEBUG_PUSH_BUF_N_[(size_t)DEBUG__PB_MKNAME(__pb_si_,__LINE__)]) {       \
            DEBUG_PUSH_BUF_AT_[0] = '\0';                                           \
            DEBUG_PUSH_BUF_AT_LEN_ = 0;                                             \
            break;                                                                  \
        }                                                                           \
        DEBUG__PB_AT_DUMP_SI_IDX(DEBUG__PB_MKNAME(__pb_si_,__LINE__),               \
                                 DEBUG__PB_MKNAME(__pb_idx_,__LINE__),              \
                                 DEBUG_PUSH_BUF_AT_,                                \
                                 (size_t)(((size_t)(bufLen) > 0) ? (size_t)(bufLen) : 1), \
                                 DEBUG_PUSH_BUF_AT_LEN_);                           \
    } while (0)


/* INT using FMT */
#define DEBUG_PUSH_BUF_BACK_INT_I(index, num)             DEBUG_PUSH_BUF_BACK_FMT_I((index), "%d", (num))
#define DEBUG_PUSH_BUF_FRONT_INT_I(index, num)            DEBUG_PUSH_BUF_FRONT_FMT_I((index), "%d", (num))
#define DEBUG_SET_BUF_INT_I(slotIndex, elemIndex, num)    DEBUG_SET_BUF_FMT_I((slotIndex), (elemIndex), "%d", (num))
#define DEBUG_INSERT_BUF_INT_I(slotIndex, elemIndex, num) DEBUG_INSERT_BUF_FMT_I((slotIndex), (elemIndex), "%d", (num))


/* single slot */
#define DEBUG_PUSH_BUF_DEFAULT_MAX_ELEMS(buf_cap)      (((buf_cap) < 256) ? (buf_cap) : 256u)
#define DEBUG_PUSH_BUF_INIT(size)                      DEBUG_PUSH_BUF_INIT_I(1, (size), DEBUG_PUSH_BUF_DEFAULT_MAX_ELEMS(size))

#define DEBUG_PUSH_BUF_BACK_STR(str)                   DEBUG_PUSH_BUF_BACK_STR_I(0, (str))
#define DEBUG_PUSH_BUF_FRONT_STR(str)                  DEBUG_PUSH_BUF_FRONT_STR_I(0, (str))
#define DEBUG_PUSH_BUF_BACK_FMT(fmt, ...)              DEBUG_PUSH_BUF_BACK_FMT_I(0, (fmt), ##__VA_ARGS__)
#define DEBUG_PUSH_BUF_FRONT_FMT(fmt, ...)             DEBUG_PUSH_BUF_FRONT_FMT_I(0, (fmt), ##__VA_ARGS__)
#define DEBUG_PUSH_BUF_BACK_INT(num)                   DEBUG_PUSH_BUF_BACK_INT_I(0, (num))
#define DEBUG_PUSH_BUF_FRONT_INT(num)                  DEBUG_PUSH_BUF_FRONT_INT_I(0, (num))
#define DEBUG_PUSH_BUF_BACK_PTR(ptr)                   DEBUG_PUSH_BUF_BACK_PTR_I(0, (ptr))
#define DEBUG_PUSH_BUF_FRONT_PTR(ptr)                  DEBUG_PUSH_BUF_FRONT_PTR_I(0, (ptr))
#define DEBUG_PUSH_BUF_BACK_ARGV(argc,argv)            DEBUG_PUSH_BUF_BACK_ARGV_I(0, (argc), (argv))
#define DEBUG_PUSH_BUF_FRONT_ARGV(argc,argv)           DEBUG_PUSH_BUF_FRONT_ARGV_I(0, (argc), (argv))
#define DEBUG_PUSH_BUF_BACK_TIME()                     DEBUG_PUSH_BUF_BACK_TIME_I(0)
#define DEBUG_PUSH_BUF_FRONT_TIME()                    DEBUG_PUSH_BUF_FRONT_TIME_I(0)
#define DEBUG_POP_BUF_BACK()                           DEBUG_POP_BUF_BACK_I(0)
#define DEBUG_POP_BUF_FRONT()                          DEBUG_POP_BUF_FRONT_I(0)
#define DEBUG_POP_BUF_BACK_DUMP(bufLen)                DEBUG_POP_BUF_BACK_DUMP_I(0, (bufLen))
#define DEBUG_POP_BUF_FRONT_DUMP(bufLen)               DEBUG_POP_BUF_FRONT_DUMP_I(0, (bufLen))

#define DEBUG_INSERT_BUF_STR(elemIndex, str)           DEBUG_INSERT_BUF_STR_I(0, (elemIndex), (str))
#define DEBUG_INSERT_BUF_FMT(elemIndex, fmt, ...)      DEBUG_INSERT_BUF_FMT_I(0, (elemIndex), (fmt), ##__VA_ARGS__)
#define DEBUG_INSERT_BUF_INT(elemIndex, num)           DEBUG_INSERT_BUF_INT_I(0, (elemIndex), (num))
#define DEBUG_INSERT_BUF_PTR(elemIndex, ptr)           DEBUG_INSERT_BUF_PTR_I(0, (elemIndex), (ptr))
#define DEBUG_ERASE_BUF(elemIndex)                     DEBUG_ERASE_BUF_I(0, (elemIndex))
#define DEBUG_SET_BUF_STR(elemIndex, str)              DEBUG_SET_BUF_STR_I(0, (elemIndex), (str))
#define DEBUG_SET_BUF_FMT(elemIndex, fmt, ...)         DEBUG_SET_BUF_FMT_I(0, (elemIndex), (fmt), ##__VA_ARGS__)
#define DEBUG_SET_BUF_INT(elemIndex, num)              DEBUG_SET_BUF_INT_I(0, (elemIndex), (num))
#define DEBUG_SET_BUF_PTR(elemIndex, ptr)              DEBUG_SET_BUF_PTR_I(0, (elemIndex), (ptr))
#define DEBUG_POP_BUF()                                DEBUG_POP_BUF_BACK_I(0)
#define DEBUG_PUSH_BUF_CLR()                           DEBUG_PUSH_BUF_CLR_I(0)

#define DEBUG_PUSH_BUF_AT(elemIndex, out_ptr, out_len) DEBUG_PUSH_BUF_AT_I(0, (elemIndex), (out_ptr), (out_len))
#define DEBUG_PUSH_BUF_AT_DUMP(elemIndex, bufLen)      DEBUG_PUSH_BUF_AT_DUMP_I(0, (elemIndex), (bufLen))

/* single slot, default back */
#define DEBUG_PUSH_BUF_STR(str)                        DEBUG_PUSH_BUF_BACK_STR_I(0, (str))
#define DEBUG_PUSH_BUF_FMT(fmt, ...)                   DEBUG_PUSH_BUF_BACK_FMT_I(0, (fmt), ##__VA_ARGS__)
#define DEBUG_PUSH_BUF_INT(num)                        DEBUG_PUSH_BUF_BACK_INT_I(0, (num))
#define DEBUG_PUSH_BUF_PTR(ptr)                        DEBUG_PUSH_BUF_BACK_PTR_I(0, (ptr))
#define DEBUG_PUSH_BUF_ARGV(argc,argv)                 DEBUG_PUSH_BUF_BACK_ARGV_I(0, (argc), (argv))
#define DEBUG_PUSH_BUF_TIME()                          DEBUG_PUSH_BUF_BACK_TIME_I(0)

#define DEBUG_PUSH_BUF0_                               (DEBUG_PUSH_BUF_[0])
#define DEBUG_PUSH_BUF_POS0_                           (DEBUG_PUSH_BUF_POS_[0])
#define DEBUG_PUSH_BUF_N0_                             (DEBUG_PUSH_BUF_N_[0])

#endif /* DEBUG_PUSH_BUF_INDEXED_H_ */
