#ifndef DEBUG_PUSH_BUF_INDEXED_H_
#define DEBUG_PUSH_BUF_INDEXED_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

/* ========================= helpers ========================= */

#define DEBUG__PB_MKNAME2(a,b) a##b
#define DEBUG__PB_MKNAME(a,b)  DEBUG__PB_MKNAME2(a,b)

#define DEBUG__PB_BUFDECL(name, bufLen) \
    char name[((bufLen) > 0) ? (bufLen) : 1] = {0}

/* Optional common error macro with call-site file/line */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define DEBUG__PB_ERR(msg) \
    fprintf(stderr, "%s:%d.%s: %s\n", __FILE__, __LINE__, __func__, (msg))
#else
#define DEBUG__PB_ERR(msg) \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, (msg))
#endif

/* ========================= initialization ========================= */
/*
slotCount : number of independent buffers ("instances")
bufCap    : bytes per buffer
maxElems  : max elements per buffer
*/
#define DEBUG_PUSH_BUF_INIT_I(slotCount, bufCap, maxElems)                          \
    char   DEBUG_PUSH_BUF_[(slotCount)][(bufCap)] = {{0}};                          \
    size_t DEBUG_PUSH_BUF_POS_[(slotCount)] = {0};                                  \
    const size_t DEBUG_PUSH_BUF_CAP_ = (size_t)(bufCap);                            \
    size_t DEBUG_PUSH_BUF_LENS_[(slotCount)][(maxElems)] = {{0}};                   \
    const size_t DEBUG_PUSH_BUF_LENS_CAP_ = (size_t)(maxElems);                     \
    size_t DEBUG_PUSH_BUF_N_[(slotCount)] = {0};                                    \
    const size_t DEBUG_PUSH_BUF_SLOT_CAP_ = (size_t)(slotCount)

/* Backward-ish single-slot init */
#define DEBUG_PUSH_BUF_INIT_1(buf_cap, max_elems)                                   \
    DEBUG_PUSH_BUF_INIT_I(1, (buf_cap), (max_elems))

/* Legacy compat init(size) with derived max elems */
#ifndef DEBUG_PUSH_BUF_DEFAULT_MAX_ELEMS
#define DEBUG_PUSH_BUF_DEFAULT_MAX_ELEMS(buf_cap) (((buf_cap) < 256) ? (buf_cap) : 256u)
#endif
#define DEBUG_PUSH_BUF_INIT(size)                                                   \
    DEBUG_PUSH_BUF_INIT_I(1, (size), DEBUG_PUSH_BUF_DEFAULT_MAX_ELEMS(size))

/* ========================= per-slot helpers ========================= */

#define DEBUG__PB_SLOT_OK(i_) ((size_t)(i_) < DEBUG_PUSH_BUF_SLOT_CAP_)

#define DEBUG__PB_HAS_ROOM_I(i_, add_len)                                           \
    ((DEBUG_PUSH_BUF_POS_[(size_t)(i_)] + (size_t)(add_len) < DEBUG_PUSH_BUF_CAP_) ? 1 : 0)

#define DEBUG__PB_HAS_ELEM_ROOM_I(i_)                                               \
    ((DEBUG_PUSH_BUF_N_[(size_t)(i_)] < DEBUG_PUSH_BUF_LENS_CAP_) ? 1 : 0)

#define DEBUG__PB_TERM_I(i_)                                                        \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(i_);                     \
        if (DEBUG_PUSH_BUF_CAP_ > 0) {                                              \
            if (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >= DEBUG_PUSH_BUF_CAP_) \
                DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] = DEBUG_PUSH_BUF_CAP_ - 1; \
            DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)][                      \
                DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]               \
            ] = '\0';                                                               \
        }                                                                           \
    } while (0)

/* Compute byte offset of element elemIdx within slot slotIdx */
#define DEBUG__PB_OFFSET_OF_I(slotIdx, elemIdx, __off, __ok)                        \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIdx);                \
        size_t DEBUG__PB_MKNAME(__ei_,__LINE__) = (size_t)(elemIdx);                \
        (__ok) = 1;                                                                 \
        (__off) = 0;                                                                \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            (__ok) = 0;                                                             \
        } else if (DEBUG__PB_MKNAME(__ei_,__LINE__) >= DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]) { \
            (__ok) = 0;                                                             \
        } else {                                                                    \
            for (size_t DEBUG__PB_MKNAME(__k_,__LINE__) = 0;                        \
                 DEBUG__PB_MKNAME(__k_,__LINE__) < DEBUG__PB_MKNAME(__ei_,__LINE__);\
                 ++DEBUG__PB_MKNAME(__k_,__LINE__)) {                               \
                (__off) += DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][  \
                    DEBUG__PB_MKNAME(__k_,__LINE__)                                 \
                ];                                                                  \
            }                                                                       \
        }                                                                           \
    } while (0)

/* ========================= clear ========================= */

#define DEBUG_PUSH_BUF_CLR_I(index)                                                 \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_CLR_I: slot index out of range");         \
            break;                                                                  \
        }                                                                           \
        memset(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)], 0, DEBUG_PUSH_BUF_CAP_); \
        memset(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)], 0,           \
               DEBUG_PUSH_BUF_LENS_CAP_ * sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));      \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] = 0;                  \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] = 0;                    \
    } while (0)

/* ========================= read/span ========================= 
   Use:
     size_t len; const char* p;
     DEBUG_PUSH_BUF_AT_I(0, i, p, len);
     printf("%.*s", (int)len, p);
*/

#define DEBUG_PUSH_BUF_AT_I(slotIndex, elemIndex, out_ptr, out_len)                 \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__off_,__LINE__) = 0;                               \
        int    DEBUG__PB_MKNAME(__ok_,__LINE__) = 0;                                \
        DEBUG__PB_OFFSET_OF_I((slotIndex), (elemIndex),                             \
                              DEBUG__PB_MKNAME(__off_,__LINE__),                    \
                              DEBUG__PB_MKNAME(__ok_,__LINE__));                    \
        if (!DEBUG__PB_MKNAME(__ok_,__LINE__)) {                                    \
            (out_ptr) = NULL;                                                       \
            (out_len) = 0;                                                          \
        } else {                                                                    \
            (out_ptr) = DEBUG_PUSH_BUF_[(size_t)(slotIndex)] +                      \
                        DEBUG__PB_MKNAME(__off_,__LINE__);                          \
            (out_len) = DEBUG_PUSH_BUF_LENS_[(size_t)(slotIndex)][(size_t)(elemIndex)]; \
        }                                                                           \
    } while (0)

/* ========================= push back/front string ========================= */

#define DEBUG_PUSH_BUF_BACK_STR_I(index, str)                                       \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        const char* DEBUG__PB_MKNAME(__s_,__LINE__) = (str);                        \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_STR_I: slot index out of range");    \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_MKNAME(__s_,__LINE__))                                       \
            DEBUG__PB_MKNAME(__s_,__LINE__) = "";                                   \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) = strlen(DEBUG__PB_MKNAME(__s_,__LINE__)); \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_STR_I: element capacity reached");   \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__), DEBUG__PB_MKNAME(__len_,__LINE__))) { \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_STR_I: buffer overflow prevented");  \
            break;                                                                  \
        }                                                                           \
        memcpy(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +                  \
                   DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)],           \
               DEBUG__PB_MKNAME(__s_,__LINE__), DEBUG__PB_MKNAME(__len_,__LINE__)); \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][                     \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++                   \
        ] = DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                    \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

#define DEBUG_PUSH_BUF_FRONT_STR_I(index, str)                                      \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        const char* DEBUG__PB_MKNAME(__s_,__LINE__) = (str);                        \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_STR_I: slot index out of range");   \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_MKNAME(__s_,__LINE__))                                       \
            DEBUG__PB_MKNAME(__s_,__LINE__) = "";                                   \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) = strlen(DEBUG__PB_MKNAME(__s_,__LINE__)); \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_STR_I: element capacity reached");  \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__), DEBUG__PB_MKNAME(__len_,__LINE__))) { \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_STR_I: buffer overflow prevented"); \
            break;                                                                  \
        }                                                                           \
        if (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] > 0) {            \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__len_,__LINE__),                          \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],              \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]);         \
        }                                                                           \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] > 0) {              \
            memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] + 1,     \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)],         \
                    DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] *           \
                        sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                        \
        }                                                                           \
        memcpy(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],                   \
               DEBUG__PB_MKNAME(__s_,__LINE__), DEBUG__PB_MKNAME(__len_,__LINE__)); \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][0] =                 \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++;                      \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                    \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

