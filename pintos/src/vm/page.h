#ifndef VM_PAGE_H
#define VM_PAGE_H

#include <stdint.h>
#include <debug.h>
#include <list.h>
#include <hash.h>
#include "threads/palloc.h"

extern struct lock lru_list_lock;

enum vm_type
  {
    VM_ANON,
    VM_FILE,
    VM_BIN
  };



struct page
  {
    void *kaddr;
    struct vm_entry *vme;
    struct thread *thread;
    struct list_elem lru;
  };

struct vm_entry
  {
    uint8_t type;
    void *vaddr;
    bool writable;
    bool is_loaded;
    bool pinned;
    struct file *file;
    struct list_elem mmap_elem;
    size_t offset;
    size_t read_bytes;
    size_t zero_bytes;
    size_t swap_slot;
    struct hash_elem elem;
  };

static unsigned vm_hash_func (const struct hash_elem *, void * UNUSED);
static bool vm_less_func (const struct hash_elem *, const struct hash_elem *, void * UNUSED);
static void vm_destroy_func (struct hash_elem *, void * UNUSED);

void vm_init (struct hash *);
void vm_destroy (struct hash *);

struct vm_entry *find_vme (void *vaddr);
bool insert_vme (struct hash *, struct vm_entry *);
bool delete_vme (struct hash *, struct vm_entry *);

bool load_file (void *kaddr, struct vm_entry *);

struct page *alloc_page (enum palloc_flags);
void free_page (void *);
void free_page_thread (struct thread *);
void __free_page (struct page *);

#endif
