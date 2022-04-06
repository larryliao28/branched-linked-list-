#include "branched-linked-list.hpp"

#include <iostream>
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
  // head_ = new Node(to_copy.head_->data_);
  Node* prev = nullptr;
  Node* curr = nullptr;        // current
  auto* copy = to_copy.head_;  // current_copy
  bool first_check = true;
  while (copy != nullptr) {
    prev = curr;
    curr = new Node(copy->data_);
    if (first_check) {
      head_ = curr;
    }
    if (prev != nullptr) {
      prev->next_node_ = curr;
    }
    if (curr->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*(copy->next_bll_));
    }
    copy = curr->next_node_;
  }
}

// equality operator
BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  Clear();
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
    return *this;
  }
  Node* prev = nullptr;
  Node* curr = nullptr;
  auto* copy = rhs.head_;
  bool first_check = true;
  while (copy != nullptr) {
    prev = curr;
    curr = new Node(copy->data_);
    if (first_check) {
      head_ = curr;
    }
    if (prev != nullptr) {
      prev->next_node_ = curr;
    }
    if (curr->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*(copy->next_bll_));
    }
    copy = curr->next_node_;
  }
  return *this;
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
    return SizeHelper(node->next_bll_->head_) + SizeHelper(node->next_node_) +
           1;
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
  while (tmp_idx < idx) {
    if (current->next_bll_ != nullptr) {
      if ((current->next_bll_->Size() + tmp_idx) < idx) {
        tmp_idx += current->next_bll_->Size();
      } else {
        return current->next_bll_->GetAt(idx - tmp_idx - 1);
      }
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
  while (tmp_idx < idx) {
    if (current->next_bll_ != nullptr) {
      if ((current->next_bll_->Size() + tmp_idx) < idx) {
        tmp_idx += current->next_bll_->Size();
      } else {
        return current->next_bll_->SetAt(idx - tmp_idx - 1, dat);
      }
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
bool BLL::IsBLLAcyclic() const { return IsBLLAcyclicHelp(head_); }
bool BLL::IsBLLAcyclicHelp(Node* node) const {
  if (node == nullptr || node->next_node_ == nullptr) {
    std::cout << "hit the end" << std::endl;
    return true;
  }
  Node* turtle = node;
  Node* hare = node->next_node_;

  std::cout << "before while loop" << std::endl;
  std::cout << "turtle: " << turtle->data_ << std::endl;
  std::cout << "hare: " << hare->data_ << std::endl;

  while ((turtle != nullptr || turtle->next_bll_ != nullptr) &&
         (hare != nullptr || hare->next_bll_ != nullptr) &&
         (hare->next_node_ != nullptr || hare->next_bll_ != nullptr)) {
    std::cout << "in while loop" << std::endl;
    std::cout << "turtle: " << turtle->data_ << std::endl;
    std::cout << "hare: " << hare->data_ << std::endl;

    if (turtle == hare) {
      return false;
    }
    if (hare->next_bll_ != nullptr) {
      return IsBLLAcyclicHelp(hare->next_bll_->head_);
    }
    if (turtle->next_bll_ != nullptr) {
      return IsBLLAcyclicHelp(turtle->next_bll_->head_);
    }

    turtle = turtle->next_node_;
    if (hare != nullptr && hare->next_node_ != nullptr &&
        hare->next_node_->next_node_ != nullptr) {
      hare = hare->next_node_->next_node_;
    } else {
      std::cout << "doesn't find the cycle 1" << std::endl;
      return true;
    }
  }
  std::cout << "doesn't find the cycle 2" << std::endl;
  return true;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0 || idx >= Size()) {
    throw std::runtime_error("invalid index");
  }

  Node* current = head_;
  size_t tmp_idx = 0;
  while (tmp_idx != idx) {
    if (current->next_bll_ != nullptr) {
      if ((current->next_bll_->Size() + tmp_idx) < idx) {
        tmp_idx += current->next_bll_->Size();
      } else {
        return current->next_bll_->Join(idx - tmp_idx - 1, list);
      }
    }
    current = current->next_node_;
    tmp_idx++;
  }
  if (current->next_bll_ != nullptr) {
    throw std::runtime_error("branch already exist");
  }
  // also need to test for cyclic
  current->next_bll_ = list;
  if (!IsBLLAcyclic()) {
    throw std::runtime_error("cycle behavior");
  }
}
