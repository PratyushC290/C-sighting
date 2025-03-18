#include <stdio.h>
#include <stdlib.h>

struct HNode { 
    char data; 
    int freq; 
    struct HNode *left, *right; 
};

struct PriorityQueue { 
    int size; 
    int capacity; 
    struct HNode* array[100]; 
};


struct HNode* createNode(char data, int freq) { 
    struct HNode* node = (struct HNode*)malloc(sizeof(struct HNode)); 
    node->data = data; 
    node->freq = freq; 
    node->left = node->right = NULL; 
    return node; 
}


struct PriorityQueue* createPriorityQueue(int capacity) {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}


int findInsertPos(struct PriorityQueue* pq, int freq) {
    int low = 0, high = pq->size - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (pq->array[mid]->freq >= freq)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return low;
}


void insertPriorityQueue(struct PriorityQueue* pq, struct HNode* node) {
    if (pq->size == pq->capacity) {
        printf("Priority Queue is full\n");
        return;
    }

    int pos = findInsertPos(pq, node->freq); 

    // Shift elements right to make space
    for (int i = pq->size; i > pos; i--) 
        pq->array[i] = pq->array[i - 1];

    pq->array[pos] = node; 
    pq->size++;
}

struct HNode* extractMin(struct PriorityQueue* pq) {
    if (pq->size == 0) return NULL;
    struct HNode* minNode = pq->array[0];

    // Shift elements left to maintain order
    for (int i = 1; i < pq->size; i++) 
        pq->array[i - 1] = pq->array[i];

    pq->size--;
    return minNode;
}


struct HNode* buildHuffmanTree(char data[], int freq[], int size) { 
    struct PriorityQueue* pq = createPriorityQueue(size);

    for (int i = 0; i < size; i++) { 
        struct HNode *p = createNode(data[i], freq[i]);
        insertPriorityQueue(pq, p);
    }
    
    while (pq->size > 1) { 
        struct HNode* left = extractMin(pq);
        struct HNode* right = extractMin(pq);

        struct HNode* newNode = createNode('$', left->freq + right->freq); 
        newNode->left = left; 
        newNode->right = right;
        
        insertPriorityQueue(pq, newNode);
    } 
    return extractMin(pq);
}


void printHCodes(struct HNode* root, int arr[], int top) {
	if (root->left) { 
		arr[top] = 0; 
		printHCodes(root->left, arr, top + 1);
		} 

	if (root->right) { 
		arr[top] = 1; 
		printHCodes(root->right, arr, top + 1); 
		} 

	if (!root->left && !root->right) { 
		printf("%c: ", root->data); 
		for (int i = 0; i < top; i++) 
			printf("%d", arr[i]); 
			printf("\n"); 
		} 
	} 

void HuffCodes(char data[], int freq[], int size) { 
	struct HNode* root = 
		buildHuffmanTree(data, freq, size); 
	int arr[100], top = 0; 
	printf("\nHuffman Codes:\n"); 	printHCodes(root, arr, top); 
	}


int main() {
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    struct HNode* root = buildHuffmanTree(data, freq, size);
    
    char code[100]; 
    HuffCodes(data, freq, size);
    
    return 0;
}