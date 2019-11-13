test: all
	$(CC) test/main.cpp -g3 -L. -l$(LIB_NAME)
	# -Wl,-rpath,. ## should i use it ?