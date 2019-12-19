/*
 * Copyright (c) 2018, 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All
 * rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
