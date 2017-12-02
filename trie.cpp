#include <iostream>
#include <algorithm>
#include "trie.hpp"

void remove_trie(trie_node* & _node);

bool trie::erase(const std::string& str) {
    trie_node* node = this->m_root;
    unsigned long long i = 0;
    unsigned long long n = str.length();
    const char * c = str.c_str();

    while(i < n) {
        if (node->children[c[i]] != nullptr) {
            node = node->children[c[i]];
        } else {
            return false;
        }
        i++;
    }
    if(node->is_terminal){
        node->is_terminal = false;
        this->m_size--;
        return true;
    }else{
        return false;
    }
}

void add_elem(trie_node* & node,const char * & c,const unsigned long long & i){
    auto * temp = new trie_node;
    temp->parent = node;
    temp->payload = c[i];
    node->children[c[i]] = temp;
    node = node->children[c[i]];
}

bool trie::insert(const std::string& str) {
    trie_node* node = this->m_root;
    unsigned long long i = 0;
    unsigned long long n = str.length();
    const char * c = str.c_str();

    if(n == 0){
        n = 1;
    }

    while (i < n){
        if(node->children[c[i]] != nullptr){
            node = node->children[c[i]];
        }else{
            break;
        }
        i++;
    }
    while (i < n){
        add_elem(node,c,i);
        ++i;
    }

    if(node->is_terminal){
        return false;
    }
    node->is_terminal = true;
    this->m_size++;
    return true;
}

bool trie::contains(const std::string& str) const {
    trie_node* node = this->m_root;
    unsigned long long i = 0;
    unsigned long long n = str.length();
    const char * c = str.c_str();
    if(n == 0){
        n = 1;
    }
    while(i<n){
        if(node->children[c[i]] == nullptr){
            return false;
        }
        node = node->children[c[i]];
        ++i;
    }
    return node->is_terminal;
}

trie::trie() {
    this->m_root = new trie_node;
    this->m_size = 0;
}

trie::trie(const std::vector<std::string>& strings) {
    this->m_root = new trie_node;
    this->m_size = 0;
    for(auto const& item: strings) {
        this->insert(item);
    }
}

void deep_copy(trie_node*& actualNode, const trie_node* copiedOne){
    for (int i = 0; i < num_chars; ++i) {
        if(copiedOne->children[i] != nullptr){
            //Create new node and put it in actual node
            auto x = new trie_node;
            x->payload = copiedOne->children[i]->payload;
            x->is_terminal = copiedOne->children[i]->is_terminal;
            x->parent = actualNode;
            actualNode->children[i] = x;

            //Recursive repeat it
            deep_copy(actualNode->children[i],copiedOne->children[i]);
        }
    }
}

trie::trie(const trie& rhs) {
    auto x = new trie_node;
    x->payload = rhs.m_root->payload;
    x->is_terminal = rhs.m_root->is_terminal;
    deep_copy(x,rhs.m_root);
    this->m_root = x;
    this->m_size = rhs.m_size;
}

trie& trie::operator=(const trie& rhs) {

    //Create copy
    auto x = new trie_node;
    x->payload = rhs.m_root->payload;
    x->is_terminal = rhs.m_root->is_terminal;
    deep_copy(x,rhs.m_root);

    //Deallocate old data
    remove_trie(this->m_root);
    delete m_root;

    //Put new data
    this->m_root = x;
    this->m_size = rhs.m_size;

    return *this;
}

trie::trie(trie&& rhs) {
//    this->m_root = rhs.m_root;
//    this->m_size = rhs.m_size;
}

trie& trie::operator=(trie&& rhs) {
//    this->m_root = rhs.m_root;
//    this->m_size = rhs.m_size;
    return *this;
}


void remove_trie(trie_node* & _node){
    for (int i = 0; i < num_chars; i++) {
        if(_node->children[i] != 0) {
            trie_node* node = _node->children[i];
            remove_trie(node);
            delete node;
        }
    }
} //done

trie::~trie() {
    trie_node * root = this->m_root;
    remove_trie(root);
    delete root;
    this->m_root = nullptr;
    this->m_size = 0;
} //done

size_t trie::size() const {
    return this->m_size;
} //done

