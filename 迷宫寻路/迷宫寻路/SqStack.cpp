#include "Header.h"
int SqStack::InitStack(void)
{
	this->base = (ElemType*)malloc(STACK_INT_SIZE*sizeof(ElemType));
	if (!this->base) {
		return ERROR;
	}
	this->top = this->base;
	this->stacksize = STACK_INT_SIZE;
	return OK;
}

int SqStack::StackEmpty(void)
{
	if (this->base == this->top) {
		return OK;
	}
	else {
		return ERROR;
	}
}

int SqStack::ClearStack(void)
{
	this->top = this->base;
	return OK;
}

int SqStack::StackLength(void)
{
	return this->top - this->base;
}

int SqStack::Push(ElemType e)
{
	if ((this->top - this->base) >= this->stacksize) {
		this->base = (ElemType*)realloc(this->base, (stacksize + STACKINCREMENT)*sizeof(ElemType));
		if (this->base==NULL) {
			return ERROR;
		}
		this->top = this->base + sizeof(ElemType)*this->stacksize;
		this->stacksize += STACKINCREMENT;
	}
	*this->top++ = e;
	return OK;
}

int SqStack::Pop(ElemType *e)
{
	if (this->base == this->top) {
		return ERROR;
	}
	*e = *(--(this->top));
	return OK;
}

int SqStack::GetTop(ElemType *e)
{
	if (this->base == this->top) {
		return ERROR;
	}
	*e = *(this->top - 1);
	return OK;
}

void SqStack::ShowStack(void)
{
	SqStack temp = *this;
	char c;
	while (!temp.StackEmpty())
	{
		temp.Pop(&c);
		printf("%c ", c);
	}
	printf("\n");
}