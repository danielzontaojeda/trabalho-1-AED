gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/util.c -o obj/util.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/main.c -o obj/main.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/header.c -o obj/header.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/order.c -o obj/order.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/input_file.c -o obj/input_file.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/screen.c -o obj/screen.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/product.c -o obj/product.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/binary_file.c -o obj/binary_file.o
gcc -Iinclude -MMD -MP -W -Wall -pedantic -c src/linked_list.c -o obj/linked_list.o
gcc -Llib obj/util.o obj/main.o obj/header.o obj/order.o obj/input_file.o obj/screen.o obj/product.o obj/binary_file.o obj/linked_list.o -lm -o bin/main.exe