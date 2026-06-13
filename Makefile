
DEFULT_C=gcc
STD=--std=c11
do :
	$(DEFULT_C) main.c -o f2h $(STD)
install:do
	@echo "This will copy the f2h excutabel to the Bin folder"
	sudo cp f2h /bin/
