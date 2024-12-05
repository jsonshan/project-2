#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */

inline void addInRange(size_t min, size_t max, std::vector<File*> result, Node* curr)
{
    /*
    add curr if valid
    recursively call left and right child
    */
   if (curr == nullptr)
   {
    return;
   }

    // recursively call on left child
    addInRange(min, max, result, curr->left_);

    if (curr->size_ >= min)
    {
        if (curr->size_ <= max)
        {
            for (auto it = curr->files_.begin(); it != curr->files_.end(); ++it)
            {
                result.push_back(*it);
            }
        }
    }

    // recursively call on right child
    addInRange(min, max, result, curr->right_);

}

std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> result;

    /*
    Check every node to see if its size is between min and max
    Insert to result vector
    return result vector
    */
    
    addInRange(min, max, result, root_);

    return result;
}

void FileTrie::addFile(File* f)
{
    std::string name = f->getName();
    // Check if name is valid
    // Characters allowed are a-z, 0-9, and . (period).
    int period = 0;

    for (int i = 0; i < name.length(); ++i)
    {
        if (!isalnum(name[i]))
        {
            if (name[i] == '.')
            {
                ++period;
            }
            if (period > 1)
            {
                return;
            }
            if (name[i] != '.')
            {
                return;
            }
        }
    }
    /* 
    - Insert file into current matching (starting at root)
    - Traverse letter of a name
    - check if next letter matches curr letter
    - if it does exist, go to that and add the file to the matching (unordered_map)
    - if it doesn't exist, create a new node and add to the matching (should be only itself)
    */ 
    
    // initalize curr
    FileTrieNode* curr = head;
    // insert file to matching of root
    curr->matching.insert(f);
    // traverse through name

   for (int i = 0; i < name.length(); ++i)
   {
    // finds if the letter does not exists
    if (curr->next.find(name[i]) == curr->next.end())
    {
        // reaches end, but finds no next so creates new file
        curr->next[name[i]] = new FileTrieNode(name[i]);
    }
    // points to the next node
    curr = curr->next[name[i]];
    // inserts to set
    curr->matching.insert(f);
   }

}

// Search
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const
{
    /*
    String prefix and we for loop prefix
    check first letter of prefix if ->next exists
    if it doesn't, return matching
    if it does, move curr = curr->next[prefix[i]]
    Should preemptively return nothing if we find anything that doesn't match

    When for loop ends, it means we have a valid prefix, return curr->matching
    */
   // initalize curr
   FileTrieNode* curr = head;

    // for loop prefix
   for (int i = 0; i < prefix.length(); ++i)
   {
    // if doesn't find any valid next letter to go to 
    if (curr->next.find(prefix[i]) == curr->next.end())
    {
        // return empty set
        return {};
    }
    // move curr ptr to next and repeat
    curr = curr->next[prefix[i]];
   }
   return curr->matching;
}

 // Destructor


inline void deleteAllNodes(FileTrieNode* current)
{
    if (current == nullptr)
    {
        return;
    }
    // iterates through each node and recursively deletes it from the trie
    for (auto curr: current->next)
    {
        deleteAllNodes(curr.second);
    }

    delete current;
}

FileTrie::~FileTrie()
{
    deleteAllNodes(head);
}

