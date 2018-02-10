#ifndef LIST_MYLIST_H
#define LIST_MYLIST_H

template <typename T, class Allocator = std::allocator<T> >
class MyList{

    struct Node;
    using value_type = T;
    using allocator_type = Allocator;
    using allocator_node = typename Allocator::template rebind<Node>::other;

public:

    class Iterator{

        Iterator(Node * node): m_node(node){};

        bool operator==( const Iterator& other ) const {
            if( this == &other ) {
                return true;
            }
            return m_node == other.m_node;
        }

        bool operator!=( const Iterator& other ) const {
            return !operator==( other );
        }

        T operator*() const {
            if( m_node ) {
                return m_node->m_t;
            }
            return T();
        }

        // Переход к следующему узлу
        void operator++() {
            if( m_node ) {
                m_node = m_node->m_next;
            } // Иначе достигнут конец списка. Уместно возбудить исключение
        }

        private:
            Node * m_node;
    };

    MyList(const allocator_node& b = allocator_node()): m_head(nullptr), B(b){
    };

    MyList(std::initializer_list<T> il,const allocator_node& b = allocator_node()): m_head(nullptr), B(b){
        for(T const * b = il.begin();b != il.end(); b++){
            this->append(*b);
        }
    };

    ~MyList(){
        while( m_head ) {
            remove();
        }
    };

    void remove() {
        if( m_head ) {
            Node* newHead = m_head->m_next;
            B.deallocate(m_head, 1);
            m_head = newHead;
        }
    };

    void append(const T& t){
        if (Node * node = createNewNode(t)) {
            node->m_next = m_head;
            m_head = node;
        }
    };

    Node * createNewNode(T t){
        Node * pNode = B.allocate(1);
        new(pNode) Node;
        return pNode;
    }

    typename MyList<T>::Iterator begin() const {
        return Iterator(m_head);
    }


    typename MyList<T>::Iterator end() const {
        return Iterator(nullptr);
    }

private:
    struct Node{
        Node() : m_next(nullptr) { }

        Node( const T& t ) : m_t( t ), m_next(nullptr) { }

        ~Node(){
        };

        T m_t;

        Node* m_next;
    };

    Node* m_head;

    allocator_node B;
};

#endif //LIST_MYLIST_H