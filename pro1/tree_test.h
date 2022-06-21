
#ifndef PRO1_TREE_TEST_H
#define PRO1_TREE_TEST_H

#include<vector>
#include <queue>
#include <limits>


using namespace std;

// 基础数据结构
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 二叉树的最大深度一
class S104 {
public:
    int depth = 0;  // 外部变量...
    int res = 0;

    int maxDepth(TreeNode *root) {
        traverse(root);
        return res;
    }

    void traverse(TreeNode *root) {
        if (root == nullptr) {
            res = max(depth, res);  // 叶子节点处，更新最大深度...
            return;
        }
        depth++;    // 前序遍历位置...
        traverse(root->left);
        traverse(root->right);
        depth--;
    }
};

// 二叉树的最大深度二
class S543 {
public:
    int maxDiameter = 0;

    int diameterOfBinaryTree(TreeNode *root) {
        maxDepth(root);
        return maxDiameter;
    }

    // 计算二叉树的最大深度
    int maxDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int leftMax = maxDepth(root->left);
        int rightMax = maxDepth(root->right);
        maxDiameter = max(leftMax + rightMax, maxDiameter);   // 后序位置,子树最大深度和的最大值...

        return 1 + max(leftMax, rightMax);  // 叶子节点，深度算作1...
    }
};

// 二叉树层序遍历
class S102 {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        if (root == nullptr) { return res; }

        queue<TreeNode *> q;    // BFS队列
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            vector<int> tmpVec;
            for (int i = 0; i < sz; i++) {
                TreeNode *tmp = q.front();  // 队列中取出一个节点
                q.pop();
                tmpVec.push_back(tmp->val);

                if (tmp->left) { q.push(tmp->left); }  // 将下一层节点放入队列...
                if (tmp->right) { q.push(tmp->right); }
            }
            res.push_back(tmpVec);  // 记录当前层的节点值...
        }
        return res;
    }
};

// 二叉树层序遍历二
class S515 {
public:
    vector<int> largestValues(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) { return res; }

        queue<TreeNode *> q;  // BFS队列...
        q.push(root);

        while (!q.empty()) {
            int maxVal = numeric_limits<int>::min();   // 当前层的初始最小值...
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                TreeNode *node = q.front();   // 单个节点...
                q.pop();
                maxVal = max(node->val, maxVal);

                if (node->left) { q.push(node->left); } // 下一层的节点...
                if (node->right) { q.push(node->right); }
            }
            res.push_back(maxVal);  // 记录当前层的最小值...
        }
        return res;
    }
};

// 翻转二叉树
class S226 {
public:
    TreeNode *invertTree(TreeNode *root) {
        traverse(root);
        return root;
    }

    void traverse(TreeNode *root) {
        if (root == nullptr) { return; }

        traverse(root->left);
        traverse(root->right);

        TreeNode *tmp = root->left; // 后序遍历位置，单个节点需要做的事...
        root->left = root->right;
        root->right = tmp;
    }
};
class S226_1 {
public:
    TreeNode *invertTree(TreeNode *root) {
        if (root == nullptr) { return nullptr; }

        TreeNode *left = invertTree(root->left);  // 分解问题，翻转后返回的根节点...
        TreeNode *right = invertTree(root->right);

        root->left = right; // 交换左右子树... , 还是后序遍历?
        root->right = left;

        return root;
    }
};

// 数组中的最大值构造二叉树
class S654 {
public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {

        return build(nums, 0, nums.size() - 1);
    }

    TreeNode *build(vector<int> &nums, int lo, int hi) {
        if (lo > hi) { return nullptr; }

        int index = lo;
        for (int i = lo; i <= hi; i++) {
            if (nums[i] > nums[index]) { index = i; }  // 寻找数组中最大值的索引...
        }

        TreeNode *root = new TreeNode(nums[index]);  // 构造根节点，然后构造子树...
        root->left = build(nums, lo, index - 1);
        root->right = build(nums, index + 1, hi);

        return root;
    }
};