/* ========================= pop back/front ========================= */

#define DEBUG_POP_BUF_BACK_I(index)                                                 \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_POP_BUF_BACK_I: slot index out of range");         \
            break;                                                                  \
        }                                                                           \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] == 0) break;        \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) =                                  \
            DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][                 \
                DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] - 1             \
            ];                                                                      \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]--;                      \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]) \
            DEBUG__PB_MKNAME(__len_,__LINE__) = DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]; \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -=                    \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

#define DEBUG_POP_BUF_FRONT_I(index)                                                \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_POP_BUF_FRONT_I: slot index out of range");        \
            break;                                                                  \
        }                                                                           \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] == 0) break;        \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) =                                  \
            DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][0];              \
        if (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] > DEBUG__PB_MKNAME(__len_,__LINE__)) { \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],              \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__len_,__LINE__),                          \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -         \
                        DEBUG__PB_MKNAME(__len_,__LINE__));                         \
        }                                                                           \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] > 1) {              \
            memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)],         \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] + 1,     \
                    (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] - 1) *     \
                        sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                        \
        }                                                                           \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]) \
            DEBUG__PB_MKNAME(__len_,__LINE__) = DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]; \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -=                    \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]--;                      \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

/* ========================= fmt/int/ptr/time (indexed) ========================= */

/* Direct-to-destination formatted append as ONE element.
   Writes into remaining space of slot buffer and records actual bytes written.
   If truncated by destination capacity, it still appends the truncated bytes and records that length.
*/
#define DEBUG_PUSH_BUF_BACK_FMT_I(index, fmt, ...)                                  \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_FMT_I: slot index out of range");    \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_FMT_I: element capacity reached");   \
            break;                                                                  \
        }                                                                           \
        if (DEBUG_PUSH_BUF_CAP_ == 0 ||                                             \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >= DEBUG_PUSH_BUF_CAP_ - 1) { \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_FMT_I: buffer overflow prevented");  \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__pos0_,__LINE__) =                                 \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)];                  \
        size_t DEBUG__PB_MKNAME(__avail_,__LINE__) =                                \
            (DEBUG_PUSH_BUF_CAP_ - 1) - DEBUG__PB_MKNAME(__pos0_,__LINE__);         \
                                                                                    \
        int DEBUG__PB_MKNAME(__n_,__LINE__) = snprintf(                             \
            DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +                     \
                DEBUG__PB_MKNAME(__pos0_,__LINE__),                                 \
            DEBUG__PB_MKNAME(__avail_,__LINE__) + 1,                                \
            (fmt), ##__VA_ARGS__);                                                  \
                                                                                    \
        if (DEBUG__PB_MKNAME(__n_,__LINE__) < 0) {                                  \
            fprintf(stderr, "%s:%d: DEBUG_PUSH_BUF_BACK_FMT_I: formatting failed\n",\
                    __FILE__, __LINE__);                                            \
            /* keep buffer valid */                                                 \
            DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                     \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        /* snprintf returns required chars (excluding NUL).                         \
           If >= avail+1?  Actually compare against avail for truncation. */        \
        size_t DEBUG__PB_MKNAME(__written_,__LINE__) =                              \
            ((size_t)DEBUG__PB_MKNAME(__n_,__LINE__) <= DEBUG__PB_MKNAME(__avail_,__LINE__)) \
                ? (size_t)DEBUG__PB_MKNAME(__n_,__LINE__)                           \
                : DEBUG__PB_MKNAME(__avail_,__LINE__);                              \
                                                                                    \
        if ((size_t)DEBUG__PB_MKNAME(__n_,__LINE__) > DEBUG__PB_MKNAME(__avail_,__LINE__)) { \
            fprintf(stderr,                                                          \
                    "%s:%d: DEBUG_PUSH_BUF_BACK_FMT_I: destination truncated (need=%d, avail=%zu)\n", \
                    __FILE__, __LINE__, DEBUG__PB_MKNAME(__n_,__LINE__),            \
                    DEBUG__PB_MKNAME(__avail_,__LINE__));                           \
        }                                                                           \
                                                                                    \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                    \
            DEBUG__PB_MKNAME(__written_,__LINE__);                                  \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][                     \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++                   \
        ] = DEBUG__PB_MKNAME(__written_,__LINE__);                                  \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

/* Direct-to-destination formatted prepend as ONE element.
   Computes required formatted length, clamps to available space, shifts existing bytes,
   and writes formatted text into the front region.
*/
#define DEBUG_PUSH_BUF_FRONT_FMT_I(index, fmt, ...)                                 \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_FMT_I: slot index out of range");   \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_FMT_I: element capacity reached");  \
            break;                                                                  \
        }                                                                           \
        if (DEBUG_PUSH_BUF_CAP_ == 0) {                                             \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_FMT_I: buffer overflow prevented"); \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__pos0_,__LINE__) =                                 \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)];                  \
        size_t DEBUG__PB_MKNAME(__avail_,__LINE__) =                                \
            (DEBUG__PB_MKNAME(__pos0_,__LINE__) < DEBUG_PUSH_BUF_CAP_)              \
                ? ((DEBUG_PUSH_BUF_CAP_ - 1) - DEBUG__PB_MKNAME(__pos0_,__LINE__))  \
                : 0;                                                                \
        if (DEBUG__PB_MKNAME(__avail_,__LINE__) == 0) {                             \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_FMT_I: buffer overflow prevented"); \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        /* Probe required length */                                                 \
        int DEBUG__PB_MKNAME(__need_,__LINE__) = snprintf(NULL, 0, (fmt), ##__VA_ARGS__); \
        if (DEBUG__PB_MKNAME(__need_,__LINE__) < 0) {                               \
            fprintf(stderr, "%s:%d: DEBUG_PUSH_BUF_FRONT_FMT_I: formatting failed\n",\
                    __FILE__, __LINE__);                                            \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__wlen_,__LINE__) =                                 \
            ((size_t)DEBUG__PB_MKNAME(__need_,__LINE__) <= DEBUG__PB_MKNAME(__avail_,__LINE__)) \
                ? (size_t)DEBUG__PB_MKNAME(__need_,__LINE__)                        \
                : DEBUG__PB_MKNAME(__avail_,__LINE__);                              \
                                                                                    \
        if ((size_t)DEBUG__PB_MKNAME(__need_,__LINE__) > DEBUG__PB_MKNAME(__avail_,__LINE__)) { \
            fprintf(stderr,                                                          \
                    "%s:%d: DEBUG_PUSH_BUF_FRONT_FMT_I: destination truncated (need=%d, avail=%zu)\n", \
                    __FILE__, __LINE__, DEBUG__PB_MKNAME(__need_,__LINE__),         \
                    DEBUG__PB_MKNAME(__avail_,__LINE__));                           \
        }                                                                           \
                                                                                    \
        /* shift existing bytes right by wlen */                                    \
        if (DEBUG__PB_MKNAME(__pos0_,__LINE__) > 0 &&                               \
            DEBUG__PB_MKNAME(__wlen_,__LINE__) > 0) {                               \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__wlen_,__LINE__),                         \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],              \
                    DEBUG__PB_MKNAME(__pos0_,__LINE__));                            \
        }                                                                           \
                                                                                    \
        /* shift lens right by 1 */                                                 \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] > 0) {              \
            memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] + 1,     \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)],         \
                    DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] *           \
                        sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                        \
        }                                                                           \
                                                                                    \
        /* write formatted output into front space (wlen bytes max) */              \
        if (DEBUG__PB_MKNAME(__wlen_,__LINE__) > 0) {                               \
            int DEBUG__PB_MKNAME(__n2_,__LINE__) = snprintf(                        \
                DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],                  \
                DEBUG__PB_MKNAME(__wlen_,__LINE__) + 1,                             \
                (fmt), ##__VA_ARGS__);                                              \
            if (DEBUG__PB_MKNAME(__n2_,__LINE__) < 0) {                             \
                fprintf(stderr, "%s:%d: DEBUG_PUSH_BUF_FRONT_FMT_I: formatting failed (2nd pass)\n", \
                        __FILE__, __LINE__);                                        \
                /* rollback best effort: shift bytes back, shift lens back */       \
                if (DEBUG__PB_MKNAME(__pos0_,__LINE__) > 0) {                       \
                    memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],      \
                            DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +     \
                                DEBUG__PB_MKNAME(__wlen_,__LINE__),                 \
                            DEBUG__PB_MKNAME(__pos0_,__LINE__));                    \
                }                                                                   \
                if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] > 0) {      \
                    memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)], \
                            DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] + 1, \
                            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] *   \
                                sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                \
                }                                                                   \
                DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                 \
                break;                                                              \
            }                                                                       \
        }                                                                           \
                                                                                    \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][0] =                 \
            DEBUG__PB_MKNAME(__wlen_,__LINE__);                                     \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++;                      \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                    \
            DEBUG__PB_MKNAME(__wlen_,__LINE__);                                     \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)


