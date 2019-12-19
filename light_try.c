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
#include <stdlib.h>

#ifdef _MSC_VER
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "light_try.h"

typedef struct ___LtEnvNode ___LtEnvNode;
struct ___LtEnvNode {
	jmp_buf env;
	___LtEnvNode *next;
};

#ifdef _MSC_VER
#define __thread __declspec(thread)
#endif

static __thread ___LtEnvNode *env_stack;
static __thread bool is_throw;
static __thread bool try_condtion;

jmp_buf *___lt_push() {
	if (env_stack) {
		___LtEnvNode *new_env_node = malloc(sizeof(___LtEnvNode));
		new_env_node->next = env_stack;
		env_stack = new_env_node;
	} else {
		env_stack = malloc(sizeof(___LtEnvNode));
		env_stack->next = NULL;
	}
	return &(env_stack->env);
}

static void ___lt_pop() {
	___LtEnvNode *top_env_node = env_stack;
	env_stack = top_env_node->next;
	free(top_env_node);
}

void ___lt_try_begin(int val) {
	if (val) {
		___lt_pop();
		is_throw = true;
		try_condtion = false;
	} else {
		is_throw = false;
		try_condtion = true;
	}
}

bool ___lt_try_condition() {
	return try_condtion;
}

void ___lt_try_end() {
	___lt_pop();
	is_throw = false;
	try_condtion = false;
}

bool ___lt_catch() {
	return is_throw;
}

void ___lt_throw() {
	if (env_stack) {
		longjmp(env_stack->env, 1);
	} else {
#ifdef _MSC_VER
		ExitThread(0);
#else
		pthread_exit(NULL);
#endif
	}
}
