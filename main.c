#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define SIZE 64
#define stack_push(stack, ...) stack_push_null(stack, __VA_ARGS__, NULL);

// TODO: Make polish_stack_t.stack a dynamic array. DONE !!
typedef struct polish_stack {
		int stack_pointer;
		int capacity;
		int *stack;
	} polish_stack_t;

// TODO: Make stack_push check if polish-stack_t.stack has available space. If not realloc. DONE!!
//	 Make stack_push a varyadic function. DONE!!
//	 Input checking for unexcpected input values.
void stack_push_null(polish_stack_t *stack, ...); // Push a number onto the stack
int stack_pop(polish_stack_t *stack); // Pop the last number from the stack
void stack_sum(polish_stack_t *stack); // Pop the last two number from the stack and push onto the stack the sum between them
void stack_sub(polish_stack_t *stack); // Pop the last two number from the stack and push onto the stack the difference between them
void stack_mul(polish_stack_t *stack); // Pop the last two number from the stack and push onto the stack the product between them
void stack_div(polish_stack_t *stack); // Pop the last two number from the stack anche push onto the stack the quotient between them
void stack_print(polish_stack_t *stack); // Print the current stack

void stack_push_null(polish_stack_t *stack, ...) {
	if ((stack->stack_pointer +1) > stack->capacity) {
		stack->capacity *= 2;
		stack->stack = (int*) realloc(stack->stack, stack->capacity);
	}
	va_list args;
	va_start(args, stack);
	int pushed_num = va_arg(args, int);
	stack->stack[stack->stack_pointer] = pushed_num;
	stack->stack_pointer++;
	int keep_polling = 1;
	while (keep_polling) {
		pushed_num = va_arg(args, int);
		if (pushed_num != NULL) {
			stack->stack[stack->stack_pointer] = pushed_num;
			stack->stack_pointer++;
		} else {
			keep_polling = 0;
		}
	}
	va_end(args);
	return;
}

int stack_pop(polish_stack_t *stack) {
	int popped_num;
	popped_num = stack->stack[--stack->stack_pointer];
	return popped_num;
}

void stack_sum(polish_stack_t *stack) {
	int result = stack_pop(stack) + stack_pop(stack);
	stack_push(stack, result);
	return;
}

void stack_sub(polish_stack_t *stack) {
	int result;
	int a = stack_pop(stack);
	int b = stack_pop(stack);
	result = b - a;
	stack_push(stack, result);
	return;
}
 
void stack_mul(polish_stack_t *stack) {
	int result = stack_pop(stack) * stack_pop(stack);
	stack_push(stack, result);
	return;
}

void stack_div(polish_stack_t *stack) {
	int result;
	int a = stack_pop(stack);
	int b = stack_pop(stack);
	result = b / a;
	stack_push(stack, result);
	return;
}

void stack_print(polish_stack_t *stack) {
	printf("%s ", "Stack:");
	for (int i = 0; i < stack->stack_pointer; i++) {
		printf("%d ", stack->stack[i]);
	}
	printf(" - Current stack pointer: %d\n", stack->stack_pointer);
	return;
}

int main(void) {
	polish_stack_t stack = {
		.stack_pointer = 0,
		.capacity = SIZE,
		.stack = (int*) malloc(sizeof(int) * SIZE)
	};
	stack_push(&stack, 5);
	stack_push(&stack, 5);
	stack_print(&stack);
	stack_push(&stack, 5);
	stack_print(&stack);
	stack_push(&stack, 5);
	stack_print(&stack);
	stack_push(&stack, 5);
	stack_print(&stack);
	return 0;
}