#define DEBUG_PUSH_BUF_BACK_INT_I(index, num)   DEBUG_PUSH_BUF_BACK_FMT_I((index), "%d", (num))
#define DEBUG_PUSH_BUF_FRONT_INT_I(index, num)  DEBUG_PUSH_BUF_FRONT_FMT_I((index), "%d", (num))

#define DEBUG_PUSH_BUF_BACK_PTR_I(index, ptr)                                       \
    do {                                                                            \
        const void* DEBUG__PB_MKNAME(__p_,__LINE__) = (const void*)(ptr);           \
        if (DEBUG__PB_MKNAME(__p_,__LINE__) == NULL)                                \
            DEBUG_PUSH_BUF_BACK_STR_I((index), "0x0");                              \
        else                                                                        \
            DEBUG_PUSH_BUF_BACK_FMT_I((index), "0x%" PRIxPTR,                       \
                (uintptr_t)DEBUG__PB_MKNAME(__p_,__LINE__));                        \
    } while (0)

#define DEBUG_PUSH_BUF_FRONT_PTR_I(index, ptr)                                      \
    do {                                                                            \
        const void* DEBUG__PB_MKNAME(__p_,__LINE__) = (const void*)(ptr);           \
        if (DEBUG__PB_MKNAME(__p_,__LINE__) == NULL)                                \
            DEBUG_PUSH_BUF_FRONT_STR_I((index), "0x0");                             \
        else                                                                        \
            DEBUG_PUSH_BUF_FRONT_FMT_I((index), "0x%" PRIxPTR,                      \
                (uintptr_t)DEBUG__PB_MKNAME(__p_,__LINE__));                        \
    } while (0)

#ifdef _MSC_VER
#define DEBUG_PUSH_BUF_BACK_TIME_I(index)                                           \
    do {                                                                            \
        time_t DEBUG__PB_MKNAME(__now_,__LINE__);                                   \
        time(&DEBUG__PB_MKNAME(__now_,__LINE__));                                   \
        char DEBUG__PB_MKNAME(__tbuf_,__LINE__)[26];                                \
        if (ctime_s(DEBUG__PB_MKNAME(__tbuf_,__LINE__),                             \
                    sizeof(DEBUG__PB_MKNAME(__tbuf_,__LINE__)),                     \
                    &DEBUG__PB_MKNAME(__now_,__LINE__)) != 0) {                     \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_TIME_I: ctime_s failed");            \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) = strlen(DEBUG__PB_MKNAME(__tbuf_,__LINE__)); \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > 0 &&                                \
            DEBUG__PB_MKNAME(__tbuf_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__) - 1] == '\n') \
            DEBUG__PB_MKNAME(__tbuf_,__LINE__)[--DEBUG__PB_MKNAME(__len_,__LINE__)] = '\0'; \
        DEBUG_PUSH_BUF_BACK_STR_I((index), DEBUG__PB_MKNAME(__tbuf_,__LINE__));     \
    } while (0)
#else
#define DEBUG_PUSH_BUF_BACK_TIME_I(index)                                           \
    do {                                                                            \
        time_t DEBUG__PB_MKNAME(__now_,__LINE__);                                   \
        time(&DEBUG__PB_MKNAME(__now_,__LINE__));                                   \
        char* DEBUG__PB_MKNAME(__t_,__LINE__) = ctime(&DEBUG__PB_MKNAME(__now_,__LINE__)); \
        if (!DEBUG__PB_MKNAME(__t_,__LINE__)) {                                     \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_TIME_I: ctime failed");              \
            break;                                                                  \
        }                                                                           \
        char DEBUG__PB_MKNAME(__tmp_,__LINE__)[64];                                 \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) = strlen(DEBUG__PB_MKNAME(__t_,__LINE__)); \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) >= sizeof(DEBUG__PB_MKNAME(__tmp_,__LINE__))) \
            DEBUG__PB_MKNAME(__len_,__LINE__) = sizeof(DEBUG__PB_MKNAME(__tmp_,__LINE__)) - 1; \
        memcpy(DEBUG__PB_MKNAME(__tmp_,__LINE__), DEBUG__PB_MKNAME(__t_,__LINE__),  \
               DEBUG__PB_MKNAME(__len_,__LINE__));                                  \
        DEBUG__PB_MKNAME(__tmp_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__)] = '\0'; \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > 0 &&                                \
            DEBUG__PB_MKNAME(__tmp_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__) - 1] == '\n') \
            DEBUG__PB_MKNAME(__tmp_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__) - 1] = '\0'; \
        DEBUG_PUSH_BUF_BACK_STR_I((index), DEBUG__PB_MKNAME(__tmp_,__LINE__));      \
    } while (0)
#endif

/* Prepend current ctime string (without trailing '\n') as one element */
#ifdef _MSC_VER
#define DEBUG_PUSH_BUF_FRONT_TIME_I(index)                                          \
    do {                                                                            \
        time_t DEBUG__PB_MKNAME(__now_,__LINE__);                                   \
        time(&DEBUG__PB_MKNAME(__now_,__LINE__));                                   \
        char DEBUG__PB_MKNAME(__tbuf_,__LINE__)[26];                                \
        if (ctime_s(DEBUG__PB_MKNAME(__tbuf_,__LINE__),                             \
                    sizeof(DEBUG__PB_MKNAME(__tbuf_,__LINE__)),                     \
                    &DEBUG__PB_MKNAME(__now_,__LINE__)) != 0) {                     \
            fprintf(stderr, "%s:%d: DEBUG_PUSH_BUF_FRONT_TIME_I: ctime_s failed\n", \
                    __FILE__, __LINE__);                                            \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) =                                  \
            strlen(DEBUG__PB_MKNAME(__tbuf_,__LINE__));                             \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > 0 &&                                \
            DEBUG__PB_MKNAME(__tbuf_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__) - 1] == '\n') { \
            DEBUG__PB_MKNAME(__tbuf_,__LINE__)[--DEBUG__PB_MKNAME(__len_,__LINE__)] = '\0'; \
        }                                                                           \
        /* Use STR insert (len known, tiny string) */                               \
        DEBUG_PUSH_BUF_FRONT_STR_I((index), DEBUG__PB_MKNAME(__tbuf_,__LINE__));    \
    } while (0)
#else
#define DEBUG_PUSH_BUF_FRONT_TIME_I(index)                                          \
    do {                                                                            \
        time_t DEBUG__PB_MKNAME(__now_,__LINE__);                                   \
        time(&DEBUG__PB_MKNAME(__now_,__LINE__));                                   \
        char* DEBUG__PB_MKNAME(__t_,__LINE__) = ctime(&DEBUG__PB_MKNAME(__now_,__LINE__)); \
        if (!DEBUG__PB_MKNAME(__t_,__LINE__)) {                                     \
            fprintf(stderr, "%s:%d: DEBUG_PUSH_BUF_FRONT_TIME_I: ctime() failed\n", \
                    __FILE__, __LINE__);                                            \
            break;                                                                  \
        }                                                                           \
        /* copy because ctime() returns static buffer; remove trailing newline */   \
        char DEBUG__PB_MKNAME(__tmp_,__LINE__)[64];                                 \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) =                                  \
            strlen(DEBUG__PB_MKNAME(__t_,__LINE__));                                \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) >= sizeof(DEBUG__PB_MKNAME(__tmp_,__LINE__))) \
            DEBUG__PB_MKNAME(__len_,__LINE__) = sizeof(DEBUG__PB_MKNAME(__tmp_,__LINE__)) - 1; \
        memcpy(DEBUG__PB_MKNAME(__tmp_,__LINE__),                                   \
               DEBUG__PB_MKNAME(__t_,__LINE__),                                     \
               DEBUG__PB_MKNAME(__len_,__LINE__));                                  \
        DEBUG__PB_MKNAME(__tmp_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__)] = '\0'; \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > 0 &&                                \
            DEBUG__PB_MKNAME(__tmp_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__) - 1] == '\n') { \
            DEBUG__PB_MKNAME(__tmp_,__LINE__)[DEBUG__PB_MKNAME(__len_,__LINE__) - 1] = '\0'; \
        }                                                                           \
        DEBUG_PUSH_BUF_FRONT_STR_I((index), DEBUG__PB_MKNAME(__tmp_,__LINE__));     \
    } while (0)
