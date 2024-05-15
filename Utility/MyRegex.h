#define __INT_MAX_MIN_2_9 "(([0-1]\\d{0,9})|([0-2][0]\\d{0,8})|([0-2][0-1][0-3]\\d{0,7})|([0-2][0-1][0-4][0-6]\\d{0,6})|([0-2][0-1][0-4][0-7][0-3]\\d{0,5})|([0-2][0-1][0-4][0-7][0-4][0-7]\\d{0,4})|([0-2][0-1][0-4][0-7][0-4][0-8][0-2]\\d{0,3})|([0-2][0-1][0-4][0-7][0-4][0-8][0-3][0-5]\\d{0,2})|([0-2][0-1][0-4][0-7][0-4][0-8][0-3][0-6][0-3]\\d{0,1}))"
#define __INT_MAX_2_10 "(" __INT_MAX_MIN_2_9 "|([0-2][0-1][0-4][0-7][0-4][0-8][0-3][0-6][0-4][0-7]))"
#define __INT_MAX_1_10 "((\\d{1,9})|" __INT_MAX_2_10 ")"
#define __INT_MAX_0_10 "((\\d{0,9})|" __INT_MAX_2_10 ")"
#define __POINT_1 "(\\." __INT_MAX_1_10 ")"
#define __POINT_0 "(\\." __INT_MAX_0_10 ")"
#define __INT_MAX_1_10_POINT_0 "(" __INT_MAX_1_10 __POINT_0 "?)"

#define __INT_MIN_2_10 "(" __INT_MAX_MIN_2_9 "|([0-2][0-1][0-4][0-7][0-4][0-8][0-3][0-6][0-4][0-8]))"
#define __INT_MIN_1_10 "((\\d{1,9})|" __INT_MIN_2_10 ")"
#define __INT_MIN_1_10_POINT_0 "(" __INT_MIN_1_10 __POINT_0 "?)"

// For unsigned decimal number pattern, common examples are 5, 5.0, 12.5, 25.00 and 0
// [0,2147483647].[0,2147483647] inclusive
// The regex is based on INT_MAX value of 0x7FFFFFFF, and may need revisiting in the future if that value were to change
#define MY_DECIMAL_NUMBER_PATTERN "^(" __POINT_1 "|" __INT_MAX_1_10_POINT_0 ")$"
// Signed decimal number pattern
// [-2147483648,2147483647].[0,2147483647] inclusive
#define MY_DECIMAL_NUMBER_PATTERN_SIGNED "^((\\-?" __POINT_1 ")|" __INT_MAX_1_10_POINT_0 "|(\\-" __INT_MIN_1_10_POINT_0 "))$"
