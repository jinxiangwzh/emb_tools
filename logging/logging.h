/*
 * @Author: jinxiangwzh jinxiangwzh@163.com
 * @Date: 2023-03-01 15:02:37
 * @LastEditors: wzh
 * @LastEditTime: 2023-08-22 15:14:36
 * @FilePath: /protocol/include/mft_dbg.h
 * @Description:
 *
 * Copyright (c) 2023 by Inomec, All Rights Reserved.
 */
#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

extern int logging_level;

#define DEBUG_LEVEL 3
#define INFO_LEVEL 2
#define WARNING_LEVEL 1
#define ERROR_LEVEL 0

#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define dbg(x, arg...)                                            \
    do                                                            \
    {                                                             \
        if (logging_level >= 3)                                   \
        {                                                         \
            printf("\033[1m\033[;33m[debug] %s:%d] " x "\033[0m\r\n", __func__, __LINE__, ##arg); \
        }                                                         \
    } while (0)

#define info(x, arg...)                                          \
    do                                                           \
    {                                                            \
        if (logging_level >= 2)                                  \
        {                                                        \
            printf("\033[1m\033[;35m[info] %s:%d] " x "\033[0m\r\n",  __func__, __LINE__, ##arg); \
        }                                                        \
    } while (0)

#define warn(x, arg...)                                          \
    do                                                           \
    {                                                            \
        if (logging_level >= 1)                                  \
        {                                                        \
            printf("\033[1m\033[;36m[warn] %s:%d] " x "\033[0m\r\n",  __func__, __LINE__, ##arg); \
        }                                                        \
    } while (0)

// print when error happens
#define err(x, arg...)                                            \
    do                                                            \
    {                                                             \
        if (logging_level >= 0)                                   \
        {                                                         \
            printf("\033[1m\033[;31m[error] %s:%d] " x "\033[0m\r\n",  __func__, __LINE__, ##arg); \
        }                                                         \
    } while (0)

/*
 * ASSERT_MSG is a macro name that can be used in code and takes two
  * arguments: condition and message. If the condition is false,
  * the macro prints an error message with the information and
  * terminates program execution.
*/
#ifndef ASSERT_MSG
#define ASSERT_MSG(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s, file %s, line %d: %s\r\n", \
                    #condition, __FILE__, __LINE__, message); \
        } \
    } while (0)
#endif

#ifndef PRINT_FUNC
#define PRINT_FUNC() printf("%s\n", __func__)
#endif

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief set device log level.
     * @param level - DEBUG:3,INFO:2,WARN:1,ERROR:0
     */
    void set_log_level(int level);
#ifdef __cplusplus
}
#endif

#endif // @page end