#endif

/* ========================= argv indexed ========================= */
/* Append argv as ONE element */
#define DEBUG_PUSH_BUF_BACK_ARGV_I(index, argc, argv)                               \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_ARGV_I: slot index out of range");   \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_BACK_ARGV_I: element capacity reached");  \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__before_,__LINE__) =                               \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)];                  \
        for (int DEBUG__PB_MKNAME(__i_,__LINE__) = 0;                               \
             DEBUG__PB_MKNAME(__i_,__LINE__) < (argc);                              \
             ++DEBUG__PB_MKNAME(__i_,__LINE__)) {                                   \
            const char* DEBUG__PB_MKNAME(__arg_,__LINE__) =                         \
                (argv)[DEBUG__PB_MKNAME(__i_,__LINE__)];                            \
            if (!DEBUG__PB_MKNAME(__arg_,__LINE__))                                 \
                DEBUG__PB_MKNAME(__arg_,__LINE__) = "";                             \
            size_t DEBUG__PB_MKNAME(__len_,__LINE__) = strlen(DEBUG__PB_MKNAME(__arg_,__LINE__)); \
            if (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >= DEBUG_PUSH_BUF_CAP_ - 1) \
                break;                                                              \
            size_t DEBUG__PB_MKNAME(__avail_,__LINE__) =                            \
                (DEBUG_PUSH_BUF_CAP_ - 1) - DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]; \
            if (DEBUG__PB_MKNAME(__len_,__LINE__) > DEBUG__PB_MKNAME(__avail_,__LINE__)) \
                DEBUG__PB_MKNAME(__len_,__LINE__) = DEBUG__PB_MKNAME(__avail_,__LINE__); \
            memcpy(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +              \
                       DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)],       \
                   DEBUG__PB_MKNAME(__arg_,__LINE__),                               \
                   DEBUG__PB_MKNAME(__len_,__LINE__));                              \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                \
                DEBUG__PB_MKNAME(__len_,__LINE__);                                  \
            if (DEBUG__PB_MKNAME(__i_,__LINE__) < (argc) - 1 &&                     \
                DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] < DEBUG_PUSH_BUF_CAP_ - 1) { \
                DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)][                  \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]++         \
                ] = ' ';                                                            \
            }                                                                       \
        }                                                                           \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][                     \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++                   \
        ] = (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -                \
             DEBUG__PB_MKNAME(__before_,__LINE__));                                 \
    } while (0)

/* Prepend argv as ONE element */
#define DEBUG_PUSH_BUF_FRONT_ARGV_I(index, argc, argv)                              \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(index);                  \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_ARGV_I: slot index out of range");  \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_ARGV_I: element capacity reached"); \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__need_,__LINE__) = 0;                              \
        for (int DEBUG__PB_MKNAME(__i_,__LINE__) = 0;                               \
             DEBUG__PB_MKNAME(__i_,__LINE__) < (argc);                              \
             ++DEBUG__PB_MKNAME(__i_,__LINE__)) {                                   \
            const char* DEBUG__PB_MKNAME(__arg_,__LINE__) =                         \
                (argv)[DEBUG__PB_MKNAME(__i_,__LINE__)];                            \
            if (!DEBUG__PB_MKNAME(__arg_,__LINE__))                                 \
                DEBUG__PB_MKNAME(__arg_,__LINE__) = "";                             \
            DEBUG__PB_MKNAME(__need_,__LINE__) += strlen(DEBUG__PB_MKNAME(__arg_,__LINE__)); \
            if (DEBUG__PB_MKNAME(__i_,__LINE__) < (argc) - 1)                       \
                DEBUG__PB_MKNAME(__need_,__LINE__) += 1;                            \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__avail_,__LINE__) =                                \
            (DEBUG_PUSH_BUF_CAP_ > 0 &&                                             \
             DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] < DEBUG_PUSH_BUF_CAP_) \
              ? ((DEBUG_PUSH_BUF_CAP_ - 1) - DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]) \
              : 0;                                                                  \
        if (DEBUG__PB_MKNAME(__avail_,__LINE__) == 0) {                             \
            DEBUG__PB_ERR("DEBUG_PUSH_BUF_FRONT_ARGV_I: buffer overflow prevented");\
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__wlen_,__LINE__) =                                 \
            (DEBUG__PB_MKNAME(__need_,__LINE__) < DEBUG__PB_MKNAME(__avail_,__LINE__) \
             ? DEBUG__PB_MKNAME(__need_,__LINE__) : DEBUG__PB_MKNAME(__avail_,__LINE__)); \
        if (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] > 0) {            \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__wlen_,__LINE__),                         \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],              \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)]);         \
        }                                                                           \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] > 0) {              \
            memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] + 1,     \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)],         \
                    DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] *           \
                        sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                        \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__pos_,__LINE__) = 0;                               \
        for (int DEBUG__PB_MKNAME(__i2_,__LINE__) = 0;                              \
             DEBUG__PB_MKNAME(__i2_,__LINE__) < (argc) &&                           \
             DEBUG__PB_MKNAME(__pos_,__LINE__) < DEBUG__PB_MKNAME(__wlen_,__LINE__);\
             ++DEBUG__PB_MKNAME(__i2_,__LINE__)) {                                  \
            const char* DEBUG__PB_MKNAME(__arg2_,__LINE__) =                        \
                (argv)[DEBUG__PB_MKNAME(__i2_,__LINE__)];                           \
            if (!DEBUG__PB_MKNAME(__arg2_,__LINE__))                                \
                DEBUG__PB_MKNAME(__arg2_,__LINE__) = "";                            \
            size_t DEBUG__PB_MKNAME(__len_,__LINE__) = strlen(DEBUG__PB_MKNAME(__arg2_,__LINE__)); \
            size_t DEBUG__PB_MKNAME(__rem_,__LINE__) =                              \
                DEBUG__PB_MKNAME(__wlen_,__LINE__) - DEBUG__PB_MKNAME(__pos_,__LINE__); \
            if (DEBUG__PB_MKNAME(__len_,__LINE__) > DEBUG__PB_MKNAME(__rem_,__LINE__)) \
                DEBUG__PB_MKNAME(__len_,__LINE__) = DEBUG__PB_MKNAME(__rem_,__LINE__); \
            if (DEBUG__PB_MKNAME(__len_,__LINE__) > 0) {                            \
                memcpy(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +          \
                           DEBUG__PB_MKNAME(__pos_,__LINE__),                       \
                       DEBUG__PB_MKNAME(__arg2_,__LINE__),                          \
                       DEBUG__PB_MKNAME(__len_,__LINE__));                          \
                DEBUG__PB_MKNAME(__pos_,__LINE__) += DEBUG__PB_MKNAME(__len_,__LINE__); \
            }                                                                       \
            if (DEBUG__PB_MKNAME(__i2_,__LINE__) < (argc) - 1 &&                    \
                DEBUG__PB_MKNAME(__pos_,__LINE__) < DEBUG__PB_MKNAME(__wlen_,__LINE__)) { \
                DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)][                  \
                    DEBUG__PB_MKNAME(__pos_,__LINE__)++                             \
                ] = ' ';                                                            \
            }                                                                       \
        }                                                                           \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][0] =                 \
            DEBUG__PB_MKNAME(__wlen_,__LINE__);                                     \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++;                      \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                    \
            DEBUG__PB_MKNAME(__wlen_,__LINE__);                                     \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

