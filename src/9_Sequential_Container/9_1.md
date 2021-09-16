* a: for a fixed amount of words, to insert them in lexical order, use list, because keeping lexical order requires insert between elements

* b: unknown amount of words, and insert new word into end, delete in the beginning, use deque.
for vector, it keeps a continuous memory space, and since operation only happens in beginning and end
use deque is the best match

* c: for unknown amount of words, and need to sort and print into std stream, should use vector