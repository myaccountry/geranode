#include <iostream>
#include "exception.hpp"
using namespace std;

template <typename type>
class listnode {
public:
	struct node {
		type value;
		node *next = nullptr;
		node *prev = nullptr;
		
		node() {}

		node(const type &val) : value(val) {}
				   
		node(const type &val, node *nxt) : next(nxt), value(val) {}

		node(node *prv, const type &val) : value(val), prev(prv) {}

		node(node *prv, const type &val, node *nxt) 
            : prev(prv), value(val), next(nxt) {}
	};

private:
	int length = 0;
	node *header = nullptr;
	node *tail = nullptr;

void check_range(int index)
{
	if (index < 0 || index >= length)
		throw IndexError();
}


public:
	listnode() {}

	listnode(const type &value) 
	{
		this->header = this->tail = new node(value);
		this->length++;
	}

	listnode(const listnode &obj) 
	{
		node *current = obj.header;
        while (current) {
            this->append(current->value);
            current = current->next;
        }
	}
 
	listnode(const initializer_list<type> &init_list)
	{
		for (int i = 0; i < init_list.size(); i++)
			this->append(*(init_list.begin() + i));
	}

	~listnode() 
	{
		this->clear();
	}

	listnode &operator=(const listnode &obj) 
	{
		if (this == &obj)
			return *this;

		this->clear();
        node *current = obj.header;
        while (current) {
            this->append(current->value);
            current = current->next;
        }
        return *this;
	}

	friend ostream &operator<<(ostream &out, const listnode &obj) 
	{
		listnode<type> tmp = listnode::clone(obj);
		iterator it = tmp.begin();
		for (int i = 0; it != tmp.end(); i++)
			out << "-[" << *it++ << "]-";
		return out;
	}

	void append(const type &value) 
	{
		node *tmp = new node(value);
		if (this->length == 0) {
			this->header = this->tail = tmp;
		} else {
			this->tail->next = tmp;
			tmp->prev = this->tail;
			this->tail = tmp;
		}
		this->length++;
	}

	void appbeg(const type &value) 
	{
		node *tmp = new node(value);
		if (this->length == 0) {
			this->header = this->tail = tmp;
		} else {
			this->header->prev = tmp;
			tmp->next = this->header;
			this->header = tmp;
		}
		this->length++;
	}

	void before(const type &value, int index) 
	{
		check_range(index);
		if (index == 0) {
			this->appbeg(value);
			return;
		} 

		iterator it = this->begin();
		for (int i = 0; i < index; i++)
			++it;
	
		node *tmp = new node(it.current->prev, value, it.current);	
		it.current->prev->next = tmp;
		it.current->prev = tmp;

		this->length++;
	}

	void after(const type &value, int index) 
	{
		check_range(index);
		this->before(value, index + 1);
	}

	bool pop(int index) 
	{
		try {
			check_range(index);		
		} catch (const IndexError &err) {
			return false;
		}

		node *tmp;
		if (index == 0) {
			tmp = this->header;
			this->header = this->header->next;
			if (this->header)
				this->header->prev = nullptr;
			else
				this->tail = nullptr;
			delete tmp;
			this->length--;
			return true;
		}

		iterator it = this->begin();
		for (int i = 0; i < index; i++)
			++it;
		tmp = it.current;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		else
			this->tail = tmp->prev;
		delete tmp;
		this->length--;
		return true;
	}

	bool remove(int index, int amount) 
	{
		if (index < 0 || index + amount >= length || amount < 0)
			return false;

		for (int i = 0; i < amount; i++)
			this->pop(index);
		return true;
	}

	bool remove(type elem)
	{
		if (this->index(elem) == -1)
			return false;
		this->pop(this->index(elem));	
		return true;
	}

	void clear() 
	{
		node *current = this->header;
		while (current) {
			node *next = current->next;
			delete current;
			current = next;
		}
	}

	type &get(int index) 
	{
		check_range(index);

		iterator it = this->begin();
		while (index-- != 0)
			++it;
		return *it;
	}

	bool find(type elem) 
	{
		iterator it = this->begin();
		for (; it != this->end(); ++it)
			if (*it == elem)
				return true;
		return false;
	}

	int index(type elem)
	{
		iterator it = this->begin();
		for (int i = 0; it != this->end(); ++it, ++i)
			if (*it == elem)
				return i;
		return -1;
	}

	int size() const 
	{
		return this->length;
	}

	struct iterator {
			node *current = nullptr;
			
			iterator(node *curr) : current(curr) {}

			type &operator*() const 
			{
				return current->value;
			}

			type *operator->() const 
			{
				return &current->value;
			}

			type value() const 
			{
				return current->value;
			}

			iterator &operator++() 
			{
				this->current = this->current->next;
				return *this;
			}

			iterator operator++(int) 
			{
				iterator tmp = *this;
				this->current = this->current->next;
				return tmp;
			}

			iterator &operator--() 
			{
				this->current = this->current->prev;
				return *this;
			}

			iterator operator--(int) 
			{
				iterator tmp = *this;
				this->current = this->current->prev;
				return tmp;
			}

			bool operator==(const iterator &obj) 
			{
				return this->current == obj.current;
			}

			bool operator!=(const iterator &obj) 
			{
				return this->current != obj.current;
			}
	};

	iterator begin() 
	{
		return iterator(this->header);
	}

	iterator prend() 
	{
		return iterator(this->tail);
	}

	iterator end() 
	{
		return iterator(nullptr);
	}

	static listnode &clone(const listnode &obj) 
	{
		listnode<type> *tmp = new listnode<type>();
		node *current = obj.header;
        while (current) {
            tmp->append(current->value);
            current = current->next;
        }
        return *tmp;
	}
};

