#include "branched-linked-list.hpp"

#include <stdexcept>

BLL::BLL(): head_(nullptr) {}

// destructor
BLL::~BLL() { Clear(); }

void BLL::Clear() {
  if (head_ != nullptr) {
    Node* current = head_;
    while (current != nullptr) {
      if (current->next_bll_ != nullptr) {
        Destruct(current->next_bll_);
      }
      Node* tmp = current->next_node_;
      delete current;
      current = tmp;
    }
    head_ = nullptr;
  }
}

// test destructor
void BLL::Destruct(BLL*& list) {
  Node* curr = list->head_;
  while (curr != nullptr) {
    if (curr->next_bll_ != nullptr) {
      return Destruct(curr->next_bll_);
    }
    Node* tmp = curr->next_node_;
    delete curr;
    curr = tmp;
  }
  list->head_ = nullptr;
}

// copy constructor
BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  head_ = new Node(to_copy.head_->data_);
  auto* prev = head_;
  auto* current = to_copy.head_->next_node_;
  while (current != nullptr) {
    auto* node = new Node(current->data_);
    prev->next_node_ = node;
    prev = node;
    if (current->next_bll_ != nullptr) {
      BLL(*(current->next_bll_));
    }
    current = current->next_node_;
  }
}

Node* BLL::PushBack(char dat) {
  if (head_ == nullptr) {
    Node* to_add = new Node(dat);
    head_ = to_add;
    return to_add;
  }
  Node* current = head_;
  while (current->next_node_ != nullptr) {
    current = current->next_node_;
  }
  Node* to_add = new Node(dat);
  current->next_node_ = to_add;
  return to_add;
}

// size
size_t BLL::Size() const { return SizeHelper(head_); }

size_t BLL::SizeHelper(Node* node) const {
  if (node == nullptr) {
    return 0;
  }
  if (node->next_bll_ != nullptr) {
    return SizeHelper(node->next_bll_->head_);
  }
  return SizeHelper(node->next_node_) + 1;
}

// getter function
char BLL::GetAt(size_t idx) const {
  if (idx < 0 || idx >= Size()) {
    throw std::runtime_error("invalid index");
  }
  Node* current = head_;
  size_t tmp_idx = 0;
  while (tmp_idx != idx) {
    if (current->next_bll_ != nullptr) {
      return current->next_bll_->GetAt(idx - tmp_idx);
    }
    current = current->next_node_;
    tmp_idx++;
  }
  return current->data_;
}

// setter function
void BLL::SetAt(size_t idx, char dat) {
  if (idx < 0 || idx >= Size()) {
    throw std::runtime_error("invalid index");
  }
  Node* current = head_;
  size_t tmp_idx = 0;
  while (tmp_idx != idx) {
    if (current->next_bll_ != nullptr) {
      current = current->next_bll_->head_;
    }
    current = current->next_node_;
    tmp_idx++;
  }
  current->data_ = dat;
}

std::string BLL::ToString() const { return ToStringHelper(head_); }

std::string BLL::ToStringHelper(Node* node) const {
  if (node == nullptr) {
    return "";
  }
  if (node->next_bll_ != nullptr) {
    return node->data_ + ToStringHelper(node->next_bll_->head_) +
           ToStringHelper(node->next_node_);
  }
  return node->data_ + ToStringHelper(node->next_node_);
}

// detect cyclic, not complete
bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return true;
  }
  // Node* turtle = head_;
  // Node* hare = head_->next_node_;
  // while (turtle != nullptr && hare != nullptr && hare->next_node_ != nullptr)
  // {
  //   if (turtle == hare) {
  //     return false;
  //   }
  //   if (turtle->next_bll_ != nullptr) {
  //     turtle = turtle->next_bll_->head_;
  //   }
  //   // if (hare -> next_bll_ != nullptr) {
  //   //   hare = hare -> next_bll_;
  //   // }
  //   turtle = turtle->next_node_;
  //   hare = hare->next_node_->next_node_;
  // }

  // alternate approach, not complete
  const int kCon = 1000;
  Node* array[kCon];
  Node* test = head_;
  int i = 0;
  while (test != nullptr) {
    if (test->next_bll_ != nullptr) {
      return IsBLLAcyclic();
    }
    array[i] = test;
    test = test->next_node_;
    ++i;
  }
  return true;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0 || idx >= Size()) {
    throw std::runtime_error("invalid index");
  }

  Node* current = head_;
  size_t tmp_idx = 0;
  while (tmp_idx != idx) {
    // if (current->next_bll_ != nullptr) {
    //   current = current->next_bll_->head_;
    // }
    current = current->next_node_;
    tmp_idx++;
  }
  current->next_bll_ = list;
}

// irrelevant
Node* BLL::GetHead() const { return head_; }
