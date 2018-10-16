#pragma once
#include <stack>

namespace myDataStruct {

	template <typename _T>
	class tree {
	private:
		struct Node {
			_T data;
			Node* parent;
			Node* previousBrother;
			Node* nextBrother;
			Node* firstChild;

			Node(_T d = _T(), Node* p = nullptr, Node* pb = nullptr, Node* nb = nullptr, Node* c = nullptr)
				: data(d), parent(p), previousBrother(pb), nextBrother(nb), firstChild(c) {
			}
		};
	public:
		tree(Node* r = nullptr) {
			root = r;
			nodeNum = 0;
		}

		~tree() {
			if (root != nullptr) {
				std::stack<Node*> tempStack;
				if (root->firstChild != nullptr) {
					tempStack.push(root->firstChild);
					while (!tempStack.empty()) {
						Node* n = tempStack.top();
						tempStack.pop();
						if (n->firstChild != nullptr) {
							tempStack.push(n->firstChild);
						}
						if (n->nextBrother != nullptr) {
							tempStack.push(n->nextBrother);
						}
						delete n;
					}
				}
				delete root;
			}
		}

		void setRoot(_T d) {
			Node* n = new Node;
			n->parent = nullptr;
			n->previousBrother = nullptr;
			n->nextBrother = nullptr;
			n->firstChild = nullptr;
			n->data = d;
			root = n;
			++nodeNum;
		}

	public:

		class Myconst_iterator {
		public:
			Myconst_iterator(Node* n = nullptr) {
				current = n;
			}
			Myconst_iterator& operator=(const Node* n) {
				current = n;
				return *this;
			}
			Myconst_iterator& operator=(const Myconst_iterator it) {
				this->current = it.current;
				return *this;
			}
			const _T& operator*() const {
				if (current != nullptr)
					return current->data;
			}
			Myconst_iterator& operator--() {
				if (current->parent != nullptr)
					current = current->parent;
				return *this;
			}
			Myconst_iterator operator--(int) {
				Myconst_iterator _Temp = *this;
				--(*this);
				return _Temp;
			}
			Myconst_iterator& operator++() {
				if (current->firstChild != nullptr)
					current = current->firstChild;
				return *this;
			}
			Myconst_iterator operator++(int) {
				Myconst_iterator _Temp = *this;
				++(*this);
				return _Temp;
			}
			bool operator==(const Myconst_iterator it) {
				if (current == it.current)
					return true;
				return false;
			}
			bool operator!=(const Myconst_iterator it) {
				return (*this) == it;
			}
			Myconst_iterator& shift_left() {
				if (current->previousBrother != nullptr)
					current = current->previousBrother;
				return *this;
			}
			Myconst_iterator& shift_right() {
				if (current->nextBrother != nullptr)
					current = current->nextBrother;
				return *this;
			}

			friend class tree<_T>;

		private:
			Node* current;
		};

		class Myiterator {
		public:
			Myiterator& operator=(Node* n) {
				current = n;
				return *this;
			}
			Myiterator& operator=(const Myiterator it) {
				current = it.current;
				return *this;
			}
			_T& operator*() const {
				if (current != nullptr)
					return current->data;
			}
			Myiterator& operator--() {
				if (current->parent != nullptr)
					current = current->parent;
				return *this;
			}
			Myiterator operator--(int) {
				Myiterator _Temp = *this;
				--(*this);
				return _Temp;
			}
			Myiterator& operator++() {
				if (current->firstChild != nullptr)
					current = current->firstChild;
				return *this;
			}
			Myiterator operator++(int) {
				Myiterator _Temp = *this;
				++(*this);
				return _Temp;
			}
			bool operator==(Myiterator it) {
				if (current == it.current)
					return true;
				return false;
			}
			bool operator!=(Myiterator it) {
				return (*this) == it;
			}
			Myiterator& shift_left() {
				if (current->previousBrother != nullptr)
					current = current->previousBrother;
				return *this;
			}
			Myiterator& shift_right() {
				if (current->nextBrother != nullptr)
					current = current->nextBrother;
				return *this;
			}
			bool isRoot(tree t) {
				if (current == t.root)
					return true;
				return false;
			}

			friend class tree<_T>;
		private:
			Node* current;
		};

		Myiterator insertChild(Myiterator it, _T d) {
			Node* n = new Node;
			n->data = d;
			n->parent = it.current;
			if (it.current->firstChild == nullptr) {
				it.current->firstChild = n;
			}
			else {
				Myiterator nit = it;
				++nit;
				while (nit.current->nextBrother != nullptr) {
					nit = nit.shift_right();
				}
				n->previousBrother = nit.current;
				nit.current->nextBrother = n;
			}
			++nodeNum;
			Myiterator cit;
			cit.current = n;
			return cit;
		}

		Myiterator insertBrother(Myiterator it, _T d) {
			Node* n = new Node;
			n->data = d;
			n->parent = it.current->parent;
			Myiterator nit = it;
			while (nit.current->nextBrother != nullptr) {
				nit = nit.shift_right();
			}
			nit.current->nextBrother = n;
			n->previousBrother = nit.current;
			++nodeNum;
			Myiterator cit;
			cit.current = n;
			return cit;
		}

		Node* begin() {
			return root;
		}

	private:
		Node* root;
		size_t nodeNum;
	};
}