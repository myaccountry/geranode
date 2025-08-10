#include <iostream>
using namespace std;

template <typename type>
class node {
private:
	size_t len = 0;
public:
	type value;
	node *prev = nullptr;
	node *next = nullptr;

	node()
		: value(0), len(1) {};
	node(const node &obj) {
		this->copy(obj);
	};
	node(type value)
		: value(value), len(1) {};
	node(type value, node *next): value(value), next(next) {
		if (next)
			this->len = ++next->len;
		else
			this->len = 1;
	};
	node(node *prev, type value) : value(value), prev(prev) {
		if (prev)
			this->len = ++prev->len;
		else
			this->len = 1;
	};
	node(node *prev_, type value, node *next_) : value(value), prev(prev_), next(next_) {
		if (this->prev)
			this->len = ++this->prev->len;
		else {
			if (this->next)
				this->len = ++this->next->len;
			else
				this->len = 1;
		}
	};

	~node() {
		this->clear();
	};

	node &operator=(const node &obj) {
		this->copy(obj);
		return *this;
	};

	friend ostream &operator<<(ostream &out, node &obj) {
		auto it = obj.begin();
		out << "-[" << *it;
		for (size_t i = 1; ++it != obj.end(); i++)
			out << ", " << *it;
		out << "]-";
		return out;
	};

	void append(type elem) {
		node<type> *stdata = new node<type>(elem);
		node<type> *last = this;
		while (last->next)
			last = last->next;
		last->next = stdata;
		stdata->prev = last;
		this->len++;
	};

	void appbeg(type elem) {
		node<type> *stdata = new node<type>(elem);
		node<type> *first = this;
		while (first->prev)
			first = first->prev;
		first->prev = stdata;
		stdata->next = first;
		this->len++;
	};

	void before(type elem, size_t index) {
		node<type> *tmp = new node<type>(this->value);
		iterator it = this->begin();
		++it;

		for (size_t i = 1; it != this->end(); ++it, ++i) {
			if (i == index)
				tmp->append(elem);
			tmp->append(*it);
		}
		if (index >= this->size())
        	tmp->append(elem);

		this->copy(*tmp);
		delete tmp;
	};

	void after(type elem, size_t index) {
		node<type> *tmp = new node<type>(this->value);
		iterator it = this->begin();
		++it;

		for (size_t i = 1; it != this->end(); ++it, ++i) {
			if (i == index + 1)
				tmp->append(elem);
			tmp->append(*it);
		}
		if (index >= this->size())
        	tmp->append(elem);

		this->copy(*tmp);
		delete tmp;
	};

	void clear() {
		node *current = this->next;
		while (current != nullptr) {
			node *next = current->next;
			current->next = nullptr;
			current = next;
		}
		this->next = nullptr;

		current = this->prev;
		while (current != nullptr) {
			node *prev = current->prev;
			current->prev = nullptr;
			current = prev;
		}
		this->prev = nullptr;
	};

	void copy(node &obj) {
		this->value = obj.value;
		this->len = 1;
		this->clear();
	    for (iterator it = obj.begin() + 1; it != obj.end(); ++it)
	    	this->append(*it);
	};

	type getelem(size_t index) {
		iterator it = this->begin() + index;
		return *it;
	};

	size_t size() const {
		return this->len;
	};

public:
	class iterator {
	public:
		node *current;

		explicit iterator(node *node = nullptr) : current(node) {};
		iterator operator=(node *node) {
			current = node;
			return *this;
		};

		type &operator*() const {
			return current->value;
		};

		type *operator->() const {
			return &current->value;
		};

		iterator &operator++() {
			current = current->next;
			return *this;
		};

		iterator operator++(int) {
			iterator tmp = *this;
			current = current->next;
			return tmp;
		};

		iterator operator+(int amount) {
			iterator tmp = *this;
			while (amount-- > 0)
				if (tmp.current->next)
					tmp.current = tmp.current->next;
				else
					return iterator(nullptr);
			return tmp;
		};

		iterator &operator--() {
			current = current->prev;
			return *this;
		};

		iterator operator--(int) {
			iterator tmp = *this;
			current = current->prev;
			return tmp;
		};

		bool operator==(const iterator& obj) const {
			return current == obj.current;
		};

        bool operator!=(const iterator& obj) const {
        	return current != obj.current;
        };
	};

	iterator begin() {
		node *first = this;
		while (first->prev)
			first = first->prev;
		return iterator(first);
	};

	iterator end() {
		return iterator(nullptr);
	};
};
