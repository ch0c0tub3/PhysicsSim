#ifndef PS_HASHFUNCS
#define PS_HASHFUNCS

// Ready to use hash function for char arrays.
inline long hash_chrp(const char *key) {

	long hash = 0;
	while (*key) {
		hash += *key++;
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	return hash;
}

#endif