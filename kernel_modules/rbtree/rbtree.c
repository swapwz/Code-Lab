#include <linux/init.h>
#include <linux/module.h>
#include <linux/rbtree.h>
#include <linux/slab.h>

struct tree_data {
    struct rb_node node;
    int key;
};

struct rb_root g_root = RB_ROOT;

void show_rbtree(void)
{
    struct rb_node *node;
    struct tree_data *data;

    for (node = rb_first(&g_root); node != NULL; node = rb_next(node)) {
        data = rb_entry(node, struct tree_data, node);
        printk("Node data: %d\n", data->key);
    }
}

int insert_rbtree(struct rb_root *root, struct tree_data *data)
{
    struct rb_node **new = &(root->rb_node);
    struct rb_node *parent = NULL;

    while (*new) {
        struct tree_data *this = container_of(*new, struct tree_data, node);

        parent = *new;
        printk("this->key %d, data->key %d\n", this->key, data->key);
        if (data->key < this->key) {
            new = &((*new)->rb_left);
        } else if (data->key > this->key) {
            new = &((*new)->rb_right); 
        } else {
            return -1;
        }
    }

    rb_link_node(&data->node, parent, new);
    rb_insert_color(&data->node, root); 

    return 0;
}

void construct_rbtree(int node_num)
{
    int i;
    struct tree_data *data;

    for (i = 0; i < node_num; i++)  {
        data = kmalloc(sizeof(struct tree_data), GFP_KERNEL); 
        if (data) {
            data->key = i; 
            if (0 == insert_rbtree(&g_root, data)) {
                printk("insert data %d\r\n", data->key);
            } else {
                printk("insert failed for %d\n", data->key);
                kfree(data);
            }
        }
    }
}

static int __init rb_init(void)
{
    construct_rbtree(10);
    show_rbtree();
    return 0;
}

static void __exit rb_exit(void)
{
    struct rb_node *node;
    struct tree_data *data;    

    for (node = rb_first(&g_root); node != NULL; ) {
        data = rb_entry(node, struct tree_data, node);
        node = rb_next(node);
        if (data) {
            rb_erase(&data->node, &g_root);
            kfree(data);
        }
    }
}

module_init(rb_init);
module_exit(rb_exit);
