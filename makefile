
count_sketch: $(count_sketch.c)
	gcc -Wall -g -o count_sketch count_sketch.c massdal/prng.c

fm_sketch: $(fm_sketch.c)
	gcc -Wall -g -o fm_sketch fm_sketch.c massdal/prng.c

hash_chaining_topk: $(hash_chaining_topk.c)
	gcc -Wall -g -o hash_chaining_topk.c massdal/prng.c