// 中序数组+前序数组,还原二叉树
class S105 {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return build(preorder, 0, preorder.size() - 1,
                     inorder, 0, inorder.size() - 1);
    }

    TreeNode *build(vector<int> &preorder, int preStart, int preEnd,
                    vector<int> &inorder, int inStart, int inEnd) {
        if (preStart > preEnd) {
            return nullptr;             // 终止条件？ 根节点所在的位置...
        }

        int rootVal = preorder[preStart];       // 前序数组第一个元素，即根节点...
        TreeNode *root = new TreeNode(rootVal);

        // 左子树中序数组
        int inOrderRootIdx = getRootIndex(rootVal, inorder, inStart, inEnd);  // 中序数组根节点索引...
        int leftInOrderStartIdx = inStart;
        int leftInOrderEndIdx = inOrderRootIdx - 1;
        // 左子树前序数组
        int leftPreOrderStartIdx = preStart + 1;
        int leftPreOrderEndIdx = preStart + (leftInOrderEndIdx - leftInOrderStartIdx + 1);  // 中序数组中计算元素个数...

        root->left = build(preorder, leftPreOrderStartIdx, leftPreOrderEndIdx,
                           inorder, leftInOrderStartIdx, leftInOrderEndIdx);

        // 右子树中序数组
        int rightInOrderStartIdx = inOrderRootIdx + 1;
        int rightInOrderEndIdx = inEnd;
        // 右子树前序数组
        int rightPreOrderStartIdx = leftPreOrderEndIdx + 1;
        int rightPreOrderEndIdx = preEnd;
        root->right = build(preorder, rightPreOrderStartIdx, rightPreOrderEndIdx,
                            inorder, rightInOrderStartIdx, rightInOrderEndIdx);
        return root;
    }

    int getRootIndex(int rootVal, vector<int> &inorder, int inStart, int inEnd) {
        int res = inStart;
        for (int i = inStart; i <= inEnd; i++) {
            if (inorder[i] == rootVal) {
                res = i;
            }
        }
        return res;
    }
};

// 中序数组+后序数组，还原二叉树
class S106 {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        return build(inorder, 0, inorder.size() - 1,
                     postorder, 0, postorder.size() - 1);
    }

    TreeNode *build(vector<int> &inorder, int inStart, int inEnd,
                    vector<int> &postorder, int postStart, int postEnd) {

        if (inStart > inEnd) {
            return nullptr;
        }

        int rootVal = postorder[postEnd];
        TreeNode *root = new TreeNode(rootVal);

        // 左子树中序数组
        int inOrderRootIdx = getRootIndex(rootVal, inorder, inStart, inEnd);
        int leftInOrderStartIdx = inStart;
        int leftInOrderEndIdx = inOrderRootIdx - 1;   // 可计算左子树元素个数...

        // 左子树后序数组
        int leftPostOrderStartIdx = postStart;
        int leftPostOrderEndIdx = leftPostOrderStartIdx - 1 + (leftInOrderEndIdx - leftInOrderStartIdx + 1);
        root->left = build(inorder, leftInOrderStartIdx, leftInOrderEndIdx,
                           postorder, leftPostOrderStartIdx, leftPostOrderEndIdx);

        // 右子树中序数组
        int rightInOrderStartIdx = inOrderRootIdx + 1;
        int rightInOrderEndIdx = inEnd;

        // 右子树后序数组
        int rightPostOrderStartIdx = leftPostOrderEndIdx + 1;
        int rightPostOrderEndIdx = postEnd - 1;
        root->right = build(inorder, rightInOrderStartIdx, rightInOrderEndIdx,
                            postorder, rightPostOrderStartIdx, rightPostOrderEndIdx);
        return root;
    }

    // 计算中序数组中根节点的索引...
    int getRootIndex(int rootVal, vector<int> &inorder, int inStart, int inEnd) {
        int res = inStart;
        for (int i = inStart; i <= inEnd; i++) {
            if (inorder[i] == rootVal) {
                res = i;
            }
        }
        return res;
    }
};

