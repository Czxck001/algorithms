#include <queue>
#include <stack>

// Goal: O(1) price to maintain the max number in a queue / stack.
//
// Mono queue / stack is constructed as an appendix of the main queue / stack.
//
// In goal of maintain the max number in the main container, the appendix is
// applied by a specific rule of push / pop. This rule keeps itself monotonic.
//
// NOTE: Elements in the appendix is featured elements that won't be
// overrided by other elements nearby.
// NOTE: The following example assumes each of the elements is unique.

template <T>
class MonoQueue {
public:
  std::queue<T> mono, queue;
  MonoQueue() : mono(), queue() {}

  void push(T v) {
    // The new element will override elements in front, until a bigger
    // element is meet. Because FIFO, a element in front won't regain the
    // chance once it is beaten by the newcomer.
    while (v > mono.back()) {
      mono.pop();
    }

    // NOTE: At first, the new element is always pushed into the mono queue.
    // This means the new element will always get a chance to become the best
    // (at least when all of the other elements are poped out).
    mono.push(v);
    queue.push(v);
  }

  T pop() {
    auto v = queue.pop();
    if (v == mono.front()) {
      mono.pop();
    }
    return v;
  }

  T get_max() {
    // The maximum is at the front of the mono queue. It beats all of the
    // old elements when it is pushed in, and it has not been beaten by the
    // newcomers.
    // Although it may not be the best at the time it comes to the queue,
    // the obstacles has already come out of the queue (FIFO).
    return mono.front();
  }
};


template <T>
class MonoStack {
public:
  std::stack<T> mono, stack;
  MonoStack() : mono(), stack() {}

  void push(T, v) {
    // The new element will be kicked out if it cannot beat the current best
    // in the queue. Because LIFO, once a new element is pushed, there will be
    // the best scenerio. If it cannot overcome the old best, it won't win
    // forever.
    //
    // Different from the queue case, even if the old best is beaten by the
    // new, the old may regain its status once the new is poped out (LIFO).
    if (v > mono.top()) {
      mono.push(v);
    }
    stack.push(v);
  }

  T pop() {
    auto v = stack.pop();
    if (v == mono.top()) {
      mono.pop();
    }
    return v;
  }

  T get_max() {
    // The maximum is at the top of the stack. Simply means it beats the old
    // best when it is pushed in the stack, and it has not been beaten by the
    // newscomers.
    return mono.top();
  }
};
