#include <vector>
#include <exception>
#include <initializer_list>
#include <cassert>
#include <iterator>
#include <stdexcept>

using std::runtime_error;

template<typename ValueType>
class Set;


struct ListNode {
    ListNode *prev_;
    ListNode *next_;

    ListNode(ListNode *prev_, ListNode *next_) : prev_(prev_), next_(next_) {}

    virtual ~ListNode() {
    }
};

template<typename ValueType>
struct TreeNode : ListNode {

    using Node = TreeNode<ValueType>;

    TreeNode *left_;
    TreeNode *right_;
    TreeNode *p_;
    ValueType value_;

    TreeNode(TreeNode *left, TreeNode *right, TreeNode *pp,
             const ValueType &val, ListNode *prev = nullptr, ListNode *next = nullptr)
            : ListNode(prev, next), left_(left), right_(right), p_(pp), value_(val) {}

    inline void UpdateSons(TreeNode<ValueType> *left, TreeNode<ValueType> *right) {
        left_ = left;
        right_ = right;
        if (left_)
            left->p_ = this;
        if (right_)
            right->p_ = this;
    }

    inline void UpdateFatherWithFather(Node *node) {
        p_ = node->p_;
        if (node->p_ == nullptr) {
            return;
        }
        if (node->p_->left_ == node) {
            p_->left_ = this;
        } else {
            p_->right_ = this;
        }
    }

    inline void AddLeftSon(const ValueType &val, bool link = false) {
        //assert(left_ == nullptr);
        left_ = new TreeNode{0, 0, this, val};
        if (link) {
            left_->next_ = this;
            left_->prev_ = this->prev_;

            left_->prev_->next_ = left_;
            left_->next_->prev_ = left_;
        }
    }

    inline void AddRightSon(const ValueType &val, bool link = false) {
        //assert(right_ == nullptr);
        right_ = new TreeNode{0, 0, this, val};

        if (link) {
            right_->next_ = this->next_;
            right_->prev_ = this;

            right_->next_->prev_ = right_;
            right_->prev_->next_ = right_;
        }
    }

    inline bool IsPLeft() {
//        if (p_ == nullptr) {
//            throw runtime_error("No father");
//        }
        return (p_->left_ == this);
    }

    bool IsPRight() {
//        if (p_ == nullptr) {
//            throw runtime_error("No father");
//        }
        return (p_->right_ == this);
    }

    ~TreeNode() {

    }
};

template<typename ValueType>
class SplayTree {
public:
    friend class Set<ValueType>;

    using Node = TreeNode<ValueType>;
    using Tree = SplayTree<ValueType>;

    SplayTree() : root_(nullptr), fict_(new ListNode(0, 0)), size_(0) {
        fict_->prev_ = fict_;
        fict_->next_ = fict_;
    }

    SplayTree(Node *root, ListNode *fict, int size) : root_(root), fict_(fict), size_(size) {
    }


private:
    SplayTree(Node *root) : root_(root), fict_(0) {
        root->p_ = nullptr;
    }

public:

    Node *Find(const ValueType &val, bool insert = false) {
        auto cur_node = root_;

        int depth = 0;
        while (cur_node) {
            bool less = val < cur_node->value_;
            bool greater = cur_node->value_ < val;
            depth += 1;
            if (!(less) && !(greater)) {
                if (depth > 120) {
                    Splay(cur_node);
                }

                return cur_node;
            }

            if (less) {
                if (insert && cur_node->left_ == nullptr) {
                    cur_node->AddLeftSon(val, size_ > 0);
                    size_++;
                }
                cur_node = cur_node->left_;
            } else {
                if (insert && cur_node->right_ == nullptr) {
                    cur_node->AddRightSon(val, size_ > 0);
                    size_++;
                }
                cur_node = cur_node->right_;
            }
        }

        if (insert) {
            root_ = new Node(0, 0, 0, val);
            size_ = 1;
        }

        return nullptr;
    }

    void Insert(const ValueType &val) {
        Find(val, true);
        if (size_ == 1) {
            fict_->next_ = root_;
            fict_->prev_ = root_;
            root_->prev_ = fict_;
            root_->next_ = fict_;
        }
    }