/* ========================= dump helpers (indexed) ========================= */

#define DEBUG_PUSH_BUF_AT_DUMP_I(slotIndex, elemIndex, bufLen)                      \
    DEBUG__PB_BUFDECL(DEBUG_PUSH_BUF_AT_, (bufLen));                                \
    size_t DEBUG_PUSH_BUF_AT_LEN_ = 0;                                              \
    do {                                                                            \
        const char* DEBUG__PB_MKNAME(__p_,__LINE__) = NULL;                         \
        size_t      DEBUG__PB_MKNAME(__n_,__LINE__) = 0;                            \
        DEBUG_PUSH_BUF_AT_I((slotIndex), (elemIndex),                               \
                            DEBUG__PB_MKNAME(__p_,__LINE__),                        \
                            DEBUG__PB_MKNAME(__n_,__LINE__));                       \
        if (DEBUG__PB_MKNAME(__p_,__LINE__)) {                                      \
            size_t DEBUG__PB_MKNAME(__cap_,__LINE__) = (size_t)(((bufLen) > 0) ? (bufLen) : 1); \
            size_t DEBUG__PB_MKNAME(__cpy_,__LINE__) =                              \
                (DEBUG__PB_MKNAME(__n_,__LINE__) < (DEBUG__PB_MKNAME(__cap_,__LINE__) - 1) \
                 ? DEBUG__PB_MKNAME(__n_,__LINE__) : (DEBUG__PB_MKNAME(__cap_,__LINE__) - 1)); \
            if (DEBUG__PB_MKNAME(__cpy_,__LINE__) > 0)                              \
                memcpy(DEBUG_PUSH_BUF_AT_, DEBUG__PB_MKNAME(__p_,__LINE__),         \
                       DEBUG__PB_MKNAME(__cpy_,__LINE__));                          \
            DEBUG_PUSH_BUF_AT_[DEBUG__PB_MKNAME(__cpy_,__LINE__)] = '\0';           \
            DEBUG_PUSH_BUF_AT_LEN_ = DEBUG__PB_MKNAME(__cpy_,__LINE__);             \
        }                                                                           \
    } while (0)

/* legacy single-slot */
#define DEBUG_PUSH_BUF_AT_DUMP(elemIndex, bufLen)                                   \
    DEBUG_PUSH_BUF_AT_DUMP_I(0, (elemIndex), (bufLen))


/* ========================= indexed insert / erase / set ========================= */

/* Insert string as one element at elemIndex in slotIndex. Valid elemIndex: 0..N */
#define DEBUG_INSERT_BUF_STR_I(slotIndex, elemIndex, str)                           \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIndex);              \
        size_t DEBUG__PB_MKNAME(__idx_,__LINE__) = (size_t)(elemIndex);             \
        const char* DEBUG__PB_MKNAME(__s_,__LINE__) = (str);                        \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_INSERT_BUF_STR_I: slot index out of range");       \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_MKNAME(__s_,__LINE__))                                       \
            DEBUG__PB_MKNAME(__s_,__LINE__) = "";                                   \
        if (DEBUG__PB_MKNAME(__idx_,__LINE__) >                                     \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]) {                  \
            DEBUG__PB_ERR("DEBUG_INSERT_BUF_STR_I: element index out of range");    \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) = strlen(DEBUG__PB_MKNAME(__s_,__LINE__)); \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_INSERT_BUF_STR_I: element capacity reached");      \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__), DEBUG__PB_MKNAME(__len_,__LINE__))) { \
            DEBUG__PB_ERR("DEBUG_INSERT_BUF_STR_I: buffer overflow prevented");     \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        /* compute byte offset of insertion point */                                \
        size_t DEBUG__PB_MKNAME(__off_,__LINE__) = 0;                               \
        for (size_t DEBUG__PB_MKNAME(__k_,__LINE__) = 0;                            \
             DEBUG__PB_MKNAME(__k_,__LINE__) < DEBUG__PB_MKNAME(__idx_,__LINE__);   \
             ++DEBUG__PB_MKNAME(__k_,__LINE__)) {                                   \
            DEBUG__PB_MKNAME(__off_,__LINE__) +=                                    \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__k_,__LINE__)]; \
        }                                                                           \
                                                                                    \
        /* shift tail bytes right */                                                \
        if (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                 \
            DEBUG__PB_MKNAME(__off_,__LINE__)) {                                    \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__off_,__LINE__) + DEBUG__PB_MKNAME(__len_,__LINE__), \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__off_,__LINE__),                          \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -         \
                        DEBUG__PB_MKNAME(__off_,__LINE__));                         \
        }                                                                           \
                                                                                    \
        /* shift lens right from idx */                                             \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                   \
            DEBUG__PB_MKNAME(__idx_,__LINE__)) {                                    \
            memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +        \
                        DEBUG__PB_MKNAME(__idx_,__LINE__) + 1,                      \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +        \
                        DEBUG__PB_MKNAME(__idx_,__LINE__),                          \
                    (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] -          \
                     DEBUG__PB_MKNAME(__idx_,__LINE__)) *                           \
                        sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                        \
        }                                                                           \
                                                                                    \
        /* write inserted bytes */                                                  \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > 0) {                                \
            memcpy(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +              \
                       DEBUG__PB_MKNAME(__off_,__LINE__),                           \
                   DEBUG__PB_MKNAME(__s_,__LINE__),                                 \
                   DEBUG__PB_MKNAME(__len_,__LINE__));                              \
        }                                                                           \
                                                                                    \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)] = \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++;                      \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                    \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

