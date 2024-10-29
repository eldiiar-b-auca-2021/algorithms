class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> result;
        if (root == nullptr)
            return result;
        queue<Node*> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            vector<int> level;
            for (int i = 0; i < size; i++)
            {
                root = q.front();
                q.pop();
                level.push_back(root->val);
                for (auto it : root->children)
                {
                    q.push(it);
                }
            }
            result.push_back(level);
        }
        return result;
    }
};