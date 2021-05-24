#ifndef PS_HASHMAP_IMPL
#define PS_HASHMAP_IMPL

#include <stdlib.h>

typedef void (*mapconsumer)(void *value);

template <class K, class V>
struct hmap_data_node {

	struct hmap_data_node *next;
	K key;
	V value;
};

template <class K, class V>
struct hmap_data {

	struct hmap_data_node<K, V> **data;
	size_t size;
	// Long if the user's hash function returns a negative value.
	long (*hash_func)(K);
};

template <class K, class V>
struct hmap_data<K, V> *genmap(size_t size, long (*hash_func)(K)) {

	// Can't create map without hash function, sorry.
	if (!hash_func)
		return NULL;

	struct hmap_data<K, V> *map = (struct hmap_data<K, V>*) malloc(sizeof(struct hmap_data<K, V>));
	if (!map)
		return NULL;

	map->data = (struct hmap_data_node<K, V>**) calloc(size, sizeof(struct hmap_data_node<K, V>*));
	if (!map->data) {
		free(map);
		return NULL;
	}

	map->size = size;
	map->hash_func = hash_func;

	return map;
}

template <class K, class V>
void freemap(struct hmap_data<K, V> *map, mapconsumer consumer = NULL) {

	if (!map)
		return;

	for (size_t i = 0; i < map->size; i++) {
		struct hmap_data_node<K, V> *ptr = map->data[i];
		while (ptr) {
			struct hmap_data_node<K, V> *tmp = ptr->next;
			if (consumer)
				consumer(&ptr->value);

			free(ptr);
			ptr = tmp;
		}

	}

	free(map->data);
	free(map);
}

// Appends the pair if not present, else replaces the old one.
template <class K, class V>
void putmap(struct hmap_data<K, V> *map, K &key, V &value) {

	if (!map)
		return;

	size_t index = map->hash_func(key) % map->size;
	struct hmap_data_node<K, V> *node = map->data[index];
	while (node && node->key != key) {
		node = node->next;
	}

	if (node) {
		node->value = value;
	}
	else {
		struct hmap_data_node<K, V> *ptr = (hmap_data_node<K, V>*) malloc(sizeof(struct hmap_data_node<K, V>));
		if (!ptr)
			return;

		ptr->key = key;
		ptr->value = value;
		ptr->next = map->data[index];
		map->data[index] = ptr;
	}

}

template <class K, class V>
void getmap(struct hmap_data<K, V> *map, K &key, V *dest) {

	if (!map)
		return;

	struct hmap_data_node<K, V> *node = map->data[map->hash_func(key) % map->size];
	if (!node)
		return;

	do {
		if (key == node->key)
			*dest = node->value;

	} while ((node = node->next));
}

template <class K, class V>
int containsmap(struct hmap_data<K, V> *map, K &key, int (*comp)(K, K)) {

	if (!map)
		return 0;

	struct hmap_data_node<K, V> *node = map->data[map->hash_func(key) % map->size];
	if (!node)
		return 0;

	do {
		if (!comp(node->key, key))
			return 1;

	} while ((node = node->next));

	return 0;
}

template <class K, class V>
void removemap(struct hmap_data<K, V> *map, K &key) {

	if (!map)
		return;

	size_t index = map->hash_func(key) % map->size;
	struct hmap_data_node<K, V> *prev = map->data[index];
	if (!prev) {
		return;
	}
	else if (key == prev->key) {
		map->data[index] = prev->next;
		free(prev);
		return;
	}

	while (prev->next) {
		if (key == prev->next->key) {
			struct hmap_data_node<K, V> *tmp = prev->next;
			prev->next = tmp->next;
			free(tmp);
			break;
		}

		prev = prev->next;
	}

}

#endif