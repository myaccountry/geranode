#include <cstddef>

template <typename type>
class listnode {
public:
	class node {
	public:
		type value;
		node *next = nullptr;
		node *prev = nullptr;
	public:
		node() {};

		node(const type &val) {
			value = val;
		};

		node(const type &val, node *nxt) : next(nxt) {
			value = val;
		};

		node(node *prv, const type &val) : prev(prv) {
			value = val;
		};

		node(node *prv, const type &val, node *nxt) : prev(prv), next(nxt) {
			value = val;
		};
	};

public:
	size_t length = 0;
	node *header = nullptr;
	node *tail = nullptr;

public:
	listnode() {};

	listnode(const type &value) {
		this->header = this->tail = new node(value);
		this->length++;
	};

	listnode(const listnode &obj) {
		node *current = obj.header;
        while (current) {
            this->append(current->value);
            current = current->next;
        }
	};

	~listnode() {
		this->clear();
	};

	listnode &operator=(const listnode &obj) {
		if (this == &obj)
			return *this;

		this->clear();
        node *current = obj.header;
        while (current) {
            this->append(current->value);
            current = current->next;
        }
        return *this;
	};

	friend std::ostream &operator<<(std::ostream &out, const listnode &obj) {
		listnode<type> tmp = listnode::clone(obj);
		iterator it = tmp.begin();
		for (size_t i = 0; it != tmp.end(); i++)
			out << "-[" << *it++ << "]-";
		return out;
	};

	void append(const type &value) {
		node *tmp = new node(value);
		if (this->length == 0) {
			this->header = this->tail = tmp;
		} else {
			this->tail->next = tmp;
			tmp->prev = this->tail;
			this->tail = tmp;
		}
		this->length++;
	};

	void appbeg(const type &value) {
		node *tmp = new node(value);
		if (this->length == 0) {
			this->header = this->tail = tmp;
		} else {
			this->header->prev = tmp;
			tmp->next = this->header;
			this->header = tmp;
		}
		this->length++;
	};

	void before(const type &value, size_t index) {
		if (index == 0) {
			this->appbeg(value);
			return;
		} if (index >= this->length) {
			this->append(value);
			return;
		}

		iterator it = this->begin();
		for (size_t i = 0; i < index; i++)
			++it;
		node *tmp = new node(it.current->prev, value, it.current);
		it.current->prev->next = tmp;
		it.current->prev = tmp;

		this->length++;
	};

	void after(const type &value, size_t index) {
		this->before(value, index + 1);
	};

	void pop(size_t index) {
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
			return;
		}

		iterator it = this->begin();
		for (size_t i = 0; i < index; i++)
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
	};

	void remove(size_t index, size_t amount) {
		for (size_t i = 0; i < amount; i++)
			this->pop(index);
	};

	void clear() {
		node *current = this->header;
		while (current) {
			node *next = current->next;
			delete current;
			current = next;
		}
	};

	type &get(size_t index) {
		iterator it = this->begin();
		while (index-- != 0)
			++it;
		return *it;
	};

	bool find(type elem) {
		iterator it = this->begin();
		for (; it != this->end(); ++it)
			if (*it == elem)
				return true;
		return false;
	};

	size_t size() const {
		return this->length;
	};

	class iterator {
		public:
			node *current = nullptr;
		public:
			iterator(node *curr) : current(curr) {};

			type &operator*() const {
				return current->value;
			};

			type *operator->() const {
				return &current->value;
			};

			type value() const {
				return current->value;
			};

			iterator &operator++() {
				this->current = this->current->next;
				return *this;
			};

			iterator operator++(int) {
				iterator tmp = *this;
				this->current = this->current->next;
				return tmp;
			};

			iterator &operator--() {
				this->current = this->current->prev;
				return *this;
			};

			iterator operator--(int) {
				iterator tmp = *this;
				this->current = this->current->prev;
				return tmp;
			};

			bool operator==(const iterator &obj) {
				return this->current == obj.current;
			};

			bool operator!=(const iterator &obj) {
				return this->current != obj.current;
			};
	};

	iterator begin() {
		return iterator(this->header);
	};

	iterator prend() {
		return iterator(this->tail);
	};

	iterator end() {
		return iterator(nullptr);
	};

	static listnode &clone(const listnode &obj) {
		listnode<type> *tmp = new listnode<type>();
		node *current = obj.header;
        while (current) {
            tmp->append(current->value);
            current = current->next;
        }
        return *tmp;
	};
};
