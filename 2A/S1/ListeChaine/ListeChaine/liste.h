typedef struct Element Element;
struct Element {

	int m_data;
	Element* m_next;
};

Element* createListNode(int p_value);
void freeList(Element * p_pRoot);
Element* addFirst(Element* p_pRoot, int p_value);
Element* pop(Element* p_pRoot, int* p_result);

Element* addLast(Element* p_pRoot, int p_value);
Element* suppressionF(Element* p_pRoot); // A Corriger.

Element* insertionFRec(Element* p_element, Element* p_nouveau); // A Verifier.
Element* suppressionFRec(Element* p_element); // A Verifier

void printList(Element* p_pRoot);


Element* addSortAsc(Element* p_element, int p_value);
void addSortAsco(Element** p_element, int p_value);

Element* addSortDesc(Element* p_element, int p_value);