bool trie::empty() const {
    return this->size() == 0;
} //done

void search(std::vector<std::string>& vector, const trie_node* node, std::string words){
    for (int i = 0; i < num_chars; i++) {
        if(node->children[i] != nullptr) {
            trie_node* n = node->children[i];
            words += n->payload;
            if(n->is_terminal){
                vector.push_back(words);
            }

            search(vector,n,words);
            words.pop_back();
        }
    }
} //done

std::vector<std::string> trie::search_by_prefix(const std::string& str) const {
//    if(!this->contains(str)){
//        return {};
//    }
    trie_node * node = this->m_root;

    //GET actual node
    unsigned long long i = 0;
    unsigned long long n = str.length();
    const char * c = str.c_str();
    while(i<n){
        node = node->children[c[i]];
        ++i;
    }

    std::vector<std::string> v;
    //Check if actual prefix is word
    if(node->is_terminal){
        v.push_back(str);
    }

    //Recursive search all nodes
    search(v,node,str);

    return v;
} //done

std::vector<std::string> trie::get_prefixes(const std::string & str) const {
    trie_node * node = this->m_root;
    unsigned long long i = 0;
    unsigned long long n = str.length();
    const char * c = str.c_str();
    std::vector<std::string> v;
    std::string s;
    while (i < n){
        node = node->children[c[i]];
        if(node != nullptr){
            s.push_back(node->payload);
            if(node->is_terminal){
                v.push_back(s);
            }
        }
        ++i;
    }
    return v;
}


const trie_node* iterator_rekurze(const trie_node* p,int index = 0){
    const trie_node* node = p;
    for (int i = index; i < num_chars; ++i) {
        if(node->children[i] != nullptr){
            node = node->children[i];
            if(node->is_terminal){
                return node;
            }else{
                return iterator_rekurze(node);
            }
        }
    }
    if(p->parent != nullptr){
        iterator_rekurze(p->parent,p->payload+1);
    }else{
        return nullptr;
    }
}

trie::const_iterator trie::begin() const {
    const trie_node* x = iterator_rekurze(this->m_root);
    return {x};
}

trie::const_iterator trie::end() const {
    return {};
}





void trie::swap(trie& rhs) {}

bool trie::operator==(const trie& rhs) const {
    return true;
}

bool trie::operator<(const trie& rhs) const {
    return false;
}

trie trie::operator&(trie const& rhs) const {
    return {};
}

trie trie::operator|(trie const& rhs) const {
    return {};
}

bool operator!=(const trie& lhs, const trie& rhs) {
	return !(lhs == rhs);
}

bool operator>(const trie& lhs, const trie& rhs) {
	return rhs < lhs;
}

bool operator<=(const trie& lhs, const trie& rhs) {
	return !(lhs > rhs);
}

bool operator>=(const trie& lhs, const trie& rhs) {
	return !(lhs < rhs);
}

void swap(trie& lhs, trie& rhs) {
    lhs.swap(rhs);
}

std::ostream& operator<<(std::ostream& out, trie const& trie) {
    return out;
}






trie::const_iterator& trie::const_iterator::operator++() {
    this->current_node = iterator_rekurze(this->current_node);
    return *this;
}

trie::const_iterator trie::const_iterator::operator++(int) {
    this->current_node = iterator_rekurze(this->current_node);
    return *this;
}

trie::const_iterator::const_iterator(const trie_node* node) {
    this->current_node = node;
}

bool trie::const_iterator::operator==(const trie::const_iterator& rhs) const {
    if(rhs.current_node != nullptr && this->current_node != nullptr){
        return true;
    }else if(rhs.current_node == nullptr && this->current_node == nullptr){
        return true;
    }
    return false;
}

bool trie::const_iterator::operator!=(const trie::const_iterator& rhs) const {
    return !(*this==rhs);
    //return false;
}

trie::const_iterator::reference trie::const_iterator::operator*() const {
    const trie_node * tmp = this->current_node;
    std::string result = "";
    while(tmp != nullptr)
    {
        if(tmp->payload != 0) {
            result.push_back(tmp->payload);
        }
        tmp = tmp->parent;
    }

    std::reverse(result.begin(), result.end());
    return result;
}