    void Delete(const ValueType &val) {
        if (auto cur = Find(val)) {
            Splay(cur);
            cur->prev_->next_ = cur->next_;
            cur->next_->prev_ = cur->prev_;
            auto root_left = cur->left_;
            auto root_right = cur->right_;
            delete (cur);

            size_--;
            if (size_ == 0) {
                root_ = nullptr;
                return;
            }
            if (!root_left) {
                root_ = root_right;
                root_->p_ = 0;
                return;
            }
            if (!root_right) {
                root_ = root_left;
                root_->p_ = 0;
                return;
            }
            root_left->p_ = 0;

            Tree left_tree(root_left);
            auto new_root = left_tree.Max();
            //assert(new_root->right_ == nullptr);
            new_root->right_ = root_right;
            root_right->p_ = new_root;
            root_ = new_root;
            //assert(new_root->p_ == nullptr);
            left_tree.root_ = 0;
        }
    }

    int Size() const {
        return size_;
    }

    bool _Debug_Validate(Node *node = nullptr) {
        if (size_ == 0 && root_) {
            assert(false);
        }
        if (size_ == 0 && !root_) {
            return true;
        }
        if (!node) {
            node = root_;
        }
        if (node->right_) {
            assert(node->right_->value_ > node->value_);
            assert(node->right_->p_ == node);
            _Debug_Validate(node->right_);
        }

        if (node->left_) {
            assert(node->left_->value_ < node->value_);
            assert(node->left_->p_ == node);
            _Debug_Validate(node->left_);
        }
        return false;
    }

    void _Debug_Linked() {
        auto find_ = root_;
        if (!root_) {
            return;
        }

        while (find_) {
            auto pp = dynamic_cast<Node *>(find_);
            if (pp->left_) {
                find_ = pp->left_;
            } else {
                break;
            }
        }

        ListNode *node = find_;

        int cnt = 1;

        assert(node->prev_ == fict_);
        assert(fict_->next_ == node);

        while (node->next_ != fict_) {
            assert(node->next_->prev_ == node);
            assert(cnt <= size_);
            assert(dynamic_cast<Node *>(node->next_)->value_ > dynamic_cast<Node *>(node)->value_);
            cnt++;
            node = node->next_;
        }
        assert(node->next_ == fict_);
        assert(cnt == size_);
    }

    void DfsDelete(Node *node) {
        if (!node) {
            return;
        }

        DfsDelete(node->left_);
        DfsDelete(node->right_);
        delete (node);
    }


    ~SplayTree() {
        if (root_) {
            DfsDelete(root_);
        }
        if (fict_) {
            delete (fict_);
        }
    }

    Tree GetDeepCopy() const {



        ListNode *new_fict = new ListNode(0, 0);
        new_fict->next_ = new_fict;
        new_fict->prev_ = new_fict;

        auto new_root = CopyDfs(root_);
        Node *last = TieSet(new_root, new_fict);
        if (last) {
            last->next_ = new_fict;
            new_fict->prev_ = last;
        }

        return {new_root, new_fict, size_};

//        Tree tree;
//        auto cur = fict_->next_;
//        while (cur != fict_) {
//            tree.Insert(dynamic_cast<Node*>(cur)->value_);
//            cur = cur->next_;
//        }
//        return tree;
    }

    ListNode *LowerBound(const ValueType &val) {
        auto cur = root_;
        Node *lower_bound = nullptr;
        int depth = 0;
        while (cur) {
            bool less = val < cur->value_;
            bool greater = cur->value_ < val;
            depth += 1;
            if (!(less) && !(greater)) {
                if (depth >= 80) {
                    Splay(cur);
                }
                return cur;
            }
            if (greater) {
                if (!cur->right_) {
                    if (depth >= 80) {
                        Splay(cur);
                    }
                    break;
                } else {
                    cur = cur->right_;
                }
            } else {
                if (lower_bound == nullptr || (cur->value_) < (lower_bound->value_)) {
                    lower_bound = cur;
                }
                if (!cur->left_) {
                    if (depth >= 80) {
                        Splay(cur);
                    }
                    break;
                } else {
                    cur = cur->left_;
                }
            }
        }
        return (lower_bound == nullptr ? fict_ : lower_bound);
    }

private:

    Node *Max() {
        auto cur_node = root_;

        while (cur_node) {
            if (cur_node->right_) {
                cur_node = cur_node->right_;
                continue;
            }
            Splay(cur_node);
            return root_;
        }
        return root_;
    }

    void Splay(TreeNode<ValueType> *node) {
        if (!node) {
            return;
        }
        auto cur_node = node;

        while (cur_node->p_) {
            if (cur_node->p_->p_ == nullptr) {
                if (cur_node->IsPLeft()) {
                    UpLeft(cur_node);

                } else {
                    UpRight(cur_node);
                }
            } else {
                if (cur_node->IsPLeft()) {
                    if (cur_node->p_->IsPLeft()) {
                        UpLeftLeft(cur_node);
                    } else {
                        UpLeftRight(cur_node);
                    }
                } else {
                    if (cur_node->p_->IsPLeft()) {
                        UpRightLeft(cur_node);

                    } else {
                        UpRightRight(cur_node);
                    }
                }
            }
        }
        root_ = cur_node;
    }


    inline void UpLeft(TreeNode<ValueType> *node) {

        auto v1 = node->p_;
        auto v2 = node;
        auto s2 = v2->right_;
        v1->p_ = v2;
        v1->left_ = s2;

        v2->p_ = 0;
        v2->right_ = v1;
        if (s2) {
            s2->p_ = v1;
        }
    }

    inline void UpRight(TreeNode<ValueType> *node) {

        auto v1 = node->p_;
        auto v2 = node;
        auto s2 = v2->left_;
        v1->p_ = v2;
        v1->right_ = s2;

        if (s2) {
            s2->p_ = v1;
        }
        v2->p_ = 0;
        v2->left_ = v1;
    }

    inline void UpLeftLeft(TreeNode<ValueType> *node) {
        auto v3 = node;
        auto v2 = node->p_;
        auto v1 = node->p_->p_;
        v3->UpdateFatherWithFather(v1);

        auto s2 = v3->right_;
        v3->right_ = v2;
        auto s3 = v2->right_;

        if (s2) {
            s2->p_ = v2;
        }
        if (s3) {
            s3->p_ = v1;
        }
        v1->p_ = v2;
        v1->left_ = s3;

        v2->right_ = v1;
        v2->left_ = s2;
        v2->p_ = v3;
    }

    inline void UpRightRight(TreeNode<ValueType> *node) {
        auto v3 = node;
        auto v2 = node->p_;
        auto v1 = v2->p_;
        v3->UpdateFatherWithFather(v1);

        auto s2 = v2->left_;
        auto s3 = v3->left_;

        if (s3) {
            s3->p_ = v2;
        }
        if (s2) {
            s2->p_ = v1;
        }
        v1->p_ = v2;
        v1->right_ = s2;

        v2->p_ = v3;
        v2->left_ = v1;
        v2->right_ = s3;

        v3->left_ = v2;
    }

    inline void UpLeftRight(TreeNode<ValueType> *node) {
        auto v3 = node;
        auto v2 = node->p_;
        auto v1 = v2->p_;
        v3->UpdateFatherWithFather(v1);


        auto s2 = v3->left_;
        auto s3 = v3->right_;

        v1->p_ = v3;
        v1->right_ = s2;

        if (s3) {
            s3->p_ = v2;
        }

        if (s2) {
            s2->p_ = v1;
        }
        v3->left_ = v1;
        v3->right_ = v2;
        v2->left_ = s3;
        v2->p_ = v3;

    }

    inline void UpRightLeft(TreeNode<ValueType> *node) {
        auto v3 = node;
        auto v2 = node->p_;
        auto v1 = v2->p_;
        v3->UpdateFatherWithFather(v1);

        auto s2 = v3->left_;
        auto s3 = v3->right_;

        v2->p_ = v3;
        v2->right_ = s2;

        if (s2)
            s2->p_ = v2;
        if (s3)
            s3->p_ = v1;
        v3->left_ = v2;
        v3->right_ = v1;

        v1->p_ = v3;
        v1->left_ = s3;
    }

