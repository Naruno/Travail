typedef struct Element Element;
struct Element {

	int m_data;
	Element* m_next;
};

Element* createListNode(int p_value);
void freeList(Element * p_pRoot);

Element* addFirst(Element* p_pRoot, int p_value);
Element* addLast(Element* p_pRoot, int p_value);

Element* addSortAsc(Element* p_element, int p_value);
void addSortAsco(Element** p_element, int p_value);
Element* addSortDesc(Element* p_element, int p_value);

Element* pop(Element* p_pRoot, int* p_result);
Element* popLast(Element* p_element);

int listLength(Element * p_pRoot);
void printList(Element* p_pRoot);
Element * at(Element * p_pRoot, int p_index);