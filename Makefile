
DEFULT_C=gcc
STD=--std=c11
do :
	$(DEFULT_C) main.c -o f2h $(STD)
install:do
	@echo "This will copy the f2h excutabel to the Bin folder"
	@echo 3
	@sleep 1
	@echo 2
	@sleep 1
	@echo 1
	@sleep 1
	cp f2h /bin/