    Node *CopyDfs(Node *node) const {

        if (!node) {
            return nullptr;
        }


        auto left = CopyDfs(node->left_);
        auto right = CopyDfs(node->right_);
        Node *cur_ver = new Node(left, right, 0, node->value_);

        if (left) {
            left->p_ = cur_ver;
        }
        if (right) {
            right->p_ = cur_ver;
        }
        return cur_ver;
    }

    Node *TieSet(Node *node, ListNode *prev_visited) const {
        if (!node) {
            return nullptr;
        }
        if (node->left_) {
            prev_visited = TieSet(node->left_, prev_visited);
        }
        prev_visited->next_ = node;
        node->prev_ = prev_visited;
        if (node->right_) {
            return TieSet(node->right_, node);
        }
        return node;
    }

    Node *root_;
    ListNode *fict_;
    int size_;
};

template<typename ValueType>
class Set {
public:
    Set() {};

    using Node = TreeNode<ValueType>;

    class iterator : public std::iterator<std::bidirectional_iterator_tag, ValueType> {
    public:
        explicit iterator(ListNode *list_node = nullptr) : list_node_(list_node) {}

        ValueType &operator*() {
            return static_cast<Node *>(list_node_)->value_;
        }

        ValueType *operator->() {
            return &static_cast<Node *>(list_node_)->value_;
        }

        iterator &operator++() {
            list_node_ = list_node_->next_;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(list_node_);
            list_node_ = list_node_->next_;
            return tmp;
        }

        iterator &operator--() {
            list_node_ = list_node_->prev_;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp(list_node_);
            list_node_ = list_node_->prev_;
            return tmp;
        }

        bool operator==(const iterator &it) const {
            return it.list_node_ == list_node_;
        }

        bool operator!=(const iterator &it) const {
            return it.list_node_ != list_node_;
        }

    private:
        ListNode *list_node_;
    };


    template<typename Iterator>
    Set(Iterator begin, Iterator end) {
        while (begin != end) {
            splay_tree_.Insert(*begin);
            ++begin;
        }
    }

    Set(std::initializer_list<ValueType> list) : Set(list.begin(), list.end()) {
    }

    Set(const Set &set) : splay_tree_(set.splay_tree_.GetDeepCopy()) {
    }

    Set(Set &&set) : splay_tree_(set.splay_tree_) {
        set.splay_tree_.root_ = 0;
        set.splay_tree_.fict_ = 0;
        set.splay_tree_.size_ = -1;
    }

    Set &operator=(const Set &set) {
        Set tmp(set);
        Swap(tmp);
        return *this;
    }

    Set &operator=(Set &&set) {
        Set splay_tree_(std::move(set.splay_tree_));
        Swap(splay_tree_);
        return *this;
    }

    int size() const {
        return splay_tree_.size_;
    }

    bool empty() const {
        return splay_tree_.size_ == 0;
    }

    void insert(const ValueType &value) {
        splay_tree_.Insert(value);
    }

    void erase(const ValueType &value) {
        splay_tree_.Delete(value);
    }

    iterator end() const {
        return iterator(splay_tree_.fict_);
    }

    iterator begin() const {
        return iterator(splay_tree_.fict_->next_);
    }

    iterator find(const ValueType &value) const {
        auto res = const_cast<Set<ValueType> *>(this)->splay_tree_.Find(value);
        if (res == nullptr) {
            return end();
        } else {
            return iterator(res);
        }
    }

    iterator lower_bound(const ValueType &val) const {
        return iterator(const_cast<Set<ValueType> *>(this)->splay_tree_.LowerBound(val));
    }

private:

    inline void Swap(Set &set) {
        std::swap(splay_tree_.size_, set.splay_tree_.size_);
        std::swap(splay_tree_.root_, set.splay_tree_.root_);
        std::swap(splay_tree_.fict_, set.splay_tree_.fict_);
    }

public:
    SplayTree<ValueType> splay_tree_;
};
