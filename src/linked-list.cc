template <T>
class Node {
public:
  T val;
  Node * next;
};


// This what Linus Torvalds' mentioned in TED Talk as a "good taste code".
// https://www.ted.com/talks/linus_torvalds_the_mind_behind_linux#t-855933
//
// It uses a pointer to pointer of the Node to traverse the linked list
// (actually traverse the "next" pointer in Node).
// Linus said the goodness of this code is it eliminate edge conditions which
// is inevitable if you use a pointer to Node to traverse the linked list.
//
// What I understand is that this approach use the pointer that directly
// points to what is needed to be changed. This ensured the code is simple and
// does not contain unnecessary "edge case".
// Since what is needed to be changed is actually "next", which is a pointer
// to Node, the pointer to traverse should be a pointer to pointer of Node.

template <T>
void delete_node(Node *head, Node *entry) {
  Node **indirect = &head;
  while (*indirect != entry) {
    indirect = &(*indirect)->next;
  }
  *indirect = entry->next;
}
