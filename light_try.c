/*
 * Copyright (c) 2018, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdlib.h>
#include "light_try.h"

typedef struct ___LtEnvNode ___LtEnvNode;
struct ___LtEnvNode {
	jmp_buf env;
	___LtEnvNode *next;
};

static __thread ___LtEnvNode *env_stack;
static __thread bool is_throw;
static __thread bool try_condtion;

struct __jmp_buf_tag *___lt_push() {
	if (env_stack) {
		___LtEnvNode *new_env_node = malloc(sizeof(___LtEnvNode));
		new_env_node->next = env_stack;
		env_stack = new_env_node;
	} else {
		env_stack = malloc(sizeof(___LtEnvNode));
		env_stack->next = NULL;
	}
	return env_stack->env;
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
		exit(1);
	}
}

