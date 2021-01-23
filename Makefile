build: passthrough.c managePermission.c
	@echo "Compilation Initiated"
	gcc -Wall passthrough.c managePermission.c `pkg-config fuse3 --cflags --libs` -o passthrough
	@echo "Compilation Finished"

exec:
	@echo "Running"
	./passthrough -f $(path)

clean:
	rm -f passthrough