/* Insert formatted string as one element at elemIndex in slotIndex.
   Direct-to-destination (no fixed temp buffer).
   Valid elemIndex: 0..N
*/
#define DEBUG_INSERT_BUF_FMT_I(slotIndex, elemIndex, fmt, ...)                      \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIndex);              \
        size_t DEBUG__PB_MKNAME(__idx_,__LINE__) = (size_t)(elemIndex);             \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_INSERT_BUF_FMT_I: slot index out of range");       \
            break;                                                                  \
        }                                                                           \
        if (DEBUG__PB_MKNAME(__idx_,__LINE__) >                                     \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]) {                  \
            DEBUG__PB_ERR("DEBUG_INSERT_BUF_FMT_I: element index out of range");    \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_HAS_ELEM_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__))) {         \
            DEBUG__PB_ERR("DEBUG_INSERT_BUF_FMT_I: element capacity reached");      \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        /* probe formatted length (excluding NUL) */                                \
        int DEBUG__PB_MKNAME(__need_i_,__LINE__) = snprintf(NULL, 0, (fmt), ##__VA_ARGS__); \
        if (DEBUG__PB_MKNAME(__need_i_,__LINE__) < 0) {                             \
            fprintf(stderr, "%s:%d: DEBUG_INSERT_BUF_FMT_I: formatting failed\n",   \
                    __FILE__, __LINE__);                                            \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) =                                  \
            (size_t)DEBUG__PB_MKNAME(__need_i_,__LINE__);                           \
                                                                                    \
        if (!DEBUG__PB_HAS_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__),                 \
                                  DEBUG__PB_MKNAME(__len_,__LINE__))) {             \
            fprintf(stderr,                                                         \
                    "%s:%d: DEBUG_INSERT_BUF_FMT_I: destination too small (need=%zu)\n", \
                    __FILE__, __LINE__, DEBUG__PB_MKNAME(__len_,__LINE__));         \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        /* compute byte offset of insertion point */                                \
        size_t DEBUG__PB_MKNAME(__off_,__LINE__) = 0;                               \
        for (size_t DEBUG__PB_MKNAME(__k_,__LINE__) = 0;                            \
             DEBUG__PB_MKNAME(__k_,__LINE__) < DEBUG__PB_MKNAME(__idx_,__LINE__);   \
             ++DEBUG__PB_MKNAME(__k_,__LINE__)) {                                   \
            DEBUG__PB_MKNAME(__off_,__LINE__) +=                                    \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__k_,__LINE__)]; \
        }                                                                           \
                                                                                    \
        /* shift tail bytes right */                                                \
        if (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                 \
            DEBUG__PB_MKNAME(__off_,__LINE__) &&                                    \
            DEBUG__PB_MKNAME(__len_,__LINE__) > 0) {                                \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__off_,__LINE__) + DEBUG__PB_MKNAME(__len_,__LINE__), \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__off_,__LINE__),                          \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -         \
                        DEBUG__PB_MKNAME(__off_,__LINE__));                         \
        }                                                                           \
                                                                                    \
        /* shift lens right from idx */                                             \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                   \
            DEBUG__PB_MKNAME(__idx_,__LINE__)) {                                    \
            memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +        \
                        DEBUG__PB_MKNAME(__idx_,__LINE__) + 1,                      \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +        \
                        DEBUG__PB_MKNAME(__idx_,__LINE__),                          \
                    (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] -          \
                     DEBUG__PB_MKNAME(__idx_,__LINE__)) *                           \
                        sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                        \
        }                                                                           \
                                                                                    \
        /* write formatted output directly into inserted region */                  \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) > 0) {                                \
            int DEBUG__PB_MKNAME(__n2_,__LINE__) = snprintf(                        \
                DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +                 \
                    DEBUG__PB_MKNAME(__off_,__LINE__),                              \
                DEBUG__PB_MKNAME(__len_,__LINE__) + 1,                              \
                (fmt), ##__VA_ARGS__);                                              \
            if (DEBUG__PB_MKNAME(__n2_,__LINE__) < 0 ||                             \
                (size_t)DEBUG__PB_MKNAME(__n2_,__LINE__) != DEBUG__PB_MKNAME(__len_,__LINE__)) { \
                fprintf(stderr,                                                     \
                        "%s:%d: DEBUG_INSERT_BUF_FMT_I: formatting failed (2nd pass)\n", \
                        __FILE__, __LINE__);                                        \
                /* best effort: keep invariants by still committing metadata/pos */ \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)] = \
                    DEBUG__PB_MKNAME(__len_,__LINE__);                              \
                DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++;              \
                DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=            \
                    DEBUG__PB_MKNAME(__len_,__LINE__);                              \
                DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                 \
                break;                                                              \
            }                                                                       \
        }                                                                           \
                                                                                    \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)] = \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]++;                      \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                    \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

/* Erase one element at elemIndex in slotIndex. Valid elemIndex: 0..N-1 */
#define DEBUG_ERASE_BUF_I(slotIndex, elemIndex)                                     \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIndex);              \
        size_t DEBUG__PB_MKNAME(__idx_,__LINE__) = (size_t)(elemIndex);             \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_ERASE_BUF_I: slot index out of range");            \
            break;                                                                  \
        }                                                                           \
        if (DEBUG__PB_MKNAME(__idx_,__LINE__) >=                                    \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]) {                  \
            DEBUG__PB_ERR("DEBUG_ERASE_BUF_I: element index out of range");         \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        /* compute byte offset */                                                   \
        size_t DEBUG__PB_MKNAME(__off_,__LINE__) = 0;                               \
        for (size_t DEBUG__PB_MKNAME(__k_,__LINE__) = 0;                            \
             DEBUG__PB_MKNAME(__k_,__LINE__) < DEBUG__PB_MKNAME(__idx_,__LINE__);   \
             ++DEBUG__PB_MKNAME(__k_,__LINE__)) {                                   \
            DEBUG__PB_MKNAME(__off_,__LINE__) +=                                    \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__k_,__LINE__)]; \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__len_,__LINE__) =                                  \
            DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)]; \
        size_t DEBUG__PB_MKNAME(__tail_off_,__LINE__) =                             \
            DEBUG__PB_MKNAME(__off_,__LINE__) + DEBUG__PB_MKNAME(__len_,__LINE__);  \
        size_t DEBUG__PB_MKNAME(__tail_len_,__LINE__) =                             \
            (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                \
             DEBUG__PB_MKNAME(__tail_off_,__LINE__))                                \
              ? (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -            \
                 DEBUG__PB_MKNAME(__tail_off_,__LINE__))                            \
              : 0;                                                                  \
                                                                                    \
        /* shift tail bytes left */                                                 \
        if (DEBUG__PB_MKNAME(__tail_len_,__LINE__) > 0) {                           \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__off_,__LINE__),                          \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__tail_off_,__LINE__),                     \
                    DEBUG__PB_MKNAME(__tail_len_,__LINE__));                        \
        }                                                                           \
                                                                                    \
        /* shift lens left */                                                       \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                   \
            DEBUG__PB_MKNAME(__idx_,__LINE__) + 1) {                                \
            memmove(DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +        \
                        DEBUG__PB_MKNAME(__idx_,__LINE__),                          \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +        \
                        DEBUG__PB_MKNAME(__idx_,__LINE__) + 1,                      \
                    (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] -          \
                     DEBUG__PB_MKNAME(__idx_,__LINE__) - 1) *                       \
                        sizeof(DEBUG_PUSH_BUF_LENS_[0][0]));                        \
        }                                                                           \
                                                                                    \
        DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]--;                      \
        if (DEBUG__PB_MKNAME(__len_,__LINE__) >                                     \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)])                  \
            DEBUG__PB_MKNAME(__len_,__LINE__) =                                     \
                DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)];              \
        DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -=                    \
            DEBUG__PB_MKNAME(__len_,__LINE__);                                      \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)

/* Set/overwrite one element at elemIndex in slotIndex (may grow/shrink). */
#define DEBUG_SET_BUF_STR_I(slotIndex, elemIndex, str)                              \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIndex);              \
        size_t DEBUG__PB_MKNAME(__idx_,__LINE__) = (size_t)(elemIndex);             \
        const char* DEBUG__PB_MKNAME(__s_,__LINE__) = (str);                        \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_SET_BUF_STR_I: slot index out of range");          \
            break;                                                                  \
        }                                                                           \
        if (!DEBUG__PB_MKNAME(__s_,__LINE__))                                       \
            DEBUG__PB_MKNAME(__s_,__LINE__) = "";                                   \
        if (DEBUG__PB_MKNAME(__idx_,__LINE__) >=                                    \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]) {                  \
            DEBUG__PB_ERR("DEBUG_SET_BUF_STR_I: element index out of range");       \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__newlen_,__LINE__) = strlen(DEBUG__PB_MKNAME(__s_,__LINE__)); \
                                                                                    \
        /* compute offset */                                                        \
        size_t DEBUG__PB_MKNAME(__off_,__LINE__) = 0;                               \
        for (size_t DEBUG__PB_MKNAME(__k_,__LINE__) = 0;                            \
             DEBUG__PB_MKNAME(__k_,__LINE__) < DEBUG__PB_MKNAME(__idx_,__LINE__);   \
             ++DEBUG__PB_MKNAME(__k_,__LINE__)) {                                   \
            DEBUG__PB_MKNAME(__off_,__LINE__) +=                                    \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__k_,__LINE__)]; \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__oldlen_,__LINE__) =                               \
            DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)]; \
                                                                                    \
        /* if growing, check capacity for delta */                                  \
        if (DEBUG__PB_MKNAME(__newlen_,__LINE__) > DEBUG__PB_MKNAME(__oldlen_,__LINE__)) { \
            size_t DEBUG__PB_MKNAME(__grow_,__LINE__) =                             \
                DEBUG__PB_MKNAME(__newlen_,__LINE__) - DEBUG__PB_MKNAME(__oldlen_,__LINE__); \
            if (!DEBUG__PB_HAS_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__),             \
                                      DEBUG__PB_MKNAME(__grow_,__LINE__))) {        \
                DEBUG__PB_ERR("DEBUG_SET_BUF_STR_I: buffer overflow prevented");    \
                break;                                                              \
            }                                                                       \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__tail_off_,__LINE__) =                             \
            DEBUG__PB_MKNAME(__off_,__LINE__) + DEBUG__PB_MKNAME(__oldlen_,__LINE__); \
        size_t DEBUG__PB_MKNAME(__tail_len_,__LINE__) =                             \
            (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                \
             DEBUG__PB_MKNAME(__tail_off_,__LINE__))                                \
              ? (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -            \
                 DEBUG__PB_MKNAME(__tail_off_,__LINE__))                            \
              : 0;                                                                  \
                                                                                    \
        /* move tail if size changed */                                             \
        if (DEBUG__PB_MKNAME(__tail_len_,__LINE__) > 0 &&                           \
            DEBUG__PB_MKNAME(__newlen_,__LINE__) != DEBUG__PB_MKNAME(__oldlen_,__LINE__)) { \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__off_,__LINE__) + DEBUG__PB_MKNAME(__newlen_,__LINE__), \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__tail_off_,__LINE__),                     \
                    DEBUG__PB_MKNAME(__tail_len_,__LINE__));                        \
        }                                                                           \
                                                                                    \
        /* write replacement bytes */                                               \
        if (DEBUG__PB_MKNAME(__newlen_,__LINE__) > 0) {                             \
            memcpy(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +              \
                       DEBUG__PB_MKNAME(__off_,__LINE__),                           \
                   DEBUG__PB_MKNAME(__s_,__LINE__),                                 \
                   DEBUG__PB_MKNAME(__newlen_,__LINE__));                           \
        }                                                                           \
                                                                                    \
        /* update pos */                                                            \
        if (DEBUG__PB_MKNAME(__newlen_,__LINE__) >= DEBUG__PB_MKNAME(__oldlen_,__LINE__)) \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                \
                (DEBUG__PB_MKNAME(__newlen_,__LINE__) - DEBUG__PB_MKNAME(__oldlen_,__LINE__)); \
        else                                                                        \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -=                \
                (DEBUG__PB_MKNAME(__oldlen_,__LINE__) - DEBUG__PB_MKNAME(__newlen_,__LINE__)); \
                                                                                    \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)] = \
            DEBUG__PB_MKNAME(__newlen_,__LINE__);                                   \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)