// 前序数组+后序数组，构造一个二叉树
class S889 {
public:
    TreeNode *constructFromPrePost(vector<int> &preorder, vector<int> &postorder) {
        return build(preorder, 0, preorder.size() - 1,
                     postorder, 0, postorder.size() - 1);
    }

    TreeNode *build(vector<int> &preorder, int preStart, int preEnd,
                    vector<int> &postorder, int postStart, int postEnd) {

        if (preStart > preEnd) {
            return nullptr;   // 终止条件？
        }

        if (preStart == preEnd) {
            return new TreeNode(preorder[preStart]);    // 只有1个元素的情况，构造该节点...
        }

        int rootVal = preorder[preStart];
        TreeNode *root = new TreeNode(rootVal);

        // 计算左子树元素个数
        int leftRootVal = preorder[preStart + 1];     // 前序数组第2个元素，设为左子树根节点...
        int leftPostOrderRootIdx = getLeftRootIdx(leftRootVal, postorder, postStart, postEnd);
        int leftSize = leftPostOrderRootIdx - postStart + 1;    // 左子树元素个数...

        // 左子树前序数组
        int leftPreOrderStart = preStart + 1;
        int leftPreOrderEnd = preStart + leftSize;
        // 左子树后序数组
        int leftPostOrderStart = postStart;
        int leftPostOrderEnd = leftPostOrderRootIdx;    // 左子树根节点为最后一个元素...
        root->left = build(preorder, leftPreOrderStart, leftPreOrderEnd,
                           postorder, leftPostOrderStart, leftPostOrderEnd);

        // 右子树前序数组
        int rightPreOrderStart = leftPreOrderEnd + 1;
        int rightPreOrderEnd = preEnd;
        // 右子树后序数组
        int rightPostOrderStart = leftPostOrderRootIdx + 1;
        int rightPostOrderEnd = postEnd - 1;
        root->right = build(preorder, rightPreOrderStart, rightPreOrderEnd,
                            postorder, rightPostOrderStart, rightPostOrderEnd);
        return root;
    }

    int getLeftRootIdx(int leftRootVal, vector<int> &postorder, int postStart, int postEnd) {
        int res;
        for (int i = postStart; i <= postEnd; i++) {
            if (postorder[i] == leftRootVal) {
                res = i;
            }
        }
        return res;
    }
};




// 有序数组构建高度平衡的BST
class S108 {
public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        return build(nums, 0, nums.size() - 1);
    }

    TreeNode *build(vector<int> &nums, int left, int right) {
        // 二叉树的构建：先构造根节点，然后构建左右子树
        // base case
        if (left > right) {
            return nullptr;
        }
        // BST即中序遍历，中间点为根节点
        int mid = left + (right - left) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        // 构建左子树
        root->left = build(nums, left, mid - 1);
        // 构建右子树
        root->right = build(nums, mid + 1, right);
        return root;
    }
};


// 有序链表构建高度平衡的BST
class S109 {
public:

    // 找到[left, right)的中间节点
    ListNode *findMiddle(ListNode *left, ListNode *right) {
        ListNode *slow = left, *fast = left;
        while (fast != right && fast->next != right) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    TreeNode *build(ListNode *left, ListNode *right) {
        // 由于是左闭右开
        if (left == right) {
            return nullptr;
        }
        ListNode *mid = findMiddle(left, right);
        TreeNode *root = new TreeNode(mid->val);
        root->left = build(left, mid);
        root->right = build(mid->next, right);
        return root;
    }

    TreeNode *sortedListToBST(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        return build(head, nullptr);
    }
};


#endif //PRO1_TREE_TEST_H
