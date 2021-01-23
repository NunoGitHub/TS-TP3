build: passthrough.c managePermission.c
	gcc -Wall -std=c11 -pthread passthrough.c managePermission.c `pkg-config fuse3 --cflags --libs` -o passthrough

exec:
	./passthrough -f $(path)

clean:
	rm -f passthrough