/* Set/overwrite one element at elemIndex in slotIndex using printf-style formatting.
   Direct-to-destination (no fixed tmp buffer).
   If formatted output exceeds available capacity growth, operation is aborted.
*/
#define DEBUG_SET_BUF_FMT_I(slotIndex, elemIndex, fmt, ...)                         \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIndex);              \
        size_t DEBUG__PB_MKNAME(__idx_,__LINE__) = (size_t)(elemIndex);             \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_SET_BUF_FMT_I: slot index out of range");          \
            break;                                                                  \
        }                                                                           \
        if (DEBUG__PB_MKNAME(__idx_,__LINE__) >=                                    \
            DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)]) {                  \
            DEBUG__PB_ERR("DEBUG_SET_BUF_FMT_I: element index out of range");       \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        /* probe formatted length (excluding NUL) */                                \
        int DEBUG__PB_MKNAME(__need_i_,__LINE__) = snprintf(NULL, 0, (fmt), ##__VA_ARGS__); \
        if (DEBUG__PB_MKNAME(__need_i_,__LINE__) < 0) {                             \
            fprintf(stderr, "%s:%d: DEBUG_SET_BUF_FMT_I: formatting failed\n",      \
                    __FILE__, __LINE__);                                            \
            break;                                                                  \
        }                                                                           \
        size_t DEBUG__PB_MKNAME(__newlen_,__LINE__) =                               \
            (size_t)DEBUG__PB_MKNAME(__need_i_,__LINE__);                           \
                                                                                    \
        /* compute byte offset of element */                                        \
        size_t DEBUG__PB_MKNAME(__off_,__LINE__) = 0;                               \
        for (size_t DEBUG__PB_MKNAME(__k_,__LINE__) = 0;                            \
             DEBUG__PB_MKNAME(__k_,__LINE__) < DEBUG__PB_MKNAME(__idx_,__LINE__);   \
             ++DEBUG__PB_MKNAME(__k_,__LINE__)) {                                   \
            DEBUG__PB_MKNAME(__off_,__LINE__) +=                                    \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__k_,__LINE__)]; \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__oldlen_,__LINE__) =                               \
            DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)]; \
                                                                                    \
        /* check capacity if growing */                                             \
        if (DEBUG__PB_MKNAME(__newlen_,__LINE__) > DEBUG__PB_MKNAME(__oldlen_,__LINE__)) { \
            size_t DEBUG__PB_MKNAME(__grow_,__LINE__) =                             \
                DEBUG__PB_MKNAME(__newlen_,__LINE__) - DEBUG__PB_MKNAME(__oldlen_,__LINE__); \
            if (!DEBUG__PB_HAS_ROOM_I(DEBUG__PB_MKNAME(__si_,__LINE__),             \
                                      DEBUG__PB_MKNAME(__grow_,__LINE__))) {        \
                fprintf(stderr,                                                     \
                        "%s:%d: DEBUG_SET_BUF_FMT_I: destination too small (need grow=%zu)\n", \
                        __FILE__, __LINE__, DEBUG__PB_MKNAME(__grow_,__LINE__));    \
                break;                                                              \
            }                                                                       \
        }                                                                           \
                                                                                    \
        size_t DEBUG__PB_MKNAME(__tail_off_,__LINE__) =                             \
            DEBUG__PB_MKNAME(__off_,__LINE__) + DEBUG__PB_MKNAME(__oldlen_,__LINE__); \
        size_t DEBUG__PB_MKNAME(__tail_len_,__LINE__) =                             \
            (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] >                \
             DEBUG__PB_MKNAME(__tail_off_,__LINE__))                                \
                ? (DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -          \
                   DEBUG__PB_MKNAME(__tail_off_,__LINE__))                          \
                : 0;                                                                \
                                                                                    \
        /* resize region by moving tail */                                          \
        if (DEBUG__PB_MKNAME(__tail_len_,__LINE__) > 0 &&                           \
            DEBUG__PB_MKNAME(__newlen_,__LINE__) != DEBUG__PB_MKNAME(__oldlen_,__LINE__)) { \
            memmove(DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__off_,__LINE__) + DEBUG__PB_MKNAME(__newlen_,__LINE__), \
                    DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +             \
                        DEBUG__PB_MKNAME(__tail_off_,__LINE__),                     \
                    DEBUG__PB_MKNAME(__tail_len_,__LINE__));                        \
        }                                                                           \
                                                                                    \
        /* write formatted text directly into element region */                     \
        if (DEBUG__PB_MKNAME(__newlen_,__LINE__) > 0) {                             \
            int DEBUG__PB_MKNAME(__n2_,__LINE__) = snprintf(                        \
                DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +                 \
                    DEBUG__PB_MKNAME(__off_,__LINE__),                              \
                DEBUG__PB_MKNAME(__newlen_,__LINE__) + 1,                           \
                (fmt), ##__VA_ARGS__);                                              \
            if (DEBUG__PB_MKNAME(__n2_,__LINE__) < 0 ||                             \
                (size_t)DEBUG__PB_MKNAME(__n2_,__LINE__) != DEBUG__PB_MKNAME(__newlen_,__LINE__)) { \
                fprintf(stderr,                                                     \
                        "%s:%d: DEBUG_SET_BUF_FMT_I: formatting failed (2nd pass)\n", \
                        __FILE__, __LINE__);                                        \
                /* buffer may be partially modified, but keep internal invariants */\
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)] = \
                    DEBUG__PB_MKNAME(__newlen_,__LINE__);                           \
                /* recompute POS_ conservatively from existing POS_ and delta */    \
                if (DEBUG__PB_MKNAME(__newlen_,__LINE__) >= DEBUG__PB_MKNAME(__oldlen_,__LINE__)) \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=        \
                        (DEBUG__PB_MKNAME(__newlen_,__LINE__) - DEBUG__PB_MKNAME(__oldlen_,__LINE__)); \
                else                                                                \
                    DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -=        \
                        (DEBUG__PB_MKNAME(__oldlen_,__LINE__) - DEBUG__PB_MKNAME(__newlen_,__LINE__)); \
                DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                 \
                break;                                                              \
            }                                                                       \
        }                                                                           \
                                                                                    \
        /* update bookkeeping */                                                    \
        if (DEBUG__PB_MKNAME(__newlen_,__LINE__) >= DEBUG__PB_MKNAME(__oldlen_,__LINE__)) \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] +=                \
                (DEBUG__PB_MKNAME(__newlen_,__LINE__) - DEBUG__PB_MKNAME(__oldlen_,__LINE__)); \
        else                                                                        \
            DEBUG_PUSH_BUF_POS_[DEBUG__PB_MKNAME(__si_,__LINE__)] -=                \
                (DEBUG__PB_MKNAME(__oldlen_,__LINE__) - DEBUG__PB_MKNAME(__newlen_,__LINE__)); \
                                                                                    \
        DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)] = \
            DEBUG__PB_MKNAME(__newlen_,__LINE__);                                   \
        DEBUG__PB_TERM_I(DEBUG__PB_MKNAME(__si_,__LINE__));                         \
    } while (0)


