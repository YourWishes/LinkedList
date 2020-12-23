OBJS := ./main.c ./../../src/list.c
CC := gcc
OUT := out

ifeq ($(OS),Windows_NT) 
	OUT := $(OUT).exe
endif

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)