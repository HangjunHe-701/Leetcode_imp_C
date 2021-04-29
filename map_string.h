// build with rbtree.c
// This is a linux rbtree based simple map implemantation
#ifndef _MAP_H
#define _MAP_H

#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// rb_root_t tree = RB_ROOT;

typedef struct map {
    struct rb_node node;
    char *key;
    char *val;
} map_t;

typedef struct rb_root rb_root_t;
typedef struct rb_node rb_node_t;

map_t *get(rb_root_t *root, char *key)
{
   rb_node_t *node = root->rb_node; 

   while (node) {
        map_t *data = container_of(node, map_t, node);

        // compare between the key with the keys in map
        int cmp = strcmp(key, data->key);
        if (cmp < 0) {
            node = node->rb_left;
        } else if (cmp > 0) {
            node = node->rb_right;
        } else {
            return data;
        }
   }
   return NULL;
}

int put(rb_root_t *root, char* key, char* val)
{
    map_t *data;
    rb_node_t **new_node = &(root->rb_node), *parent = NULL;

    while (*new_node) {
        map_t *this_node = container_of(*new_node, map_t, node);
        int result = strcmp(key, this_node->key);
        parent = *new_node;

        if (result < 0) {
            new_node = &((*new_node)->rb_left);
        } else if (result > 0) {
            new_node = &((*new_node)->rb_right);
        } else {
			// updated
            strcpy(this_node->val, val);
            return 0;
        }
    }

	// new data
    data = (map_t*)malloc(sizeof(map_t));
    data->key = strdup(key);
    data->val = strdup(val);
    rb_link_node(&data->node, parent, new_node);
    rb_insert_color(&data->node, root);

    return 1;
}

map_t *map_first(rb_root_t *tree)
{
    rb_node_t *node = rb_first(tree);
    return (rb_entry(node, map_t, node));
}

map_t *map_next(rb_node_t *node)
{
    rb_node_t *next =  rb_next(node);
    return rb_entry(next, map_t, node);
}

void map_free(map_t *node)
{
    if (node != NULL) {
        if (node->key != NULL) {
            free(node->key);
            node->key = NULL;
            free(node->val);
            node->val = NULL;
		}
        free(node);
        node = NULL;
    }
}

void map_destroy(rb_root_t *root)
{
    rb_node_t *node = rb_first(root);
	
	while (node) {
		map_free(rb_entry(node, map_t, node));
		rb_erase(node, root);
		node = rb_first(root);
	}	
}
#endif  //_MAP_H