/* ========================= indexed pop+dump ========================= */

/* Pop front element from slotIndex and dump to local DEBUG_POP_BUF_FRONT_[bufLen] */
#define DEBUG_POP_BUF_FRONT_DUMP_I(slotIndex, bufLen)                               \
    DEBUG__PB_BUFDECL(DEBUG_POP_BUF_FRONT_, (bufLen));                              \
    size_t DEBUG_POP_BUF_FRONT_LEN_ = 0;                                            \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIndex);              \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_POP_BUF_FRONT_DUMP_I: slot index out of range");   \
            break;                                                                  \
        }                                                                           \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] == 0) {             \
            /* empty: leave "" */                                                   \
        } else {                                                                    \
            size_t DEBUG__PB_MKNAME(__n_,__LINE__) =                                \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][0];          \
            size_t DEBUG__PB_MKNAME(__cap_,__LINE__) =                              \
                (size_t)(((bufLen) > 0) ? (bufLen) : 1);                            \
            size_t DEBUG__PB_MKNAME(__cpy_,__LINE__) =                              \
                (DEBUG__PB_MKNAME(__n_,__LINE__) < (DEBUG__PB_MKNAME(__cap_,__LINE__) - 1) \
                 ? DEBUG__PB_MKNAME(__n_,__LINE__) : (DEBUG__PB_MKNAME(__cap_,__LINE__) - 1)); \
            if (DEBUG__PB_MKNAME(__cpy_,__LINE__) > 0) {                            \
                memcpy(DEBUG_POP_BUF_FRONT_,                                        \
                       DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)],           \
                       DEBUG__PB_MKNAME(__cpy_,__LINE__));                          \
            }                                                                       \
            DEBUG_POP_BUF_FRONT_[DEBUG__PB_MKNAME(__cpy_,__LINE__)] = '\0';         \
            DEBUG_POP_BUF_FRONT_LEN_ = DEBUG__PB_MKNAME(__cpy_,__LINE__);           \
            DEBUG_POP_BUF_FRONT_I(DEBUG__PB_MKNAME(__si_,__LINE__));                \
        }                                                                           \
    } while (0)

/* Pop back element from slotIndex and dump to local DEBUG_POP_BUF_BACK_[bufLen] */
#define DEBUG_POP_BUF_BACK_DUMP_I(slotIndex, bufLen)                                \
    DEBUG__PB_BUFDECL(DEBUG_POP_BUF_BACK_, (bufLen));                               \
    size_t DEBUG_POP_BUF_BACK_LEN_ = 0;                                             \
    do {                                                                            \
        size_t DEBUG__PB_MKNAME(__si_,__LINE__) = (size_t)(slotIndex);              \
        if (!DEBUG__PB_SLOT_OK(DEBUG__PB_MKNAME(__si_,__LINE__))) {                 \
            DEBUG__PB_ERR("DEBUG_POP_BUF_BACK_DUMP_I: slot index out of range");    \
            break;                                                                  \
        }                                                                           \
        if (DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] == 0) {             \
            /* empty: leave "" */                                                   \
        } else {                                                                    \
            size_t DEBUG__PB_MKNAME(__idx_,__LINE__) =                              \
                DEBUG_PUSH_BUF_N_[DEBUG__PB_MKNAME(__si_,__LINE__)] - 1;            \
            size_t DEBUG__PB_MKNAME(__off_,__LINE__) = 0;                           \
            for (size_t DEBUG__PB_MKNAME(__k_,__LINE__) = 0;                        \
                 DEBUG__PB_MKNAME(__k_,__LINE__) < DEBUG__PB_MKNAME(__idx_,__LINE__); \
                 ++DEBUG__PB_MKNAME(__k_,__LINE__)) {                               \
                DEBUG__PB_MKNAME(__off_,__LINE__) +=                                \
                    DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__k_,__LINE__)]; \
            }                                                                       \
            size_t DEBUG__PB_MKNAME(__n_,__LINE__) =                                \
                DEBUG_PUSH_BUF_LENS_[DEBUG__PB_MKNAME(__si_,__LINE__)][DEBUG__PB_MKNAME(__idx_,__LINE__)]; \
            size_t DEBUG__PB_MKNAME(__cap_,__LINE__) =                              \
                (size_t)(((bufLen) > 0) ? (bufLen) : 1);                            \
            size_t DEBUG__PB_MKNAME(__cpy_,__LINE__) =                              \
                (DEBUG__PB_MKNAME(__n_,__LINE__) < (DEBUG__PB_MKNAME(__cap_,__LINE__) - 1) \
                 ? DEBUG__PB_MKNAME(__n_,__LINE__) : (DEBUG__PB_MKNAME(__cap_,__LINE__) - 1)); \
            if (DEBUG__PB_MKNAME(__cpy_,__LINE__) > 0) {                            \
                memcpy(DEBUG_POP_BUF_BACK_,                                         \
                       DEBUG_PUSH_BUF_[DEBUG__PB_MKNAME(__si_,__LINE__)] +          \
                           DEBUG__PB_MKNAME(__off_,__LINE__),                       \
                       DEBUG__PB_MKNAME(__cpy_,__LINE__));                          \
            }                                                                       \
            DEBUG_POP_BUF_BACK_[DEBUG__PB_MKNAME(__cpy_,__LINE__)] = '\0';          \
            DEBUG_POP_BUF_BACK_LEN_ = DEBUG__PB_MKNAME(__cpy_,__LINE__);            \
            DEBUG_POP_BUF_BACK_I(DEBUG__PB_MKNAME(__si_,__LINE__));                 \
        }                                                                           \
    } while (0)

#define DEBUG_SET_BUF_INT_I(slotIndex, elemIndex, num)                              \
    DEBUG_SET_BUF_FMT_I((slotIndex), (elemIndex), "%d", (num))
	
#define DEBUG_INSERT_BUF_INT_I(slotIndex, elemIndex, num)                           \
    DEBUG_INSERT_BUF_FMT_I((slotIndex), (elemIndex), "%d", (num))

#define DEBUG_SET_BUF_PTR_I(slotIndex, elemIndex, ptr)                              \
    do {                                                                            \
        const void* DEBUG__PB_MKNAME(__p_,__LINE__) = (const void*)(ptr);           \
        if (DEBUG__PB_MKNAME(__p_,__LINE__) == NULL)                                \
            DEBUG_SET_BUF_STR_I((slotIndex), (elemIndex), "0x0");                   \
        else                                                                        \
            DEBUG_SET_BUF_FMT_I((slotIndex), (elemIndex), "0x%" PRIxPTR,            \
                               (uintptr_t)DEBUG__PB_MKNAME(__p_,__LINE__));         \
    } while (0)

#define DEBUG_INSERT_BUF_PTR_I(slotIndex, elemIndex, ptr)                           \
    do {                                                                            \
        const void* DEBUG__PB_MKNAME(__p_,__LINE__) = (const void*)(ptr);           \
        if (DEBUG__PB_MKNAME(__p_,__LINE__) == NULL)                                \
            DEBUG_INSERT_BUF_STR_I((slotIndex), (elemIndex), "0x0");                \
        else                                                                        \
            DEBUG_INSERT_BUF_FMT_I((slotIndex), (elemIndex), "0x%" PRIxPTR,         \
                                   (uintptr_t)DEBUG__PB_MKNAME(__p_,__LINE__));     \
    } while (0)


/* single slot */
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


#endif /* DEBUG_PUSH_BUF_INDEXED_H_ */