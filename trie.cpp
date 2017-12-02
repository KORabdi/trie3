#include <iostream>
#include "trie.hpp"

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

trie::trie(const trie& rhs) {
    this->m_root = rhs.m_root;
    this->m_size = rhs.m_size;
}

trie& trie::operator=(const trie& rhs) {
    this->m_root = rhs.m_root;
    this->m_size = rhs.m_size;
    return *this;
}

trie::trie(trie&& rhs) {
    this->m_root = rhs.m_root;
    this->m_size = rhs.m_size;
}

trie& trie::operator=(trie&& rhs) {
    this->m_root = rhs.m_root;
    this->m_size = rhs.m_size;
    return *this;
}



trie::~trie() {}

size_t trie::size() const {
    return this->m_size;
} //done

bool trie::empty() const {
    return this->size() == 0;
} //done

std::vector<std::string> trie::search_by_prefix(const std::string& str) const {
    return {};
}

std::vector<std::string> trie::get_prefixes(const std::string & str) const {
    return {};
}

trie::const_iterator trie::begin() const {
    return {};
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
    return *this;
}

trie::const_iterator trie::const_iterator::operator++(int) {
    return {};
}

trie::const_iterator::const_iterator(const trie_node* node) {}

bool trie::const_iterator::operator==(const trie::const_iterator& rhs) const {
    return true;
}

bool trie::const_iterator::operator!=(const trie::const_iterator& rhs) const {
    return false;
}

trie::const_iterator::reference trie::const_iterator::operator*() const {
    return {};
}
