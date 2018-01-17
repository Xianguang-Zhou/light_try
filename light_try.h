/*
 * Copyright (c) 2018, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LIGHT_TRY_H
#define LIGHT_TRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <setjmp.h>

jmp_buf *___lt_push();
void ___lt_try_begin(int val);
bool ___lt_try_condition();
void ___lt_try_end();
bool ___lt_catch();
void ___lt_throw();

#define lt_try for (___lt_try_begin(setjmp(*___lt_push())); ___lt_try_condition(); ___lt_try_end())
#define lt_catch if (___lt_catch())
#define lt_throw ___lt_throw()

#ifdef __cplusplus
}
#endif

#endif

