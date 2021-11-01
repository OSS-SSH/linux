=====================================
Linux Memory Management Documentation
=====================================

This is a collection of documents about the Linux memory management (mm)
subsystem.  If you are looking for advice on simply allocating memory,
see the :ref:`memory_allocation`.

User guides for MM features
===========================

The following documents provide guides for controlling and tuning
various features of the Linux memory management

.. toctree::
   :maxdepth: 1

   swap_numa
   zswap

Kernel developers MM documentation
==================================

The below documents describe MM internals with different level of
details ranging from notes and mailing list responses to elaborate
descriptions of data structures and algorithms.

.. toctree::
   :maxdepth: 1

   active_mm
   arch_pgtable_helpers
   balance
   cleancache
<<<<<<< HEAD
<<<<<<< HEAD
   damon/index
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
   damon/index
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
   free_page_reporting
   frontswap
   highmem
   hmm
   hwpoison
   hugetlbfs_reserv
   ksm
   memory-model
   mmu_notifier
   numa
   overcommit-accounting
   page_migration
   page_frags
   page_owner
   remap_file_pages
   slub
   split_page_table_lock
   transhuge
   unevictable-lru
   z3fold
   zsmalloc
