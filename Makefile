executaveis: main.c #passthrough.c passthrough.h
    gcc -o main.c  `pkg-config fuse3 --cflags --libs` 

clean:
    rm main passthrough   
