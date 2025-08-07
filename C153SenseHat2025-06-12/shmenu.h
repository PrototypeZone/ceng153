/** @brief Structures, function prototypes for examples of sense-hat usage
 *  @file shmenu.h
 *  @since 2024-03-12
 */
#ifndef SHMENU_H
#define SHMENU_H

// Includes
#include "led2472g.h"
#include "hts221.h"
#include "lps25h.h"
#include "lsm9ds1.h"
#include "tcs3400.h"

// Constants

// Enumerated Types

// Structures

// Function Prototypes
/// @cond INTERNAL
int led2472g(void);
int game(void);
void hts221(void);
void lps25h(void);
void lsm9ds1(void);
void tcs3400(void);
int shtest(void);
/// @endcond

#endif // SHMENU_H